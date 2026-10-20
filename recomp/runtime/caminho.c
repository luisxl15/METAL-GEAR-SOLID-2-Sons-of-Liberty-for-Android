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

static int existe(const char *p) { struct stat st; return lstat(p, &st) == 0; }

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
                DIR *d = opendir(lo ? out : "/");
                out[lo] = '/';
                if (d) {
                    struct dirent *e;
                    while ((e = readdir(d)))
                        if (!strcasecmp(e->d_name, comp) && strlen(e->d_name) == lc) {
                            memcpy(out + lo + 1, e->d_name, lc + 1); achou = 1; break;
                        }
                    closedir(d);
                }
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
