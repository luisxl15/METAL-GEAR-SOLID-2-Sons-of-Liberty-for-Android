/* Velocidade do jogo independente dos quadros desenhados (pulo de quadros).
 *
 * O MGS2 HD e o codigo do PS2: a logica anda um passo por quadro, sem relogio. Se o
 * aparelho desenha a 40 q/s o jogo fica a 2/3 da velocidade; com o limite em 30, a metade.
 * Aqui, na ponte GL (tudo o que a camada D3D9->GL da TransGaming desenha passa por ela):
 *
 *  - ritmo: cada troca de quadro (eglSwapBuffers) e um passo da logica, cadenciado a 60 por
 *    segundo. A thread MainGame so fica 3 quadros a frente da D3DGL (MTD3DNumFramesAhead),
 *    entao a logica segue esse ritmo;
 *  - pulo: quando o quadro termina atrasado (ou o limite de quadros da tela pede), o quadro
 *    SEGUINTE e processado inteiro (estado, texturas, buffers, shaders), mas os desenhos,
 *    clears e blits nao vao para a GPU e ele nao e mostrado. A GPU recupera o atraso e a
 *    logica continua a 60;
 *  - seguranca: so e pulado desenho em alvo "fixo", usado nos 3 quadros anteriores (tela,
 *    cena, pos-processamento). Alvo novo ou de uso esporadico (textura montada uma vez no
 *    carregamento, mapa de sombra que so muda as vezes) e sempre desenhado: pular ali deixaria
 *    lixo para sempre. Nada e pulado depois de um tranco grande (carregamento), e nunca dois
 *    quadros seguidos por atraso.
 *
 * Desligado (ajuste pulo=0): o comportamento antigo, logica = quadros, limitada por fps. */
#ifndef _WIN32
#include "gl_ponte.h"
#include <string.h>
#include <time.h>

int aj_int(const char *chave, int padrao);

/* ---- alvo de desenho atual ------------------------------------------------- */
static __thread GLuint t_fb_desenho, t_fb_leitura;

/* fb -> chave do anexo de cor 0 e do de profundidade (o objeto da textura/renderbuffer, a face) */
#define FBS 4096
static struct { GLuint fb; uint64_t cor, prof; } fbs[FBS];
static unsigned fb_slot(GLuint fb, int cria) {
    unsigned h = (fb * 2654435761u) & (FBS - 1);
    for (unsigned i = 0; i < FBS; i++, h = (h + 1) & (FBS - 1)) {
        if (fbs[h].fb == fb) return h;
        if (!fbs[h].fb) { if (!cria) return FBS; fbs[h].fb = fb; fbs[h].cor = fbs[h].prof = 0; return h; }
    }
    return FBS;
}

void pq_bind_fb(GLenum alvo, GLuint fb) {
    if (alvo == GL_FRAMEBUFFER || alvo == GL_DRAW_FRAMEBUFFER) t_fb_desenho = fb;
    if (alvo == GL_FRAMEBUFFER || alvo == GL_READ_FRAMEBUFFER) t_fb_leitura = fb;
}
/* obj: textura ou renderbuffer (rb = 1); sub: face do cubo / camada */
void pq_anexo(GLenum alvo, GLenum anexo, GLuint obj, int rb, GLuint sub) {
    GLuint fb = alvo == GL_READ_FRAMEBUFFER ? t_fb_leitura : t_fb_desenho;
    if (!fb) return;
    unsigned s = fb_slot(fb, 1);
    if (s == FBS) return;
    uint64_t k = obj ? ((uint64_t)obj << 24) ^ ((uint64_t)rb << 23) ^ (sub & 0x7fffff) ^ 0x8000000000000000ull : 0;
    if (anexo == GL_COLOR_ATTACHMENT0) fbs[s].cor = k;
    else if (anexo == GL_DEPTH_ATTACHMENT || anexo == GL_DEPTH_STENCIL_ATTACHMENT) fbs[s].prof = k;
}
void pq_apaga_fbs(GLsizei n, const GLuint *ids) {
    for (GLsizei i = 0; i < n; i++) {
        unsigned s = fb_slot(ids[i], 0);
        if (s != FBS) fbs[s].cor = fbs[s].prof = 0;   /* o id pode voltar com outros anexos */
    }
}

