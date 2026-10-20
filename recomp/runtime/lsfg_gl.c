/* Lado GL da geracao de quadros (LSFG, ver lsfg_vk.cpp).
 *
 * Com a geracao ligada o Vulkan e dono da janela e o contexto GL do jogo fica numa
 * superficie pbuffer. O blit final do jogo (o quadro 1280x720 para a janela) e desviado
 * para um AHardwareBuffer do anel do lsfg_vk.cpp, e o eglSwapBuffers vira uma fence
 * nativa entregue ao apresentador Vulkan. O quadro vai de cabeca para baixo no AHB
 * (linha 0 = topo), que e a orientacao das imagens do Vulkan. */
#ifndef _WIN32
#include "runtime.h"
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GLES3/gl32.h>
#include <GLES2/gl2ext.h>
#include <android/hardware_buffer.h>
#include <android/native_window.h>

int fg_quer(void);
int fg_inicia(ANativeWindow *jan, int w, int h);
int fg_ativo(void);
void fg_janela(ANativeWindow *jan);
AHardwareBuffer *fg_alvo(int w, int h, int *idx, int *geracao);
void fg_envia(int idx, int fd);
void fg_devolve(int idx);

#define ANEL 3
static struct {
    EGLSurface sup;                 /* o pbuffer que o jogo recebeu no lugar da janela */
    int jan_w, jan_h;
    int geracao;
    AHardwareBuffer *ahb[ANEL];
    EGLImageKHR img[ANEL];
    GLuint tex[ANEL], fbo[ANEL];
    int pendente;                   /* AHB desenhado neste quadro, ainda nao entregue */
} FG = { EGL_NO_SURFACE, 0, 0, -1, {0}, {0}, {0}, {0}, -1 };

static PFNEGLGETNATIVECLIENTBUFFERANDROIDPROC p_cliente;
static PFNEGLCREATEIMAGEKHRPROC p_cria_img;
static PFNEGLDESTROYIMAGEKHRPROC p_destroi_img;
static PFNGLEGLIMAGETARGETTEXTURE2DOESPROC p_img_tex;
static PFNEGLCREATESYNCKHRPROC p_cria_sync;
static PFNEGLDESTROYSYNCKHRPROC p_destroi_sync;
static PFNEGLDUPNATIVEFENCEFDANDROIDPROC p_dup_fence;

static int carrega_ext(void) {
    p_cliente = (PFNEGLGETNATIVECLIENTBUFFERANDROIDPROC)eglGetProcAddress("eglGetNativeClientBufferANDROID");
    p_cria_img = (PFNEGLCREATEIMAGEKHRPROC)eglGetProcAddress("eglCreateImageKHR");
    p_destroi_img = (PFNEGLDESTROYIMAGEKHRPROC)eglGetProcAddress("eglDestroyImageKHR");
    p_img_tex = (PFNGLEGLIMAGETARGETTEXTURE2DOESPROC)eglGetProcAddress("glEGLImageTargetTexture2DOES");
    p_cria_sync = (PFNEGLCREATESYNCKHRPROC)eglGetProcAddress("eglCreateSyncKHR");
    p_destroi_sync = (PFNEGLDESTROYSYNCKHRPROC)eglGetProcAddress("eglDestroySyncKHR");
    p_dup_fence = (PFNEGLDUPNATIVEFENCEFDANDROIDPROC)eglGetProcAddress("eglDupNativeFenceFDANDROID");
    if (!p_cliente || !p_cria_img || !p_destroi_img || !p_img_tex) {
        rt_log("LSFG: EGL sem AHardwareBuffer -> EGLImage; geracao desligada");
        return 0;
    }
    if (!p_cria_sync || !p_dup_fence) rt_log("LSFG: EGL sem fence nativa: glFinish a cada quadro");
    return 1;
}

/* eglCreateWindowSurface: com a geracao ligada e tudo montado, devolve um pbuffer e o
 * Vulkan fica com a janela; EGL_NO_SURFACE = siga o caminho normal */
EGLSurface fg_cria_superficie(EGLDisplay d, EGLConfig cfg, ANativeWindow *jan) {
    if (FG.sup != EGL_NO_SURFACE) {          /* volta do segundo plano: janela nova, mesmo pbuffer */
        fg_janela(jan);
        FG.jan_w = ANativeWindow_getWidth(jan); FG.jan_h = ANativeWindow_getHeight(jan);
        return FG.sup;
    }
    if (!fg_quer() || !carrega_ext()) return EGL_NO_SURFACE;
    /* o pbuffer primeiro: se a config do jogo nao servir, a janela continua do GL */
    static const EGLint at[] = { EGL_WIDTH, 16, EGL_HEIGHT, 16, EGL_NONE };
    EGLSurface pb = eglCreatePbufferSurface(d, cfg, at);
    if (pb == EGL_NO_SURFACE) {
        rt_log("LSFG: a config do jogo nao aceita pbuffer (%x); geracao desligada", eglGetError());
        return EGL_NO_SURFACE;
    }
    if (!fg_inicia(jan, 1280, 720)) { eglDestroySurface(d, pb); return EGL_NO_SURFACE; }
    FG.sup = pb;
    FG.jan_w = ANativeWindow_getWidth(jan); FG.jan_h = ANativeWindow_getHeight(jan);
    rt_log("LSFG: GL em pbuffer, janela %dx%d com o Vulkan", FG.jan_w, FG.jan_h);
    return pb;
}

int fg_eh_superficie(EGLSurface s) { return s != EGL_NO_SURFACE && s == FG.sup; }

/* eglDestroySurface do pbuffer: a janela vai sumir (segundo plano). O pbuffer fica vivo
 * para a volta; so a swapchain morre. Devolve 1 = nao destrua de verdade. */
