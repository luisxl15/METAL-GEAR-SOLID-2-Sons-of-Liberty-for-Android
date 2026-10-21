/* Pontes da libc que precisam de traducao de estrutura (32 -> 64 bits),
 * de argumentos variaveis ou de memoria nova do jogo. */
#include "runtime.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <math.h>
#include <wchar.h>
#include <locale.h>
#include <sys/stat.h>
#ifdef _WIN32
#include <direct.h>
#include <io.h>
#else
#include <unistd.h>
#include <dirent.h>
#include <sys/time.h>
#include <sys/uio.h>
#include <sys/sysinfo.h>
#include <sys/syscall.h>
#include <android/log.h>
#endif

/* ======================================================================== */
/* errno por thread: um int na memoria do jogo; sincronizado quando o jogo   */
/* pede o endereco (ele sempre le logo depois da chamada que falhou)          */
static __thread uint32_t t_errno;
void I___errno(CPU *c) { RT_PRIMEIRA("__errno");
    if (!t_errno) t_errno = heap_malloc(4);
    int e = errno;
    memcpy(g_mem + t_errno, &e, 4);
    ret32(c, t_errno);
}

/* ======================================================================== */
/* __aeabi (o jogo foi compilado sem divisao em hardware)                     */
void I___aeabi_d2uiz(CPU *c) { RT_PRIMEIRA("__aeabi_d2uiz"); Args a = args_de(c); double d = argd(&a); ret32(c, cvt_u32_f(d)); }
void I___aeabi_d2ulz(CPU *c) { RT_PRIMEIRA("__aeabi_d2ulz");
    Args a = args_de(c); double d = argd(&a);
    uint64_t r = (d != d || d <= -1.0) ? 0 : (d >= 18446744073709551616.0 ? ~0ull : (uint64_t)d);
    ret64(c, r);
}
void I___aeabi_dmul(CPU *c) { RT_PRIMEIRA("__aeabi_dmul"); Args a = args_de(c); double x = argd(&a), y = argd(&a); retd(c, x * y); }
void I___aeabi_dsub(CPU *c) { RT_PRIMEIRA("__aeabi_dsub"); Args a = args_de(c); double x = argd(&a), y = argd(&a); retd(c, x - y); }
void I___aeabi_f2d(CPU *c) { RT_PRIMEIRA("__aeabi_f2d"); Args a = args_de(c); float f = argf(&a); retd(c, (double)f); }
void I___aeabi_l2d(CPU *c) { RT_PRIMEIRA("__aeabi_l2d"); Args a = args_de(c); int64_t v = (int64_t)arg64(&a); retd(c, (double)v); }
void I___aeabi_ui2d(CPU *c) { RT_PRIMEIRA("__aeabi_ui2d"); Args a = args_de(c); retd(c, (double)arg32(&a)); }
void I___aeabi_ul2d(CPU *c) { RT_PRIMEIRA("__aeabi_ul2d"); Args a = args_de(c); retd(c, (double)arg64(&a)); }
void I___aeabi_ldivmod(CPU *c) { RT_PRIMEIRA("__aeabi_ldivmod");
    Args a = args_de(c);
    int64_t n = (int64_t)arg64(&a), d = (int64_t)arg64(&a);
    int64_t q = 0, r = 0;
    if (d == 0) { q = n < 0 ? INT64_MIN : (n > 0 ? INT64_MAX : 0); r = 0; }
    else if (n == INT64_MIN && d == -1) { q = n; r = 0; }
    else { q = n / d; r = n % d; }
    c->r[0] = (uint32_t)q; c->r[1] = (uint32_t)((uint64_t)q >> 32);
    c->r[2] = (uint32_t)r; c->r[3] = (uint32_t)((uint64_t)r >> 32);
}

/* ======================================================================== */
/* heap                                                                       */
void I_malloc(CPU *c) { RT_PRIMEIRA("malloc"); ret32(c, heap_malloc(c->r[0])); }
void I_free(CPU *c) { RT_PRIMEIRA("free"); heap_free(c->r[0]); }
void I_calloc(CPU *c) { RT_PRIMEIRA("calloc"); ret32(c, heap_calloc(c->r[0], c->r[1])); }
void I_realloc(CPU *c) { RT_PRIMEIRA("realloc"); ret32(c, heap_realloc(c->r[0], c->r[1])); }
void I_memalign(CPU *c) { RT_PRIMEIRA("memalign"); ret32(c, heap_memalign(c->r[0], c->r[1])); }
void I_strdup(CPU *c) { RT_PRIMEIRA("strdup"); ret32(c, guest_strdup(G2H(c->r[0]))); }

/* ======================================================================== */
/* strto* e companhia: o ponteiro de fim volta como endereco do jogo          */
static void fim_para_jogo(uint32_t pend, const char *base_h, uint32_t base_g, const char *fim) {
    if (!pend) return;
    uint32_t v = base_g + (uint32_t)(fim - base_h);
    memcpy(g_mem + pend, &v, 4);
}
void I_strtol(CPU *c) { RT_PRIMEIRA("strtol");
    const char *s = G2H(c->r[0]); char *fim;
    long v = strtol(s, &fim, (int)c->r[2]);
    if (v > INT32_MAX) { v = INT32_MAX; errno = ERANGE; }
    if (v < INT32_MIN) { v = INT32_MIN; errno = ERANGE; }
    fim_para_jogo(c->r[1], s, c->r[0], fim);
    ret32(c, (uint32_t)(int32_t)v);
}
void I_strtoul(CPU *c) { RT_PRIMEIRA("strtoul");
    const char *s = G2H(c->r[0]); char *fim;
    unsigned long long v = strtoull(s, &fim, (int)c->r[2]);
    /* strtoul de 32 bits: "-1" vira 0xffffffff, estouro satura */
    int neg = 0; const char *p = s; while (*p == ' ' || *p == '\t') p++; if (*p == '-') neg = 1;
    uint32_t r;
    if (!neg && v > 0xffffffffull) { r = 0xffffffffu; errno = ERANGE; }
    else r = (uint32_t)v;
    fim_para_jogo(c->r[1], s, c->r[0], fim);
    ret32(c, r);
}
void I_strtoull(CPU *c) { RT_PRIMEIRA("strtoull");
    const char *s = G2H(c->r[0]); char *fim;
    unsigned long long v = strtoull(s, &fim, (int)c->r[2]);
    fim_para_jogo(c->r[1], s, c->r[0], fim);
    ret64(c, v);
}
void I_strtod(CPU *c) { RT_PRIMEIRA("strtod");
    const char *s = G2H(c->r[0]); char *fim;
    double v = strtod(s, &fim);
    fim_para_jogo(c->r[1], s, c->r[0], fim);
    retd(c, v);
}
void I_wcstol(CPU *c) { RT_PRIMEIRA("wcstol");
    const wchar_t *s = G2H(c->r[0]); wchar_t *fim;
    long v = wcstol(s, &fim, (int)c->r[2]);
    if (c->r[1]) { uint32_t g = c->r[0] + (uint32_t)((const char *)fim - (const char *)s); memcpy(g_mem + c->r[1], &g, 4); }
    ret32(c, (uint32_t)(int32_t)v);
}
void I_strtok_r(CPU *c) { RT_PRIMEIRA("strtok_r");
    /* reimplementado para o ponteiro salvo ficar em endereco do jogo */
    uint32_t s = c->r[0], dl = c->r[1], salvo = c->r[2];
    const char *delim = G2H(dl);
    if (!s) memcpy(&s, g_mem + salvo, 4);
    if (!s) { ret32(c, 0); return; }
    char *p = G2H(s);
    p += strspn(p, delim);
    if (!*p) { uint32_t z = 0; memcpy(g_mem + salvo, &z, 4); ret32(c, 0); return; }
    char *fim = p + strcspn(p, delim);
    uint32_t prox;
    if (*fim) { *fim = 0; prox = H2G(fim + 1); } else prox = H2G(fim);
    memcpy(g_mem + salvo, &prox, 4);
    ret32(c, H2G(p));
}
void I_frexp(CPU *c) { RT_PRIMEIRA("frexp"); Args a = args_de(c); double d = argd(&a); uint32_t pe = arg32(&a); int e; double r = frexp(d, &e); memcpy(g_mem + pe, &e, 4); retd(c, r); }
void I_modf(CPU *c) { RT_PRIMEIRA("modf"); Args a = args_de(c); double d = argd(&a); uint32_t pi = arg32(&a); double ip; double r = modf(d, &ip); memcpy(g_mem + pi, &ip, 8); retd(c, r); }