/* ---- historico de uso dos alvos ------------------------------------------- */
#define ALVOS 8192
static struct { uint64_t k; unsigned ultimo; unsigned hist; } alvos[ALVOS];   /* hist bit 0 = quadro atual */
static unsigned g_quadro = 1;
static int g_pulando;          /* o quadro em curso esta sendo pulado */
static int g_ligado = -1;

static uint64_t chave_atual(void) {
    GLuint fb = t_fb_desenho;
    if (!fb) return 1;                                     /* janela */
    unsigned s = fb_slot(fb, 0);
    if (s != FBS) { if (fbs[s].cor) return fbs[s].cor; if (fbs[s].prof) return fbs[s].prof; }
    return 0x4000000000000000ull | fb;
}

/* chamado por cada desenho, clear e blit: 1 = manda para o driver, 0 = pula */
int pq_desenha(void) {
    if (g_ligado <= 0) return 1;
    uint64_t k = chave_atual();
    unsigned h = (unsigned)((k * 0x9E3779B97F4A7C15ull) >> 51) & (ALVOS - 1);
    unsigned i = 0;
    for (; i < ALVOS; i++, h = (h + 1) & (ALVOS - 1)) {
        if (alvos[h].k == k || !alvos[h].k) break;
    }
    if (i == ALVOS) return 1;                                /* tabela cheia: na duvida, desenha */
    if (!alvos[h].k) { alvos[h].k = k; alvos[h].ultimo = g_quadro; alvos[h].hist = 0; }
    unsigned d = g_quadro - alvos[h].ultimo;
    unsigned hist = d >= 32 ? 0 : alvos[h].hist << d;
    int fixo = (hist & 0xe) == 0xe;                         /* usado nos 3 quadros anteriores */
    alvos[h].hist = hist | 1; alvos[h].ultimo = g_quadro;
    return !(g_pulando && fixo);
}

/* ---- ritmo e decisao ------------------------------------------------------ */
static long long agora_ns(void) { struct timespec t; clock_gettime(CLOCK_MONOTONIC, &t); return (long long)t.tv_sec * 1000000000LL + t.tv_nsec; }
static unsigned long long g_mostrados;
unsigned long long pq_mostrados(void) { return g_mostrados; }
int pq_ligado(void) { return g_ligado > 0; }

/* Na troca de quadro (thread D3DGL). Devolve 1 se o quadro que acaba de terminar deve ir para a
 * tela; 0 = foi pulado (nada novo desenhado). Dorme para cadenciar a logica e decide o seguinte. */
int pq_troca(void) {
    void aj_ritmo(void);
    if (g_ligado < 0) {
        g_ligado = aj_int("pulo", 1);
        rt_log("pulo de quadros: %s (logica a 60 por segundo, tela no limite de quadros)", g_ligado ? "ligado" : "desligado");
    }
    if (!g_ligado) { aj_ritmo(); g_quadro++; g_mostrados++; return 1; }

    static long long prox, ult_mostrado;
    static int pulados_seguidos, fps_tela = -1;
    if (fps_tela < 0) fps_tela = aj_int("fps", 60);
    const long long passo = 1000000000LL / 60;
    long long t = agora_ns();
    if (!prox) prox = t;
    if (t < prox) {
        struct timespec ts = { (time_t)(prox / 1000000000LL), (long)(prox % 1000000000LL) };
        clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &ts, NULL);
        t = prox;
    }
    long long atraso = t - prox;
    int tranco = atraso > 8 * passo;                       /* carregamento: nao tenta recuperar */
    if (tranco) { prox = t; atraso = 0; }
    prox += passo;

    int este_pulado = g_pulando;
    if (!este_pulado) { g_mostrados++; ult_mostrado = t; }

    /* o proximo quadro: pula se atrasou mais de meio passo, ou se o limite da tela pede */
    int pular = 0;
    if (!tranco) {
        if (atraso > passo / 2 && pulados_seguidos < 1) pular = 1;
        if (fps_tela > 0 && fps_tela < 60) {
            long long minimo = 1000000000LL / fps_tela - passo / 2;
            int max_seg = 60 / fps_tela - 1;                 /* 30 -> 1, 20 -> 2 */
            if (t + passo - ult_mostrado < minimo && pulados_seguidos < max_seg) pular = 1;
        }
    }
    pulados_seguidos = pular ? pulados_seguidos + 1 : 0;
    g_pulando = pular;
    g_quadro++;
    return !este_pulado;
}
#endif
