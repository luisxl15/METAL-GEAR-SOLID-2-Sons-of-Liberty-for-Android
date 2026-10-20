/* pthread do jogo (bionic de 32 bits) sobre a do hospedeiro.
 *  pthread_mutex_t / pthread_cond_t / pthread_once_t: 4 bytes no jogo.
 *    Mapa endereco-do-jogo -> objeto do hospedeiro, criado no primeiro uso
 *    (respeita os inicializadores estaticos: 0 normal, 0x4000 recursivo,
 *    0x8000 verificacao de erro).
 *  pthread_attr_t: 24 bytes {flags, stack_base, stack_size, guard_size,
 *    sched_policy, sched_priority}.
 *  pthread_t: 4 bytes; aqui e um indice na tabela de threads.
 *  pthread_key_t: indice na nossa tabela de chaves (valores de 32 bits). */
#ifndef _WIN32
#define _GNU_SOURCE   /* cpu_set_t, sched_setaffinity */
#endif
#include "runtime.h"
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#ifndef _WIN32
#include <pthread.h>
#include <sched.h>
#include <time.h>
#endif

#ifdef _WIN32
/* o teste no PC so precisa de uma thread; as pontes viram quase nada */
void I_pthread_mutex_init(CPU *c) { RT_PRIMEIRA("pthread_mutex_init"); ret32(c, 0); }
void I_pthread_mutex_destroy(CPU *c) { RT_PRIMEIRA("pthread_mutex_destroy"); ret32(c, 0); }
void I_pthread_mutex_lock(CPU *c) { RT_PRIMEIRA("pthread_mutex_lock"); ret32(c, 0); }
void I_pthread_mutex_trylock(CPU *c) { RT_PRIMEIRA("pthread_mutex_trylock"); ret32(c, 0); }
void I_pthread_mutex_unlock(CPU *c) { RT_PRIMEIRA("pthread_mutex_unlock"); ret32(c, 0); }
void I_pthread_mutexattr_init(CPU *c) { RT_PRIMEIRA("pthread_mutexattr_init"); ret32(c, 0); }
void I_pthread_mutexattr_destroy(CPU *c) { RT_PRIMEIRA("pthread_mutexattr_destroy"); ret32(c, 0); }
void I_pthread_mutexattr_settype(CPU *c) { RT_PRIMEIRA("pthread_mutexattr_settype"); ret32(c, 0); }
void I_pthread_cond_init(CPU *c) { RT_PRIMEIRA("pthread_cond_init"); ret32(c, 0); }
void I_pthread_cond_destroy(CPU *c) { RT_PRIMEIRA("pthread_cond_destroy"); ret32(c, 0); }
void I_pthread_cond_signal(CPU *c) { RT_PRIMEIRA("pthread_cond_signal"); ret32(c, 0); }
void I_pthread_cond_broadcast(CPU *c) { RT_PRIMEIRA("pthread_cond_broadcast"); ret32(c, 0); }
void I_pthread_cond_wait(CPU *c) { RT_PRIMEIRA("pthread_cond_wait"); rt_fatal("pthread_cond_wait no teste do PC"); }
void I_pthread_cond_timedwait(CPU *c) { RT_PRIMEIRA("pthread_cond_timedwait"); ret32(c, 110); }
void I_pthread_create(CPU *c) { RT_PRIMEIRA("pthread_create"); rt_log("pthread_create ignorado no teste do PC (fn=%08x)", c->r[2]); uint32_t id = 2; memcpy(g_mem + c->r[0], &id, 4); ret32(c, 0); }
void I_pthread_detach(CPU *c) { RT_PRIMEIRA("pthread_detach"); ret32(c, 0); }
void I_pthread_join(CPU *c) { RT_PRIMEIRA("pthread_join"); ret32(c, 0); }
void I_pthread_exit(CPU *c) { RT_PRIMEIRA("pthread_exit"); rt_fatal("pthread_exit no teste do PC"); }
void I_pthread_equal(CPU *c) { RT_PRIMEIRA("pthread_equal"); ret32(c, c->r[0] == c->r[1]); }
void I_pthread_self(CPU *c) { RT_PRIMEIRA("pthread_self"); ret32(c, 1); }
void I_pthread_kill(CPU *c) { RT_PRIMEIRA("pthread_kill"); ret32(c, 0); }
void I_pthread_setname_np(CPU *c) { RT_PRIMEIRA("pthread_setname_np"); ret32(c, 0); }
static uint32_t chaves[256]; static uint32_t n_chaves = 1;
void I_pthread_key_create(CPU *c) { RT_PRIMEIRA("pthread_key_create"); uint32_t k = n_chaves++; memcpy(g_mem + c->r[0], &k, 4); ret32(c, 0); }
void I_pthread_key_delete(CPU *c) { RT_PRIMEIRA("pthread_key_delete"); ret32(c, 0); }
void I_pthread_getspecific(CPU *c) { RT_PRIMEIRA("pthread_getspecific"); ret32(c, chaves[c->r[0] & 255]); }
void I_pthread_setspecific(CPU *c) { RT_PRIMEIRA("pthread_setspecific"); chaves[c->r[0] & 255] = c->r[1]; ret32(c, 0); }
void I_pthread_once(CPU *c) { RT_PRIMEIRA("pthread_once"); uint32_t v; memcpy(&v, g_mem + c->r[0], 4); if (!v) { v = 1; memcpy(g_mem + c->r[0], &v, 4); jogo_chama(c->r[1], 0); } ret32(c, 0); }
void I_pthread_attr_init(CPU *c) { RT_PRIMEIRA("pthread_attr_init"); memset(g_mem + c->r[0], 0, 24); uint32_t t = 1 << 20; memcpy(g_mem + c->r[0] + 8, &t, 4); ret32(c, 0); }
void I_pthread_attr_destroy(CPU *c) { RT_PRIMEIRA("pthread_attr_destroy"); ret32(c, 0); }
void I_pthread_attr_setdetachstate(CPU *c) { RT_PRIMEIRA("pthread_attr_setdetachstate"); ret32(c, 0); }
void I_pthread_attr_setstack(CPU *c) { RT_PRIMEIRA("pthread_attr_setstack"); memcpy(g_mem + c->r[0] + 4, &c->r[1], 4); memcpy(g_mem + c->r[0] + 8, &c->r[2], 4); ret32(c, 0); }
void I_pthread_attr_getstack(CPU *c) { RT_PRIMEIRA("pthread_attr_getstack"); memcpy(g_mem + c->r[1], g_mem + c->r[0] + 4, 4); memcpy(g_mem + c->r[2], g_mem + c->r[0] + 8, 4); ret32(c, 0); }
void I_pthread_getattr_np(CPU *c) { RT_PRIMEIRA("pthread_getattr_np"); CPU *e = cpu_atual(); memset(g_mem + c->r[1], 0, 24); memcpy(g_mem + c->r[1] + 4, &e->pilha_base, 4); memcpy(g_mem + c->r[1] + 8, &e->pilha_tam, 4); ret32(c, 0); }
void I_sched_setaffinity(CPU *c) { RT_PRIMEIRA("sched_setaffinity"); ret32(c, 0); }
#else