static __thread uint32_t t_strerror;
void I_strerror(CPU *c) { RT_PRIMEIRA("strerror");
    if (!t_strerror) t_strerror = heap_malloc(128);
    snprintf(G2H(t_strerror), 128, "%s", strerror((int)c->r[0]));
    ret32(c, t_strerror);
}

/* getenv: copia no jogo e guarda (a mesma variavel devolve o mesmo endereco) */
void I_getenv(CPU *c) { RT_PRIMEIRA("getenv");
    const char *v = getenv(G2H(c->r[0]));
    ret32(c, v ? guest_strdup(v) : 0);
}
void I_setlocale(CPU *c) { RT_PRIMEIRA("setlocale");
    static uint32_t cloc;
    if (!cloc) cloc = guest_strdup("C");
    ret32(c, cloc);
}
void I_getcwd(CPU *c) { RT_PRIMEIRA("getcwd");
    char buf[1024];
#ifdef _WIN32
    if (!_getcwd(buf, sizeof buf)) { ret32(c, 0); return; }
#else
    if (!getcwd(buf, sizeof buf)) { ret32(c, 0); return; }
#endif
    uint32_t g = c->r[0];
    if (!g) g = heap_malloc(c->r[1] ? c->r[1] : (uint32_t)strlen(buf) + 1);
    snprintf(G2H(g), c->r[1] ? c->r[1] : strlen(buf) + 1, "%s", buf);
    ret32(c, g);
}

/* ======================================================================== */
/* formatacao: printf com argumentos lidos do jogo                            */
typedef struct { int modo; Args a; uint32_t va; } Fonte;
static uint32_t f32(Fonte *f) {
    if (!f->modo) return arg32(&f->a);
    uint32_t v; memcpy(&v, g_mem + f->va, 4); f->va += 4; return v;
}
static uint64_t f64(Fonte *f) {
    if (!f->modo) return arg64(&f->a);
    f->va = (f->va + 7) & ~7u;
    uint64_t v; memcpy(&v, g_mem + f->va, 8); f->va += 8; return v;
}

typedef struct { char *p; size_t cap, n; } Saida;
static void poe(Saida *s, const char *t, size_t k) {
    if (s->n < s->cap) {
        size_t cabe = s->cap - s->n;
        memcpy(s->p + s->n, t, k < cabe ? k : cabe);
    }
    s->n += k;
}

static size_t formata(char *out, size_t cap, const char *fmt, Fonte *f) {
    Saida s = { out, cap, 0 };
    char spec[64], tmp[512];
    while (*fmt) {
        if (*fmt != '%') {
            const char *q = strchr(fmt, '%');
            size_t k = q ? (size_t)(q - fmt) : strlen(fmt);
            poe(&s, fmt, k); fmt += k; continue;
        }
        const char *ini = fmt++;
        if (*fmt == '%') { poe(&s, "%", 1); fmt++; continue; }
        size_t sp = 0; spec[sp++] = '%';
        while (strchr("-+ #0'", *fmt) && *fmt) { if (*fmt != '\'') spec[sp++] = *fmt; fmt++; }
        if (*fmt == '*') { sp += snprintf(spec + sp, sizeof spec - sp, "%d", (int32_t)f32(f)); fmt++; }
        else while (*fmt >= '0' && *fmt <= '9') spec[sp++] = *fmt++;
        if (*fmt == '.') {
            spec[sp++] = *fmt++;
            if (*fmt == '*') { sp += snprintf(spec + sp, sizeof spec - sp, "%d", (int32_t)f32(f)); fmt++; }
            else while (*fmt >= '0' && *fmt <= '9') spec[sp++] = *fmt++;
        }
        int lg = 0;  /* 0 int, 1 hh, 2 h, 3 l(32), 4 ll, 5 L */
        for (;;) {
            if (*fmt == 'h') { lg = lg == 2 ? 1 : 2; fmt++; }
            else if (*fmt == 'l') { lg = lg == 3 ? 4 : 3; fmt++; }
            else if (*fmt == 'q' || *fmt == 'j') { lg = 4; fmt++; }
            else if (*fmt == 'z' || *fmt == 't') { lg = 3; fmt++; }
            else if (*fmt == 'L') { lg = 5; fmt++; }
            else break;
        }
        char cv = *fmt++;
        if (!cv) break;
        int k = 0;
        switch (cv) {
        case 'd': case 'i':
            if (lg == 4) { memcpy(spec + sp, "lld", 4); k = snprintf(tmp, sizeof tmp, spec, (long long)f64(f)); }
            else {
                int32_t v = (int32_t)f32(f);
                if (lg == 1) v = (int8_t)v; else if (lg == 2) v = (int16_t)v;
                spec[sp++] = cv; spec[sp] = 0; k = snprintf(tmp, sizeof tmp, spec, v);
            }
            break;
        case 'u': case 'o': case 'x': case 'X':
            if (lg == 4) { spec[sp++] = 'l'; spec[sp++] = 'l'; spec[sp++] = cv; spec[sp] = 0; k = snprintf(tmp, sizeof tmp, spec, (unsigned long long)f64(f)); }
            else {
                uint32_t v = f32(f);
                if (lg == 1) v = (uint8_t)v; else if (lg == 2) v = (uint16_t)v;
                spec[sp++] = cv; spec[sp] = 0; k = snprintf(tmp, sizeof tmp, spec, v);
            }
            break;
        case 'c':
            spec[sp++] = 'c'; spec[sp] = 0; k = snprintf(tmp, sizeof tmp, spec, (int)f32(f));
            break;
        case 'p':
            k = snprintf(tmp, sizeof tmp, "0x%x", f32(f));
            break;
        case 's': {
            uint32_t g = f32(f);
            if (lg == 3) {
                spec[sp++] = 'l'; spec[sp++] = 's'; spec[sp] = 0;
                char *big = malloc(65536);
                int kk = snprintf(big, 65536, spec, g ? (const wchar_t *)G2H(g) : L"(null)");
                poe(&s, big, kk > 0 ? (size_t)(kk < 65535 ? kk : 65535) : 0);
                free(big);
                continue;
            }
            const char *str = g ? (const char *)G2H(g) : "(null)";
            spec[sp++] = 's'; spec[sp] = 0;
            if (strcmp(spec, "%s") == 0) { poe(&s, str, strlen(str)); continue; }
            int kk = snprintf(NULL, 0, spec, str);
            char *big = malloc((size_t)kk + 1);
            snprintf(big, (size_t)kk + 1, spec, str);
            poe(&s, big, (size_t)kk);
            free(big);
            continue;
        }
        case 'f': case 'F': case 'e': case 'E': case 'g': case 'G': case 'a': case 'A': {
            uint64_t u = f64(f); double d; memcpy(&d, &u, 8);
            spec[sp++] = cv; spec[sp] = 0;
            k = snprintf(tmp, sizeof tmp, spec, d);
            break;
        }
        case 'n': {
            uint32_t g = f32(f);
            int32_t n = (int32_t)s.n;
            if (lg == 1) g_mem[g] = (uint8_t)n;
            else if (lg == 2) { int16_t h = (int16_t)n; memcpy(g_mem + g, &h, 2); }
            else if (lg == 4) { int64_t l = n; memcpy(g_mem + g, &l, 8); }
            else memcpy(g_mem + g, &n, 4);
            continue;
        }
        default:
            poe(&s, ini, (size_t)(fmt - ini));
            continue;
        }
        if (k > 0) poe(&s, tmp, (size_t)(k < (int)sizeof tmp ? k : (int)sizeof tmp - 1));
    }
    if (cap) out[s.n < cap ? s.n : cap - 1] = 0;
    return s.n;
}

