/* Teste no PC: carrega as imagens e roda os construtores das duas bibliotecas. */
#include "runtime.h"
#include <stdio.h>
#include <string.h>
#include <windows.h>
extern const char *g_dir_dados;
extern void (*g_depura)(void);
#ifdef RASTRO
extern __thread const char *t_rastro[64];
extern __thread unsigned t_rastro_i;
#endif

static uint32_t u32(uint32_t a) { uint32_t v; memcpy(&v, g_mem + a, 4); return v; }

/* estado do locale da gnustl (o bad_cast do use_facet) */
static void rt_depura(void) {
    static const struct { uint32_t a; const char *n; } ids[] = {
        {0x10b51fc, "ctype<char>"}, {0x10b5200, "ctype<wchar_t>"}, {0x10b51f4, "codecvt<char>"},
        {0x10b51f8, "codecvt<wchar_t>"}, {0x10b680c, "collate<char>"}, {0x10b6828, "numpunct<char>"},
        {0x10b6820, "num_put<char>"}, {0x10b6824, "num_get<char>"}, {0x10b59f0, "id::_S_refcount"}};
    for (unsigned k = 0; k < sizeof ids / sizeof ids[0]; k++)
        fprintf(stderr, "  %-18s _M_index=%u\n", ids[k].n, u32(ids[k].a));
    uint32_t imp = u32(0x10b5a04);
    fprintf(stderr, "  _S_classic=%08x\n", imp);
    if (imp) {
        uint32_t f = u32(imp + 4), n = u32(imp + 8);
        fprintf(stderr, "  facetas=%08x n=%u\n", f, n);
        for (uint32_t k = 0; k < n && k < 40; k++) {
            uint32_t fc = u32(f + 4 * k);
            if (!fc) { fprintf(stderr, "   [%2u] -\n", k); continue; }
            uint32_t vt = u32(fc), ti = u32(vt - 4), nm = u32(ti + 4);
            fprintf(stderr, "   [%2u] %08x vt=%08x ti=%08x %s\n", k, fc, vt, ti, nm ? (char *)g_mem + nm : "?");
        }
    }
    fflush(stderr);
    /* instantaneo da memoria (imagens + heap) para o diferencial no Unicorn */
    FILE *f = fopen("build/instantaneo.bin", "wb");
    if (f) { fwrite(g_mem + 0x00f00000u, 1, HEAP_INI - 0x00f00000u + heap_topo_atual(), f); fclose(f); }
    fprintf(stderr, "  instantaneo gravado (%u MB)\n", (HEAP_INI - 0x00f00000u + heap_topo_atual()) >> 20);
    fflush(stderr);
}

static LONG WINAPI queda(EXCEPTION_POINTERS *e) {
    fprintf(stderr, "QUEDA: codigo %08lx em %p", e->ExceptionRecord->ExceptionCode, e->ExceptionRecord->ExceptionAddress);
    if (e->ExceptionRecord->ExceptionCode == EXCEPTION_ACCESS_VIOLATION) {
        ULONG_PTR a = e->ExceptionRecord->ExceptionInformation[1];
        fprintf(stderr, " (%s endereco %p = jogo %08llx)", e->ExceptionRecord->ExceptionInformation[0] ? "escrevendo" : "lendo",
                (void *)a, (unsigned long long)(a - (ULONG_PTR)g_mem));
    }
    fprintf(stderr, "\n");
#ifdef RASTRO
    fprintf(stderr, "ultimas funcoes (mais recente por ultimo):\n");
    for (unsigned k = 0; k < 64; k++) { const char *f = t_rastro[(t_rastro_i + k) & 63]; if (f) fprintf(stderr, "  %s\n", f); }
#endif
    fflush(stderr);
    return EXCEPTION_EXECUTE_HANDLER;
}

/* teste_pc.exe chama <arquivo> <funcao> [args...]: roda uma funcao do jogo
 * sobre um instantaneo de memoria e imprime r0 */
static int modo_chama(int argc, char **argv) {
    mem_inicia(); heap_inicia();
    FILE *f = fopen(argv[2], "rb");
    if (!f) { printf("sem instantaneo\n"); return 1; }
    size_t n = fread(g_mem + 0x00f00000u, 1, 0x40000000u, f); fclose(f);
    uint32_t fn = (uint32_t)strtoul(argv[3], NULL, 16), a[8] = {0};
    int na = argc - 4;
    for (int k = 0; k < na && k < 8; k++) a[k] = (uint32_t)strtoul(argv[4 + k], NULL, 16);
    CPU *c = cpu_atual();
    uint32_t r = jogo_chama_v(c, fn, na, a);
    printf("r0=%08x (instantaneo %zu bytes)\n", r, n);
    return 0;
}

int main(int argc, char **argv) {
    SetUnhandledExceptionFilter(queda);
    if (argc > 3 && !strcmp(argv[1], "chama")) return modo_chama(argc, argv);
    g_depura = rt_depura;
    g_dir_dados = argc > 1 ? argv[1] : "saida";
    /* o Java da Forge define isto antes de carregar o jogo */
    _putenv("FORGELIB_CONFIG_PATH=pc_dados/config");
    _putenv("FORGELIB_LOG_PATH=pc_dados/saveData");
    rt_inicia();
    printf("OK: construtores rodaram\n");
    /* MGS2_INSTANTANEO=arquivo: memoria do jogo (imagens + heap) depois dos construtores,
     * para comparar duas compilacoes do mesmo C (ex.: -DMGS2_CARREGA_TUDO x padrao) */
    const char *inst = getenv("MGS2_INSTANTANEO");
    if (inst) {
        uint32_t n = HEAP_INI - 0x00f00000u + heap_topo_atual();
        FILE *f = fopen(inst, "wb");
        if (f) { fwrite(g_mem + 0x00f00000u, 1, n, f); fclose(f); printf("instantaneo: %u bytes\n", n); }
    }
    return 0;
}