/* ---- mapa de objetos ----------------------------------------------------- */
#define MAPA_TAM 65536
typedef struct { uint32_t g; void *h; } Par;
static Par mapa_mutex[MAPA_TAM], mapa_cond[MAPA_TAM];
static pthread_mutex_t trava_mapa = PTHREAD_MUTEX_INITIALIZER;

static inline uint32_t hsh(uint32_t g) { return (g * 2654435761u) >> 16; }

static void *procura(Par *m, uint32_t g, int cria, int eh_mutex) {
    uint32_t k = hsh(g) & (MAPA_TAM - 1);
    for (uint32_t t = 0; t < MAPA_TAM; t++, k = (k + 1) & (MAPA_TAM - 1)) {
        if (m[k].g == g) return m[k].h;
        if (!m[k].g) {
            if (!cria) return NULL;
            pthread_mutex_lock(&trava_mapa);
            if (m[k].g == g) { pthread_mutex_unlock(&trava_mapa); return m[k].h; }
            if (m[k].g) { pthread_mutex_unlock(&trava_mapa); continue; }
            void *h;
            if (eh_mutex) {
                uint32_t v; memcpy(&v, g_mem + g, 4);
                pthread_mutexattr_t a; pthread_mutexattr_init(&a);
                /* bionic: bits 14-15 do valor = tipo (1 recursivo, 2 erro) */
                int tipo = (v >> 14) & 3;
                pthread_mutexattr_settype(&a, tipo == 1 ? PTHREAD_MUTEX_RECURSIVE : tipo == 2 ? PTHREAD_MUTEX_ERRORCHECK : PTHREAD_MUTEX_NORMAL);
                h = malloc(sizeof(pthread_mutex_t));
                pthread_mutex_init(h, &a);
            } else {
                h = malloc(sizeof(pthread_cond_t));
                pthread_condattr_t ca; pthread_condattr_init(&ca);
                pthread_cond_init(h, &ca);
            }
            m[k].h = h;
            __atomic_store_n(&m[k].g, g, __ATOMIC_RELEASE);
            pthread_mutex_unlock(&trava_mapa);
            return h;
        }
    }
    rt_fatal("mapa de sincronizacao cheio");
}

