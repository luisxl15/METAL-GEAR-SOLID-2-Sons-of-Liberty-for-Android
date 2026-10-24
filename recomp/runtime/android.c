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

/* Sinais fatais: registra onde foi (funcao recompilada F_xxxxxxxx = endereco ARM32 do jogo) e a
 * ultima ponte desta thread, e morre como antes. SIGILL e o caso do ARMv8.0 (Snapdragon 680);
 * SIGTRAP e o raise(5) das assercoes do jogo. */
#include <signal.h>
#include <ucontext.h>
extern __thread uint32_t t_ultima_ponte, t_ultima_lr;
const char *rt_nome_ponte(uint32_t ad);
static const int SINAIS[] = { SIGSEGV, SIGBUS, SIGILL, SIGFPE, SIGTRAP, SIGABRT };
static struct sigaction ant[sizeof SINAIS / sizeof SINAIS[0]];
static void no_sinal(int sig, siginfo_t *si, void *uc) {
    uintptr_t pc = (uintptr_t)((ucontext_t *)uc)->uc_mcontext.pc;
    Dl_info di; memset(&di, 0, sizeof di);
    dladdr((void *)pc, &di);
    const char *lib = di.dli_fname ? (strrchr(di.dli_fname, '/') ? strrchr(di.dli_fname, '/') + 1 : di.dli_fname) : "?";
    rt_log("SINAL %d (codigo %d) em %p, pc %s+0x%lx (%s); ultima ponte desta thread: %s (lr do jogo %08x)",
           sig, si->si_code, si->si_addr, lib,
           (unsigned long)(pc - (uintptr_t)di.dli_fbase), di.dli_sname ? di.dli_sname : "?",
           t_ultima_ponte ? rt_nome_ponte(t_ultima_ponte) : "nenhuma", t_ultima_lr);
    for (unsigned k = 0; k < sizeof SINAIS / sizeof SINAIS[0]; k++)
        if (SINAIS[k] == sig) sigaction(sig, &ant[k], NULL);
    /* falha de instrucao/memoria: ao voltar, a instrucao repete e o tratador antigo age.
     * raise()/abort()/kill: o sinal nao repete sozinho, entao manda de novo (fica pendente
     * ate este tratador voltar) -- senao o jogo seguiria depois da assercao. */
    if (si->si_code <= 0) raise(sig);
}
static void instala_sinais(void) {
    struct sigaction sa; memset(&sa, 0, sizeof sa);
    sa.sa_sigaction = no_sinal; sa.sa_flags = SA_SIGINFO | SA_ONSTACK;
    for (unsigned k = 0; k < sizeof SINAIS / sizeof SINAIS[0]; k++) sigaction(SINAIS[k], &sa, &ant[k]);
}

/* files/mgs2_log.txt (ao lado de saveData, que e o FORGELIB_LOG_PATH) + cabecalho do aparelho */
#include <sys/auxv.h>
#include <unistd.h>
#include <sys/system_properties.h>
#include <asm/hwcap.h>
void rt_log_arquivo(FILE *f);
static void abre_log(void) {
    const char *pd = getenv("FORGELIB_LOG_PATH");
    if (!pd) return;
    char cam[600];
    snprintf(cam, sizeof cam, "%s", pd);
    char *b = strrchr(cam, '/');
    if (!b) return;
    snprintf(b, sizeof cam - (size_t)(b - cam), "/mgs2_log.txt");
    FILE *f = fopen(cam, "a");
    if (!f) return;
    rt_log_arquivo(f);
    char modelo[PROP_VALUE_MAX] = "", fab[PROP_VALUE_MAX] = "", soc[PROP_VALUE_MAX] = "", android[PROP_VALUE_MAX] = "";
    __system_property_get("ro.product.manufacturer", fab);
    __system_property_get("ro.product.model", modelo);
    __system_property_get("ro.soc.model", soc);
    if (!soc[0]) __system_property_get("ro.board.platform", soc);
    __system_property_get("ro.build.version.release", android);
    unsigned long hw = getauxval(AT_HWCAP);
    rt_log("==== MGS2 ARM64: %s %s, SoC %s, Android %s, atomicas LSE %s, %ld nucleos ====", fab, modelo, soc,
           android, hw & HWCAP_ATOMICS ? "sim" : "nao", sysconf(_SC_NPROCESSORS_CONF));
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
    abre_log();
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
/* Quadro lento: o que custou naquele quadro (contadores g_est do gl_manual.c, diferenca entre
 * duas trocas de quadro). Vai para o mgs2_log.txt: e o que diz a causa de uma queda num
 * aparelho que nao temos. Ate 1 linha por segundo e 300 por sessao, nada nos 10 s iniciais. */
extern volatile long long g_est[12];
static void quadro_lento(uint64_t t) {
    static long long ant[12];
    static uint64_t ult, ult_aviso, primeiro;
    static unsigned avisos;
    long long d[12];
    for (int i = 0; i < 12; i++) { long long v = g_est[i]; d[i] = v >= ant[i] ? v - ant[i] : v; ant[i] = v; }   /* depuracao zera a cada 2 s */
    if (!primeiro) primeiro = t;
    if (ult && t - ult > 50000000ull && t - primeiro > 10000000000ull && t - ult_aviso > 1000000000ull && avisos < 300) {
        avisos++; ult_aviso = t;
        rt_log("quadro lento: %.0f ms | texturas %lld KB, compilacoes %lld, ReadPixels %lld, mapas c/ leitura %lld "
               "(%lld KB lidos da GPU), BufferData %lld KB, pastas lidas %lld, arquivos abertos %lld, desenhos %lld",
               (t - ult) / 1e6, d[7] >> 10, d[8], d[9], d[3], d[1] >> 10, (d[5] + d[6]) >> 10, d[10], d[11], d[4]);
    }
    ult = t;
}

void rt_quadro(void) {
    __atomic_fetch_add(&g_quadros_jogo, 1, __ATOMIC_RELAXED);
    uint64_t t = agora_ns();
    quadro_lento(t);
    if (!ini_janela) ini_janela = t;
    quadros++;
    if (t - ini_janela >= 2000000000ull) {
        unsigned long long pq_mostrados(void); static unsigned long long mostrados_ant;
        unsigned long long m = pq_mostrados();
        rt_log("%.1f quadros/s de jogo, %.1f na tela (heap do jogo: %u MB)", quadros * 1e9 / (double)(t - ini_janela),
               (m - mostrados_ant) * 1e9 / (double)(t - ini_janela), heap_topo_atual() >> 20);
        mostrados_ant = m;
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
    unsigned long long pq_mostrados(void);   /* com o pulo de quadros, a tela mostra menos que o jogo calcula */
    v[1] = v[3] ? (jlong)fg_apresentados() : (jlong)pq_mostrados();
    v[2] = v[3] ? (jlong)fg_gerados() : 0;
    jlongArray r = (*e)->NewLongArray(e, 4);
    if (r) (*e)->SetLongArrayRegion(e, r, 0, 4, v);
    return r;
}
#endif
