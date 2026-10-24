/* Caminhos do jogo sem diferenciar maiusculas de minusculas.
 *
 * O MGS2 foi feito para o SHIELD, cujo armazenamento nao diferencia maiusculas: ele pede
 * "$/enginesupport/fonts/console.cfon" e o arquivo extraido da OBB e
 * "EngineSupport/Fonts/console.cfon". No S25+ o /sdcard tambem nao diferencia e funciona;
 * no Redmi 13C (Helio G85, Android 15) diferencia, e o fopen devolvia NULL -> o jogo usava o
 * ponteiro nulo e caia (SIGSEGV no endereco 0 da memoria do jogo).
 *
 * rt_caminho: se o caminho pedido existe, devolve ele mesmo (caso comum: um access()).
 * Senao resolve componente a componente procurando o nome no diretorio com strcasecmp;
 * o que nao existir fica como foi pedido (criar arquivo novo continua funcionando).
 * Resultados (achados e nao achados) vao para um cache, revalidado antes de usar. */
#ifndef _WIN32
#include "runtime.h"
#include <ctype.h>
#include <dirent.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/stat.h>
#include <unistd.h>

#define CACHE 4096
static struct { char *pedido, *achado; int inteiro; } cache[CACHE];
static pthread_mutex_t trava_cache = PTHREAD_MUTEX_INITIALIZER;
static unsigned n_resolvidos;

static unsigned hash(const char *s) { unsigned h = 2166136261u; while (*s) h = (h ^ (unsigned char)*s++) * 16777619u; return h; }
static unsigned hash_min(const char *s, size_t n) {
    unsigned h = 2166136261u;
    for (size_t i = 0; i < n; i++) h = (h ^ (unsigned char)tolower((unsigned char)s[i])) * 16777619u;
    return h;
}

static int existe(const char *p) { struct stat st; return lstat(p, &st) == 0; }

/* ---- listagem de pasta em cache ---------------------------------------------
 * O jogo procura cada arquivo primeiro em .../_bp/ (substituicoes da Bluepoint) e quase
 * nunca acha. Antes, cada nome diferente que faltava relia a pasta inteira pelo FUSE do
 * /sdcard: textures/flatlist/_win tem 15.246 arquivos, us/vox 2.141 (as vozes do codec),
 * dezenas de ms por busca no meio do jogo. Agora cada pasta e lida uma vez e vira uma
 * tabela (nome sem caixa -> nome real). Quando o jogo cria/renomeia/apaga algo
 * (rt_caminho_mudou: saves), as listagens ficam velhas e sao relidas so se uma busca falhar. */
typedef struct { char *cam; unsigned ger; int n; char **nomes; int *tab; unsigned mascara; } Pasta;
#define PASTAS 2048
static Pasta *pastas[PASTAS];
static unsigned ger_atual = 1;
extern volatile long long g_est[12];   /* [10]: pastas lidas (gl_manual.c) */

void rt_caminho_mudou(void) { __atomic_add_fetch(&ger_atual, 1, __ATOMIC_RELAXED); }