static void esquece(Par *m, uint32_t g) {
    /* nao remove (quebraria a sondagem linear); so reinicializa na proxima
     * criacao: marcamos o valor do jogo e deixamos o objeto vivo */
    (void)m; (void)g;
}

static pthread_mutex_t *mtx(uint32_t g) { return procura(mapa_mutex, g, 1, 1); }
static pthread_cond_t *cnd(uint32_t g) { return procura(mapa_cond, g, 1, 0); }

/* ---- mutex --------------------------------------------------------------- */
void I_pthread_mutexattr_init(CPU *c) { RT_PRIMEIRA("pthread_mutexattr_init"); uint32_t z = 0; memcpy(g_mem + c->r[0], &z, 4); ret32(c, 0); }
void I_pthread_mutexattr_destroy(CPU *c) { RT_PRIMEIRA("pthread_mutexattr_destroy"); ret32(c, 0); }
void I_pthread_mutexattr_settype(CPU *c) { RT_PRIMEIRA("pthread_mutexattr_settype"); memcpy(g_mem + c->r[0], &c->r[1], 4); ret32(c, 0); }
void I_pthread_mutex_init(CPU *c) { RT_PRIMEIRA("pthread_mutex_init");
    uint32_t g = c->r[0], tipo = 0;
    if (c->r[1]) memcpy(&tipo, g_mem + c->r[1], 4);
    /* grava o inicializador equivalente e (re)cria o do hospedeiro */
    uint32_t v = tipo == 1 ? 0x4000 : tipo == 2 ? 0x8000 : 0;
    memcpy(g_mem + g, &v, 4);
    pthread_mutex_t *h = procura(mapa_mutex, g, 0, 1);
    if (h) {
        pthread_mutexattr_t a; pthread_mutexattr_init(&a);
        pthread_mutexattr_settype(&a, tipo == 1 ? PTHREAD_MUTEX_RECURSIVE : tipo == 2 ? PTHREAD_MUTEX_ERRORCHECK : PTHREAD_MUTEX_NORMAL);
        pthread_mutex_init(h, &a);
    } else mtx(g);
    ret32(c, 0);
}
void I_pthread_mutex_destroy(CPU *c) { RT_PRIMEIRA("pthread_mutex_destroy"); esquece(mapa_mutex, c->r[0]); ret32(c, 0); }
void I_pthread_mutex_lock(CPU *c) { RT_PRIMEIRA("pthread_mutex_lock"); ret32(c, (uint32_t)pthread_mutex_lock(mtx(c->r[0]))); }
void I_pthread_mutex_trylock(CPU *c) { RT_PRIMEIRA("pthread_mutex_trylock"); ret32(c, (uint32_t)pthread_mutex_trylock(mtx(c->r[0]))); }
void I_pthread_mutex_unlock(CPU *c) { RT_PRIMEIRA("pthread_mutex_unlock"); ret32(c, (uint32_t)pthread_mutex_unlock(mtx(c->r[0]))); }

