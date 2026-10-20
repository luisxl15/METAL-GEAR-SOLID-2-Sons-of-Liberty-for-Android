// Roda a cadeia LSFG do runtime (runtime/lsfg_vk.cpp, o MESMO codigo do .so) no Vulkan do PC,
// com as camadas de validacao (inclusive a de sincronizacao), sobre o Lossless_teste.dll.
//
// Quadros alternam dois desenhos conhecidos (A e B). Com os shaders de teste o "generate"
// devolve a media dos dois quadros: confere CADA pixel do quadro gerado. Controle no fim:
// um despacho sem pipeline tem de ser acusado pela validacao (prova que ela escuta).
//
//   teste_cadeia.exe <Lossless_teste.dll> [quadros]
#include <cstdarg>
#include <cstdio>
#include <cstdlib>
static const char *g_caminho = nullptr;
#define LSFG_PC
#define DLL_LOSSLESS g_caminho
#include "../runtime/lsfg_vk.cpp"

extern "C" void rt_log(const char *f, ...) { va_list a; va_start(a, f); vprintf(f, a); va_end(a); printf("\n"); }
extern "C" int aj_int(const char *, int d) { return d; }

static int g_erros = 0, g_avisos = 0;
static VKAPI_ATTR VkBool32 VKAPI_CALL mensagem(VkDebugUtilsMessageSeverityFlagBitsEXT sev, VkDebugUtilsMessageTypeFlagsEXT,
                                               const VkDebugUtilsMessengerCallbackDataEXT *d, void *) {
    if (sev & VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT) { if (g_erros++ < 12) printf("VALIDACAO ERRO: %s\n\n", d->pMessage); }
    else if (sev & VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) { if (g_avisos++ < 6) printf("validacao aviso: %s\n\n", d->pMessage); }
    return VK_FALSE;
}

static bool dispositivo_pc() {
    const VkApplicationInfo app{VK_STRUCTURE_TYPE_APPLICATION_INFO, nullptr, "teste LSFG", 1, "mgs2", 1, VK_API_VERSION_1_2};
    const char *camadas[] = {"VK_LAYER_KHRONOS_validation"};
    const char *exts[] = {"VK_EXT_debug_utils"};
    const VkValidationFeatureEnableEXT liga[] = {VK_VALIDATION_FEATURE_ENABLE_SYNCHRONIZATION_VALIDATION_EXT,
                                                 VK_VALIDATION_FEATURE_ENABLE_BEST_PRACTICES_EXT};
    VkDebugUtilsMessengerCreateInfoEXT mi{VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT, nullptr, 0,
        VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT,
        VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT, mensagem, nullptr};
    const VkValidationFeaturesEXT vf{VK_STRUCTURE_TYPE_VALIDATION_FEATURES_EXT, &mi, 1, liga, 0, nullptr};
    const VkInstanceCreateInfo ici{VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO, &vf, 0, &app, 1, camadas, 1, exts};
    VKCHK(vkCreateInstance(&ici, nullptr, &V.inst));
    auto cria_msg = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(V.inst, "vkCreateDebugUtilsMessengerEXT");
    VkDebugUtilsMessengerEXT m; cria_msg(V.inst, &mi, nullptr, &m);
    u32 n = 1; vkEnumeratePhysicalDevices(V.inst, &n, &V.pd);
    VkPhysicalDeviceProperties pr; vkGetPhysicalDeviceProperties(V.pd, &pr);
    printf("GPU do PC: %s\n", pr.deviceName);
    vkGetPhysicalDeviceMemoryProperties(V.pd, &V.mp);
    // as mesmas features que cria_dispositivo() liga no Android
    VkPhysicalDeviceRobustness2FeaturesEXT r2{VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ROBUSTNESS_2_FEATURES_EXT};
    VkPhysicalDeviceVulkan12Features f12{VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES, &r2};
    VkPhysicalDeviceVulkan11Features f11{VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_1_FEATURES, &f12};
    VkPhysicalDeviceFeatures2 f2{VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2, &f11};
    vkGetPhysicalDeviceFeatures2(V.pd, &f2);
    if (!r2.nullDescriptor || !f12.vulkanMemoryModel || !f12.shaderFloat16) { printf("GPU do PC sem as features\n"); return false; }
    VkPhysicalDeviceRobustness2FeaturesEXT r2e{VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ROBUSTNESS_2_FEATURES_EXT}; r2e.nullDescriptor = VK_TRUE;
    VkPhysicalDeviceVulkan12Features f12e{VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES, &r2e};
    f12e.vulkanMemoryModel = VK_TRUE; f12e.vulkanMemoryModelDeviceScope = f12.vulkanMemoryModelDeviceScope; f12e.shaderFloat16 = VK_TRUE;
    f12e.shaderInt8 = f12.shaderInt8; f12e.storageBuffer8BitAccess = f12.storageBuffer8BitAccess;
    VkPhysicalDeviceVulkan11Features f11e{VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_1_FEATURES, &f12e};
    f11e.storageBuffer16BitAccess = f11.storageBuffer16BitAccess; f11e.uniformAndStorageBuffer16BitAccess = f11.uniformAndStorageBuffer16BitAccess;
    VkPhysicalDeviceFeatures2 f2e{VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2, &f11e};
    f2e.features.shaderInt16 = f2.features.shaderInt16;
    f2e.features.shaderStorageImageExtendedFormats = f2.features.shaderStorageImageExtendedFormats;
    f2e.features.shaderStorageImageReadWithoutFormat = f2.features.shaderStorageImageReadWithoutFormat;
    f2e.features.shaderStorageImageWriteWithoutFormat = f2.features.shaderStorageImageWriteWithoutFormat;
    u32 nq = 0; vkGetPhysicalDeviceQueueFamilyProperties(V.pd, &nq, nullptr);
    std::vector<VkQueueFamilyProperties> qs(nq); vkGetPhysicalDeviceQueueFamilyProperties(V.pd, &nq, qs.data());
    for (u32 i = 0; i < nq; ++i) if ((qs[i].queueFlags & 3) == 3) { V.qf = i; break; }
    const float prio = 1.0f;
    const VkDeviceQueueCreateInfo qi{VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO, nullptr, 0, V.qf, 1, &prio};
    const char *dext[] = {"VK_EXT_robustness2"};
    const VkDeviceCreateInfo di{VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO, &f2e, 0, 1, &qi, 0, nullptr, 1, dext, nullptr};
    VKCHK(vkCreateDevice(V.pd, &di, nullptr, &V.dev));
    vkGetDeviceQueue(V.dev, V.qf, 0, &V.fila);
    return true;
}

