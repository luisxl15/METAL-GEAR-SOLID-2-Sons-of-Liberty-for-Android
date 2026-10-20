// SPDX-FileCopyrightText: Copyright 2026 Eden Emulator Project
// SPDX-FileCopyrightText: Copyright 2025 lsfg-vk
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Geracao de quadros (LSFG) para o MGS2 recompilado: porte da cadeia lsfg-vk como o
// emulador Eden a implementou (PR #4263, src/video_core/renderer_vulkan/present/lsfg_*),
// sem o invólucro Vulkan do Eden.
//
// O jogo desenha em GLES. Com a geracao ligada:
//   GL:     o blit final do jogo (1280x720) vai para um AHardwareBuffer em vez da janela;
//           no eglSwapBuffers sai uma fence nativa (EGL_ANDROID_native_fence_sync).
//   Vulkan: dono da janela (swapchain FIFO). Importa o AHardwareBuffer, copia para a
//           entrada da cadeia, roda mipmaps/alpha/beta (uma vez por quadro do jogo) e
//           gamma/delta/generate (uma vez por quadro gerado), e apresenta GERADO -> REAL,
//           escalando para a janela (faixas pretas ou esticado).
// Os shaders vem do Lossless.dll do PROPRIO usuario (Lossless Scaling, Steam): o recurso
// RCDATA id+49 de cada shader ja e SPIR-V fp16. O DLL e lido como dado, nunca executado.
//
// Tudo que pode falhar (DLL, extensoes, features, pipelines) e testado em fg_inicia,
// ANTES de o GL abrir mao da janela: se falhar, o jogo segue no caminho GL de sempre.

#if !defined(LSFG_SO_PARSER) && !defined(LSFG_PC)   /* teste_parser.cpp / teste_cadeia.cpp (PC) */
#define VK_USE_PLATFORM_ANDROID_KHR 1
#include <vulkan/vulkan.h>
#include <android/hardware_buffer.h>
#include <android/native_window.h>
#elif defined(LSFG_PC)
#include <vulkan/vulkan.h>
#endif

#include <algorithm>
#include <array>
#include <atomic>
#include <cmath>
#include <condition_variable>
#include <cstdio>
#include <cstring>
#include <deque>
#include <functional>
#include <initializer_list>
#include <map>
#include <mutex>
#include <optional>
#include <span>
#include <thread>
#include <utility>
#include <vector>

#if !defined(LSFG_SO_PARSER) && !defined(LSFG_PC)
#include <poll.h>
#include <pthread.h>
#include <sys/resource.h>
#include <unistd.h>
#endif

extern "C" void rt_log(const char *fmt, ...);
extern "C" int aj_int(const char *chave, int padrao);

namespace {

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;
using f32 = float;

#ifndef DLL_LOSSLESS
#define DLL_LOSSLESS "/storage/emulated/0/Android/data/jp.konami.mgs2hd.shield/files/Lossless.dll"
#endif

// ============================================================================
// Lossless.dll -> SPIR-V (porte de video_core/frame_gen/lossless_dll.cpp e
// lsfg_translate.cpp do Eden; sem o cache, a leitura direta leva milissegundos)
// ============================================================================
namespace Shader {
constexpr u32 MIPMAPS = 255;
constexpr u32 GENERATE = 256;
constexpr std::array<u32, 4> ALPHA{290, 291, 292, 293};
constexpr std::array<u32, 5> BETA{298, 299, 300, 301, 302};
constexpr std::array<u32, 5> GAMMA{280, 282, 283, 284, 285};
constexpr std::array<u32, 10> DELTA{280, 286, 287, 288, 289, 281, 294, 295, 296, 297};
constexpr u32 NATIVE_FP16_OFFSET = 49;
constexpr u32 PRIMEIRO = 280, ULTIMO = 302;
} // namespace Shader

struct Leitor {
    std::span<const u8> img;
    template <typename T> bool le(size_t o, T &v) const {
        if (o > img.size() || img.size() - o < sizeof(T)) return false;
        std::memcpy(&v, img.data() + o, sizeof(T));
        return true;
    }
};
struct Secao { u32 va, vtam, raw, rawtam; };

std::optional<size_t> rva_para_arquivo(const std::vector<Secao> &s, u32 rva) {
    for (const Secao &x : s) {
        const u32 vao = std::max(x.vtam, x.rawtam);
        if (!vao || rva < x.va) continue;
        if (rva - x.va < vao) return size_t{x.raw} + (rva - x.va);
    }
    return std::nullopt;
}

struct EntradaRes { u32 id, off; bool dir, nomeada; };
bool entradas(const Leitor &r, size_t dir, std::vector<EntradaRes> &out) {
    u16 nn = 0, ni = 0;
    if (!r.le(dir + 12, nn) || !r.le(dir + 14, ni)) return false;
    out.clear();
    for (size_t i = 0; i < size_t{nn} + ni; ++i) {
        u32 nome = 0, dado = 0;
        const size_t o = dir + 16 + i * 8;
        if (!r.le(o, nome) || !r.le(o + 4, dado)) return false;
        out.push_back({nome & 0x7fffffffu, dado & 0x7fffffffu, (dado & 0x80000000u) != 0, (nome & 0x80000000u) != 0});
    }
    return true;
}

constexpr u32 SPIRV_MAGICO = 0x07230203;
bool eh_spirv(std::span<const u8> b) {
    if (b.size() < 20 || b.size() % 4) return false;
    u32 m; std::memcpy(&m, b.data(), 4);
    return m == SPIRV_MAGICO;
}

// Eden lsfg_translate.cpp: renumera os bindings na ordem (set, binding) -> 0..n-1, que e
// a ordem dos tipos declarados em cada LsfgPass
std::vector<u32> adota_spirv(std::span<const u8> blob) {
    if (!eh_spirv(blob)) return {};
    std::vector<u32> w(blob.size() / 4);
    std::memcpy(w.data(), blob.data(), blob.size());
    struct Slot { u32 set, binding; size_t lit; };
    std::map<u32, u32> sets;
    std::vector<Slot> slots;
    size_t o = 5;
    while (o + 1 <= w.size()) {
        const u32 len = w[o] >> 16, op = w[o] & 0xffff;
        if (!len || o + len > w.size()) return w;
        if (op == 54) break;                                  // OpFunction
        if (op == 71 && len >= 4) {                           // OpDecorate
            if (w[o + 2] == 34) sets[w[o + 1]] = w[o + 3];    // DescriptorSet
            else if (w[o + 2] == 33) slots.push_back({0, w[o + 3], o + 3});   // Binding
        }
        o += len;
    }
    for (Slot &s : slots) { auto h = sets.find(w[s.lit - 2]); s.set = h == sets.end() ? 0 : h->second; }
    std::stable_sort(slots.begin(), slots.end(), [](const Slot &a, const Slot &b) {
        return std::tie(a.set, a.binding) < std::tie(b.set, b.binding); });
    for (size_t i = 0; i < slots.size(); ++i) w[slots[i].lit] = (u32)i;
    return w;
}

std::vector<u32> ids_desempenho() {
    std::vector<u32> ids{Shader::MIPMAPS, Shader::GENERATE};
    for (u32 i = Shader::PRIMEIRO; i <= Shader::ULTIMO; ++i) ids.push_back(i);
    return ids;
}

// 0 = ok; senao texto do motivo
const char *carrega_shaders(std::map<u32, std::vector<u32>> &out) {
    FILE *f = std::fopen(DLL_LOSSLESS, "rb");
    if (!f) return "Lossless.dll nao encontrado (copie para Android/data/jp.konami.mgs2hd.shield/files/)";
    std::vector<u8> img;
    std::fseek(f, 0, SEEK_END); long n = std::ftell(f); std::fseek(f, 0, SEEK_SET);
    if (n > 0) { img.resize((size_t)n); if (std::fread(img.data(), 1, img.size(), f) != img.size()) img.clear(); }
    std::fclose(f);
    if (img.empty()) return "Lossless.dll ilegivel";
    const Leitor r{img};
    u16 mz = 0; u32 pe = 0, assin = 0;
    if (!r.le(0, mz) || mz != 0x5A4D || !r.le(0x3C, pe) || !r.le(pe, assin) || assin != 0x00004550) return "Lossless.dll nao e um PE";
    const size_t opt = pe + 4 + 20;
    u16 magico = 0; if (!r.le(opt, magico)) return "PE sem cabecalho opcional";
    const size_t dd = opt + (magico == 0x20B ? 112 : magico == 0x10B ? 96 : 0);
    if (dd == opt) return "PE de tipo desconhecido";
    u16 nsec = 0, tam_opt = 0;
    if (!r.le(pe + 6, nsec) || !r.le(pe + 4 + 16, tam_opt)) return "PE sem secoes";
    std::vector<Secao> secs;
    for (size_t i = 0; i < nsec; ++i) {
        const size_t o = pe + 4 + 20 + tam_opt + i * 40; Secao s{};
        if (!r.le(o + 8, s.vtam) || !r.le(o + 12, s.va) || !r.le(o + 16, s.rawtam) || !r.le(o + 20, s.raw)) return "secao ilegivel";
        secs.push_back(s);
    }
    u32 rva_res = 0;
    if (!r.le(dd + 2 * 8, rva_res) || !rva_res) return "PE sem recursos";
    const auto base = rva_para_arquivo(secs, rva_res);
    if (!base) return "recursos fora das secoes";
    std::map<u32, std::span<const u8>> recursos;
    std::vector<EntradaRes> tipos, nomes, idiomas;
    if (!entradas(r, *base, tipos)) return "diretorio de recursos ilegivel";
    for (const auto &t : tipos) {
        if (t.nomeada || t.id != 10 || !t.dir) continue;       // RT_RCDATA
        if (!entradas(r, *base + t.off, nomes)) return "RCDATA ilegivel";
        for (const auto &nm : nomes) {
            if (nm.nomeada || !nm.dir) continue;
            if (!entradas(r, *base + nm.off, idiomas)) continue;
            for (const auto &id : idiomas) {
                if (id.dir) continue;
                u32 rva = 0, tam = 0;
                if (!r.le(*base + id.off, rva) || !r.le(*base + id.off + 4, tam) || !tam) continue;
                const auto o = rva_para_arquivo(secs, rva);
                if (!o || *o > img.size() || img.size() - *o < tam) continue;
                recursos[nm.id] = std::span<const u8>(img.data() + *o, tam);
                break;
            }
        }
    }
    out.clear();
    for (u32 id : ids_desempenho()) {
        auto h = recursos.find(id + Shader::NATIVE_FP16_OFFSET);
        if (h == recursos.end() || !eh_spirv(h->second)) return "Lossless.dll sem os shaders SPIR-V (versao antiga do Lossless Scaling?)";
        auto w = adota_spirv(h->second);
        if (w.empty()) return "shader SPIR-V invalido";
        out.emplace(id, std::move(w));
    }
    return nullptr;
}

#ifdef LSFG_SO_PARSER
} // namespace
#else
// ============================================================================
// Vulkan minimo
// ============================================================================
struct Vk {
    VkInstance inst = VK_NULL_HANDLE;
    VkPhysicalDevice pd = VK_NULL_HANDLE;
    VkDevice dev = VK_NULL_HANDLE;
    VkQueue fila = VK_NULL_HANDLE;
    u32 qf = 0;
    VkPhysicalDeviceMemoryProperties mp{};
    bool sem_fd = false;           // importa fence nativa como semaforo (senao espera na CPU)
#ifndef LSFG_PC
    PFN_vkGetAndroidHardwareBufferPropertiesANDROID ahb_props = nullptr;
#endif
    PFN_vkImportSemaphoreFdKHR importa_fd = nullptr;
} V;

#define VKCHK(x) do { VkResult _r = (x); if (_r != VK_SUCCESS) { rt_log("LSFG: %s falhou (%d) em %s:%d", #x, (int)_r, __FILE__, __LINE__); return false; } } while (0)

u32 tipo_mem(u32 bits, VkMemoryPropertyFlags quer) {
    for (u32 i = 0; i < V.mp.memoryTypeCount; ++i)
        if ((bits & (1u << i)) && (V.mp.memoryTypes[i].propertyFlags & quer) == quer) return i;
    for (u32 i = 0; i < V.mp.memoryTypeCount; ++i)
        if (bits & (1u << i)) return i;
    return 0;
}

// Lixeira: tudo que a cadeia cria vai para ca e morre junto (o Eden usa RAII do wrapper)
struct Lixeira {
    std::vector<std::function<void()>> itens;
    void poe(std::function<void()> f) { itens.push_back(std::move(f)); }
    void esvazia() { for (auto it = itens.rbegin(); it != itens.rend(); ++it) (*it)(); itens.clear(); }
};
Lixeira *g_lix = nullptr;   // a cadeia em construcao