/* ---- cond ---------------------------------------------------------------- */
void I_pthread_cond_init(CPU *c) { RT_PRIMEIRA("pthread_cond_init"); cnd(c->r[0]); ret32(c, 0); }
void I_pthread_cond_destroy(CPU *c) { RT_PRIMEIRA("pthread_cond_destroy"); ret32(c, 0); }
void I_pthread_cond_signal(CPU *c) { RT_PRIMEIRA("pthread_cond_signal"); ret32(c, (uint32_t)pthread_cond_signal(cnd(c->r[0]))); }
void I_pthread_cond_broadcast(CPU *c) { RT_PRIMEIRA("pthread_cond_broadcast"); ret32(c, (uint32_t)pthread_cond_broadcast(cnd(c->r[0]))); }
void I_pthread_cond_wait(CPU *c) { RT_PRIMEIRA("pthread_cond_wait"); ret32(c, (uint32_t)pthread_cond_wait(cnd(c->r[0]), mtx(c->r[1]))); }
void I_pthread_cond_timedwait(CPU *c) { RT_PRIMEIRA("pthread_cond_timedwait");
    int32_t v[2]; memcpy(v, g_mem + c->r[2], 8);
    struct timespec ts = { v[0], v[1] };
    ret32(c, (uint32_t)pthread_cond_timedwait(cnd(c->r[0]), mtx(c->r[1]), &ts));
}

/* ---- threads ------------------------------------------------------------- */
#define MAX_THREADS 256
typedef struct {
    pthread_t h;
    uint32_t fn, arg, pilha, tam_pilha, pilha_nossa, ret;
    int usado, destacada;
    CPU *cpu;
} Thr;
static Thr thrs[MAX_THREADS];
static __thread uint32_t t_id;

static uint32_t id_atual(void) {
    if (t_id) return t_id;
    pthread_mutex_lock(&trava_mapa);
    for (uint32_t k = 1; k < MAX_THREADS; k++) if (!thrs[k].usado) {
        thrs[k].usado = 1; thrs[k].h = pthread_self(); t_id = k; break;
    }
    pthread_mutex_unlock(&trava_mapa);
    return t_id;
}

/* chaves: valores de 32 bits por thread, com destrutor do jogo */
#define MAX_CHAVES 128
static uint32_t destrutores[MAX_CHAVES];
static int chave_usada[MAX_CHAVES];
static __thread uint32_t t_valores[MAX_CHAVES];

static void roda_destrutores(void) {
    for (int volta = 0; volta < 4; volta++) {
        int algum = 0;
        for (int k = 0; k < MAX_CHAVES; k++) {
            if (chave_usada[k] && destrutores[k] && t_valores[k]) {
                uint32_t v = t_valores[k]; t_valores[k] = 0; algum = 1;
                jogo_chama(destrutores[k], 1, v);
            }
        }
        if (!algum) break;
    }
}

void cpu_define_atual(CPU *c);
static void *corpo_thread(void *p) {
    Thr *t = p;
    t_id = (uint32_t)(t - thrs);
    CPU *c = calloc(1, sizeof(CPU));
    c->pilha_base = t->pilha; c->pilha_tam = t->tam_pilha;
    c->r[13] = (t->pilha + t->tam_pilha - 16) & ~7u;
    t->cpu = c;
    cpu_define_atual(c);
    t->ret = jogo_chama(t->fn, 1, t->arg);
    roda_destrutores();
    if (t->pilha_nossa) heap_free(t->pilha_nossa);
    cpu_define_atual(NULL);
    free(c);
    if (t->destacada) t->usado = 0;
    return NULL;
}

