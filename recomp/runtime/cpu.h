/* Contexto de CPU ARM32 e primitivas usadas pelo codigo gerado. */
#pragma once
#include <stdint.h>
#include <string.h>
#include <math.h>

typedef struct CPU {
    uint32_t r[16];
    uint32_t fn, fz, fc, fv;             /* bandeiras do APSR (0/1) */
    union {
        uint8_t u8[256];  int8_t s8[256];
        uint16_t u16[128]; int16_t s16[128];
        uint32_t u32[64]; int32_t s32[64];
        uint64_t u64[32]; int64_t s64[32];
        float f32[64];    double f64[32];
    } v;                                 /* s0-s31 / d0-d31 / q0-q15 */
    uint32_t fpnzcv, fpscr;
    uint32_t ex_a, ex_v, ex_ok;          /* monitor exclusivo (ldrex/strex) */
    uint32_t pilha_base, pilha_tam;      /* pilha do jogo desta thread */
    void *extra;                         /* uso do runtime */
} CPU;

extern uint8_t *g_mem;                   /* endereco 0 do jogo no hospedeiro */

typedef void (*FuncJogo)(CPU *);
void despacha(CPU *c, uint32_t alvo);
void falha_tabela(uint32_t onde, uint32_t indice);
void nao_suportado(CPU *c, uint32_t onde);
void armadilha(CPU *c, uint32_t onde);

/* ---- rastro de depuracao (compilar com -DRASTRO) ------------------------- */
#ifdef RASTRO
extern __thread const char *t_rastro[64];
extern __thread unsigned t_rastro_i;
#define RASTRO_MARCA() (t_rastro[t_rastro_i++ & 63] = __func__)
#else
#define RASTRO_MARCA() ((void)0)
#endif

/* ---- entrada / saida / chamadas ------------------------------------------ */
#define ENTRA RASTRO_MARCA(); \
    uint8_t *const m = g_mem; (void)m; \
    uint32_t r0 = c->r[0], r1 = c->r[1], r2 = c->r[2], r3 = c->r[3], r4 = c->r[4], \
             r5 = c->r[5], r6 = c->r[6], r7 = c->r[7], r8 = c->r[8], r9 = c->r[9], \
             r10 = c->r[10], r11 = c->r[11], r12 = c->r[12], sp = c->r[13], lr = c->r[14]; \
    uint32_t fn = c->fn, fz = c->fz, fc = c->fc, fv = c->fv; \
    const uint32_t lr0 = lr; (void)lr0

#define SALVA do { \
    c->r[0] = r0; c->r[1] = r1; c->r[2] = r2; c->r[3] = r3; c->r[4] = r4; c->r[5] = r5; \
    c->r[6] = r6; c->r[7] = r7; c->r[8] = r8; c->r[9] = r9; c->r[10] = r10; c->r[11] = r11; \
    c->r[12] = r12; c->r[13] = sp; c->r[14] = lr; \
    c->fn = fn; c->fz = fz; c->fc = fc; c->fv = fv; } while (0)

#define CARREGA do { \
    r0 = c->r[0]; r1 = c->r[1]; r2 = c->r[2]; r3 = c->r[3]; r4 = c->r[4]; r5 = c->r[5]; \
    r6 = c->r[6]; r7 = c->r[7]; r8 = c->r[8]; r9 = c->r[9]; r10 = c->r[10]; r11 = c->r[11]; \
    r12 = c->r[12]; sp = c->r[13]; lr = c->r[14]; \
    fn = c->fn; fz = c->fz; fc = c->fc; fv = c->fv; } while (0)

/* chamadas (bl/blx): as bandeiras nao atravessam uma chamada pela ABI do ARM;
 * CARREGA_CHF so onde o codigo seguinte as le (ajudantes __aeabi_c*cmp*) */
#define SALVA_CH do {     c->r[0] = r0; c->r[1] = r1; c->r[2] = r2; c->r[3] = r3; c->r[4] = r4; c->r[5] = r5;     c->r[6] = r6; c->r[7] = r7; c->r[8] = r8; c->r[9] = r9; c->r[10] = r10; c->r[11] = r11;     c->r[12] = r12; c->r[13] = sp; c->r[14] = lr; } while (0)
#define CARREGA_CH do {     r0 = c->r[0]; r1 = c->r[1]; r2 = c->r[2]; r3 = c->r[3]; r4 = c->r[4]; r5 = c->r[5];     r6 = c->r[6]; r7 = c->r[7]; r8 = c->r[8]; r9 = c->r[9]; r10 = c->r[10]; r11 = c->r[11];     r12 = c->r[12]; sp = c->r[13]; lr = c->r[14]; } while (0)
#define CARREGA_CHF CARREGA