static char *formata_novo(const char *fmt, Fonte *f) {
    Fonte copia = *f;
    size_t n = formata(NULL, 0, fmt, &copia);
    char *b = malloc(n + 1);
    formata(b, n + 1, fmt, f);
    return b;
}

void I_sprintf(CPU *c) { RT_PRIMEIRA("sprintf");
    Args a = args_de(c); uint32_t buf = arg32(&a); uint32_t fmt = arg32(&a);
    Fonte f = { 0, a, 0 };
    char *t = formata_novo(G2H(fmt), &f);
    size_t n = strlen(t);
    memcpy(g_mem + buf, t, n + 1);
    free(t);
    ret32(c, (uint32_t)n);
}
void I_snprintf(CPU *c) { RT_PRIMEIRA("snprintf");
    Args a = args_de(c); uint32_t buf = arg32(&a), cap = arg32(&a), fmt = arg32(&a);
    Fonte f = { 0, a, 0 };
    ret32(c, (uint32_t)formata(G2H(buf), cap, G2H(fmt), &f));
}
void I_vsnprintf(CPU *c) { RT_PRIMEIRA("vsnprintf");
    Fonte f = { 1, {0}, c->r[3] };
    ret32(c, (uint32_t)formata(G2H(c->r[0]), c->r[1], G2H(c->r[2]), &f));
}
void I_vsprintf(CPU *c) { RT_PRIMEIRA("vsprintf");
    Fonte f = { 1, {0}, c->r[2] };
    char *t = formata_novo(G2H(c->r[1]), &f);
    size_t n = strlen(t);
    memcpy(g_mem + c->r[0], t, n + 1);
    free(t);
    ret32(c, (uint32_t)n);
}

/* ======================================================================== */
/* log do Android                                                             */
void rt_log_prio(int prio, const char *tag, const char *msg);
void I___android_log_print(CPU *c) { RT_PRIMEIRA("__android_log_print");
    Args a = args_de(c); int prio = (int)arg32(&a); uint32_t tag = arg32(&a), fmt = arg32(&a);
    Fonte f = { 0, a, 0 };
    char *t = formata_novo(G2H(fmt), &f);
    rt_log_prio(prio, tag ? (const char *)G2H(tag) : "MGS2", t);
    free(t);
    ret32(c, 1);
}
void I___assert2(CPU *c) { RT_PRIMEIRA("__assert2");
    rt_fatal("assert do jogo: %s:%d %s: %s", (char *)G2H(c->r[0]), (int)c->r[1], (char *)G2H(c->r[2]), (char *)G2H(c->r[3]));
}

/* ======================================================================== */
/* FILE*: o jogo ve um endereco seu; aqui dentro e um FILE* do hospedeiro     */
#define MAX_ARQ 256
typedef struct { uint32_t g; FILE *h; int log; } Arq;
static Arq arqs[MAX_ARQ];
static Trava trava_arq;
static uint32_t sF;   /* __sF do jogo: stdin/stdout/stderr, 84 bytes cada */

static FILE *arq_h(uint32_t g) {
    for (int k = 0; k < MAX_ARQ; k++) if (arqs[k].g == g) return arqs[k].h;
    return NULL;
}
static int arq_eh_log(uint32_t g) { return g == sF + 84 || g == sF + 168; }
static uint32_t arq_novo(FILE *h) {
    trava(&trava_arq);
    for (int k = 0; k < MAX_ARQ; k++) if (!arqs[k].g) {
        arqs[k].g = heap_calloc(1, 84); arqs[k].h = h;
        destrava(&trava_arq); return arqs[k].g;
    }
    destrava(&trava_arq);
    return 0;
}
static void arq_fecha(uint32_t g) {
    trava(&trava_arq);
    for (int k = 0; k < MAX_ARQ; k++) if (arqs[k].g == g) { heap_free(g); arqs[k].g = 0; arqs[k].h = NULL; }
    destrava(&trava_arq);
}

/* saida padrao do jogo vai para o log, por linha */
static __thread char linha_log[1024];
static __thread size_t n_linha;
static void log_escreve(const char *p, size_t n) {
    for (size_t k = 0; k < n; k++) {
        if (p[k] == '\n' || n_linha == sizeof linha_log - 1) {
            linha_log[n_linha] = 0; rt_log_prio(4, "MGS2-stdout", linha_log); n_linha = 0;
            if (p[k] == '\n') continue;
        }
        linha_log[n_linha++] = p[k];
    }
}