// ---- lsfg_common ----------------------------------------------------------
constexpr VkFormat LSFG_DEFAULT_FORMAT = VK_FORMAT_R8G8B8A8_UNORM;
constexpr VkFormat LSFG_FLOW_FORMAT = VK_FORMAT_R8_UNORM;
constexpr VkFormat LSFG_MOTION_FORMAT = VK_FORMAT_R16G16B16A16_SFLOAT;
constexpr size_t LSFG_HISTORY_SLOTS = 3;
constexpr size_t LSFG_MAX_TARGETS = 7;
constexpr size_t LSFG_MAX_GENERATIONS = 3;
constexpr size_t LSFG_GENERATION_SLOTS = LSFG_MAX_GENERATIONS * (LSFG_MAX_GENERATIONS + 1) / 2;
constexpr size_t LSFG_MIP_LEVELS = 7;
constexpr size_t LSFG_ALPHA_STAGES = 4;
constexpr size_t LSFG_BETA_STAGES = 5;
constexpr size_t LSFG_BETA_OUTPUTS = 6;
constexpr size_t LSFG_GAMMA_STAGES = 5;
constexpr size_t LSFG_GAMMA_TEMPS = 3;
constexpr size_t LSFG_DELTA_STAGES = 10;
constexpr size_t LSFG_DELTA_TEMPS = 3;
constexpr size_t LSFG_DELTA_INSTANCES = 3;

constexpr size_t LsfgGenerationSlot(size_t count, size_t gen) { return (count - 1) * count / 2 + gen; }
constexpr f32 LsfgTimestamp(size_t gen, size_t count) { return (f32)(gen + 1) / (f32)(count + 1); }
constexpr size_t LsfgSlotCount(size_t slot) { size_t c = 1; while (LsfgGenerationSlot(c + 1, 0) <= slot) ++c; return c; }
constexpr f32 LsfgSlotTimestamp(size_t slot) { const size_t c = LsfgSlotCount(slot); return LsfgTimestamp(slot - LsfgGenerationSlot(c, 0), c); }

u32 GroupCount(u32 size, u32 shift) { return (size + (1u << shift) - 1) >> shift; }

class LsfgImage {
public:
    LsfgImage() = default;
    LsfgImage(VkExtent2D e, VkFormat f = LSFG_DEFAULT_FORMAT) : extent{std::max(1u, e.width), std::max(1u, e.height)}, format{f} {
        const VkImageCreateInfo ci{VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO, nullptr, 0, VK_IMAGE_TYPE_2D, format,
            {extent.width, extent.height, 1}, 1, 1, VK_SAMPLE_COUNT_1_BIT, VK_IMAGE_TILING_OPTIMAL,
            VK_IMAGE_USAGE_TRANSFER_SRC_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_STORAGE_BIT | VK_IMAGE_USAGE_SAMPLED_BIT,
            VK_SHARING_MODE_EXCLUSIVE, 0, nullptr, VK_IMAGE_LAYOUT_UNDEFINED};
        if (vkCreateImage(V.dev, &ci, nullptr, &image) != VK_SUCCESS) { rt_log("LSFG: vkCreateImage %ux%u fmt %d falhou", extent.width, extent.height, (int)format); return; }
        VkMemoryRequirements req; vkGetImageMemoryRequirements(V.dev, image, &req);
        const VkMemoryAllocateInfo ai{VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO, nullptr, req.size, tipo_mem(req.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT)};
        vkAllocateMemory(V.dev, &ai, nullptr, &mem);
        vkBindImageMemory(V.dev, image, mem, 0);
        const VkImageViewCreateInfo vi{VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO, nullptr, 0, image, VK_IMAGE_VIEW_TYPE_2D, format, {},
            {VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1}};
        vkCreateImageView(V.dev, &vi, nullptr, &view);
        VkImage i = image; VkImageView v = view; VkDeviceMemory m = mem;
        if (g_lix) g_lix->poe([i, v, m] { vkDestroyImageView(V.dev, v, nullptr); vkDestroyImage(V.dev, i, nullptr); vkFreeMemory(V.dev, m, nullptr); });
    }
    VkImage Handle() const { return image; }
    VkImageView View() const { return view; }
    VkExtent2D Extent() const { return extent; }
    VkFormat Format() const { return format; }
    VkImageLayout Layout() const { return layout; }
    void SetLayout(VkImageLayout l) { layout = l; }
    bool ok() const { return image && view && mem; }
private:
    VkImage image = VK_NULL_HANDLE;
    VkImageView view = VK_NULL_HANDLE;
    VkDeviceMemory mem = VK_NULL_HANDLE;
    VkExtent2D extent{};
    VkFormat format = VK_FORMAT_UNDEFINED;
    VkImageLayout layout = VK_IMAGE_LAYOUT_UNDEFINED;
};
using LsfgImagePair = std::array<LsfgImage, 2>;
using LsfgImageHistory = std::array<LsfgImagePair, LSFG_HISTORY_SLOTS>;

struct LsfgConstants {
    std::array<u32, 2> input_offset;
    u32 first_iter, first_iter_s, advanced_color_kind, hdr_support;
    f32 resolution_inv_scale, timestamp, ui_threshold;
    std::array<u32, 3> padding;
};
static_assert(sizeof(LsfgConstants) == 48);

class LsfgResources {
public:
    LsfgResources() = default;
    explicit LsfgResources(f32 fs) : flow_scale{fs} {}
    VkSampler GetSampler(VkSamplerAddressMode modo = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER, VkCompareOp cmp = VK_COMPARE_OP_NEVER, bool branco = false) {
        const u64 k = (u64)modo | ((u64)cmp << 8) | ((u64)branco << 16);
        auto it = samplers.find(k); if (it != samplers.end()) return it->second;
        const VkSamplerCreateInfo ci{VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO, nullptr, 0, VK_FILTER_LINEAR, VK_FILTER_LINEAR,
            VK_SAMPLER_MIPMAP_MODE_LINEAR, modo, modo, modo, 0.0f, VK_FALSE, 0.0f, VK_FALSE, cmp, 0.0f, VK_LOD_CLAMP_NONE,
            branco ? VK_BORDER_COLOR_FLOAT_OPAQUE_WHITE : VK_BORDER_COLOR_FLOAT_TRANSPARENT_BLACK, VK_FALSE};
        VkSampler s = VK_NULL_HANDLE; vkCreateSampler(V.dev, &ci, nullptr, &s);
        if (g_lix) g_lix->poe([s] { vkDestroySampler(V.dev, s, nullptr); });
        return samplers[k] = s;
    }
    VkBuffer GetBuffer(f32 ts = 0.0f, bool fi = false, bool fis = false) {
        u32 tb; std::memcpy(&tb, &ts, 4);
        const u64 k = (u64)tb | ((u64)fi << 32) | ((u64)fis << 33);
        auto it = buffers.find(k); if (it != buffers.end()) return it->second;
        const VkBufferCreateInfo bi{VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO, nullptr, 0, sizeof(LsfgConstants),
            VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_SHARING_MODE_EXCLUSIVE, 0, nullptr};
        VkBuffer b = VK_NULL_HANDLE; vkCreateBuffer(V.dev, &bi, nullptr, &b);
        VkMemoryRequirements req; vkGetBufferMemoryRequirements(V.dev, b, &req);
        const VkMemoryAllocateInfo ai{VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO, nullptr, req.size,
            tipo_mem(req.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT)};
        VkDeviceMemory m = VK_NULL_HANDLE; vkAllocateMemory(V.dev, &ai, nullptr, &m); vkBindBufferMemory(V.dev, b, m, 0);
        const LsfgConstants c{{0, 0}, fi ? 1u : 0u, fis ? 1u : 0u, 0, 0, 1.0f / flow_scale, ts, 0.5f, {0, 0, 0}};
        void *p = nullptr; vkMapMemory(V.dev, m, 0, sizeof c, 0, &p); std::memcpy(p, &c, sizeof c); vkUnmapMemory(V.dev, m);
        if (g_lix) g_lix->poe([b, m] { vkDestroyBuffer(V.dev, b, nullptr); vkFreeMemory(V.dev, m, nullptr); });
        return buffers[k] = b;
    }
    static VkDeviceSize BufferSize() { return sizeof(LsfgConstants); }
private:
    f32 flow_scale = 1.0f;
    std::map<u64, VkSampler> samplers;
    std::map<u64, VkBuffer> buffers;
};

class LsfgBarriers {
public:
    explicit LsfgBarriers(VkCommandBuffer c) : cmd{c} {}
    LsfgBarriers &WriteToRead(LsfgImage &i) { return Push(i, VK_ACCESS_SHADER_WRITE_BIT, VK_ACCESS_SHADER_READ_BIT); }
    LsfgBarriers &ReadToWrite(LsfgImage &i) { return Push(i, VK_ACCESS_SHADER_READ_BIT, VK_ACCESS_SHADER_WRITE_BIT); }
    LsfgBarriers &WriteToRead(LsfgImage *i) { return i ? WriteToRead(*i) : *this; }
    LsfgBarriers &ReadToWrite(LsfgImage *i) { return i ? ReadToWrite(*i) : *this; }
    LsfgBarriers &DiscardToWrite(VkImage img) {
        b.push_back({VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER, nullptr, 0, VK_ACCESS_SHADER_WRITE_BIT, VK_IMAGE_LAYOUT_UNDEFINED,
                     VK_IMAGE_LAYOUT_GENERAL, VK_QUEUE_FAMILY_IGNORED, VK_QUEUE_FAMILY_IGNORED, img, {VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1}});
        return *this;
    }
    template <typename R> LsfgBarriers &WriteToReadAll(R &r) { for (auto &i : r) WriteToRead(i); return *this; }
    template <typename R> LsfgBarriers &ReadToWriteAll(R &r) { for (auto &i : r) ReadToWrite(i); return *this; }
    void Build() {
        if (b.empty()) return;
        vkCmdPipelineBarrier(cmd, VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT, VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT, 0, 0, nullptr, 0, nullptr, (u32)b.size(), b.data());
        b.clear();
    }
private:
    LsfgBarriers &Push(LsfgImage &i, VkAccessFlags s, VkAccessFlags d) {
        b.push_back({VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER, nullptr, s, d, i.Layout(), VK_IMAGE_LAYOUT_GENERAL,
                     VK_QUEUE_FAMILY_IGNORED, VK_QUEUE_FAMILY_IGNORED, i.Handle(), {VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1}});
        i.SetLayout(VK_IMAGE_LAYOUT_GENERAL);
        return *this;
    }
    VkCommandBuffer cmd;
    std::vector<VkImageMemoryBarrier> b;
};

class LsfgDescriptorWriter {
public:
    explicit LsfgDescriptorWriter(VkDescriptorSet s) : set{s} {}
    LsfgDescriptorWriter &AddSampler(VkSampler s) { return PushImage(VK_DESCRIPTOR_TYPE_SAMPLER, s, VK_NULL_HANDLE); }
    LsfgDescriptorWriter &AddSampledImage(const LsfgImage &i) { return PushImage(VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, VK_NULL_HANDLE, i.View()); }
    LsfgDescriptorWriter &AddSampledImage(const LsfgImage *i) { return PushImage(VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, VK_NULL_HANDLE, i ? i->View() : VK_NULL_HANDLE); }
    LsfgDescriptorWriter &AddStorageImage(const LsfgImage &i) { return PushImage(VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, VK_NULL_HANDLE, i.View()); }
    LsfgDescriptorWriter &AddStorageView(VkImageView v) { return PushImage(VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, VK_NULL_HANDLE, v); }
    template <typename R> LsfgDescriptorWriter &AddSampledImages(const R &r) { for (const auto &i : r) AddSampledImage(i); return *this; }
    template <typename R> LsfgDescriptorWriter &AddStorageImages(const R &r) { for (const auto &i : r) AddStorageImage(i); return *this; }
    LsfgDescriptorWriter &AddUniformBuffer(VkBuffer buf, VkDeviceSize tam) {
        bi.push_back({buf, 0, tam});
        w.push_back({VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET, nullptr, set, binding++, 0, 1, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, nullptr, &bi.back(), nullptr});
        return *this;
    }
    void Build() { if (!w.empty()) vkUpdateDescriptorSets(V.dev, (u32)w.size(), w.data(), 0, nullptr); w.clear(); }
private:
    LsfgDescriptorWriter &PushImage(VkDescriptorType t, VkSampler s, VkImageView v) {
        ii.push_back({s, v, v == VK_NULL_HANDLE ? VK_IMAGE_LAYOUT_UNDEFINED : VK_IMAGE_LAYOUT_GENERAL});
        w.push_back({VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET, nullptr, set, binding++, 0, 1, t, &ii.back(), nullptr, nullptr});
        return *this;
    }
    VkDescriptorSet set;
    u32 binding = 0;
    std::deque<VkDescriptorImageInfo> ii;
    std::deque<VkDescriptorBufferInfo> bi;
    std::vector<VkWriteDescriptorSet> w;
};

using LsfgBindings = std::initializer_list<std::pair<u32, VkDescriptorType>>;
std::map<u32, VkShaderModule> g_modulos;   // shaders do Lossless.dll (vivem enquanto o dispositivo vive)
bool g_pipeline_falhou = false;

