/* Despacho de chamadas indiretas, pontes criadas em execucao, CPU por thread
 * e chamadas do hospedeiro para dentro do jogo. */
#include "runtime.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ---- pontes dinamicas --------------------------------------------------- */
#define MAX_PONTES 8192
static Ponte pontes[MAX_PONTES];
static const char *nomes_pontes[MAX_PONTES];
static uint32_t n_pontes;
static Trava trava_pontes;
static int pontes_ok;

uint32_t ponte_nova(Ponte fn, const char *nome) {
    if (!pontes_ok) { trava_inicia(&trava_pontes); pontes_ok = 1; }
    trava(&trava_pontes);
    for (uint32_t k = 0; k < n_pontes; k++)
        if (pontes[k] == fn) { destrava(&trava_pontes); return PONTES_BASE + 8 * k; }
    if (n_pontes >= MAX_PONTES) rt_fatal("pontes esgotadas");
    uint32_t k = n_pontes++;
    pontes[k] = fn;
    nomes_pontes[k] = nome;
    destrava(&trava_pontes);
    return PONTES_BASE + 8 * k;
}

Ponte ponte_de(uint32_t ad) {
    if (ad >= PONTES_BASE && ad < PONTES_BASE + 8 * MAX_PONTES) {
        uint32_t k = (ad - PONTES_BASE) / 8;
        if (k < n_pontes) return pontes[k];
    }
    return NULL;
}

/* ---- tabela estatica ---------------------------------------------------- */
/* Toda chamada indireta (metodo virtual, ponteiro de funcao, tabela de despacho
 * da camada D3D) passa por aqui. A busca binaria em 25 mil funcoes custa ~15
 * comparacoes com faltas de cache; na frente dela fica um cache direto de 64 mil
 * entradas, cada uma um uint64 {indice << 32 | endereco} lido e escrito de forma
 * atomica (sem trava e sem par rasgado entre threads). */
#define CACHE_BITS 16
static uint64_t cache_desp[1u << CACHE_BITS];

static uint32_t busca(uint32_t ad) {
    uint32_t lo = 0, hi = g_n_despacho;
    while (lo < hi) {
        uint32_t m = (lo + hi) / 2;
        if (g_despacho[m].ad < ad) lo = m + 1;
        else hi = m;
    }
    return (lo < g_n_despacho && g_despacho[lo].ad == ad) ? lo : 0xffffffffu;
}

static inline FuncJogo procura(uint32_t ad) {
    uint32_t h = ((ad >> 1) ^ (ad >> (1 + CACHE_BITS))) & ((1u << CACHE_BITS) - 1);
    uint64_t v = __atomic_load_n(&cache_desp[h], __ATOMIC_RELAXED);
    if ((uint32_t)v == ad && ad) return g_despacho[v >> 32].fn;
    uint32_t i = busca(ad);
    if (i == 0xffffffffu) return NULL;
    __atomic_store_n(&cache_desp[h], ((uint64_t)i << 32) | ad, __ATOMIC_RELAXED);
    return g_despacho[i].fn;
}

const char *nome_de_endereco(uint32_t ad) {
    static __thread char buf[64];
    ad &= ~1u;
    for (uint32_t k = 0; k < g_n_importacoes; k++)
        if (g_importacoes[k].ad == ad) return g_importacoes[k].nome;
    Ponte p = ponte_de(ad);
    if (p) return nomes_pontes[(ad - PONTES_BASE) / 8];
    snprintf(buf, sizeof buf, "%08x", ad);
    return buf;
}

/* diagnostico: a ultima ponte dinamica chamada por esta thread (o SIGSEGV a registra) */
__thread uint32_t t_ultima_ponte, t_ultima_lr;
const char *rt_nome_ponte(uint32_t ad) { Ponte p = ponte_de(ad); return p ? nomes_pontes[(ad - PONTES_BASE) / 8] : "?"; }

void despacha(CPU *c, uint32_t alvo) {
    uint32_t ad = alvo & ~1u;
    FuncJogo f = procura(ad);
    if (f) { f(c); return; }
    Ponte p = ponte_de(ad);
    if (p) { t_ultima_ponte = ad; t_ultima_lr = c->r[14]; p(c); return; }
    rt_fatal("despacho para endereco sem funcao: %08x (lr=%08x sp=%08x)", alvo, c->r[14], c->r[13]);
}

void falha_tabela(uint32_t onde, uint32_t i) {
    rt_fatal("tabela de salto em %08x com indice fora: %u", onde, i);
}
void nao_suportado(CPU *c, uint32_t onde) {
    rt_fatal("instrucao nao suportada em %08x (lr=%08x)", onde, c->r[14]);
}
void armadilha(CPU *c, uint32_t onde) {
    rt_fatal("udf/svc em %08x (lr=%08x)", onde, c->r[14]);
}

/* ---- CPU por thread ----------------------------------------------------- */
static __thread CPU *t_cpu;

CPU *cpu_atual(void) {
    if (t_cpu) return t_cpu;
    CPU *c = calloc(1, sizeof(CPU));
    c->pilha_tam = PILHA_PADRAO;
    c->pilha_base = heap_memalign(16, c->pilha_tam);
    if (!c->pilha_base) rt_fatal("sem memoria para a pilha do jogo");
    c->r[13] = c->pilha_base + c->pilha_tam - 64;
    t_cpu = c;
    return c;
}

void cpu_define_atual(CPU *c) { t_cpu = c; }

void cpu_libera_thread(void) {
    if (!t_cpu) return;
    heap_free(t_cpu->pilha_base);
    free(t_cpu);
    t_cpu = NULL;
}

/* endereco de retorno "magico": a funcao chamada volta por 'goto sai' e o
 * desvio indireto para lr0 conta como retorno, entao nunca e executado */
#define RETORNO_HOSPEDEIRO 0xfffffff0u

uint32_t jogo_chama_v(CPU *c, uint32_t fn, int n, const uint32_t *args) {
    uint32_t salvo[16];
    memcpy(salvo, c->r, sizeof salvo);
    uint32_t sp = c->r[13];
    int na_pilha = n > 4 ? n - 4 : 0;
    sp -= 4 * (uint32_t)na_pilha;
    sp &= ~7u;
    for (int k = 0; k < na_pilha; k++) memcpy(g_mem + sp + 4 * k, &args[4 + k], 4);
    for (int k = 0; k < n && k < 4; k++) c->r[k] = args[k];
    c->r[13] = sp;
    c->r[14] = RETORNO_HOSPEDEIRO;
    despacha(c, fn);
    uint32_t r0 = c->r[0], r1 = c->r[1];
    /* preserva o contexto de quem chamou (callee-saved e pilha) */
    memcpy(c->r, salvo, sizeof salvo);
    c->r[0] = r0; c->r[1] = r1;
    return r0;
}

uint32_t jogo_chama(uint32_t fn, int n, ...) {
    uint32_t args[12];
    va_list ap;
    va_start(ap, n);
    for (int k = 0; k < n && k < 12; k++) args[k] = va_arg(ap, uint32_t);
    va_end(ap);
    return jogo_chama_v(cpu_atual(), fn, n, args);
}

uint32_t guest_strdup(const char *s) {
    if (!s) return 0;
    size_t n = strlen(s) + 1;
    uint32_t p = heap_malloc((uint32_t)n);
    if (p) memcpy(g_mem + p, s, n);
    return p;
}
