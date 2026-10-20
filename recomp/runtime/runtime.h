/* Runtime do MGS2 recompilado: interface comum entre os modulos. */
#pragma once
#include "cpu.h"
#include "tabela.h"
#include <stddef.h>
#include <stdarg.h>

/* ---- log ---------------------------------------------------------------- */
void rt_log(const char *fmt, ...);
void rt_fatal(const char *fmt, ...) __attribute__((noreturn));
/* primeira chamada de cada importacao vai para o log (mostra a sequencia do jogo) */
#ifdef MGS2_DEPURA
#define RT_PRIMEIRA(nome) do { static int _v; if (!__atomic_exchange_n(&_v, 1, __ATOMIC_RELAXED)) rt_log("imp %s", nome); } while (0)
#else
#define RT_PRIMEIRA(nome) ((void)0)
#endif

/* ---- travas do hospedeiro ----------------------------------------------- */
#ifdef _WIN32
#include <windows.h>
typedef CRITICAL_SECTION Trava;
static inline void trava_inicia(Trava *t) { InitializeCriticalSection(t); }
static inline void trava(Trava *t) { EnterCriticalSection(t); }
static inline void destrava(Trava *t) { LeaveCriticalSection(t); }
#else
#include <pthread.h>
typedef pthread_mutex_t Trava;
static inline void trava_inicia(Trava *t) {
    pthread_mutexattr_t a; pthread_mutexattr_init(&a);
    pthread_mutexattr_settype(&a, PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(t, &a);
}
static inline void trava(Trava *t) { pthread_mutex_lock(t); }
static inline void destrava(Trava *t) { pthread_mutex_unlock(t); }
#endif

/* ---- memoria ------------------------------------------------------------ */
void mem_inicia(void);
void heap_inicia(void);
uint32_t heap_malloc(uint32_t n);
void heap_free(uint32_t p);
uint32_t heap_realloc(uint32_t p, uint32_t n);
uint32_t heap_calloc(uint32_t a, uint32_t b);
uint32_t heap_memalign(uint32_t al, uint32_t n);
uint32_t heap_tamanho(uint32_t p);
uint32_t heap_topo_atual(void);

/* ponteiros: jogo (32 bits) <-> hospedeiro */
static inline void *G2H(uint32_t a) { return a ? (void *)(g_mem + a) : NULL; }
static inline uint32_t H2G(const void *p) {
    if (!p) return 0;
    ptrdiff_t d = (const uint8_t *)p - g_mem;
    if (d <= 0 || d >= (ptrdiff_t)0x100000000ll) rt_fatal("ponteiro do hospedeiro %p fora da memoria do jogo", p);
    return (uint32_t)d;
}
/* copia uma cadeia do hospedeiro para memoria nova do jogo */
uint32_t guest_strdup(const char *s);

/* ---- CPU por thread e chamadas hospedeiro -> jogo ------------------------ */
CPU *cpu_atual(void);                    /* cria na primeira vez (thread nova) */
void cpu_libera_thread(void);
#define PILHA_PADRAO (1u << 20)
/* chama a funcao do jogo em 'fn' com ate 8 argumentos de 32 bits (AAPCS:
 * r0-r3 e o resto na pilha); devolve r0.  r1 fica em c->r[1]. */
uint32_t jogo_chama(uint32_t fn, int n, ...);
uint32_t jogo_chama_v(CPU *c, uint32_t fn, int n, const uint32_t *args);

/* ---- argumentos das pontes (AAPCS softfp) ------------------------------- */
typedef struct { CPU *c; int ncrn; uint32_t nsaa; } Args;
static inline Args args_de(CPU *c) { Args a = { c, 0, c->r[13] }; return a; }
static inline uint32_t arg32(Args *a) {
    if (a->ncrn < 4) return a->c->r[a->ncrn++];
    uint32_t v; memcpy(&v, g_mem + a->nsaa, 4); a->nsaa += 4; return v;
}
static inline uint64_t arg64(Args *a) {
    if (a->ncrn & 1) a->ncrn++;
    if (a->ncrn < 4) { uint64_t v = a->c->r[a->ncrn] | (uint64_t)a->c->r[a->ncrn + 1] << 32; a->ncrn += 2; return v; }
    a->ncrn = 4;
    a->nsaa = (a->nsaa + 7) & ~7u;
    uint64_t v; memcpy(&v, g_mem + a->nsaa, 8); a->nsaa += 8; return v;
}
static inline float argf(Args *a) { uint32_t u = arg32(a); float f; memcpy(&f, &u, 4); return f; }
static inline double argd(Args *a) { uint64_t u = arg64(a); double d; memcpy(&d, &u, 8); return d; }
static inline void ret32(CPU *c, uint32_t v) { c->r[0] = v; }
static inline void ret64(CPU *c, uint64_t v) { c->r[0] = (uint32_t)v; c->r[1] = (uint32_t)(v >> 32); }
static inline void retf(CPU *c, float f) { uint32_t u; memcpy(&u, &f, 4); c->r[0] = u; }
static inline void retd(CPU *c, double d) { uint64_t u; memcpy(&u, &d, 8); ret64(c, u); }

/* ---- pontes criadas em execucao (ponteiros de funcao do hospedeiro que o
 *      jogo recebe: eglGetProcAddress, tabela JNI, interfaces OpenSL) ------ */
typedef void (*Ponte)(CPU *c);
uint32_t ponte_nova(Ponte fn, const char *nome);   /* endereco falso do jogo */
Ponte ponte_de(uint32_t ad);
const char *nome_de_endereco(uint32_t ad);

/* ---- inicializacao ------------------------------------------------------ */
void rt_inicia(void);                    /* memoria, heap, imagens, dados importados, construtores */
uint32_t rt_exportado(const char *nome); /* endereco de funcao exportada do jogo */