class LsfgPass {
public:
    LsfgPass() = default;
    LsfgPass(u32 shader_id, LsfgBindings bindings) {
        std::vector<VkDescriptorSetLayoutBinding> b;
        for (const auto &[n, t] : bindings)
            for (u32 k = 0; k < n; ++k) b.push_back({(u32)b.size(), t, 1, VK_SHADER_STAGE_COMPUTE_BIT, nullptr});
        const VkDescriptorSetLayoutCreateInfo li{VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO, nullptr, 0, (u32)b.size(), b.data()};
        vkCreateDescriptorSetLayout(V.dev, &li, nullptr, &dsl);
        const VkPipelineLayoutCreateInfo pli{VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO, nullptr, 0, 1, &dsl, 0, nullptr};
        vkCreatePipelineLayout(V.dev, &pli, nullptr, &pl);
        auto h = g_modulos.find(shader_id);
        const VkComputePipelineCreateInfo ci{VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO, nullptr, 0,
            {VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO, nullptr, 0, VK_SHADER_STAGE_COMPUTE_BIT,
             h == g_modulos.end() ? VK_NULL_HANDLE : h->second, "main", nullptr}, pl, VK_NULL_HANDLE, 0};
        const VkResult r = h == g_modulos.end() ? VK_ERROR_INITIALIZATION_FAILED
                                                : vkCreateComputePipelines(V.dev, VK_NULL_HANDLE, 1, &ci, nullptr, &pipe);
        if (r != VK_SUCCESS) { g_pipeline_falhou = true; rt_log("LSFG: pipeline do shader %u falhou (%d)", shader_id, (int)r); }
        VkDescriptorSetLayout a = dsl; VkPipelineLayout b2 = pl; VkPipeline c = pipe;
        if (g_lix) g_lix->poe([a, b2, c] { if (c) vkDestroyPipeline(V.dev, c, nullptr); vkDestroyPipelineLayout(V.dev, b2, nullptr); vkDestroyDescriptorSetLayout(V.dev, a, nullptr); });
    }
    VkDescriptorSetLayout SetLayout() const { return dsl; }
    void Bind(VkCommandBuffer c, VkDescriptorSet s) const { BindPipeline(c); BindSet(c, s); }
    void BindPipeline(VkCommandBuffer c) const { vkCmdBindPipeline(c, VK_PIPELINE_BIND_POINT_COMPUTE, pipe); }
    void BindSet(VkCommandBuffer c, VkDescriptorSet s) const { vkCmdBindDescriptorSets(c, VK_PIPELINE_BIND_POINT_COMPUTE, pl, 0, 1, &s, 0, nullptr); }
private:
    VkDescriptorSetLayout dsl = VK_NULL_HANDLE;
    VkPipelineLayout pl = VK_NULL_HANDLE;
    VkPipeline pipe = VK_NULL_HANDLE;
};

std::vector<VkDescriptorSet> aloca_sets(VkDescriptorPool pool, const std::vector<VkDescriptorSetLayout> &layouts) {
    std::vector<VkDescriptorSet> s(layouts.size());
    const VkDescriptorSetAllocateInfo ai{VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO, nullptr, pool, (u32)layouts.size(), layouts.data()};
    if (vkAllocateDescriptorSets(V.dev, &ai, s.data()) != VK_SUCCESS) { rt_log("LSFG: vkAllocateDescriptorSets(%zu) falhou", layouts.size()); g_pipeline_falhou = true; }
    return s;
}

// ---- lsfg_mipmaps ----------------------------------------------------------
class LsfgMipmaps {
public:
    LsfgMipmaps() = default;
    LsfgMipmaps(LsfgResources &res, VkDescriptorPool pool, LsfgImagePair &fr, f32 flow_scale) : frames{&fr} {
        pass = LsfgPass(Shader::MIPMAPS, {{1, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER}, {1, VK_DESCRIPTOR_TYPE_SAMPLER},
                                          {1, VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE}, {LSFG_MIP_LEVELS, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE}});
        const VkExtent2D in = (*frames)[0].Extent();
        flow_extent = {std::max(1u, (u32)((f32)in.width * flow_scale)), std::max(1u, (u32)((f32)in.height * flow_scale))};
        for (size_t i = 0; i < LSFG_MIP_LEVELS; ++i)
            out_images[i] = LsfgImage({flow_extent.width >> i, flow_extent.height >> i}, LSFG_FLOW_FORMAT);
        auto s = aloca_sets(pool, std::vector<VkDescriptorSetLayout>(2, pass.SetLayout()));
        for (size_t i = 0; i < 2; ++i) {
            sets[i] = s[i];
            LsfgDescriptorWriter(sets[i]).AddUniformBuffer(res.GetBuffer(), LsfgResources::BufferSize()).AddSampler(res.GetSampler())
                .AddSampledImage((*frames)[i]).AddStorageImages(out_images).Build();
        }
    }
    void Dispatch(VkCommandBuffer c, u64 fc) {
        const size_t slot = fc % 2;
        LsfgBarriers(c).WriteToRead((*frames)[slot]).ReadToWriteAll(out_images).Build();
        pass.Bind(c, sets[slot]);
        vkCmdDispatch(c, GroupCount(flow_extent.width, 6), GroupCount(flow_extent.height, 6), 1);
    }
    LsfgImage &Output(size_t l) { return out_images[l]; }
private:
    LsfgImagePair *frames = nullptr;
    LsfgPass pass;
    std::array<VkDescriptorSet, 2> sets{};
    VkExtent2D flow_extent{};
    std::array<LsfgImage, LSFG_MIP_LEVELS> out_images;
};

// ---- lsfg_alpha ------------------------------------------------------------
VkExtent2D metade(VkExtent2D e) { return {(e.width + 1) >> 1, (e.height + 1) >> 1}; }

class LsfgAlphaPasses {
public:
    LsfgAlphaPasses() = default;
    explicit LsfgAlphaPasses(int) {
        p[0] = LsfgPass(Shader::ALPHA[0], {{1, VK_DESCRIPTOR_TYPE_SAMPLER}, {1, VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE}, {1, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE}});
        p[1] = LsfgPass(Shader::ALPHA[1], {{1, VK_DESCRIPTOR_TYPE_SAMPLER}, {1, VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE}, {1, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE}});
        p[2] = LsfgPass(Shader::ALPHA[2], {{1, VK_DESCRIPTOR_TYPE_SAMPLER}, {1, VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE}, {2, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE}});
        p[3] = LsfgPass(Shader::ALPHA[3], {{1, VK_DESCRIPTOR_TYPE_SAMPLER}, {2, VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE}, {2, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE}});
    }
    const LsfgPass &Get(size_t s) const { return p[s]; }
private:
    std::array<LsfgPass, LSFG_ALPHA_STAGES> p;
};

class LsfgAlpha {
public:
    LsfgAlpha() = default;
    LsfgAlpha(const LsfgAlphaPasses &ps, LsfgResources &res, VkDescriptorPool pool, LsfgImage &in) : passes{&ps}, input{&in} {
        const VkExtent2D h = metade(input->Extent()), q = metade(h);
        temp1 = LsfgImage(h); temp2 = LsfgImage(h);
        for (size_t i = 0; i < 2; ++i) {
            temp3[i] = LsfgImage(q);
            for (size_t j = 0; j < LSFG_HISTORY_SLOTS; ++j) out_images[j][i] = LsfgImage(q);
        }
        std::vector<VkDescriptorSetLayout> l;
        for (size_t i = 0; i < LSFG_ALPHA_STAGES - 1; ++i) l.push_back(passes->Get(i).SetLayout());
        for (size_t i = 0; i < LSFG_HISTORY_SLOTS; ++i) l.push_back(passes->Get(3).SetLayout());
        auto s = aloca_sets(pool, l);
        for (size_t i = 0; i < LSFG_ALPHA_STAGES - 1; ++i) sets[i] = s[i];
        for (size_t i = 0; i < LSFG_HISTORY_SLOTS; ++i) last_sets[i] = s[LSFG_ALPHA_STAGES - 1 + i];
        const VkSampler sm = res.GetSampler();
        LsfgDescriptorWriter(sets[0]).AddSampler(sm).AddSampledImage(*input).AddStorageImage(temp1).Build();
        LsfgDescriptorWriter(sets[1]).AddSampler(sm).AddSampledImage(temp1).AddStorageImage(temp2).Build();
        LsfgDescriptorWriter(sets[2]).AddSampler(sm).AddSampledImage(temp2).AddStorageImages(temp3).Build();
        for (size_t i = 0; i < LSFG_HISTORY_SLOTS; ++i)
            LsfgDescriptorWriter(last_sets[i]).AddSampler(sm).AddSampledImages(temp3).AddStorageImages(out_images[i]).Build();
    }
    void PushBarriers(LsfgBarriers &b, u64 fc, size_t st) {
        switch (st) {
        case 0: b.WriteToRead(*input).ReadToWrite(temp1); break;
        case 1: b.WriteToRead(temp1).ReadToWrite(temp2); break;
        case 2: b.WriteToRead(temp2).ReadToWriteAll(temp3); break;
        default: b.WriteToReadAll(temp3).ReadToWriteAll(out_images[fc % LSFG_HISTORY_SLOTS]); break;
        }
    }
    void DispatchStage(VkCommandBuffer c, u64 fc, size_t st) {
        const VkExtent2D e = st < 2 ? temp1.Extent() : temp3[0].Extent();
        const VkDescriptorSet s = st < LSFG_ALPHA_STAGES - 1 ? sets[st] : last_sets[fc % LSFG_HISTORY_SLOTS];
        passes->Get(st).BindSet(c, s);
        vkCmdDispatch(c, GroupCount(e.width, 3), GroupCount(e.height, 3), 1);
    }
    LsfgImageHistory &Outputs() { return out_images; }
private:
    const LsfgAlphaPasses *passes = nullptr;
    LsfgImage *input = nullptr;
    std::array<VkDescriptorSet, LSFG_ALPHA_STAGES - 1> sets{};
    std::array<VkDescriptorSet, LSFG_HISTORY_SLOTS> last_sets{};
    LsfgImage temp1, temp2;
    LsfgImagePair temp3;
    LsfgImageHistory out_images;
};

// ---- lsfg_beta -------------------------------------------------------------
class LsfgBeta {
public:
    LsfgBeta() = default;
    LsfgBeta(LsfgResources &res, VkDescriptorPool pool, LsfgImageHistory &ins) : inputs{&ins} {
        passes[0] = LsfgPass(Shader::BETA[0], {{1, VK_DESCRIPTOR_TYPE_SAMPLER}, {6, VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE}, {2, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE}});
        for (size_t i = 1; i < LSFG_BETA_STAGES - 1; ++i)
            passes[i] = LsfgPass(Shader::BETA[i], {{1, VK_DESCRIPTOR_TYPE_SAMPLER}, {2, VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE}, {2, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE}});
        passes[4] = LsfgPass(Shader::BETA[4], {{1, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER}, {1, VK_DESCRIPTOR_TYPE_SAMPLER},
                                               {2, VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE}, {6, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE}});
        const VkExtent2D e = (*inputs)[0][0].Extent();
        for (size_t i = 0; i < 2; ++i) { temp1[i] = LsfgImage(e); temp2[i] = LsfgImage(e); }
        for (size_t i = 0; i < LSFG_BETA_OUTPUTS; ++i) out_images[i] = LsfgImage({e.width >> i, e.height >> i}, LSFG_FLOW_FORMAT);
        std::vector<VkDescriptorSetLayout> l;
        for (size_t i = 0; i < LSFG_HISTORY_SLOTS; ++i) l.push_back(passes[0].SetLayout());
        for (size_t i = 1; i < LSFG_BETA_STAGES; ++i) l.push_back(passes[i].SetLayout());
        auto s = aloca_sets(pool, l);
        for (size_t i = 0; i < LSFG_HISTORY_SLOTS; ++i) first_sets[i] = s[i];
        for (size_t i = 0; i < LSFG_BETA_STAGES - 1; ++i) sets[i] = s[LSFG_HISTORY_SLOTS + i];
        const VkSampler sm = res.GetSampler();
        const VkSampler borda = res.GetSampler(VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER, VK_COMPARE_OP_NEVER, true);
        for (size_t i = 0; i < LSFG_HISTORY_SLOTS; ++i)
            LsfgDescriptorWriter(first_sets[i]).AddSampler(borda).AddSampledImages((*inputs)[(i + 1) % LSFG_HISTORY_SLOTS])
                .AddSampledImages((*inputs)[(i + 2) % LSFG_HISTORY_SLOTS]).AddSampledImages((*inputs)[i % LSFG_HISTORY_SLOTS])
                .AddStorageImages(temp1).Build();
        LsfgDescriptorWriter(sets[0]).AddSampler(sm).AddSampledImages(temp1).AddStorageImages(temp2).Build();
        LsfgDescriptorWriter(sets[1]).AddSampler(sm).AddSampledImages(temp2).AddStorageImages(temp1).Build();
        LsfgDescriptorWriter(sets[2]).AddSampler(sm).AddSampledImages(temp1).AddStorageImages(temp2).Build();
        LsfgDescriptorWriter(sets[3]).AddUniformBuffer(res.GetBuffer(0.5f), LsfgResources::BufferSize()).AddSampler(sm)
            .AddSampledImages(temp2).AddStorageImages(out_images).Build();
    }
    void Dispatch(VkCommandBuffer c, u64 fc) {
        const VkExtent2D e = temp1[0].Extent();
        const u32 gx = GroupCount(e.width, 3), gy = GroupCount(e.height, 3);
        LsfgBarriers b(c);
        for (auto &s : *inputs) b.WriteToReadAll(s);
        b.ReadToWriteAll(temp1).Build();
        passes[0].Bind(c, first_sets[fc % LSFG_HISTORY_SLOTS]); vkCmdDispatch(c, gx, gy, 1);
        LsfgBarriers(c).WriteToReadAll(temp1).ReadToWriteAll(temp2).Build();
        passes[1].Bind(c, sets[0]); vkCmdDispatch(c, gx, gy, 1);
        LsfgBarriers(c).WriteToReadAll(temp2).ReadToWriteAll(temp1).Build();
        passes[2].Bind(c, sets[1]); vkCmdDispatch(c, gx, gy, 1);
        LsfgBarriers(c).WriteToReadAll(temp1).ReadToWriteAll(temp2).Build();
        passes[3].Bind(c, sets[2]); vkCmdDispatch(c, gx, gy, 1);
        LsfgBarriers(c).WriteToReadAll(temp2).ReadToWriteAll(out_images).Build();
        passes[4].Bind(c, sets[3]); vkCmdDispatch(c, GroupCount(e.width, 5), GroupCount(e.height, 5), 1);
    }
    LsfgImage &Output(size_t l) { return out_images[l]; }
private:
    LsfgImageHistory *inputs = nullptr;
    std::array<LsfgPass, LSFG_BETA_STAGES> passes;
    std::array<VkDescriptorSet, LSFG_HISTORY_SLOTS> first_sets{};
    std::array<VkDescriptorSet, LSFG_BETA_STAGES - 1> sets{};
    LsfgImagePair temp1, temp2;
    std::array<LsfgImage, LSFG_BETA_OUTPUTS> out_images;
};