static void pasta_solta(Pasta *p) {
    if (!p) return;
    for (int i = 0; i < p->n; i++) free(p->nomes[i]);
    free(p->nomes); free(p->tab); free(p->cam); free(p);
}
static Pasta *pasta_le(const char *cam) {
    DIR *d = opendir(*cam ? cam : "/");
    if (!d) return NULL;
    Pasta *p = calloc(1, sizeof *p);
    p->cam = strdup(cam);
    p->ger = __atomic_load_n(&ger_atual, __ATOMIC_RELAXED);
    int cap = 64;
    p->nomes = malloc(sizeof(char *) * (size_t)cap);
    struct dirent *e;
    while ((e = readdir(d))) {
        if (p->n == cap) { cap *= 2; p->nomes = realloc(p->nomes, sizeof(char *) * (size_t)cap); }
        p->nomes[p->n++] = strdup(e->d_name);
    }
    closedir(d);
    unsigned t = 16; while (t < (unsigned)p->n * 2) t <<= 1;
    p->mascara = t - 1;
    p->tab = malloc(sizeof(int) * t);
    for (unsigned i = 0; i < t; i++) p->tab[i] = -1;
    for (int i = 0; i < p->n; i++) {
        unsigned h = hash_min(p->nomes[i], strlen(p->nomes[i])) & p->mascara;
        while (p->tab[h] >= 0) h = (h + 1) & p->mascara;
        p->tab[h] = i;
    }
    g_est[10]++;
    return p;
}
static const char *pasta_acha(const Pasta *p, const char *nome, size_t n) {
    unsigned h = hash_min(nome, n) & p->mascara;
    for (; p->tab[h] >= 0; h = (h + 1) & p->mascara) {
        const char *s = p->nomes[p->tab[h]];
        if (strlen(s) == n && !strncasecmp(s, nome, n)) return s;
    }
    return NULL;
}
/* nome real de 'comp' dentro da pasta 'cam' (sem diferenciar caixa) em out; 1 = achou */
static pthread_mutex_t trava_pastas = PTHREAD_MUTEX_INITIALIZER;
static int procura_na_pasta(const char *cam, const char *comp, size_t lc, char *out) {
    pthread_mutex_lock(&trava_pastas);
    unsigned h = hash(cam) & (PASTAS - 1), k = h;
    Pasta *p = NULL;
    for (unsigned t = 0; t < PASTAS; t++, k = (k + 1) & (PASTAS - 1)) {
        if (!pastas[k] || !strcmp(pastas[k]->cam, cam)) { p = pastas[k]; break; }
    }
    if (!p) { p = pasta_le(cam); if (p) { if (pastas[k]) pasta_solta(pastas[k]); pastas[k] = p; } }
    const char *s = p ? pasta_acha(p, comp, lc) : NULL;
    if (!s && p && p->ger != __atomic_load_n(&ger_atual, __ATOMIC_RELAXED)) {   /* velha: o jogo criou algo */
        Pasta *q = pasta_le(cam);
        if (q) { pasta_solta(p); pastas[k] = p = q; s = pasta_acha(p, comp, lc); }
    }
    if (s) memcpy(out, s, lc + 1);
    pthread_mutex_unlock(&trava_pastas);
    return s != NULL;
}

/* resolve p em out (tam n); 1 = achou o caminho inteiro (com outra caixa) */
static int resolve(const char *p, char *out, size_t n) {
    size_t lo = 0;
    out[0] = 0;
    const char *s = p;
    int inteiro = 1;
    while (*s) {
        while (*s == '/') s++;
        if (!*s) break;
        const char *fim = strchr(s, '/');
        size_t lc = fim ? (size_t)(fim - s) : strlen(s);
        char comp[256];
        if (lc >= sizeof comp || lo + lc + 2 >= n) return 0;
        memcpy(comp, s, lc); comp[lc] = 0;
        out[lo] = '/'; memcpy(out + lo + 1, comp, lc + 1);
        if (!inteiro || !existe(out)) {
            int achou = 0;
            if (inteiro) {
                out[lo] = 0;
                achou = procura_na_pasta(out, comp, lc, out + lo + 1);
                out[lo] = '/';
                if (!achou) memcpy(out + lo + 1, comp, lc + 1);
            }
            if (!achou) inteiro = 0;          /* o resto fica como foi pedido */
        }
        lo += lc + 1;
        s += lc;
    }
    if (!lo) { out[0] = '/'; out[1] = 0; }
    return inteiro;
}

const char *rt_caminho(const char *p, char *buf, size_t n) {
    if (!p || p[0] != '/' || existe(p)) return p;
    unsigned h = hash(p) & (CACHE - 1);
    char r[1024];
    int achou = -1;
    pthread_mutex_lock(&trava_cache);
    if (cache[h].pedido && !strcmp(cache[h].pedido, p) && strlen(cache[h].achado) < sizeof r) {
        strcpy(r, cache[h].achado);
        achou = cache[h].inteiro;
    }
    pthread_mutex_unlock(&trava_cache);
    if (achou == 1 && !existe(r)) achou = -1;          /* sumiu desde entao: resolve de novo */
    if (achou < 0) {
        achou = resolve(p, r, sizeof r);
        pthread_mutex_lock(&trava_cache);
        free(cache[h].pedido); free(cache[h].achado);
        cache[h].pedido = strdup(p); cache[h].achado = strdup(r); cache[h].inteiro = achou;
        if (achou && n_resolvidos++ < 20) rt_log("caminho sem diferenciar maiusculas: %s -> %s", p, r);
        pthread_mutex_unlock(&trava_cache);
    }
    /* achado: o caminho real; nao achado: os diretorios que existem com a caixa certa (criar) */
    if (strcmp(r, p) && strlen(r) < n) { strcpy(buf, r); return buf; }
    return p;
}
#endif
