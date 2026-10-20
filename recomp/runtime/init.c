/* Carregador: poe as imagens no espaco do jogo, prepara os dados importados
 * e roda os construtores das duas bibliotecas. */
#include "runtime.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef __ANDROID__
#include <android/log.h>
#endif

extern const Importacao g_exportados_jogo[];
extern const uint32_t g_n_exportados_jogo;
extern const uint32_t g_exidx_gnu[2], g_exidx_jogo[2];
uint32_t g_exidx[2][2];
void libc_inicia(uint32_t sF, uint32_t stdout_var, uint32_t stderr_var);
void sles_inicia_iids(uint32_t engine, uint32_t bq, uint32_t play, uint32_t vol);

const char *g_dir_dados = ".";   /* onde estao os .img (o app define) */

/* ---- log ----------------------------------------------------------------- */
void rt_log_prio(int prio, const char *tag, const char *msg) {
#ifdef __ANDROID__
    __android_log_write(prio, tag, msg);
#else
    (void)prio;
    fprintf(stderr, "[%s] %s\n", tag, msg);
    fflush(stderr);
#endif
}
void rt_log(const char *fmt, ...) {
    char b[1024]; va_list ap; va_start(ap, fmt); vsnprintf(b, sizeof b, fmt, ap); va_end(ap);
    rt_log_prio(4, "MGS2-RT", b);
}
#ifdef RASTRO
__thread const char *t_rastro[64];
__thread unsigned t_rastro_i;
#endif
void (*g_depura)(void);
#include <setjmp.h>
jmp_buf *g_fatal_jmp;          /* teste: volta ao chamador em vez de abortar */
void rt_fatal(const char *fmt, ...) {
    char b[1024]; va_list ap; va_start(ap, fmt); vsnprintf(b, sizeof b, fmt, ap); va_end(ap);
    if (g_fatal_jmp) { if (getenv("RT_FALA")) rt_log_prio(7, "MGS2-RT", b); longjmp(*g_fatal_jmp, 1); }
    rt_log_prio(7, "MGS2-RT", b);
    if (g_depura) g_depura();
#ifdef RASTRO
    for (unsigned k = 0; k < 64; k++) { const char *f = t_rastro[(t_rastro_i + k) & 63]; if (f) rt_log_prio(7, "MGS2-RT", f); }
#endif
    abort();
}

#ifdef _WIN32   /* no Android: caminho.c (sem diferenciar maiusculas) */
const char *rt_caminho(const char *p, char *buf, size_t n) { (void)buf; (void)n; return p; }
#endif

/* ---- tabela _ctype_ do bionic (BSD): 1 + 256 entradas ------------------- */
static void ctype_bionic(uint8_t *t) {
    enum { U = 1, L = 2, N = 4, S = 8, P = 0x10, C = 0x20, X = 0x40, B = 0x80 };
    t[0] = 0;                                  /* EOF */
    for (int ch = 0; ch < 256; ch++) {
        uint8_t v = 0;
        if (ch < 0x20 || ch == 0x7f) v |= C;
        if (ch == ' ') v |= S | B;
        if (ch >= 9 && ch <= 13) v |= S;
        if (ch >= '0' && ch <= '9') v |= N;
        if (ch >= 'A' && ch <= 'Z') v |= U;
        if (ch >= 'a' && ch <= 'z') v |= L;
        if ((ch >= 'A' && ch <= 'F') || (ch >= 'a' && ch <= 'f')) v |= X;
        if (ch > 0x20 && ch < 0x7f && !(v & (U | L | N))) v |= P;
        t[1 + ch] = v;
    }
}

static uint32_t dado(const char *nome) {
    for (uint32_t k = 0; k < g_n_dados_importados; k++)
        if (!strcmp(g_dados_importados[k].nome, nome)) return g_dados_importados[k].ad;
    return 0;
}

uint32_t rt_exportado(const char *nome) {
    for (uint32_t k = 0; k < g_n_exportados_jogo; k++)
        if (!strcmp(g_exportados_jogo[k].nome, nome)) return g_exportados_jogo[k].ad;
    return 0;
}

static void carrega_imagem(const ImagemLib *l) {
    char cam[1024];
    char nome[128];
    snprintf(nome, sizeof nome, "%s", l->nome);
    char *p = strstr(nome, ".so"); if (p) strcpy(p, ".img");
    snprintf(cam, sizeof cam, "%s/%s", g_dir_dados, nome);
    FILE *f = fopen(cam, "rb");
    if (!f) {
        /* no APK: jniLibs/arm64-v8a/libmgs2img_{gnustl,jogo}.so */
        snprintf(cam, sizeof cam, "%s/libmgs2img_%s.so", g_dir_dados, strstr(l->nome, "gnustl") ? "gnustl" : "jogo");
        f = fopen(cam, "rb");
    }
    if (!f) rt_fatal("nao abri %s", cam);
    size_t n = fread(g_mem + l->base, 1, l->tam, f);
    fclose(f);
    if (n != l->tam) rt_fatal("%s: li %zu de %u bytes", cam, n, l->tam);
    rt_log("%s em %08x (%u bytes)", l->nome, l->base, l->tam);
}

void rt_inicia(void) {
    mem_inicia();
    heap_inicia();
    for (int k = 0; k < 2; k++) carrega_imagem(&g_libs[k]);
    memcpy(g_exidx[0], g_exidx_gnu, 8);
    memcpy(g_exidx[1], g_exidx_jogo, 8);

    /* dados importados */
    uint32_t sF = dado("__sF");
    libc_inicia(sF, dado("stdout"), dado("stderr"));
    uint32_t ct = dado("_ctype_");
    if (ct) {
        uint32_t tab = heap_malloc(260);
        ctype_bionic(g_mem + tab);
        memcpy(g_mem + ct, &tab, 4);
    }
    sles_inicia_iids(dado("SL_IID_ENGINE"), dado("SL_IID_BUFFERQUEUE"), dado("SL_IID_PLAY"), dado("SL_IID_VOLUME"));

    /* construtores: gnustl primeiro (o jogo depende dela) */
    for (int k = 0; k < 2; k++) {
        const ImagemLib *l = &g_libs[k];
        rt_log("construtores de %s: %u", l->nome, l->n_init);
        for (uint32_t i = 0; i < l->n_init; i++) {
            uint32_t fn; memcpy(&fn, g_mem + l->init_array + 4 * i, 4);
            if (fn == 0 || fn == 0xffffffffu) continue;
            rt_log("  construtor %u: %08x", i, fn);
            jogo_chama(fn, 0);
        }
    }
    rt_log("runtime pronto; heap usado: %u KB", heap_topo_atual() / 1024);
}