// ---- lsfg_gamma ------------------------------------------------------------
class LsfgGamma {
public:
    LsfgGamma() = default;
    LsfgGamma(LsfgResources &res, VkDescriptorPool pool, LsfgImageHistory &ins, LsfgImage &flow, LsfgImage *prev)
        : inputs{&ins}, flow_input{&flow}, previous{prev} {
        passes[0] = LsfgPass(Shader::GAMMA[0], {{1, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER}, {2, VK_DESCRIPTOR_TYPE_SAMPLER},
                                                {5, VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE}, {3, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE}});
        passes[1] = LsfgPass(Shader::GAMMA[1], {{1, VK_DESCRIPTOR_TYPE_SAMPLER}, {3, VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE}, {2, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE}});
        passes[2] = LsfgPass(Shader::GAMMA[2], {{1, VK_DESCRIPTOR_TYPE_SAMPLER}, {2, VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE}, {2, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE}});
        passes[3] = LsfgPass(Shader::GAMMA[3], {{1, VK_DESCRIPTOR_TYPE_SAMPLER}, {2, VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE}, {2, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE}});
        passes[4] = LsfgPass(Shader::GAMMA[4], {{1, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER}, {2, VK_DESCRIPTOR_TYPE_SAMPLER},
                                                {4, VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE}, {1, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE}});
        const VkExtent2D e = (*inputs)[0][0].Extent();
        for (auto &i : temp1) i = LsfgImage(e);
        for (auto &i : temp2) i = LsfgImage(e);
        out_image = LsfgImage(e, LSFG_MOTION_FORMAT);
        std::vector<VkDescriptorSetLayout> l;
        for (size_t s = 0; s < LSFG_GENERATION_SLOTS; ++s) {
            for (size_t i = 0; i < LSFG_HISTORY_SLOTS; ++i) l.push_back(passes[0].SetLayout());
            for (size_t i = 1; i < LSFG_GAMMA_STAGES; ++i) l.push_back(passes[i].SetLayout());
        }
        auto ow = aloca_sets(pool, l);
        const VkSampler sm = res.GetSampler();
        const VkSampler borda = res.GetSampler(VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER, VK_COMPARE_OP_NEVER, true);
        const VkSampler beira = res.GetSampler(VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE, VK_COMPARE_OP_ALWAYS, false);
        size_t nx = 0;
        for (size_t s = 0; s < LSFG_GENERATION_SLOTS; ++s) {
            Generation &g = gens[s];
            const VkBuffer buf = res.GetBuffer(LsfgSlotTimestamp(s), previous == nullptr);
            for (size_t i = 0; i < LSFG_HISTORY_SLOTS; ++i) g.first[i] = ow[nx++];
            for (size_t i = 0; i < LSFG_GAMMA_STAGES - 1; ++i) g.sets[i] = ow[nx++];
            for (size_t i = 0; i < LSFG_HISTORY_SLOTS; ++i)
                LsfgDescriptorWriter(g.first[i]).AddUniformBuffer(buf, LsfgResources::BufferSize()).AddSampler(borda).AddSampler(beira)
                    .AddSampledImages((*inputs)[(i + 2) % LSFG_HISTORY_SLOTS]).AddSampledImages((*inputs)[i % LSFG_HISTORY_SLOTS])
                    .AddSampledImage(previous).AddStorageImages(temp1).Build();
            LsfgDescriptorWriter(g.sets[0]).AddSampler(sm).AddSampledImages(temp1).AddStorageImages(temp2).Build();
            LsfgDescriptorWriter(g.sets[1]).AddSampler(sm).AddSampledImages(temp2).AddStorageImage(temp1[0]).AddStorageImage(temp1[1]).Build();
            LsfgDescriptorWriter(g.sets[2]).AddSampler(sm).AddSampledImage(temp1[0]).AddSampledImage(temp1[1]).AddStorageImages(temp2).Build();
            LsfgDescriptorWriter(g.sets[3]).AddUniformBuffer(buf, LsfgResources::BufferSize()).AddSampler(sm).AddSampler(beira)
                .AddSampledImages(temp2).AddSampledImage(previous).AddSampledImage(*flow_input).AddStorageImage(out_image).Build();
        }
    }
    void Dispatch(VkCommandBuffer c, u64 fc, size_t slot) {
        const Generation &g = gens[slot];
        const VkExtent2D e = temp1[0].Extent();
        const u32 gx = GroupCount(e.width, 3), gy = GroupCount(e.height, 3);
        const size_t hist = fc % LSFG_HISTORY_SLOTS, prevh = (fc + 2) % LSFG_HISTORY_SLOTS;
        LsfgBarriers(c).WriteToReadAll((*inputs)[prevh]).WriteToReadAll((*inputs)[hist]).WriteToRead(previous).ReadToWriteAll(temp1).Build();
        passes[0].Bind(c, g.first[hist]); vkCmdDispatch(c, gx, gy, 1);
        LsfgBarriers(c).WriteToReadAll(temp1).ReadToWriteAll(temp2).Build();
        passes[1].Bind(c, g.sets[0]); vkCmdDispatch(c, gx, gy, 1);
        LsfgBarriers(c).WriteToReadAll(temp2).ReadToWrite(temp1[0]).ReadToWrite(temp1[1]).Build();
        passes[2].Bind(c, g.sets[1]); vkCmdDispatch(c, gx, gy, 1);
        LsfgBarriers(c).WriteToRead(temp1[0]).WriteToRead(temp1[1]).ReadToWriteAll(temp2).Build();
        passes[3].Bind(c, g.sets[2]); vkCmdDispatch(c, gx, gy, 1);
        LsfgBarriers(c).WriteToReadAll(temp2).WriteToRead(previous).WriteToRead(*flow_input).ReadToWrite(out_image).Build();
        passes[4].Bind(c, g.sets[3]); vkCmdDispatch(c, gx, gy, 1);
    }
    LsfgImage &Output() { return out_image; }
private:
    struct Generation { std::array<VkDescriptorSet, LSFG_HISTORY_SLOTS> first{}; std::array<VkDescriptorSet, LSFG_GAMMA_STAGES - 1> sets{}; };
    LsfgImageHistory *inputs = nullptr;
    LsfgImage *flow_input = nullptr, *previous = nullptr;
    std::array<LsfgPass, LSFG_GAMMA_STAGES> passes;
    std::array<Generation, LSFG_GENERATION_SLOTS> gens{};
    std::array<LsfgImage, LSFG_GAMMA_TEMPS> temp1;
    LsfgImagePair temp2;
    LsfgImage out_image;
};