void libc_inicia(uint32_t sF_jogo, uint32_t stdout_var, uint32_t stderr_var) {
    trava_inicia(&trava_arq);
    sF = sF_jogo;
    arqs[0].g = sF; arqs[0].h = stdin;
    arqs[1].g = sF + 84; arqs[1].h = stdout;
    arqs[2].g = sF + 168; arqs[2].h = stderr;
    uint32_t o = sF + 84, e = sF + 168;
    if (stdout_var) memcpy(g_mem + stdout_var, &o, 4);
    if (stderr_var) memcpy(g_mem + stderr_var, &e, 4);
}

/* caminhos do jogo passam pelo tradutor de caminho (definido no android.c) */
const char *rt_caminho(const char *p, char *buf, size_t n);

void I_fopen(CPU *c) { RT_PRIMEIRA("fopen");
    char buf[1024];
    const char *p = rt_caminho(G2H(c->r[0]), buf, sizeof buf);
    FILE *h = NULL;
#ifndef _WIN32
    FILE *aj_abre_config(const char *caminho, const char *modo);
    h = aj_abre_config(p, G2H(c->r[1]));    /* config da Forge com os ajustes do usuario */
#endif
    if (!h) h = fopen(p, G2H(c->r[1]));
    if (!h) {   /* falha de fopen sempre no log (as 40 primeiras): o motor usa o NULL sem conferir */
        static int nf; if (__atomic_fetch_add(&nf, 1, __ATOMIC_RELAXED) < 40)
            rt_log("fopen FALHOU: %s (%s) pedido %s", p, (char *)G2H(c->r[1]), (char *)G2H(c->r[0]));
    }
#ifdef MGS2_DEPURA
    { static int n; if (__atomic_fetch_add(&n, 1, __ATOMIC_RELAXED) < 80) rt_log("fopen(%s, %s) -> %s", p, (char *)G2H(c->r[1]), h ? "ok" : "falhou"); }
#endif
    ret32(c, h ? arq_novo(h) : 0);
}
void I_fdopen(CPU *c) { RT_PRIMEIRA("fdopen");
#ifdef _WIN32
    FILE *h = _fdopen((int)c->r[0], G2H(c->r[1]));
#else
    FILE *h = fdopen((int)c->r[0], G2H(c->r[1]));
#endif
    ret32(c, h ? arq_novo(h) : 0);
}
void I_fclose(CPU *c) { RT_PRIMEIRA("fclose");
    FILE *h = arq_h(c->r[0]);
    int r = h ? fclose(h) : -1;
    arq_fecha(c->r[0]);
    ret32(c, (uint32_t)r);
}
void I_fread(CPU *c) { RT_PRIMEIRA("fread");
    FILE *h = arq_h(c->r[3]);
    ret32(c, h ? (uint32_t)fread(G2H(c->r[0]), c->r[1], c->r[2], h) : 0);
}
void I_fwrite(CPU *c) { RT_PRIMEIRA("fwrite");
    if (arq_eh_log(c->r[3])) { log_escreve(G2H(c->r[0]), (size_t)c->r[1] * c->r[2]); ret32(c, c->r[2]); return; }
    FILE *h = arq_h(c->r[3]);
    ret32(c, h ? (uint32_t)fwrite(G2H(c->r[0]), c->r[1], c->r[2], h) : 0);
}
void I_fseek(CPU *c) { RT_PRIMEIRA("fseek"); FILE *h = arq_h(c->r[0]); ret32(c, h ? (uint32_t)fseek(h, (int32_t)c->r[1], (int)c->r[2]) : (uint32_t)-1); }
void I_ftell(CPU *c) { RT_PRIMEIRA("ftell"); FILE *h = arq_h(c->r[0]); ret32(c, h ? (uint32_t)(int32_t)ftell(h) : (uint32_t)-1); }
void I_feof(CPU *c) { RT_PRIMEIRA("feof"); FILE *h = arq_h(c->r[0]); ret32(c, h ? (uint32_t)feof(h) : 1); }
void I_ferror(CPU *c) { RT_PRIMEIRA("ferror"); FILE *h = arq_h(c->r[0]); ret32(c, h ? (uint32_t)ferror(h) : 1); }
void I_clearerr(CPU *c) { RT_PRIMEIRA("clearerr"); FILE *h = arq_h(c->r[0]); if (h) clearerr(h); }
void I_fflush(CPU *c) { RT_PRIMEIRA("fflush"); FILE *h = c->r[0] ? arq_h(c->r[0]) : NULL; ret32(c, (uint32_t)fflush(h)); }
void I_fileno(CPU *c) { RT_PRIMEIRA("fileno");
    FILE *h = arq_h(c->r[0]);
#ifdef _WIN32
    ret32(c, h ? (uint32_t)_fileno(h) : (uint32_t)-1);
#else
    ret32(c, h ? (uint32_t)fileno(h) : (uint32_t)-1);
#endif
}
void I_setbuf(CPU *c) { RT_PRIMEIRA("setbuf"); (void)c; }
void I_setvbuf(CPU *c) { RT_PRIMEIRA("setvbuf"); ret32(c, 0); }
void I_flockfile(CPU *c) { RT_PRIMEIRA("flockfile"); (void)c; }
void I_funlockfile(CPU *c) { RT_PRIMEIRA("funlockfile"); (void)c; }
void I_fgets(CPU *c) { RT_PRIMEIRA("fgets");
    FILE *h = arq_h(c->r[2]);
    char *r = h ? fgets(G2H(c->r[0]), (int)c->r[1], h) : NULL;
    ret32(c, r ? c->r[0] : 0);
}
void I_fputs(CPU *c) { RT_PRIMEIRA("fputs");
    const char *s = G2H(c->r[0]);
    if (arq_eh_log(c->r[1])) { log_escreve(s, strlen(s)); ret32(c, 1); return; }
    FILE *h = arq_h(c->r[1]); ret32(c, h ? (uint32_t)fputs(s, h) : (uint32_t)-1);
}
void I_puts(CPU *c) { RT_PRIMEIRA("puts"); const char *s = G2H(c->r[0]); log_escreve(s, strlen(s)); log_escreve("\n", 1); ret32(c, 1); }
void I_fputc(CPU *c) { RT_PRIMEIRA("fputc");
    char ch = (char)c->r[0];
    if (arq_eh_log(c->r[1])) { log_escreve(&ch, 1); ret32(c, (uint8_t)ch); return; }
    FILE *h = arq_h(c->r[1]); ret32(c, h ? (uint32_t)fputc(ch, h) : (uint32_t)-1);
}
void I_putc(CPU *c) { RT_PRIMEIRA("putc"); I_fputc(c); }
void I_getc(CPU *c) { RT_PRIMEIRA("getc"); FILE *h = arq_h(c->r[0]); ret32(c, h ? (uint32_t)getc(h) : (uint32_t)-1); }
void I_ungetc(CPU *c) { RT_PRIMEIRA("ungetc"); FILE *h = arq_h(c->r[1]); ret32(c, h ? (uint32_t)ungetc((int)c->r[0], h) : (uint32_t)-1); }
void I_getwc(CPU *c) { RT_PRIMEIRA("getwc"); FILE *h = arq_h(c->r[0]); ret32(c, h ? (uint32_t)getwc(h) : (uint32_t)WEOF); }
void I_ungetwc(CPU *c) { RT_PRIMEIRA("ungetwc"); FILE *h = arq_h(c->r[1]); ret32(c, h ? (uint32_t)ungetwc((wint_t)c->r[0], h) : (uint32_t)WEOF); }
void I_putwc(CPU *c) { RT_PRIMEIRA("putwc");
    if (arq_eh_log(c->r[1])) { char ch = (char)c->r[0]; log_escreve(&ch, 1); ret32(c, c->r[0]); return; }
    FILE *h = arq_h(c->r[1]); ret32(c, h ? (uint32_t)putwc((wchar_t)c->r[0], h) : (uint32_t)WEOF);
}
void I_fprintf(CPU *c) { RT_PRIMEIRA("fprintf");
    Args a = args_de(c); uint32_t arq = arg32(&a), fmt = arg32(&a);
    Fonte f = { 0, a, 0 };
    char *t = formata_novo(G2H(fmt), &f);
    size_t n = strlen(t);
    if (arq_eh_log(arq)) log_escreve(t, n);
    else { FILE *h = arq_h(arq); if (h) fwrite(t, 1, n, h); }
    free(t);
    ret32(c, (uint32_t)n);
}
void I_printf(CPU *c) { RT_PRIMEIRA("printf");
    Args a = args_de(c); uint32_t fmt = arg32(&a);
    Fonte f = { 0, a, 0 };
    char *t = formata_novo(G2H(fmt), &f);
    size_t n = strlen(t);
    log_escreve(t, n);
    free(t);
    ret32(c, (uint32_t)n);
}