/* Chamada a funcao que segue a ABI (medir_abi.py: 22.550 de 22.551 do jogo).
 * Retorno de funcao do jogo NAO grava as bandeiras: ninguem as le depois de uma
 * chamada (medir_bandeiras.py: 0 leituras em 147 mil chamadas fora da gnustl).
 * r4-r11/sp CONTINUAM voltando de c: deixar o clang mante-los vivos atraves da
 * chamada foi MEDIDO pior no ARM64 (+13% instrucoes, +27% stores: derramamento na
 * pilha do hospedeiro custa mais que a recarga de c). -DMGS2_ABI_SEM_RECARGA
 * liga esse modo so para medir; -DMGS2_CARREGA_TUDO volta ao 100% antigo. */
#if defined(MGS2_CARREGA_TUDO)
#define CARREGA_ABI CARREGA_CH
#define SAI_ABI SAI
#elif defined(MGS2_ABI_SEM_RECARGA)
#define CARREGA_ABI do { r0 = c->r[0]; r1 = c->r[1]; r2 = c->r[2]; r3 = c->r[3];     r12 = c->r[12]; lr = c->r[14]; } while (0)
#define SAI_ABI SALVA_CH; return
#else
#define CARREGA_ABI CARREGA_CH
#define SAI_ABI SALVA_CH; return
#endif

#define SAI SALVA; return

#define FALHA_TABELA(onde, i) do { falha_tabela(onde, i); SALVA; return; } while (0)
#define NAO_SUPORTADO(c, onde) nao_suportado(c, onde)
#define ARMADILHA(c, onde) armadilha(c, onde)

/* ---- memoria ------------------------------------------------------------- */
static inline uint32_t L32_(uint8_t *m, uint32_t a) { uint32_t v; memcpy(&v, m + a, 4); return v; }
static inline uint64_t L64_(uint8_t *m, uint32_t a) { uint64_t v; memcpy(&v, m + a, 8); return v; }
static inline uint32_t L16_(uint8_t *m, uint32_t a) { uint16_t v; memcpy(&v, m + a, 2); return v; }
static inline void S32_(uint8_t *m, uint32_t a, uint32_t v) { memcpy(m + a, &v, 4); }
static inline void S64_(uint8_t *m, uint32_t a, uint64_t v) { memcpy(m + a, &v, 8); }
static inline void S16_(uint8_t *m, uint32_t a, uint32_t v) { uint16_t x = (uint16_t)v; memcpy(m + a, &x, 2); }
#define L32(a)  L32_(m, (uint32_t)(a))
#define L64(a)  L64_(m, (uint32_t)(a))
#define L16(a)  L16_(m, (uint32_t)(a))
#define L16S(a) ((uint32_t)(int32_t)(int16_t)L16_(m, (uint32_t)(a)))
#define L8(a)   ((uint32_t)m[(uint32_t)(a)])
#define L8S(a)  ((uint32_t)(int32_t)(int8_t)m[(uint32_t)(a)])
#define S32(a, v) S32_(m, (uint32_t)(a), (uint32_t)(v))
#define S64(a, v) S64_(m, (uint32_t)(a), (uint64_t)(v))
#define S16(a, v) S16_(m, (uint32_t)(a), (uint32_t)(v))
#define S8(a, v)  (m[(uint32_t)(a)] = (uint8_t)(v))

#define BARREIRA() __atomic_thread_fence(__ATOMIC_SEQ_CST)

static inline uint32_t STREX32(CPU *c, uint32_t a, uint32_t v) {
    uint32_t esperado = c->ex_v;
    int ok = c->ex_ok && c->ex_a == a &&
             __atomic_compare_exchange_n((uint32_t *)(g_mem + a), &esperado, v, 0,
                                         __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST);
    c->ex_ok = 0;
    return ok ? 0 : 1;
}
static inline uint32_t STREX8(CPU *c, uint32_t a, uint32_t v) {
    uint8_t esperado = (uint8_t)c->ex_v;
    int ok = c->ex_ok && c->ex_a == a &&
             __atomic_compare_exchange_n(g_mem + a, &esperado, (uint8_t)v, 0,
                                         __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST);
    c->ex_ok = 0;
    return ok ? 0 : 1;
}