// ---- lsfg_delta ------------------------------------------------------------
class LsfgDelta {
public:
    LsfgDelta() = default;
    LsfgDelta(LsfgResources &res, VkDescriptorPool pool, LsfgImageHistory &ins, LsfgImage &flow, LsfgImage *pg, LsfgImage *p1, LsfgImage *p2)
        : inputs{&ins}, flow_input{&flow}, previous_gamma{pg}, previous1{p1}, previous2{p2} {
        passes[0] = LsfgPass(Shader::DELTA[0], {{1, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER}, {2, VK_DESCRIPTOR_TYPE_SAMPLER},
                                                {5, VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE}, {3, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE}});
        passes[1] = LsfgPass(Shader::DELTA[1], {{1, VK_DESCRIPTOR_TYPE_SAMPLER}, {3, VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE}, {2, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE}});
        passes[2] = LsfgPass(Shader::DELTA[2], {{1, VK_DESCRIPTOR_TYPE_SAMPLER}, {2, VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE}, {2, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE}});
        passes[3] = LsfgPass(Shader::DELTA[3], {{1, VK_DESCRIPTOR_TYPE_SAMPLER}, {2, VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE}, {2, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE}});
        passes[4] = LsfgPass(Shader::DELTA[4], {{1, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER}, {2, VK_DESCRIPTOR_TYPE_SAMPLER},
                                                {4, VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE}, {1, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE}});
        passes[5] = LsfgPass(Shader::DELTA[5], {{1, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER}, {2, VK_DESCRIPTOR_TYPE_SAMPLER},
                                                {6, VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE}, {1, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE}});
        for (size_t i = 6; i < LSFG_DELTA_STAGES - 1; ++i)
            passes[i] = LsfgPass(Shader::DELTA[i], {{1, VK_DESCRIPTOR_TYPE_SAMPLER}, {1, VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE}, {1, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE}});
        passes[9] = LsfgPass(Shader::DELTA[9], {{1, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER}, {2, VK_DESCRIPTOR_TYPE_SAMPLER},
                                                {2, VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE}, {1, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE}});
        const VkExtent2D e = (*inputs)[0][0].Extent();
        for (auto &i : temp1) i = LsfgImage(e);
        for (auto &i : temp2) i = LsfgImage(e);
        out1 = LsfgImage(e, LSFG_MOTION_FORMAT);
        out2 = LsfgImage(e, LSFG_MOTION_FORMAT);
        std::vector<VkDescriptorSetLayout> l;
        for (size_t s = 0; s < LSFG_GENERATION_SLOTS; ++s) {
            for (size_t i = 0; i < LSFG_HISTORY_SLOTS; ++i) l.push_back(passes[0].SetLayout());
            for (size_t i = 1; i <= 4; ++i) l.push_back(passes[i].SetLayout());
            for (size_t i = 0; i < LSFG_HISTORY_SLOTS; ++i) l.push_back(passes[5].SetLayout());
            for (size_t i = 6; i < LSFG_DELTA_STAGES; ++i) l.push_back(passes[i].SetLayout());
        }
        auto ow = aloca_sets(pool, l);
        const VkSampler sm = res.GetSampler();
        const VkSampler borda = res.GetSampler(VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER, VK_COMPARE_OP_NEVER, true);
        const VkSampler beira = res.GetSampler(VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE, VK_COMPARE_OP_ALWAYS, false);
        size_t nx = 0;
        for (size_t s = 0; s < LSFG_GENERATION_SLOTS; ++s) {
            Generation &g = gens[s];
            const VkBuffer buf = res.GetBuffer(LsfgSlotTimestamp(s), false, previous_gamma == nullptr);
            for (size_t i = 0; i < LSFG_HISTORY_SLOTS; ++i) g.first[i] = ow[nx++];
            for (size_t i = 0; i < 4; ++i) g.sets[i] = ow[nx++];
            for (size_t i = 0; i < LSFG_HISTORY_SLOTS; ++i) g.sixth[i] = ow[nx++];
            for (size_t i = 4; i < LSFG_DELTA_STAGES - 2; ++i) g.sets[i] = ow[nx++];
            for (size_t i = 0; i < LSFG_HISTORY_SLOTS; ++i) {
                LsfgDescriptorWriter(g.first[i]).AddUniformBuffer(buf, LsfgResources::BufferSize()).AddSampler(borda).AddSampler(beira)
                    .AddSampledImages((*inputs)[(i + 2) % LSFG_HISTORY_SLOTS]).AddSampledImages((*inputs)[i % LSFG_HISTORY_SLOTS])
                    .AddSampledImage(previous_gamma).AddStorageImages(temp1).Build();
                LsfgDescriptorWriter(g.sixth[i]).AddUniformBuffer(buf, LsfgResources::BufferSize()).AddSampler(borda).AddSampler(beira)
                    .AddSampledImages((*inputs)[(i + 2) % LSFG_HISTORY_SLOTS]).AddSampledImages((*inputs)[i % LSFG_HISTORY_SLOTS])
                    .AddSampledImage(previous_gamma).AddSampledImage(previous1).AddStorageImage(temp2[0]).Build();
            }
            LsfgDescriptorWriter(g.sets[0]).AddSampler(sm).AddSampledImages(temp1).AddStorageImages(temp2).Build();
            LsfgDescriptorWriter(g.sets[1]).AddSampler(sm).AddSampledImages(temp2).AddStorageImage(temp1[0]).AddStorageImage(temp1[1]).Build();
            LsfgDescriptorWriter(g.sets[2]).AddSampler(sm).AddSampledImage(temp1[0]).AddSampledImage(temp1[1]).AddStorageImages(temp2).Build();
            LsfgDescriptorWriter(g.sets[3]).AddUniformBuffer(buf, LsfgResources::BufferSize()).AddSampler(sm).AddSampler(beira)
                .AddSampledImages(temp2).AddSampledImage(previous_gamma).AddSampledImage(*flow_input).AddStorageImage(out1).Build();
            LsfgDescriptorWriter(g.sets[4]).AddSampler(sm).AddSampledImage(temp2[0]).AddStorageImage(temp1[0]).Build();
            LsfgDescriptorWriter(g.sets[5]).AddSampler(sm).AddSampledImage(temp1[0]).AddStorageImage(temp2[0]).Build();
            LsfgDescriptorWriter(g.sets[6]).AddSampler(sm).AddSampledImage(temp2[0]).AddStorageImage(temp1[0]).Build();
            LsfgDescriptorWriter(g.sets[7]).AddUniformBuffer(buf, LsfgResources::BufferSize()).AddSampler(sm).AddSampler(beira)
                .AddSampledImage(temp1[0]).AddSampledImage(previous2).AddStorageImage(out2).Build();
        }
    }
    void Dispatch(VkCommandBuffer c, u64 fc, size_t slot) {
        const Generation &g = gens[slot];
        const VkExtent2D e = temp1[0].Extent();
        const u32 gx = GroupCount(e.width, 3), gy = GroupCount(e.height, 3);
        const size_t hist = fc % LSFG_HISTORY_SLOTS, prevh = (fc + 2) % LSFG_HISTORY_SLOTS;
        LsfgBarriers(c).WriteToReadAll((*inputs)[prevh]).WriteToReadAll((*inputs)[hist]).WriteToRead(previous_gamma).ReadToWriteAll(temp1).Build();
        passes[0].Bind(c, g.first[hist]); vkCmdDispatch(c, gx, gy, 1);
        LsfgBarriers(c).WriteToReadAll(temp1).ReadToWriteAll(temp2).Build();
        passes[1].Bind(c, g.sets[0]); vkCmdDispatch(c, gx, gy, 1);
        LsfgBarriers(c).WriteToReadAll(temp2).ReadToWriteAll(temp1).Build();
        passes[2].Bind(c, g.sets[1]); vkCmdDispatch(c, gx, gy, 1);
        LsfgBarriers(c).WriteToReadAll(temp1).ReadToWriteAll(temp2).Build();
        passes[3].Bind(c, g.sets[2]); vkCmdDispatch(c, gx, gy, 1);
        LsfgBarriers(c).WriteToReadAll(temp2).WriteToRead(previous_gamma).WriteToRead(*flow_input).ReadToWrite(out1).Build();
        passes[4].Bind(c, g.sets[3]); vkCmdDispatch(c, gx, gy, 1);
        LsfgBarriers(c).WriteToReadAll((*inputs)[prevh]).WriteToReadAll((*inputs)[hist]).WriteToRead(previous_gamma)
            .WriteToRead(previous1).ReadToWriteAll(temp2).Build();
        passes[5].Bind(c, g.sixth[hist]); vkCmdDispatch(c, gx, gy, 1);
        LsfgBarriers(c).WriteToReadAll(temp2).ReadToWrite(temp1[0]).ReadToWrite(temp1[1]).Build();
        passes[6].Bind(c, g.sets[4]); vkCmdDispatch(c, gx, gy, 1);
        LsfgBarriers(c).WriteToRead(temp1[0]).WriteToRead(temp1[1]).ReadToWriteAll(temp2).Build();
        passes[7].Bind(c, g.sets[5]); vkCmdDispatch(c, gx, gy, 1);
        LsfgBarriers(c).WriteToReadAll(temp2).ReadToWrite(temp1[0]).ReadToWrite(temp1[1]).Build();
        passes[8].Bind(c, g.sets[6]); vkCmdDispatch(c, gx, gy, 1);
        LsfgBarriers(c).WriteToRead(temp1[0]).WriteToRead(temp1[1]).WriteToRead(previous2).ReadToWrite(out2).Build();
        passes[9].Bind(c, g.sets[7]); vkCmdDispatch(c, gx, gy, 1);
    }
    LsfgImage &Output1() { return out1; }
    LsfgImage &Output2() { return out2; }
private:
    struct Generation {
        std::array<VkDescriptorSet, LSFG_HISTORY_SLOTS> first{}, sixth{};
        std::array<VkDescriptorSet, LSFG_DELTA_STAGES - 2> sets{};
    };
    LsfgImageHistory *inputs = nullptr;
    LsfgImage *flow_input = nullptr, *previous_gamma = nullptr, *previous1 = nullptr, *previous2 = nullptr;
    std::array<LsfgPass, LSFG_DELTA_STAGES> passes;
    std::array<Generation, LSFG_GENERATION_SLOTS> gens{};
    std::array<LsfgImage, LSFG_DELTA_TEMPS> temp1;
    LsfgImagePair temp2;
    LsfgImage out1, out2;
};

// ---- lsfg_generate ---------------------------------------------------------
class LsfgGenerate {
public:
    LsfgGenerate() = default;
    LsfgGenerate(LsfgResources &res, VkDescriptorPool pool, LsfgImagePair &fr, LsfgImage &mo, LsfgImage &d1, LsfgImage &d2)
        : frames{&fr}, motion{&mo}, detail1{&d1}, detail2{&d2} {
        pass = LsfgPass(Shader::GENERATE, {{1, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER}, {2, VK_DESCRIPTOR_TYPE_SAMPLER},
                                           {5, VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE}, {1, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE}});
        sampler = res.GetSampler();
        edge = res.GetSampler(VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE, VK_COMPARE_OP_ALWAYS, false);
        auto ow = aloca_sets(pool, std::vector<VkDescriptorSetLayout>(LSFG_GENERATION_SLOTS * LSFG_MAX_TARGETS * 2, pass.SetLayout()));
        size_t nx = 0;
        for (size_t s = 0; s < LSFG_GENERATION_SLOTS; ++s) {
            gens[s].buffer = res.GetBuffer(LsfgSlotTimestamp(s));
            for (auto &t : gens[s].targets) for (auto &d : t.sets) d = ow[nx++];
        }
    }
    void SetTarget(size_t slot, u32 target, VkImageView view) {
        Target &t = gens[slot].targets[target];
        if (t.view == view) return;
        t.view = view;
        for (size_t i = 0; i < 2; ++i)
            LsfgDescriptorWriter(t.sets[i]).AddUniformBuffer(gens[slot].buffer, LsfgResources::BufferSize()).AddSampler(sampler).AddSampler(edge)
                .AddSampledImage((*frames)[1 - i]).AddSampledImage((*frames)[i]).AddSampledImage(*motion)
                .AddSampledImage(*detail1).AddSampledImage(*detail2).AddStorageView(view).Build();
    }
    void Dispatch(VkCommandBuffer c, u64 fc, size_t slot, u32 target, VkImage image, VkExtent2D e) {
        const Target &t = gens[slot].targets[target];
        LsfgBarriers(c).WriteToReadAll(*frames).WriteToRead(*motion).WriteToRead(*detail1).WriteToRead(*detail2).DiscardToWrite(image).Build();
        pass.Bind(c, t.sets[fc % 2]);
        vkCmdDispatch(c, GroupCount(e.width, 4), GroupCount(e.height, 4), 1);
        const VkImageMemoryBarrier depois{VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER, nullptr, VK_ACCESS_SHADER_WRITE_BIT, VK_ACCESS_TRANSFER_READ_BIT,
            VK_IMAGE_LAYOUT_GENERAL, VK_IMAGE_LAYOUT_GENERAL, VK_QUEUE_FAMILY_IGNORED, VK_QUEUE_FAMILY_IGNORED, image, {VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1}};
        vkCmdPipelineBarrier(c, VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT, 0, 0, nullptr, 0, nullptr, 1, &depois);
    }
private:
    struct Target { std::array<VkDescriptorSet, 2> sets{}; VkImageView view = VK_NULL_HANDLE; };
    struct Generation { std::array<Target, LSFG_MAX_TARGETS> targets{}; VkBuffer buffer = VK_NULL_HANDLE; };
    LsfgImagePair *frames = nullptr;
    LsfgImage *motion = nullptr, *detail1 = nullptr, *detail2 = nullptr;
    VkSampler sampler = VK_NULL_HANDLE, edge = VK_NULL_HANDLE;
    LsfgPass pass;
    std::array<Generation, LSFG_GENERATION_SLOTS> gens{};
};

// ---- lsfg_chain ------------------------------------------------------------
class LsfgChain {
public:
    LsfgChain(VkExtent2D extent, VkFormat format, f32 flow_scale) : resources{flow_scale} {
        g_lix = &lixo;
        constexpr u32 FIXOS = 64, POR_SLOT = 112;
        const std::array<VkDescriptorPoolSize, 4> ps{{{VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 4096}, {VK_DESCRIPTOR_TYPE_SAMPLER, 4096},
                                                      {VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, 4096}, {VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, 4096}}};
        const VkDescriptorPoolCreateInfo pi{VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO, nullptr, 0,
                                            FIXOS + POR_SLOT * (u32)LSFG_GENERATION_SLOTS, (u32)ps.size(), ps.data()};
        vkCreateDescriptorPool(V.dev, &pi, nullptr, &pool);
        VkDescriptorPool p = pool; lixo.poe([p] { vkDestroyDescriptorPool(V.dev, p, nullptr); });

        for (auto &i : frames) i = LsfgImage(extent, format);
        mipmaps = LsfgMipmaps(resources, pool, frames, flow_scale);
        alpha_passes = LsfgAlphaPasses(0);
        for (size_t i = 0; i < LSFG_MIP_LEVELS; ++i) alpha[i] = LsfgAlpha(alpha_passes, resources, pool, mipmaps.Output(i));
        beta = LsfgBeta(resources, pool, alpha[0].Outputs());
        constexpr size_t PRIMEIRO_DELTA = 4;
        for (size_t i = 0; i < LSFG_MIP_LEVELS; ++i) {
            const size_t nivel = LSFG_MIP_LEVELS - 1 - i;
            gamma[i] = LsfgGamma(resources, pool, alpha[nivel].Outputs(), beta.Output(std::min(nivel, LSFG_BETA_OUTPUTS - 1)),
                                 i == 0 ? nullptr : &gamma[i - 1].Output());
            if (i < PRIMEIRO_DELTA) continue;
            const size_t k = i - PRIMEIRO_DELTA;
            delta[k] = LsfgDelta(resources, pool, alpha[nivel].Outputs(), beta.Output(nivel),
                                 i == PRIMEIRO_DELTA ? nullptr : &gamma[i - 1].Output(),
                                 i == PRIMEIRO_DELTA ? nullptr : &delta[k - 1].Output1(),
                                 i == PRIMEIRO_DELTA ? nullptr : &delta[k - 1].Output2());
        }
        generate = LsfgGenerate(resources, pool, frames, gamma[LSFG_MIP_LEVELS - 1].Output(),
                                delta[LSFG_DELTA_INSTANCES - 1].Output1(), delta[LSFG_DELTA_INSTANCES - 1].Output2());
        g_lix = nullptr;
    }
    ~LsfgChain() { lixo.esvazia(); }
    LsfgChain(const LsfgChain &) = delete;
    LsfgChain &operator=(const LsfgChain &) = delete;

    void DispatchShared(VkCommandBuffer c, u64 fc) {
        mipmaps.Dispatch(c, fc);
        for (size_t st = 0; st < LSFG_ALPHA_STAGES; ++st) {
            LsfgBarriers b(c);
            for (auto &l : alpha) l.PushBarriers(b, fc, st);
            b.Build();
            alpha_passes.Get(st).BindPipeline(c);
            for (auto &l : alpha) l.DispatchStage(c, fc, st);
        }
        beta.Dispatch(c, fc);
    }
    void DispatchGeneration(VkCommandBuffer c, u64 fc, size_t count, size_t gen, u32 target, VkImage img, VkExtent2D e) {
        const size_t slot = LsfgGenerationSlot(count, gen);
        for (size_t i = 0; i < LSFG_MIP_LEVELS; ++i) {
            gamma[i].Dispatch(c, fc, slot);
            if (i >= 4) delta[i - 4].Dispatch(c, fc, slot);
        }
        generate.Dispatch(c, fc, slot, target, img, e);
    }
    void SetTarget(size_t count, size_t gen, u32 target, VkImageView v) { generate.SetTarget(LsfgGenerationSlot(count, gen), target, v); }
    LsfgImage &Input(u64 fc) { return frames[fc % frames.size()]; }
private:
    Lixeira lixo;
    LsfgResources resources;
    VkDescriptorPool pool = VK_NULL_HANDLE;
    LsfgImagePair frames;
    LsfgMipmaps mipmaps;
    LsfgAlphaPasses alpha_passes;
    std::array<LsfgAlpha, LSFG_MIP_LEVELS> alpha;
    LsfgBeta beta;
    std::array<LsfgGamma, LSFG_MIP_LEVELS> gamma;
    std::array<LsfgDelta, LSFG_DELTA_INSTANCES> delta;
    LsfgGenerate generate;
};