/* ======================================================================== */
/* sscanf: um trecho (texto + uma conversao) por vez, com %n para andar       */
void I_sscanf(CPU *c) { RT_PRIMEIRA("sscanf");
    Args a = args_de(c);
    const char *s = G2H(arg32(&a));
    const char *fmt = G2H(arg32(&a));
    int atribuidos = 0;
    size_t pos = 0;
    char trecho[256];
    while (*fmt) {
        /* texto literal ate o proximo % (inclusive espacos) */
        const char *q = fmt;
        while (*q && *q != '%') q++;
        if (*q == '%' && q[1] == '%') { q += 2; while (*q && *q != '%') q++; }
        size_t lit = (size_t)(q - fmt);
        if (!*q) {
            /* so literal no fim: consome e acaba */
            memcpy(trecho, fmt, lit < 200 ? lit : 200); trecho[lit < 200 ? lit : 200] = 0;
            strcat(trecho, "%n");
            int n = -1; sscanf(s + pos, trecho, &n);
            break;
        }
        /* a conversao */
        const char *p = q + 1;
        int suprime = 0;
        if (*p == '*') { suprime = 1; p++; }
        while (*p >= '0' && *p <= '9') p++;
        int lg = 0;
        while (*p == 'h' || *p == 'l' || *p == 'L' || *p == 'q' || *p == 'j' || *p == 'z') {
            if (*p == 'l') lg = lg == 3 ? 4 : 3; else if (*p == 'h') lg = lg == 2 ? 1 : 2; else if (*p == 'L' || *p == 'q' || *p == 'j') lg = 4; else lg = 3;
            p++;
        }
        char cv = *p;
        const char *fimconv = p + 1;
        if (cv == '[') { fimconv = p + 1; if (*fimconv == '^') fimconv++; if (*fimconv == ']') fimconv++; while (*fimconv && *fimconv != ']') fimconv++; if (*fimconv) fimconv++; }
        /* monta o trecho com o tamanho do hospedeiro */
        size_t k = 0;
        memcpy(trecho + k, fmt, lit); k += lit;
        trecho[k++] = '%';
        if (suprime) trecho[k++] = '*';
        const char *w = q + 1 + suprime;
        while (*w >= '0' && *w <= '9') trecho[k++] = *w++;
        int dest64 = 0, destf = 0, desth = 0, desthh = 0, destd = 0;
        switch (cv) {
        case 'd': case 'i': case 'u': case 'x': case 'X': case 'o':
            if (lg == 4) { trecho[k++] = 'l'; trecho[k++] = 'l'; dest64 = 1; }
            else if (lg == 2) { trecho[k++] = 'h'; desth = 1; }
            else if (lg == 1) { trecho[k++] = 'h'; trecho[k++] = 'h'; desthh = 1; }
            trecho[k++] = cv; break;
        case 'f': case 'e': case 'g': case 'E': case 'G': case 'a':
            if (lg >= 3) { trecho[k++] = 'l'; destd = 1; } else destf = 1;
            trecho[k++] = cv; break;
        case 'n':
            trecho[k++] = 'n'; break;
        default:
            if (lg == 3 && (cv == 's' || cv == 'c')) trecho[k++] = 'l';
            memcpy(trecho + k, p, (size_t)(fimconv - p)); k += (size_t)(fimconv - p);
            break;
        }
        memcpy(trecho + k, "%n", 3);
        int andou = -1, r;
        if (suprime) r = sscanf(s + pos, trecho, &andou);
        else {
            uint32_t g = arg32(&a);
            void *d = G2H(g);
            if (cv == 'n') { int32_t v = (int32_t)pos; memcpy(d, &v, 4); andou = 0; r = 0; memcpy(trecho, "%n", 3); sscanf(s + pos, fmt[0] == '%' ? "%n" : "%n", &andou); andou = 0; }
            else if (dest64) { long long v; r = sscanf(s + pos, trecho, &v, &andou); if (r == 1) memcpy(d, &v, 8); }
            else if (destd) { double v; r = sscanf(s + pos, trecho, &v, &andou); if (r == 1) memcpy(d, &v, 8); }
            else if (destf) { float v; r = sscanf(s + pos, trecho, &v, &andou); if (r == 1) memcpy(d, &v, 4); }
            else if (desth) { short v; r = sscanf(s + pos, trecho, &v, &andou); if (r == 1) memcpy(d, &v, 2); }
            else if (desthh) { char v; r = sscanf(s + pos, trecho, &v, &andou); if (r == 1) memcpy(d, &v, 1); }
            else if (cv == 'd' || cv == 'i' || cv == 'u' || cv == 'x' || cv == 'X' || cv == 'o') { int v; r = sscanf(s + pos, trecho, &v, &andou); if (r == 1) memcpy(d, &v, 4); }
            else r = sscanf(s + pos, trecho, d, &andou);   /* s, c, [ : escreve direto */
            if (r == 1 && cv != 'n') atribuidos++;
            if (r == EOF && atribuidos == 0) { ret32(c, (uint32_t)EOF); return; }
        }
        if (andou < 0) break;
        pos += (size_t)andou;
        fmt = fimconv;
    }
    ret32(c, (uint32_t)atribuidos);
}