void I_pthread_create(CPU *c) { RT_PRIMEIRA("pthread_create");
    uint32_t pid = c->r[0], attr = c->r[1], fn = c->r[2], arg = c->r[3];
    uint32_t flags = 0, base = 0, tam = 1u << 20;
    if (attr) {
        memcpy(&flags, g_mem + attr, 4); memcpy(&base, g_mem + attr + 4, 4);
        uint32_t t; memcpy(&t, g_mem + attr + 8, 4); if (t) tam = t;
    }
    pthread_mutex_lock(&trava_mapa);
    uint32_t id = 0;
    for (uint32_t k = 1; k < MAX_THREADS; k++) if (!thrs[k].usado) { id = k; thrs[k].usado = 1; break; }
    pthread_mutex_unlock(&trava_mapa);
    if (!id) { ret32(c, EAGAIN); return; }
    Thr *t = &thrs[id];
    t->fn = fn; t->arg = arg; t->destacada = flags & 1; t->pilha_nossa = 0;
    if (base) { t->pilha = base; t->tam_pilha = tam; }
    else { t->pilha = t->pilha_nossa = heap_memalign(16, tam); t->tam_pilha = tam; }
    pthread_attr_t a; pthread_attr_init(&a);
    pthread_attr_setstacksize(&a, 8u << 20);   /* pilha do HOSPEDEIRO: o C gerado usa bastante */
    if (t->destacada) pthread_attr_setdetachstate(&a, PTHREAD_CREATE_DETACHED);
    int r = pthread_create(&t->h, &a, corpo_thread, t);
    if (r) { t->usado = 0; ret32(c, (uint32_t)r); return; }
    memcpy(g_mem + pid, &id, 4);
    ret32(c, 0);
}
void I_pthread_detach(CPU *c) { RT_PRIMEIRA("pthread_detach");
    uint32_t id = c->r[0];
    if (id < MAX_THREADS && thrs[id].usado) { thrs[id].destacada = 1; pthread_detach(thrs[id].h); }
    ret32(c, 0);
}
void I_pthread_join(CPU *c) { RT_PRIMEIRA("pthread_join");
    uint32_t id = c->r[0];
    if (id >= MAX_THREADS || !thrs[id].usado) { ret32(c, ESRCH); return; }
    int r = pthread_join(thrs[id].h, NULL);
    if (c->r[1]) memcpy(g_mem + c->r[1], &thrs[id].ret, 4);
    thrs[id].usado = 0;
    ret32(c, (uint32_t)r);
}
void I_pthread_exit(CPU *c) { RT_PRIMEIRA("pthread_exit");
    roda_destrutores();
    uint32_t id = id_atual();
    thrs[id].ret = c->r[0];
    pthread_exit(NULL);
}
void I_pthread_equal(CPU *c) { RT_PRIMEIRA("pthread_equal"); ret32(c, c->r[0] == c->r[1]); }
void I_pthread_self(CPU *c) { RT_PRIMEIRA("pthread_self"); ret32(c, id_atual()); }
void I_pthread_kill(CPU *c) { RT_PRIMEIRA("pthread_kill");
    uint32_t id = c->r[0];
    if (id >= MAX_THREADS || !thrs[id].usado) { ret32(c, ESRCH); return; }
    ret32(c, c->r[1] == 0 ? 0 : (uint32_t)pthread_kill(thrs[id].h, (int)c->r[1]));
}
/* Nucleos rapidos: os de maior frequencia maxima (>= 85% da maior; pelo menos 2).
 * No MediaTek (1+3+4, 4+4) uma thread pesada num nucleo de eficiencia corta o
 * desempenho pela metade; o agendador do Android nem sempre move a tempo. */
#include <stdio.h>
#include <sys/resource.h>
static cpu_set_t nucleos_rapidos(int *quantos) {
    long freq[32] = {0}, maior = 0;
    int n = 0;
    for (int k = 0; k < 32; k++) {
        char cam[96]; snprintf(cam, sizeof cam, "/sys/devices/system/cpu/cpu%d/cpufreq/cpuinfo_max_freq", k);
        FILE *f = fopen(cam, "r");
        if (!f) continue;
        if (fscanf(f, "%ld", &freq[k]) == 1 && freq[k] > maior) maior = freq[k];
        fclose(f);
    }
    cpu_set_t m; CPU_ZERO(&m);
    for (int lim = 85; lim >= 50 && n < 2; lim -= 15) {
        CPU_ZERO(&m); n = 0;
        for (int k = 0; k < 32; k++) if (freq[k] && freq[k] * 100 >= maior * lim) { CPU_SET(k, &m); n++; }
    }
    *quantos = n;
    return m;
}
static void thread_pesada(pthread_t h, const char *nome) {
    static cpu_set_t rapidos; static int n_rapidos = -1;
    if (n_rapidos < 0) {
        rapidos = nucleos_rapidos(&n_rapidos);
        rt_log("nucleos rapidos: %d (afinidade das threads MainGame e D3DGL MTD3D)", n_rapidos);
    }
    pid_t tid = pthread_gettid_np(h);
    if (n_rapidos >= 2) sched_setaffinity(tid, sizeof rapidos, &rapidos);
    setpriority(PRIO_PROCESS, (id_t)tid, -4);   /* um pouco acima do normal (o Android permite) */
    (void)nome;
}