// ============================================================================
// Dispositivo, swapchain, anel de AHardwareBuffer e o apresentador
// ============================================================================
bool tem_ext(const std::vector<VkExtensionProperties> &l, const char *n) {
    for (const auto &e : l) if (!std::strcmp(e.extensionName, n)) return true;
    return false;
}

#ifndef LSFG_PC
bool cria_dispositivo() {
    const VkApplicationInfo app{VK_STRUCTURE_TYPE_APPLICATION_INFO, nullptr, "MGS2 LSFG", 1, "mgs2-recomp", 1, VK_API_VERSION_1_2};
    const char *iext[] = {"VK_KHR_surface", "VK_KHR_android_surface"};
    const VkInstanceCreateInfo ici{VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO, nullptr, 0, &app, 0, nullptr, 2, iext};
    VKCHK(vkCreateInstance(&ici, nullptr, &V.inst));
    u32 n = 0; vkEnumeratePhysicalDevices(V.inst, &n, nullptr);
    if (!n) { rt_log("LSFG: nenhuma GPU Vulkan"); return false; }
    std::vector<VkPhysicalDevice> pds(n); vkEnumeratePhysicalDevices(V.inst, &n, pds.data());
    V.pd = pds[0];
    VkPhysicalDeviceProperties prop; vkGetPhysicalDeviceProperties(V.pd, &prop);
    rt_log("LSFG: GPU %s, Vulkan %u.%u.%u", prop.deviceName, VK_VERSION_MAJOR(prop.apiVersion), VK_VERSION_MINOR(prop.apiVersion), VK_VERSION_PATCH(prop.apiVersion));
    if (prop.apiVersion < VK_API_VERSION_1_2) { rt_log("LSFG: precisa de Vulkan 1.2"); return false; }
    vkGetPhysicalDeviceMemoryProperties(V.pd, &V.mp);

    u32 ne = 0; vkEnumerateDeviceExtensionProperties(V.pd, nullptr, &ne, nullptr);
    std::vector<VkExtensionProperties> exts(ne); vkEnumerateDeviceExtensionProperties(V.pd, nullptr, &ne, exts.data());
    std::vector<const char *> quer = {"VK_KHR_swapchain", "VK_EXT_robustness2", "VK_ANDROID_external_memory_android_hardware_buffer", "VK_EXT_queue_family_foreign"};
    for (const char *e : quer) if (!tem_ext(exts, e)) { rt_log("LSFG: GPU sem %s", e); return false; }
    if (tem_ext(exts, "VK_KHR_external_semaphore_fd")) quer.push_back("VK_KHR_external_semaphore_fd");

    // features: as que os shaders do lsfg-vk exigem (nullDescriptor, vulkanMemoryModel, fp16)
    VkPhysicalDeviceRobustness2FeaturesEXT r2{VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ROBUSTNESS_2_FEATURES_EXT};
    VkPhysicalDeviceVulkan12Features f12{VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES, &r2};
    VkPhysicalDeviceVulkan11Features f11{VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_1_FEATURES, &f12};
    VkPhysicalDeviceFeatures2 f2{VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2, &f11};
    // funcoes 1.1 pelo carregador: a libvulkan da API 26 do NDK so exporta as 1.0
    auto features2 = (PFN_vkGetPhysicalDeviceFeatures2)vkGetInstanceProcAddr(V.inst, "vkGetPhysicalDeviceFeatures2");
    if (!features2) { rt_log("LSFG: sem vkGetPhysicalDeviceFeatures2"); return false; }
    features2(V.pd, &f2);
    if (!r2.nullDescriptor || !f12.vulkanMemoryModel || !f12.shaderFloat16) {
        rt_log("LSFG: GPU sem features (nullDescriptor %d, vulkanMemoryModel %d, shaderFloat16 %d)", r2.nullDescriptor, f12.vulkanMemoryModel, f12.shaderFloat16);
        return false;
    }
    VkPhysicalDeviceRobustness2FeaturesEXT r2e{VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ROBUSTNESS_2_FEATURES_EXT};
    r2e.nullDescriptor = VK_TRUE;
    VkPhysicalDeviceVulkan12Features f12e{VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES, &r2e};
    f12e.vulkanMemoryModel = VK_TRUE;
    f12e.vulkanMemoryModelDeviceScope = f12.vulkanMemoryModelDeviceScope;
    f12e.shaderFloat16 = VK_TRUE;
    f12e.shaderInt8 = f12.shaderInt8;
    f12e.storageBuffer8BitAccess = f12.storageBuffer8BitAccess;
    VkPhysicalDeviceVulkan11Features f11e{VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_1_FEATURES, &f12e};
    f11e.storageBuffer16BitAccess = f11.storageBuffer16BitAccess;
    f11e.uniformAndStorageBuffer16BitAccess = f11.uniformAndStorageBuffer16BitAccess;
    VkPhysicalDeviceFeatures2 f2e{VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2, &f11e};
    f2e.features.shaderInt16 = f2.features.shaderInt16;
    f2e.features.shaderStorageImageExtendedFormats = f2.features.shaderStorageImageExtendedFormats;
    f2e.features.shaderStorageImageReadWithoutFormat = f2.features.shaderStorageImageReadWithoutFormat;
    f2e.features.shaderStorageImageWriteWithoutFormat = f2.features.shaderStorageImageWriteWithoutFormat;

    u32 nq = 0; vkGetPhysicalDeviceQueueFamilyProperties(V.pd, &nq, nullptr);
    std::vector<VkQueueFamilyProperties> qs(nq); vkGetPhysicalDeviceQueueFamilyProperties(V.pd, &nq, qs.data());
    V.qf = ~0u;
    for (u32 i = 0; i < nq; ++i)
        if ((qs[i].queueFlags & (VK_QUEUE_GRAPHICS_BIT | VK_QUEUE_COMPUTE_BIT)) == (VK_QUEUE_GRAPHICS_BIT | VK_QUEUE_COMPUTE_BIT)) { V.qf = i; break; }
    if (V.qf == ~0u) { rt_log("LSFG: sem fila grafica+computacao"); return false; }
    const float prio = 1.0f;
    const VkDeviceQueueCreateInfo qi{VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO, nullptr, 0, V.qf, 1, &prio};
    const VkDeviceCreateInfo di{VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO, &f2e, 0, 1, &qi, 0, nullptr, (u32)quer.size(), quer.data(), nullptr};
    VKCHK(vkCreateDevice(V.pd, &di, nullptr, &V.dev));
    vkGetDeviceQueue(V.dev, V.qf, 0, &V.fila);
    V.ahb_props = (PFN_vkGetAndroidHardwareBufferPropertiesANDROID)vkGetDeviceProcAddr(V.dev, "vkGetAndroidHardwareBufferPropertiesANDROID");
    V.importa_fd = (PFN_vkImportSemaphoreFdKHR)vkGetDeviceProcAddr(V.dev, "vkImportSemaphoreFdKHR");
    if (!V.ahb_props) { rt_log("LSFG: sem vkGetAndroidHardwareBufferPropertiesANDROID"); return false; }
    if (V.importa_fd) {
        VkPhysicalDeviceExternalSemaphoreInfo ei{VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_SEMAPHORE_INFO, nullptr, VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_SYNC_FD_BIT};
        VkExternalSemaphoreProperties ep{VK_STRUCTURE_TYPE_EXTERNAL_SEMAPHORE_PROPERTIES};
        auto props = (PFN_vkGetPhysicalDeviceExternalSemaphoreProperties)vkGetInstanceProcAddr(V.inst, "vkGetPhysicalDeviceExternalSemaphoreProperties");
        if (props) props(V.pd, &ei, &ep);
        V.sem_fd = (ep.externalSemaphoreFeatures & VK_EXTERNAL_SEMAPHORE_FEATURE_IMPORTABLE_BIT) != 0;
    }
    rt_log("LSFG: dispositivo pronto (fila %u, fence GL->Vulkan %s)", V.qf, V.sem_fd ? "por semaforo" : "esperada na CPU");
    return true;
}

#endif // !LSFG_PC
bool cria_modulos(const std::map<u32, std::vector<u32>> &spv) {
    for (const auto &[id, w] : spv) {
        const VkShaderModuleCreateInfo ci{VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO, nullptr, 0, w.size() * 4, w.data()};
        VkShaderModule m = VK_NULL_HANDLE;
        VKCHK(vkCreateShaderModule(V.dev, &ci, nullptr, &m));
        g_modulos[id] = m;
    }
    return true;
}

#ifndef LSFG_PC
// ---- estado do apresentador -------------------------------------------------
constexpr int ANEL = 3;
std::atomic<u64> g_apresentados{0}, g_gerados_tot{0};   // medidor de FPS (Java)
struct Alvo {                      // um AHardwareBuffer que o GL desenha e o Vulkan le
    AHardwareBuffer *ahb = nullptr;
    VkImage img = VK_NULL_HANDLE;
    VkDeviceMemory mem = VK_NULL_HANDLE;
    bool livre = true;
};
struct Pedido { int idx; int fd; u64 quando_ns; };

struct Estado {
    std::mutex m;
    std::condition_variable cv;
    std::deque<Pedido> fila;
    Alvo alvos[ANEL];
    int geracao_anel = 0;           // muda quando os AHB sao refeitos (GL esquece os EGLImage)
    u32 w = 0, h = 0;               // tamanho do quadro do jogo (AHB e entrada da cadeia)
    ANativeWindow *janela = nullptr;        // pedida (fg_janela)
    ANativeWindow *janela_atual = nullptr;  // a da swapchain (com ANativeWindow_acquire)
    bool janela_nova = false;
    bool sair = false;
    int esticar = 0;
    std::thread th;
    u64 reais = 0, gerados = 0, pulados = 0;
} E;

struct Swap {
    VkSurfaceKHR sup = VK_NULL_HANDLE;
    VkSwapchainKHR sc = VK_NULL_HANDLE;
    VkFormat fmt = VK_FORMAT_UNDEFINED;
    VkExtent2D ext{};
    std::vector<VkImage> imgs;
    std::vector<VkSemaphore> prontos;   // um por imagem da swapchain
} S;

#endif // !LSFG_PC
constexpr int NCMD = 8;
struct Cmd { VkCommandBuffer cb = VK_NULL_HANDLE; VkFence f = VK_NULL_HANDLE; VkSemaphore adq = VK_NULL_HANDLE; };
VkCommandPool g_pool = VK_NULL_HANDLE;
Cmd g_cmd[NCMD];
int g_cmd_i = 0;
std::optional<LsfgChain> g_chain;
int g_geracoes = 1;                 // 1 = 2x, 2 = 3x, 3 = 4x
f32 g_fluxo = 1.0f;
std::array<LsfgImage, LSFG_MAX_GENERATIONS> g_saidas;   // alvos do generate (um por quadro gerado)
Lixeira g_lix_saidas;
VkExtent2D g_chain_ext{};
u64 g_contador = 0;
u32 g_morno = 0;

Cmd &proximo_cmd() {
    Cmd &c = g_cmd[g_cmd_i];
    g_cmd_i = (g_cmd_i + 1) % NCMD;
    vkWaitForFences(V.dev, 1, &c.f, VK_TRUE, UINT64_MAX);
    vkResetFences(V.dev, 1, &c.f);
    vkResetCommandBuffer(c.cb, 0);
    const VkCommandBufferBeginInfo bi{VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO, nullptr, VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT, nullptr};
    vkBeginCommandBuffer(c.cb, &bi);
    return c;
}

bool cria_comandos() {
    const VkCommandPoolCreateInfo pi{VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO, nullptr, VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT, V.qf};
    VKCHK(vkCreateCommandPool(V.dev, &pi, nullptr, &g_pool));
    for (auto &c : g_cmd) {
        const VkCommandBufferAllocateInfo ai{VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO, nullptr, g_pool, VK_COMMAND_BUFFER_LEVEL_PRIMARY, 1};
        VKCHK(vkAllocateCommandBuffers(V.dev, &ai, &c.cb));
        const VkFenceCreateInfo fi{VK_STRUCTURE_TYPE_FENCE_CREATE_INFO, nullptr, VK_FENCE_CREATE_SIGNALED_BIT};
        VKCHK(vkCreateFence(V.dev, &fi, nullptr, &c.f));
        const VkSemaphoreCreateInfo si{VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO};
        VKCHK(vkCreateSemaphore(V.dev, &si, nullptr, &c.adq));
    }
    return true;
}