/* ---- deslocamentos por registrador (quantidade = byte baixo) ------------- */
static inline uint32_t ROR32(uint32_t x, uint32_t n) { n &= 31; return n ? (x >> n) | (x << (32 - n)) : x; }
static inline uint32_t SHL_R(uint32_t x, uint32_t s) { return s >= 32 ? 0 : x << s; }
static inline uint32_t SHR_R(uint32_t x, uint32_t s) { return s >= 32 ? 0 : x >> s; }
static inline uint32_t SAR_R(uint32_t x, uint32_t s) { return (uint32_t)((int32_t)x >> (s >= 32 ? 31 : s)); }
static inline uint32_t ROR_R(uint32_t x, uint32_t s) { return ROR32(x, s & 31); }
static inline uint32_t SHL_R_C(uint32_t x, uint32_t s, uint32_t c) { return s == 0 ? c : s <= 32 ? (x >> (32 - s)) & 1 : 0; }
static inline uint32_t SHR_R_C(uint32_t x, uint32_t s, uint32_t c) { return s == 0 ? c : s <= 32 ? (x >> (s - 1)) & 1 : 0; }
static inline uint32_t SAR_R_C(uint32_t x, uint32_t s, uint32_t c) { return s == 0 ? c : s <= 32 ? ((uint32_t)((int32_t)x >> (s - 1))) & 1 : x >> 31; }
static inline uint32_t ROR_R_C(uint32_t x, uint32_t s, uint32_t c) { return s == 0 ? c : (x >> (((s & 31) + 31) & 31)) & 1; }

static inline uint32_t RBIT32(uint32_t x) {
    x = ((x >> 1) & 0x55555555u) | ((x & 0x55555555u) << 1);
    x = ((x >> 2) & 0x33333333u) | ((x & 0x33333333u) << 2);
    x = ((x >> 4) & 0x0f0f0f0fu) | ((x & 0x0f0f0f0fu) << 4);
    return __builtin_bswap32(x);
}
static inline uint32_t SDIV32(uint32_t a, uint32_t b) {
    if (!b) return 0;
    if (a == 0x80000000u && b == 0xffffffffu) return a;
    return (uint32_t)((int32_t)a / (int32_t)b);
}

/* ---- ponto flutuante ----------------------------------------------------- */
static inline uint32_t fcmp_(double a, double b) {
    if (a != a || b != b) return 0x3;        /* nao ordenado: C V */
    if (a == b) return 0x6;                  /* Z C */
    if (a < b) return 0x8;                   /* N */
    return 0x2;                              /* C */
}
#define FCMP(a, b) fcmp_((double)(a), (double)(b))

static inline int32_t cvt_s32_f(double x) {
    if (x != x) return 0;
    if (x >= 2147483648.0) return 0x7fffffff;
    if (x <= -2147483649.0) return (int32_t)0x80000000;
    return (int32_t)x;
}
static inline uint32_t cvt_u32_f(double x) {
    if (x != x || x <= -1.0) return 0;
    if (x >= 4294967296.0) return 0xffffffffu;
    return (uint32_t)x;
}
static inline int32_t cvt_s16_f(double x) {
    if (x != x) return 0;
    if (x >= 32767.0) return 32767;
    if (x <= -32768.0) return -32768;
    return (int32_t)x;
}
static inline uint32_t cvt_u16_f(double x) {
    if (x != x || x <= -1.0) return 0;
    if (x >= 65535.0) return 65535;
    return (uint32_t)x;
}
#define CVT_S16(x) cvt_s16_f((double)(x))
#define CVT_U16(x) cvt_u16_f((double)(x))
#define CVT_S32(x) cvt_s32_f((double)(x))
#define CVT_U32(x) cvt_u32_f((double)(x))
#define RINT(x) rint(x)

/* NEON usa FPSCR padrao: subnormais viram zero, NaN padrao */
static inline float FTZ(float x) {
    uint32_t u; memcpy(&u, &x, 4);
    if ((u & 0x7f800000u) == 0 && (u & 0x007fffffu)) { u &= 0x80000000u; memcpy(&x, &u, 4); }
    return x;
}
static inline float nan_padrao(void) { uint32_t u = 0x7fc00000u; float f; memcpy(&f, &u, 4); return f; }
static inline float FMIN_NEON(float a, float b) {
    a = FTZ(a); b = FTZ(b);
    if (a != a || b != b) return nan_padrao();
    if (a == 0 && b == 0) { uint32_t x, y; memcpy(&x, &a, 4); memcpy(&y, &b, 4); x |= y; memcpy(&a, &x, 4); return a; }
    return a < b ? a : b;
}
static inline float FMAX_NEON(float a, float b) {
    a = FTZ(a); b = FTZ(b);
    if (a != a || b != b) return nan_padrao();
    if (a == 0 && b == 0) { uint32_t x, y; memcpy(&x, &a, 4); memcpy(&y, &b, 4); x &= y; memcpy(&a, &x, 4); return a; }
    return a > b ? a : b;
}

