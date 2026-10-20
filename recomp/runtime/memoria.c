/* Memoria do jogo: 4 GB reservados, enderecos de 32 bits = deslocamento.
 * O heap do jogo (malloc/free/realloc/memalign) e um TLSF sobre a faixa
 * HEAP_INI..HEAP_FIM: O(1), coalesce vizinhos, nunca devolve ao sistema. */
#include "runtime.h"
#include <stdio.h>
#include <stdlib.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <sys/mman.h>
#endif

uint8_t *g_mem;

void mem_inicia(void) {
#ifdef _WIN32
    g_mem = VirtualAlloc(NULL, 1ull << 32, MEM_RESERVE, PAGE_NOACCESS);
    /* no Windows o teste compromete so o que usa: imagens agora, heap conforme cresce */
    if (!VirtualAlloc(g_mem + 0x00f00000u, HEAP_INI - 0x00f00000u, MEM_COMMIT, PAGE_READWRITE)) { rt_log("commit falhou"); abort(); }
#else
    /* reserva sem compromisso: so ocupa RAM o que for tocado */
    g_mem = mmap(NULL, 1ull << 32, PROT_NONE, MAP_PRIVATE | MAP_ANONYMOUS | MAP_NORESERVE, -1, 0);
    if (g_mem == MAP_FAILED) { rt_log("mmap de 4 GB falhou"); abort(); }
    /* 0..64K fica inacessivel: ponteiro nulo do jogo cai ali e vira SIGSEGV */
    if (mprotect(g_mem + 0x10000, (1ull << 32) - 0x20000, PROT_READ | PROT_WRITE)) {
        rt_log("mprotect falhou"); abort();
    }
#endif
    rt_log("memoria do jogo em %p", (void *)g_mem);
}

/* ------------------------------------------------------------------------ */
/* TLSF: blocos com cabecalho de 8 bytes (tamanho|livre|anterior_livre e o
 * endereco do bloco fisico anterior).  Enderecos sao do jogo (uint32_t). */
#define FL_MAX 30
#define SL_LOG 5
#define SL_N (1 << SL_LOG)
#define ALINHA 16u
#define MIN_BLOCO 32u

#define B_LIVRE 1u
#define B_ANT_LIVRE 2u

typedef struct {           /* no inicio de cada bloco, na memoria do jogo */
    uint32_t anterior;      /* bloco fisico anterior (valido se B_ANT_LIVRE) */
    uint32_t tam;           /* tamanho do bloco inteiro | bandeiras */
    uint32_t prox_livre, ant_livre;  /* so em blocos livres */
} Bloco;

static uint32_t fl_bits;
static uint32_t sl_bits[FL_MAX];
static uint32_t cabecas[FL_MAX][SL_N];
static uint32_t heap_topo, heap_fim;
static Trava trava_heap;

#define BL(a) ((Bloco *)(g_mem + (a)))
static inline uint32_t tam_de(uint32_t b) { return BL(b)->tam & ~3u; }

static void mapeia(uint32_t tam, int *fl, int *sl) {
    if (tam < (1u << (SL_LOG + 4))) { *fl = 0; *sl = (int)(tam >> 4) & (SL_N - 1); return; }
    int f = 31 - __builtin_clz(tam);
    *sl = (int)((tam >> (f - SL_LOG)) ^ SL_N);
    *fl = f - (SL_LOG + 4) + 1;
}

static void insere(uint32_t b) {
    int fl, sl;
    mapeia(tam_de(b), &fl, &sl);
    uint32_t cab = cabecas[fl][sl];
    BL(b)->prox_livre = cab;
    BL(b)->ant_livre = 0;
    if (cab) BL(cab)->ant_livre = b;
    cabecas[fl][sl] = b;
    fl_bits |= 1u << fl;
    sl_bits[fl] |= 1u << sl;
}

static void remove_livre(uint32_t b) {
    int fl, sl;
    mapeia(tam_de(b), &fl, &sl);
    uint32_t p = BL(b)->prox_livre, a = BL(b)->ant_livre;
    if (p) BL(p)->ant_livre = a;
    if (a) BL(a)->prox_livre = p;
    else {
        cabecas[fl][sl] = p;
        if (!p) {
            sl_bits[fl] &= ~(1u << sl);
            if (!sl_bits[fl]) fl_bits &= ~(1u << fl);
        }
    }
}

static uint32_t procura(uint32_t tam) {
    int fl, sl;
    /* arredonda para cima para cair numa lista onde todos servem */
    if (tam >= (1u << (SL_LOG + 4))) tam += (1u << (31 - __builtin_clz(tam) - SL_LOG)) - 1;
    mapeia(tam, &fl, &sl);
    if (fl >= FL_MAX) return 0;
    uint32_t m = sl_bits[fl] & (~0u << sl);
    if (!m) {
        uint32_t f = fl_bits & (~0u << (fl + 1));
        if (!f) return 0;
        fl = __builtin_ctz(f);
        m = sl_bits[fl];
    }
    sl = __builtin_ctz(m);
    return cabecas[fl][sl];
}

static uint32_t seguinte(uint32_t b) { return b + tam_de(b); }

static void marca_livre(uint32_t b) {
    BL(b)->tam |= B_LIVRE;
    uint32_t s = seguinte(b);
    if (s < heap_topo) { BL(s)->tam |= B_ANT_LIVRE; BL(s)->anterior = b; }
}

static void marca_usado(uint32_t b) {
    BL(b)->tam &= ~B_LIVRE;
    uint32_t s = seguinte(b);
    if (s < heap_topo) BL(s)->tam &= ~B_ANT_LIVRE;
}