#ifndef LSFG_PC
void destroi_swapchain() {
    if (!V.dev) return;
    vkDeviceWaitIdle(V.dev);
    for (VkSemaphore s : S.prontos) vkDestroySemaphore(V.dev, s, nullptr);
    S.prontos.clear(); S.imgs.clear();
    if (S.sc) vkDestroySwapchainKHR(V.dev, S.sc, nullptr);
    if (S.sup) vkDestroySurfaceKHR(V.inst, S.sup, nullptr);
    S.sc = VK_NULL_HANDLE; S.sup = VK_NULL_HANDLE;
}

bool cria_swapchain(ANativeWindow *jan) {
    const VkAndroidSurfaceCreateInfoKHR si{VK_STRUCTURE_TYPE_ANDROID_SURFACE_CREATE_INFO_KHR, nullptr, 0, jan};
    VKCHK(vkCreateAndroidSurfaceKHR(V.inst, &si, nullptr, &S.sup));
    VkBool32 pode = VK_FALSE; vkGetPhysicalDeviceSurfaceSupportKHR(V.pd, V.qf, S.sup, &pode);
    if (!pode) { rt_log("LSFG: a fila nao apresenta nesta superficie"); return false; }
    VkSurfaceCapabilitiesKHR cap; VKCHK(vkGetPhysicalDeviceSurfaceCapabilitiesKHR(V.pd, S.sup, &cap));
    u32 nf = 0; vkGetPhysicalDeviceSurfaceFormatsKHR(V.pd, S.sup, &nf, nullptr);
    std::vector<VkSurfaceFormatKHR> fs(nf); vkGetPhysicalDeviceSurfaceFormatsKHR(V.pd, S.sup, &nf, fs.data());
    S.fmt = VK_FORMAT_UNDEFINED;
    VkColorSpaceKHR cs = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
    for (auto &f : fs) if (f.format == VK_FORMAT_R8G8B8A8_UNORM) { S.fmt = f.format; cs = f.colorSpace; }
    if (S.fmt == VK_FORMAT_UNDEFINED) for (auto &f : fs) if (f.format == VK_FORMAT_B8G8R8A8_UNORM) { S.fmt = f.format; cs = f.colorSpace; }
    if (S.fmt == VK_FORMAT_UNDEFINED) { rt_log("LSFG: superficie sem RGBA8/BGRA8 UNORM"); return false; }
    // Como o Eden no Android: preTransform IDENTITY (o compositor gira) e o tamanho da janela
    S.ext = {(u32)ANativeWindow_getWidth(jan), (u32)ANativeWindow_getHeight(jan)};
    u32 nimg = std::max(cap.minImageCount + 1, 3u);
    if (cap.maxImageCount) nimg = std::min(nimg, cap.maxImageCount);
    VkCompositeAlphaFlagBitsKHR alfa = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    if (!(cap.supportedCompositeAlpha & alfa)) alfa = VK_COMPOSITE_ALPHA_INHERIT_BIT_KHR;
    const VkSwapchainCreateInfoKHR ci{VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR, nullptr, 0, S.sup, nimg, S.fmt, cs, S.ext, 1,
        VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT, VK_SHARING_MODE_EXCLUSIVE, 0, nullptr,
        VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR, alfa, VK_PRESENT_MODE_FIFO_KHR, VK_TRUE, VK_NULL_HANDLE};
    VKCHK(vkCreateSwapchainKHR(V.dev, &ci, nullptr, &S.sc));
    u32 n = 0; vkGetSwapchainImagesKHR(V.dev, S.sc, &n, nullptr);
    S.imgs.resize(n); vkGetSwapchainImagesKHR(V.dev, S.sc, &n, S.imgs.data());
    for (u32 i = 0; i < n; ++i) {
        const VkSemaphoreCreateInfo s{VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO}; VkSemaphore x;
        VKCHK(vkCreateSemaphore(V.dev, &s, nullptr, &x)); S.prontos.push_back(x);
    }
    rt_log("LSFG: swapchain %ux%u, %u imagens, formato %d, transform da superficie %x", S.ext.width, S.ext.height, n, (int)S.fmt, cap.currentTransform);
    return true;
}

// importa o AHB do alvo k como VkImage (uma vez por geracao do anel)
bool importa_alvo(Alvo &a) {
    VkAndroidHardwareBufferFormatPropertiesANDROID fp{VK_STRUCTURE_TYPE_ANDROID_HARDWARE_BUFFER_FORMAT_PROPERTIES_ANDROID};
    VkAndroidHardwareBufferPropertiesANDROID pr{VK_STRUCTURE_TYPE_ANDROID_HARDWARE_BUFFER_PROPERTIES_ANDROID, &fp};
    VKCHK(V.ahb_props(V.dev, a.ahb, &pr));
    AHardwareBuffer_Desc d; AHardwareBuffer_describe(a.ahb, &d);
    const VkExternalMemoryImageCreateInfo ex{VK_STRUCTURE_TYPE_EXTERNAL_MEMORY_IMAGE_CREATE_INFO, nullptr,
                                             VK_EXTERNAL_MEMORY_HANDLE_TYPE_ANDROID_HARDWARE_BUFFER_BIT_ANDROID};
    const VkImageCreateInfo ci{VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO, &ex, 0, VK_IMAGE_TYPE_2D, VK_FORMAT_R8G8B8A8_UNORM, {d.width, d.height, 1}, 1, 1,
        VK_SAMPLE_COUNT_1_BIT, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_TRANSFER_SRC_BIT | VK_IMAGE_USAGE_SAMPLED_BIT,
        VK_SHARING_MODE_EXCLUSIVE, 0, nullptr, VK_IMAGE_LAYOUT_UNDEFINED};
    VKCHK(vkCreateImage(V.dev, &ci, nullptr, &a.img));
    const VkImportAndroidHardwareBufferInfoANDROID imp{VK_STRUCTURE_TYPE_IMPORT_ANDROID_HARDWARE_BUFFER_INFO_ANDROID, nullptr, a.ahb};
    const VkMemoryDedicatedAllocateInfo ded{VK_STRUCTURE_TYPE_MEMORY_DEDICATED_ALLOCATE_INFO, &imp, a.img, VK_NULL_HANDLE};
    const VkMemoryAllocateInfo ai{VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO, &ded, pr.allocationSize, tipo_mem(pr.memoryTypeBits, 0)};
    VKCHK(vkAllocateMemory(V.dev, &ai, nullptr, &a.mem));
    VKCHK(vkBindImageMemory(V.dev, a.img, a.mem, 0));
    return true;
}

void solta_alvos() {   // com E.m travado e a fila vazia
    if (V.dev) vkDeviceWaitIdle(V.dev);
    for (auto &a : E.alvos) {
        if (a.img) vkDestroyImage(V.dev, a.img, nullptr);
        if (a.mem) vkFreeMemory(V.dev, a.mem, nullptr);
        if (a.ahb) AHardwareBuffer_release(a.ahb);
        a = Alvo{};
    }
}

#endif // !LSFG_PC
bool refaz_cadeia(VkExtent2D e) {
    vkDeviceWaitIdle(V.dev);
    g_chain.reset();
    g_lix_saidas.esvazia();
    g_pipeline_falhou = false;
    g_chain.emplace(e, LSFG_DEFAULT_FORMAT, g_fluxo);
    g_lix = &g_lix_saidas;
    for (auto &s : g_saidas) s = LsfgImage(e);
    g_lix = nullptr;
    g_chain_ext = e;
    g_contador = 0;
    g_morno = 0;
    if (g_pipeline_falhou) { rt_log("LSFG: a cadeia nao montou"); return false; }
    rt_log("LSFG: cadeia montada %ux%u, fluxo %.2f, %d quadro(s) gerado(s) por quadro do jogo", e.width, e.height, g_fluxo, g_geracoes);
    return true;
}

void barreira(VkCommandBuffer c, VkImage img, VkAccessFlags sa, VkAccessFlags da, VkImageLayout de, VkImageLayout para,
              VkPipelineStageFlags ss, VkPipelineStageFlags ds, u32 qde = VK_QUEUE_FAMILY_IGNORED, u32 qpara = VK_QUEUE_FAMILY_IGNORED) {
    const VkImageMemoryBarrier b{VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER, nullptr, sa, da, de, para, qde, qpara, img, {VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1}};
    vkCmdPipelineBarrier(c, ss, ds, 0, 0, nullptr, 0, nullptr, 1, &b);
}

// escala a imagem (layout GENERAL, ja visivel para TRANSFER) para a imagem da swapchain e apresenta
#ifndef LSFG_PC
bool apresenta(VkImage origem, VkExtent2D oe, Cmd *c_usado) {
    if (!S.sc) return false;
    Cmd &c = c_usado ? *c_usado : proximo_cmd();
    u32 k = 0;
    VkResult r = vkAcquireNextImageKHR(V.dev, S.sc, UINT64_MAX, c.adq, VK_NULL_HANDLE, &k);
    if (r != VK_SUCCESS && r != VK_SUBOPTIMAL_KHR) {
        vkEndCommandBuffer(c.cb);
        const VkSubmitInfo vazio{VK_STRUCTURE_TYPE_SUBMIT_INFO};
        vkQueueSubmit(V.fila, 1, &vazio, c.f);      // devolve a fence ao anel
        rt_log("LSFG: vkAcquireNextImageKHR %d", (int)r);
        return false;
    }
    const VkImage dst = S.imgs[k];
    barreira(c.cb, dst, 0, VK_ACCESS_TRANSFER_WRITE_BIT, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
             VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT);
    const VkClearColorValue preto{{0, 0, 0, 1}};
    const VkImageSubresourceRange sr{VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1};
    vkCmdClearColorImage(c.cb, dst, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, &preto, 1, &sr);
    barreira(c.cb, dst, VK_ACCESS_TRANSFER_WRITE_BIT, VK_ACCESS_TRANSFER_WRITE_BIT, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
             VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT);
    // retangulo com a proporcao da origem, centrado (ou esticado), como o blit do GL fazia
    int sw = (int)S.ext.width, sh = (int)S.ext.height, w = sw, h = (int)((long)sw * oe.height / oe.width);
    if (h > sh) { h = sh; w = (int)((long)sh * oe.width / oe.height); }
    if (E.esticar) { w = sw; h = sh; }
    const int x = (sw - w) / 2, y = (sh - h) / 2;
    const VkImageBlit reg{{VK_IMAGE_ASPECT_COLOR_BIT, 0, 0, 1}, {{0, 0, 0}, {(int32_t)oe.width, (int32_t)oe.height, 1}},
                          {VK_IMAGE_ASPECT_COLOR_BIT, 0, 0, 1}, {{x, y, 0}, {x + w, y + h, 1}}};
    vkCmdBlitImage(c.cb, origem, VK_IMAGE_LAYOUT_GENERAL, dst, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &reg, VK_FILTER_LINEAR);
    barreira(c.cb, dst, VK_ACCESS_TRANSFER_WRITE_BIT, 0, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
             VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT);
    vkEndCommandBuffer(c.cb);
    const VkPipelineStageFlags espera = VK_PIPELINE_STAGE_TRANSFER_BIT;
    const VkSubmitInfo si{VK_STRUCTURE_TYPE_SUBMIT_INFO, nullptr, 1, &c.adq, &espera, 1, &c.cb, 1, &S.prontos[k]};
    if (vkQueueSubmit(V.fila, 1, &si, c.f) != VK_SUCCESS) return false;
    const VkPresentInfoKHR pi{VK_STRUCTURE_TYPE_PRESENT_INFO_KHR, nullptr, 1, &S.prontos[k], 1, &S.sc, &k, nullptr};
    r = vkQueuePresentKHR(V.fila, &pi);
    if (r == VK_SUCCESS || r == VK_SUBOPTIMAL_KHR) g_apresentados.fetch_add(1, std::memory_order_relaxed);
    if (r != VK_SUCCESS && r != VK_SUBOPTIMAL_KHR) rt_log("LSFG: vkQueuePresentKHR %d", (int)r);
    return true;
}

