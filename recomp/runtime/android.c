/* Cola do lado Android: o libMGS2HD.so de 64 bits que o Java da Forge carrega.
 *  - JNI_OnLoad: sobe o runtime (memoria, imagens, construtores) e chama o
 *    JNI_OnLoad do jogo com o JavaVM do jogo;
 *  - as imagens relocadas vem como libmgs2img_gnustl.so / libmgs2img_jogo.so
 *    ao lado desta biblioteca (jniLibs: o Android extrai para a pasta nativa);
 *  - contador de quadros para o log. */
#ifdef __ANDROID__
#include "runtime.h"
#include "jni_ponte.h"
#include <dlfcn.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

extern const char *g_dir_dados;
static char dir_libs[512];
static pthread_once_t uma_vez = PTHREAD_ONCE_INIT;

/* SIGSEGV/SIGBUS: registra a ultima ponte (GL etc.) desta thread e morre como antes */
#include <signal.h>
extern __thread uint32_t t_ultima_ponte, t_ultima_lr;
const char *rt_nome_ponte(uint32_t ad);
static struct sigaction ant_segv, ant_bus;
static void no_sinal(int sig, siginfo_t *si, void *uc) {
    rt_log("SINAL %d em %p; ultima ponte desta thread: %s (lr do jogo %08x)", sig, si->si_addr,
           t_ultima_ponte ? rt_nome_ponte(t_ultima_ponte) : "nenhuma", t_ultima_lr);
    sigaction(sig, sig == SIGSEGV ? &ant_segv : &ant_bus, NULL);
    (void)uc;
}
static void instala_sinais(void) {
    struct sigaction sa; memset(&sa, 0, sizeof sa);
    sa.sa_sigaction = no_sinal; sa.sa_flags = SA_SIGINFO | SA_ONSTACK;
    sigaction(SIGSEGV, &sa, &ant_segv);
    sigaction(SIGBUS, &sa, &ant_bus);
}

/* Saves das versoes antigas: o cartao de memoria do jogo criava a pasta de cada save sem o
 * modo (r--------, ver I_mkdir em pontes_auto.c) e nada gravava dentro. Sobrescrever um save
 * nao passa pelo mkdir, entao o conserto vai aqui, uma vez por abertura: toda pasta do app em
 * <FORGELIB_LOG_PATH>/Documents/mgs2_savedata ganha rwxr-x---. */
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
static void conserta_pastas_de_save(void) {
    const char *pd = getenv("FORGELIB_LOG_PATH");
    if (!pd) return;
    char raiz[512], cam[768];
    snprintf(raiz, sizeof raiz, "%s/Documents/mgs2_savedata", pd);
    DIR *d = opendir(raiz);
    if (!d) return;
    struct dirent *e;
    while ((e = readdir(d))) {
        if (e->d_name[0] == '.') continue;
        snprintf(cam, sizeof cam, "%s/%s", raiz, e->d_name);
        struct stat st;
        if (stat(cam, &st) || !S_ISDIR(st.st_mode) || st.st_uid != getuid() || (st.st_mode & 0750) == 0750) continue;
        int r = chmod(cam, (st.st_mode & 07777) | 0750);
        rt_log("save: %s estava %o; chmod -> %s", e->d_name, (unsigned)(st.st_mode & 07777), r ? "falhou" : "ok");
    }
    closedir(d);
}

static void sobe(void) {
    instala_sinais();
    conserta_pastas_de_save();
    Dl_info di;
    if (dladdr((void *)sobe, &di) && di.dli_fname) {
        snprintf(dir_libs, sizeof dir_libs, "%s", di.dli_fname);
        char *b = strrchr(dir_libs, '/');
        if (b) *b = 0;
    }
    g_dir_dados = dir_libs;
    rt_log("MGS2 recompilado para ARM64; libs em %s", dir_libs);
    rt_inicia();
}
void rt_garante(void) { pthread_once(&uma_vez, sobe); }

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reservado) {
    (void)reservado;
    JNIEnv *e = NULL;
    (*vm)->GetEnv(vm, (void **)&e, JNI_VERSION_1_6);
    jh_inicia(vm, e, NULL);
    rt_garante();
    uint32_t f = rt_exportado("JNI_OnLoad");
    if (f) {
        int marca = jh_marca_locais();
        uint32_t v = jogo_chama(f, 2, jh_vm_jogo(), 0);
        jh_solta_locais(marca);
        rt_log("JNI_OnLoad do jogo devolveu %08x", v);
    }
    return JNI_VERSION_1_6;
}

/* ---- quadros ----------------------------------------------------------- */
static uint64_t agora_ns(void) { struct timespec t; clock_gettime(CLOCK_MONOTONIC, &t); return (uint64_t)t.tv_sec * 1000000000ull + (uint64_t)t.tv_nsec; }
static uint64_t ini_janela;
static unsigned quadros;
static volatile unsigned long long g_quadros_jogo;   /* medidor de FPS (MedidorFps.java) */
void rt_quadro(void) {
    __atomic_fetch_add(&g_quadros_jogo, 1, __ATOMIC_RELAXED);
    uint64_t t = agora_ns();
    if (!ini_janela) ini_janela = t;
    quadros++;
    if (t - ini_janela >= 2000000000ull) {
        rt_log("%.1f quadros/s (heap do jogo: %u MB)", quadros * 1e9 / (double)(t - ini_janela), heap_topo_atual() >> 20);
#ifdef MGS2_DEPURA
        void gl_estat_log(void); gl_estat_log();
#endif
        quadros = 0; ini_janela = t;
    }
}

/* Medidor de FPS da casca Java (com.nvidia.forge.MedidorFps): contadores acumulados,
 * o Java tira a taxa pela diferenca. [0] quadros do jogo (eglSwapBuffers), [1] quadros
 * na tela (com a geracao: os apresentados pelo Vulkan; sem ela, os mesmos do jogo),
 * [2] quadros gerados pelo LSFG, [3] geracao ligada (0/1) */
int fg_ativo(void);
unsigned long long fg_apresentados(void);
unsigned long long fg_gerados(void);
JNIEXPORT jlongArray JNICALL Java_com_nvidia_forge_MedidorFps_contadores(JNIEnv *e, jclass k) {
    (void)k;
    jlong v[4];
    v[0] = (jlong)__atomic_load_n(&g_quadros_jogo, __ATOMIC_RELAXED);
    v[3] = fg_ativo();
    v[1] = v[3] ? (jlong)fg_apresentados() : v[0];
    v[2] = v[3] ? (jlong)fg_gerados() : 0;
    jlongArray r = (*e)->NewLongArray(e, 4);
    if (r) (*e)->SetLongArrayRegion(e, r, 0, 4, v);
    return r;
}
#endif
