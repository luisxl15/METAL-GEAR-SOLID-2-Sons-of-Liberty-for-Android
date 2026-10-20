/* Ajustes do usuario (tela de ajustes em Java, java_tela/): um arquivo chave=valor
 * na pasta externa do app, lido pelo runtime.
 *
 *   /sdcard/Android/data/jp.konami.mgs2hd.shield/files/mgs2_ajustes.txt
 *     fps=60            limite de quadros (30, 60; 0 = sem limite)
 *     resolucao=1280x720  resolucao de desenho do jogo ([droiddrv] SupportedResolutions)
 *
 * A resolucao entra no config da Forge: quando o jogo abre .../preferences/config
 * para ler, entregamos uma copia com a chave aplicada (o arquivo interno so e
 * copiado do APK na primeira execucao, e nao da para mexer nele de fora). */
#ifndef _WIN32
#include "runtime.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pthread.h>

#define ARQ_AJUSTES "/storage/emulated/0/Android/data/jp.konami.mgs2hd.shield/files/mgs2_ajustes.txt"

static char g_txt[4096];
static pthread_once_t uma = PTHREAD_ONCE_INIT;

static void carrega(void) {
    FILE *f = fopen(ARQ_AJUSTES, "rb");
    if (!f) { rt_log("ajustes: %s nao existe, valores padrao", ARQ_AJUSTES); return; }
    size_t n = fread(g_txt, 1, sizeof g_txt - 1, f);
    g_txt[n] = 0;
    fclose(f);
    rt_log("ajustes: %s", g_txt);
}

/* valor da chave (copia em buf) ou NULL */
const char *aj_valor(const char *chave, char *buf, size_t tam) {
    pthread_once(&uma, carrega);
    size_t lc = strlen(chave);
    for (const char *p = g_txt; *p; ) {
        const char *e = strchr(p, '\n'); size_t n = e ? (size_t)(e - p) : strlen(p);
        if (n > lc && !strncmp(p, chave, lc) && p[lc] == '=') {
            size_t m = n - lc - 1; while (m && (p[lc + 1 + m - 1] == '\r' || p[lc + 1 + m - 1] == ' ')) m--;
            if (m >= tam) m = tam - 1;
            memcpy(buf, p + lc + 1, m); buf[m] = 0;
            return buf;
        }
        p += n + (e ? 1 : 0);
    }
    return NULL;
}
int aj_int(const char *chave, int padrao) {
    char b[32]; const char *v = aj_valor(chave, b, sizeof b);
    return v && *v ? atoi(v) : padrao;
}

/* ---- config da Forge com os ajustes aplicados ----------------------------- */
static int termina_com(const char *s, const char *fim) {
    size_t a = strlen(s), b = strlen(fim);
    return a >= b && !strcmp(s + a - b, fim);
}

FILE *aj_abre_config(const char *caminho, const char *modo) {
    if (!termina_com(caminho, "/preferences/config") || modo[0] != 'r') return NULL;
    char res[32];
    if (!aj_valor("resolucao", res, sizeof res) || !strchr(res, 'x')) return NULL;
    FILE *f = fopen(caminho, "rb");
    if (!f) return NULL;
    fseek(f, 0, SEEK_END); long n = ftell(f); fseek(f, 0, SEEK_SET);
    char *orig = malloc((size_t)n + 1); n = (long)fread(orig, 1, (size_t)n, f); orig[n] = 0; fclose(f);
    /* tira qualquer "SupportedResolutions" existente e poe a nossa na secao [droiddrv] */
    size_t cap = (size_t)n + 256; char *novo = malloc(cap); size_t k = 0;
    char linha[96]; snprintf(linha, sizeof linha, "\"SupportedResolutions\" = \"%s\"\n", res);
    int pos_sec = 0;
    for (const char *p = orig; *p; ) {
        const char *e = strchr(p, '\n'); size_t m = e ? (size_t)(e - p) + 1 : strlen(p);
        if (!(m > 22 && strstr(p, "\"SupportedResolutions\"") && strstr(p, "\"SupportedResolutions\"") < p + m)) {
            memcpy(novo + k, p, m); k += m;
            if (!pos_sec && m >= 10 && !strncmp(p, "[droiddrv]", 10)) { memcpy(novo + k, linha, strlen(linha)); k += strlen(linha); pos_sec = 1; }
        }
        p += m;
    }
    if (!pos_sec) { k += (size_t)snprintf(novo + k, cap - k, "\n[droiddrv]\n%s", linha); }
    free(orig);
    rt_log("ajustes: config da Forge com [droiddrv] SupportedResolutions = %s", res);
    return fmemopen(novo, k, "rb");   /* 'novo' fica vivo enquanto o arquivo existir (vaza pouco, uma vez) */
}

/* ---- limite de quadros (chamado a cada eglSwapBuffers) --------------------- */
void aj_ritmo(void) {
    static int fps = -1;
    static struct timespec prox;
    if (fps < 0) {
        fps = aj_int("fps", 60);
        rt_log("ajustes: limite de quadros %d", fps);
    }
    if (fps <= 0) return;
    long passo = 1000000000L / fps;
    struct timespec agora; clock_gettime(CLOCK_MONOTONIC, &agora);
    if (!prox.tv_sec) prox = agora;
    long long a = (long long)agora.tv_sec * 1000000000LL + agora.tv_nsec;
    long long p = (long long)prox.tv_sec * 1000000000LL + prox.tv_nsec;
    if (a < p) {
        struct timespec ts = { (time_t)(p / 1000000000LL), (long)(p % 1000000000LL) };
        clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &ts, NULL);
        a = p;
    } else if (a - p > 4 * passo) {
        p = a;   /* atrasou demais (carregamento): nao tenta recuperar correndo */
    }
    p += passo;
    prox.tv_sec = (time_t)(p / 1000000000LL); prox.tv_nsec = (long)(p % 1000000000LL);
}
#endif