/* corta b em (tam) + resto livre, se sobrar o bastante */
static void corta(uint32_t b, uint32_t tam) {
    uint32_t total = tam_de(b);
    if (total - tam < MIN_BLOCO) return;
    uint32_t r = b + tam;
    BL(b)->tam = tam | (BL(b)->tam & 3u);
    BL(r)->tam = (total - tam) | B_LIVRE;
    BL(r)->anterior = b;
    uint32_t s = seguinte(r);
    if (s < heap_topo) { BL(s)->tam |= B_ANT_LIVRE; BL(s)->anterior = r; }
    insere(r);
}

#ifdef _WIN32
static uint32_t comprometido = HEAP_INI;
void mem_compromete(uint32_t ini, uint32_t tam) {
    if (!VirtualAlloc(g_mem + ini, tam, MEM_COMMIT, PAGE_READWRITE)) rt_fatal("commit de %08x+%x falhou", ini, tam);
}
#endif
static uint32_t cresce(uint32_t tam) {
    if (heap_fim - heap_topo < tam) return 0;
    uint32_t b = heap_topo;
    heap_topo += tam;
#ifdef _WIN32
    if (heap_topo > comprometido) {
        uint32_t novo = (heap_topo + 0xffffffu) & ~0xffffffu;   /* de 16 em 16 MB */
        mem_compromete(comprometido, novo - comprometido);
        comprometido = novo;
    }
#endif
    BL(b)->tam = tam;
    return b;
}

void heap_inicia(void) {
    trava_inicia(&trava_heap);
    heap_topo = HEAP_INI;
    heap_fim = HEAP_FIM;
}

static uint32_t aloca_bloco(uint32_t n) {
    uint32_t tam = (n + 8 + ALINHA - 1) & ~(ALINHA - 1);
    if (tam < MIN_BLOCO) tam = MIN_BLOCO;
    if (n > 0xe0000000u) return 0;
    uint32_t b = procura(tam);
    if (b) {
        remove_livre(b);
        marca_usado(b);
        corta(b, tam);
    } else {
        b = cresce(tam);
        if (!b) return 0;
    }
    return b;
}

/* o ponteiro do usuario fica 8 bytes depois do cabecalho: alinhado a 8 como
 * o malloc do bionic de 32 bits; com ALINHA 16 e cabecalho 8 o usuario fica
 * em 16k+8.  memalign trata alinhamentos maiores. */
uint32_t heap_malloc(uint32_t n) {
    trava(&trava_heap);
    uint32_t b = aloca_bloco(n);
    destrava(&trava_heap);
    return b ? b + 8 : 0;
}

void heap_free(uint32_t p) {
    if (!p) return;
    trava(&trava_heap);
    uint32_t b = p - 8;
    if (BL(b)->tam & B_LIVRE) { destrava(&trava_heap); rt_log("free duplo em %08x", p); return; }
    /* junta com o seguinte */
    uint32_t s = seguinte(b);
    if (s < heap_topo && (BL(s)->tam & B_LIVRE)) {
        remove_livre(s);
        BL(b)->tam = (tam_de(b) + tam_de(s)) | (BL(b)->tam & 3u);
    }
    /* junta com o anterior */
    if (BL(b)->tam & B_ANT_LIVRE) {
        uint32_t a = BL(b)->anterior;
        remove_livre(a);
        BL(a)->tam = (tam_de(a) + tam_de(b)) | (BL(a)->tam & 3u);
        b = a;
    }
    if (seguinte(b) == heap_topo) {
        /* devolve ao topo */
        heap_topo = b;
        if (b > HEAP_INI) { /* o anterior continua valido */ }
    } else {
        marca_livre(b);
        insere(b);
    }
    destrava(&trava_heap);
}

uint32_t heap_tamanho(uint32_t p) { return p ? tam_de(p - 8) - 8 : 0; }

uint32_t heap_realloc(uint32_t p, uint32_t n) {
    if (!p) return heap_malloc(n);
    if (!n) { heap_free(p); return 0; }
    uint32_t velho = heap_tamanho(p);
    if (n <= velho) return p;
    uint32_t q = heap_malloc(n);
    if (!q) return 0;
    memcpy(g_mem + q, g_mem + p, velho);
    heap_free(p);
    return q;
}

uint32_t heap_calloc(uint32_t a, uint32_t b) {
    uint64_t n = (uint64_t)a * b;
    if (n > 0xe0000000u) return 0;
    uint32_t p = heap_malloc((uint32_t)n);
    if (p) memset(g_mem + p, 0, (size_t)n);
    return p;
}

uint32_t heap_memalign(uint32_t al, uint32_t n) {
    if (al <= 8) return heap_malloc(n);
    /* pede folga, e o pedaco antes do alinhamento vira um bloco livre */
    trava(&trava_heap);
    uint32_t b = aloca_bloco(n + al + MIN_BLOCO);
    if (!b) { destrava(&trava_heap); return 0; }
    uint32_t u = ((b + 8 + MIN_BLOCO + al - 1) & ~(al - 1));
    uint32_t nb = u - 8;
    uint32_t total = tam_de(b);
    uint32_t antes = nb - b;
    /* o bloco novo comeca em nb; o pedaco [b, nb) fica livre */
    BL(nb)->tam = (total - antes);
    BL(nb)->anterior = b;
    BL(b)->tam = antes | (BL(b)->tam & B_ANT_LIVRE);
    marca_livre(b);
    BL(nb)->tam |= B_ANT_LIVRE;
    insere(b);
    destrava(&trava_heap);
    return u;
}

/* estatistica para o painel */
uint32_t heap_topo_atual(void) { return heap_topo - HEAP_INI; }