/* ======================================================================== */
/* stat: layout do bionic de 32 bits (104 bytes)                             */
static void stat_para_jogo(uint32_t g, const struct stat *st) {
    uint8_t *p = g_mem + g;
    memset(p, 0, 104);
    uint64_t dev = (uint64_t)st->st_dev, ino = (uint64_t)st->st_ino, rdev = (uint64_t)st->st_rdev;
    uint32_t ino32 = (uint32_t)ino, mode = (uint32_t)st->st_mode, nlink = (uint32_t)st->st_nlink;
    uint32_t uid = (uint32_t)st->st_uid, gid = (uint32_t)st->st_gid;
    int64_t tam = (int64_t)st->st_size;
    memcpy(p + 0, &dev, 8); memcpy(p + 12, &ino32, 4); memcpy(p + 16, &mode, 4);
    memcpy(p + 20, &nlink, 4); memcpy(p + 24, &uid, 4); memcpy(p + 28, &gid, 4);
    memcpy(p + 32, &rdev, 8); memcpy(p + 48, &tam, 8);
#ifndef _WIN32
    uint32_t blksize = (uint32_t)st->st_blksize; uint64_t blocks = (uint64_t)st->st_blocks;
    memcpy(p + 56, &blksize, 4); memcpy(p + 64, &blocks, 8);
    int32_t t[6] = { (int32_t)st->st_atim.tv_sec, (int32_t)st->st_atim.tv_nsec, (int32_t)st->st_mtim.tv_sec,
                     (int32_t)st->st_mtim.tv_nsec, (int32_t)st->st_ctim.tv_sec, (int32_t)st->st_ctim.tv_nsec };
#else
    int32_t t[6] = { (int32_t)st->st_atime, 0, (int32_t)st->st_mtime, 0, (int32_t)st->st_ctime, 0 };
#endif
    memcpy(p + 72, t, 24);
    memcpy(p + 96, &ino, 8);
}
void I_stat(CPU *c) { RT_PRIMEIRA("stat");
    char buf[1024]; struct stat st;
    int r = stat(rt_caminho(G2H(c->r[0]), buf, sizeof buf), &st);
    if (!r) stat_para_jogo(c->r[1], &st);
    ret32(c, (uint32_t)r);
}
void I_lstat(CPU *c) { RT_PRIMEIRA("lstat");
#ifdef _WIN32
    I_stat(c);
#else
    char buf[1024]; struct stat st;
    int r = lstat(rt_caminho(G2H(c->r[0]), buf, sizeof buf), &st);
    if (!r) stat_para_jogo(c->r[1], &st);
    ret32(c, (uint32_t)r);
#endif
}
void I_fstat(CPU *c) { RT_PRIMEIRA("fstat");
    struct stat st;
    int r = fstat((int)c->r[0], &st);
    if (!r) stat_para_jogo(c->r[1], &st);
    ret32(c, (uint32_t)r);
}

/* ======================================================================== */
/* diretorios: DIR* vira endereco do jogo com o dirent dentro                 */
#ifndef _WIN32
#define MAX_DIR 64
static struct { uint32_t g; DIR *h; } dirs[MAX_DIR];
void I_opendir(CPU *c) { RT_PRIMEIRA("opendir");
    char buf[1024];
    DIR *h = opendir(rt_caminho(G2H(c->r[0]), buf, sizeof buf));
    if (!h) { ret32(c, 0); return; }
    for (int k = 0; k < MAX_DIR; k++) if (!dirs[k].g) {
        dirs[k].g = heap_calloc(1, 288); dirs[k].h = h; ret32(c, dirs[k].g); return;
    }
    closedir(h); ret32(c, 0);
}
void I_readdir(CPU *c) { RT_PRIMEIRA("readdir");
    for (int k = 0; k < MAX_DIR; k++) if (dirs[k].g == c->r[0]) {
        struct dirent *d = readdir(dirs[k].h);
        if (!d) { ret32(c, 0); return; }
        uint8_t *p = g_mem + dirs[k].g;
        uint64_t ino = d->d_ino; int64_t off = d->d_off; uint16_t rl = 280; uint8_t ty = d->d_type;
        memcpy(p, &ino, 8); memcpy(p + 8, &off, 8); memcpy(p + 16, &rl, 2); p[18] = ty;
        snprintf((char *)p + 19, 256, "%s", d->d_name);
        ret32(c, dirs[k].g); return;
    }
    ret32(c, 0);
}
void I_closedir(CPU *c) { RT_PRIMEIRA("closedir");
    for (int k = 0; k < MAX_DIR; k++) if (dirs[k].g == c->r[0]) {
        closedir(dirs[k].h); heap_free(dirs[k].g); dirs[k].g = 0; ret32(c, 0); return;
    }
    ret32(c, (uint32_t)-1);
}
#else
void I_opendir(CPU *c) { RT_PRIMEIRA("opendir"); ret32(c, 0); }
void I_readdir(CPU *c) { RT_PRIMEIRA("readdir"); ret32(c, 0); }
void I_closedir(CPU *c) { RT_PRIMEIRA("closedir"); ret32(c, 0); }
#endif