static u8 padrao(int q, u32 x, u32 y, int c) {   // dois desenhos conhecidos, alternando por quadro
    if (q % 2 == 0) { const u8 v[4] = {(u8)(x & 255), (u8)(y & 255), 64, 255}; return v[c]; }
    const u8 v[4] = {(u8)((x * 3) & 255), 0, (u8)((y * 2) & 255), 255}; return v[c];
}

int main(int argc, char **argv) {
    setvbuf(stdout, nullptr, _IONBF, 0);
    g_caminho = argc > 1 ? argv[1] : "Lossless_teste.dll";
    const int quadros = argc > 2 ? atoi(argv[2]) : 8;
    std::map<u32, std::vector<u32>> spv;
    if (const char *e = carrega_shaders(spv)) { printf("DLL recusado: %s\n", e); return 1; }
    if (!dispositivo_pc() || !cria_modulos(spv) || !cria_comandos()) return 1;
    const VkExtent2D ext{1280, 720};
    g_fluxo = 1.0f; g_geracoes = 1;
    if (!refaz_cadeia(ext)) { printf("cadeia nao montou\n"); return 1; }

    // buffer de ida e volta (visivel ao host)
    const VkDeviceSize tam = (VkDeviceSize)ext.width * ext.height * 4;
    const VkBufferCreateInfo bi{VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO, nullptr, 0, tam,
        VK_BUFFER_USAGE_TRANSFER_SRC_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT, VK_SHARING_MODE_EXCLUSIVE, 0, nullptr};
    VkBuffer buf; vkCreateBuffer(V.dev, &bi, nullptr, &buf);
    VkMemoryRequirements req; vkGetBufferMemoryRequirements(V.dev, buf, &req);
    const VkMemoryAllocateInfo ai{VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO, nullptr, req.size,
        tipo_mem(req.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT)};
    VkDeviceMemory mem; vkAllocateMemory(V.dev, &ai, nullptr, &mem); vkBindBufferMemory(V.dev, buf, mem, 0);
    u8 *px = nullptr; vkMapMemory(V.dev, mem, 0, tam, 0, (void **)&px);
    const VkBufferImageCopy reg{0, 0, 0, {VK_IMAGE_ASPECT_COLOR_BIT, 0, 0, 1}, {0, 0, 0}, {ext.width, ext.height, 1}};

    for (int q = 0; q < quadros; ++q) {
        for (u32 y = 0; y < ext.height; ++y) for (u32 x = 0; x < ext.width; ++x) for (int c = 0; c < 4; ++c)
            px[((size_t)y * ext.width + x) * 4 + c] = padrao(q, x, y, c);
        const u64 fc = g_contador++;
        LsfgImage &ent = g_chain->Input(fc);
        Cmd &cm = proximo_cmd();
        // como processa(): entrada da cadeia escrita por transferencia, lida por compute/transferencia
        barreira(cm.cb, ent.Handle(), VK_ACCESS_SHADER_READ_BIT | VK_ACCESS_TRANSFER_READ_BIT, VK_ACCESS_TRANSFER_WRITE_BIT, ent.Layout(),
                 VK_IMAGE_LAYOUT_GENERAL, VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT | VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT);
        vkCmdCopyBufferToImage(cm.cb, buf, ent.Handle(), VK_IMAGE_LAYOUT_GENERAL, 1, &reg);
        barreira(cm.cb, ent.Handle(), VK_ACCESS_TRANSFER_WRITE_BIT, VK_ACCESS_SHADER_READ_BIT | VK_ACCESS_TRANSFER_READ_BIT, VK_IMAGE_LAYOUT_GENERAL,
                 VK_IMAGE_LAYOUT_GENERAL, VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT | VK_PIPELINE_STAGE_TRANSFER_BIT);
        ent.SetLayout(VK_IMAGE_LAYOUT_GENERAL);
        const bool morno = fc + 1 >= 2;
        if (morno) g_chain->DispatchShared(cm.cb, fc);
        if (morno) {
            LsfgImage &sai = g_saidas[0];
            g_chain->SetTarget(1, 0, 0, sai.View());
            g_chain->DispatchGeneration(cm.cb, fc, 1, 0, 0, sai.Handle(), sai.Extent());
            sai.SetLayout(VK_IMAGE_LAYOUT_GENERAL);
            if (q == quadros - 1) vkCmdCopyImageToBuffer(cm.cb, sai.Handle(), VK_IMAGE_LAYOUT_GENERAL, buf, 1, &reg);
        }
        vkEndCommandBuffer(cm.cb);
        const VkSubmitInfo si{VK_STRUCTURE_TYPE_SUBMIT_INFO, nullptr, 0, nullptr, nullptr, 1, &cm.cb, 0, nullptr};
        vkQueueSubmit(V.fila, 1, &si, cm.f);
        vkWaitForFences(V.dev, 1, &cm.f, VK_TRUE, UINT64_MAX);
    }
    // o gerado deve ser a media de A e B (os shaders de teste), pixel a pixel
    size_t medidos = 0, errados = 0;
    for (u32 y = 0; y < ext.height; ++y) for (u32 x = 0; x < ext.width; ++x) for (int c = 0; c < 4; ++c) {
        const int esperado = (padrao(0, x, y, c) + padrao(1, x, y, c) + 1) / 2;
        const int obtido = px[((size_t)y * ext.width + x) * 4 + c];
        ++medidos;
        if (std::abs(obtido - esperado) > 1 && errados++ < 5) printf("  pixel %u,%u canal %d: %d (esperado %d)\n", x, y, c, obtido, esperado);
    }
    printf("quadro gerado: %zu canais medidos, %zu fora de +-1\n", medidos, errados);
    const int erros_cadeia = g_erros;
    printf("validacao durante %d quadros: %d erros, %d avisos\n", quadros, erros_cadeia, g_avisos);

    // desmonta a cadeia (lixeira) e remonta com 3 geracoes e fluxo 50%: destruicao e
    // outra configuracao tambem passam pela validacao
    vkDeviceWaitIdle(V.dev);
    g_geracoes = 3; g_fluxo = 0.5f;
    const bool remontou = refaz_cadeia(ext);
    vkDeviceWaitIdle(V.dev);
    g_chain.reset(); g_lix_saidas.esvazia();
    vkDeviceWaitIdle(V.dev);
    const int erros_total = g_erros;
    printf("remontagem (3 geracoes, fluxo 50%%) %s; desmontagem: %d erros de validacao\n", remontou ? "ok" : "FALHOU", erros_total - erros_cadeia);

    // controle: alocacao de tamanho zero (uso invalido) TEM de ser acusada
    const VkMemoryAllocateInfo zero{VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO, nullptr, 0, 0};
    VkDeviceMemory mz = VK_NULL_HANDLE; vkAllocateMemory(V.dev, &zero, nullptr, &mz);
    const bool acusou = g_erros > erros_total;
    printf("controle (vkAllocateMemory de 0 bytes): validacao %s\n", acusou ? "ACUSOU (ok, ela escuta)" : "NAO acusou: o teste nao mede nada");
    fflush(stdout);
    std::_Exit((errados || erros_total || !acusou || !remontou) ? 1 : 0);   // sem teardown: o buffer do controle e invalido
}