int fg_destroi_superficie(EGLSurface s) {
    if (!fg_eh_superficie(s)) return 0;
    fg_janela(NULL);
    return 1;
}

/* eglQuerySurface no pbuffer: o tamanho e o da janela */
int fg_tamanho(EGLSurface s, EGLint atr, EGLint *v) {
    if (!fg_eh_superficie(s)) return 0;
    if (atr == EGL_WIDTH) { *v = FG.jan_w; return 1; }
    if (atr == EGL_HEIGHT) { *v = FG.jan_h; return 1; }
    return 0;
}

static void esquece_anel(void) {
    EGLDisplay d = eglGetCurrentDisplay();
    for (int k = 0; k < ANEL; k++) {
        if (FG.fbo[k]) glDeleteFramebuffers(1, &FG.fbo[k]);
        if (FG.tex[k]) glDeleteTextures(1, &FG.tex[k]);
        if (FG.img[k]) p_destroi_img(d, FG.img[k]);
        FG.fbo[k] = FG.tex[k] = 0; FG.img[k] = 0; FG.ahb[k] = NULL;
    }
}

static int prepara(int k, AHardwareBuffer *ahb) {
    if (FG.ahb[k] == ahb && FG.fbo[k]) return 1;
    EGLDisplay d = eglGetCurrentDisplay();
    if (FG.fbo[k]) { glDeleteFramebuffers(1, &FG.fbo[k]); glDeleteTextures(1, &FG.tex[k]); p_destroi_img(d, FG.img[k]); }
    static const EGLint at[] = { EGL_IMAGE_PRESERVED_KHR, EGL_TRUE, EGL_NONE };
    FG.img[k] = p_cria_img(d, EGL_NO_CONTEXT, EGL_NATIVE_BUFFER_ANDROID, p_cliente(ahb), at);
    if (!FG.img[k]) { rt_log("LSFG: eglCreateImageKHR do AHB falhou (%x)", eglGetError()); return 0; }
    GLint tex_antes = 0, fb_antes = 0;
    glGetIntegerv(GL_TEXTURE_BINDING_2D, &tex_antes);
    glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &fb_antes);
    glGenTextures(1, &FG.tex[k]);
    glBindTexture(GL_TEXTURE_2D, FG.tex[k]);
    p_img_tex(GL_TEXTURE_2D, (GLeglImageOES)FG.img[k]);
    glGenFramebuffers(1, &FG.fbo[k]);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, FG.fbo[k]);
    glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, FG.tex[k], 0);
    GLenum st = glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, (GLuint)fb_antes);
    glBindTexture(GL_TEXTURE_2D, (GLuint)tex_antes);
    if (st != GL_FRAMEBUFFER_COMPLETE) { rt_log("LSFG: FBO do AHB incompleto (%x)", st); return 0; }
    FG.ahb[k] = ahb;
    return 1;
}

typedef void (*BlitFn)(GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLbitfield, GLenum);

/* blit do jogo para o framebuffer 0: vai para o AHB (1:1, cabeca para baixo). 1 = feito */
int fg_gl_blit(BlitFn p, GLint a0, GLint a1, GLint a2, GLint a3, GLint a4, GLint a5, GLint a6, GLint a7) {
    if (FG.sup == EGL_NO_SURFACE || !fg_ativo()) return 0;
    int w = a2 > a0 ? a2 - a0 : a0 - a2, h = a3 > a1 ? a3 - a1 : a1 - a3;
    if (w <= 0 || h <= 0) return 1;
    int k = FG.pendente;
    if (k < 0) {
        int ger = 0;
        AHardwareBuffer *ahb = fg_alvo(w, h, &k, &ger);
        if (ger != FG.geracao) { esquece_anel(); FG.geracao = ger; }
        if (!ahb || !prepara(k, ahb)) { if (ahb) fg_devolve(k); return 1; }
        FG.pendente = k;
    }
    GLboolean tes = glIsEnabled(GL_SCISSOR_TEST);
    if (tes) glDisable(GL_SCISSOR_TEST);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, FG.fbo[k]);
    /* mesmo sentido horizontal do jogo; vertical invertido (linha 0 = topo, como no Vulkan) */
    GLint x0 = a6 >= a4 ? 0 : w, x1 = a6 >= a4 ? w : 0;
    GLint y0 = a7 >= a5 ? h : 0, y1 = a7 >= a5 ? 0 : h;
    p(a0, a1, a2, a3, x0, y0, x1, y1, GL_COLOR_BUFFER_BIT, GL_NEAREST);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    if (tes) glEnable(GL_SCISSOR_TEST);
    return 1;
}

/* eglSwapBuffers no pbuffer: entrega o quadro ao Vulkan. 1 = feito (nao chame o swap real) */
int fg_troca(EGLDisplay d, EGLSurface s) {
    if (!fg_eh_superficie(s)) return 0;
    if (FG.pendente < 0) return 1;           /* quadro sem blit para a janela */
    int fd = -1;
    if (p_cria_sync && p_dup_fence) {
        static const EGLint at[] = { EGL_SYNC_NATIVE_FENCE_FD_ANDROID, EGL_NO_NATIVE_FENCE_FD_ANDROID, EGL_NONE };
        EGLSyncKHR sy = p_cria_sync(d, EGL_SYNC_NATIVE_FENCE_ANDROID, at);
        glFlush();                               /* a fence so ganha fd depois do flush */
        if (sy != EGL_NO_SYNC_KHR) { fd = p_dup_fence(d, sy); p_destroi_sync(d, sy); }
    }
    if (fd < 0) glFinish();
    fg_envia(FG.pendente, fd);
    FG.pendente = -1;
    return 1;
}
#endif