/* ======================================================================== */
/* tempo: time_t, timeval e timespec de 32 bits                               */
void I_time(CPU *c) { RT_PRIMEIRA("time");
    int32_t t = (int32_t)time(NULL);
    if (c->r[0]) memcpy(g_mem + c->r[0], &t, 4);
    ret32(c, (uint32_t)t);
}
void I_gettimeofday(CPU *c) { RT_PRIMEIRA("gettimeofday");
#ifdef _WIN32
    struct timespec ts; timespec_get(&ts, TIME_UTC);
    int32_t v[2] = { (int32_t)ts.tv_sec, (int32_t)(ts.tv_nsec / 1000) };
#else
    struct timeval tv; gettimeofday(&tv, NULL);
    int32_t v[2] = { (int32_t)tv.tv_sec, (int32_t)tv.tv_usec };
#endif
    if (c->r[0]) memcpy(g_mem + c->r[0], v, 8);
    ret32(c, 0);
}
void I_clock_gettime(CPU *c) { RT_PRIMEIRA("clock_gettime");
    struct timespec ts;
#ifdef _WIN32
    timespec_get(&ts, TIME_UTC);
#else
    int r = clock_gettime((clockid_t)c->r[0], &ts);
    if (r) { ret32(c, (uint32_t)r); return; }
#endif
    int32_t v[2] = { (int32_t)ts.tv_sec, (int32_t)ts.tv_nsec };
    memcpy(g_mem + c->r[1], v, 8);
    ret32(c, 0);
}
void I_nanosleep(CPU *c) { RT_PRIMEIRA("nanosleep");
    int32_t v[2]; memcpy(v, g_mem + c->r[0], 8);
#ifdef _WIN32
    Sleep((DWORD)(v[0] * 1000 + v[1] / 1000000));
    ret32(c, 0);
#else
    struct timespec ts = { v[0], v[1] };
    ret32(c, (uint32_t)nanosleep(&ts, NULL));
#endif
}
/* struct tm de 32 bits: 9 int + long tm_gmtoff + char* tm_zone = 44 bytes */
static __thread uint32_t t_tm;
static uint32_t tm_para_jogo(const struct tm *t, uint32_t g) {
    if (!g) { if (!t_tm) t_tm = heap_calloc(1, 44); g = t_tm; }
    int32_t v[11] = { t->tm_sec, t->tm_min, t->tm_hour, t->tm_mday, t->tm_mon, t->tm_year, t->tm_wday, t->tm_yday, t->tm_isdst, 0, 0 };
    memcpy(g_mem + g, v, 44);
    return g;
}
static void tm_do_jogo(uint32_t g, struct tm *t) {
    int32_t v[9]; memcpy(v, g_mem + g, 36);
    memset(t, 0, sizeof *t);
    t->tm_sec = v[0]; t->tm_min = v[1]; t->tm_hour = v[2]; t->tm_mday = v[3]; t->tm_mon = v[4];
    t->tm_year = v[5]; t->tm_wday = v[6]; t->tm_yday = v[7]; t->tm_isdst = v[8];
}
void I_localtime(CPU *c) { RT_PRIMEIRA("localtime");
    int32_t t32; memcpy(&t32, g_mem + c->r[0], 4); time_t t = t32;
    struct tm *r = localtime(&t);
    ret32(c, r ? tm_para_jogo(r, 0) : 0);
}
void I_gmtime(CPU *c) { RT_PRIMEIRA("gmtime");
    int32_t t32; memcpy(&t32, g_mem + c->r[0], 4); time_t t = t32;
    struct tm *r = gmtime(&t);
    ret32(c, r ? tm_para_jogo(r, 0) : 0);
}
void I_strftime(CPU *c) { RT_PRIMEIRA("strftime");
    struct tm t; tm_do_jogo(c->r[3], &t);
    ret32(c, (uint32_t)strftime(G2H(c->r[0]), c->r[1], G2H(c->r[2]), &t));
}
void I_wcsftime(CPU *c) { RT_PRIMEIRA("wcsftime");
    struct tm t; tm_do_jogo(c->r[3], &t);
    ret32(c, (uint32_t)wcsftime(G2H(c->r[0]), c->r[1], G2H(c->r[2]), &t));
}

/* ======================================================================== */
/* mbstate_t: 4 bytes no jogo                                                 */
void I_mbrtowc(CPU *c) { RT_PRIMEIRA("mbrtowc");
    mbstate_t st; memset(&st, 0, sizeof st);
    if (c->r[3]) memcpy(&st, g_mem + c->r[3], 4);
    size_t r = mbrtowc(G2H(c->r[0]), G2H(c->r[1]), c->r[2], &st);
    if (c->r[3]) memcpy(g_mem + c->r[3], &st, 4);
    ret32(c, (uint32_t)r);
}
void I_wcrtomb(CPU *c) { RT_PRIMEIRA("wcrtomb");
    mbstate_t st; memset(&st, 0, sizeof st);
    if (c->r[2]) memcpy(&st, g_mem + c->r[2], 4);
    size_t r = wcrtomb(G2H(c->r[0]), (wchar_t)c->r[1], &st);
    if (c->r[2]) memcpy(g_mem + c->r[2], &st, 4);
    ret32(c, (uint32_t)r);
}

/* ======================================================================== */
/* qsort com o comparador do jogo                                             */
static __thread uint32_t q_cmp, q_base_g;
static __thread uint8_t *q_base_h;
static int cmp_ponte(const void *a, const void *b) {
    uint32_t ga = q_base_g + (uint32_t)((const uint8_t *)a - q_base_h);
    uint32_t gb = q_base_g + (uint32_t)((const uint8_t *)b - q_base_h);
    return (int32_t)jogo_chama(q_cmp, 2, ga, gb);
}
void I_qsort(CPU *c) { RT_PRIMEIRA("qsort");
    uint32_t sc = q_cmp, sg = q_base_g; uint8_t *sh = q_base_h;
    q_cmp = c->r[3]; q_base_g = c->r[0]; q_base_h = G2H(c->r[0]);
    qsort(q_base_h, c->r[1], c->r[2], cmp_ponte);
    q_cmp = sc; q_base_g = sg; q_base_h = sh;
}

