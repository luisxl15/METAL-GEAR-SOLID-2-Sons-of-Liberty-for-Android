// Teste no PC do leitor de Lossless.dll do runtime (o MESMO codigo de runtime/lsfg_vk.cpp,
// so a parte do PE/SPIR-V). Grava cada modulo adotado em <saida>/<id>.spv.
//   teste_parser.exe <Lossless.dll> <pasta de saida>
#include <cstdarg>
#include <cstdio>
static const char *g_caminho = nullptr;
#define LSFG_SO_PARSER
#define DLL_LOSSLESS g_caminho
#include "../runtime/lsfg_vk.cpp"

extern "C" void rt_log(const char *f, ...) { va_list a; va_start(a, f); vprintf(f, a); va_end(a); printf("\n"); }
extern "C" int aj_int(const char *, int d) { return d; }

int main(int argc, char **argv) {
    if (argc < 3) { printf("uso: teste_parser <dll> <saida>\n"); return 2; }
    g_caminho = argv[1];
    std::map<u32, std::vector<u32>> m;
    const char *erro = carrega_shaders(m);
    if (erro) { printf("RECUSADO: %s\n", erro); return 1; }
    for (const auto &[id, w] : m) {
        char n[512]; std::snprintf(n, sizeof n, "%s/%u.spv", argv[2], id);
        FILE *f = std::fopen(n, "wb"); std::fwrite(w.data(), 4, w.size(), f); std::fclose(f);
    }
    printf("ACEITO: %zu modulos\n", m.size());
    return 0;
}