void processa(const Pedido &p) {
    Alvo &a = E.alvos[p.idx];
    if (!a.img && !importa_alvo(a)) { if (p.fd >= 0) close(p.fd); return; }
    AHardwareBuffer_Desc d; AHardwareBuffer_describe(a.ahb, &d);
    const VkExtent2D e{d.width, d.height};
    if (!g_chain || e.width != g_chain_ext.width || e.height != g_chain_ext.height) refaz_cadeia(e);

    // espera o GL terminar de desenhar no AHB
    VkSemaphore sem_gl = VK_NULL_HANDLE;
    if (p.fd >= 0) {
        if (V.sem_fd) {
            const VkSemaphoreCreateInfo si{VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO};
            vkCreateSemaphore(V.dev, &si, nullptr, &sem_gl);
            const VkImportSemaphoreFdInfoKHR ii{VK_STRUCTURE_TYPE_IMPORT_SEMAPHORE_FD_INFO_KHR, nullptr, sem_gl,
                VK_SEMAPHORE_IMPORT_TEMPORARY_BIT, VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_SYNC_FD_BIT, p.fd};
            if (V.importa_fd(V.dev, &ii) != VK_SUCCESS) {   // nao importou: o fd ainda e nosso
                vkDestroySemaphore(V.dev, sem_gl, nullptr); sem_gl = VK_NULL_HANDLE;
                pollfd pf{p.fd, POLLIN, 0}; poll(&pf, 1, 100); close(p.fd);
            }
        } else {
            pollfd pf{p.fd, POLLIN, 0}; poll(&pf, 1, 100); close(p.fd);
        }
    }

    const u64 fc = g_contador++;
    LsfgImage &ent = g_chain->Input(fc);
    const bool morno = fc + 1 >= 2;
    g_morno = morno ? g_morno + 1 : 0;
    // atrasado (ja ha outro quadro do jogo na fila): so o real, para o jogo nao desacelerar
    bool atrasado;
    { std::lock_guard<std::mutex> l(E.m); atrasado = !E.fila.empty(); }
    const bool gera = morno && g_morno >= 2 && g_geracoes > 0 && !atrasado;
    if (atrasado) E.pulados++;

    Cmd &c = proximo_cmd();
    // AHB (fila estrangeira, escrita pelo GL) -> entrada da cadeia
    barreira(c.cb, a.img, 0, VK_ACCESS_TRANSFER_READ_BIT, VK_IMAGE_LAYOUT_GENERAL, VK_IMAGE_LAYOUT_GENERAL,
             VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT, VK_QUEUE_FAMILY_FOREIGN_EXT, V.qf);
    barreira(c.cb, ent.Handle(), VK_ACCESS_SHADER_READ_BIT | VK_ACCESS_TRANSFER_READ_BIT, VK_ACCESS_TRANSFER_WRITE_BIT, ent.Layout(),
             VK_IMAGE_LAYOUT_GENERAL, VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT | VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT);
    const VkImageCopy cp{{VK_IMAGE_ASPECT_COLOR_BIT, 0, 0, 1}, {}, {VK_IMAGE_ASPECT_COLOR_BIT, 0, 0, 1}, {}, {e.width, e.height, 1}};
    vkCmdCopyImage(c.cb, a.img, VK_IMAGE_LAYOUT_GENERAL, ent.Handle(), VK_IMAGE_LAYOUT_GENERAL, 1, &cp);
    barreira(c.cb, a.img, VK_ACCESS_TRANSFER_READ_BIT, 0, VK_IMAGE_LAYOUT_GENERAL, VK_IMAGE_LAYOUT_GENERAL,
             VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT, V.qf, VK_QUEUE_FAMILY_FOREIGN_EXT);
    barreira(c.cb, ent.Handle(), VK_ACCESS_TRANSFER_WRITE_BIT, VK_ACCESS_SHADER_READ_BIT | VK_ACCESS_TRANSFER_READ_BIT, VK_IMAGE_LAYOUT_GENERAL,
             VK_IMAGE_LAYOUT_GENERAL, VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT | VK_PIPELINE_STAGE_TRANSFER_BIT);
    ent.SetLayout(VK_IMAGE_LAYOUT_GENERAL);
    if (morno) g_chain->DispatchShared(c.cb, fc);
    vkEndCommandBuffer(c.cb);
    const VkPipelineStageFlags esp = VK_PIPELINE_STAGE_TRANSFER_BIT;
    const VkSubmitInfo si{VK_STRUCTURE_TYPE_SUBMIT_INFO, nullptr, sem_gl ? 1u : 0u, sem_gl ? &sem_gl : nullptr, sem_gl ? &esp : nullptr, 1, &c.cb, 0, nullptr};
    vkQueueSubmit(V.fila, 1, &si, c.f);
    const VkFence copia = c.f;

    // quadros gerados ANTES do real (como o Eden): o gerado fica entre o anterior e este
    if (gera) {
        const size_t n = (size_t)g_geracoes;
        for (size_t g = 0; g < n; ++g) {
            LsfgImage &sai = g_saidas[g];
            g_chain->SetTarget(n, g, (u32)g, sai.View());
            Cmd &cg = proximo_cmd();
            g_chain->DispatchGeneration(cg.cb, fc, n, g, (u32)g, sai.Handle(), sai.Extent());
            sai.SetLayout(VK_IMAGE_LAYOUT_GENERAL);
            apresenta(sai.Handle(), sai.Extent(), &cg);
            E.gerados++;
            g_gerados_tot.fetch_add(1, std::memory_order_relaxed);
        }
    }
    {
        Cmd &cr = proximo_cmd();
        barreira(cr.cb, ent.Handle(), VK_ACCESS_TRANSFER_WRITE_BIT | VK_ACCESS_SHADER_WRITE_BIT, VK_ACCESS_TRANSFER_READ_BIT,
                 VK_IMAGE_LAYOUT_GENERAL, VK_IMAGE_LAYOUT_GENERAL, VK_PIPELINE_STAGE_TRANSFER_BIT | VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT,
                 VK_PIPELINE_STAGE_TRANSFER_BIT);
        apresenta(ent.Handle(), e, &cr);
        E.reais++;
    }
    // a copia terminou: o GL pode desenhar de novo neste AHB
    vkWaitForFences(V.dev, 1, &copia, VK_TRUE, UINT64_MAX);
    if (sem_gl) vkDestroySemaphore(V.dev, sem_gl, nullptr);
    {
        std::lock_guard<std::mutex> l(E.m);
        a.livre = true;
    }
    E.cv.notify_all();
}

void laco() {
    pthread_setname_np(pthread_self(), "LSFG apresenta");
    setpriority(PRIO_PROCESS, 0, -4);
    u64 ultimo_log = 0;
    for (;;) {
        Pedido p{};
        bool tem_janela;
        {
            std::unique_lock<std::mutex> l(E.m);
            E.cv.wait(l, [] { return E.sair || !E.fila.empty() || E.janela_nova; });
            if (E.sair) break;
            if (E.janela_nova) {
                ANativeWindow *j = E.janela;
                l.unlock();
                destroi_swapchain();
                if (E.janela_atual) ANativeWindow_release(E.janela_atual);
                E.janela_atual = j;
                if (j && !cria_swapchain(j)) destroi_swapchain();
                l.lock();
                E.janela_nova = false;
                E.cv.notify_all();          // fg_janela espera isto
            }
            tem_janela = S.sc != VK_NULL_HANDLE;
            if (E.fila.empty()) continue;
            p = E.fila.front(); E.fila.pop_front();
        }
        if (tem_janela) processa(p);
        else {   // sem janela (app em segundo plano): so devolve o AHB
            if (p.fd >= 0) { pollfd pf{p.fd, POLLIN, 0}; poll(&pf, 1, 100); close(p.fd); }
            { std::lock_guard<std::mutex> l(E.m); E.alvos[p.idx].livre = true; }
            E.cv.notify_all();
        }
        const u64 t = E.reais;
        if (t - ultimo_log >= 600) {
            ultimo_log = t;
            rt_log("LSFG: %llu quadros do jogo, %llu gerados, %llu sem gerar (atraso)", (unsigned long long)E.reais,
                   (unsigned long long)E.gerados, (unsigned long long)E.pulados);
        }
    }
}

bool g_ativo = false;

#endif // !LSFG_PC
} // namespace

// ============================================================================
// interface C (gl_manual.c / gl_auto.c)
// ============================================================================
#ifndef LSFG_PC
extern "C" {

void fg_janela(ANativeWindow *jan);

/* o usuario ligou a geracao e o Lossless.dll tem os shaders? */
int fg_quer(void) {
    if (aj_int("lsfg", 0) <= 0) return 0;
    std::map<u32, std::vector<u32>> spv;
    const char *erro = carrega_shaders(spv);
    if (erro) { rt_log("LSFG: desligado: %s", erro); return 0; }
    return 1;
}

/* monta tudo sobre a janela; 1 = o Vulkan e dono da janela, o GL vai para pbuffer */
int fg_inicia(ANativeWindow *jan, int w, int h) {
    if (g_ativo) { fg_janela(jan); return 1; }
    g_geracoes = std::clamp(aj_int("lsfg", 1), 1, (int)LSFG_MAX_GENERATIONS);
    g_fluxo = std::clamp(aj_int("lsfg_fluxo", 100), 25, 100) / 100.0f;
    E.esticar = aj_int("esticar", 0);
    std::map<u32, std::vector<u32>> spv;
    const char *erro = carrega_shaders(spv);
    if (erro) { rt_log("LSFG: %s", erro); return 0; }
    rt_log("LSFG: %zu shaders lidos do Lossless.dll", spv.size());
    if (!cria_dispositivo() || !cria_modulos(spv) || !cria_comandos()) goto falha;
    // a cadeia inteira e montada AQUI (pipelines de todos os shaders): se algum falhar,
    // o jogo ainda nao perdeu a janela
    if (!refaz_cadeia({(u32)(w > 0 ? w : 1280), (u32)(h > 0 ? h : 720)})) goto falha;
    if (!cria_swapchain(jan)) goto falha;
    ANativeWindow_acquire(jan);
    E.janela = E.janela_atual = jan;
    E.th = std::thread(laco);
    g_ativo = true;
    rt_log("LSFG: LIGADO (%dx)", g_geracoes + 1);
    return 1;
falha:
    rt_log("LSFG: nao iniciou; o jogo segue sem geracao de quadros");
    destroi_swapchain();
    g_chain.reset(); g_lix_saidas.esvazia();
    if (V.dev) {
        for (auto &c : g_cmd) { if (c.f) vkDestroyFence(V.dev, c.f, nullptr); if (c.adq) vkDestroySemaphore(V.dev, c.adq, nullptr); c = Cmd{}; }
        if (g_pool) vkDestroyCommandPool(V.dev, g_pool, nullptr);
        g_pool = VK_NULL_HANDLE;
        for (auto &[id, m] : g_modulos) vkDestroyShaderModule(V.dev, m, nullptr);
        g_modulos.clear();
        vkDestroyDevice(V.dev, nullptr);
    }
    if (V.inst) vkDestroyInstance(V.inst, nullptr);
    V = Vk{};
    return 0;
}

int fg_ativo(void) { return g_ativo; }
/* medidor de FPS: quadros que chegaram a tela (reais + gerados) e so os gerados */
unsigned long long fg_apresentados(void) { return g_apresentados.load(std::memory_order_relaxed); }
unsigned long long fg_gerados(void) { return g_gerados_tot.load(std::memory_order_relaxed); }
int fg_geracoes(void) { return g_ativo ? g_geracoes : 0; }

/* janela nova (retorno do segundo plano) ou NULL (perdida). SINCRONO: quando volta, a
 * swapchain da janela anterior ja foi destruida (o Android pode liberar a janela logo) */
void fg_janela(ANativeWindow *jan) {
    if (!g_ativo) return;
    if (jan) ANativeWindow_acquire(jan);
    std::unique_lock<std::mutex> l(E.m);
    E.janela = jan; E.janela_nova = true;
    E.cv.notify_all();
    E.cv.wait(l, [] { return !E.janela_nova || E.sair; });
}

/* proximo AHB livre para o GL desenhar (espera se os 3 estao em uso); *geracao muda
 * quando o anel foi refeito e o GL tem de esquecer os EGLImage antigos */
AHardwareBuffer *fg_alvo(int w, int h, int *idx, int *geracao) {
    std::unique_lock<std::mutex> l(E.m);
    if ((u32)w != E.w || (u32)h != E.h) {
        E.cv.wait(l, [] { return E.fila.empty() && std::all_of(std::begin(E.alvos), std::end(E.alvos), [](const Alvo &a) { return a.livre; }); });
        solta_alvos();
        E.w = (u32)w; E.h = (u32)h;
        for (auto &a : E.alvos) {
            const AHardwareBuffer_Desc d{(u32)w, (u32)h, 1, AHARDWAREBUFFER_FORMAT_R8G8B8A8_UNORM,
                AHARDWAREBUFFER_USAGE_GPU_SAMPLED_IMAGE | AHARDWAREBUFFER_USAGE_GPU_COLOR_OUTPUT, 0, 0, 0};
            if (AHardwareBuffer_allocate(&d, &a.ahb) != 0) { rt_log("LSFG: AHardwareBuffer_allocate %dx%d falhou", w, h); a.ahb = nullptr; }
        }
        E.geracao_anel++;
        rt_log("LSFG: anel de %d AHardwareBuffer %dx%d", ANEL, w, h);
    }
    static int prox = 0;
    E.cv.wait(l, [] { for (int k = 0; k < ANEL; ++k) if (E.alvos[(prox + k) % ANEL].livre) return true; return false; });
    int k = prox;
    while (!E.alvos[k].livre) k = (k + 1) % ANEL;
    prox = (k + 1) % ANEL;
    E.alvos[k].livre = false;
    *idx = k;
    *geracao = E.geracao_anel;
    return E.alvos[k].ahb;
}

/* o GL terminou de mandar o quadro para o AHB idx; fd = fence nativa (-1 = ja pronto) */
void fg_envia(int idx, int fd) {
    { std::lock_guard<std::mutex> l(E.m); E.fila.push_back({idx, fd, 0}); }
    E.cv.notify_all();
}

/* o GL desistiu do AHB (quadro sem blit): devolve ao anel */
void fg_devolve(int idx) {
    { std::lock_guard<std::mutex> l(E.m); E.alvos[idx].livre = true; }
    E.cv.notify_all();
}

} // extern "C"
#endif // !LSFG_PC
#endif // LSFG_SO_PARSER