void I_pthread_setname_np(CPU *c) { RT_PRIMEIRA("pthread_setname_np");
    uint32_t id = c->r[0];
    if (id < MAX_THREADS && thrs[id].usado) {
        const char *nome = G2H(c->r[1]);
        pthread_setname_np(thrs[id].h, nome);
        if (!strcmp(nome, "MainGame") || !strcmp(nome, "D3DGL MTD3D")) thread_pesada(thrs[id].h, nome);
    }
    ret32(c, 0);
}

void I_pthread_key_create(CPU *c) { RT_PRIMEIRA("pthread_key_create");
    pthread_mutex_lock(&trava_mapa);
    for (uint32_t k = 1; k < MAX_CHAVES; k++) if (!chave_usada[k]) {
        chave_usada[k] = 1; destrutores[k] = c->r[1];
        pthread_mutex_unlock(&trava_mapa);
        memcpy(g_mem + c->r[0], &k, 4); ret32(c, 0); return;
    }
    pthread_mutex_unlock(&trava_mapa);
    ret32(c, EAGAIN);
}
void I_pthread_key_delete(CPU *c) { RT_PRIMEIRA("pthread_key_delete"); if (c->r[0] < MAX_CHAVES) chave_usada[c->r[0]] = 0; ret32(c, 0); }
void I_pthread_getspecific(CPU *c) { RT_PRIMEIRA("pthread_getspecific"); ret32(c, c->r[0] < MAX_CHAVES ? t_valores[c->r[0]] : 0); }
void I_pthread_setspecific(CPU *c) { RT_PRIMEIRA("pthread_setspecific"); if (c->r[0] < MAX_CHAVES) t_valores[c->r[0]] = c->r[1]; ret32(c, 0); }

/* Estado por variavel, como a bionic (0 = nao, 1 = rodando, 2 = feito).
 * Uma trava global aqui trava sozinha: a rotina de um once da gnustl chama
 * outro once (inicializacao do locale) na mesma thread. */
void I_pthread_once(CPU *c) { RT_PRIMEIRA("pthread_once");
    uint32_t *v = (uint32_t *)(g_mem + c->r[0]);
    uint32_t zero = 0;
    if (__atomic_compare_exchange_n(v, &zero, 1, 0, __ATOMIC_ACQ_REL, __ATOMIC_ACQUIRE)) {
        jogo_chama(c->r[1], 0);
        __atomic_store_n(v, 2, __ATOMIC_RELEASE);
    } else {
        while (__atomic_load_n(v, __ATOMIC_ACQUIRE) != 2) sched_yield();
    }
    ret32(c, 0);
}

void I_pthread_attr_init(CPU *c) { RT_PRIMEIRA("pthread_attr_init");
    uint32_t v[6] = { 0, 0, 1u << 20, 4096, 0, 0 };
    memcpy(g_mem + c->r[0], v, 24); ret32(c, 0);
}
void I_pthread_attr_destroy(CPU *c) { RT_PRIMEIRA("pthread_attr_destroy"); ret32(c, 0); }
void I_pthread_attr_setdetachstate(CPU *c) { RT_PRIMEIRA("pthread_attr_setdetachstate");
    uint32_t f; memcpy(&f, g_mem + c->r[0], 4);
    f = c->r[1] ? (f | 1) : (f & ~1u);
    memcpy(g_mem + c->r[0], &f, 4); ret32(c, 0);
}
void I_pthread_attr_setstack(CPU *c) { RT_PRIMEIRA("pthread_attr_setstack");
    memcpy(g_mem + c->r[0] + 4, &c->r[1], 4); memcpy(g_mem + c->r[0] + 8, &c->r[2], 4); ret32(c, 0);
}
void I_pthread_attr_getstack(CPU *c) { RT_PRIMEIRA("pthread_attr_getstack");
    memcpy(g_mem + c->r[1], g_mem + c->r[0] + 4, 4); memcpy(g_mem + c->r[2], g_mem + c->r[0] + 8, 4); ret32(c, 0);
}
void I_pthread_getattr_np(CPU *c) { RT_PRIMEIRA("pthread_getattr_np");
    CPU *e = cpu_atual();
    uint32_t v[6] = { 0, e->pilha_base, e->pilha_tam, 4096, 0, 0 };
    memcpy(g_mem + c->r[1], v, 24); ret32(c, 0);
}
void I_sched_setaffinity(CPU *c) { RT_PRIMEIRA("sched_setaffinity"); ret32(c, 0); }
#endif