/* ======================================================================== */
/* processo                                                                   */
#define MAX_ATEXIT 256
static struct { uint32_t fn, arg; } atexits[MAX_ATEXIT];
static int n_atexit;
void I___cxa_atexit(CPU *c) { RT_PRIMEIRA("__cxa_atexit");
    if (n_atexit < MAX_ATEXIT) { atexits[n_atexit].fn = c->r[0]; atexits[n_atexit].arg = c->r[1]; n_atexit++; }
    ret32(c, 0);
}
void I___cxa_finalize(CPU *c) { RT_PRIMEIRA("__cxa_finalize"); (void)c; }
void I_exit(CPU *c) { RT_PRIMEIRA("exit");
    rt_log("o jogo chamou exit(%d)", (int)c->r[0]);
    for (int k = n_atexit - 1; k >= 0; k--) jogo_chama(atexits[k].fn, 1, atexits[k].arg);
    exit((int)c->r[0]);
}
void I__exit(CPU *c) { RT_PRIMEIRA("_exit"); rt_log("o jogo chamou _exit(%d)", (int)c->r[0]); _exit((int)c->r[0]); }
void I_abort(CPU *c) { RT_PRIMEIRA("abort"); rt_fatal("o jogo chamou abort() (lr=%08x)", c->r[14]); }
void I_signal(CPU *c) { RT_PRIMEIRA("signal"); ret32(c, 0); }
void I_sysconf(CPU *c) { RT_PRIMEIRA("sysconf");
#ifdef _WIN32
    ret32(c, c->r[0] == 0x27 ? 4096 : 4);
#else
    ret32(c, (uint32_t)sysconf((int)c->r[0]));
#endif
}
void I_sysinfo(CPU *c) { RT_PRIMEIRA("sysinfo");
    /* struct sysinfo de 32 bits: long uptime; ulong loads[3]; ulong total,free,shared,buffer,
     * totalswap,freeswap; ushort procs; ushort pad; ulong totalhigh,freehigh; uint mem_unit; char f[8] */
    uint32_t v[16]; memset(v, 0, sizeof v);
#ifndef _WIN32
    struct sysinfo s; sysinfo(&s);
    v[0] = (uint32_t)s.uptime;
    uint64_t unidade = s.mem_unit ? s.mem_unit : 1;
    /* em unidades de 4 KB, para caber em 32 bits */
    v[4] = (uint32_t)((uint64_t)s.totalram * unidade / 4096); v[5] = (uint32_t)((uint64_t)s.freeram * unidade / 4096);
    v[13] = 4096;
    uint16_t procs = s.procs; memcpy((uint8_t *)v + 40, &procs, 2);
#else
    v[4] = 2u << 20; v[5] = 1u << 20; v[13] = 4096;
#endif
    memcpy(g_mem + c->r[0], v, 64);
    ret32(c, 0);
}
void I_mmap(CPU *c) { RT_PRIMEIRA("mmap");
    /* so anonimo faz sentido aqui: vem do heap do jogo, alinhado a pagina */
    Args a = args_de(c);
    uint32_t addr = arg32(&a), len = arg32(&a); (void)addr;
    arg32(&a); uint32_t flags = arg32(&a); int32_t fd = (int32_t)arg32(&a);
    if (!(flags & 0x20) && fd >= 0) { rt_log("mmap de arquivo nao suportado"); ret32(c, 0xffffffffu); return; }
    uint32_t p = heap_memalign(4096, len);
    if (!p) { ret32(c, 0xffffffffu); return; }
    memset(g_mem + p, 0, len);
    ret32(c, p);
}
void I_munmap(CPU *c) { RT_PRIMEIRA("munmap"); heap_free(c->r[0]); ret32(c, 0); }
void I_mprotect(CPU *c) { RT_PRIMEIRA("mprotect"); ret32(c, 0); }
void I_ioctl(CPU *c) { RT_PRIMEIRA("ioctl"); rt_log("ioctl(%d, %08x) ignorado", (int)c->r[0], c->r[1]); ret32(c, (uint32_t)-1); }
void I_syscall(CPU *c) { RT_PRIMEIRA("syscall");
    /* numeros do ARM32 */
    switch (c->r[0]) {
    case 224: /* gettid */
#ifndef _WIN32
        ret32(c, (uint32_t)gettid());
#else
        ret32(c, GetCurrentThreadId());
#endif
        return;
#ifndef _WIN32
    case 240: { /* futex(uaddr, op, val, timeout, uaddr2, val3): a memoria do jogo e
                 * do proprio processo, entao o futex do hospedeiro serve direto */
        uint32_t sp = c->r[13];
        uint32_t uaddr = c->r[1], op = c->r[2], val = c->r[3], pts, uaddr2, val3;
        memcpy(&pts, g_mem + sp, 4); memcpy(&uaddr2, g_mem + sp + 4, 4); memcpy(&val3, g_mem + sp + 8, 4);
        int cmd = op & 127;
        struct timespec ts, *tsp = NULL;
        long r;
        if ((cmd == 0 || cmd == 9) && pts) {    /* WAIT / WAIT_BITSET: timespec de 32 bits */
            int32_t v[2]; memcpy(v, g_mem + pts, 8);
            ts.tv_sec = v[0]; ts.tv_nsec = v[1]; tsp = &ts;
        }
        if (cmd == 0 || cmd == 9 || cmd == 1 || cmd == 10)
            r = syscall(SYS_futex, g_mem + uaddr, op, val, tsp, NULL, val3);
        else if (cmd == 3 || cmd == 4)          /* REQUEUE / CMP_REQUEUE: 4o arg e contagem */
            r = syscall(SYS_futex, g_mem + uaddr, op, val, (void *)(uintptr_t)pts, g_mem + uaddr2, val3);
        else if (cmd == 5)                      /* WAKE_OP */
            r = syscall(SYS_futex, g_mem + uaddr, op, val, (void *)(uintptr_t)pts, g_mem + uaddr2, val3);
        else { rt_log("futex op %u nao suportada", op); errno = ENOSYS; r = -1; }
        ret32(c, (uint32_t)r);
        return;
    }
    case 268: /* tgkill(pid, tid, sig): a camada da TransGaming manda sinal 0 para ver se uma
               * thread ainda vive; os tids sao os do hospedeiro (gettid acima) */
        ret32(c, (uint32_t)syscall(SYS_tgkill, (int)c->r[1], (int)c->r[2], (int)c->r[3]));
        return;
#endif
    default:
        rt_log("syscall %u nao suportada", c->r[0]);
        ret32(c, (uint32_t)-1);
    }
}
void I_writev(CPU *c) { RT_PRIMEIRA("writev");
    uint32_t iov = c->r[1], n = c->r[2], total = 0;
    for (uint32_t k = 0; k < n; k++) {
        uint32_t base, len; memcpy(&base, g_mem + iov + 8 * k, 4); memcpy(&len, g_mem + iov + 8 * k + 4, 4);
#ifdef _WIN32
        int r = _write((int)c->r[0], G2H(base), len);
#else
        ssize_t r = write((int)c->r[0], G2H(base), len);
#endif
        if (r < 0) { ret32(c, (uint32_t)-1); return; }
        total += (uint32_t)r;
    }
    ret32(c, total);
}

/* dlopen/dlsym: o jogo so usa para achar EGL/GLES; dlsym devolve a ponte */
uint32_t gl_ponte_por_nome(const char *nome);
void I_dlopen(CPU *c) { RT_PRIMEIRA("dlopen"); rt_log("dlopen(%s)", c->r[0] ? (char *)G2H(c->r[0]) : "NULL"); ret32(c, 0x1000); }
void I_dlclose(CPU *c) { RT_PRIMEIRA("dlclose"); ret32(c, 0); }
void I_dlsym(CPU *c) { RT_PRIMEIRA("dlsym");
    const char *n = G2H(c->r[1]);
    uint32_t p = gl_ponte_por_nome(n);
    if (!p) p = rt_exportado(n);
    if (!p) rt_log("dlsym(%s) sem resultado", n);
    ret32(c, p);
}

/* desenrolador de excecoes da gnustl: tabela exidx do modulo do pc */
void I___gnu_Unwind_Find_exidx(CPU *c) { RT_PRIMEIRA("__gnu_Unwind_Find_exidx");
    extern uint32_t g_exidx[2][2];   /* {inicio, n} por biblioteca, preenchido no rt_inicia */
    uint32_t pc = c->r[0];
    for (int k = 0; k < 2; k++) {
        const ImagemLib *l = &g_libs[k];
        if (pc >= l->base && pc < l->base + l->tam) {
            memcpy(g_mem + c->r[1], &g_exidx[k][1], 4);
            ret32(c, g_exidx[k][0]); return;
        }
    }
    ret32(c, 0);
}
void I___google_potentially_blocking_region_begin(CPU *c) { RT_PRIMEIRA("__google_potentially_blocking_region_begin"); (void)c; }
void I___google_potentially_blocking_region_end(CPU *c) { RT_PRIMEIRA("__google_potentially_blocking_region_end"); (void)c; }