/* FPRecipEstimate / FPRSqrtEstimate do manual da ARM (precisao de 8 bits) */
static inline float f_de_u(uint32_t u) { float f; memcpy(&f, &u, 4); return f; }
static inline uint32_t u_de_f(float f) { uint32_t u; memcpy(&u, &f, 4); return u; }
static inline uint32_t recip_estimate_(uint32_t a) {     /* a em [256,511] */
    uint32_t aa = a * 2 + 1;
    uint32_t b = (1u << 19) / aa;
    return (b + 1) / 2;                                   /* [256,511] */
}
static inline float RECPE(float x) {
    x = FTZ(x);
    uint32_t u = u_de_f(x), s = u & 0x80000000u;
    int e = (u >> 23) & 0xff;
    if (x != x) return nan_padrao();
    if (e == 0) return f_de_u(s | 0x7f800000u);          /* zero -> infinito */
    if (e == 0xff) return f_de_u(s);                      /* infinito -> zero */
    if (e >= 253) return f_de_u(s);                       /* resultado subnormal -> zero */
    uint32_t sc = ((u >> 15) & 0xff) | 0x100;            /* 1.xxxxxxxx em [256,511] */
    uint32_t est = recip_estimate_(sc);
    int re = 253 - e;
    return f_de_u(s | ((uint32_t)re << 23) | ((est & 0xff) << 15));
}
static inline float RECPS(float a, float b) {
    a = FTZ(a); b = FTZ(b);
    if ((isinf(a) && b == 0) || (a == 0 && isinf(b))) return 2.0f;
    return FTZ(2.0f - a * b);
}
static inline uint32_t rsqrt_estimate_(uint32_t a) {   /* a em [128,511] */
    uint32_t aa, b = 512;
    if (a < 256) aa = a * 2 + 1; else { a = (a >> 1) << 1; aa = (a + 1) * 2; }
    while (aa * (b + 1) * (b + 1) < (1u << 28)) b++;
    return (b + 1) / 2;
}
static inline float RSQRTE(float x) {
    x = FTZ(x);
    uint32_t u = u_de_f(x);
    int e = (u >> 23) & 0xff;
    if (x != x || (u >> 31 && x != 0)) return nan_padrao();
    if (x == 0) return f_de_u((u & 0x80000000u) | 0x7f800000u);
    if (e == 0xff) return 0.0f;
    /* expoente par: '1':fracao<22:15> (256..511); impar: '01':fracao<22:16> (128..255)
     * (corrigido no BL2: a paridade estava invertida; o MGS2 nao usa vrsqrte) */
    uint32_t sc = (e & 1) ? (((u >> 16) & 0x7f) | 0x80) : (((u >> 15) & 0xff) | 0x100);
    uint32_t est = rsqrt_estimate_(sc);
    int re = (380 - e) / 2;
    return f_de_u(((uint32_t)re << 23) | ((est & 0xff) << 15));
}
static inline float RSQRTS(float a, float b) {
    a = FTZ(a); b = FTZ(b);
    if ((isinf(a) && b == 0) || (a == 0 && isinf(b))) return 1.5f;
    return FTZ((3.0f - a * b) / 2.0f);
}

/* vshl por registrador: s > 0 esquerda, s < 0 direita */
#define VSHL_DEF(T, NOME, BITS) \
    static inline T NOME(T x, int8_t s) { \
        if (s >= BITS) return 0; if (s >= 0) return (T)(x << s); \
        if (s <= -BITS) return (T)(x < 0 ? -1 : 0) & (T)(((T)-1 < 0) ? -1 : 0); return (T)(x >> -s); }
VSHL_DEF(uint8_t, VSHL_U8, 8)
VSHL_DEF(uint16_t, VSHL_U16, 16)
VSHL_DEF(uint32_t, VSHL_U32, 32)
VSHL_DEF(uint64_t, VSHL_U64, 64)
VSHL_DEF(int8_t, VSHL_S8, 8)
VSHL_DEF(int16_t, VSHL_S16, 16)
VSHL_DEF(int32_t, VSHL_S32, 32)
VSHL_DEF(int64_t, VSHL_S64, 64)
