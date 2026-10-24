/* GERADO por gerar_gl.py */
#ifndef _WIN32
#include "runtime.h"
#include <EGL/egl.h>
#define GL_GLEXT_PROTOTYPES
#include <GLES3/gl32.h>
#include <GLES2/gl2ext.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "gl_ponte.h"
/* pulo de quadros (pulo.c) */
void pq_bind_fb(GLenum alvo, GLuint fb);
void pq_anexo(GLenum alvo, GLenum anexo, GLuint obj, int rb, GLuint sub);
void pq_apaga_fbs(GLsizei n, const GLuint *ids);
int pq_desenha(void);


void G_glAcquireKeyedMutexWin32EXT(CPU *c) { RT_PRIMEIRA("glAcquireKeyedMutexWin32EXT");
    static GLboolean (*p)(GLuint, GLuint64, GLuint); if (!p) p = gl_proc("glAcquireKeyedMutexWin32EXT");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLuint64 a1 = (GLuint64)arg64(&a);
    GLuint a2 = (GLuint)arg32(&a);
    ret32(c, (uint32_t)p(a0, a1, a2));
}
void G_glActiveShaderProgram(CPU *c) { RT_PRIMEIRA("glActiveShaderProgram");
    static void (*p)(GLuint, GLuint); if (!p) p = gl_proc("glActiveShaderProgram");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLuint a1 = (GLuint)arg32(&a);
    p(a0, a1);
}
void G_glActiveShaderProgramEXT(CPU *c) { RT_PRIMEIRA("glActiveShaderProgramEXT");
    static void (*p)(GLuint, GLuint); if (!p) p = gl_proc("glActiveShaderProgramEXT");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLuint a1 = (GLuint)arg32(&a);
    p(a0, a1);
}
void G_glActiveTexture(CPU *c) { RT_PRIMEIRA("glActiveTexture");
    static void (*p)(GLenum); if (!p) p = gl_proc("glActiveTexture");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    p(a0);
}
void G_glAlphaFuncQCOM(CPU *c) { RT_PRIMEIRA("glAlphaFuncQCOM");
    static void (*p)(GLenum, GLclampf); if (!p) p = gl_proc("glAlphaFuncQCOM");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLclampf a1 = argf(&a);
    p(a0, a1);
}
void G_glApplyFramebufferAttachmentCMAAINTEL(CPU *c) { RT_PRIMEIRA("glApplyFramebufferAttachmentCMAAINTEL");
    static void (*p)(void); if (!p) p = gl_proc("glApplyFramebufferAttachmentCMAAINTEL");
    Args a = args_de(c); (void)a;
    p();
}
void G_glAttachShader(CPU *c) { RT_PRIMEIRA("glAttachShader");
    static void (*p)(GLuint, GLuint); if (!p) p = gl_proc("glAttachShader");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLuint a1 = (GLuint)arg32(&a);
    p(a0, a1);
}
void G_glBeginConditionalRenderNV(CPU *c) { RT_PRIMEIRA("glBeginConditionalRenderNV");
    static void (*p)(GLuint, GLenum); if (!p) p = gl_proc("glBeginConditionalRenderNV");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    p(a0, a1);
}
void G_glBeginPerfMonitorAMD(CPU *c) { RT_PRIMEIRA("glBeginPerfMonitorAMD");
    static void (*p)(GLuint); if (!p) p = gl_proc("glBeginPerfMonitorAMD");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    p(a0);
}
void G_glBeginPerfQueryINTEL(CPU *c) { RT_PRIMEIRA("glBeginPerfQueryINTEL");
    static void (*p)(GLuint); if (!p) p = gl_proc("glBeginPerfQueryINTEL");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    p(a0);
}
void G_glBeginQuery(CPU *c) { RT_PRIMEIRA("glBeginQuery");
    static void (*p)(GLenum, GLuint); if (!p) p = gl_proc("glBeginQuery");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLuint a1 = (GLuint)arg32(&a);
    p(a0, a1);
}
void G_glBeginQueryEXT(CPU *c) { RT_PRIMEIRA("glBeginQueryEXT");
    static void (*p)(GLenum, GLuint); if (!p) p = gl_proc("glBeginQueryEXT");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLuint a1 = (GLuint)arg32(&a);
    p(a0, a1);
}
void G_glBeginTransformFeedback(CPU *c) { RT_PRIMEIRA("glBeginTransformFeedback");
    static void (*p)(GLenum); if (!p) p = gl_proc("glBeginTransformFeedback");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    p(a0);
}
void G_glBindAttribLocation(CPU *c) { RT_PRIMEIRA("glBindAttribLocation");
    static void (*p)(GLuint, GLuint, const GLchar *); if (!p) p = gl_proc("glBindAttribLocation");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLuint a1 = (GLuint)arg32(&a);
    const GLchar * a2 = (const GLchar *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glBindBufferBase(CPU *c) { RT_PRIMEIRA("glBindBufferBase");
    static void (*p)(GLenum, GLuint, GLuint); if (!p) p = gl_proc("glBindBufferBase");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLuint a1 = (GLuint)arg32(&a);
    GLuint a2 = (GLuint)arg32(&a);
    p(a0, a1, a2);
}
void G_glBindBufferRange(CPU *c) { RT_PRIMEIRA("glBindBufferRange");
    static void (*p)(GLenum, GLuint, GLuint, GLintptr, GLsizeiptr); if (!p) p = gl_proc("glBindBufferRange");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLuint a1 = (GLuint)arg32(&a);
    GLuint a2 = (GLuint)arg32(&a);
    GLintptr a3 = (GLintptr)(int32_t)arg32(&a);
    GLsizeiptr a4 = (GLsizeiptr)(int32_t)arg32(&a);
    p(a0, a1, a2, a3, a4);
}
void G_glBindFragDataLocationEXT(CPU *c) { RT_PRIMEIRA("glBindFragDataLocationEXT");
    static void (*p)(GLuint, GLuint, const GLchar *); if (!p) p = gl_proc("glBindFragDataLocationEXT");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLuint a1 = (GLuint)arg32(&a);
    const GLchar * a2 = (const GLchar *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glBindFragDataLocationIndexedEXT(CPU *c) { RT_PRIMEIRA("glBindFragDataLocationIndexedEXT");
    static void (*p)(GLuint, GLuint, GLuint, const GLchar *); if (!p) p = gl_proc("glBindFragDataLocationIndexedEXT");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLuint a1 = (GLuint)arg32(&a);
    GLuint a2 = (GLuint)arg32(&a);
    const GLchar * a3 = (const GLchar *)G2H(arg32(&a));
    p(a0, a1, a2, a3);
}
void G_glBindFramebuffer(CPU *c) { RT_PRIMEIRA("glBindFramebuffer");
    static void (*p)(GLenum, GLuint); if (!p) p = gl_proc("glBindFramebuffer");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLuint a1 = (GLuint)arg32(&a);
    pq_bind_fb(a0, a1);
    p(a0, a1);
}
void G_glBindImageTexture(CPU *c) { RT_PRIMEIRA("glBindImageTexture");
    static void (*p)(GLuint, GLuint, GLint, GLboolean, GLint, GLenum, GLenum); if (!p) p = gl_proc("glBindImageTexture");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLuint a1 = (GLuint)arg32(&a);
    GLint a2 = (GLint)arg32(&a);
    GLboolean a3 = (GLboolean)arg32(&a);
    GLint a4 = (GLint)arg32(&a);
    GLenum a5 = (GLenum)arg32(&a);
    GLenum a6 = (GLenum)arg32(&a);
    p(a0, a1, a2, a3, a4, a5, a6);
}
void G_glBindProgramPipeline(CPU *c) { RT_PRIMEIRA("glBindProgramPipeline");
    static void (*p)(GLuint); if (!p) p = gl_proc("glBindProgramPipeline");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    p(a0);
}
void G_glBindProgramPipelineEXT(CPU *c) { RT_PRIMEIRA("glBindProgramPipelineEXT");
    static void (*p)(GLuint); if (!p) p = gl_proc("glBindProgramPipelineEXT");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    p(a0);
}
void G_glBindRenderbuffer(CPU *c) { RT_PRIMEIRA("glBindRenderbuffer");
    static void (*p)(GLenum, GLuint); if (!p) p = gl_proc("glBindRenderbuffer");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLuint a1 = (GLuint)arg32(&a);
    p(a0, a1);
}
void G_glBindSampler(CPU *c) { RT_PRIMEIRA("glBindSampler");
    static void (*p)(GLuint, GLuint); if (!p) p = gl_proc("glBindSampler");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLuint a1 = (GLuint)arg32(&a);
    p(a0, a1);
}
void G_glBindTexture(CPU *c) { RT_PRIMEIRA("glBindTexture");
    static void (*p)(GLenum, GLuint); if (!p) p = gl_proc("glBindTexture");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLuint a1 = (GLuint)arg32(&a);
    p(a0, a1);
}
void G_glBindTransformFeedback(CPU *c) { RT_PRIMEIRA("glBindTransformFeedback");
    static void (*p)(GLenum, GLuint); if (!p) p = gl_proc("glBindTransformFeedback");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLuint a1 = (GLuint)arg32(&a);
    p(a0, a1);
}
void G_glBindVertexArray(CPU *c) { RT_PRIMEIRA("glBindVertexArray");
    static void (*p)(GLuint); if (!p) p = gl_proc("glBindVertexArray");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    p(a0);
}
void G_glBindVertexArrayOES(CPU *c) { RT_PRIMEIRA("glBindVertexArrayOES");
    static void (*p)(GLuint); if (!p) p = gl_proc("glBindVertexArrayOES");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    p(a0);
}
void G_glBindVertexBuffer(CPU *c) { RT_PRIMEIRA("glBindVertexBuffer");
    static void (*p)(GLuint, GLuint, GLintptr, GLsizei); if (!p) p = gl_proc("glBindVertexBuffer");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLuint a1 = (GLuint)arg32(&a);
    GLintptr a2 = (GLintptr)(int32_t)arg32(&a);
    GLsizei a3 = (GLsizei)arg32(&a);
#ifdef MGS2_DEPURA
    { static int _n; if (_n++ < 40) rt_log("glBindVertexBuffer(%u buf %u desloc %d passo %d)", a0,a1,(int)a2,a3); }
#endif
    p(a0, a1, a2, a3);
}
void G_glBlendBarrier(CPU *c) { RT_PRIMEIRA("glBlendBarrier");
    static void (*p)(void); if (!p) p = gl_proc("glBlendBarrier");
    Args a = args_de(c); (void)a;
    p();
}
void G_glBlendBarrierKHR(CPU *c) { RT_PRIMEIRA("glBlendBarrierKHR");
    static void (*p)(void); if (!p) p = gl_proc("glBlendBarrierKHR");
    Args a = args_de(c); (void)a;
    p();
}
void G_glBlendBarrierNV(CPU *c) { RT_PRIMEIRA("glBlendBarrierNV");
    static void (*p)(void); if (!p) p = gl_proc("glBlendBarrierNV");
    Args a = args_de(c); (void)a;
    p();
}
void G_glBlendColor(CPU *c) { RT_PRIMEIRA("glBlendColor");
    static void (*p)(GLfloat, GLfloat, GLfloat, GLfloat); if (!p) p = gl_proc("glBlendColor");
    Args a = args_de(c); (void)a;
    GLfloat a0 = argf(&a);
    GLfloat a1 = argf(&a);
    GLfloat a2 = argf(&a);
    GLfloat a3 = argf(&a);
    p(a0, a1, a2, a3);
}
void G_glBlendEquation(CPU *c) { RT_PRIMEIRA("glBlendEquation");
    static void (*p)(GLenum); if (!p) p = gl_proc("glBlendEquation");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    p(a0);
}
void G_glBlendEquationSeparate(CPU *c) { RT_PRIMEIRA("glBlendEquationSeparate");
    static void (*p)(GLenum, GLenum); if (!p) p = gl_proc("glBlendEquationSeparate");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    p(a0, a1);
}
void G_glBlendEquationSeparatei(CPU *c) { RT_PRIMEIRA("glBlendEquationSeparatei");
    static void (*p)(GLuint, GLenum, GLenum); if (!p) p = gl_proc("glBlendEquationSeparatei");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLenum a2 = (GLenum)arg32(&a);
    p(a0, a1, a2);
}
void G_glBlendEquationSeparateiEXT(CPU *c) { RT_PRIMEIRA("glBlendEquationSeparateiEXT");
    static void (*p)(GLuint, GLenum, GLenum); if (!p) p = gl_proc("glBlendEquationSeparateiEXT");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLenum a2 = (GLenum)arg32(&a);
    p(a0, a1, a2);
}
void G_glBlendEquationSeparateiOES(CPU *c) { RT_PRIMEIRA("glBlendEquationSeparateiOES");
    static void (*p)(GLuint, GLenum, GLenum); if (!p) p = gl_proc("glBlendEquationSeparateiOES");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLenum a2 = (GLenum)arg32(&a);
    p(a0, a1, a2);
}
void G_glBlendEquationi(CPU *c) { RT_PRIMEIRA("glBlendEquationi");
    static void (*p)(GLuint, GLenum); if (!p) p = gl_proc("glBlendEquationi");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    p(a0, a1);
}
void G_glBlendEquationiEXT(CPU *c) { RT_PRIMEIRA("glBlendEquationiEXT");
    static void (*p)(GLuint, GLenum); if (!p) p = gl_proc("glBlendEquationiEXT");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    p(a0, a1);
}
void G_glBlendEquationiOES(CPU *c) { RT_PRIMEIRA("glBlendEquationiOES");
    static void (*p)(GLuint, GLenum); if (!p) p = gl_proc("glBlendEquationiOES");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    p(a0, a1);
}
void G_glBlendFunc(CPU *c) { RT_PRIMEIRA("glBlendFunc");
    static void (*p)(GLenum, GLenum); if (!p) p = gl_proc("glBlendFunc");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    p(a0, a1);
}
void G_glBlendFuncSeparate(CPU *c) { RT_PRIMEIRA("glBlendFuncSeparate");
    static void (*p)(GLenum, GLenum, GLenum, GLenum); if (!p) p = gl_proc("glBlendFuncSeparate");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLenum a2 = (GLenum)arg32(&a);
    GLenum a3 = (GLenum)arg32(&a);
    p(a0, a1, a2, a3);
}
void G_glBlendFuncSeparatei(CPU *c) { RT_PRIMEIRA("glBlendFuncSeparatei");
    static void (*p)(GLuint, GLenum, GLenum, GLenum, GLenum); if (!p) p = gl_proc("glBlendFuncSeparatei");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLenum a2 = (GLenum)arg32(&a);
    GLenum a3 = (GLenum)arg32(&a);
    GLenum a4 = (GLenum)arg32(&a);
    p(a0, a1, a2, a3, a4);
}
void G_glBlendFuncSeparateiEXT(CPU *c) { RT_PRIMEIRA("glBlendFuncSeparateiEXT");
    static void (*p)(GLuint, GLenum, GLenum, GLenum, GLenum); if (!p) p = gl_proc("glBlendFuncSeparateiEXT");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLenum a2 = (GLenum)arg32(&a);
    GLenum a3 = (GLenum)arg32(&a);
    GLenum a4 = (GLenum)arg32(&a);
    p(a0, a1, a2, a3, a4);
}
void G_glBlendFuncSeparateiOES(CPU *c) { RT_PRIMEIRA("glBlendFuncSeparateiOES");
    static void (*p)(GLuint, GLenum, GLenum, GLenum, GLenum); if (!p) p = gl_proc("glBlendFuncSeparateiOES");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLenum a2 = (GLenum)arg32(&a);
    GLenum a3 = (GLenum)arg32(&a);
    GLenum a4 = (GLenum)arg32(&a);
    p(a0, a1, a2, a3, a4);
}
void G_glBlendFunci(CPU *c) { RT_PRIMEIRA("glBlendFunci");
    static void (*p)(GLuint, GLenum, GLenum); if (!p) p = gl_proc("glBlendFunci");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLenum a2 = (GLenum)arg32(&a);
    p(a0, a1, a2);
}
void G_glBlendFunciEXT(CPU *c) { RT_PRIMEIRA("glBlendFunciEXT");
    static void (*p)(GLuint, GLenum, GLenum); if (!p) p = gl_proc("glBlendFunciEXT");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLenum a2 = (GLenum)arg32(&a);
    p(a0, a1, a2);
}
void G_glBlendFunciOES(CPU *c) { RT_PRIMEIRA("glBlendFunciOES");
    static void (*p)(GLuint, GLenum, GLenum); if (!p) p = gl_proc("glBlendFunciOES");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLenum a2 = (GLenum)arg32(&a);
    p(a0, a1, a2);
}
void G_glBlendParameteriNV(CPU *c) { RT_PRIMEIRA("glBlendParameteriNV");
    static void (*p)(GLenum, GLint); if (!p) p = gl_proc("glBlendParameteriNV");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    p(a0, a1);
}
void G_glBlitFramebuffer(CPU *c) { RT_PRIMEIRA("glBlitFramebuffer");
    if (!pq_desenha()) return;   /* quadro pulado (pulo.c) */
    static void (*p)(GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLbitfield, GLenum); if (!p) p = gl_proc("glBlitFramebuffer");
    Args a = args_de(c); (void)a;
    GLint a0 = (GLint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLint a2 = (GLint)arg32(&a);
    GLint a3 = (GLint)arg32(&a);
    GLint a4 = (GLint)arg32(&a);
    GLint a5 = (GLint)arg32(&a);
    GLint a6 = (GLint)arg32(&a);
    GLint a7 = (GLint)arg32(&a);
    GLbitfield a8 = (GLbitfield)arg32(&a);
    GLenum a9 = (GLenum)arg32(&a);
#ifdef MGS2_DEPURA
    { static int _n; if (_n++ < 40) { GLint _fb = 0; glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &_fb); rt_log("glBlitFramebuffer(%d,%d-%d,%d -> %d,%d-%d,%d m %x f %x) fbo %d", a0,a1,a2,a3,a4,a5,a6,a7,a8,a9, _fb); } }
#endif
#ifdef MGS2_DEPURA
    {   /* medicao: salva a imagem de origem do blit (FBO do jogo) uma vez, depois de ~8 s */
        static int n; n++;
        if (n == 900) {
            GLint rfb = 0; glGetIntegerv(GL_READ_FRAMEBUFFER_BINDING, &rfb);
            int w = a2 - a0, h = a3 - a1;
            uint8_t *px = malloc((size_t)w * h * 4);
            glReadPixels(a0, a1, w, h, GL_RGBA, GL_UNSIGNED_BYTE, px);
            FILE *f = fopen("/sdcard/Android/data/jp.konami.mgs2hd.shield/files/fbo_origem.rgba", "wb");
            if (f) { fwrite(px, 1, (size_t)w * h * 4, f); fclose(f); }
            free(px);
            EGLint sw = 0, sh = 0; eglQuerySurface(eglGetCurrentDisplay(), eglGetCurrentSurface(EGL_DRAW), EGL_WIDTH, &sw);
            eglQuerySurface(eglGetCurrentDisplay(), eglGetCurrentSurface(EGL_DRAW), EGL_HEIGHT, &sh);
            rt_log("fbo_origem salvo: fbo leitura %d, %dx%d; superficie %dx%d", rfb, w, h, sw, sh);
        }
    }
#endif
    {   /* geracao de quadros ligada: o quadro vai para o AHardwareBuffer do Vulkan */
        typedef void (*BlitFn)(GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLbitfield, GLenum);
        int fg_gl_blit(BlitFn p, GLint a0, GLint a1, GLint a2, GLint a3, GLint a4, GLint a5, GLint a6, GLint a7);
        GLint dfb = 0; glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &dfb);
        if (!dfb && (a8 & GL_COLOR_BUFFER_BIT) && fg_gl_blit(p, a0, a1, a2, a3, a4, a5, a6, a7)) {
#ifdef MGS2_MALI
            static const GLenum ds[] = { GL_DEPTH_ATTACHMENT, GL_STENCIL_ATTACHMENT };
            glInvalidateFramebuffer(GL_READ_FRAMEBUFFER, 2, ds);
#endif
            return;
        }
    }
    {   /* destino = janela: retangulo com a proporcao da origem, centrado, faixas pretas */
        GLint dfb = 0; glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &dfb);
        extern int g_jan_w;
        if (!dfb && g_jan_w > 0) {
            EGLint sw = 0, sh = 0; EGLDisplay dp = eglGetCurrentDisplay(); EGLSurface sf = eglGetCurrentSurface(EGL_DRAW);
            eglQuerySurface(dp, sf, EGL_WIDTH, &sw); eglQuerySurface(dp, sf, EGL_HEIGHT, &sh);
            int ow = a2 > a0 ? a2 - a0 : a0 - a2, oh = a3 > a1 ? a3 - a1 : a1 - a3;
            if (sw > 0 && sh > 0 && ow > 0 && oh > 0) {
                int w = sw, h = (int)((long)sw * oh / ow);
                if (h > sh) { h = sh; w = (int)((long)sh * ow / oh); }
                { int aj_int(const char *chave, int padrao); static int esticar = -1;
                  if (esticar < 0) esticar = aj_int("esticar", 0);
                  if (esticar) { w = sw; h = sh; } }   /* ajuste "Esticar para a tela" */
                int x = (sw - w) / 2, y = (sh - h) / 2;
                GLboolean tes = glIsEnabled(GL_SCISSOR_TEST); glDisable(GL_SCISSOR_TEST);
                GLfloat cc[4]; glGetFloatv(GL_COLOR_CLEAR_VALUE, cc);
                glClearColor(0, 0, 0, 1); glClear(GL_COLOR_BUFFER_BIT);
                glClearColor(cc[0], cc[1], cc[2], cc[3]);
                if (tes) glEnable(GL_SCISSOR_TEST);
                /* preserva o sentido (o jogo inverte Y no blit) */
                GLint nx0 = a6 >= a4 ? x : x + w, nx1 = a6 >= a4 ? x + w : x;
                GLint ny0 = a7 >= a5 ? y : y + h, ny1 = a7 >= a5 ? y + h : y;
                a4 = nx0; a6 = nx1; a5 = ny0; a7 = ny1;
                if (a9 == GL_NEAREST && (w != ow || h != oh)) a9 = GL_LINEAR;   /* escala: filtra */
                a8 &= GL_COLOR_BUFFER_BIT;   /* profundidade/estencil nao escalam */
            }
        }
    }
    p(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9);
#ifdef MGS2_MALI
    {   /* GPU de ladrilhos (Mali): o blit para a janela e o fim do quadro do jogo; sem isto a
         * profundidade/estencil do FBO do jogo e gravada de volta na memoria a cada quadro */
        GLint dfb = 0; glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &dfb);
        if (!dfb) {
            static const GLenum ds[] = { GL_DEPTH_ATTACHMENT, GL_STENCIL_ATTACHMENT };
            glInvalidateFramebuffer(GL_READ_FRAMEBUFFER, 2, ds);
        }
    }
#endif
}
void G_glBlitFramebufferANGLE(CPU *c) { RT_PRIMEIRA("glBlitFramebufferANGLE");
    if (!pq_desenha()) return;   /* quadro pulado (pulo.c) */
    static void (*p)(GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLbitfield, GLenum); if (!p) p = gl_proc("glBlitFramebufferANGLE");
    Args a = args_de(c); (void)a;
    GLint a0 = (GLint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLint a2 = (GLint)arg32(&a);
    GLint a3 = (GLint)arg32(&a);
    GLint a4 = (GLint)arg32(&a);
    GLint a5 = (GLint)arg32(&a);
    GLint a6 = (GLint)arg32(&a);
    GLint a7 = (GLint)arg32(&a);
    GLbitfield a8 = (GLbitfield)arg32(&a);
    GLenum a9 = (GLenum)arg32(&a);
    p(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9);
}
void G_glBlitFramebufferNV(CPU *c) { RT_PRIMEIRA("glBlitFramebufferNV");
    if (!pq_desenha()) return;   /* quadro pulado (pulo.c) */
    static void (*p)(GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLbitfield, GLenum); if (!p) p = gl_proc("glBlitFramebufferNV");
    Args a = args_de(c); (void)a;
    GLint a0 = (GLint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLint a2 = (GLint)arg32(&a);
    GLint a3 = (GLint)arg32(&a);
    GLint a4 = (GLint)arg32(&a);
    GLint a5 = (GLint)arg32(&a);
    GLint a6 = (GLint)arg32(&a);
    GLint a7 = (GLint)arg32(&a);
    GLbitfield a8 = (GLbitfield)arg32(&a);
    GLenum a9 = (GLenum)arg32(&a);
    p(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9);
}
void G_glBufferData(CPU *c) { RT_PRIMEIRA("glBufferData");
    static void (*p)(GLenum, GLsizeiptr, const void *, GLenum); if (!p) p = gl_proc("glBufferData");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLsizeiptr a1 = (GLsizeiptr)(int32_t)arg32(&a);
    const void * a2 = (const void *)G2H(arg32(&a));
    GLenum a3 = (GLenum)arg32(&a);
    { extern volatile long long g_est[12]; g_est[5] += (long long)a1; }
    p(a0, a1, a2, a3);
}
void G_glBufferStorageExternalEXT(CPU *c) { RT_PRIMEIRA("glBufferStorageExternalEXT");
    static void (*p)(GLenum, GLintptr, GLsizeiptr, GLeglClientBufferEXT, GLbitfield); if (!p) p = gl_proc("glBufferStorageExternalEXT");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLintptr a1 = (GLintptr)(int32_t)arg32(&a);
    GLsizeiptr a2 = (GLsizeiptr)(int32_t)arg32(&a);
    GLeglClientBufferEXT a3 = (GLeglClientBufferEXT)egl_obj(arg32(&a));
    GLbitfield a4 = (GLbitfield)arg32(&a);
    p(a0, a1, a2, a3, a4);
}
void G_glBufferStorageMemEXT(CPU *c) { RT_PRIMEIRA("glBufferStorageMemEXT");
    static void (*p)(GLenum, GLsizeiptr, GLuint, GLuint64); if (!p) p = gl_proc("glBufferStorageMemEXT");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLsizeiptr a1 = (GLsizeiptr)(int32_t)arg32(&a);
    GLuint a2 = (GLuint)arg32(&a);
    GLuint64 a3 = (GLuint64)arg64(&a);
    p(a0, a1, a2, a3);
}
void G_glBufferSubData(CPU *c) { RT_PRIMEIRA("glBufferSubData");
    static void (*p)(GLenum, GLintptr, GLsizeiptr, const void *); if (!p) p = gl_proc("glBufferSubData");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLintptr a1 = (GLintptr)(int32_t)arg32(&a);
    GLsizeiptr a2 = (GLsizeiptr)(int32_t)arg32(&a);
    const void * a3 = (const void *)G2H(arg32(&a));
    { extern volatile long long g_est[12]; g_est[6] += (long long)a2; }
    p(a0, a1, a2, a3);
}
void G_glCheckFramebufferStatus(CPU *c) { RT_PRIMEIRA("glCheckFramebufferStatus");
    static GLenum (*p)(GLenum); if (!p) p = gl_proc("glCheckFramebufferStatus");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    ret32(c, (uint32_t)p(a0));
}
void G_glClear(CPU *c) { RT_PRIMEIRA("glClear");
    if (!pq_desenha()) return;   /* quadro pulado (pulo.c) */
    static void (*p)(GLbitfield); if (!p) p = gl_proc("glClear");
    Args a = args_de(c); (void)a;
    GLbitfield a0 = (GLbitfield)arg32(&a);
    p(a0);
}
void G_glClearBufferfi(CPU *c) { RT_PRIMEIRA("glClearBufferfi");
    if (!pq_desenha()) return;   /* quadro pulado (pulo.c) */
    static void (*p)(GLenum, GLint, GLfloat, GLint); if (!p) p = gl_proc("glClearBufferfi");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLfloat a2 = argf(&a);
    GLint a3 = (GLint)arg32(&a);
    p(a0, a1, a2, a3);
}
void G_glClearBufferfv(CPU *c) { RT_PRIMEIRA("glClearBufferfv");
    if (!pq_desenha()) return;   /* quadro pulado (pulo.c) */
    static void (*p)(GLenum, GLint, const GLfloat *); if (!p) p = gl_proc("glClearBufferfv");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    const GLfloat * a2 = (const GLfloat *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glClearBufferiv(CPU *c) { RT_PRIMEIRA("glClearBufferiv");
    if (!pq_desenha()) return;   /* quadro pulado (pulo.c) */
    static void (*p)(GLenum, GLint, const GLint *); if (!p) p = gl_proc("glClearBufferiv");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    const GLint * a2 = (const GLint *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glClearBufferuiv(CPU *c) { RT_PRIMEIRA("glClearBufferuiv");
    if (!pq_desenha()) return;   /* quadro pulado (pulo.c) */
    static void (*p)(GLenum, GLint, const GLuint *); if (!p) p = gl_proc("glClearBufferuiv");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    const GLuint * a2 = (const GLuint *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glClearColor(CPU *c) { RT_PRIMEIRA("glClearColor");
    static void (*p)(GLfloat, GLfloat, GLfloat, GLfloat); if (!p) p = gl_proc("glClearColor");
    Args a = args_de(c); (void)a;
    GLfloat a0 = argf(&a);
    GLfloat a1 = argf(&a);
    GLfloat a2 = argf(&a);
    GLfloat a3 = argf(&a);
    p(a0, a1, a2, a3);
}
void G_glClearDepthf(CPU *c) { RT_PRIMEIRA("glClearDepthf");
    static void (*p)(GLfloat); if (!p) p = gl_proc("glClearDepthf");
    Args a = args_de(c); (void)a;
    GLfloat a0 = argf(&a);
    p(a0);
}
void G_glClearPixelLocalStorageuiEXT(CPU *c) { RT_PRIMEIRA("glClearPixelLocalStorageuiEXT");
    static void (*p)(GLsizei, GLsizei, const GLuint *); if (!p) p = gl_proc("glClearPixelLocalStorageuiEXT");
    Args a = args_de(c); (void)a;
    GLsizei a0 = (GLsizei)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    const GLuint * a2 = (const GLuint *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glClearStencil(CPU *c) { RT_PRIMEIRA("glClearStencil");
    static void (*p)(GLint); if (!p) p = gl_proc("glClearStencil");
    Args a = args_de(c); (void)a;
    GLint a0 = (GLint)arg32(&a);
    p(a0);
}
void G_glClearTexImageEXT(CPU *c) { RT_PRIMEIRA("glClearTexImageEXT");
    static void (*p)(GLuint, GLint, GLenum, GLenum, const void *); if (!p) p = gl_proc("glClearTexImageEXT");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLenum a2 = (GLenum)arg32(&a);
    GLenum a3 = (GLenum)arg32(&a);
    const void * a4 = (const void *)G2H(arg32(&a));
    p(a0, a1, a2, a3, a4);
}
void G_glClearTexSubImageEXT(CPU *c) { RT_PRIMEIRA("glClearTexSubImageEXT");
    static void (*p)(GLuint, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLenum, const void *); if (!p) p = gl_proc("glClearTexSubImageEXT");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLint a2 = (GLint)arg32(&a);
    GLint a3 = (GLint)arg32(&a);
    GLint a4 = (GLint)arg32(&a);
    GLsizei a5 = (GLsizei)arg32(&a);
    GLsizei a6 = (GLsizei)arg32(&a);
    GLsizei a7 = (GLsizei)arg32(&a);
    GLenum a8 = (GLenum)arg32(&a);
    GLenum a9 = (GLenum)arg32(&a);
    const void * a10 = (const void *)G2H(arg32(&a));
    p(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
}
void G_glClipControlEXT(CPU *c) { RT_PRIMEIRA("glClipControlEXT");
    static void (*p)(GLenum, GLenum); if (!p) p = gl_proc("glClipControlEXT");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    p(a0, a1);
}
void G_glColorMask(CPU *c) { RT_PRIMEIRA("glColorMask");
    static void (*p)(GLboolean, GLboolean, GLboolean, GLboolean); if (!p) p = gl_proc("glColorMask");
    Args a = args_de(c); (void)a;
    GLboolean a0 = (GLboolean)arg32(&a);
    GLboolean a1 = (GLboolean)arg32(&a);
    GLboolean a2 = (GLboolean)arg32(&a);
    GLboolean a3 = (GLboolean)arg32(&a);
    p(a0, a1, a2, a3);
}
void G_glColorMaski(CPU *c) { RT_PRIMEIRA("glColorMaski");
    static void (*p)(GLuint, GLboolean, GLboolean, GLboolean, GLboolean); if (!p) p = gl_proc("glColorMaski");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLboolean a1 = (GLboolean)arg32(&a);
    GLboolean a2 = (GLboolean)arg32(&a);
    GLboolean a3 = (GLboolean)arg32(&a);
    GLboolean a4 = (GLboolean)arg32(&a);
    p(a0, a1, a2, a3, a4);
}
void G_glColorMaskiEXT(CPU *c) { RT_PRIMEIRA("glColorMaskiEXT");
    static void (*p)(GLuint, GLboolean, GLboolean, GLboolean, GLboolean); if (!p) p = gl_proc("glColorMaskiEXT");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLboolean a1 = (GLboolean)arg32(&a);
    GLboolean a2 = (GLboolean)arg32(&a);
    GLboolean a3 = (GLboolean)arg32(&a);
    GLboolean a4 = (GLboolean)arg32(&a);
    p(a0, a1, a2, a3, a4);
}
void G_glColorMaskiOES(CPU *c) { RT_PRIMEIRA("glColorMaskiOES");
    static void (*p)(GLuint, GLboolean, GLboolean, GLboolean, GLboolean); if (!p) p = gl_proc("glColorMaskiOES");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLboolean a1 = (GLboolean)arg32(&a);
    GLboolean a2 = (GLboolean)arg32(&a);
    GLboolean a3 = (GLboolean)arg32(&a);
    GLboolean a4 = (GLboolean)arg32(&a);
    p(a0, a1, a2, a3, a4);
}
void G_glCompileShader(CPU *c) { RT_PRIMEIRA("glCompileShader");
    static void (*p)(GLuint); if (!p) p = gl_proc("glCompileShader");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    { extern volatile long long g_est[12]; g_est[8]++; }
    p(a0);
#ifdef MGS2_DEPURA
    {   /* medicao: erros de compilacao dos shaders da camada */
        static int n_erros; GLint ok = 1; glGetShaderiv(a0, GL_COMPILE_STATUS, &ok);
        if (!ok && __atomic_fetch_add(&n_erros, 1, __ATOMIC_RELAXED) < 5) {
            char b[600]; GLsizei l = 0; glGetShaderInfoLog(a0, sizeof b, &l, b); rt_log("glCompileShader %u falhou: %.500s", a0, b);
            GLint n = 0; glGetShaderiv(a0, GL_SHADER_SOURCE_LENGTH, &n);
            char *fonte = malloc((size_t)n + 1); glGetShaderSource(a0, n + 1, NULL, fonte);
            char nome[160]; snprintf(nome, sizeof nome, "/sdcard/Android/data/jp.konami.mgs2hd.shield/files/shader_erro_%u.txt", a0);
            FILE *f = fopen(nome, "wb"); if (f) { fputs(b, f); fputs("\n/* ==== fonte traduzido ==== */\n", f); fputs(fonte, f); fclose(f); }
            free(fonte);
        }
    }
#endif
}
void G_glConservativeRasterParameteriNV(CPU *c) { RT_PRIMEIRA("glConservativeRasterParameteriNV");
    static void (*p)(GLenum, GLint); if (!p) p = gl_proc("glConservativeRasterParameteriNV");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    p(a0, a1);
}
void G_glCopyBufferSubData(CPU *c) { RT_PRIMEIRA("glCopyBufferSubData");
    static void (*p)(GLenum, GLenum, GLintptr, GLintptr, GLsizeiptr); if (!p) p = gl_proc("glCopyBufferSubData");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLintptr a2 = (GLintptr)(int32_t)arg32(&a);
    GLintptr a3 = (GLintptr)(int32_t)arg32(&a);
    GLsizeiptr a4 = (GLsizeiptr)(int32_t)arg32(&a);
    p(a0, a1, a2, a3, a4);
}
void G_glCopyBufferSubDataNV(CPU *c) { RT_PRIMEIRA("glCopyBufferSubDataNV");
    static void (*p)(GLenum, GLenum, GLintptr, GLintptr, GLsizeiptr); if (!p) p = gl_proc("glCopyBufferSubDataNV");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLintptr a2 = (GLintptr)(int32_t)arg32(&a);
    GLintptr a3 = (GLintptr)(int32_t)arg32(&a);
    GLsizeiptr a4 = (GLsizeiptr)(int32_t)arg32(&a);
    p(a0, a1, a2, a3, a4);
}
void G_glCopyImageSubData(CPU *c) { RT_PRIMEIRA("glCopyImageSubData");
    static void (*p)(GLuint, GLenum, GLint, GLint, GLint, GLint, GLuint, GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei); if (!p) p = gl_proc("glCopyImageSubData");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLint a2 = (GLint)arg32(&a);
    GLint a3 = (GLint)arg32(&a);
    GLint a4 = (GLint)arg32(&a);
    GLint a5 = (GLint)arg32(&a);
    GLuint a6 = (GLuint)arg32(&a);
    GLenum a7 = (GLenum)arg32(&a);
    GLint a8 = (GLint)arg32(&a);
    GLint a9 = (GLint)arg32(&a);
    GLint a10 = (GLint)arg32(&a);
    GLint a11 = (GLint)arg32(&a);
    GLsizei a12 = (GLsizei)arg32(&a);
    GLsizei a13 = (GLsizei)arg32(&a);
    GLsizei a14 = (GLsizei)arg32(&a);
    p(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14);
}
void G_glCopyImageSubDataEXT(CPU *c) { RT_PRIMEIRA("glCopyImageSubDataEXT");
    static void (*p)(GLuint, GLenum, GLint, GLint, GLint, GLint, GLuint, GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei); if (!p) p = gl_proc("glCopyImageSubDataEXT");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLint a2 = (GLint)arg32(&a);
    GLint a3 = (GLint)arg32(&a);
    GLint a4 = (GLint)arg32(&a);
    GLint a5 = (GLint)arg32(&a);
    GLuint a6 = (GLuint)arg32(&a);
    GLenum a7 = (GLenum)arg32(&a);
    GLint a8 = (GLint)arg32(&a);
    GLint a9 = (GLint)arg32(&a);
    GLint a10 = (GLint)arg32(&a);
    GLint a11 = (GLint)arg32(&a);
    GLsizei a12 = (GLsizei)arg32(&a);
    GLsizei a13 = (GLsizei)arg32(&a);
    GLsizei a14 = (GLsizei)arg32(&a);
    p(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14);
}
void G_glCopyImageSubDataOES(CPU *c) { RT_PRIMEIRA("glCopyImageSubDataOES");
    static void (*p)(GLuint, GLenum, GLint, GLint, GLint, GLint, GLuint, GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei); if (!p) p = gl_proc("glCopyImageSubDataOES");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLint a2 = (GLint)arg32(&a);
    GLint a3 = (GLint)arg32(&a);
    GLint a4 = (GLint)arg32(&a);
    GLint a5 = (GLint)arg32(&a);
    GLuint a6 = (GLuint)arg32(&a);
    GLenum a7 = (GLenum)arg32(&a);
    GLint a8 = (GLint)arg32(&a);
    GLint a9 = (GLint)arg32(&a);
    GLint a10 = (GLint)arg32(&a);
    GLint a11 = (GLint)arg32(&a);
    GLsizei a12 = (GLsizei)arg32(&a);
    GLsizei a13 = (GLsizei)arg32(&a);
    GLsizei a14 = (GLsizei)arg32(&a);
    p(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14);
}
void G_glCopyPathNV(CPU *c) { RT_PRIMEIRA("glCopyPathNV");
    static void (*p)(GLuint, GLuint); if (!p) p = gl_proc("glCopyPathNV");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLuint a1 = (GLuint)arg32(&a);
    p(a0, a1);
}
void G_glCopyTexImage2D(CPU *c) { RT_PRIMEIRA("glCopyTexImage2D");
    static void (*p)(GLenum, GLint, GLenum, GLint, GLint, GLsizei, GLsizei, GLint); if (!p) p = gl_proc("glCopyTexImage2D");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLenum a2 = (GLenum)arg32(&a);
    GLint a3 = (GLint)arg32(&a);
    GLint a4 = (GLint)arg32(&a);
    GLsizei a5 = (GLsizei)arg32(&a);
    GLsizei a6 = (GLsizei)arg32(&a);
    GLint a7 = (GLint)arg32(&a);
    p(a0, a1, a2, a3, a4, a5, a6, a7);
}
void G_glCopyTexSubImage2D(CPU *c) { RT_PRIMEIRA("glCopyTexSubImage2D");
    static void (*p)(GLenum, GLint, GLint, GLint, GLint, GLint, GLsizei, GLsizei); if (!p) p = gl_proc("glCopyTexSubImage2D");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLint a2 = (GLint)arg32(&a);
    GLint a3 = (GLint)arg32(&a);
    GLint a4 = (GLint)arg32(&a);
    GLint a5 = (GLint)arg32(&a);
    GLsizei a6 = (GLsizei)arg32(&a);
    GLsizei a7 = (GLsizei)arg32(&a);
    p(a0, a1, a2, a3, a4, a5, a6, a7);
}
void G_glCopyTexSubImage3D(CPU *c) { RT_PRIMEIRA("glCopyTexSubImage3D");
    static void (*p)(GLenum, GLint, GLint, GLint, GLint, GLint, GLint, GLsizei, GLsizei); if (!p) p = gl_proc("glCopyTexSubImage3D");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLint a2 = (GLint)arg32(&a);
    GLint a3 = (GLint)arg32(&a);
    GLint a4 = (GLint)arg32(&a);
    GLint a5 = (GLint)arg32(&a);
    GLint a6 = (GLint)arg32(&a);
    GLsizei a7 = (GLsizei)arg32(&a);
    GLsizei a8 = (GLsizei)arg32(&a);
    p(a0, a1, a2, a3, a4, a5, a6, a7, a8);
}
void G_glCopyTexSubImage3DOES(CPU *c) { RT_PRIMEIRA("glCopyTexSubImage3DOES");
    static void (*p)(GLenum, GLint, GLint, GLint, GLint, GLint, GLint, GLsizei, GLsizei); if (!p) p = gl_proc("glCopyTexSubImage3DOES");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLint a2 = (GLint)arg32(&a);
    GLint a3 = (GLint)arg32(&a);
    GLint a4 = (GLint)arg32(&a);
    GLint a5 = (GLint)arg32(&a);
    GLint a6 = (GLint)arg32(&a);
    GLsizei a7 = (GLsizei)arg32(&a);
    GLsizei a8 = (GLsizei)arg32(&a);
    p(a0, a1, a2, a3, a4, a5, a6, a7, a8);
}
void G_glCopyTextureLevelsAPPLE(CPU *c) { RT_PRIMEIRA("glCopyTextureLevelsAPPLE");
    static void (*p)(GLuint, GLuint, GLint, GLsizei); if (!p) p = gl_proc("glCopyTextureLevelsAPPLE");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLuint a1 = (GLuint)arg32(&a);
    GLint a2 = (GLint)arg32(&a);
    GLsizei a3 = (GLsizei)arg32(&a);
    p(a0, a1, a2, a3);
}
void G_glCoverFillPathInstancedNV(CPU *c) { RT_PRIMEIRA("glCoverFillPathInstancedNV");
    static void (*p)(GLsizei, GLenum, const void *, GLuint, GLenum, GLenum, const GLfloat *); if (!p) p = gl_proc("glCoverFillPathInstancedNV");
    Args a = args_de(c); (void)a;
    GLsizei a0 = (GLsizei)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    const void * a2 = (const void *)G2H(arg32(&a));
    GLuint a3 = (GLuint)arg32(&a);
    GLenum a4 = (GLenum)arg32(&a);
    GLenum a5 = (GLenum)arg32(&a);
    const GLfloat * a6 = (const GLfloat *)G2H(arg32(&a));
    p(a0, a1, a2, a3, a4, a5, a6);
}
void G_glCoverFillPathNV(CPU *c) { RT_PRIMEIRA("glCoverFillPathNV");
    static void (*p)(GLuint, GLenum); if (!p) p = gl_proc("glCoverFillPathNV");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    p(a0, a1);
}
void G_glCoverStrokePathInstancedNV(CPU *c) { RT_PRIMEIRA("glCoverStrokePathInstancedNV");
    static void (*p)(GLsizei, GLenum, const void *, GLuint, GLenum, GLenum, const GLfloat *); if (!p) p = gl_proc("glCoverStrokePathInstancedNV");
    Args a = args_de(c); (void)a;
    GLsizei a0 = (GLsizei)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    const void * a2 = (const void *)G2H(arg32(&a));
    GLuint a3 = (GLuint)arg32(&a);
    GLenum a4 = (GLenum)arg32(&a);
    GLenum a5 = (GLenum)arg32(&a);
    const GLfloat * a6 = (const GLfloat *)G2H(arg32(&a));
    p(a0, a1, a2, a3, a4, a5, a6);
}
void G_glCoverStrokePathNV(CPU *c) { RT_PRIMEIRA("glCoverStrokePathNV");
    static void (*p)(GLuint, GLenum); if (!p) p = gl_proc("glCoverStrokePathNV");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    p(a0, a1);
}
void G_glCoverageMaskNV(CPU *c) { RT_PRIMEIRA("glCoverageMaskNV");
    static void (*p)(GLboolean); if (!p) p = gl_proc("glCoverageMaskNV");
    Args a = args_de(c); (void)a;
    GLboolean a0 = (GLboolean)arg32(&a);
    p(a0);
}
void G_glCoverageModulationNV(CPU *c) { RT_PRIMEIRA("glCoverageModulationNV");
    static void (*p)(GLenum); if (!p) p = gl_proc("glCoverageModulationNV");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    p(a0);
}
void G_glCoverageModulationTableNV(CPU *c) { RT_PRIMEIRA("glCoverageModulationTableNV");
    static void (*p)(GLsizei, const GLfloat *); if (!p) p = gl_proc("glCoverageModulationTableNV");
    Args a = args_de(c); (void)a;
    GLsizei a0 = (GLsizei)arg32(&a);
    const GLfloat * a1 = (const GLfloat *)G2H(arg32(&a));
    p(a0, a1);
}
void G_glCoverageOperationNV(CPU *c) { RT_PRIMEIRA("glCoverageOperationNV");
    static void (*p)(GLenum); if (!p) p = gl_proc("glCoverageOperationNV");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    p(a0);
}
void G_glCreateMemoryObjectsEXT(CPU *c) { RT_PRIMEIRA("glCreateMemoryObjectsEXT");
    static void (*p)(GLsizei, GLuint *); if (!p) p = gl_proc("glCreateMemoryObjectsEXT");
    Args a = args_de(c); (void)a;
    GLsizei a0 = (GLsizei)arg32(&a);
    GLuint * a1 = (GLuint *)G2H(arg32(&a));
    p(a0, a1);
}
void G_glCreatePerfQueryINTEL(CPU *c) { RT_PRIMEIRA("glCreatePerfQueryINTEL");
    static void (*p)(GLuint, GLuint *); if (!p) p = gl_proc("glCreatePerfQueryINTEL");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLuint * a1 = (GLuint *)G2H(arg32(&a));
    p(a0, a1);
}
void G_glCreateProgram(CPU *c) { RT_PRIMEIRA("glCreateProgram");
    static GLuint (*p)(void); if (!p) p = gl_proc("glCreateProgram");
    Args a = args_de(c); (void)a;
    ret32(c, (uint32_t)p());
}
void G_glCreateShader(CPU *c) { RT_PRIMEIRA("glCreateShader");
    static GLuint (*p)(GLenum); if (!p) p = gl_proc("glCreateShader");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    ret32(c, (uint32_t)p(a0));
}
void G_glCreateShaderProgramv(CPU *c) { RT_PRIMEIRA("glCreateShaderProgramv");
    static GLuint (*p)(GLenum, GLsizei, const GLchar *const*); if (!p) p = gl_proc("glCreateShaderProgramv");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    const GLchar *const* a2 = (const GLchar *const*)G2H(arg32(&a));
    ret32(c, (uint32_t)p(a0, a1, a2));
}
void G_glCreateShaderProgramvEXT(CPU *c) { RT_PRIMEIRA("glCreateShaderProgramvEXT");
    static GLuint (*p)(GLenum, GLsizei, const GLchar **); if (!p) p = gl_proc("glCreateShaderProgramvEXT");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    const GLchar ** a2 = (const GLchar **)G2H(arg32(&a));
    ret32(c, (uint32_t)p(a0, a1, a2));
}
void G_glCullFace(CPU *c) { RT_PRIMEIRA("glCullFace");
    static void (*p)(GLenum); if (!p) p = gl_proc("glCullFace");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    p(a0);
}
void G_glDebugMessageControl(CPU *c) { RT_PRIMEIRA("glDebugMessageControl");
    static void (*p)(GLenum, GLenum, GLenum, GLsizei, const GLuint *, GLboolean); if (!p) p = gl_proc("glDebugMessageControl");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLenum a2 = (GLenum)arg32(&a);
    GLsizei a3 = (GLsizei)arg32(&a);
    const GLuint * a4 = (const GLuint *)G2H(arg32(&a));
    GLboolean a5 = (GLboolean)arg32(&a);
    p(a0, a1, a2, a3, a4, a5);
}
void G_glDebugMessageControlKHR(CPU *c) { RT_PRIMEIRA("glDebugMessageControlKHR");
    static void (*p)(GLenum, GLenum, GLenum, GLsizei, const GLuint *, GLboolean); if (!p) p = gl_proc("glDebugMessageControlKHR");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLenum a2 = (GLenum)arg32(&a);
    GLsizei a3 = (GLsizei)arg32(&a);
    const GLuint * a4 = (const GLuint *)G2H(arg32(&a));
    GLboolean a5 = (GLboolean)arg32(&a);
    p(a0, a1, a2, a3, a4, a5);
}
void G_glDebugMessageInsert(CPU *c) { RT_PRIMEIRA("glDebugMessageInsert");
    static void (*p)(GLenum, GLenum, GLuint, GLenum, GLsizei, const GLchar *); if (!p) p = gl_proc("glDebugMessageInsert");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLuint a2 = (GLuint)arg32(&a);
    GLenum a3 = (GLenum)arg32(&a);
    GLsizei a4 = (GLsizei)arg32(&a);
    const GLchar * a5 = (const GLchar *)G2H(arg32(&a));
    p(a0, a1, a2, a3, a4, a5);
}
void G_glDebugMessageInsertKHR(CPU *c) { RT_PRIMEIRA("glDebugMessageInsertKHR");
    static void (*p)(GLenum, GLenum, GLuint, GLenum, GLsizei, const GLchar *); if (!p) p = gl_proc("glDebugMessageInsertKHR");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLuint a2 = (GLuint)arg32(&a);
    GLenum a3 = (GLenum)arg32(&a);
    GLsizei a4 = (GLsizei)arg32(&a);
    const GLchar * a5 = (const GLchar *)G2H(arg32(&a));
    p(a0, a1, a2, a3, a4, a5);
}
void G_glDeleteBuffers(CPU *c) { RT_PRIMEIRA("glDeleteBuffers");
    static void (*p)(GLsizei, const GLuint *); if (!p) p = gl_proc("glDeleteBuffers");
    Args a = args_de(c); (void)a;
    GLsizei a0 = (GLsizei)arg32(&a);
    const GLuint * a1 = (const GLuint *)G2H(arg32(&a));
    p(a0, a1);
}
void G_glDeleteFencesNV(CPU *c) { RT_PRIMEIRA("glDeleteFencesNV");
    static void (*p)(GLsizei, const GLuint *); if (!p) p = gl_proc("glDeleteFencesNV");
    Args a = args_de(c); (void)a;
    GLsizei a0 = (GLsizei)arg32(&a);
    const GLuint * a1 = (const GLuint *)G2H(arg32(&a));
    p(a0, a1);
}
void G_glDeleteFramebuffers(CPU *c) { RT_PRIMEIRA("glDeleteFramebuffers");
    static void (*p)(GLsizei, const GLuint *); if (!p) p = gl_proc("glDeleteFramebuffers");
    Args a = args_de(c); (void)a;
    GLsizei a0 = (GLsizei)arg32(&a);
    const GLuint * a1 = (const GLuint *)G2H(arg32(&a));
    pq_apaga_fbs(a0, a1);
    p(a0, a1);
}
void G_glDeleteMemoryObjectsEXT(CPU *c) { RT_PRIMEIRA("glDeleteMemoryObjectsEXT");
    static void (*p)(GLsizei, const GLuint *); if (!p) p = gl_proc("glDeleteMemoryObjectsEXT");
    Args a = args_de(c); (void)a;
    GLsizei a0 = (GLsizei)arg32(&a);
    const GLuint * a1 = (const GLuint *)G2H(arg32(&a));
    p(a0, a1);
}
void G_glDeletePathsNV(CPU *c) { RT_PRIMEIRA("glDeletePathsNV");
    static void (*p)(GLuint, GLsizei); if (!p) p = gl_proc("glDeletePathsNV");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    p(a0, a1);
}
void G_glDeletePerfMonitorsAMD(CPU *c) { RT_PRIMEIRA("glDeletePerfMonitorsAMD");
    static void (*p)(GLsizei, GLuint *); if (!p) p = gl_proc("glDeletePerfMonitorsAMD");
    Args a = args_de(c); (void)a;
    GLsizei a0 = (GLsizei)arg32(&a);
    GLuint * a1 = (GLuint *)G2H(arg32(&a));
    p(a0, a1);
}
void G_glDeletePerfQueryINTEL(CPU *c) { RT_PRIMEIRA("glDeletePerfQueryINTEL");
    static void (*p)(GLuint); if (!p) p = gl_proc("glDeletePerfQueryINTEL");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    p(a0);
}
void G_glDeleteProgram(CPU *c) { RT_PRIMEIRA("glDeleteProgram");
    static void (*p)(GLuint); if (!p) p = gl_proc("glDeleteProgram");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    p(a0);
}
void G_glDeleteProgramPipelines(CPU *c) { RT_PRIMEIRA("glDeleteProgramPipelines");
    static void (*p)(GLsizei, const GLuint *); if (!p) p = gl_proc("glDeleteProgramPipelines");
    Args a = args_de(c); (void)a;
    GLsizei a0 = (GLsizei)arg32(&a);
    const GLuint * a1 = (const GLuint *)G2H(arg32(&a));
    p(a0, a1);
}
void G_glDeleteProgramPipelinesEXT(CPU *c) { RT_PRIMEIRA("glDeleteProgramPipelinesEXT");
    static void (*p)(GLsizei, const GLuint *); if (!p) p = gl_proc("glDeleteProgramPipelinesEXT");
    Args a = args_de(c); (void)a;
    GLsizei a0 = (GLsizei)arg32(&a);
    const GLuint * a1 = (const GLuint *)G2H(arg32(&a));
    p(a0, a1);
}
void G_glDeleteQueries(CPU *c) { RT_PRIMEIRA("glDeleteQueries");
    static void (*p)(GLsizei, const GLuint *); if (!p) p = gl_proc("glDeleteQueries");
    Args a = args_de(c); (void)a;
    GLsizei a0 = (GLsizei)arg32(&a);
    const GLuint * a1 = (const GLuint *)G2H(arg32(&a));
    p(a0, a1);
}
void G_glDeleteQueriesEXT(CPU *c) { RT_PRIMEIRA("glDeleteQueriesEXT");
    static void (*p)(GLsizei, const GLuint *); if (!p) p = gl_proc("glDeleteQueriesEXT");
    Args a = args_de(c); (void)a;
    GLsizei a0 = (GLsizei)arg32(&a);
    const GLuint * a1 = (const GLuint *)G2H(arg32(&a));
    p(a0, a1);
}
void G_glDeleteRenderbuffers(CPU *c) { RT_PRIMEIRA("glDeleteRenderbuffers");
    static void (*p)(GLsizei, const GLuint *); if (!p) p = gl_proc("glDeleteRenderbuffers");
    Args a = args_de(c); (void)a;
    GLsizei a0 = (GLsizei)arg32(&a);
    const GLuint * a1 = (const GLuint *)G2H(arg32(&a));
    p(a0, a1);
}
void G_glDeleteSamplers(CPU *c) { RT_PRIMEIRA("glDeleteSamplers");
    static void (*p)(GLsizei, const GLuint *); if (!p) p = gl_proc("glDeleteSamplers");
    Args a = args_de(c); (void)a;
    GLsizei a0 = (GLsizei)arg32(&a);
    const GLuint * a1 = (const GLuint *)G2H(arg32(&a));
    p(a0, a1);
}
void G_glDeleteSemaphoresEXT(CPU *c) { RT_PRIMEIRA("glDeleteSemaphoresEXT");
    static void (*p)(GLsizei, const GLuint *); if (!p) p = gl_proc("glDeleteSemaphoresEXT");
    Args a = args_de(c); (void)a;
    GLsizei a0 = (GLsizei)arg32(&a);
    const GLuint * a1 = (const GLuint *)G2H(arg32(&a));
    p(a0, a1);
}
void G_glDeleteShader(CPU *c) { RT_PRIMEIRA("glDeleteShader");
    static void (*p)(GLuint); if (!p) p = gl_proc("glDeleteShader");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    p(a0);
}
void G_glDeleteTextures(CPU *c) { RT_PRIMEIRA("glDeleteTextures");
    static void (*p)(GLsizei, const GLuint *); if (!p) p = gl_proc("glDeleteTextures");
    Args a = args_de(c); (void)a;
    GLsizei a0 = (GLsizei)arg32(&a);
    const GLuint * a1 = (const GLuint *)G2H(arg32(&a));
    p(a0, a1);
}
void G_glDeleteTransformFeedbacks(CPU *c) { RT_PRIMEIRA("glDeleteTransformFeedbacks");
    static void (*p)(GLsizei, const GLuint *); if (!p) p = gl_proc("glDeleteTransformFeedbacks");
    Args a = args_de(c); (void)a;
    GLsizei a0 = (GLsizei)arg32(&a);
    const GLuint * a1 = (const GLuint *)G2H(arg32(&a));
    p(a0, a1);
}
void G_glDeleteVertexArrays(CPU *c) { RT_PRIMEIRA("glDeleteVertexArrays");
    static void (*p)(GLsizei, const GLuint *); if (!p) p = gl_proc("glDeleteVertexArrays");
    Args a = args_de(c); (void)a;
    GLsizei a0 = (GLsizei)arg32(&a);
    const GLuint * a1 = (const GLuint *)G2H(arg32(&a));
    p(a0, a1);
}
void G_glDeleteVertexArraysOES(CPU *c) { RT_PRIMEIRA("glDeleteVertexArraysOES");
    static void (*p)(GLsizei, const GLuint *); if (!p) p = gl_proc("glDeleteVertexArraysOES");
    Args a = args_de(c); (void)a;
    GLsizei a0 = (GLsizei)arg32(&a);
    const GLuint * a1 = (const GLuint *)G2H(arg32(&a));
    p(a0, a1);
}
void G_glDepthFunc(CPU *c) { RT_PRIMEIRA("glDepthFunc");
    static void (*p)(GLenum); if (!p) p = gl_proc("glDepthFunc");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    p(a0);
}
void G_glDepthMask(CPU *c) { RT_PRIMEIRA("glDepthMask");
    static void (*p)(GLboolean); if (!p) p = gl_proc("glDepthMask");
    Args a = args_de(c); (void)a;
    GLboolean a0 = (GLboolean)arg32(&a);
    p(a0);
}
void G_glDepthRangeArrayfvNV(CPU *c) { RT_PRIMEIRA("glDepthRangeArrayfvNV");
    static void (*p)(GLuint, GLsizei, const GLfloat *); if (!p) p = gl_proc("glDepthRangeArrayfvNV");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    const GLfloat * a2 = (const GLfloat *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glDepthRangeArrayfvOES(CPU *c) { RT_PRIMEIRA("glDepthRangeArrayfvOES");
    static void (*p)(GLuint, GLsizei, const GLfloat *); if (!p) p = gl_proc("glDepthRangeArrayfvOES");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    const GLfloat * a2 = (const GLfloat *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glDepthRangeIndexedfNV(CPU *c) { RT_PRIMEIRA("glDepthRangeIndexedfNV");
    static void (*p)(GLuint, GLfloat, GLfloat); if (!p) p = gl_proc("glDepthRangeIndexedfNV");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLfloat a1 = argf(&a);
    GLfloat a2 = argf(&a);
    p(a0, a1, a2);
}
void G_glDepthRangeIndexedfOES(CPU *c) { RT_PRIMEIRA("glDepthRangeIndexedfOES");
    static void (*p)(GLuint, GLfloat, GLfloat); if (!p) p = gl_proc("glDepthRangeIndexedfOES");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLfloat a1 = argf(&a);
    GLfloat a2 = argf(&a);
    p(a0, a1, a2);
}
void G_glDepthRangef(CPU *c) { RT_PRIMEIRA("glDepthRangef");
    static void (*p)(GLfloat, GLfloat); if (!p) p = gl_proc("glDepthRangef");
    Args a = args_de(c); (void)a;
    GLfloat a0 = argf(&a);
    GLfloat a1 = argf(&a);
    p(a0, a1);
}
void G_glDetachShader(CPU *c) { RT_PRIMEIRA("glDetachShader");
    static void (*p)(GLuint, GLuint); if (!p) p = gl_proc("glDetachShader");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLuint a1 = (GLuint)arg32(&a);
    p(a0, a1);
}
void G_glDisable(CPU *c) { RT_PRIMEIRA("glDisable");
    static void (*p)(GLenum); if (!p) p = gl_proc("glDisable");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
#ifdef MGS2_DEPURA
    if (a0 == 0x8DB9) { static int n; if (n++ < 6) rt_log("glDisable(GL_FRAMEBUFFER_SRGB)"); }
#endif
    p(a0);
}
void G_glDisableDriverControlQCOM(CPU *c) { RT_PRIMEIRA("glDisableDriverControlQCOM");
    static void (*p)(GLuint); if (!p) p = gl_proc("glDisableDriverControlQCOM");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    p(a0);
}
void G_glDisableVertexAttribArray(CPU *c) { RT_PRIMEIRA("glDisableVertexAttribArray");
    static void (*p)(GLuint); if (!p) p = gl_proc("glDisableVertexAttribArray");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    p(a0);
}
void G_glDisablei(CPU *c) { RT_PRIMEIRA("glDisablei");
    static void (*p)(GLenum, GLuint); if (!p) p = gl_proc("glDisablei");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLuint a1 = (GLuint)arg32(&a);
    p(a0, a1);
}
void G_glDisableiEXT(CPU *c) { RT_PRIMEIRA("glDisableiEXT");
    static void (*p)(GLenum, GLuint); if (!p) p = gl_proc("glDisableiEXT");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLuint a1 = (GLuint)arg32(&a);
    p(a0, a1);
}
void G_glDisableiNV(CPU *c) { RT_PRIMEIRA("glDisableiNV");
    static void (*p)(GLenum, GLuint); if (!p) p = gl_proc("glDisableiNV");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLuint a1 = (GLuint)arg32(&a);
    p(a0, a1);
}
void G_glDisableiOES(CPU *c) { RT_PRIMEIRA("glDisableiOES");
    static void (*p)(GLenum, GLuint); if (!p) p = gl_proc("glDisableiOES");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLuint a1 = (GLuint)arg32(&a);
    p(a0, a1);
}
void G_glDiscardFramebufferEXT(CPU *c) { RT_PRIMEIRA("glDiscardFramebufferEXT");
    static void (*p)(GLenum, GLsizei, const GLenum *); if (!p) p = gl_proc("glDiscardFramebufferEXT");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    const GLenum * a2 = (const GLenum *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glDispatchCompute(CPU *c) { RT_PRIMEIRA("glDispatchCompute");
    static void (*p)(GLuint, GLuint, GLuint); if (!p) p = gl_proc("glDispatchCompute");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLuint a1 = (GLuint)arg32(&a);
    GLuint a2 = (GLuint)arg32(&a);
    p(a0, a1, a2);
}
void G_glDispatchComputeIndirect(CPU *c) { RT_PRIMEIRA("glDispatchComputeIndirect");
    static void (*p)(GLintptr); if (!p) p = gl_proc("glDispatchComputeIndirect");
    Args a = args_de(c); (void)a;
    GLintptr a0 = (GLintptr)(int32_t)arg32(&a);
    p(a0);
}
void G_glDrawArrays(CPU *c) { RT_PRIMEIRA("glDrawArrays");
    if (!pq_desenha()) return;   /* quadro pulado (pulo.c) */
    static void (*p)(GLenum, GLint, GLsizei); if (!p) p = gl_proc("glDrawArrays");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
#ifdef MGS2_DEPURA
    { void gl_mostra_vertices(const char *, GLint); gl_mostra_vertices("DrawArrays", a1); }
#endif
    { extern volatile long long g_est[12]; g_est[4]++; }
    p(a0, a1, a2);
}
void G_glDrawArraysInstanced(CPU *c) { RT_PRIMEIRA("glDrawArraysInstanced");
    if (!pq_desenha()) return;   /* quadro pulado (pulo.c) */
    static void (*p)(GLenum, GLint, GLsizei, GLsizei); if (!p) p = gl_proc("glDrawArraysInstanced");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    GLsizei a3 = (GLsizei)arg32(&a);
    p(a0, a1, a2, a3);
}
void G_glDrawArraysInstancedANGLE(CPU *c) { RT_PRIMEIRA("glDrawArraysInstancedANGLE");
    if (!pq_desenha()) return;   /* quadro pulado (pulo.c) */
    static void (*p)(GLenum, GLint, GLsizei, GLsizei); if (!p) p = gl_proc("glDrawArraysInstancedANGLE");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    GLsizei a3 = (GLsizei)arg32(&a);
    p(a0, a1, a2, a3);
}
void G_glDrawArraysInstancedBaseInstanceEXT(CPU *c) { RT_PRIMEIRA("glDrawArraysInstancedBaseInstanceEXT");
    if (!pq_desenha()) return;   /* quadro pulado (pulo.c) */
    static void (*p)(GLenum, GLint, GLsizei, GLsizei, GLuint); if (!p) p = gl_proc("glDrawArraysInstancedBaseInstanceEXT");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    GLsizei a3 = (GLsizei)arg32(&a);
    GLuint a4 = (GLuint)arg32(&a);
    p(a0, a1, a2, a3, a4);
}
void G_glDrawArraysInstancedEXT(CPU *c) { RT_PRIMEIRA("glDrawArraysInstancedEXT");
    if (!pq_desenha()) return;   /* quadro pulado (pulo.c) */
    static void (*p)(GLenum, GLint, GLsizei, GLsizei); if (!p) p = gl_proc("glDrawArraysInstancedEXT");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    GLsizei a3 = (GLsizei)arg32(&a);
    p(a0, a1, a2, a3);
}
void G_glDrawArraysInstancedNV(CPU *c) { RT_PRIMEIRA("glDrawArraysInstancedNV");
    if (!pq_desenha()) return;   /* quadro pulado (pulo.c) */
    static void (*p)(GLenum, GLint, GLsizei, GLsizei); if (!p) p = gl_proc("glDrawArraysInstancedNV");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    GLsizei a3 = (GLsizei)arg32(&a);
    p(a0, a1, a2, a3);
}
void G_glDrawBuffers(CPU *c) { RT_PRIMEIRA("glDrawBuffers");
    static void (*p)(GLsizei, const GLenum *); if (!p) p = gl_proc("glDrawBuffers");
    Args a = args_de(c); (void)a;
    GLsizei a0 = (GLsizei)arg32(&a);
    const GLenum * a1 = (const GLenum *)G2H(arg32(&a));
    p(a0, a1);
}
void G_glDrawBuffersEXT(CPU *c) { RT_PRIMEIRA("glDrawBuffersEXT");
    static void (*p)(GLsizei, const GLenum *); if (!p) p = gl_proc("glDrawBuffersEXT");
    Args a = args_de(c); (void)a;
    GLsizei a0 = (GLsizei)arg32(&a);
    const GLenum * a1 = (const GLenum *)G2H(arg32(&a));
    p(a0, a1);
}
void G_glDrawBuffersIndexedEXT(CPU *c) { RT_PRIMEIRA("glDrawBuffersIndexedEXT");
    static void (*p)(GLint, const GLenum *, const GLint *); if (!p) p = gl_proc("glDrawBuffersIndexedEXT");
    Args a = args_de(c); (void)a;
    GLint a0 = (GLint)arg32(&a);
    const GLenum * a1 = (const GLenum *)G2H(arg32(&a));
    const GLint * a2 = (const GLint *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glDrawBuffersNV(CPU *c) { RT_PRIMEIRA("glDrawBuffersNV");
    static void (*p)(GLsizei, const GLenum *); if (!p) p = gl_proc("glDrawBuffersNV");
    Args a = args_de(c); (void)a;
    GLsizei a0 = (GLsizei)arg32(&a);
    const GLenum * a1 = (const GLenum *)G2H(arg32(&a));
    p(a0, a1);
}
void G_glDrawElementsInstancedBaseInstanceEXT(CPU *c) { RT_PRIMEIRA("glDrawElementsInstancedBaseInstanceEXT");
    if (!pq_desenha()) return;   /* quadro pulado (pulo.c) */
    static void (*p)(GLenum, GLsizei, GLenum, const void *, GLsizei, GLuint); if (!p) p = gl_proc("glDrawElementsInstancedBaseInstanceEXT");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    GLenum a2 = (GLenum)arg32(&a);
    const void * a3 = (const void *)G2H(arg32(&a));
    GLsizei a4 = (GLsizei)arg32(&a);
    GLuint a5 = (GLuint)arg32(&a);
    p(a0, a1, a2, a3, a4, a5);
}
void G_glDrawElementsInstancedBaseVertexBaseInstanceEXT(CPU *c) { RT_PRIMEIRA("glDrawElementsInstancedBaseVertexBaseInstanceEXT");
    if (!pq_desenha()) return;   /* quadro pulado (pulo.c) */
    static void (*p)(GLenum, GLsizei, GLenum, const void *, GLsizei, GLint, GLuint); if (!p) p = gl_proc("glDrawElementsInstancedBaseVertexBaseInstanceEXT");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    GLenum a2 = (GLenum)arg32(&a);
    const void * a3 = (const void *)G2H(arg32(&a));
    GLsizei a4 = (GLsizei)arg32(&a);
    GLint a5 = (GLint)arg32(&a);
    GLuint a6 = (GLuint)arg32(&a);
    p(a0, a1, a2, a3, a4, a5, a6);
}
void G_glDrawTransformFeedbackEXT(CPU *c) { RT_PRIMEIRA("glDrawTransformFeedbackEXT");
    if (!pq_desenha()) return;   /* quadro pulado (pulo.c) */
    static void (*p)(GLenum, GLuint); if (!p) p = gl_proc("glDrawTransformFeedbackEXT");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLuint a1 = (GLuint)arg32(&a);
    p(a0, a1);
}
void G_glDrawTransformFeedbackInstancedEXT(CPU *c) { RT_PRIMEIRA("glDrawTransformFeedbackInstancedEXT");
    if (!pq_desenha()) return;   /* quadro pulado (pulo.c) */
    static void (*p)(GLenum, GLuint, GLsizei); if (!p) p = gl_proc("glDrawTransformFeedbackInstancedEXT");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLuint a1 = (GLuint)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    p(a0, a1, a2);
}
void G_glDrawVkImageNV(CPU *c) { RT_PRIMEIRA("glDrawVkImageNV");
    if (!pq_desenha()) return;   /* quadro pulado (pulo.c) */
    static void (*p)(GLuint64, GLuint, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat); if (!p) p = gl_proc("glDrawVkImageNV");
    Args a = args_de(c); (void)a;
    GLuint64 a0 = (GLuint64)arg64(&a);
    GLuint a1 = (GLuint)arg32(&a);
    GLfloat a2 = argf(&a);
    GLfloat a3 = argf(&a);
    GLfloat a4 = argf(&a);
    GLfloat a5 = argf(&a);
    GLfloat a6 = argf(&a);
    GLfloat a7 = argf(&a);
    GLfloat a8 = argf(&a);
    GLfloat a9 = argf(&a);
    GLfloat a10 = argf(&a);
    p(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
}
void G_glEGLImageTargetTexStorageEXT(CPU *c) { RT_PRIMEIRA("glEGLImageTargetTexStorageEXT");
    static void (*p)(GLenum, GLeglImageOES, const GLint*); if (!p) p = gl_proc("glEGLImageTargetTexStorageEXT");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLeglImageOES a1 = (GLeglImageOES)egl_obj(arg32(&a));
    const GLint* a2 = (const GLint*)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glEGLImageTargetTextureStorageEXT(CPU *c) { RT_PRIMEIRA("glEGLImageTargetTextureStorageEXT");
    static void (*p)(GLuint, GLeglImageOES, const GLint*); if (!p) p = gl_proc("glEGLImageTargetTextureStorageEXT");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLeglImageOES a1 = (GLeglImageOES)egl_obj(arg32(&a));
    const GLint* a2 = (const GLint*)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glEnable(CPU *c) { RT_PRIMEIRA("glEnable");
    static void (*p)(GLenum); if (!p) p = gl_proc("glEnable");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
#ifdef MGS2_DEPURA
    if (a0 == 0x8DB9) { static int n; if (n++ < 6) rt_log("glEnable(GL_FRAMEBUFFER_SRGB)"); }
#endif
    p(a0);
}
void G_glEnableDriverControlQCOM(CPU *c) { RT_PRIMEIRA("glEnableDriverControlQCOM");
    static void (*p)(GLuint); if (!p) p = gl_proc("glEnableDriverControlQCOM");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    p(a0);
}
void G_glEnableVertexAttribArray(CPU *c) { RT_PRIMEIRA("glEnableVertexAttribArray");
    static void (*p)(GLuint); if (!p) p = gl_proc("glEnableVertexAttribArray");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    p(a0);
}
void G_glEnablei(CPU *c) { RT_PRIMEIRA("glEnablei");
    static void (*p)(GLenum, GLuint); if (!p) p = gl_proc("glEnablei");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLuint a1 = (GLuint)arg32(&a);
    p(a0, a1);
}
void G_glEnableiEXT(CPU *c) { RT_PRIMEIRA("glEnableiEXT");
    static void (*p)(GLenum, GLuint); if (!p) p = gl_proc("glEnableiEXT");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLuint a1 = (GLuint)arg32(&a);
    p(a0, a1);
}
void G_glEnableiNV(CPU *c) { RT_PRIMEIRA("glEnableiNV");
    static void (*p)(GLenum, GLuint); if (!p) p = gl_proc("glEnableiNV");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLuint a1 = (GLuint)arg32(&a);
    p(a0, a1);
}
void G_glEnableiOES(CPU *c) { RT_PRIMEIRA("glEnableiOES");
    static void (*p)(GLenum, GLuint); if (!p) p = gl_proc("glEnableiOES");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLuint a1 = (GLuint)arg32(&a);
    p(a0, a1);
}
void G_glEndConditionalRenderNV(CPU *c) { RT_PRIMEIRA("glEndConditionalRenderNV");
    static void (*p)(void); if (!p) p = gl_proc("glEndConditionalRenderNV");
    Args a = args_de(c); (void)a;
    p();
}
void G_glEndPerfMonitorAMD(CPU *c) { RT_PRIMEIRA("glEndPerfMonitorAMD");
    static void (*p)(GLuint); if (!p) p = gl_proc("glEndPerfMonitorAMD");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    p(a0);
}
void G_glEndPerfQueryINTEL(CPU *c) { RT_PRIMEIRA("glEndPerfQueryINTEL");
    static void (*p)(GLuint); if (!p) p = gl_proc("glEndPerfQueryINTEL");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    p(a0);
}
void G_glEndQuery(CPU *c) { RT_PRIMEIRA("glEndQuery");
    static void (*p)(GLenum); if (!p) p = gl_proc("glEndQuery");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    p(a0);
}
void G_glEndQueryEXT(CPU *c) { RT_PRIMEIRA("glEndQueryEXT");
    static void (*p)(GLenum); if (!p) p = gl_proc("glEndQueryEXT");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    p(a0);
}
void G_glEndTilingQCOM(CPU *c) { RT_PRIMEIRA("glEndTilingQCOM");
    static void (*p)(GLbitfield); if (!p) p = gl_proc("glEndTilingQCOM");
    Args a = args_de(c); (void)a;
    GLbitfield a0 = (GLbitfield)arg32(&a);
    p(a0);
}
void G_glEndTransformFeedback(CPU *c) { RT_PRIMEIRA("glEndTransformFeedback");
    static void (*p)(void); if (!p) p = gl_proc("glEndTransformFeedback");
    Args a = args_de(c); (void)a;
    p();
}
void G_glExtGetBufferPointervQCOM(CPU *c) { RT_PRIMEIRA("glExtGetBufferPointervQCOM");
    static void (*p)(GLenum, void **); if (!p) p = gl_proc("glExtGetBufferPointervQCOM");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    void ** a1 = (void **)G2H(arg32(&a));
    p(a0, a1);
}
void G_glExtGetBuffersQCOM(CPU *c) { RT_PRIMEIRA("glExtGetBuffersQCOM");
    static void (*p)(GLuint *, GLint, GLint *); if (!p) p = gl_proc("glExtGetBuffersQCOM");
    Args a = args_de(c); (void)a;
    GLuint * a0 = (GLuint *)G2H(arg32(&a));
    GLint a1 = (GLint)arg32(&a);
    GLint * a2 = (GLint *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glExtGetFramebuffersQCOM(CPU *c) { RT_PRIMEIRA("glExtGetFramebuffersQCOM");
    static void (*p)(GLuint *, GLint, GLint *); if (!p) p = gl_proc("glExtGetFramebuffersQCOM");
    Args a = args_de(c); (void)a;
    GLuint * a0 = (GLuint *)G2H(arg32(&a));
    GLint a1 = (GLint)arg32(&a);
    GLint * a2 = (GLint *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glExtGetProgramBinarySourceQCOM(CPU *c) { RT_PRIMEIRA("glExtGetProgramBinarySourceQCOM");
    static void (*p)(GLuint, GLenum, GLchar *, GLint *); if (!p) p = gl_proc("glExtGetProgramBinarySourceQCOM");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLchar * a2 = (GLchar *)G2H(arg32(&a));
    GLint * a3 = (GLint *)G2H(arg32(&a));
    p(a0, a1, a2, a3);
}
void G_glExtGetProgramsQCOM(CPU *c) { RT_PRIMEIRA("glExtGetProgramsQCOM");
    static void (*p)(GLuint *, GLint, GLint *); if (!p) p = gl_proc("glExtGetProgramsQCOM");
    Args a = args_de(c); (void)a;
    GLuint * a0 = (GLuint *)G2H(arg32(&a));
    GLint a1 = (GLint)arg32(&a);
    GLint * a2 = (GLint *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glExtGetRenderbuffersQCOM(CPU *c) { RT_PRIMEIRA("glExtGetRenderbuffersQCOM");
    static void (*p)(GLuint *, GLint, GLint *); if (!p) p = gl_proc("glExtGetRenderbuffersQCOM");
    Args a = args_de(c); (void)a;
    GLuint * a0 = (GLuint *)G2H(arg32(&a));
    GLint a1 = (GLint)arg32(&a);
    GLint * a2 = (GLint *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glExtGetShadersQCOM(CPU *c) { RT_PRIMEIRA("glExtGetShadersQCOM");
    static void (*p)(GLuint *, GLint, GLint *); if (!p) p = gl_proc("glExtGetShadersQCOM");
    Args a = args_de(c); (void)a;
    GLuint * a0 = (GLuint *)G2H(arg32(&a));
    GLint a1 = (GLint)arg32(&a);
    GLint * a2 = (GLint *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glExtGetTexLevelParameterivQCOM(CPU *c) { RT_PRIMEIRA("glExtGetTexLevelParameterivQCOM");
    static void (*p)(GLuint, GLenum, GLint, GLenum, GLint *); if (!p) p = gl_proc("glExtGetTexLevelParameterivQCOM");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLint a2 = (GLint)arg32(&a);
    GLenum a3 = (GLenum)arg32(&a);
    GLint * a4 = (GLint *)G2H(arg32(&a));
    p(a0, a1, a2, a3, a4);
}
void G_glExtGetTexSubImageQCOM(CPU *c) { RT_PRIMEIRA("glExtGetTexSubImageQCOM");
    static void (*p)(GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLenum, void *); if (!p) p = gl_proc("glExtGetTexSubImageQCOM");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLint a2 = (GLint)arg32(&a);
    GLint a3 = (GLint)arg32(&a);
    GLint a4 = (GLint)arg32(&a);
    GLsizei a5 = (GLsizei)arg32(&a);
    GLsizei a6 = (GLsizei)arg32(&a);
    GLsizei a7 = (GLsizei)arg32(&a);
    GLenum a8 = (GLenum)arg32(&a);
    GLenum a9 = (GLenum)arg32(&a);
    void * a10 = (void *)G2H(arg32(&a));
    p(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
}
void G_glExtGetTexturesQCOM(CPU *c) { RT_PRIMEIRA("glExtGetTexturesQCOM");
    static void (*p)(GLuint *, GLint, GLint *); if (!p) p = gl_proc("glExtGetTexturesQCOM");
    Args a = args_de(c); (void)a;
    GLuint * a0 = (GLuint *)G2H(arg32(&a));
    GLint a1 = (GLint)arg32(&a);
    GLint * a2 = (GLint *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glExtIsProgramBinaryQCOM(CPU *c) { RT_PRIMEIRA("glExtIsProgramBinaryQCOM");
    static GLboolean (*p)(GLuint); if (!p) p = gl_proc("glExtIsProgramBinaryQCOM");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    ret32(c, (uint32_t)p(a0));
}
void G_glExtTexObjectStateOverrideiQCOM(CPU *c) { RT_PRIMEIRA("glExtTexObjectStateOverrideiQCOM");
    static void (*p)(GLenum, GLenum, GLint); if (!p) p = gl_proc("glExtTexObjectStateOverrideiQCOM");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLint a2 = (GLint)arg32(&a);
    p(a0, a1, a2);
}
void G_glFinish(CPU *c) { RT_PRIMEIRA("glFinish");
    static void (*p)(void); if (!p) p = gl_proc("glFinish");
    Args a = args_de(c); (void)a;
    p();
}
void G_glFinishFenceNV(CPU *c) { RT_PRIMEIRA("glFinishFenceNV");
    static void (*p)(GLuint); if (!p) p = gl_proc("glFinishFenceNV");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    p(a0);
}
void G_glFlush(CPU *c) { RT_PRIMEIRA("glFlush");
    static void (*p)(void); if (!p) p = gl_proc("glFlush");
    Args a = args_de(c); (void)a;
    p();
}
void G_glFragmentCoverageColorNV(CPU *c) { RT_PRIMEIRA("glFragmentCoverageColorNV");
    static void (*p)(GLuint); if (!p) p = gl_proc("glFragmentCoverageColorNV");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    p(a0);
}
void G_glFramebufferFetchBarrierEXT(CPU *c) { RT_PRIMEIRA("glFramebufferFetchBarrierEXT");
    static void (*p)(void); if (!p) p = gl_proc("glFramebufferFetchBarrierEXT");
    Args a = args_de(c); (void)a;
    p();
}
void G_glFramebufferFetchBarrierQCOM(CPU *c) { RT_PRIMEIRA("glFramebufferFetchBarrierQCOM");
    static void (*p)(void); if (!p) p = gl_proc("glFramebufferFetchBarrierQCOM");
    Args a = args_de(c); (void)a;
    p();
}
void G_glFramebufferFoveationConfigQCOM(CPU *c) { RT_PRIMEIRA("glFramebufferFoveationConfigQCOM");
    static void (*p)(GLuint, GLuint, GLuint, GLuint, GLuint *); if (!p) p = gl_proc("glFramebufferFoveationConfigQCOM");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLuint a1 = (GLuint)arg32(&a);
    GLuint a2 = (GLuint)arg32(&a);
    GLuint a3 = (GLuint)arg32(&a);
    GLuint * a4 = (GLuint *)G2H(arg32(&a));
    p(a0, a1, a2, a3, a4);
}
void G_glFramebufferFoveationParametersQCOM(CPU *c) { RT_PRIMEIRA("glFramebufferFoveationParametersQCOM");
    static void (*p)(GLuint, GLuint, GLuint, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat); if (!p) p = gl_proc("glFramebufferFoveationParametersQCOM");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLuint a1 = (GLuint)arg32(&a);
    GLuint a2 = (GLuint)arg32(&a);
    GLfloat a3 = argf(&a);
    GLfloat a4 = argf(&a);
    GLfloat a5 = argf(&a);
    GLfloat a6 = argf(&a);
    GLfloat a7 = argf(&a);
    p(a0, a1, a2, a3, a4, a5, a6, a7);
}
void G_glFramebufferParameteri(CPU *c) { RT_PRIMEIRA("glFramebufferParameteri");
    static void (*p)(GLenum, GLenum, GLint); if (!p) p = gl_proc("glFramebufferParameteri");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLint a2 = (GLint)arg32(&a);
    p(a0, a1, a2);
}
void G_glFramebufferPixelLocalStorageSizeEXT(CPU *c) { RT_PRIMEIRA("glFramebufferPixelLocalStorageSizeEXT");
    static void (*p)(GLuint, GLsizei); if (!p) p = gl_proc("glFramebufferPixelLocalStorageSizeEXT");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    p(a0, a1);
}
void G_glFramebufferRenderbuffer(CPU *c) { RT_PRIMEIRA("glFramebufferRenderbuffer");
    static void (*p)(GLenum, GLenum, GLenum, GLuint); if (!p) p = gl_proc("glFramebufferRenderbuffer");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLenum a2 = (GLenum)arg32(&a);
    GLuint a3 = (GLuint)arg32(&a);
    pq_anexo(a0, a1, a3, 1, 0);
    p(a0, a1, a2, a3);
}
void G_glFramebufferSampleLocationsfvNV(CPU *c) { RT_PRIMEIRA("glFramebufferSampleLocationsfvNV");
    static void (*p)(GLenum, GLuint, GLsizei, const GLfloat *); if (!p) p = gl_proc("glFramebufferSampleLocationsfvNV");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLuint a1 = (GLuint)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    const GLfloat * a3 = (const GLfloat *)G2H(arg32(&a));
    p(a0, a1, a2, a3);
}
void G_glFramebufferTexture(CPU *c) { RT_PRIMEIRA("glFramebufferTexture");
    static void (*p)(GLenum, GLenum, GLuint, GLint); if (!p) p = gl_proc("glFramebufferTexture");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLuint a2 = (GLuint)arg32(&a);
    GLint a3 = (GLint)arg32(&a);
    pq_anexo(a0, a1, a2, 0, 0);
    p(a0, a1, a2, a3);
}
void G_glFramebufferTexture2D(CPU *c) { RT_PRIMEIRA("glFramebufferTexture2D");
    static void (*p)(GLenum, GLenum, GLenum, GLuint, GLint); if (!p) p = gl_proc("glFramebufferTexture2D");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLenum a2 = (GLenum)arg32(&a);
    GLuint a3 = (GLuint)arg32(&a);
    GLint a4 = (GLint)arg32(&a);
    pq_anexo(a0, a1, a3, 0, a2);
    p(a0, a1, a2, a3, a4);
}
void G_glFramebufferTexture2DDownsampleIMG(CPU *c) { RT_PRIMEIRA("glFramebufferTexture2DDownsampleIMG");
    static void (*p)(GLenum, GLenum, GLenum, GLuint, GLint, GLint, GLint); if (!p) p = gl_proc("glFramebufferTexture2DDownsampleIMG");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLenum a2 = (GLenum)arg32(&a);
    GLuint a3 = (GLuint)arg32(&a);
    GLint a4 = (GLint)arg32(&a);
    GLint a5 = (GLint)arg32(&a);
    GLint a6 = (GLint)arg32(&a);
    p(a0, a1, a2, a3, a4, a5, a6);
}
void G_glFramebufferTexture2DMultisampleEXT(CPU *c) { RT_PRIMEIRA("glFramebufferTexture2DMultisampleEXT");
    static void (*p)(GLenum, GLenum, GLenum, GLuint, GLint, GLsizei); if (!p) p = gl_proc("glFramebufferTexture2DMultisampleEXT");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLenum a2 = (GLenum)arg32(&a);
    GLuint a3 = (GLuint)arg32(&a);
    GLint a4 = (GLint)arg32(&a);
    GLsizei a5 = (GLsizei)arg32(&a);
    p(a0, a1, a2, a3, a4, a5);
}
void G_glFramebufferTexture2DMultisampleIMG(CPU *c) { RT_PRIMEIRA("glFramebufferTexture2DMultisampleIMG");
    static void (*p)(GLenum, GLenum, GLenum, GLuint, GLint, GLsizei); if (!p) p = gl_proc("glFramebufferTexture2DMultisampleIMG");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLenum a2 = (GLenum)arg32(&a);
    GLuint a3 = (GLuint)arg32(&a);
    GLint a4 = (GLint)arg32(&a);
    GLsizei a5 = (GLsizei)arg32(&a);
    p(a0, a1, a2, a3, a4, a5);
}
void G_glFramebufferTexture3DOES(CPU *c) { RT_PRIMEIRA("glFramebufferTexture3DOES");
    static void (*p)(GLenum, GLenum, GLenum, GLuint, GLint, GLint); if (!p) p = gl_proc("glFramebufferTexture3DOES");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLenum a2 = (GLenum)arg32(&a);
    GLuint a3 = (GLuint)arg32(&a);
    GLint a4 = (GLint)arg32(&a);
    GLint a5 = (GLint)arg32(&a);
    p(a0, a1, a2, a3, a4, a5);
}
void G_glFramebufferTextureEXT(CPU *c) { RT_PRIMEIRA("glFramebufferTextureEXT");
    static void (*p)(GLenum, GLenum, GLuint, GLint); if (!p) p = gl_proc("glFramebufferTextureEXT");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLuint a2 = (GLuint)arg32(&a);
    GLint a3 = (GLint)arg32(&a);
    pq_anexo(a0, a1, a2, 0, 0);
    p(a0, a1, a2, a3);
}
void G_glFramebufferTextureLayer(CPU *c) { RT_PRIMEIRA("glFramebufferTextureLayer");
    static void (*p)(GLenum, GLenum, GLuint, GLint, GLint); if (!p) p = gl_proc("glFramebufferTextureLayer");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLuint a2 = (GLuint)arg32(&a);
    GLint a3 = (GLint)arg32(&a);
    GLint a4 = (GLint)arg32(&a);
    pq_anexo(a0, a1, a2, 0, (GLuint)a4);
    p(a0, a1, a2, a3, a4);
}
void G_glFramebufferTextureLayerDownsampleIMG(CPU *c) { RT_PRIMEIRA("glFramebufferTextureLayerDownsampleIMG");
    static void (*p)(GLenum, GLenum, GLuint, GLint, GLint, GLint, GLint); if (!p) p = gl_proc("glFramebufferTextureLayerDownsampleIMG");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLuint a2 = (GLuint)arg32(&a);
    GLint a3 = (GLint)arg32(&a);
    GLint a4 = (GLint)arg32(&a);
    GLint a5 = (GLint)arg32(&a);
    GLint a6 = (GLint)arg32(&a);
    p(a0, a1, a2, a3, a4, a5, a6);
}
void G_glFramebufferTextureMultisampleMultiviewOVR(CPU *c) { RT_PRIMEIRA("glFramebufferTextureMultisampleMultiviewOVR");
    static void (*p)(GLenum, GLenum, GLuint, GLint, GLsizei, GLint, GLsizei); if (!p) p = gl_proc("glFramebufferTextureMultisampleMultiviewOVR");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLuint a2 = (GLuint)arg32(&a);
    GLint a3 = (GLint)arg32(&a);
    GLsizei a4 = (GLsizei)arg32(&a);
    GLint a5 = (GLint)arg32(&a);
    GLsizei a6 = (GLsizei)arg32(&a);
    p(a0, a1, a2, a3, a4, a5, a6);
}
void G_glFramebufferTextureMultiviewOVR(CPU *c) { RT_PRIMEIRA("glFramebufferTextureMultiviewOVR");
    static void (*p)(GLenum, GLenum, GLuint, GLint, GLint, GLsizei); if (!p) p = gl_proc("glFramebufferTextureMultiviewOVR");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLuint a2 = (GLuint)arg32(&a);
    GLint a3 = (GLint)arg32(&a);
    GLint a4 = (GLint)arg32(&a);
    GLsizei a5 = (GLsizei)arg32(&a);
    p(a0, a1, a2, a3, a4, a5);
}
void G_glFramebufferTextureOES(CPU *c) { RT_PRIMEIRA("glFramebufferTextureOES");
    static void (*p)(GLenum, GLenum, GLuint, GLint); if (!p) p = gl_proc("glFramebufferTextureOES");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLuint a2 = (GLuint)arg32(&a);
    GLint a3 = (GLint)arg32(&a);
    pq_anexo(a0, a1, a2, 0, 0);
    p(a0, a1, a2, a3);
}
void G_glFrontFace(CPU *c) { RT_PRIMEIRA("glFrontFace");
    static void (*p)(GLenum); if (!p) p = gl_proc("glFrontFace");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    p(a0);
}
void G_glGenBuffers(CPU *c) { RT_PRIMEIRA("glGenBuffers");
    static void (*p)(GLsizei, GLuint *); if (!p) p = gl_proc("glGenBuffers");
    Args a = args_de(c); (void)a;
    GLsizei a0 = (GLsizei)arg32(&a);
    GLuint * a1 = (GLuint *)G2H(arg32(&a));
    p(a0, a1);
}
void G_glGenFencesNV(CPU *c) { RT_PRIMEIRA("glGenFencesNV");
    static void (*p)(GLsizei, GLuint *); if (!p) p = gl_proc("glGenFencesNV");
    Args a = args_de(c); (void)a;
    GLsizei a0 = (GLsizei)arg32(&a);
    GLuint * a1 = (GLuint *)G2H(arg32(&a));
    p(a0, a1);
}
void G_glGenFramebuffers(CPU *c) { RT_PRIMEIRA("glGenFramebuffers");
    static void (*p)(GLsizei, GLuint *); if (!p) p = gl_proc("glGenFramebuffers");
    Args a = args_de(c); (void)a;
    GLsizei a0 = (GLsizei)arg32(&a);
    GLuint * a1 = (GLuint *)G2H(arg32(&a));
    p(a0, a1);
}
void G_glGenPathsNV(CPU *c) { RT_PRIMEIRA("glGenPathsNV");
    static GLuint (*p)(GLsizei); if (!p) p = gl_proc("glGenPathsNV");
    Args a = args_de(c); (void)a;
    GLsizei a0 = (GLsizei)arg32(&a);
    ret32(c, (uint32_t)p(a0));
}
void G_glGenPerfMonitorsAMD(CPU *c) { RT_PRIMEIRA("glGenPerfMonitorsAMD");
    static void (*p)(GLsizei, GLuint *); if (!p) p = gl_proc("glGenPerfMonitorsAMD");
    Args a = args_de(c); (void)a;
    GLsizei a0 = (GLsizei)arg32(&a);
    GLuint * a1 = (GLuint *)G2H(arg32(&a));
    p(a0, a1);
}
void G_glGenProgramPipelines(CPU *c) { RT_PRIMEIRA("glGenProgramPipelines");
    static void (*p)(GLsizei, GLuint *); if (!p) p = gl_proc("glGenProgramPipelines");
    Args a = args_de(c); (void)a;
    GLsizei a0 = (GLsizei)arg32(&a);
    GLuint * a1 = (GLuint *)G2H(arg32(&a));
    p(a0, a1);
}
void G_glGenProgramPipelinesEXT(CPU *c) { RT_PRIMEIRA("glGenProgramPipelinesEXT");
    static void (*p)(GLsizei, GLuint *); if (!p) p = gl_proc("glGenProgramPipelinesEXT");
    Args a = args_de(c); (void)a;
    GLsizei a0 = (GLsizei)arg32(&a);
    GLuint * a1 = (GLuint *)G2H(arg32(&a));
    p(a0, a1);
}
void G_glGenQueries(CPU *c) { RT_PRIMEIRA("glGenQueries");
    static void (*p)(GLsizei, GLuint *); if (!p) p = gl_proc("glGenQueries");
    Args a = args_de(c); (void)a;
    GLsizei a0 = (GLsizei)arg32(&a);
    GLuint * a1 = (GLuint *)G2H(arg32(&a));
    p(a0, a1);
}
void G_glGenQueriesEXT(CPU *c) { RT_PRIMEIRA("glGenQueriesEXT");
    static void (*p)(GLsizei, GLuint *); if (!p) p = gl_proc("glGenQueriesEXT");
    Args a = args_de(c); (void)a;
    GLsizei a0 = (GLsizei)arg32(&a);
    GLuint * a1 = (GLuint *)G2H(arg32(&a));
    p(a0, a1);
}
void G_glGenRenderbuffers(CPU *c) { RT_PRIMEIRA("glGenRenderbuffers");
    static void (*p)(GLsizei, GLuint *); if (!p) p = gl_proc("glGenRenderbuffers");
    Args a = args_de(c); (void)a;
    GLsizei a0 = (GLsizei)arg32(&a);
    GLuint * a1 = (GLuint *)G2H(arg32(&a));
    p(a0, a1);
}
void G_glGenSamplers(CPU *c) { RT_PRIMEIRA("glGenSamplers");
    static void (*p)(GLsizei, GLuint *); if (!p) p = gl_proc("glGenSamplers");
    Args a = args_de(c); (void)a;
    GLsizei a0 = (GLsizei)arg32(&a);
    GLuint * a1 = (GLuint *)G2H(arg32(&a));
    p(a0, a1);
}
void G_glGenSemaphoresEXT(CPU *c) { RT_PRIMEIRA("glGenSemaphoresEXT");
    static void (*p)(GLsizei, GLuint *); if (!p) p = gl_proc("glGenSemaphoresEXT");
    Args a = args_de(c); (void)a;
    GLsizei a0 = (GLsizei)arg32(&a);
    GLuint * a1 = (GLuint *)G2H(arg32(&a));
    p(a0, a1);
}
void G_glGenTextures(CPU *c) { RT_PRIMEIRA("glGenTextures");
    static void (*p)(GLsizei, GLuint *); if (!p) p = gl_proc("glGenTextures");
    Args a = args_de(c); (void)a;
    GLsizei a0 = (GLsizei)arg32(&a);
    GLuint * a1 = (GLuint *)G2H(arg32(&a));
    p(a0, a1);
}
void G_glGenTransformFeedbacks(CPU *c) { RT_PRIMEIRA("glGenTransformFeedbacks");
    static void (*p)(GLsizei, GLuint *); if (!p) p = gl_proc("glGenTransformFeedbacks");
    Args a = args_de(c); (void)a;
    GLsizei a0 = (GLsizei)arg32(&a);
    GLuint * a1 = (GLuint *)G2H(arg32(&a));
    p(a0, a1);
}
void G_glGenVertexArrays(CPU *c) { RT_PRIMEIRA("glGenVertexArrays");
    static void (*p)(GLsizei, GLuint *); if (!p) p = gl_proc("glGenVertexArrays");
    Args a = args_de(c); (void)a;
    GLsizei a0 = (GLsizei)arg32(&a);
    GLuint * a1 = (GLuint *)G2H(arg32(&a));
    p(a0, a1);
}
void G_glGenVertexArraysOES(CPU *c) { RT_PRIMEIRA("glGenVertexArraysOES");
    static void (*p)(GLsizei, GLuint *); if (!p) p = gl_proc("glGenVertexArraysOES");
    Args a = args_de(c); (void)a;
    GLsizei a0 = (GLsizei)arg32(&a);
    GLuint * a1 = (GLuint *)G2H(arg32(&a));
    p(a0, a1);
}
void G_glGenerateMipmap(CPU *c) { RT_PRIMEIRA("glGenerateMipmap");
    static void (*p)(GLenum); if (!p) p = gl_proc("glGenerateMipmap");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    p(a0);
}
void G_glGetActiveAttrib(CPU *c) { RT_PRIMEIRA("glGetActiveAttrib");
    static void (*p)(GLuint, GLuint, GLsizei, GLsizei *, GLint *, GLenum *, GLchar *); if (!p) p = gl_proc("glGetActiveAttrib");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLuint a1 = (GLuint)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    GLsizei * a3 = (GLsizei *)G2H(arg32(&a));
    GLint * a4 = (GLint *)G2H(arg32(&a));
    GLenum * a5 = (GLenum *)G2H(arg32(&a));
    GLchar * a6 = (GLchar *)G2H(arg32(&a));
    p(a0, a1, a2, a3, a4, a5, a6);
}
void G_glGetActiveUniform(CPU *c) { RT_PRIMEIRA("glGetActiveUniform");
    static void (*p)(GLuint, GLuint, GLsizei, GLsizei *, GLint *, GLenum *, GLchar *); if (!p) p = gl_proc("glGetActiveUniform");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLuint a1 = (GLuint)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    GLsizei * a3 = (GLsizei *)G2H(arg32(&a));
    GLint * a4 = (GLint *)G2H(arg32(&a));
    GLenum * a5 = (GLenum *)G2H(arg32(&a));
    GLchar * a6 = (GLchar *)G2H(arg32(&a));
    p(a0, a1, a2, a3, a4, a5, a6);
}
void G_glGetActiveUniformBlockName(CPU *c) { RT_PRIMEIRA("glGetActiveUniformBlockName");
    static void (*p)(GLuint, GLuint, GLsizei, GLsizei *, GLchar *); if (!p) p = gl_proc("glGetActiveUniformBlockName");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLuint a1 = (GLuint)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    GLsizei * a3 = (GLsizei *)G2H(arg32(&a));
    GLchar * a4 = (GLchar *)G2H(arg32(&a));
    p(a0, a1, a2, a3, a4);
}
void G_glGetActiveUniformBlockiv(CPU *c) { RT_PRIMEIRA("glGetActiveUniformBlockiv");
    static void (*p)(GLuint, GLuint, GLenum, GLint *); if (!p) p = gl_proc("glGetActiveUniformBlockiv");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLuint a1 = (GLuint)arg32(&a);
    GLenum a2 = (GLenum)arg32(&a);
    GLint * a3 = (GLint *)G2H(arg32(&a));
    p(a0, a1, a2, a3);
}
void G_glGetActiveUniformsiv(CPU *c) { RT_PRIMEIRA("glGetActiveUniformsiv");
    static void (*p)(GLuint, GLsizei, const GLuint *, GLenum, GLint *); if (!p) p = gl_proc("glGetActiveUniformsiv");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    const GLuint * a2 = (const GLuint *)G2H(arg32(&a));
    GLenum a3 = (GLenum)arg32(&a);
    GLint * a4 = (GLint *)G2H(arg32(&a));
    p(a0, a1, a2, a3, a4);
}
void G_glGetAttachedShaders(CPU *c) { RT_PRIMEIRA("glGetAttachedShaders");
    static void (*p)(GLuint, GLsizei, GLsizei *, GLuint *); if (!p) p = gl_proc("glGetAttachedShaders");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    GLsizei * a2 = (GLsizei *)G2H(arg32(&a));
    GLuint * a3 = (GLuint *)G2H(arg32(&a));
    p(a0, a1, a2, a3);
}
void G_glGetAttribLocation(CPU *c) { RT_PRIMEIRA("glGetAttribLocation");
    static GLint (*p)(GLuint, const GLchar *); if (!p) p = gl_proc("glGetAttribLocation");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    const GLchar * a1 = (const GLchar *)G2H(arg32(&a));
    GLint loc = p(a0, a1);
#ifdef MGS2_DEPURA
    { static int n; if (!strcmp(a1, "vs_pos_offset") && n++ < 10) rt_log("glGetUniformLocation(prog %u, vs_pos_offset) = %d", a0, loc); }
#endif
    ret32(c, (uint32_t)loc);
}
void G_glGetBooleani_v(CPU *c) { RT_PRIMEIRA("glGetBooleani_v");
    static void (*p)(GLenum, GLuint, GLboolean *); if (!p) p = gl_proc("glGetBooleani_v");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLuint a1 = (GLuint)arg32(&a);
    GLboolean * a2 = (GLboolean *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glGetBooleanv(CPU *c) { RT_PRIMEIRA("glGetBooleanv");
    static void (*p)(GLenum, GLboolean *); if (!p) p = gl_proc("glGetBooleanv");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLboolean * a1 = (GLboolean *)G2H(arg32(&a));
    p(a0, a1);
}
void G_glGetBufferParameteri64v(CPU *c) { RT_PRIMEIRA("glGetBufferParameteri64v");
    static void (*p)(GLenum, GLenum, GLint64 *); if (!p) p = gl_proc("glGetBufferParameteri64v");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLint64 * a2 = (GLint64 *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glGetBufferParameteriv(CPU *c) { RT_PRIMEIRA("glGetBufferParameteriv");
    static void (*p)(GLenum, GLenum, GLint *); if (!p) p = gl_proc("glGetBufferParameteriv");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLint * a2 = (GLint *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glGetCoverageModulationTableNV(CPU *c) { RT_PRIMEIRA("glGetCoverageModulationTableNV");
    static void (*p)(GLsizei, GLfloat *); if (!p) p = gl_proc("glGetCoverageModulationTableNV");
    Args a = args_de(c); (void)a;
    GLsizei a0 = (GLsizei)arg32(&a);
    GLfloat * a1 = (GLfloat *)G2H(arg32(&a));
    p(a0, a1);
}
void G_glGetDebugMessageLog(CPU *c) { RT_PRIMEIRA("glGetDebugMessageLog");
    static GLuint (*p)(GLuint, GLsizei, GLenum *, GLenum *, GLuint *, GLenum *, GLsizei *, GLchar *); if (!p) p = gl_proc("glGetDebugMessageLog");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    GLenum * a2 = (GLenum *)G2H(arg32(&a));
    GLenum * a3 = (GLenum *)G2H(arg32(&a));
    GLuint * a4 = (GLuint *)G2H(arg32(&a));
    GLenum * a5 = (GLenum *)G2H(arg32(&a));
    GLsizei * a6 = (GLsizei *)G2H(arg32(&a));
    GLchar * a7 = (GLchar *)G2H(arg32(&a));
    ret32(c, (uint32_t)p(a0, a1, a2, a3, a4, a5, a6, a7));
}
void G_glGetDebugMessageLogKHR(CPU *c) { RT_PRIMEIRA("glGetDebugMessageLogKHR");
    static GLuint (*p)(GLuint, GLsizei, GLenum *, GLenum *, GLuint *, GLenum *, GLsizei *, GLchar *); if (!p) p = gl_proc("glGetDebugMessageLogKHR");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    GLenum * a2 = (GLenum *)G2H(arg32(&a));
    GLenum * a3 = (GLenum *)G2H(arg32(&a));
    GLuint * a4 = (GLuint *)G2H(arg32(&a));
    GLenum * a5 = (GLenum *)G2H(arg32(&a));
    GLsizei * a6 = (GLsizei *)G2H(arg32(&a));
    GLchar * a7 = (GLchar *)G2H(arg32(&a));
    ret32(c, (uint32_t)p(a0, a1, a2, a3, a4, a5, a6, a7));
}
void G_glGetDriverControlStringQCOM(CPU *c) { RT_PRIMEIRA("glGetDriverControlStringQCOM");
    static void (*p)(GLuint, GLsizei, GLsizei *, GLchar *); if (!p) p = gl_proc("glGetDriverControlStringQCOM");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    GLsizei * a2 = (GLsizei *)G2H(arg32(&a));
    GLchar * a3 = (GLchar *)G2H(arg32(&a));
    p(a0, a1, a2, a3);
}
void G_glGetDriverControlsQCOM(CPU *c) { RT_PRIMEIRA("glGetDriverControlsQCOM");
    static void (*p)(GLint *, GLsizei, GLuint *); if (!p) p = gl_proc("glGetDriverControlsQCOM");
    Args a = args_de(c); (void)a;
    GLint * a0 = (GLint *)G2H(arg32(&a));
    GLsizei a1 = (GLsizei)arg32(&a);
    GLuint * a2 = (GLuint *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glGetError(CPU *c) { RT_PRIMEIRA("glGetError");
    static GLenum (*p)(void); if (!p) p = gl_proc("glGetError");
    Args a = args_de(c); (void)a;
    extern __thread GLenum t_erro_gl_pendente;   /* erro que uma ponte de textura ja leu */
    if (t_erro_gl_pendente) { GLenum e = t_erro_gl_pendente; t_erro_gl_pendente = 0; p(); ret32(c, e); return; }
    ret32(c, (uint32_t)p());
}
void G_glGetFenceivNV(CPU *c) { RT_PRIMEIRA("glGetFenceivNV");
    static void (*p)(GLuint, GLenum, GLint *); if (!p) p = gl_proc("glGetFenceivNV");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLint * a2 = (GLint *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glGetFirstPerfQueryIdINTEL(CPU *c) { RT_PRIMEIRA("glGetFirstPerfQueryIdINTEL");
    static void (*p)(GLuint *); if (!p) p = gl_proc("glGetFirstPerfQueryIdINTEL");
    Args a = args_de(c); (void)a;
    GLuint * a0 = (GLuint *)G2H(arg32(&a));
    p(a0);
}
void G_glGetFloati_vNV(CPU *c) { RT_PRIMEIRA("glGetFloati_vNV");
    static void (*p)(GLenum, GLuint, GLfloat *); if (!p) p = gl_proc("glGetFloati_vNV");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLuint a1 = (GLuint)arg32(&a);
    GLfloat * a2 = (GLfloat *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glGetFloati_vOES(CPU *c) { RT_PRIMEIRA("glGetFloati_vOES");
    static void (*p)(GLenum, GLuint, GLfloat *); if (!p) p = gl_proc("glGetFloati_vOES");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLuint a1 = (GLuint)arg32(&a);
    GLfloat * a2 = (GLfloat *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glGetFloatv(CPU *c) { RT_PRIMEIRA("glGetFloatv");
    static void (*p)(GLenum, GLfloat *); if (!p) p = gl_proc("glGetFloatv");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLfloat * a1 = (GLfloat *)G2H(arg32(&a));
    p(a0, a1);
}
void G_glGetFragDataIndexEXT(CPU *c) { RT_PRIMEIRA("glGetFragDataIndexEXT");
    static GLint (*p)(GLuint, const GLchar *); if (!p) p = gl_proc("glGetFragDataIndexEXT");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    const GLchar * a1 = (const GLchar *)G2H(arg32(&a));
    ret32(c, (uint32_t)p(a0, a1));
}
void G_glGetFragDataLocation(CPU *c) { RT_PRIMEIRA("glGetFragDataLocation");
    static GLint (*p)(GLuint, const GLchar *); if (!p) p = gl_proc("glGetFragDataLocation");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    const GLchar * a1 = (const GLchar *)G2H(arg32(&a));
    ret32(c, (uint32_t)p(a0, a1));
}
void G_glGetFramebufferAttachmentParameteriv(CPU *c) { RT_PRIMEIRA("glGetFramebufferAttachmentParameteriv");
    static void (*p)(GLenum, GLenum, GLenum, GLint *); if (!p) p = gl_proc("glGetFramebufferAttachmentParameteriv");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLenum a2 = (GLenum)arg32(&a);
    GLint * a3 = (GLint *)G2H(arg32(&a));
    p(a0, a1, a2, a3);
}
void G_glGetFramebufferParameteriv(CPU *c) { RT_PRIMEIRA("glGetFramebufferParameteriv");
    static void (*p)(GLenum, GLenum, GLint *); if (!p) p = gl_proc("glGetFramebufferParameteriv");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLint * a2 = (GLint *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glGetFramebufferPixelLocalStorageSizeEXT(CPU *c) { RT_PRIMEIRA("glGetFramebufferPixelLocalStorageSizeEXT");
    static GLsizei (*p)(GLuint); if (!p) p = gl_proc("glGetFramebufferPixelLocalStorageSizeEXT");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    ret32(c, (uint32_t)p(a0));
}
void G_glGetGraphicsResetStatus(CPU *c) { RT_PRIMEIRA("glGetGraphicsResetStatus");
    static GLenum (*p)(void); if (!p) p = gl_proc("glGetGraphicsResetStatus");
    Args a = args_de(c); (void)a;
    ret32(c, (uint32_t)p());
}
void G_glGetGraphicsResetStatusEXT(CPU *c) { RT_PRIMEIRA("glGetGraphicsResetStatusEXT");
    static GLenum (*p)(void); if (!p) p = gl_proc("glGetGraphicsResetStatusEXT");
    Args a = args_de(c); (void)a;
    ret32(c, (uint32_t)p());
}
void G_glGetGraphicsResetStatusKHR(CPU *c) { RT_PRIMEIRA("glGetGraphicsResetStatusKHR");
    static GLenum (*p)(void); if (!p) p = gl_proc("glGetGraphicsResetStatusKHR");
    Args a = args_de(c); (void)a;
    ret32(c, (uint32_t)p());
}
void G_glGetInteger64i_v(CPU *c) { RT_PRIMEIRA("glGetInteger64i_v");
    static void (*p)(GLenum, GLuint, GLint64 *); if (!p) p = gl_proc("glGetInteger64i_v");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLuint a1 = (GLuint)arg32(&a);
    GLint64 * a2 = (GLint64 *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glGetInteger64v(CPU *c) { RT_PRIMEIRA("glGetInteger64v");
    static void (*p)(GLenum, GLint64 *); if (!p) p = gl_proc("glGetInteger64v");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLint64 * a1 = (GLint64 *)G2H(arg32(&a));
    p(a0, a1);
}
void G_glGetInteger64vAPPLE(CPU *c) { RT_PRIMEIRA("glGetInteger64vAPPLE");
    static void (*p)(GLenum, GLint64 *); if (!p) p = gl_proc("glGetInteger64vAPPLE");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLint64 * a1 = (GLint64 *)G2H(arg32(&a));
    p(a0, a1);
}
void G_glGetIntegeri_v(CPU *c) { RT_PRIMEIRA("glGetIntegeri_v");
    static void (*p)(GLenum, GLuint, GLint *); if (!p) p = gl_proc("glGetIntegeri_v");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLuint a1 = (GLuint)arg32(&a);
    GLint * a2 = (GLint *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glGetIntegeri_vEXT(CPU *c) { RT_PRIMEIRA("glGetIntegeri_vEXT");
    static void (*p)(GLenum, GLuint, GLint *); if (!p) p = gl_proc("glGetIntegeri_vEXT");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLuint a1 = (GLuint)arg32(&a);
    GLint * a2 = (GLint *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glGetIntegerv(CPU *c) { RT_PRIMEIRA("glGetIntegerv");
    static void (*p)(GLenum, GLint *); if (!p) p = gl_proc("glGetIntegerv");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLint * a1 = (GLint *)G2H(arg32(&a));
    if (a0 == GL_NUM_EXTENSIONS) { int gl_num_exts(void); *a1 = gl_num_exts(); return; }
    if (a0 == GL_NUM_COMPRESSED_TEXTURE_FORMATS || a0 == GL_COMPRESSED_TEXTURE_FORMATS) {
        /* DXT/RGTC descomprimidos na CPU (GPU sem os formatos): a camada tem de continuar vendo-os */
        int fmt_dxt_na_cpu(void), fmt_rgtc_na_cpu(void);
        static const GLint dxt[] = { 0x83F0, 0x83F1, 0x83F2, 0x83F3 }, rgtc[] = { 0x8DBB, 0x8DBD };
        int nd = fmt_dxt_na_cpu() ? 4 : 0, nr = fmt_rgtc_na_cpu() ? 2 : 0;
        GLint n = 0; p(GL_NUM_COMPRESSED_TEXTURE_FORMATS, &n);
        if (a0 == GL_NUM_COMPRESSED_TEXTURE_FORMATS) { *a1 = n + nd + nr; return; }
        p(a0, a1);
        for (int k = 0; k < nd; k++) a1[n++] = dxt[k];
        for (int k = 0; k < nr; k++) a1[n++] = rgtc[k];
        return;
    }
    if (a0 == GL_MAJOR_VERSION) { *a1 = 3; return; }
    if (a0 == GL_MINOR_VERSION) { *a1 = 3; return; }
    if (a0 >= 0x0D52 && a0 <= 0x0D57) {
        /* GL_RED..STENCIL_BITS: num contexto sem superficie (a thread MTD3D da camada)
         * o driver da Adreno desreferencia NULL. Sem superficie e sem FBO, respondemos
         * pelo formato que a camada pediu (RGBA8, D24S8). */
        GLint fbo = 0; p(GL_DRAW_FRAMEBUFFER_BINDING, &fbo);
        if (!fbo && eglGetCurrentSurface(EGL_DRAW) == EGL_NO_SURFACE) {
            static const GLint v[6] = { 8, 8, 8, 8, 24, 8 };
            *a1 = v[a0 - 0x0D52];
            return;
        }
    }
    p(a0, a1);
}
void G_glGetInternalformatSampleivNV(CPU *c) { RT_PRIMEIRA("glGetInternalformatSampleivNV");
    static void (*p)(GLenum, GLenum, GLsizei, GLenum, GLsizei, GLint *); if (!p) p = gl_proc("glGetInternalformatSampleivNV");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    GLenum a3 = (GLenum)arg32(&a);
    GLsizei a4 = (GLsizei)arg32(&a);
    GLint * a5 = (GLint *)G2H(arg32(&a));
    p(a0, a1, a2, a3, a4, a5);
}
void G_glGetInternalformativ(CPU *c) { RT_PRIMEIRA("glGetInternalformativ");
    static void (*p)(GLenum, GLenum, GLenum, GLsizei, GLint *); if (!p) p = gl_proc("glGetInternalformativ");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLenum a2 = (GLenum)arg32(&a);
    GLsizei a3 = (GLsizei)arg32(&a);
    GLint * a4 = (GLint *)G2H(arg32(&a));
    p(a0, a1, a2, a3, a4);
}
void G_glGetMemoryObjectParameterivEXT(CPU *c) { RT_PRIMEIRA("glGetMemoryObjectParameterivEXT");
    static void (*p)(GLuint, GLenum, GLint *); if (!p) p = gl_proc("glGetMemoryObjectParameterivEXT");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLint * a2 = (GLint *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glGetMultisamplefv(CPU *c) { RT_PRIMEIRA("glGetMultisamplefv");
    static void (*p)(GLenum, GLuint, GLfloat *); if (!p) p = gl_proc("glGetMultisamplefv");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLuint a1 = (GLuint)arg32(&a);
    GLfloat * a2 = (GLfloat *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glGetNextPerfQueryIdINTEL(CPU *c) { RT_PRIMEIRA("glGetNextPerfQueryIdINTEL");
    static void (*p)(GLuint, GLuint *); if (!p) p = gl_proc("glGetNextPerfQueryIdINTEL");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLuint * a1 = (GLuint *)G2H(arg32(&a));
    p(a0, a1);
}
void G_glGetObjectLabel(CPU *c) { RT_PRIMEIRA("glGetObjectLabel");
    static void (*p)(GLenum, GLuint, GLsizei, GLsizei *, GLchar *); if (!p) p = gl_proc("glGetObjectLabel");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLuint a1 = (GLuint)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    GLsizei * a3 = (GLsizei *)G2H(arg32(&a));
    GLchar * a4 = (GLchar *)G2H(arg32(&a));
    p(a0, a1, a2, a3, a4);
}
void G_glGetObjectLabelEXT(CPU *c) { RT_PRIMEIRA("glGetObjectLabelEXT");
    static void (*p)(GLenum, GLuint, GLsizei, GLsizei *, GLchar *); if (!p) p = gl_proc("glGetObjectLabelEXT");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLuint a1 = (GLuint)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    GLsizei * a3 = (GLsizei *)G2H(arg32(&a));
    GLchar * a4 = (GLchar *)G2H(arg32(&a));
    p(a0, a1, a2, a3, a4);
}
void G_glGetObjectLabelKHR(CPU *c) { RT_PRIMEIRA("glGetObjectLabelKHR");
    static void (*p)(GLenum, GLuint, GLsizei, GLsizei *, GLchar *); if (!p) p = gl_proc("glGetObjectLabelKHR");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLuint a1 = (GLuint)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    GLsizei * a3 = (GLsizei *)G2H(arg32(&a));
    GLchar * a4 = (GLchar *)G2H(arg32(&a));
    p(a0, a1, a2, a3, a4);
}
void G_glGetObjectPtrLabel(CPU *c) { RT_PRIMEIRA("glGetObjectPtrLabel");
    static void (*p)(const void *, GLsizei, GLsizei *, GLchar *); if (!p) p = gl_proc("glGetObjectPtrLabel");
    Args a = args_de(c); (void)a;
    const void * a0 = (const void *)G2H(arg32(&a));
    GLsizei a1 = (GLsizei)arg32(&a);
    GLsizei * a2 = (GLsizei *)G2H(arg32(&a));
    GLchar * a3 = (GLchar *)G2H(arg32(&a));
    p(a0, a1, a2, a3);
}
void G_glGetObjectPtrLabelKHR(CPU *c) { RT_PRIMEIRA("glGetObjectPtrLabelKHR");
    static void (*p)(const void *, GLsizei, GLsizei *, GLchar *); if (!p) p = gl_proc("glGetObjectPtrLabelKHR");
    Args a = args_de(c); (void)a;
    const void * a0 = (const void *)G2H(arg32(&a));
    GLsizei a1 = (GLsizei)arg32(&a);
    GLsizei * a2 = (GLsizei *)G2H(arg32(&a));
    GLchar * a3 = (GLchar *)G2H(arg32(&a));
    p(a0, a1, a2, a3);
}
void G_glGetPathCommandsNV(CPU *c) { RT_PRIMEIRA("glGetPathCommandsNV");
    static void (*p)(GLuint, GLubyte *); if (!p) p = gl_proc("glGetPathCommandsNV");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLubyte * a1 = (GLubyte *)G2H(arg32(&a));
    p(a0, a1);
}
void G_glGetPathCoordsNV(CPU *c) { RT_PRIMEIRA("glGetPathCoordsNV");
    static void (*p)(GLuint, GLfloat *); if (!p) p = gl_proc("glGetPathCoordsNV");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLfloat * a1 = (GLfloat *)G2H(arg32(&a));
    p(a0, a1);
}
void G_glGetPathDashArrayNV(CPU *c) { RT_PRIMEIRA("glGetPathDashArrayNV");
    static void (*p)(GLuint, GLfloat *); if (!p) p = gl_proc("glGetPathDashArrayNV");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLfloat * a1 = (GLfloat *)G2H(arg32(&a));
    p(a0, a1);
}
void G_glGetPathLengthNV(CPU *c) { RT_PRIMEIRA("glGetPathLengthNV");
    static GLfloat (*p)(GLuint, GLsizei, GLsizei); if (!p) p = gl_proc("glGetPathLengthNV");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    retf(c, p(a0, a1, a2));
}
void G_glGetPathMetricRangeNV(CPU *c) { RT_PRIMEIRA("glGetPathMetricRangeNV");
    static void (*p)(GLbitfield, GLuint, GLsizei, GLsizei, GLfloat *); if (!p) p = gl_proc("glGetPathMetricRangeNV");
    Args a = args_de(c); (void)a;
    GLbitfield a0 = (GLbitfield)arg32(&a);
    GLuint a1 = (GLuint)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    GLsizei a3 = (GLsizei)arg32(&a);
    GLfloat * a4 = (GLfloat *)G2H(arg32(&a));
    p(a0, a1, a2, a3, a4);
}
void G_glGetPathMetricsNV(CPU *c) { RT_PRIMEIRA("glGetPathMetricsNV");
    static void (*p)(GLbitfield, GLsizei, GLenum, const void *, GLuint, GLsizei, GLfloat *); if (!p) p = gl_proc("glGetPathMetricsNV");
    Args a = args_de(c); (void)a;
    GLbitfield a0 = (GLbitfield)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    GLenum a2 = (GLenum)arg32(&a);
    const void * a3 = (const void *)G2H(arg32(&a));
    GLuint a4 = (GLuint)arg32(&a);
    GLsizei a5 = (GLsizei)arg32(&a);
    GLfloat * a6 = (GLfloat *)G2H(arg32(&a));
    p(a0, a1, a2, a3, a4, a5, a6);
}
void G_glGetPathParameterfvNV(CPU *c) { RT_PRIMEIRA("glGetPathParameterfvNV");
    static void (*p)(GLuint, GLenum, GLfloat *); if (!p) p = gl_proc("glGetPathParameterfvNV");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLfloat * a2 = (GLfloat *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glGetPathParameterivNV(CPU *c) { RT_PRIMEIRA("glGetPathParameterivNV");
    static void (*p)(GLuint, GLenum, GLint *); if (!p) p = gl_proc("glGetPathParameterivNV");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLint * a2 = (GLint *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glGetPathSpacingNV(CPU *c) { RT_PRIMEIRA("glGetPathSpacingNV");
    static void (*p)(GLenum, GLsizei, GLenum, const void *, GLuint, GLfloat, GLfloat, GLenum, GLfloat *); if (!p) p = gl_proc("glGetPathSpacingNV");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    GLenum a2 = (GLenum)arg32(&a);
    const void * a3 = (const void *)G2H(arg32(&a));
    GLuint a4 = (GLuint)arg32(&a);
    GLfloat a5 = argf(&a);
    GLfloat a6 = argf(&a);
    GLenum a7 = (GLenum)arg32(&a);
    GLfloat * a8 = (GLfloat *)G2H(arg32(&a));
    p(a0, a1, a2, a3, a4, a5, a6, a7, a8);
}
void G_glGetPerfCounterInfoINTEL(CPU *c) { RT_PRIMEIRA("glGetPerfCounterInfoINTEL");
    static void (*p)(GLuint, GLuint, GLuint, GLchar *, GLuint, GLchar *, GLuint *, GLuint *, GLuint *, GLuint *, GLuint64 *); if (!p) p = gl_proc("glGetPerfCounterInfoINTEL");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLuint a1 = (GLuint)arg32(&a);
    GLuint a2 = (GLuint)arg32(&a);
    GLchar * a3 = (GLchar *)G2H(arg32(&a));
    GLuint a4 = (GLuint)arg32(&a);
    GLchar * a5 = (GLchar *)G2H(arg32(&a));
    GLuint * a6 = (GLuint *)G2H(arg32(&a));
    GLuint * a7 = (GLuint *)G2H(arg32(&a));
    GLuint * a8 = (GLuint *)G2H(arg32(&a));
    GLuint * a9 = (GLuint *)G2H(arg32(&a));
    GLuint64 * a10 = (GLuint64 *)G2H(arg32(&a));
    p(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
}
void G_glGetPerfMonitorCounterDataAMD(CPU *c) { RT_PRIMEIRA("glGetPerfMonitorCounterDataAMD");
    static void (*p)(GLuint, GLenum, GLsizei, GLuint *, GLint *); if (!p) p = gl_proc("glGetPerfMonitorCounterDataAMD");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    GLuint * a3 = (GLuint *)G2H(arg32(&a));
    GLint * a4 = (GLint *)G2H(arg32(&a));
    p(a0, a1, a2, a3, a4);
}
void G_glGetPerfMonitorCounterInfoAMD(CPU *c) { RT_PRIMEIRA("glGetPerfMonitorCounterInfoAMD");
    static void (*p)(GLuint, GLuint, GLenum, void *); if (!p) p = gl_proc("glGetPerfMonitorCounterInfoAMD");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLuint a1 = (GLuint)arg32(&a);
    GLenum a2 = (GLenum)arg32(&a);
    void * a3 = (void *)G2H(arg32(&a));
    p(a0, a1, a2, a3);
}
void G_glGetPerfMonitorCounterStringAMD(CPU *c) { RT_PRIMEIRA("glGetPerfMonitorCounterStringAMD");
    static void (*p)(GLuint, GLuint, GLsizei, GLsizei *, GLchar *); if (!p) p = gl_proc("glGetPerfMonitorCounterStringAMD");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLuint a1 = (GLuint)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    GLsizei * a3 = (GLsizei *)G2H(arg32(&a));
    GLchar * a4 = (GLchar *)G2H(arg32(&a));
    p(a0, a1, a2, a3, a4);
}
void G_glGetPerfMonitorCountersAMD(CPU *c) { RT_PRIMEIRA("glGetPerfMonitorCountersAMD");
    static void (*p)(GLuint, GLint *, GLint *, GLsizei, GLuint *); if (!p) p = gl_proc("glGetPerfMonitorCountersAMD");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint * a1 = (GLint *)G2H(arg32(&a));
    GLint * a2 = (GLint *)G2H(arg32(&a));
    GLsizei a3 = (GLsizei)arg32(&a);
    GLuint * a4 = (GLuint *)G2H(arg32(&a));
    p(a0, a1, a2, a3, a4);
}
void G_glGetPerfMonitorGroupStringAMD(CPU *c) { RT_PRIMEIRA("glGetPerfMonitorGroupStringAMD");
    static void (*p)(GLuint, GLsizei, GLsizei *, GLchar *); if (!p) p = gl_proc("glGetPerfMonitorGroupStringAMD");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    GLsizei * a2 = (GLsizei *)G2H(arg32(&a));
    GLchar * a3 = (GLchar *)G2H(arg32(&a));
    p(a0, a1, a2, a3);
}
void G_glGetPerfMonitorGroupsAMD(CPU *c) { RT_PRIMEIRA("glGetPerfMonitorGroupsAMD");
    static void (*p)(GLint *, GLsizei, GLuint *); if (!p) p = gl_proc("glGetPerfMonitorGroupsAMD");
    Args a = args_de(c); (void)a;
    GLint * a0 = (GLint *)G2H(arg32(&a));
    GLsizei a1 = (GLsizei)arg32(&a);
    GLuint * a2 = (GLuint *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glGetPerfQueryDataINTEL(CPU *c) { RT_PRIMEIRA("glGetPerfQueryDataINTEL");
    static void (*p)(GLuint, GLuint, GLsizei, void *, GLuint *); if (!p) p = gl_proc("glGetPerfQueryDataINTEL");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLuint a1 = (GLuint)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    void * a3 = (void *)G2H(arg32(&a));
    GLuint * a4 = (GLuint *)G2H(arg32(&a));
    p(a0, a1, a2, a3, a4);
}
void G_glGetPerfQueryIdByNameINTEL(CPU *c) { RT_PRIMEIRA("glGetPerfQueryIdByNameINTEL");
    static void (*p)(GLchar *, GLuint *); if (!p) p = gl_proc("glGetPerfQueryIdByNameINTEL");
    Args a = args_de(c); (void)a;
    GLchar * a0 = (GLchar *)G2H(arg32(&a));
    GLuint * a1 = (GLuint *)G2H(arg32(&a));
    p(a0, a1);
}
void G_glGetPerfQueryInfoINTEL(CPU *c) { RT_PRIMEIRA("glGetPerfQueryInfoINTEL");
    static void (*p)(GLuint, GLuint, GLchar *, GLuint *, GLuint *, GLuint *, GLuint *); if (!p) p = gl_proc("glGetPerfQueryInfoINTEL");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLuint a1 = (GLuint)arg32(&a);
    GLchar * a2 = (GLchar *)G2H(arg32(&a));
    GLuint * a3 = (GLuint *)G2H(arg32(&a));
    GLuint * a4 = (GLuint *)G2H(arg32(&a));
    GLuint * a5 = (GLuint *)G2H(arg32(&a));
    GLuint * a6 = (GLuint *)G2H(arg32(&a));
    p(a0, a1, a2, a3, a4, a5, a6);
}
void G_glGetProgramBinary(CPU *c) { RT_PRIMEIRA("glGetProgramBinary");
    static void (*p)(GLuint, GLsizei, GLsizei *, GLenum *, void *); if (!p) p = gl_proc("glGetProgramBinary");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    GLsizei * a2 = (GLsizei *)G2H(arg32(&a));
    GLenum * a3 = (GLenum *)G2H(arg32(&a));
    void * a4 = (void *)G2H(arg32(&a));
    p(a0, a1, a2, a3, a4);
}
void G_glGetProgramBinaryOES(CPU *c) { RT_PRIMEIRA("glGetProgramBinaryOES");
    static void (*p)(GLuint, GLsizei, GLsizei *, GLenum *, void *); if (!p) p = gl_proc("glGetProgramBinaryOES");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    GLsizei * a2 = (GLsizei *)G2H(arg32(&a));
    GLenum * a3 = (GLenum *)G2H(arg32(&a));
    void * a4 = (void *)G2H(arg32(&a));
    p(a0, a1, a2, a3, a4);
}
void G_glGetProgramInfoLog(CPU *c) { RT_PRIMEIRA("glGetProgramInfoLog");
    static void (*p)(GLuint, GLsizei, GLsizei *, GLchar *); if (!p) p = gl_proc("glGetProgramInfoLog");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    GLsizei * a2 = (GLsizei *)G2H(arg32(&a));
    GLchar * a3 = (GLchar *)G2H(arg32(&a));
    p(a0, a1, a2, a3);
}
void G_glGetProgramInterfaceiv(CPU *c) { RT_PRIMEIRA("glGetProgramInterfaceiv");
    static void (*p)(GLuint, GLenum, GLenum, GLint *); if (!p) p = gl_proc("glGetProgramInterfaceiv");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLenum a2 = (GLenum)arg32(&a);
    GLint * a3 = (GLint *)G2H(arg32(&a));
    p(a0, a1, a2, a3);
}
void G_glGetProgramPipelineInfoLog(CPU *c) { RT_PRIMEIRA("glGetProgramPipelineInfoLog");
    static void (*p)(GLuint, GLsizei, GLsizei *, GLchar *); if (!p) p = gl_proc("glGetProgramPipelineInfoLog");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    GLsizei * a2 = (GLsizei *)G2H(arg32(&a));
    GLchar * a3 = (GLchar *)G2H(arg32(&a));
    p(a0, a1, a2, a3);
}
void G_glGetProgramPipelineInfoLogEXT(CPU *c) { RT_PRIMEIRA("glGetProgramPipelineInfoLogEXT");
    static void (*p)(GLuint, GLsizei, GLsizei *, GLchar *); if (!p) p = gl_proc("glGetProgramPipelineInfoLogEXT");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    GLsizei * a2 = (GLsizei *)G2H(arg32(&a));
    GLchar * a3 = (GLchar *)G2H(arg32(&a));
    p(a0, a1, a2, a3);
}
void G_glGetProgramPipelineiv(CPU *c) { RT_PRIMEIRA("glGetProgramPipelineiv");
    static void (*p)(GLuint, GLenum, GLint *); if (!p) p = gl_proc("glGetProgramPipelineiv");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLint * a2 = (GLint *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glGetProgramPipelineivEXT(CPU *c) { RT_PRIMEIRA("glGetProgramPipelineivEXT");
    static void (*p)(GLuint, GLenum, GLint *); if (!p) p = gl_proc("glGetProgramPipelineivEXT");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLint * a2 = (GLint *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glGetProgramResourceIndex(CPU *c) { RT_PRIMEIRA("glGetProgramResourceIndex");
    static GLuint (*p)(GLuint, GLenum, const GLchar *); if (!p) p = gl_proc("glGetProgramResourceIndex");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    const GLchar * a2 = (const GLchar *)G2H(arg32(&a));
    ret32(c, (uint32_t)p(a0, a1, a2));
}
void G_glGetProgramResourceLocation(CPU *c) { RT_PRIMEIRA("glGetProgramResourceLocation");
    static GLint (*p)(GLuint, GLenum, const GLchar *); if (!p) p = gl_proc("glGetProgramResourceLocation");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    const GLchar * a2 = (const GLchar *)G2H(arg32(&a));
    ret32(c, (uint32_t)p(a0, a1, a2));
}
void G_glGetProgramResourceLocationIndexEXT(CPU *c) { RT_PRIMEIRA("glGetProgramResourceLocationIndexEXT");
    static GLint (*p)(GLuint, GLenum, const GLchar *); if (!p) p = gl_proc("glGetProgramResourceLocationIndexEXT");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    const GLchar * a2 = (const GLchar *)G2H(arg32(&a));
    ret32(c, (uint32_t)p(a0, a1, a2));
}
void G_glGetProgramResourceName(CPU *c) { RT_PRIMEIRA("glGetProgramResourceName");
    static void (*p)(GLuint, GLenum, GLuint, GLsizei, GLsizei *, GLchar *); if (!p) p = gl_proc("glGetProgramResourceName");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLuint a2 = (GLuint)arg32(&a);
    GLsizei a3 = (GLsizei)arg32(&a);
    GLsizei * a4 = (GLsizei *)G2H(arg32(&a));
    GLchar * a5 = (GLchar *)G2H(arg32(&a));
    p(a0, a1, a2, a3, a4, a5);
}
void G_glGetProgramResourcefvNV(CPU *c) { RT_PRIMEIRA("glGetProgramResourcefvNV");
    static void (*p)(GLuint, GLenum, GLuint, GLsizei, const GLenum *, GLsizei, GLsizei *, GLfloat *); if (!p) p = gl_proc("glGetProgramResourcefvNV");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLuint a2 = (GLuint)arg32(&a);
    GLsizei a3 = (GLsizei)arg32(&a);
    const GLenum * a4 = (const GLenum *)G2H(arg32(&a));
    GLsizei a5 = (GLsizei)arg32(&a);
    GLsizei * a6 = (GLsizei *)G2H(arg32(&a));
    GLfloat * a7 = (GLfloat *)G2H(arg32(&a));
    p(a0, a1, a2, a3, a4, a5, a6, a7);
}
void G_glGetProgramResourceiv(CPU *c) { RT_PRIMEIRA("glGetProgramResourceiv");
    static void (*p)(GLuint, GLenum, GLuint, GLsizei, const GLenum *, GLsizei, GLsizei *, GLint *); if (!p) p = gl_proc("glGetProgramResourceiv");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLuint a2 = (GLuint)arg32(&a);
    GLsizei a3 = (GLsizei)arg32(&a);
    const GLenum * a4 = (const GLenum *)G2H(arg32(&a));
    GLsizei a5 = (GLsizei)arg32(&a);
    GLsizei * a6 = (GLsizei *)G2H(arg32(&a));
    GLint * a7 = (GLint *)G2H(arg32(&a));
    p(a0, a1, a2, a3, a4, a5, a6, a7);
}
void G_glGetProgramiv(CPU *c) { RT_PRIMEIRA("glGetProgramiv");
    static void (*p)(GLuint, GLenum, GLint *); if (!p) p = gl_proc("glGetProgramiv");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLint * a2 = (GLint *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glGetQueryObjecti64vEXT(CPU *c) { RT_PRIMEIRA("glGetQueryObjecti64vEXT");
    static void (*p)(GLuint, GLenum, GLint64 *); if (!p) p = gl_proc("glGetQueryObjecti64vEXT");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLint64 * a2 = (GLint64 *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glGetQueryObjectivEXT(CPU *c) { RT_PRIMEIRA("glGetQueryObjectivEXT");
    static void (*p)(GLuint, GLenum, GLint *); if (!p) p = gl_proc("glGetQueryObjectivEXT");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLint * a2 = (GLint *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glGetQueryObjectui64vEXT(CPU *c) { RT_PRIMEIRA("glGetQueryObjectui64vEXT");
    static void (*p)(GLuint, GLenum, GLuint64 *); if (!p) p = gl_proc("glGetQueryObjectui64vEXT");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLuint64 * a2 = (GLuint64 *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glGetQueryObjectuiv(CPU *c) { RT_PRIMEIRA("glGetQueryObjectuiv");
    static void (*p)(GLuint, GLenum, GLuint *); if (!p) p = gl_proc("glGetQueryObjectuiv");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLuint * a2 = (GLuint *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glGetQueryObjectuivEXT(CPU *c) { RT_PRIMEIRA("glGetQueryObjectuivEXT");
    static void (*p)(GLuint, GLenum, GLuint *); if (!p) p = gl_proc("glGetQueryObjectuivEXT");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLuint * a2 = (GLuint *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glGetQueryiv(CPU *c) { RT_PRIMEIRA("glGetQueryiv");
    static void (*p)(GLenum, GLenum, GLint *); if (!p) p = gl_proc("glGetQueryiv");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLint * a2 = (GLint *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glGetQueryivEXT(CPU *c) { RT_PRIMEIRA("glGetQueryivEXT");
    static void (*p)(GLenum, GLenum, GLint *); if (!p) p = gl_proc("glGetQueryivEXT");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLint * a2 = (GLint *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glGetRenderbufferParameteriv(CPU *c) { RT_PRIMEIRA("glGetRenderbufferParameteriv");
    static void (*p)(GLenum, GLenum, GLint *); if (!p) p = gl_proc("glGetRenderbufferParameteriv");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLint * a2 = (GLint *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glGetSamplerParameterIiv(CPU *c) { RT_PRIMEIRA("glGetSamplerParameterIiv");
    static void (*p)(GLuint, GLenum, GLint *); if (!p) p = gl_proc("glGetSamplerParameterIiv");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLint * a2 = (GLint *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glGetSamplerParameterIivEXT(CPU *c) { RT_PRIMEIRA("glGetSamplerParameterIivEXT");
    static void (*p)(GLuint, GLenum, GLint *); if (!p) p = gl_proc("glGetSamplerParameterIivEXT");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLint * a2 = (GLint *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glGetSamplerParameterIivOES(CPU *c) { RT_PRIMEIRA("glGetSamplerParameterIivOES");
    static void (*p)(GLuint, GLenum, GLint *); if (!p) p = gl_proc("glGetSamplerParameterIivOES");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLint * a2 = (GLint *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glGetSamplerParameterIuiv(CPU *c) { RT_PRIMEIRA("glGetSamplerParameterIuiv");
    static void (*p)(GLuint, GLenum, GLuint *); if (!p) p = gl_proc("glGetSamplerParameterIuiv");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLuint * a2 = (GLuint *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glGetSamplerParameterIuivEXT(CPU *c) { RT_PRIMEIRA("glGetSamplerParameterIuivEXT");
    static void (*p)(GLuint, GLenum, GLuint *); if (!p) p = gl_proc("glGetSamplerParameterIuivEXT");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLuint * a2 = (GLuint *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glGetSamplerParameterIuivOES(CPU *c) { RT_PRIMEIRA("glGetSamplerParameterIuivOES");
    static void (*p)(GLuint, GLenum, GLuint *); if (!p) p = gl_proc("glGetSamplerParameterIuivOES");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLuint * a2 = (GLuint *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glGetSamplerParameterfv(CPU *c) { RT_PRIMEIRA("glGetSamplerParameterfv");
    static void (*p)(GLuint, GLenum, GLfloat *); if (!p) p = gl_proc("glGetSamplerParameterfv");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLfloat * a2 = (GLfloat *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glGetSamplerParameteriv(CPU *c) { RT_PRIMEIRA("glGetSamplerParameteriv");
    static void (*p)(GLuint, GLenum, GLint *); if (!p) p = gl_proc("glGetSamplerParameteriv");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLint * a2 = (GLint *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glGetSemaphoreParameterui64vEXT(CPU *c) { RT_PRIMEIRA("glGetSemaphoreParameterui64vEXT");
    static void (*p)(GLuint, GLenum, GLuint64 *); if (!p) p = gl_proc("glGetSemaphoreParameterui64vEXT");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLuint64 * a2 = (GLuint64 *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glGetShaderInfoLog(CPU *c) { RT_PRIMEIRA("glGetShaderInfoLog");
    static void (*p)(GLuint, GLsizei, GLsizei *, GLchar *); if (!p) p = gl_proc("glGetShaderInfoLog");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    GLsizei * a2 = (GLsizei *)G2H(arg32(&a));
    GLchar * a3 = (GLchar *)G2H(arg32(&a));
    p(a0, a1, a2, a3);
}
void G_glGetShaderPrecisionFormat(CPU *c) { RT_PRIMEIRA("glGetShaderPrecisionFormat");
    static void (*p)(GLenum, GLenum, GLint *, GLint *); if (!p) p = gl_proc("glGetShaderPrecisionFormat");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLint * a2 = (GLint *)G2H(arg32(&a));
    GLint * a3 = (GLint *)G2H(arg32(&a));
    p(a0, a1, a2, a3);
}
void G_glGetShaderSource(CPU *c) { RT_PRIMEIRA("glGetShaderSource");
    static void (*p)(GLuint, GLsizei, GLsizei *, GLchar *); if (!p) p = gl_proc("glGetShaderSource");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    GLsizei * a2 = (GLsizei *)G2H(arg32(&a));
    GLchar * a3 = (GLchar *)G2H(arg32(&a));
    p(a0, a1, a2, a3);
}
void G_glGetShaderiv(CPU *c) { RT_PRIMEIRA("glGetShaderiv");
    static void (*p)(GLuint, GLenum, GLint *); if (!p) p = gl_proc("glGetShaderiv");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLint * a2 = (GLint *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glGetTexLevelParameterfv(CPU *c) { RT_PRIMEIRA("glGetTexLevelParameterfv");
    static void (*p)(GLenum, GLint, GLenum, GLfloat *); if (!p) p = gl_proc("glGetTexLevelParameterfv");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLenum a2 = (GLenum)arg32(&a);
    GLfloat * a3 = (GLfloat *)G2H(arg32(&a));
    p(a0, a1, a2, a3);
}
void G_glGetTexLevelParameteriv(CPU *c) { RT_PRIMEIRA("glGetTexLevelParameteriv");
    static void (*p)(GLenum, GLint, GLenum, GLint *); if (!p) p = gl_proc("glGetTexLevelParameteriv");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLenum a2 = (GLenum)arg32(&a);
    GLint * a3 = (GLint *)G2H(arg32(&a));
    p(a0, a1, a2, a3);
}
void G_glGetTexParameterIiv(CPU *c) { RT_PRIMEIRA("glGetTexParameterIiv");
    static void (*p)(GLenum, GLenum, GLint *); if (!p) p = gl_proc("glGetTexParameterIiv");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLint * a2 = (GLint *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glGetTexParameterIivEXT(CPU *c) { RT_PRIMEIRA("glGetTexParameterIivEXT");
    static void (*p)(GLenum, GLenum, GLint *); if (!p) p = gl_proc("glGetTexParameterIivEXT");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLint * a2 = (GLint *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glGetTexParameterIivOES(CPU *c) { RT_PRIMEIRA("glGetTexParameterIivOES");
    static void (*p)(GLenum, GLenum, GLint *); if (!p) p = gl_proc("glGetTexParameterIivOES");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLint * a2 = (GLint *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glGetTexParameterIuiv(CPU *c) { RT_PRIMEIRA("glGetTexParameterIuiv");
    static void (*p)(GLenum, GLenum, GLuint *); if (!p) p = gl_proc("glGetTexParameterIuiv");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLuint * a2 = (GLuint *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glGetTexParameterIuivEXT(CPU *c) { RT_PRIMEIRA("glGetTexParameterIuivEXT");
    static void (*p)(GLenum, GLenum, GLuint *); if (!p) p = gl_proc("glGetTexParameterIuivEXT");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLuint * a2 = (GLuint *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glGetTexParameterIuivOES(CPU *c) { RT_PRIMEIRA("glGetTexParameterIuivOES");
    static void (*p)(GLenum, GLenum, GLuint *); if (!p) p = gl_proc("glGetTexParameterIuivOES");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLuint * a2 = (GLuint *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glGetTexParameterfv(CPU *c) { RT_PRIMEIRA("glGetTexParameterfv");
    static void (*p)(GLenum, GLenum, GLfloat *); if (!p) p = gl_proc("glGetTexParameterfv");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLfloat * a2 = (GLfloat *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glGetTexParameteriv(CPU *c) { RT_PRIMEIRA("glGetTexParameteriv");
    static void (*p)(GLenum, GLenum, GLint *); if (!p) p = gl_proc("glGetTexParameteriv");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLint * a2 = (GLint *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glGetTransformFeedbackVarying(CPU *c) { RT_PRIMEIRA("glGetTransformFeedbackVarying");
    static void (*p)(GLuint, GLuint, GLsizei, GLsizei *, GLsizei *, GLenum *, GLchar *); if (!p) p = gl_proc("glGetTransformFeedbackVarying");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLuint a1 = (GLuint)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    GLsizei * a3 = (GLsizei *)G2H(arg32(&a));
    GLsizei * a4 = (GLsizei *)G2H(arg32(&a));
    GLenum * a5 = (GLenum *)G2H(arg32(&a));
    GLchar * a6 = (GLchar *)G2H(arg32(&a));
    p(a0, a1, a2, a3, a4, a5, a6);
}
void G_glGetTranslatedShaderSourceANGLE(CPU *c) { RT_PRIMEIRA("glGetTranslatedShaderSourceANGLE");
    static void (*p)(GLuint, GLsizei, GLsizei *, GLchar *); if (!p) p = gl_proc("glGetTranslatedShaderSourceANGLE");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    GLsizei * a2 = (GLsizei *)G2H(arg32(&a));
    GLchar * a3 = (GLchar *)G2H(arg32(&a));
    p(a0, a1, a2, a3);
}
void G_glGetUniformBlockIndex(CPU *c) { RT_PRIMEIRA("glGetUniformBlockIndex");
    static GLuint (*p)(GLuint, const GLchar *); if (!p) p = gl_proc("glGetUniformBlockIndex");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    const GLchar * a1 = (const GLchar *)G2H(arg32(&a));
    ret32(c, (uint32_t)p(a0, a1));
}
void G_glGetUniformLocation(CPU *c) { RT_PRIMEIRA("glGetUniformLocation");
    static GLint (*p)(GLuint, const GLchar *); if (!p) p = gl_proc("glGetUniformLocation");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    const GLchar * a1 = (const GLchar *)G2H(arg32(&a));
    ret32(c, (uint32_t)p(a0, a1));
}
void G_glGetUniformfv(CPU *c) { RT_PRIMEIRA("glGetUniformfv");
    static void (*p)(GLuint, GLint, GLfloat *); if (!p) p = gl_proc("glGetUniformfv");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLfloat * a2 = (GLfloat *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glGetUniformi64vNV(CPU *c) { RT_PRIMEIRA("glGetUniformi64vNV");
    static void (*p)(GLuint, GLint, GLint64EXT *); if (!p) p = gl_proc("glGetUniformi64vNV");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLint64EXT * a2 = (GLint64EXT *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glGetUniformiv(CPU *c) { RT_PRIMEIRA("glGetUniformiv");
    static void (*p)(GLuint, GLint, GLint *); if (!p) p = gl_proc("glGetUniformiv");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLint * a2 = (GLint *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glGetUniformuiv(CPU *c) { RT_PRIMEIRA("glGetUniformuiv");
    static void (*p)(GLuint, GLint, GLuint *); if (!p) p = gl_proc("glGetUniformuiv");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLuint * a2 = (GLuint *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glGetUnsignedBytei_vEXT(CPU *c) { RT_PRIMEIRA("glGetUnsignedBytei_vEXT");
    static void (*p)(GLenum, GLuint, GLubyte *); if (!p) p = gl_proc("glGetUnsignedBytei_vEXT");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLuint a1 = (GLuint)arg32(&a);
    GLubyte * a2 = (GLubyte *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glGetUnsignedBytevEXT(CPU *c) { RT_PRIMEIRA("glGetUnsignedBytevEXT");
    static void (*p)(GLenum, GLubyte *); if (!p) p = gl_proc("glGetUnsignedBytevEXT");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLubyte * a1 = (GLubyte *)G2H(arg32(&a));
    p(a0, a1);
}
void G_glGetVertexAttribIiv(CPU *c) { RT_PRIMEIRA("glGetVertexAttribIiv");
    static void (*p)(GLuint, GLenum, GLint *); if (!p) p = gl_proc("glGetVertexAttribIiv");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLint * a2 = (GLint *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glGetVertexAttribIuiv(CPU *c) { RT_PRIMEIRA("glGetVertexAttribIuiv");
    static void (*p)(GLuint, GLenum, GLuint *); if (!p) p = gl_proc("glGetVertexAttribIuiv");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLuint * a2 = (GLuint *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glGetVertexAttribfv(CPU *c) { RT_PRIMEIRA("glGetVertexAttribfv");
    static void (*p)(GLuint, GLenum, GLfloat *); if (!p) p = gl_proc("glGetVertexAttribfv");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLfloat * a2 = (GLfloat *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glGetVertexAttribiv(CPU *c) { RT_PRIMEIRA("glGetVertexAttribiv");
    static void (*p)(GLuint, GLenum, GLint *); if (!p) p = gl_proc("glGetVertexAttribiv");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLint * a2 = (GLint *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glGetnUniformfv(CPU *c) { RT_PRIMEIRA("glGetnUniformfv");
    static void (*p)(GLuint, GLint, GLsizei, GLfloat *); if (!p) p = gl_proc("glGetnUniformfv");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    GLfloat * a3 = (GLfloat *)G2H(arg32(&a));
    p(a0, a1, a2, a3);
}
void G_glGetnUniformfvEXT(CPU *c) { RT_PRIMEIRA("glGetnUniformfvEXT");
    static void (*p)(GLuint, GLint, GLsizei, GLfloat *); if (!p) p = gl_proc("glGetnUniformfvEXT");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    GLfloat * a3 = (GLfloat *)G2H(arg32(&a));
    p(a0, a1, a2, a3);
}
void G_glGetnUniformfvKHR(CPU *c) { RT_PRIMEIRA("glGetnUniformfvKHR");
    static void (*p)(GLuint, GLint, GLsizei, GLfloat *); if (!p) p = gl_proc("glGetnUniformfvKHR");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    GLfloat * a3 = (GLfloat *)G2H(arg32(&a));
    p(a0, a1, a2, a3);
}
void G_glGetnUniformiv(CPU *c) { RT_PRIMEIRA("glGetnUniformiv");
    static void (*p)(GLuint, GLint, GLsizei, GLint *); if (!p) p = gl_proc("glGetnUniformiv");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    GLint * a3 = (GLint *)G2H(arg32(&a));
    p(a0, a1, a2, a3);
}
void G_glGetnUniformivEXT(CPU *c) { RT_PRIMEIRA("glGetnUniformivEXT");
    static void (*p)(GLuint, GLint, GLsizei, GLint *); if (!p) p = gl_proc("glGetnUniformivEXT");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    GLint * a3 = (GLint *)G2H(arg32(&a));
    p(a0, a1, a2, a3);
}
void G_glGetnUniformivKHR(CPU *c) { RT_PRIMEIRA("glGetnUniformivKHR");
    static void (*p)(GLuint, GLint, GLsizei, GLint *); if (!p) p = gl_proc("glGetnUniformivKHR");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    GLint * a3 = (GLint *)G2H(arg32(&a));
    p(a0, a1, a2, a3);
}
void G_glGetnUniformuiv(CPU *c) { RT_PRIMEIRA("glGetnUniformuiv");
    static void (*p)(GLuint, GLint, GLsizei, GLuint *); if (!p) p = gl_proc("glGetnUniformuiv");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    GLuint * a3 = (GLuint *)G2H(arg32(&a));
    p(a0, a1, a2, a3);
}
void G_glGetnUniformuivKHR(CPU *c) { RT_PRIMEIRA("glGetnUniformuivKHR");
    static void (*p)(GLuint, GLint, GLsizei, GLuint *); if (!p) p = gl_proc("glGetnUniformuivKHR");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    GLuint * a3 = (GLuint *)G2H(arg32(&a));
    p(a0, a1, a2, a3);
}
void G_glHint(CPU *c) { RT_PRIMEIRA("glHint");
    static void (*p)(GLenum, GLenum); if (!p) p = gl_proc("glHint");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    p(a0, a1);
}
void G_glImportMemoryFdEXT(CPU *c) { RT_PRIMEIRA("glImportMemoryFdEXT");
    static void (*p)(GLuint, GLuint64, GLenum, GLint); if (!p) p = gl_proc("glImportMemoryFdEXT");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLuint64 a1 = (GLuint64)arg64(&a);
    GLenum a2 = (GLenum)arg32(&a);
    GLint a3 = (GLint)arg32(&a);
    p(a0, a1, a2, a3);
}
void G_glImportMemoryWin32HandleEXT(CPU *c) { RT_PRIMEIRA("glImportMemoryWin32HandleEXT");
    static void (*p)(GLuint, GLuint64, GLenum, void *); if (!p) p = gl_proc("glImportMemoryWin32HandleEXT");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLuint64 a1 = (GLuint64)arg64(&a);
    GLenum a2 = (GLenum)arg32(&a);
    void * a3 = (void *)G2H(arg32(&a));
    p(a0, a1, a2, a3);
}
void G_glImportMemoryWin32NameEXT(CPU *c) { RT_PRIMEIRA("glImportMemoryWin32NameEXT");
    static void (*p)(GLuint, GLuint64, GLenum, const void *); if (!p) p = gl_proc("glImportMemoryWin32NameEXT");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLuint64 a1 = (GLuint64)arg64(&a);
    GLenum a2 = (GLenum)arg32(&a);
    const void * a3 = (const void *)G2H(arg32(&a));
    p(a0, a1, a2, a3);
}
void G_glImportSemaphoreFdEXT(CPU *c) { RT_PRIMEIRA("glImportSemaphoreFdEXT");
    static void (*p)(GLuint, GLenum, GLint); if (!p) p = gl_proc("glImportSemaphoreFdEXT");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLint a2 = (GLint)arg32(&a);
    p(a0, a1, a2);
}
void G_glImportSemaphoreWin32HandleEXT(CPU *c) { RT_PRIMEIRA("glImportSemaphoreWin32HandleEXT");
    static void (*p)(GLuint, GLenum, void *); if (!p) p = gl_proc("glImportSemaphoreWin32HandleEXT");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    void * a2 = (void *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glImportSemaphoreWin32NameEXT(CPU *c) { RT_PRIMEIRA("glImportSemaphoreWin32NameEXT");
    static void (*p)(GLuint, GLenum, const void *); if (!p) p = gl_proc("glImportSemaphoreWin32NameEXT");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    const void * a2 = (const void *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glInsertEventMarkerEXT(CPU *c) { RT_PRIMEIRA("glInsertEventMarkerEXT");
    static void (*p)(GLsizei, const GLchar *); if (!p) p = gl_proc("glInsertEventMarkerEXT");
    Args a = args_de(c); (void)a;
    GLsizei a0 = (GLsizei)arg32(&a);
    const GLchar * a1 = (const GLchar *)G2H(arg32(&a));
    p(a0, a1);
}
void G_glInterpolatePathsNV(CPU *c) { RT_PRIMEIRA("glInterpolatePathsNV");
    static void (*p)(GLuint, GLuint, GLuint, GLfloat); if (!p) p = gl_proc("glInterpolatePathsNV");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLuint a1 = (GLuint)arg32(&a);
    GLuint a2 = (GLuint)arg32(&a);
    GLfloat a3 = argf(&a);
    p(a0, a1, a2, a3);
}
void G_glInvalidateFramebuffer(CPU *c) { RT_PRIMEIRA("glInvalidateFramebuffer");
    static void (*p)(GLenum, GLsizei, const GLenum *); if (!p) p = gl_proc("glInvalidateFramebuffer");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    const GLenum * a2 = (const GLenum *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glInvalidateSubFramebuffer(CPU *c) { RT_PRIMEIRA("glInvalidateSubFramebuffer");
    static void (*p)(GLenum, GLsizei, const GLenum *, GLint, GLint, GLsizei, GLsizei); if (!p) p = gl_proc("glInvalidateSubFramebuffer");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    const GLenum * a2 = (const GLenum *)G2H(arg32(&a));
    GLint a3 = (GLint)arg32(&a);
    GLint a4 = (GLint)arg32(&a);
    GLsizei a5 = (GLsizei)arg32(&a);
    GLsizei a6 = (GLsizei)arg32(&a);
    p(a0, a1, a2, a3, a4, a5, a6);
}
void G_glIsBuffer(CPU *c) { RT_PRIMEIRA("glIsBuffer");
    static GLboolean (*p)(GLuint); if (!p) p = gl_proc("glIsBuffer");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    ret32(c, (uint32_t)p(a0));
}
void G_glIsEnabled(CPU *c) { RT_PRIMEIRA("glIsEnabled");
    static GLboolean (*p)(GLenum); if (!p) p = gl_proc("glIsEnabled");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    ret32(c, (uint32_t)p(a0));
}
void G_glIsEnabledi(CPU *c) { RT_PRIMEIRA("glIsEnabledi");
    static GLboolean (*p)(GLenum, GLuint); if (!p) p = gl_proc("glIsEnabledi");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLuint a1 = (GLuint)arg32(&a);
    ret32(c, (uint32_t)p(a0, a1));
}
void G_glIsEnablediEXT(CPU *c) { RT_PRIMEIRA("glIsEnablediEXT");
    static GLboolean (*p)(GLenum, GLuint); if (!p) p = gl_proc("glIsEnablediEXT");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLuint a1 = (GLuint)arg32(&a);
    ret32(c, (uint32_t)p(a0, a1));
}
void G_glIsEnablediNV(CPU *c) { RT_PRIMEIRA("glIsEnablediNV");
    static GLboolean (*p)(GLenum, GLuint); if (!p) p = gl_proc("glIsEnablediNV");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLuint a1 = (GLuint)arg32(&a);
    ret32(c, (uint32_t)p(a0, a1));
}
void G_glIsEnablediOES(CPU *c) { RT_PRIMEIRA("glIsEnablediOES");
    static GLboolean (*p)(GLenum, GLuint); if (!p) p = gl_proc("glIsEnablediOES");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLuint a1 = (GLuint)arg32(&a);
    ret32(c, (uint32_t)p(a0, a1));
}
void G_glIsFenceNV(CPU *c) { RT_PRIMEIRA("glIsFenceNV");
    static GLboolean (*p)(GLuint); if (!p) p = gl_proc("glIsFenceNV");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    ret32(c, (uint32_t)p(a0));
}
void G_glIsFramebuffer(CPU *c) { RT_PRIMEIRA("glIsFramebuffer");
    static GLboolean (*p)(GLuint); if (!p) p = gl_proc("glIsFramebuffer");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    ret32(c, (uint32_t)p(a0));
}
void G_glIsImageHandleResidentNV(CPU *c) { RT_PRIMEIRA("glIsImageHandleResidentNV");
    static GLboolean (*p)(GLuint64); if (!p) p = gl_proc("glIsImageHandleResidentNV");
    Args a = args_de(c); (void)a;
    GLuint64 a0 = (GLuint64)arg64(&a);
    ret32(c, (uint32_t)p(a0));
}
void G_glIsMemoryObjectEXT(CPU *c) { RT_PRIMEIRA("glIsMemoryObjectEXT");
    static GLboolean (*p)(GLuint); if (!p) p = gl_proc("glIsMemoryObjectEXT");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    ret32(c, (uint32_t)p(a0));
}
void G_glIsPathNV(CPU *c) { RT_PRIMEIRA("glIsPathNV");
    static GLboolean (*p)(GLuint); if (!p) p = gl_proc("glIsPathNV");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    ret32(c, (uint32_t)p(a0));
}
void G_glIsPointInFillPathNV(CPU *c) { RT_PRIMEIRA("glIsPointInFillPathNV");
    static GLboolean (*p)(GLuint, GLuint, GLfloat, GLfloat); if (!p) p = gl_proc("glIsPointInFillPathNV");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLuint a1 = (GLuint)arg32(&a);
    GLfloat a2 = argf(&a);
    GLfloat a3 = argf(&a);
    ret32(c, (uint32_t)p(a0, a1, a2, a3));
}
void G_glIsPointInStrokePathNV(CPU *c) { RT_PRIMEIRA("glIsPointInStrokePathNV");
    static GLboolean (*p)(GLuint, GLfloat, GLfloat); if (!p) p = gl_proc("glIsPointInStrokePathNV");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLfloat a1 = argf(&a);
    GLfloat a2 = argf(&a);
    ret32(c, (uint32_t)p(a0, a1, a2));
}
void G_glIsProgram(CPU *c) { RT_PRIMEIRA("glIsProgram");
    static GLboolean (*p)(GLuint); if (!p) p = gl_proc("glIsProgram");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    ret32(c, (uint32_t)p(a0));
}
void G_glIsProgramPipeline(CPU *c) { RT_PRIMEIRA("glIsProgramPipeline");
    static GLboolean (*p)(GLuint); if (!p) p = gl_proc("glIsProgramPipeline");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    ret32(c, (uint32_t)p(a0));
}
void G_glIsProgramPipelineEXT(CPU *c) { RT_PRIMEIRA("glIsProgramPipelineEXT");
    static GLboolean (*p)(GLuint); if (!p) p = gl_proc("glIsProgramPipelineEXT");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    ret32(c, (uint32_t)p(a0));
}
void G_glIsQuery(CPU *c) { RT_PRIMEIRA("glIsQuery");
    static GLboolean (*p)(GLuint); if (!p) p = gl_proc("glIsQuery");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    ret32(c, (uint32_t)p(a0));
}
void G_glIsQueryEXT(CPU *c) { RT_PRIMEIRA("glIsQueryEXT");
    static GLboolean (*p)(GLuint); if (!p) p = gl_proc("glIsQueryEXT");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    ret32(c, (uint32_t)p(a0));
}
void G_glIsRenderbuffer(CPU *c) { RT_PRIMEIRA("glIsRenderbuffer");
    static GLboolean (*p)(GLuint); if (!p) p = gl_proc("glIsRenderbuffer");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    ret32(c, (uint32_t)p(a0));
}
void G_glIsSampler(CPU *c) { RT_PRIMEIRA("glIsSampler");
    static GLboolean (*p)(GLuint); if (!p) p = gl_proc("glIsSampler");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    ret32(c, (uint32_t)p(a0));
}
void G_glIsSemaphoreEXT(CPU *c) { RT_PRIMEIRA("glIsSemaphoreEXT");
    static GLboolean (*p)(GLuint); if (!p) p = gl_proc("glIsSemaphoreEXT");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    ret32(c, (uint32_t)p(a0));
}
void G_glIsShader(CPU *c) { RT_PRIMEIRA("glIsShader");
    static GLboolean (*p)(GLuint); if (!p) p = gl_proc("glIsShader");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    ret32(c, (uint32_t)p(a0));
}
void G_glIsTexture(CPU *c) { RT_PRIMEIRA("glIsTexture");
    static GLboolean (*p)(GLuint); if (!p) p = gl_proc("glIsTexture");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    ret32(c, (uint32_t)p(a0));
}
void G_glIsTextureHandleResidentNV(CPU *c) { RT_PRIMEIRA("glIsTextureHandleResidentNV");
    static GLboolean (*p)(GLuint64); if (!p) p = gl_proc("glIsTextureHandleResidentNV");
    Args a = args_de(c); (void)a;
    GLuint64 a0 = (GLuint64)arg64(&a);
    ret32(c, (uint32_t)p(a0));
}
void G_glIsTransformFeedback(CPU *c) { RT_PRIMEIRA("glIsTransformFeedback");
    static GLboolean (*p)(GLuint); if (!p) p = gl_proc("glIsTransformFeedback");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    ret32(c, (uint32_t)p(a0));
}
void G_glIsVertexArray(CPU *c) { RT_PRIMEIRA("glIsVertexArray");
    static GLboolean (*p)(GLuint); if (!p) p = gl_proc("glIsVertexArray");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    ret32(c, (uint32_t)p(a0));
}
void G_glIsVertexArrayOES(CPU *c) { RT_PRIMEIRA("glIsVertexArrayOES");
    static GLboolean (*p)(GLuint); if (!p) p = gl_proc("glIsVertexArrayOES");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    ret32(c, (uint32_t)p(a0));
}
void G_glLabelObjectEXT(CPU *c) { RT_PRIMEIRA("glLabelObjectEXT");
    static void (*p)(GLenum, GLuint, GLsizei, const GLchar *); if (!p) p = gl_proc("glLabelObjectEXT");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLuint a1 = (GLuint)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    const GLchar * a3 = (const GLchar *)G2H(arg32(&a));
    p(a0, a1, a2, a3);
}
void G_glLineWidth(CPU *c) { RT_PRIMEIRA("glLineWidth");
    static void (*p)(GLfloat); if (!p) p = gl_proc("glLineWidth");
    Args a = args_de(c); (void)a;
    GLfloat a0 = argf(&a);
    p(a0);
}
void G_glLinkProgram(CPU *c) { RT_PRIMEIRA("glLinkProgram");
    static void (*p)(GLuint); if (!p) p = gl_proc("glLinkProgram");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    p(a0);
#ifdef MGS2_DEPURA
    {   /* medicao: erros de link */
        static int n_erros; GLint ok = 1; glGetProgramiv(a0, GL_LINK_STATUS, &ok);
        if (!ok && __atomic_fetch_add(&n_erros, 1, __ATOMIC_RELAXED) < 5) {
            char b[600]; GLsizei l = 0; glGetProgramInfoLog(a0, sizeof b, &l, b); rt_log("glLinkProgram %u falhou: %.500s", a0, b);
        }
    }
#endif
}
void G_glMakeImageHandleNonResidentNV(CPU *c) { RT_PRIMEIRA("glMakeImageHandleNonResidentNV");
    static void (*p)(GLuint64); if (!p) p = gl_proc("glMakeImageHandleNonResidentNV");
    Args a = args_de(c); (void)a;
    GLuint64 a0 = (GLuint64)arg64(&a);
    p(a0);
}
void G_glMakeImageHandleResidentNV(CPU *c) { RT_PRIMEIRA("glMakeImageHandleResidentNV");
    static void (*p)(GLuint64, GLenum); if (!p) p = gl_proc("glMakeImageHandleResidentNV");
    Args a = args_de(c); (void)a;
    GLuint64 a0 = (GLuint64)arg64(&a);
    GLenum a1 = (GLenum)arg32(&a);
    p(a0, a1);
}
void G_glMakeTextureHandleNonResidentNV(CPU *c) { RT_PRIMEIRA("glMakeTextureHandleNonResidentNV");
    static void (*p)(GLuint64); if (!p) p = gl_proc("glMakeTextureHandleNonResidentNV");
    Args a = args_de(c); (void)a;
    GLuint64 a0 = (GLuint64)arg64(&a);
    p(a0);
}
void G_glMakeTextureHandleResidentNV(CPU *c) { RT_PRIMEIRA("glMakeTextureHandleResidentNV");
    static void (*p)(GLuint64); if (!p) p = gl_proc("glMakeTextureHandleResidentNV");
    Args a = args_de(c); (void)a;
    GLuint64 a0 = (GLuint64)arg64(&a);
    p(a0);
}
void G_glMatrixFrustumEXT(CPU *c) { RT_PRIMEIRA("glMatrixFrustumEXT");
    static void (*p)(GLenum, GLdouble, GLdouble, GLdouble, GLdouble, GLdouble, GLdouble); if (!p) p = gl_proc("glMatrixFrustumEXT");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLdouble a1 = (GLdouble)arg32(&a);
    GLdouble a2 = (GLdouble)arg32(&a);
    GLdouble a3 = (GLdouble)arg32(&a);
    GLdouble a4 = (GLdouble)arg32(&a);
    GLdouble a5 = (GLdouble)arg32(&a);
    GLdouble a6 = (GLdouble)arg32(&a);
    p(a0, a1, a2, a3, a4, a5, a6);
}
void G_glMatrixLoad3x2fNV(CPU *c) { RT_PRIMEIRA("glMatrixLoad3x2fNV");
    static void (*p)(GLenum, const GLfloat *); if (!p) p = gl_proc("glMatrixLoad3x2fNV");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    const GLfloat * a1 = (const GLfloat *)G2H(arg32(&a));
    p(a0, a1);
}
void G_glMatrixLoad3x3fNV(CPU *c) { RT_PRIMEIRA("glMatrixLoad3x3fNV");
    static void (*p)(GLenum, const GLfloat *); if (!p) p = gl_proc("glMatrixLoad3x3fNV");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    const GLfloat * a1 = (const GLfloat *)G2H(arg32(&a));
    p(a0, a1);
}
void G_glMatrixLoadIdentityEXT(CPU *c) { RT_PRIMEIRA("glMatrixLoadIdentityEXT");
    static void (*p)(GLenum); if (!p) p = gl_proc("glMatrixLoadIdentityEXT");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    p(a0);
}
void G_glMatrixLoadTranspose3x3fNV(CPU *c) { RT_PRIMEIRA("glMatrixLoadTranspose3x3fNV");
    static void (*p)(GLenum, const GLfloat *); if (!p) p = gl_proc("glMatrixLoadTranspose3x3fNV");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    const GLfloat * a1 = (const GLfloat *)G2H(arg32(&a));
    p(a0, a1);
}
void G_glMatrixLoadTransposedEXT(CPU *c) { RT_PRIMEIRA("glMatrixLoadTransposedEXT");
    static void (*p)(GLenum, const GLdouble *); if (!p) p = gl_proc("glMatrixLoadTransposedEXT");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    const GLdouble * a1 = (const GLdouble *)G2H(arg32(&a));
    p(a0, a1);
}
void G_glMatrixLoadTransposefEXT(CPU *c) { RT_PRIMEIRA("glMatrixLoadTransposefEXT");
    static void (*p)(GLenum, const GLfloat *); if (!p) p = gl_proc("glMatrixLoadTransposefEXT");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    const GLfloat * a1 = (const GLfloat *)G2H(arg32(&a));
    p(a0, a1);
}
void G_glMatrixLoaddEXT(CPU *c) { RT_PRIMEIRA("glMatrixLoaddEXT");
    static void (*p)(GLenum, const GLdouble *); if (!p) p = gl_proc("glMatrixLoaddEXT");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    const GLdouble * a1 = (const GLdouble *)G2H(arg32(&a));
    p(a0, a1);
}
void G_glMatrixLoadfEXT(CPU *c) { RT_PRIMEIRA("glMatrixLoadfEXT");
    static void (*p)(GLenum, const GLfloat *); if (!p) p = gl_proc("glMatrixLoadfEXT");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    const GLfloat * a1 = (const GLfloat *)G2H(arg32(&a));
    p(a0, a1);
}
void G_glMatrixMult3x2fNV(CPU *c) { RT_PRIMEIRA("glMatrixMult3x2fNV");
    static void (*p)(GLenum, const GLfloat *); if (!p) p = gl_proc("glMatrixMult3x2fNV");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    const GLfloat * a1 = (const GLfloat *)G2H(arg32(&a));
    p(a0, a1);
}
void G_glMatrixMult3x3fNV(CPU *c) { RT_PRIMEIRA("glMatrixMult3x3fNV");
    static void (*p)(GLenum, const GLfloat *); if (!p) p = gl_proc("glMatrixMult3x3fNV");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    const GLfloat * a1 = (const GLfloat *)G2H(arg32(&a));
    p(a0, a1);
}
void G_glMatrixMultTranspose3x3fNV(CPU *c) { RT_PRIMEIRA("glMatrixMultTranspose3x3fNV");
    static void (*p)(GLenum, const GLfloat *); if (!p) p = gl_proc("glMatrixMultTranspose3x3fNV");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    const GLfloat * a1 = (const GLfloat *)G2H(arg32(&a));
    p(a0, a1);
}
void G_glMatrixMultTransposedEXT(CPU *c) { RT_PRIMEIRA("glMatrixMultTransposedEXT");
    static void (*p)(GLenum, const GLdouble *); if (!p) p = gl_proc("glMatrixMultTransposedEXT");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    const GLdouble * a1 = (const GLdouble *)G2H(arg32(&a));
    p(a0, a1);
}
void G_glMatrixMultTransposefEXT(CPU *c) { RT_PRIMEIRA("glMatrixMultTransposefEXT");
    static void (*p)(GLenum, const GLfloat *); if (!p) p = gl_proc("glMatrixMultTransposefEXT");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    const GLfloat * a1 = (const GLfloat *)G2H(arg32(&a));
    p(a0, a1);
}
void G_glMatrixMultdEXT(CPU *c) { RT_PRIMEIRA("glMatrixMultdEXT");
    static void (*p)(GLenum, const GLdouble *); if (!p) p = gl_proc("glMatrixMultdEXT");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    const GLdouble * a1 = (const GLdouble *)G2H(arg32(&a));
    p(a0, a1);
}
void G_glMatrixMultfEXT(CPU *c) { RT_PRIMEIRA("glMatrixMultfEXT");
    static void (*p)(GLenum, const GLfloat *); if (!p) p = gl_proc("glMatrixMultfEXT");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    const GLfloat * a1 = (const GLfloat *)G2H(arg32(&a));
    p(a0, a1);
}
void G_glMatrixOrthoEXT(CPU *c) { RT_PRIMEIRA("glMatrixOrthoEXT");
    static void (*p)(GLenum, GLdouble, GLdouble, GLdouble, GLdouble, GLdouble, GLdouble); if (!p) p = gl_proc("glMatrixOrthoEXT");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLdouble a1 = (GLdouble)arg32(&a);
    GLdouble a2 = (GLdouble)arg32(&a);
    GLdouble a3 = (GLdouble)arg32(&a);
    GLdouble a4 = (GLdouble)arg32(&a);
    GLdouble a5 = (GLdouble)arg32(&a);
    GLdouble a6 = (GLdouble)arg32(&a);
    p(a0, a1, a2, a3, a4, a5, a6);
}
void G_glMatrixPopEXT(CPU *c) { RT_PRIMEIRA("glMatrixPopEXT");
    static void (*p)(GLenum); if (!p) p = gl_proc("glMatrixPopEXT");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    p(a0);
}
void G_glMatrixPushEXT(CPU *c) { RT_PRIMEIRA("glMatrixPushEXT");
    static void (*p)(GLenum); if (!p) p = gl_proc("glMatrixPushEXT");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    p(a0);
}
void G_glMatrixRotatedEXT(CPU *c) { RT_PRIMEIRA("glMatrixRotatedEXT");
    static void (*p)(GLenum, GLdouble, GLdouble, GLdouble, GLdouble); if (!p) p = gl_proc("glMatrixRotatedEXT");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLdouble a1 = (GLdouble)arg32(&a);
    GLdouble a2 = (GLdouble)arg32(&a);
    GLdouble a3 = (GLdouble)arg32(&a);
    GLdouble a4 = (GLdouble)arg32(&a);
    p(a0, a1, a2, a3, a4);
}
void G_glMatrixRotatefEXT(CPU *c) { RT_PRIMEIRA("glMatrixRotatefEXT");
    static void (*p)(GLenum, GLfloat, GLfloat, GLfloat, GLfloat); if (!p) p = gl_proc("glMatrixRotatefEXT");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLfloat a1 = argf(&a);
    GLfloat a2 = argf(&a);
    GLfloat a3 = argf(&a);
    GLfloat a4 = argf(&a);
    p(a0, a1, a2, a3, a4);
}
void G_glMatrixScaledEXT(CPU *c) { RT_PRIMEIRA("glMatrixScaledEXT");
    static void (*p)(GLenum, GLdouble, GLdouble, GLdouble); if (!p) p = gl_proc("glMatrixScaledEXT");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLdouble a1 = (GLdouble)arg32(&a);
    GLdouble a2 = (GLdouble)arg32(&a);
    GLdouble a3 = (GLdouble)arg32(&a);
    p(a0, a1, a2, a3);
}
void G_glMatrixScalefEXT(CPU *c) { RT_PRIMEIRA("glMatrixScalefEXT");
    static void (*p)(GLenum, GLfloat, GLfloat, GLfloat); if (!p) p = gl_proc("glMatrixScalefEXT");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLfloat a1 = argf(&a);
    GLfloat a2 = argf(&a);
    GLfloat a3 = argf(&a);
    p(a0, a1, a2, a3);
}
void G_glMatrixTranslatedEXT(CPU *c) { RT_PRIMEIRA("glMatrixTranslatedEXT");
    static void (*p)(GLenum, GLdouble, GLdouble, GLdouble); if (!p) p = gl_proc("glMatrixTranslatedEXT");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLdouble a1 = (GLdouble)arg32(&a);
    GLdouble a2 = (GLdouble)arg32(&a);
    GLdouble a3 = (GLdouble)arg32(&a);
    p(a0, a1, a2, a3);
}
void G_glMatrixTranslatefEXT(CPU *c) { RT_PRIMEIRA("glMatrixTranslatefEXT");
    static void (*p)(GLenum, GLfloat, GLfloat, GLfloat); if (!p) p = gl_proc("glMatrixTranslatefEXT");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLfloat a1 = argf(&a);
    GLfloat a2 = argf(&a);
    GLfloat a3 = argf(&a);
    p(a0, a1, a2, a3);
}
void G_glMaxShaderCompilerThreadsKHR(CPU *c) { RT_PRIMEIRA("glMaxShaderCompilerThreadsKHR");
    static void (*p)(GLuint); if (!p) p = gl_proc("glMaxShaderCompilerThreadsKHR");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    p(a0);
}
void G_glMemoryBarrier(CPU *c) { RT_PRIMEIRA("glMemoryBarrier");
    static void (*p)(GLbitfield); if (!p) p = gl_proc("glMemoryBarrier");
    Args a = args_de(c); (void)a;
    GLbitfield a0 = (GLbitfield)arg32(&a);
    p(a0);
}
void G_glMemoryBarrierByRegion(CPU *c) { RT_PRIMEIRA("glMemoryBarrierByRegion");
    static void (*p)(GLbitfield); if (!p) p = gl_proc("glMemoryBarrierByRegion");
    Args a = args_de(c); (void)a;
    GLbitfield a0 = (GLbitfield)arg32(&a);
    p(a0);
}
void G_glMemoryObjectParameterivEXT(CPU *c) { RT_PRIMEIRA("glMemoryObjectParameterivEXT");
    static void (*p)(GLuint, GLenum, const GLint *); if (!p) p = gl_proc("glMemoryObjectParameterivEXT");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    const GLint * a2 = (const GLint *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glMinSampleShading(CPU *c) { RT_PRIMEIRA("glMinSampleShading");
    static void (*p)(GLfloat); if (!p) p = gl_proc("glMinSampleShading");
    Args a = args_de(c); (void)a;
    GLfloat a0 = argf(&a);
    p(a0);
}
void G_glMinSampleShadingOES(CPU *c) { RT_PRIMEIRA("glMinSampleShadingOES");
    static void (*p)(GLfloat); if (!p) p = gl_proc("glMinSampleShadingOES");
    Args a = args_de(c); (void)a;
    GLfloat a0 = argf(&a);
    p(a0);
}
void G_glMultiDrawArraysEXT(CPU *c) { RT_PRIMEIRA("glMultiDrawArraysEXT");
    static void (*p)(GLenum, const GLint *, const GLsizei *, GLsizei); if (!p) p = gl_proc("glMultiDrawArraysEXT");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    const GLint * a1 = (const GLint *)G2H(arg32(&a));
    const GLsizei * a2 = (const GLsizei *)G2H(arg32(&a));
    GLsizei a3 = (GLsizei)arg32(&a);
    p(a0, a1, a2, a3);
}
void G_glMultiDrawArraysIndirectEXT(CPU *c) { RT_PRIMEIRA("glMultiDrawArraysIndirectEXT");
    static void (*p)(GLenum, const void *, GLsizei, GLsizei); if (!p) p = gl_proc("glMultiDrawArraysIndirectEXT");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    const void * a1 = (const void *)G2H(arg32(&a));
    GLsizei a2 = (GLsizei)arg32(&a);
    GLsizei a3 = (GLsizei)arg32(&a);
    p(a0, a1, a2, a3);
}
void G_glMultiDrawElementsIndirectEXT(CPU *c) { RT_PRIMEIRA("glMultiDrawElementsIndirectEXT");
    static void (*p)(GLenum, GLenum, const void *, GLsizei, GLsizei); if (!p) p = gl_proc("glMultiDrawElementsIndirectEXT");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    const void * a2 = (const void *)G2H(arg32(&a));
    GLsizei a3 = (GLsizei)arg32(&a);
    GLsizei a4 = (GLsizei)arg32(&a);
    p(a0, a1, a2, a3, a4);
}
void G_glNamedBufferStorageExternalEXT(CPU *c) { RT_PRIMEIRA("glNamedBufferStorageExternalEXT");
    static void (*p)(GLuint, GLintptr, GLsizeiptr, GLeglClientBufferEXT, GLbitfield); if (!p) p = gl_proc("glNamedBufferStorageExternalEXT");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLintptr a1 = (GLintptr)(int32_t)arg32(&a);
    GLsizeiptr a2 = (GLsizeiptr)(int32_t)arg32(&a);
    GLeglClientBufferEXT a3 = (GLeglClientBufferEXT)egl_obj(arg32(&a));
    GLbitfield a4 = (GLbitfield)arg32(&a);
    p(a0, a1, a2, a3, a4);
}
void G_glNamedBufferStorageMemEXT(CPU *c) { RT_PRIMEIRA("glNamedBufferStorageMemEXT");
    static void (*p)(GLuint, GLsizeiptr, GLuint, GLuint64); if (!p) p = gl_proc("glNamedBufferStorageMemEXT");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLsizeiptr a1 = (GLsizeiptr)(int32_t)arg32(&a);
    GLuint a2 = (GLuint)arg32(&a);
    GLuint64 a3 = (GLuint64)arg64(&a);
    p(a0, a1, a2, a3);
}
void G_glNamedFramebufferSampleLocationsfvNV(CPU *c) { RT_PRIMEIRA("glNamedFramebufferSampleLocationsfvNV");
    static void (*p)(GLuint, GLuint, GLsizei, const GLfloat *); if (!p) p = gl_proc("glNamedFramebufferSampleLocationsfvNV");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLuint a1 = (GLuint)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    const GLfloat * a3 = (const GLfloat *)G2H(arg32(&a));
    p(a0, a1, a2, a3);
}
void G_glObjectLabel(CPU *c) { RT_PRIMEIRA("glObjectLabel");
    static void (*p)(GLenum, GLuint, GLsizei, const GLchar *); if (!p) p = gl_proc("glObjectLabel");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLuint a1 = (GLuint)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    const GLchar * a3 = (const GLchar *)G2H(arg32(&a));
    p(a0, a1, a2, a3);
}
void G_glObjectLabelKHR(CPU *c) { RT_PRIMEIRA("glObjectLabelKHR");
    static void (*p)(GLenum, GLuint, GLsizei, const GLchar *); if (!p) p = gl_proc("glObjectLabelKHR");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLuint a1 = (GLuint)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    const GLchar * a3 = (const GLchar *)G2H(arg32(&a));
    p(a0, a1, a2, a3);
}
void G_glObjectPtrLabel(CPU *c) { RT_PRIMEIRA("glObjectPtrLabel");
    static void (*p)(const void *, GLsizei, const GLchar *); if (!p) p = gl_proc("glObjectPtrLabel");
    Args a = args_de(c); (void)a;
    const void * a0 = (const void *)G2H(arg32(&a));
    GLsizei a1 = (GLsizei)arg32(&a);
    const GLchar * a2 = (const GLchar *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glObjectPtrLabelKHR(CPU *c) { RT_PRIMEIRA("glObjectPtrLabelKHR");
    static void (*p)(const void *, GLsizei, const GLchar *); if (!p) p = gl_proc("glObjectPtrLabelKHR");
    Args a = args_de(c); (void)a;
    const void * a0 = (const void *)G2H(arg32(&a));
    GLsizei a1 = (GLsizei)arg32(&a);
    const GLchar * a2 = (const GLchar *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glPatchParameteri(CPU *c) { RT_PRIMEIRA("glPatchParameteri");
    static void (*p)(GLenum, GLint); if (!p) p = gl_proc("glPatchParameteri");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    p(a0, a1);
}
void G_glPatchParameteriEXT(CPU *c) { RT_PRIMEIRA("glPatchParameteriEXT");
    static void (*p)(GLenum, GLint); if (!p) p = gl_proc("glPatchParameteriEXT");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    p(a0, a1);
}
void G_glPatchParameteriOES(CPU *c) { RT_PRIMEIRA("glPatchParameteriOES");
    static void (*p)(GLenum, GLint); if (!p) p = gl_proc("glPatchParameteriOES");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    p(a0, a1);
}
void G_glPathCommandsNV(CPU *c) { RT_PRIMEIRA("glPathCommandsNV");
    static void (*p)(GLuint, GLsizei, const GLubyte *, GLsizei, GLenum, const void *); if (!p) p = gl_proc("glPathCommandsNV");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    const GLubyte * a2 = (const GLubyte *)G2H(arg32(&a));
    GLsizei a3 = (GLsizei)arg32(&a);
    GLenum a4 = (GLenum)arg32(&a);
    const void * a5 = (const void *)G2H(arg32(&a));
    p(a0, a1, a2, a3, a4, a5);
}
void G_glPathCoordsNV(CPU *c) { RT_PRIMEIRA("glPathCoordsNV");
    static void (*p)(GLuint, GLsizei, GLenum, const void *); if (!p) p = gl_proc("glPathCoordsNV");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    GLenum a2 = (GLenum)arg32(&a);
    const void * a3 = (const void *)G2H(arg32(&a));
    p(a0, a1, a2, a3);
}
void G_glPathCoverDepthFuncNV(CPU *c) { RT_PRIMEIRA("glPathCoverDepthFuncNV");
    static void (*p)(GLenum); if (!p) p = gl_proc("glPathCoverDepthFuncNV");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    p(a0);
}
void G_glPathDashArrayNV(CPU *c) { RT_PRIMEIRA("glPathDashArrayNV");
    static void (*p)(GLuint, GLsizei, const GLfloat *); if (!p) p = gl_proc("glPathDashArrayNV");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    const GLfloat * a2 = (const GLfloat *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glPathGlyphIndexArrayNV(CPU *c) { RT_PRIMEIRA("glPathGlyphIndexArrayNV");
    static GLenum (*p)(GLuint, GLenum, const void *, GLbitfield, GLuint, GLsizei, GLuint, GLfloat); if (!p) p = gl_proc("glPathGlyphIndexArrayNV");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    const void * a2 = (const void *)G2H(arg32(&a));
    GLbitfield a3 = (GLbitfield)arg32(&a);
    GLuint a4 = (GLuint)arg32(&a);
    GLsizei a5 = (GLsizei)arg32(&a);
    GLuint a6 = (GLuint)arg32(&a);
    GLfloat a7 = argf(&a);
    ret32(c, (uint32_t)p(a0, a1, a2, a3, a4, a5, a6, a7));
}
void G_glPathGlyphIndexRangeNV(CPU *c) { RT_PRIMEIRA("glPathGlyphIndexRangeNV");
    static GLenum (*p)(GLenum, const void *, GLbitfield, GLuint, GLfloat, GLuint *); if (!p) p = gl_proc("glPathGlyphIndexRangeNV");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    const void * a1 = (const void *)G2H(arg32(&a));
    GLbitfield a2 = (GLbitfield)arg32(&a);
    GLuint a3 = (GLuint)arg32(&a);
    GLfloat a4 = argf(&a);
    GLuint * a5 = (GLuint *)G2H(arg32(&a));
    ret32(c, (uint32_t)p(a0, a1, a2, a3, a4, a5));
}
void G_glPathGlyphRangeNV(CPU *c) { RT_PRIMEIRA("glPathGlyphRangeNV");
    static void (*p)(GLuint, GLenum, const void *, GLbitfield, GLuint, GLsizei, GLenum, GLuint, GLfloat); if (!p) p = gl_proc("glPathGlyphRangeNV");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    const void * a2 = (const void *)G2H(arg32(&a));
    GLbitfield a3 = (GLbitfield)arg32(&a);
    GLuint a4 = (GLuint)arg32(&a);
    GLsizei a5 = (GLsizei)arg32(&a);
    GLenum a6 = (GLenum)arg32(&a);
    GLuint a7 = (GLuint)arg32(&a);
    GLfloat a8 = argf(&a);
    p(a0, a1, a2, a3, a4, a5, a6, a7, a8);
}
void G_glPathGlyphsNV(CPU *c) { RT_PRIMEIRA("glPathGlyphsNV");
    static void (*p)(GLuint, GLenum, const void *, GLbitfield, GLsizei, GLenum, const void *, GLenum, GLuint, GLfloat); if (!p) p = gl_proc("glPathGlyphsNV");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    const void * a2 = (const void *)G2H(arg32(&a));
    GLbitfield a3 = (GLbitfield)arg32(&a);
    GLsizei a4 = (GLsizei)arg32(&a);
    GLenum a5 = (GLenum)arg32(&a);
    const void * a6 = (const void *)G2H(arg32(&a));
    GLenum a7 = (GLenum)arg32(&a);
    GLuint a8 = (GLuint)arg32(&a);
    GLfloat a9 = argf(&a);
    p(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9);
}
void G_glPathMemoryGlyphIndexArrayNV(CPU *c) { RT_PRIMEIRA("glPathMemoryGlyphIndexArrayNV");
    static GLenum (*p)(GLuint, GLenum, GLsizeiptr, const void *, GLsizei, GLuint, GLsizei, GLuint, GLfloat); if (!p) p = gl_proc("glPathMemoryGlyphIndexArrayNV");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLsizeiptr a2 = (GLsizeiptr)(int32_t)arg32(&a);
    const void * a3 = (const void *)G2H(arg32(&a));
    GLsizei a4 = (GLsizei)arg32(&a);
    GLuint a5 = (GLuint)arg32(&a);
    GLsizei a6 = (GLsizei)arg32(&a);
    GLuint a7 = (GLuint)arg32(&a);
    GLfloat a8 = argf(&a);
    ret32(c, (uint32_t)p(a0, a1, a2, a3, a4, a5, a6, a7, a8));
}
void G_glPathParameterfNV(CPU *c) { RT_PRIMEIRA("glPathParameterfNV");
    static void (*p)(GLuint, GLenum, GLfloat); if (!p) p = gl_proc("glPathParameterfNV");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLfloat a2 = argf(&a);
    p(a0, a1, a2);
}
void G_glPathParameterfvNV(CPU *c) { RT_PRIMEIRA("glPathParameterfvNV");
    static void (*p)(GLuint, GLenum, const GLfloat *); if (!p) p = gl_proc("glPathParameterfvNV");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    const GLfloat * a2 = (const GLfloat *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glPathParameteriNV(CPU *c) { RT_PRIMEIRA("glPathParameteriNV");
    static void (*p)(GLuint, GLenum, GLint); if (!p) p = gl_proc("glPathParameteriNV");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLint a2 = (GLint)arg32(&a);
    p(a0, a1, a2);
}
void G_glPathParameterivNV(CPU *c) { RT_PRIMEIRA("glPathParameterivNV");
    static void (*p)(GLuint, GLenum, const GLint *); if (!p) p = gl_proc("glPathParameterivNV");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    const GLint * a2 = (const GLint *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glPathStencilDepthOffsetNV(CPU *c) { RT_PRIMEIRA("glPathStencilDepthOffsetNV");
    static void (*p)(GLfloat, GLfloat); if (!p) p = gl_proc("glPathStencilDepthOffsetNV");
    Args a = args_de(c); (void)a;
    GLfloat a0 = argf(&a);
    GLfloat a1 = argf(&a);
    p(a0, a1);
}
void G_glPathStencilFuncNV(CPU *c) { RT_PRIMEIRA("glPathStencilFuncNV");
    static void (*p)(GLenum, GLint, GLuint); if (!p) p = gl_proc("glPathStencilFuncNV");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLuint a2 = (GLuint)arg32(&a);
    p(a0, a1, a2);
}
void G_glPathStringNV(CPU *c) { RT_PRIMEIRA("glPathStringNV");
    static void (*p)(GLuint, GLenum, GLsizei, const void *); if (!p) p = gl_proc("glPathStringNV");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    const void * a3 = (const void *)G2H(arg32(&a));
    p(a0, a1, a2, a3);
}
void G_glPathSubCommandsNV(CPU *c) { RT_PRIMEIRA("glPathSubCommandsNV");
    static void (*p)(GLuint, GLsizei, GLsizei, GLsizei, const GLubyte *, GLsizei, GLenum, const void *); if (!p) p = gl_proc("glPathSubCommandsNV");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    GLsizei a3 = (GLsizei)arg32(&a);
    const GLubyte * a4 = (const GLubyte *)G2H(arg32(&a));
    GLsizei a5 = (GLsizei)arg32(&a);
    GLenum a6 = (GLenum)arg32(&a);
    const void * a7 = (const void *)G2H(arg32(&a));
    p(a0, a1, a2, a3, a4, a5, a6, a7);
}
void G_glPathSubCoordsNV(CPU *c) { RT_PRIMEIRA("glPathSubCoordsNV");
    static void (*p)(GLuint, GLsizei, GLsizei, GLenum, const void *); if (!p) p = gl_proc("glPathSubCoordsNV");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    GLenum a3 = (GLenum)arg32(&a);
    const void * a4 = (const void *)G2H(arg32(&a));
    p(a0, a1, a2, a3, a4);
}
void G_glPauseTransformFeedback(CPU *c) { RT_PRIMEIRA("glPauseTransformFeedback");
    static void (*p)(void); if (!p) p = gl_proc("glPauseTransformFeedback");
    Args a = args_de(c); (void)a;
    p();
}
void G_glPixelStorei(CPU *c) { RT_PRIMEIRA("glPixelStorei");
    static void (*p)(GLenum, GLint); if (!p) p = gl_proc("glPixelStorei");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    p(a0, a1);
}
void G_glPointAlongPathNV(CPU *c) { RT_PRIMEIRA("glPointAlongPathNV");
    static GLboolean (*p)(GLuint, GLsizei, GLsizei, GLfloat, GLfloat *, GLfloat *, GLfloat *, GLfloat *); if (!p) p = gl_proc("glPointAlongPathNV");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    GLfloat a3 = argf(&a);
    GLfloat * a4 = (GLfloat *)G2H(arg32(&a));
    GLfloat * a5 = (GLfloat *)G2H(arg32(&a));
    GLfloat * a6 = (GLfloat *)G2H(arg32(&a));
    GLfloat * a7 = (GLfloat *)G2H(arg32(&a));
    ret32(c, (uint32_t)p(a0, a1, a2, a3, a4, a5, a6, a7));
}
void G_glPolygonModeNV(CPU *c) { RT_PRIMEIRA("glPolygonModeNV");
    static void (*p)(GLenum, GLenum); if (!p) p = gl_proc("glPolygonModeNV");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    p(a0, a1);
}
void G_glPolygonOffset(CPU *c) { RT_PRIMEIRA("glPolygonOffset");
    static void (*p)(GLfloat, GLfloat); if (!p) p = gl_proc("glPolygonOffset");
    Args a = args_de(c); (void)a;
    GLfloat a0 = argf(&a);
    GLfloat a1 = argf(&a);
    p(a0, a1);
}
void G_glPolygonOffsetClampEXT(CPU *c) { RT_PRIMEIRA("glPolygonOffsetClampEXT");
    static void (*p)(GLfloat, GLfloat, GLfloat); if (!p) p = gl_proc("glPolygonOffsetClampEXT");
    Args a = args_de(c); (void)a;
    GLfloat a0 = argf(&a);
    GLfloat a1 = argf(&a);
    GLfloat a2 = argf(&a);
    p(a0, a1, a2);
}
void G_glPopDebugGroup(CPU *c) { RT_PRIMEIRA("glPopDebugGroup");
    static void (*p)(void); if (!p) p = gl_proc("glPopDebugGroup");
    Args a = args_de(c); (void)a;
    p();
}
void G_glPopDebugGroupKHR(CPU *c) { RT_PRIMEIRA("glPopDebugGroupKHR");
    static void (*p)(void); if (!p) p = gl_proc("glPopDebugGroupKHR");
    Args a = args_de(c); (void)a;
    p();
}
void G_glPopGroupMarkerEXT(CPU *c) { RT_PRIMEIRA("glPopGroupMarkerEXT");
    static void (*p)(void); if (!p) p = gl_proc("glPopGroupMarkerEXT");
    Args a = args_de(c); (void)a;
    p();
}
void G_glPrimitiveBoundingBox(CPU *c) { RT_PRIMEIRA("glPrimitiveBoundingBox");
    static void (*p)(GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat); if (!p) p = gl_proc("glPrimitiveBoundingBox");
    Args a = args_de(c); (void)a;
    GLfloat a0 = argf(&a);
    GLfloat a1 = argf(&a);
    GLfloat a2 = argf(&a);
    GLfloat a3 = argf(&a);
    GLfloat a4 = argf(&a);
    GLfloat a5 = argf(&a);
    GLfloat a6 = argf(&a);
    GLfloat a7 = argf(&a);
    p(a0, a1, a2, a3, a4, a5, a6, a7);
}
void G_glPrimitiveBoundingBoxEXT(CPU *c) { RT_PRIMEIRA("glPrimitiveBoundingBoxEXT");
    static void (*p)(GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat); if (!p) p = gl_proc("glPrimitiveBoundingBoxEXT");
    Args a = args_de(c); (void)a;
    GLfloat a0 = argf(&a);
    GLfloat a1 = argf(&a);
    GLfloat a2 = argf(&a);
    GLfloat a3 = argf(&a);
    GLfloat a4 = argf(&a);
    GLfloat a5 = argf(&a);
    GLfloat a6 = argf(&a);
    GLfloat a7 = argf(&a);
    p(a0, a1, a2, a3, a4, a5, a6, a7);
}
void G_glPrimitiveBoundingBoxOES(CPU *c) { RT_PRIMEIRA("glPrimitiveBoundingBoxOES");
    static void (*p)(GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat); if (!p) p = gl_proc("glPrimitiveBoundingBoxOES");
    Args a = args_de(c); (void)a;
    GLfloat a0 = argf(&a);
    GLfloat a1 = argf(&a);
    GLfloat a2 = argf(&a);
    GLfloat a3 = argf(&a);
    GLfloat a4 = argf(&a);
    GLfloat a5 = argf(&a);
    GLfloat a6 = argf(&a);
    GLfloat a7 = argf(&a);
    p(a0, a1, a2, a3, a4, a5, a6, a7);
}
void G_glProgramBinary(CPU *c) { RT_PRIMEIRA("glProgramBinary");
    static void (*p)(GLuint, GLenum, const void *, GLsizei); if (!p) p = gl_proc("glProgramBinary");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    const void * a2 = (const void *)G2H(arg32(&a));
    GLsizei a3 = (GLsizei)arg32(&a);
    p(a0, a1, a2, a3);
}
void G_glProgramBinaryOES(CPU *c) { RT_PRIMEIRA("glProgramBinaryOES");
    static void (*p)(GLuint, GLenum, const void *, GLint); if (!p) p = gl_proc("glProgramBinaryOES");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    const void * a2 = (const void *)G2H(arg32(&a));
    GLint a3 = (GLint)arg32(&a);
    p(a0, a1, a2, a3);
}
void G_glProgramParameteri(CPU *c) { RT_PRIMEIRA("glProgramParameteri");
    static void (*p)(GLuint, GLenum, GLint); if (!p) p = gl_proc("glProgramParameteri");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLint a2 = (GLint)arg32(&a);
    p(a0, a1, a2);
}
void G_glProgramParameteriEXT(CPU *c) { RT_PRIMEIRA("glProgramParameteriEXT");
    static void (*p)(GLuint, GLenum, GLint); if (!p) p = gl_proc("glProgramParameteriEXT");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLint a2 = (GLint)arg32(&a);
    p(a0, a1, a2);
}
void G_glProgramPathFragmentInputGenNV(CPU *c) { RT_PRIMEIRA("glProgramPathFragmentInputGenNV");
    static void (*p)(GLuint, GLint, GLenum, GLint, const GLfloat *); if (!p) p = gl_proc("glProgramPathFragmentInputGenNV");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLenum a2 = (GLenum)arg32(&a);
    GLint a3 = (GLint)arg32(&a);
    const GLfloat * a4 = (const GLfloat *)G2H(arg32(&a));
    p(a0, a1, a2, a3, a4);
}
void G_glProgramUniform1f(CPU *c) { RT_PRIMEIRA("glProgramUniform1f");
    static void (*p)(GLuint, GLint, GLfloat); if (!p) p = gl_proc("glProgramUniform1f");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLfloat a2 = argf(&a);
    p(a0, a1, a2);
}
void G_glProgramUniform1fEXT(CPU *c) { RT_PRIMEIRA("glProgramUniform1fEXT");
    static void (*p)(GLuint, GLint, GLfloat); if (!p) p = gl_proc("glProgramUniform1fEXT");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLfloat a2 = argf(&a);
    p(a0, a1, a2);
}
void G_glProgramUniform1fv(CPU *c) { RT_PRIMEIRA("glProgramUniform1fv");
    static void (*p)(GLuint, GLint, GLsizei, const GLfloat *); if (!p) p = gl_proc("glProgramUniform1fv");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    const GLfloat * a3 = (const GLfloat *)G2H(arg32(&a));
    p(a0, a1, a2, a3);
}
void G_glProgramUniform1fvEXT(CPU *c) { RT_PRIMEIRA("glProgramUniform1fvEXT");
    static void (*p)(GLuint, GLint, GLsizei, const GLfloat *); if (!p) p = gl_proc("glProgramUniform1fvEXT");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    const GLfloat * a3 = (const GLfloat *)G2H(arg32(&a));
    p(a0, a1, a2, a3);
}
void G_glProgramUniform1i(CPU *c) { RT_PRIMEIRA("glProgramUniform1i");
    static void (*p)(GLuint, GLint, GLint); if (!p) p = gl_proc("glProgramUniform1i");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLint a2 = (GLint)arg32(&a);
    p(a0, a1, a2);
}
void G_glProgramUniform1i64NV(CPU *c) { RT_PRIMEIRA("glProgramUniform1i64NV");
    static void (*p)(GLuint, GLint, GLint64EXT); if (!p) p = gl_proc("glProgramUniform1i64NV");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLint64EXT a2 = (GLint64EXT)arg64(&a);
    p(a0, a1, a2);
}
void G_glProgramUniform1i64vNV(CPU *c) { RT_PRIMEIRA("glProgramUniform1i64vNV");
    static void (*p)(GLuint, GLint, GLsizei, const GLint64EXT *); if (!p) p = gl_proc("glProgramUniform1i64vNV");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    const GLint64EXT * a3 = (const GLint64EXT *)G2H(arg32(&a));
    p(a0, a1, a2, a3);
}
void G_glProgramUniform1iEXT(CPU *c) { RT_PRIMEIRA("glProgramUniform1iEXT");
    static void (*p)(GLuint, GLint, GLint); if (!p) p = gl_proc("glProgramUniform1iEXT");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLint a2 = (GLint)arg32(&a);
    p(a0, a1, a2);
}
void G_glProgramUniform1iv(CPU *c) { RT_PRIMEIRA("glProgramUniform1iv");
    static void (*p)(GLuint, GLint, GLsizei, const GLint *); if (!p) p = gl_proc("glProgramUniform1iv");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    const GLint * a3 = (const GLint *)G2H(arg32(&a));
    p(a0, a1, a2, a3);
}
void G_glProgramUniform1ivEXT(CPU *c) { RT_PRIMEIRA("glProgramUniform1ivEXT");
    static void (*p)(GLuint, GLint, GLsizei, const GLint *); if (!p) p = gl_proc("glProgramUniform1ivEXT");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    const GLint * a3 = (const GLint *)G2H(arg32(&a));
    p(a0, a1, a2, a3);
}
void G_glProgramUniform1ui(CPU *c) { RT_PRIMEIRA("glProgramUniform1ui");
    static void (*p)(GLuint, GLint, GLuint); if (!p) p = gl_proc("glProgramUniform1ui");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLuint a2 = (GLuint)arg32(&a);
    p(a0, a1, a2);
}
void G_glProgramUniform1ui64NV(CPU *c) { RT_PRIMEIRA("glProgramUniform1ui64NV");
    static void (*p)(GLuint, GLint, GLuint64EXT); if (!p) p = gl_proc("glProgramUniform1ui64NV");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLuint64EXT a2 = (GLuint64EXT)arg64(&a);
    p(a0, a1, a2);
}
void G_glProgramUniform1ui64vNV(CPU *c) { RT_PRIMEIRA("glProgramUniform1ui64vNV");
    static void (*p)(GLuint, GLint, GLsizei, const GLuint64EXT *); if (!p) p = gl_proc("glProgramUniform1ui64vNV");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    const GLuint64EXT * a3 = (const GLuint64EXT *)G2H(arg32(&a));
    p(a0, a1, a2, a3);
}
void G_glProgramUniform1uiEXT(CPU *c) { RT_PRIMEIRA("glProgramUniform1uiEXT");
    static void (*p)(GLuint, GLint, GLuint); if (!p) p = gl_proc("glProgramUniform1uiEXT");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLuint a2 = (GLuint)arg32(&a);
    p(a0, a1, a2);
}
void G_glProgramUniform1uiv(CPU *c) { RT_PRIMEIRA("glProgramUniform1uiv");
    static void (*p)(GLuint, GLint, GLsizei, const GLuint *); if (!p) p = gl_proc("glProgramUniform1uiv");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    const GLuint * a3 = (const GLuint *)G2H(arg32(&a));
    p(a0, a1, a2, a3);
}
void G_glProgramUniform1uivEXT(CPU *c) { RT_PRIMEIRA("glProgramUniform1uivEXT");
    static void (*p)(GLuint, GLint, GLsizei, const GLuint *); if (!p) p = gl_proc("glProgramUniform1uivEXT");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    const GLuint * a3 = (const GLuint *)G2H(arg32(&a));
    p(a0, a1, a2, a3);
}
void G_glProgramUniform2f(CPU *c) { RT_PRIMEIRA("glProgramUniform2f");
    static void (*p)(GLuint, GLint, GLfloat, GLfloat); if (!p) p = gl_proc("glProgramUniform2f");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLfloat a2 = argf(&a);
    GLfloat a3 = argf(&a);
    p(a0, a1, a2, a3);
}
void G_glProgramUniform2fEXT(CPU *c) { RT_PRIMEIRA("glProgramUniform2fEXT");
    static void (*p)(GLuint, GLint, GLfloat, GLfloat); if (!p) p = gl_proc("glProgramUniform2fEXT");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLfloat a2 = argf(&a);
    GLfloat a3 = argf(&a);
    p(a0, a1, a2, a3);
}
void G_glProgramUniform2fv(CPU *c) { RT_PRIMEIRA("glProgramUniform2fv");
    static void (*p)(GLuint, GLint, GLsizei, const GLfloat *); if (!p) p = gl_proc("glProgramUniform2fv");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    const GLfloat * a3 = (const GLfloat *)G2H(arg32(&a));
    p(a0, a1, a2, a3);
}
void G_glProgramUniform2fvEXT(CPU *c) { RT_PRIMEIRA("glProgramUniform2fvEXT");
    static void (*p)(GLuint, GLint, GLsizei, const GLfloat *); if (!p) p = gl_proc("glProgramUniform2fvEXT");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    const GLfloat * a3 = (const GLfloat *)G2H(arg32(&a));
    p(a0, a1, a2, a3);
}
void G_glProgramUniform2i(CPU *c) { RT_PRIMEIRA("glProgramUniform2i");
    static void (*p)(GLuint, GLint, GLint, GLint); if (!p) p = gl_proc("glProgramUniform2i");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLint a2 = (GLint)arg32(&a);
    GLint a3 = (GLint)arg32(&a);
    p(a0, a1, a2, a3);
}
void G_glProgramUniform2i64NV(CPU *c) { RT_PRIMEIRA("glProgramUniform2i64NV");
    static void (*p)(GLuint, GLint, GLint64EXT, GLint64EXT); if (!p) p = gl_proc("glProgramUniform2i64NV");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLint64EXT a2 = (GLint64EXT)arg64(&a);
    GLint64EXT a3 = (GLint64EXT)arg64(&a);
    p(a0, a1, a2, a3);
}
void G_glProgramUniform2i64vNV(CPU *c) { RT_PRIMEIRA("glProgramUniform2i64vNV");
    static void (*p)(GLuint, GLint, GLsizei, const GLint64EXT *); if (!p) p = gl_proc("glProgramUniform2i64vNV");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    const GLint64EXT * a3 = (const GLint64EXT *)G2H(arg32(&a));
    p(a0, a1, a2, a3);
}
void G_glProgramUniform2iEXT(CPU *c) { RT_PRIMEIRA("glProgramUniform2iEXT");
    static void (*p)(GLuint, GLint, GLint, GLint); if (!p) p = gl_proc("glProgramUniform2iEXT");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLint a2 = (GLint)arg32(&a);
    GLint a3 = (GLint)arg32(&a);
    p(a0, a1, a2, a3);
}
void G_glProgramUniform2iv(CPU *c) { RT_PRIMEIRA("glProgramUniform2iv");
    static void (*p)(GLuint, GLint, GLsizei, const GLint *); if (!p) p = gl_proc("glProgramUniform2iv");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    const GLint * a3 = (const GLint *)G2H(arg32(&a));
    p(a0, a1, a2, a3);
}
void G_glProgramUniform2ivEXT(CPU *c) { RT_PRIMEIRA("glProgramUniform2ivEXT");
    static void (*p)(GLuint, GLint, GLsizei, const GLint *); if (!p) p = gl_proc("glProgramUniform2ivEXT");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    const GLint * a3 = (const GLint *)G2H(arg32(&a));
    p(a0, a1, a2, a3);
}
void G_glProgramUniform2ui(CPU *c) { RT_PRIMEIRA("glProgramUniform2ui");
    static void (*p)(GLuint, GLint, GLuint, GLuint); if (!p) p = gl_proc("glProgramUniform2ui");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLuint a2 = (GLuint)arg32(&a);
    GLuint a3 = (GLuint)arg32(&a);
    p(a0, a1, a2, a3);
}
void G_glProgramUniform2ui64NV(CPU *c) { RT_PRIMEIRA("glProgramUniform2ui64NV");
    static void (*p)(GLuint, GLint, GLuint64EXT, GLuint64EXT); if (!p) p = gl_proc("glProgramUniform2ui64NV");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLuint64EXT a2 = (GLuint64EXT)arg64(&a);
    GLuint64EXT a3 = (GLuint64EXT)arg64(&a);
    p(a0, a1, a2, a3);
}
void G_glProgramUniform2ui64vNV(CPU *c) { RT_PRIMEIRA("glProgramUniform2ui64vNV");
    static void (*p)(GLuint, GLint, GLsizei, const GLuint64EXT *); if (!p) p = gl_proc("glProgramUniform2ui64vNV");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    const GLuint64EXT * a3 = (const GLuint64EXT *)G2H(arg32(&a));
    p(a0, a1, a2, a3);
}
void G_glProgramUniform2uiEXT(CPU *c) { RT_PRIMEIRA("glProgramUniform2uiEXT");
    static void (*p)(GLuint, GLint, GLuint, GLuint); if (!p) p = gl_proc("glProgramUniform2uiEXT");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLuint a2 = (GLuint)arg32(&a);
    GLuint a3 = (GLuint)arg32(&a);
    p(a0, a1, a2, a3);
}
void G_glProgramUniform2uiv(CPU *c) { RT_PRIMEIRA("glProgramUniform2uiv");
    static void (*p)(GLuint, GLint, GLsizei, const GLuint *); if (!p) p = gl_proc("glProgramUniform2uiv");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    const GLuint * a3 = (const GLuint *)G2H(arg32(&a));
    p(a0, a1, a2, a3);
}
void G_glProgramUniform2uivEXT(CPU *c) { RT_PRIMEIRA("glProgramUniform2uivEXT");
    static void (*p)(GLuint, GLint, GLsizei, const GLuint *); if (!p) p = gl_proc("glProgramUniform2uivEXT");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    const GLuint * a3 = (const GLuint *)G2H(arg32(&a));
    p(a0, a1, a2, a3);
}
void G_glProgramUniform3f(CPU *c) { RT_PRIMEIRA("glProgramUniform3f");
    static void (*p)(GLuint, GLint, GLfloat, GLfloat, GLfloat); if (!p) p = gl_proc("glProgramUniform3f");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLfloat a2 = argf(&a);
    GLfloat a3 = argf(&a);
    GLfloat a4 = argf(&a);
    p(a0, a1, a2, a3, a4);
}
void G_glProgramUniform3fEXT(CPU *c) { RT_PRIMEIRA("glProgramUniform3fEXT");
    static void (*p)(GLuint, GLint, GLfloat, GLfloat, GLfloat); if (!p) p = gl_proc("glProgramUniform3fEXT");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLfloat a2 = argf(&a);
    GLfloat a3 = argf(&a);
    GLfloat a4 = argf(&a);
    p(a0, a1, a2, a3, a4);
}
void G_glProgramUniform3fv(CPU *c) { RT_PRIMEIRA("glProgramUniform3fv");
    static void (*p)(GLuint, GLint, GLsizei, const GLfloat *); if (!p) p = gl_proc("glProgramUniform3fv");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    const GLfloat * a3 = (const GLfloat *)G2H(arg32(&a));
    p(a0, a1, a2, a3);
}
void G_glProgramUniform3fvEXT(CPU *c) { RT_PRIMEIRA("glProgramUniform3fvEXT");
    static void (*p)(GLuint, GLint, GLsizei, const GLfloat *); if (!p) p = gl_proc("glProgramUniform3fvEXT");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    const GLfloat * a3 = (const GLfloat *)G2H(arg32(&a));
    p(a0, a1, a2, a3);
}
void G_glProgramUniform3i(CPU *c) { RT_PRIMEIRA("glProgramUniform3i");
    static void (*p)(GLuint, GLint, GLint, GLint, GLint); if (!p) p = gl_proc("glProgramUniform3i");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLint a2 = (GLint)arg32(&a);
    GLint a3 = (GLint)arg32(&a);
    GLint a4 = (GLint)arg32(&a);
    p(a0, a1, a2, a3, a4);
}
void G_glProgramUniform3i64NV(CPU *c) { RT_PRIMEIRA("glProgramUniform3i64NV");
    static void (*p)(GLuint, GLint, GLint64EXT, GLint64EXT, GLint64EXT); if (!p) p = gl_proc("glProgramUniform3i64NV");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLint64EXT a2 = (GLint64EXT)arg64(&a);
    GLint64EXT a3 = (GLint64EXT)arg64(&a);
    GLint64EXT a4 = (GLint64EXT)arg64(&a);
    p(a0, a1, a2, a3, a4);
}
void G_glProgramUniform3i64vNV(CPU *c) { RT_PRIMEIRA("glProgramUniform3i64vNV");
    static void (*p)(GLuint, GLint, GLsizei, const GLint64EXT *); if (!p) p = gl_proc("glProgramUniform3i64vNV");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    const GLint64EXT * a3 = (const GLint64EXT *)G2H(arg32(&a));
    p(a0, a1, a2, a3);
}
void G_glProgramUniform3iEXT(CPU *c) { RT_PRIMEIRA("glProgramUniform3iEXT");
    static void (*p)(GLuint, GLint, GLint, GLint, GLint); if (!p) p = gl_proc("glProgramUniform3iEXT");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLint a2 = (GLint)arg32(&a);
    GLint a3 = (GLint)arg32(&a);
    GLint a4 = (GLint)arg32(&a);
    p(a0, a1, a2, a3, a4);
}
void G_glProgramUniform3iv(CPU *c) { RT_PRIMEIRA("glProgramUniform3iv");
    static void (*p)(GLuint, GLint, GLsizei, const GLint *); if (!p) p = gl_proc("glProgramUniform3iv");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    const GLint * a3 = (const GLint *)G2H(arg32(&a));
    p(a0, a1, a2, a3);
}
void G_glProgramUniform3ivEXT(CPU *c) { RT_PRIMEIRA("glProgramUniform3ivEXT");
    static void (*p)(GLuint, GLint, GLsizei, const GLint *); if (!p) p = gl_proc("glProgramUniform3ivEXT");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    const GLint * a3 = (const GLint *)G2H(arg32(&a));
    p(a0, a1, a2, a3);
}
void G_glProgramUniform3ui(CPU *c) { RT_PRIMEIRA("glProgramUniform3ui");
    static void (*p)(GLuint, GLint, GLuint, GLuint, GLuint); if (!p) p = gl_proc("glProgramUniform3ui");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLuint a2 = (GLuint)arg32(&a);
    GLuint a3 = (GLuint)arg32(&a);
    GLuint a4 = (GLuint)arg32(&a);
    p(a0, a1, a2, a3, a4);
}
void G_glProgramUniform3ui64NV(CPU *c) { RT_PRIMEIRA("glProgramUniform3ui64NV");
    static void (*p)(GLuint, GLint, GLuint64EXT, GLuint64EXT, GLuint64EXT); if (!p) p = gl_proc("glProgramUniform3ui64NV");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLuint64EXT a2 = (GLuint64EXT)arg64(&a);
    GLuint64EXT a3 = (GLuint64EXT)arg64(&a);
    GLuint64EXT a4 = (GLuint64EXT)arg64(&a);
    p(a0, a1, a2, a3, a4);
}
void G_glProgramUniform3ui64vNV(CPU *c) { RT_PRIMEIRA("glProgramUniform3ui64vNV");
    static void (*p)(GLuint, GLint, GLsizei, const GLuint64EXT *); if (!p) p = gl_proc("glProgramUniform3ui64vNV");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    const GLuint64EXT * a3 = (const GLuint64EXT *)G2H(arg32(&a));
    p(a0, a1, a2, a3);
}
void G_glProgramUniform3uiEXT(CPU *c) { RT_PRIMEIRA("glProgramUniform3uiEXT");
    static void (*p)(GLuint, GLint, GLuint, GLuint, GLuint); if (!p) p = gl_proc("glProgramUniform3uiEXT");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLuint a2 = (GLuint)arg32(&a);
    GLuint a3 = (GLuint)arg32(&a);
    GLuint a4 = (GLuint)arg32(&a);
    p(a0, a1, a2, a3, a4);
}
void G_glProgramUniform3uiv(CPU *c) { RT_PRIMEIRA("glProgramUniform3uiv");
    static void (*p)(GLuint, GLint, GLsizei, const GLuint *); if (!p) p = gl_proc("glProgramUniform3uiv");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    const GLuint * a3 = (const GLuint *)G2H(arg32(&a));
    p(a0, a1, a2, a3);
}
void G_glProgramUniform3uivEXT(CPU *c) { RT_PRIMEIRA("glProgramUniform3uivEXT");
    static void (*p)(GLuint, GLint, GLsizei, const GLuint *); if (!p) p = gl_proc("glProgramUniform3uivEXT");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    const GLuint * a3 = (const GLuint *)G2H(arg32(&a));
    p(a0, a1, a2, a3);
}
void G_glProgramUniform4f(CPU *c) { RT_PRIMEIRA("glProgramUniform4f");
    static void (*p)(GLuint, GLint, GLfloat, GLfloat, GLfloat, GLfloat); if (!p) p = gl_proc("glProgramUniform4f");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLfloat a2 = argf(&a);
    GLfloat a3 = argf(&a);
    GLfloat a4 = argf(&a);
    GLfloat a5 = argf(&a);
    p(a0, a1, a2, a3, a4, a5);
}
void G_glProgramUniform4fEXT(CPU *c) { RT_PRIMEIRA("glProgramUniform4fEXT");
    static void (*p)(GLuint, GLint, GLfloat, GLfloat, GLfloat, GLfloat); if (!p) p = gl_proc("glProgramUniform4fEXT");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLfloat a2 = argf(&a);
    GLfloat a3 = argf(&a);
    GLfloat a4 = argf(&a);
    GLfloat a5 = argf(&a);
    p(a0, a1, a2, a3, a4, a5);
}
void G_glProgramUniform4fv(CPU *c) { RT_PRIMEIRA("glProgramUniform4fv");
    static void (*p)(GLuint, GLint, GLsizei, const GLfloat *); if (!p) p = gl_proc("glProgramUniform4fv");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    const GLfloat * a3 = (const GLfloat *)G2H(arg32(&a));
    p(a0, a1, a2, a3);
}
void G_glProgramUniform4fvEXT(CPU *c) { RT_PRIMEIRA("glProgramUniform4fvEXT");
    static void (*p)(GLuint, GLint, GLsizei, const GLfloat *); if (!p) p = gl_proc("glProgramUniform4fvEXT");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    const GLfloat * a3 = (const GLfloat *)G2H(arg32(&a));
    p(a0, a1, a2, a3);
}
void G_glProgramUniform4i(CPU *c) { RT_PRIMEIRA("glProgramUniform4i");
    static void (*p)(GLuint, GLint, GLint, GLint, GLint, GLint); if (!p) p = gl_proc("glProgramUniform4i");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLint a2 = (GLint)arg32(&a);
    GLint a3 = (GLint)arg32(&a);
    GLint a4 = (GLint)arg32(&a);
    GLint a5 = (GLint)arg32(&a);
    p(a0, a1, a2, a3, a4, a5);
}
void G_glProgramUniform4i64NV(CPU *c) { RT_PRIMEIRA("glProgramUniform4i64NV");
    static void (*p)(GLuint, GLint, GLint64EXT, GLint64EXT, GLint64EXT, GLint64EXT); if (!p) p = gl_proc("glProgramUniform4i64NV");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLint64EXT a2 = (GLint64EXT)arg64(&a);
    GLint64EXT a3 = (GLint64EXT)arg64(&a);
    GLint64EXT a4 = (GLint64EXT)arg64(&a);
    GLint64EXT a5 = (GLint64EXT)arg64(&a);
    p(a0, a1, a2, a3, a4, a5);
}
void G_glProgramUniform4i64vNV(CPU *c) { RT_PRIMEIRA("glProgramUniform4i64vNV");
    static void (*p)(GLuint, GLint, GLsizei, const GLint64EXT *); if (!p) p = gl_proc("glProgramUniform4i64vNV");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    const GLint64EXT * a3 = (const GLint64EXT *)G2H(arg32(&a));
    p(a0, a1, a2, a3);
}
void G_glProgramUniform4iEXT(CPU *c) { RT_PRIMEIRA("glProgramUniform4iEXT");
    static void (*p)(GLuint, GLint, GLint, GLint, GLint, GLint); if (!p) p = gl_proc("glProgramUniform4iEXT");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLint a2 = (GLint)arg32(&a);
    GLint a3 = (GLint)arg32(&a);
    GLint a4 = (GLint)arg32(&a);
    GLint a5 = (GLint)arg32(&a);
    p(a0, a1, a2, a3, a4, a5);
}
void G_glProgramUniform4iv(CPU *c) { RT_PRIMEIRA("glProgramUniform4iv");
    static void (*p)(GLuint, GLint, GLsizei, const GLint *); if (!p) p = gl_proc("glProgramUniform4iv");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    const GLint * a3 = (const GLint *)G2H(arg32(&a));
    p(a0, a1, a2, a3);
}
void G_glProgramUniform4ivEXT(CPU *c) { RT_PRIMEIRA("glProgramUniform4ivEXT");
    static void (*p)(GLuint, GLint, GLsizei, const GLint *); if (!p) p = gl_proc("glProgramUniform4ivEXT");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    const GLint * a3 = (const GLint *)G2H(arg32(&a));
    p(a0, a1, a2, a3);
}
void G_glProgramUniform4ui(CPU *c) { RT_PRIMEIRA("glProgramUniform4ui");
    static void (*p)(GLuint, GLint, GLuint, GLuint, GLuint, GLuint); if (!p) p = gl_proc("glProgramUniform4ui");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLuint a2 = (GLuint)arg32(&a);
    GLuint a3 = (GLuint)arg32(&a);
    GLuint a4 = (GLuint)arg32(&a);
    GLuint a5 = (GLuint)arg32(&a);
    p(a0, a1, a2, a3, a4, a5);
}
void G_glProgramUniform4ui64NV(CPU *c) { RT_PRIMEIRA("glProgramUniform4ui64NV");
    static void (*p)(GLuint, GLint, GLuint64EXT, GLuint64EXT, GLuint64EXT, GLuint64EXT); if (!p) p = gl_proc("glProgramUniform4ui64NV");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLuint64EXT a2 = (GLuint64EXT)arg64(&a);
    GLuint64EXT a3 = (GLuint64EXT)arg64(&a);
    GLuint64EXT a4 = (GLuint64EXT)arg64(&a);
    GLuint64EXT a5 = (GLuint64EXT)arg64(&a);
    p(a0, a1, a2, a3, a4, a5);
}
void G_glProgramUniform4ui64vNV(CPU *c) { RT_PRIMEIRA("glProgramUniform4ui64vNV");
    static void (*p)(GLuint, GLint, GLsizei, const GLuint64EXT *); if (!p) p = gl_proc("glProgramUniform4ui64vNV");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    const GLuint64EXT * a3 = (const GLuint64EXT *)G2H(arg32(&a));
    p(a0, a1, a2, a3);
}
void G_glProgramUniform4uiEXT(CPU *c) { RT_PRIMEIRA("glProgramUniform4uiEXT");
    static void (*p)(GLuint, GLint, GLuint, GLuint, GLuint, GLuint); if (!p) p = gl_proc("glProgramUniform4uiEXT");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLuint a2 = (GLuint)arg32(&a);
    GLuint a3 = (GLuint)arg32(&a);
    GLuint a4 = (GLuint)arg32(&a);
    GLuint a5 = (GLuint)arg32(&a);
    p(a0, a1, a2, a3, a4, a5);
}
void G_glProgramUniform4uiv(CPU *c) { RT_PRIMEIRA("glProgramUniform4uiv");
    static void (*p)(GLuint, GLint, GLsizei, const GLuint *); if (!p) p = gl_proc("glProgramUniform4uiv");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    const GLuint * a3 = (const GLuint *)G2H(arg32(&a));
    p(a0, a1, a2, a3);
}
void G_glProgramUniform4uivEXT(CPU *c) { RT_PRIMEIRA("glProgramUniform4uivEXT");
    static void (*p)(GLuint, GLint, GLsizei, const GLuint *); if (!p) p = gl_proc("glProgramUniform4uivEXT");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    const GLuint * a3 = (const GLuint *)G2H(arg32(&a));
    p(a0, a1, a2, a3);
}
void G_glProgramUniformHandleui64IMG(CPU *c) { RT_PRIMEIRA("glProgramUniformHandleui64IMG");
    static void (*p)(GLuint, GLint, GLuint64); if (!p) p = gl_proc("glProgramUniformHandleui64IMG");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLuint64 a2 = (GLuint64)arg64(&a);
    p(a0, a1, a2);
}
void G_glProgramUniformHandleui64NV(CPU *c) { RT_PRIMEIRA("glProgramUniformHandleui64NV");
    static void (*p)(GLuint, GLint, GLuint64); if (!p) p = gl_proc("glProgramUniformHandleui64NV");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLuint64 a2 = (GLuint64)arg64(&a);
    p(a0, a1, a2);
}
void G_glProgramUniformHandleui64vIMG(CPU *c) { RT_PRIMEIRA("glProgramUniformHandleui64vIMG");
    static void (*p)(GLuint, GLint, GLsizei, const GLuint64 *); if (!p) p = gl_proc("glProgramUniformHandleui64vIMG");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    const GLuint64 * a3 = (const GLuint64 *)G2H(arg32(&a));
    p(a0, a1, a2, a3);
}
void G_glProgramUniformHandleui64vNV(CPU *c) { RT_PRIMEIRA("glProgramUniformHandleui64vNV");
    static void (*p)(GLuint, GLint, GLsizei, const GLuint64 *); if (!p) p = gl_proc("glProgramUniformHandleui64vNV");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    const GLuint64 * a3 = (const GLuint64 *)G2H(arg32(&a));
    p(a0, a1, a2, a3);
}
void G_glProgramUniformMatrix2fv(CPU *c) { RT_PRIMEIRA("glProgramUniformMatrix2fv");
    static void (*p)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *); if (!p) p = gl_proc("glProgramUniformMatrix2fv");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    GLboolean a3 = (GLboolean)arg32(&a);
    const GLfloat * a4 = (const GLfloat *)G2H(arg32(&a));
    p(a0, a1, a2, a3, a4);
}
void G_glProgramUniformMatrix2fvEXT(CPU *c) { RT_PRIMEIRA("glProgramUniformMatrix2fvEXT");
    static void (*p)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *); if (!p) p = gl_proc("glProgramUniformMatrix2fvEXT");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    GLboolean a3 = (GLboolean)arg32(&a);
    const GLfloat * a4 = (const GLfloat *)G2H(arg32(&a));
    p(a0, a1, a2, a3, a4);
}
void G_glProgramUniformMatrix2x3fv(CPU *c) { RT_PRIMEIRA("glProgramUniformMatrix2x3fv");
    static void (*p)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *); if (!p) p = gl_proc("glProgramUniformMatrix2x3fv");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    GLboolean a3 = (GLboolean)arg32(&a);
    const GLfloat * a4 = (const GLfloat *)G2H(arg32(&a));
    p(a0, a1, a2, a3, a4);
}
void G_glProgramUniformMatrix2x3fvEXT(CPU *c) { RT_PRIMEIRA("glProgramUniformMatrix2x3fvEXT");
    static void (*p)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *); if (!p) p = gl_proc("glProgramUniformMatrix2x3fvEXT");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    GLboolean a3 = (GLboolean)arg32(&a);
    const GLfloat * a4 = (const GLfloat *)G2H(arg32(&a));
    p(a0, a1, a2, a3, a4);
}
void G_glProgramUniformMatrix2x4fv(CPU *c) { RT_PRIMEIRA("glProgramUniformMatrix2x4fv");
    static void (*p)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *); if (!p) p = gl_proc("glProgramUniformMatrix2x4fv");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    GLboolean a3 = (GLboolean)arg32(&a);
    const GLfloat * a4 = (const GLfloat *)G2H(arg32(&a));
    p(a0, a1, a2, a3, a4);
}
void G_glProgramUniformMatrix2x4fvEXT(CPU *c) { RT_PRIMEIRA("glProgramUniformMatrix2x4fvEXT");
    static void (*p)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *); if (!p) p = gl_proc("glProgramUniformMatrix2x4fvEXT");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    GLboolean a3 = (GLboolean)arg32(&a);
    const GLfloat * a4 = (const GLfloat *)G2H(arg32(&a));
    p(a0, a1, a2, a3, a4);
}
void G_glProgramUniformMatrix3fv(CPU *c) { RT_PRIMEIRA("glProgramUniformMatrix3fv");
    static void (*p)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *); if (!p) p = gl_proc("glProgramUniformMatrix3fv");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    GLboolean a3 = (GLboolean)arg32(&a);
    const GLfloat * a4 = (const GLfloat *)G2H(arg32(&a));
    p(a0, a1, a2, a3, a4);
}
void G_glProgramUniformMatrix3fvEXT(CPU *c) { RT_PRIMEIRA("glProgramUniformMatrix3fvEXT");
    static void (*p)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *); if (!p) p = gl_proc("glProgramUniformMatrix3fvEXT");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    GLboolean a3 = (GLboolean)arg32(&a);
    const GLfloat * a4 = (const GLfloat *)G2H(arg32(&a));
    p(a0, a1, a2, a3, a4);
}
void G_glProgramUniformMatrix3x2fv(CPU *c) { RT_PRIMEIRA("glProgramUniformMatrix3x2fv");
    static void (*p)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *); if (!p) p = gl_proc("glProgramUniformMatrix3x2fv");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    GLboolean a3 = (GLboolean)arg32(&a);
    const GLfloat * a4 = (const GLfloat *)G2H(arg32(&a));
    p(a0, a1, a2, a3, a4);
}
void G_glProgramUniformMatrix3x2fvEXT(CPU *c) { RT_PRIMEIRA("glProgramUniformMatrix3x2fvEXT");
    static void (*p)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *); if (!p) p = gl_proc("glProgramUniformMatrix3x2fvEXT");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    GLboolean a3 = (GLboolean)arg32(&a);
    const GLfloat * a4 = (const GLfloat *)G2H(arg32(&a));
    p(a0, a1, a2, a3, a4);
}
void G_glProgramUniformMatrix3x4fv(CPU *c) { RT_PRIMEIRA("glProgramUniformMatrix3x4fv");
    static void (*p)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *); if (!p) p = gl_proc("glProgramUniformMatrix3x4fv");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    GLboolean a3 = (GLboolean)arg32(&a);
    const GLfloat * a4 = (const GLfloat *)G2H(arg32(&a));
    p(a0, a1, a2, a3, a4);
}
void G_glProgramUniformMatrix3x4fvEXT(CPU *c) { RT_PRIMEIRA("glProgramUniformMatrix3x4fvEXT");
    static void (*p)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *); if (!p) p = gl_proc("glProgramUniformMatrix3x4fvEXT");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    GLboolean a3 = (GLboolean)arg32(&a);
    const GLfloat * a4 = (const GLfloat *)G2H(arg32(&a));
    p(a0, a1, a2, a3, a4);
}
void G_glProgramUniformMatrix4fv(CPU *c) { RT_PRIMEIRA("glProgramUniformMatrix4fv");
    static void (*p)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *); if (!p) p = gl_proc("glProgramUniformMatrix4fv");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    GLboolean a3 = (GLboolean)arg32(&a);
    const GLfloat * a4 = (const GLfloat *)G2H(arg32(&a));
    p(a0, a1, a2, a3, a4);
}
void G_glProgramUniformMatrix4fvEXT(CPU *c) { RT_PRIMEIRA("glProgramUniformMatrix4fvEXT");
    static void (*p)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *); if (!p) p = gl_proc("glProgramUniformMatrix4fvEXT");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    GLboolean a3 = (GLboolean)arg32(&a);
    const GLfloat * a4 = (const GLfloat *)G2H(arg32(&a));
    p(a0, a1, a2, a3, a4);
}
void G_glProgramUniformMatrix4x2fv(CPU *c) { RT_PRIMEIRA("glProgramUniformMatrix4x2fv");
    static void (*p)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *); if (!p) p = gl_proc("glProgramUniformMatrix4x2fv");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    GLboolean a3 = (GLboolean)arg32(&a);
    const GLfloat * a4 = (const GLfloat *)G2H(arg32(&a));
    p(a0, a1, a2, a3, a4);
}
void G_glProgramUniformMatrix4x2fvEXT(CPU *c) { RT_PRIMEIRA("glProgramUniformMatrix4x2fvEXT");
    static void (*p)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *); if (!p) p = gl_proc("glProgramUniformMatrix4x2fvEXT");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    GLboolean a3 = (GLboolean)arg32(&a);
    const GLfloat * a4 = (const GLfloat *)G2H(arg32(&a));
    p(a0, a1, a2, a3, a4);
}
void G_glProgramUniformMatrix4x3fv(CPU *c) { RT_PRIMEIRA("glProgramUniformMatrix4x3fv");
    static void (*p)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *); if (!p) p = gl_proc("glProgramUniformMatrix4x3fv");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    GLboolean a3 = (GLboolean)arg32(&a);
    const GLfloat * a4 = (const GLfloat *)G2H(arg32(&a));
    p(a0, a1, a2, a3, a4);
}
void G_glProgramUniformMatrix4x3fvEXT(CPU *c) { RT_PRIMEIRA("glProgramUniformMatrix4x3fvEXT");
    static void (*p)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *); if (!p) p = gl_proc("glProgramUniformMatrix4x3fvEXT");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    GLboolean a3 = (GLboolean)arg32(&a);
    const GLfloat * a4 = (const GLfloat *)G2H(arg32(&a));
    p(a0, a1, a2, a3, a4);
}
void G_glPushDebugGroup(CPU *c) { RT_PRIMEIRA("glPushDebugGroup");
    static void (*p)(GLenum, GLuint, GLsizei, const GLchar *); if (!p) p = gl_proc("glPushDebugGroup");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLuint a1 = (GLuint)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    const GLchar * a3 = (const GLchar *)G2H(arg32(&a));
    p(a0, a1, a2, a3);
}
void G_glPushDebugGroupKHR(CPU *c) { RT_PRIMEIRA("glPushDebugGroupKHR");
    static void (*p)(GLenum, GLuint, GLsizei, const GLchar *); if (!p) p = gl_proc("glPushDebugGroupKHR");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLuint a1 = (GLuint)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    const GLchar * a3 = (const GLchar *)G2H(arg32(&a));
    p(a0, a1, a2, a3);
}
void G_glPushGroupMarkerEXT(CPU *c) { RT_PRIMEIRA("glPushGroupMarkerEXT");
    static void (*p)(GLsizei, const GLchar *); if (!p) p = gl_proc("glPushGroupMarkerEXT");
    Args a = args_de(c); (void)a;
    GLsizei a0 = (GLsizei)arg32(&a);
    const GLchar * a1 = (const GLchar *)G2H(arg32(&a));
    p(a0, a1);
}
void G_glQueryCounterEXT(CPU *c) { RT_PRIMEIRA("glQueryCounterEXT");
    static void (*p)(GLuint, GLenum); if (!p) p = gl_proc("glQueryCounterEXT");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    p(a0, a1);
}
void G_glRasterSamplesEXT(CPU *c) { RT_PRIMEIRA("glRasterSamplesEXT");
    static void (*p)(GLuint, GLboolean); if (!p) p = gl_proc("glRasterSamplesEXT");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLboolean a1 = (GLboolean)arg32(&a);
    p(a0, a1);
}
void G_glReadBuffer(CPU *c) { RT_PRIMEIRA("glReadBuffer");
    static void (*p)(GLenum); if (!p) p = gl_proc("glReadBuffer");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    p(a0);
}
void G_glReadBufferIndexedEXT(CPU *c) { RT_PRIMEIRA("glReadBufferIndexedEXT");
    static void (*p)(GLenum, GLint); if (!p) p = gl_proc("glReadBufferIndexedEXT");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    p(a0, a1);
}
void G_glReadBufferNV(CPU *c) { RT_PRIMEIRA("glReadBufferNV");
    static void (*p)(GLenum); if (!p) p = gl_proc("glReadBufferNV");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    p(a0);
}
void G_glReadnPixels(CPU *c) { RT_PRIMEIRA("glReadnPixels");
    static void (*p)(GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, GLsizei, void *); if (!p) p = gl_proc("glReadnPixels");
    Args a = args_de(c); (void)a;
    GLint a0 = (GLint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    GLsizei a3 = (GLsizei)arg32(&a);
    GLenum a4 = (GLenum)arg32(&a);
    GLenum a5 = (GLenum)arg32(&a);
    GLsizei a6 = (GLsizei)arg32(&a);
    void * a7 = (void *)G2H(arg32(&a));
    p(a0, a1, a2, a3, a4, a5, a6, a7);
}
void G_glReadnPixelsEXT(CPU *c) { RT_PRIMEIRA("glReadnPixelsEXT");
    static void (*p)(GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, GLsizei, void *); if (!p) p = gl_proc("glReadnPixelsEXT");
    Args a = args_de(c); (void)a;
    GLint a0 = (GLint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    GLsizei a3 = (GLsizei)arg32(&a);
    GLenum a4 = (GLenum)arg32(&a);
    GLenum a5 = (GLenum)arg32(&a);
    GLsizei a6 = (GLsizei)arg32(&a);
    void * a7 = (void *)G2H(arg32(&a));
    p(a0, a1, a2, a3, a4, a5, a6, a7);
}
void G_glReadnPixelsKHR(CPU *c) { RT_PRIMEIRA("glReadnPixelsKHR");
    static void (*p)(GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, GLsizei, void *); if (!p) p = gl_proc("glReadnPixelsKHR");
    Args a = args_de(c); (void)a;
    GLint a0 = (GLint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    GLsizei a3 = (GLsizei)arg32(&a);
    GLenum a4 = (GLenum)arg32(&a);
    GLenum a5 = (GLenum)arg32(&a);
    GLsizei a6 = (GLsizei)arg32(&a);
    void * a7 = (void *)G2H(arg32(&a));
    p(a0, a1, a2, a3, a4, a5, a6, a7);
}
void G_glReleaseKeyedMutexWin32EXT(CPU *c) { RT_PRIMEIRA("glReleaseKeyedMutexWin32EXT");
    static GLboolean (*p)(GLuint, GLuint64); if (!p) p = gl_proc("glReleaseKeyedMutexWin32EXT");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLuint64 a1 = (GLuint64)arg64(&a);
    ret32(c, (uint32_t)p(a0, a1));
}
void G_glReleaseShaderCompiler(CPU *c) { RT_PRIMEIRA("glReleaseShaderCompiler");
    static void (*p)(void); if (!p) p = gl_proc("glReleaseShaderCompiler");
    Args a = args_de(c); (void)a;
    p();
}
void G_glRenderbufferStorage(CPU *c) { RT_PRIMEIRA("glRenderbufferStorage");
    static void (*p)(GLenum, GLenum, GLsizei, GLsizei); if (!p) p = gl_proc("glRenderbufferStorage");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    GLsizei a3 = (GLsizei)arg32(&a);
    { GLenum fmt_interno(GLenum, int); a1 = fmt_interno(a1, 1); }
    p(a0, a1, a2, a3);
}
void G_glRenderbufferStorageMultisample(CPU *c) { RT_PRIMEIRA("glRenderbufferStorageMultisample");
    static void (*p)(GLenum, GLsizei, GLenum, GLsizei, GLsizei); if (!p) p = gl_proc("glRenderbufferStorageMultisample");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    GLenum a2 = (GLenum)arg32(&a);
    GLsizei a3 = (GLsizei)arg32(&a);
    GLsizei a4 = (GLsizei)arg32(&a);
    { GLenum fmt_interno(GLenum, int); a2 = fmt_interno(a2, 1); }
    p(a0, a1, a2, a3, a4);
}
void G_glRenderbufferStorageMultisampleANGLE(CPU *c) { RT_PRIMEIRA("glRenderbufferStorageMultisampleANGLE");
    static void (*p)(GLenum, GLsizei, GLenum, GLsizei, GLsizei); if (!p) p = gl_proc("glRenderbufferStorageMultisampleANGLE");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    GLenum a2 = (GLenum)arg32(&a);
    GLsizei a3 = (GLsizei)arg32(&a);
    GLsizei a4 = (GLsizei)arg32(&a);
    p(a0, a1, a2, a3, a4);
}
void G_glRenderbufferStorageMultisampleAPPLE(CPU *c) { RT_PRIMEIRA("glRenderbufferStorageMultisampleAPPLE");
    static void (*p)(GLenum, GLsizei, GLenum, GLsizei, GLsizei); if (!p) p = gl_proc("glRenderbufferStorageMultisampleAPPLE");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    GLenum a2 = (GLenum)arg32(&a);
    GLsizei a3 = (GLsizei)arg32(&a);
    GLsizei a4 = (GLsizei)arg32(&a);
    p(a0, a1, a2, a3, a4);
}
void G_glRenderbufferStorageMultisampleEXT(CPU *c) { RT_PRIMEIRA("glRenderbufferStorageMultisampleEXT");
    static void (*p)(GLenum, GLsizei, GLenum, GLsizei, GLsizei); if (!p) p = gl_proc("glRenderbufferStorageMultisampleEXT");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    GLenum a2 = (GLenum)arg32(&a);
    GLsizei a3 = (GLsizei)arg32(&a);
    GLsizei a4 = (GLsizei)arg32(&a);
    p(a0, a1, a2, a3, a4);
}
void G_glRenderbufferStorageMultisampleIMG(CPU *c) { RT_PRIMEIRA("glRenderbufferStorageMultisampleIMG");
    static void (*p)(GLenum, GLsizei, GLenum, GLsizei, GLsizei); if (!p) p = gl_proc("glRenderbufferStorageMultisampleIMG");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    GLenum a2 = (GLenum)arg32(&a);
    GLsizei a3 = (GLsizei)arg32(&a);
    GLsizei a4 = (GLsizei)arg32(&a);
    p(a0, a1, a2, a3, a4);
}
void G_glRenderbufferStorageMultisampleNV(CPU *c) { RT_PRIMEIRA("glRenderbufferStorageMultisampleNV");
    static void (*p)(GLenum, GLsizei, GLenum, GLsizei, GLsizei); if (!p) p = gl_proc("glRenderbufferStorageMultisampleNV");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    GLenum a2 = (GLenum)arg32(&a);
    GLsizei a3 = (GLsizei)arg32(&a);
    GLsizei a4 = (GLsizei)arg32(&a);
    p(a0, a1, a2, a3, a4);
}
void G_glResolveDepthValuesNV(CPU *c) { RT_PRIMEIRA("glResolveDepthValuesNV");
    static void (*p)(void); if (!p) p = gl_proc("glResolveDepthValuesNV");
    Args a = args_de(c); (void)a;
    p();
}
void G_glResolveMultisampleFramebufferAPPLE(CPU *c) { RT_PRIMEIRA("glResolveMultisampleFramebufferAPPLE");
    static void (*p)(void); if (!p) p = gl_proc("glResolveMultisampleFramebufferAPPLE");
    Args a = args_de(c); (void)a;
    p();
}
void G_glResumeTransformFeedback(CPU *c) { RT_PRIMEIRA("glResumeTransformFeedback");
    static void (*p)(void); if (!p) p = gl_proc("glResumeTransformFeedback");
    Args a = args_de(c); (void)a;
    p();
}
void G_glSampleCoverage(CPU *c) { RT_PRIMEIRA("glSampleCoverage");
    static void (*p)(GLfloat, GLboolean); if (!p) p = gl_proc("glSampleCoverage");
    Args a = args_de(c); (void)a;
    GLfloat a0 = argf(&a);
    GLboolean a1 = (GLboolean)arg32(&a);
    p(a0, a1);
}
void G_glSampleMaski(CPU *c) { RT_PRIMEIRA("glSampleMaski");
    static void (*p)(GLuint, GLbitfield); if (!p) p = gl_proc("glSampleMaski");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLbitfield a1 = (GLbitfield)arg32(&a);
    p(a0, a1);
}
void G_glSamplerParameterIiv(CPU *c) { RT_PRIMEIRA("glSamplerParameterIiv");
    static void (*p)(GLuint, GLenum, const GLint *); if (!p) p = gl_proc("glSamplerParameterIiv");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    const GLint * a2 = (const GLint *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glSamplerParameterIivEXT(CPU *c) { RT_PRIMEIRA("glSamplerParameterIivEXT");
    static void (*p)(GLuint, GLenum, const GLint *); if (!p) p = gl_proc("glSamplerParameterIivEXT");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    const GLint * a2 = (const GLint *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glSamplerParameterIivOES(CPU *c) { RT_PRIMEIRA("glSamplerParameterIivOES");
    static void (*p)(GLuint, GLenum, const GLint *); if (!p) p = gl_proc("glSamplerParameterIivOES");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    const GLint * a2 = (const GLint *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glSamplerParameterIuiv(CPU *c) { RT_PRIMEIRA("glSamplerParameterIuiv");
    static void (*p)(GLuint, GLenum, const GLuint *); if (!p) p = gl_proc("glSamplerParameterIuiv");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    const GLuint * a2 = (const GLuint *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glSamplerParameterIuivEXT(CPU *c) { RT_PRIMEIRA("glSamplerParameterIuivEXT");
    static void (*p)(GLuint, GLenum, const GLuint *); if (!p) p = gl_proc("glSamplerParameterIuivEXT");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    const GLuint * a2 = (const GLuint *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glSamplerParameterIuivOES(CPU *c) { RT_PRIMEIRA("glSamplerParameterIuivOES");
    static void (*p)(GLuint, GLenum, const GLuint *); if (!p) p = gl_proc("glSamplerParameterIuivOES");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    const GLuint * a2 = (const GLuint *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glSamplerParameterf(CPU *c) { RT_PRIMEIRA("glSamplerParameterf");
    static void (*p)(GLuint, GLenum, GLfloat); if (!p) p = gl_proc("glSamplerParameterf");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLfloat a2 = argf(&a);
    p(a0, a1, a2);
}
void G_glSamplerParameterfv(CPU *c) { RT_PRIMEIRA("glSamplerParameterfv");
    static void (*p)(GLuint, GLenum, const GLfloat *); if (!p) p = gl_proc("glSamplerParameterfv");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    const GLfloat * a2 = (const GLfloat *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glSamplerParameteri(CPU *c) { RT_PRIMEIRA("glSamplerParameteri");
    static void (*p)(GLuint, GLenum, GLint); if (!p) p = gl_proc("glSamplerParameteri");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLint a2 = (GLint)arg32(&a);
    p(a0, a1, a2);
}
void G_glSamplerParameteriv(CPU *c) { RT_PRIMEIRA("glSamplerParameteriv");
    static void (*p)(GLuint, GLenum, const GLint *); if (!p) p = gl_proc("glSamplerParameteriv");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    const GLint * a2 = (const GLint *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glScissor(CPU *c) { RT_PRIMEIRA("glScissor");
    static void (*p)(GLint, GLint, GLsizei, GLsizei); if (!p) p = gl_proc("glScissor");
    Args a = args_de(c); (void)a;
    GLint a0 = (GLint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    GLsizei a3 = (GLsizei)arg32(&a);
#ifdef MGS2_DEPURA
    { static int _n; if (_n++ < 15) { GLint _fb = 0; glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &_fb); rt_log("glScissor(%d,%d %dx%d) fbo %d", a0, a1, a2, a3, _fb); } }
#endif
    p(a0, a1, a2, a3);
}
void G_glScissorArrayvNV(CPU *c) { RT_PRIMEIRA("glScissorArrayvNV");
    static void (*p)(GLuint, GLsizei, const GLint *); if (!p) p = gl_proc("glScissorArrayvNV");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    const GLint * a2 = (const GLint *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glScissorArrayvOES(CPU *c) { RT_PRIMEIRA("glScissorArrayvOES");
    static void (*p)(GLuint, GLsizei, const GLint *); if (!p) p = gl_proc("glScissorArrayvOES");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    const GLint * a2 = (const GLint *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glScissorIndexedNV(CPU *c) { RT_PRIMEIRA("glScissorIndexedNV");
    static void (*p)(GLuint, GLint, GLint, GLsizei, GLsizei); if (!p) p = gl_proc("glScissorIndexedNV");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLint a2 = (GLint)arg32(&a);
    GLsizei a3 = (GLsizei)arg32(&a);
    GLsizei a4 = (GLsizei)arg32(&a);
    p(a0, a1, a2, a3, a4);
}
void G_glScissorIndexedOES(CPU *c) { RT_PRIMEIRA("glScissorIndexedOES");
    static void (*p)(GLuint, GLint, GLint, GLsizei, GLsizei); if (!p) p = gl_proc("glScissorIndexedOES");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLint a2 = (GLint)arg32(&a);
    GLsizei a3 = (GLsizei)arg32(&a);
    GLsizei a4 = (GLsizei)arg32(&a);
    p(a0, a1, a2, a3, a4);
}
void G_glScissorIndexedvNV(CPU *c) { RT_PRIMEIRA("glScissorIndexedvNV");
    static void (*p)(GLuint, const GLint *); if (!p) p = gl_proc("glScissorIndexedvNV");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    const GLint * a1 = (const GLint *)G2H(arg32(&a));
    p(a0, a1);
}
void G_glScissorIndexedvOES(CPU *c) { RT_PRIMEIRA("glScissorIndexedvOES");
    static void (*p)(GLuint, const GLint *); if (!p) p = gl_proc("glScissorIndexedvOES");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    const GLint * a1 = (const GLint *)G2H(arg32(&a));
    p(a0, a1);
}
void G_glSelectPerfMonitorCountersAMD(CPU *c) { RT_PRIMEIRA("glSelectPerfMonitorCountersAMD");
    static void (*p)(GLuint, GLboolean, GLuint, GLint, GLuint *); if (!p) p = gl_proc("glSelectPerfMonitorCountersAMD");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLboolean a1 = (GLboolean)arg32(&a);
    GLuint a2 = (GLuint)arg32(&a);
    GLint a3 = (GLint)arg32(&a);
    GLuint * a4 = (GLuint *)G2H(arg32(&a));
    p(a0, a1, a2, a3, a4);
}
void G_glSemaphoreParameterui64vEXT(CPU *c) { RT_PRIMEIRA("glSemaphoreParameterui64vEXT");
    static void (*p)(GLuint, GLenum, const GLuint64 *); if (!p) p = gl_proc("glSemaphoreParameterui64vEXT");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    const GLuint64 * a2 = (const GLuint64 *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glSetFenceNV(CPU *c) { RT_PRIMEIRA("glSetFenceNV");
    static void (*p)(GLuint, GLenum); if (!p) p = gl_proc("glSetFenceNV");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    p(a0, a1);
}
void G_glShaderBinary(CPU *c) { RT_PRIMEIRA("glShaderBinary");
    static void (*p)(GLsizei, const GLuint *, GLenum, const void *, GLsizei); if (!p) p = gl_proc("glShaderBinary");
    Args a = args_de(c); (void)a;
    GLsizei a0 = (GLsizei)arg32(&a);
    const GLuint * a1 = (const GLuint *)G2H(arg32(&a));
    GLenum a2 = (GLenum)arg32(&a);
    const void * a3 = (const void *)G2H(arg32(&a));
    GLsizei a4 = (GLsizei)arg32(&a);
    p(a0, a1, a2, a3, a4);
}
void G_glSignalSemaphoreEXT(CPU *c) { RT_PRIMEIRA("glSignalSemaphoreEXT");
    static void (*p)(GLuint, GLuint, const GLuint *, GLuint, const GLuint *, const GLenum *); if (!p) p = gl_proc("glSignalSemaphoreEXT");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLuint a1 = (GLuint)arg32(&a);
    const GLuint * a2 = (const GLuint *)G2H(arg32(&a));
    GLuint a3 = (GLuint)arg32(&a);
    const GLuint * a4 = (const GLuint *)G2H(arg32(&a));
    const GLenum * a5 = (const GLenum *)G2H(arg32(&a));
    p(a0, a1, a2, a3, a4, a5);
}
void G_glSignalVkFenceNV(CPU *c) { RT_PRIMEIRA("glSignalVkFenceNV");
    static void (*p)(GLuint64); if (!p) p = gl_proc("glSignalVkFenceNV");
    Args a = args_de(c); (void)a;
    GLuint64 a0 = (GLuint64)arg64(&a);
    p(a0);
}
void G_glSignalVkSemaphoreNV(CPU *c) { RT_PRIMEIRA("glSignalVkSemaphoreNV");
    static void (*p)(GLuint64); if (!p) p = gl_proc("glSignalVkSemaphoreNV");
    Args a = args_de(c); (void)a;
    GLuint64 a0 = (GLuint64)arg64(&a);
    p(a0);
}
void G_glStartTilingQCOM(CPU *c) { RT_PRIMEIRA("glStartTilingQCOM");
    static void (*p)(GLuint, GLuint, GLuint, GLuint, GLbitfield); if (!p) p = gl_proc("glStartTilingQCOM");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLuint a1 = (GLuint)arg32(&a);
    GLuint a2 = (GLuint)arg32(&a);
    GLuint a3 = (GLuint)arg32(&a);
    GLbitfield a4 = (GLbitfield)arg32(&a);
    p(a0, a1, a2, a3, a4);
}
void G_glStencilFillPathInstancedNV(CPU *c) { RT_PRIMEIRA("glStencilFillPathInstancedNV");
    static void (*p)(GLsizei, GLenum, const void *, GLuint, GLenum, GLuint, GLenum, const GLfloat *); if (!p) p = gl_proc("glStencilFillPathInstancedNV");
    Args a = args_de(c); (void)a;
    GLsizei a0 = (GLsizei)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    const void * a2 = (const void *)G2H(arg32(&a));
    GLuint a3 = (GLuint)arg32(&a);
    GLenum a4 = (GLenum)arg32(&a);
    GLuint a5 = (GLuint)arg32(&a);
    GLenum a6 = (GLenum)arg32(&a);
    const GLfloat * a7 = (const GLfloat *)G2H(arg32(&a));
    p(a0, a1, a2, a3, a4, a5, a6, a7);
}
void G_glStencilFillPathNV(CPU *c) { RT_PRIMEIRA("glStencilFillPathNV");
    static void (*p)(GLuint, GLenum, GLuint); if (!p) p = gl_proc("glStencilFillPathNV");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLuint a2 = (GLuint)arg32(&a);
    p(a0, a1, a2);
}
void G_glStencilFunc(CPU *c) { RT_PRIMEIRA("glStencilFunc");
    static void (*p)(GLenum, GLint, GLuint); if (!p) p = gl_proc("glStencilFunc");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLuint a2 = (GLuint)arg32(&a);
    p(a0, a1, a2);
}
void G_glStencilFuncSeparate(CPU *c) { RT_PRIMEIRA("glStencilFuncSeparate");
    static void (*p)(GLenum, GLenum, GLint, GLuint); if (!p) p = gl_proc("glStencilFuncSeparate");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLint a2 = (GLint)arg32(&a);
    GLuint a3 = (GLuint)arg32(&a);
    p(a0, a1, a2, a3);
}
void G_glStencilMask(CPU *c) { RT_PRIMEIRA("glStencilMask");
    static void (*p)(GLuint); if (!p) p = gl_proc("glStencilMask");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    p(a0);
}
void G_glStencilMaskSeparate(CPU *c) { RT_PRIMEIRA("glStencilMaskSeparate");
    static void (*p)(GLenum, GLuint); if (!p) p = gl_proc("glStencilMaskSeparate");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLuint a1 = (GLuint)arg32(&a);
    p(a0, a1);
}
void G_glStencilOp(CPU *c) { RT_PRIMEIRA("glStencilOp");
    static void (*p)(GLenum, GLenum, GLenum); if (!p) p = gl_proc("glStencilOp");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLenum a2 = (GLenum)arg32(&a);
    p(a0, a1, a2);
}
void G_glStencilOpSeparate(CPU *c) { RT_PRIMEIRA("glStencilOpSeparate");
    static void (*p)(GLenum, GLenum, GLenum, GLenum); if (!p) p = gl_proc("glStencilOpSeparate");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLenum a2 = (GLenum)arg32(&a);
    GLenum a3 = (GLenum)arg32(&a);
    p(a0, a1, a2, a3);
}
void G_glStencilStrokePathInstancedNV(CPU *c) { RT_PRIMEIRA("glStencilStrokePathInstancedNV");
    static void (*p)(GLsizei, GLenum, const void *, GLuint, GLint, GLuint, GLenum, const GLfloat *); if (!p) p = gl_proc("glStencilStrokePathInstancedNV");
    Args a = args_de(c); (void)a;
    GLsizei a0 = (GLsizei)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    const void * a2 = (const void *)G2H(arg32(&a));
    GLuint a3 = (GLuint)arg32(&a);
    GLint a4 = (GLint)arg32(&a);
    GLuint a5 = (GLuint)arg32(&a);
    GLenum a6 = (GLenum)arg32(&a);
    const GLfloat * a7 = (const GLfloat *)G2H(arg32(&a));
    p(a0, a1, a2, a3, a4, a5, a6, a7);
}
void G_glStencilStrokePathNV(CPU *c) { RT_PRIMEIRA("glStencilStrokePathNV");
    static void (*p)(GLuint, GLint, GLuint); if (!p) p = gl_proc("glStencilStrokePathNV");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLuint a2 = (GLuint)arg32(&a);
    p(a0, a1, a2);
}
void G_glStencilThenCoverFillPathInstancedNV(CPU *c) { RT_PRIMEIRA("glStencilThenCoverFillPathInstancedNV");
    static void (*p)(GLsizei, GLenum, const void *, GLuint, GLenum, GLuint, GLenum, GLenum, const GLfloat *); if (!p) p = gl_proc("glStencilThenCoverFillPathInstancedNV");
    Args a = args_de(c); (void)a;
    GLsizei a0 = (GLsizei)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    const void * a2 = (const void *)G2H(arg32(&a));
    GLuint a3 = (GLuint)arg32(&a);
    GLenum a4 = (GLenum)arg32(&a);
    GLuint a5 = (GLuint)arg32(&a);
    GLenum a6 = (GLenum)arg32(&a);
    GLenum a7 = (GLenum)arg32(&a);
    const GLfloat * a8 = (const GLfloat *)G2H(arg32(&a));
    p(a0, a1, a2, a3, a4, a5, a6, a7, a8);
}
void G_glStencilThenCoverFillPathNV(CPU *c) { RT_PRIMEIRA("glStencilThenCoverFillPathNV");
    static void (*p)(GLuint, GLenum, GLuint, GLenum); if (!p) p = gl_proc("glStencilThenCoverFillPathNV");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLuint a2 = (GLuint)arg32(&a);
    GLenum a3 = (GLenum)arg32(&a);
    p(a0, a1, a2, a3);
}
void G_glStencilThenCoverStrokePathInstancedNV(CPU *c) { RT_PRIMEIRA("glStencilThenCoverStrokePathInstancedNV");
    static void (*p)(GLsizei, GLenum, const void *, GLuint, GLint, GLuint, GLenum, GLenum, const GLfloat *); if (!p) p = gl_proc("glStencilThenCoverStrokePathInstancedNV");
    Args a = args_de(c); (void)a;
    GLsizei a0 = (GLsizei)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    const void * a2 = (const void *)G2H(arg32(&a));
    GLuint a3 = (GLuint)arg32(&a);
    GLint a4 = (GLint)arg32(&a);
    GLuint a5 = (GLuint)arg32(&a);
    GLenum a6 = (GLenum)arg32(&a);
    GLenum a7 = (GLenum)arg32(&a);
    const GLfloat * a8 = (const GLfloat *)G2H(arg32(&a));
    p(a0, a1, a2, a3, a4, a5, a6, a7, a8);
}
void G_glStencilThenCoverStrokePathNV(CPU *c) { RT_PRIMEIRA("glStencilThenCoverStrokePathNV");
    static void (*p)(GLuint, GLint, GLuint, GLenum); if (!p) p = gl_proc("glStencilThenCoverStrokePathNV");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLuint a2 = (GLuint)arg32(&a);
    GLenum a3 = (GLenum)arg32(&a);
    p(a0, a1, a2, a3);
}
void G_glSubpixelPrecisionBiasNV(CPU *c) { RT_PRIMEIRA("glSubpixelPrecisionBiasNV");
    static void (*p)(GLuint, GLuint); if (!p) p = gl_proc("glSubpixelPrecisionBiasNV");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLuint a1 = (GLuint)arg32(&a);
    p(a0, a1);
}
void G_glTestFenceNV(CPU *c) { RT_PRIMEIRA("glTestFenceNV");
    static GLboolean (*p)(GLuint); if (!p) p = gl_proc("glTestFenceNV");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    ret32(c, (uint32_t)p(a0));
}
void G_glTexBuffer(CPU *c) { RT_PRIMEIRA("glTexBuffer");
    static void (*p)(GLenum, GLenum, GLuint); if (!p) p = gl_proc("glTexBuffer");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLuint a2 = (GLuint)arg32(&a);
    p(a0, a1, a2);
}
void G_glTexBufferEXT(CPU *c) { RT_PRIMEIRA("glTexBufferEXT");
    static void (*p)(GLenum, GLenum, GLuint); if (!p) p = gl_proc("glTexBufferEXT");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLuint a2 = (GLuint)arg32(&a);
    p(a0, a1, a2);
}
void G_glTexBufferOES(CPU *c) { RT_PRIMEIRA("glTexBufferOES");
    static void (*p)(GLenum, GLenum, GLuint); if (!p) p = gl_proc("glTexBufferOES");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLuint a2 = (GLuint)arg32(&a);
    p(a0, a1, a2);
}
void G_glTexBufferRange(CPU *c) { RT_PRIMEIRA("glTexBufferRange");
    static void (*p)(GLenum, GLenum, GLuint, GLintptr, GLsizeiptr); if (!p) p = gl_proc("glTexBufferRange");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLuint a2 = (GLuint)arg32(&a);
    GLintptr a3 = (GLintptr)(int32_t)arg32(&a);
    GLsizeiptr a4 = (GLsizeiptr)(int32_t)arg32(&a);
    p(a0, a1, a2, a3, a4);
}
void G_glTexBufferRangeEXT(CPU *c) { RT_PRIMEIRA("glTexBufferRangeEXT");
    static void (*p)(GLenum, GLenum, GLuint, GLintptr, GLsizeiptr); if (!p) p = gl_proc("glTexBufferRangeEXT");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLuint a2 = (GLuint)arg32(&a);
    GLintptr a3 = (GLintptr)(int32_t)arg32(&a);
    GLsizeiptr a4 = (GLsizeiptr)(int32_t)arg32(&a);
    p(a0, a1, a2, a3, a4);
}
void G_glTexBufferRangeOES(CPU *c) { RT_PRIMEIRA("glTexBufferRangeOES");
    static void (*p)(GLenum, GLenum, GLuint, GLintptr, GLsizeiptr); if (!p) p = gl_proc("glTexBufferRangeOES");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLuint a2 = (GLuint)arg32(&a);
    GLintptr a3 = (GLintptr)(int32_t)arg32(&a);
    GLsizeiptr a4 = (GLsizeiptr)(int32_t)arg32(&a);
    p(a0, a1, a2, a3, a4);
}
void G_glTexPageCommitmentEXT(CPU *c) { RT_PRIMEIRA("glTexPageCommitmentEXT");
    static void (*p)(GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLboolean); if (!p) p = gl_proc("glTexPageCommitmentEXT");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLint a2 = (GLint)arg32(&a);
    GLint a3 = (GLint)arg32(&a);
    GLint a4 = (GLint)arg32(&a);
    GLsizei a5 = (GLsizei)arg32(&a);
    GLsizei a6 = (GLsizei)arg32(&a);
    GLsizei a7 = (GLsizei)arg32(&a);
    GLboolean a8 = (GLboolean)arg32(&a);
    p(a0, a1, a2, a3, a4, a5, a6, a7, a8);
}
void G_glTexParameterIiv(CPU *c) { RT_PRIMEIRA("glTexParameterIiv");
    static void (*p)(GLenum, GLenum, const GLint *); if (!p) p = gl_proc("glTexParameterIiv");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    const GLint * a2 = (const GLint *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glTexParameterIivEXT(CPU *c) { RT_PRIMEIRA("glTexParameterIivEXT");
    static void (*p)(GLenum, GLenum, const GLint *); if (!p) p = gl_proc("glTexParameterIivEXT");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    const GLint * a2 = (const GLint *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glTexParameterIivOES(CPU *c) { RT_PRIMEIRA("glTexParameterIivOES");
    static void (*p)(GLenum, GLenum, const GLint *); if (!p) p = gl_proc("glTexParameterIivOES");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    const GLint * a2 = (const GLint *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glTexParameterIuiv(CPU *c) { RT_PRIMEIRA("glTexParameterIuiv");
    static void (*p)(GLenum, GLenum, const GLuint *); if (!p) p = gl_proc("glTexParameterIuiv");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    const GLuint * a2 = (const GLuint *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glTexParameterIuivEXT(CPU *c) { RT_PRIMEIRA("glTexParameterIuivEXT");
    static void (*p)(GLenum, GLenum, const GLuint *); if (!p) p = gl_proc("glTexParameterIuivEXT");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    const GLuint * a2 = (const GLuint *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glTexParameterIuivOES(CPU *c) { RT_PRIMEIRA("glTexParameterIuivOES");
    static void (*p)(GLenum, GLenum, const GLuint *); if (!p) p = gl_proc("glTexParameterIuivOES");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    const GLuint * a2 = (const GLuint *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glTexParameterf(CPU *c) { RT_PRIMEIRA("glTexParameterf");
    static void (*p)(GLenum, GLenum, GLfloat); if (!p) p = gl_proc("glTexParameterf");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLfloat a2 = argf(&a);
    if (a1 == 0x8501 /* GL_TEXTURE_LOD_BIAS: so no desktop */) return;
    p(a0, a1, a2);
}
void G_glTexParameterfv(CPU *c) { RT_PRIMEIRA("glTexParameterfv");
    static void (*p)(GLenum, GLenum, const GLfloat *); if (!p) p = gl_proc("glTexParameterfv");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    const GLfloat * a2 = (const GLfloat *)G2H(arg32(&a));
    if (a1 == 0x8501) return;
    p(a0, a1, a2);
}
void G_glTexParameteri(CPU *c) { RT_PRIMEIRA("glTexParameteri");
    static void (*p)(GLenum, GLenum, GLint); if (!p) p = gl_proc("glTexParameteri");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLint a2 = (GLint)arg32(&a);
    if (a1 == 0x8501) return;
    p(a0, a1, a2);
}
void G_glTexParameteriv(CPU *c) { RT_PRIMEIRA("glTexParameteriv");
    static void (*p)(GLenum, GLenum, const GLint *); if (!p) p = gl_proc("glTexParameteriv");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    const GLint * a2 = (const GLint *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glTexStorage1DEXT(CPU *c) { RT_PRIMEIRA("glTexStorage1DEXT");
    static void (*p)(GLenum, GLsizei, GLenum, GLsizei); if (!p) p = gl_proc("glTexStorage1DEXT");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    GLenum a2 = (GLenum)arg32(&a);
    GLsizei a3 = (GLsizei)arg32(&a);
    p(a0, a1, a2, a3);
}
void G_glTexStorage2D(CPU *c) { RT_PRIMEIRA("glTexStorage2D");
    static void (*p)(GLenum, GLsizei, GLenum, GLsizei, GLsizei); if (!p) p = gl_proc("glTexStorage2D");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    GLenum a2 = (GLenum)arg32(&a);
    GLsizei a3 = (GLsizei)arg32(&a);
    GLsizei a4 = (GLsizei)arg32(&a);
    { GLenum fmt_interno(GLenum, int); a2 = fmt_interno(a2, 0); }
    p(a0, a1, a2, a3, a4);
}
void G_glTexStorage2DEXT(CPU *c) { RT_PRIMEIRA("glTexStorage2DEXT");
    static void (*p)(GLenum, GLsizei, GLenum, GLsizei, GLsizei); if (!p) p = gl_proc("glTexStorage2DEXT");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    GLenum a2 = (GLenum)arg32(&a);
    GLsizei a3 = (GLsizei)arg32(&a);
    GLsizei a4 = (GLsizei)arg32(&a);
    p(a0, a1, a2, a3, a4);
}
void G_glTexStorage2DMultisample(CPU *c) { RT_PRIMEIRA("glTexStorage2DMultisample");
    static void (*p)(GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLboolean); if (!p) p = gl_proc("glTexStorage2DMultisample");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    GLenum a2 = (GLenum)arg32(&a);
    GLsizei a3 = (GLsizei)arg32(&a);
    GLsizei a4 = (GLsizei)arg32(&a);
    GLboolean a5 = (GLboolean)arg32(&a);
    { GLenum fmt_interno(GLenum, int); a2 = fmt_interno(a2, 1); }
    p(a0, a1, a2, a3, a4, a5);
}
void G_glTexStorage3D(CPU *c) { RT_PRIMEIRA("glTexStorage3D");
    static void (*p)(GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLsizei); if (!p) p = gl_proc("glTexStorage3D");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    GLenum a2 = (GLenum)arg32(&a);
    GLsizei a3 = (GLsizei)arg32(&a);
    GLsizei a4 = (GLsizei)arg32(&a);
    GLsizei a5 = (GLsizei)arg32(&a);
    { GLenum fmt_interno(GLenum, int); a2 = fmt_interno(a2, 0); }
    p(a0, a1, a2, a3, a4, a5);
}
void G_glTexStorage3DEXT(CPU *c) { RT_PRIMEIRA("glTexStorage3DEXT");
    static void (*p)(GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLsizei); if (!p) p = gl_proc("glTexStorage3DEXT");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    GLenum a2 = (GLenum)arg32(&a);
    GLsizei a3 = (GLsizei)arg32(&a);
    GLsizei a4 = (GLsizei)arg32(&a);
    GLsizei a5 = (GLsizei)arg32(&a);
    p(a0, a1, a2, a3, a4, a5);
}
void G_glTexStorage3DMultisample(CPU *c) { RT_PRIMEIRA("glTexStorage3DMultisample");
    static void (*p)(GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLsizei, GLboolean); if (!p) p = gl_proc("glTexStorage3DMultisample");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    GLenum a2 = (GLenum)arg32(&a);
    GLsizei a3 = (GLsizei)arg32(&a);
    GLsizei a4 = (GLsizei)arg32(&a);
    GLsizei a5 = (GLsizei)arg32(&a);
    GLboolean a6 = (GLboolean)arg32(&a);
    p(a0, a1, a2, a3, a4, a5, a6);
}
void G_glTexStorage3DMultisampleOES(CPU *c) { RT_PRIMEIRA("glTexStorage3DMultisampleOES");
    static void (*p)(GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLsizei, GLboolean); if (!p) p = gl_proc("glTexStorage3DMultisampleOES");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    GLenum a2 = (GLenum)arg32(&a);
    GLsizei a3 = (GLsizei)arg32(&a);
    GLsizei a4 = (GLsizei)arg32(&a);
    GLsizei a5 = (GLsizei)arg32(&a);
    GLboolean a6 = (GLboolean)arg32(&a);
    p(a0, a1, a2, a3, a4, a5, a6);
}
void G_glTexStorageMem2DEXT(CPU *c) { RT_PRIMEIRA("glTexStorageMem2DEXT");
    static void (*p)(GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLuint, GLuint64); if (!p) p = gl_proc("glTexStorageMem2DEXT");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    GLenum a2 = (GLenum)arg32(&a);
    GLsizei a3 = (GLsizei)arg32(&a);
    GLsizei a4 = (GLsizei)arg32(&a);
    GLuint a5 = (GLuint)arg32(&a);
    GLuint64 a6 = (GLuint64)arg64(&a);
    p(a0, a1, a2, a3, a4, a5, a6);
}
void G_glTexStorageMem2DMultisampleEXT(CPU *c) { RT_PRIMEIRA("glTexStorageMem2DMultisampleEXT");
    static void (*p)(GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLboolean, GLuint, GLuint64); if (!p) p = gl_proc("glTexStorageMem2DMultisampleEXT");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    GLenum a2 = (GLenum)arg32(&a);
    GLsizei a3 = (GLsizei)arg32(&a);
    GLsizei a4 = (GLsizei)arg32(&a);
    GLboolean a5 = (GLboolean)arg32(&a);
    GLuint a6 = (GLuint)arg32(&a);
    GLuint64 a7 = (GLuint64)arg64(&a);
    p(a0, a1, a2, a3, a4, a5, a6, a7);
}
void G_glTexStorageMem3DEXT(CPU *c) { RT_PRIMEIRA("glTexStorageMem3DEXT");
    static void (*p)(GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLsizei, GLuint, GLuint64); if (!p) p = gl_proc("glTexStorageMem3DEXT");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    GLenum a2 = (GLenum)arg32(&a);
    GLsizei a3 = (GLsizei)arg32(&a);
    GLsizei a4 = (GLsizei)arg32(&a);
    GLsizei a5 = (GLsizei)arg32(&a);
    GLuint a6 = (GLuint)arg32(&a);
    GLuint64 a7 = (GLuint64)arg64(&a);
    p(a0, a1, a2, a3, a4, a5, a6, a7);
}
void G_glTexStorageMem3DMultisampleEXT(CPU *c) { RT_PRIMEIRA("glTexStorageMem3DMultisampleEXT");
    static void (*p)(GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLsizei, GLboolean, GLuint, GLuint64); if (!p) p = gl_proc("glTexStorageMem3DMultisampleEXT");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    GLenum a2 = (GLenum)arg32(&a);
    GLsizei a3 = (GLsizei)arg32(&a);
    GLsizei a4 = (GLsizei)arg32(&a);
    GLsizei a5 = (GLsizei)arg32(&a);
    GLboolean a6 = (GLboolean)arg32(&a);
    GLuint a7 = (GLuint)arg32(&a);
    GLuint64 a8 = (GLuint64)arg64(&a);
    p(a0, a1, a2, a3, a4, a5, a6, a7, a8);
}
void G_glTextureFoveationParametersQCOM(CPU *c) { RT_PRIMEIRA("glTextureFoveationParametersQCOM");
    static void (*p)(GLuint, GLuint, GLuint, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat); if (!p) p = gl_proc("glTextureFoveationParametersQCOM");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLuint a1 = (GLuint)arg32(&a);
    GLuint a2 = (GLuint)arg32(&a);
    GLfloat a3 = argf(&a);
    GLfloat a4 = argf(&a);
    GLfloat a5 = argf(&a);
    GLfloat a6 = argf(&a);
    GLfloat a7 = argf(&a);
    p(a0, a1, a2, a3, a4, a5, a6, a7);
}
void G_glTextureStorage1DEXT(CPU *c) { RT_PRIMEIRA("glTextureStorage1DEXT");
    static void (*p)(GLuint, GLenum, GLsizei, GLenum, GLsizei); if (!p) p = gl_proc("glTextureStorage1DEXT");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    GLenum a3 = (GLenum)arg32(&a);
    GLsizei a4 = (GLsizei)arg32(&a);
    p(a0, a1, a2, a3, a4);
}
void G_glTextureStorage2DEXT(CPU *c) { RT_PRIMEIRA("glTextureStorage2DEXT");
    static void (*p)(GLuint, GLenum, GLsizei, GLenum, GLsizei, GLsizei); if (!p) p = gl_proc("glTextureStorage2DEXT");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    GLenum a3 = (GLenum)arg32(&a);
    GLsizei a4 = (GLsizei)arg32(&a);
    GLsizei a5 = (GLsizei)arg32(&a);
    p(a0, a1, a2, a3, a4, a5);
}
void G_glTextureStorage3DEXT(CPU *c) { RT_PRIMEIRA("glTextureStorage3DEXT");
    static void (*p)(GLuint, GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLsizei); if (!p) p = gl_proc("glTextureStorage3DEXT");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    GLenum a3 = (GLenum)arg32(&a);
    GLsizei a4 = (GLsizei)arg32(&a);
    GLsizei a5 = (GLsizei)arg32(&a);
    GLsizei a6 = (GLsizei)arg32(&a);
    p(a0, a1, a2, a3, a4, a5, a6);
}
void G_glTextureStorageMem2DEXT(CPU *c) { RT_PRIMEIRA("glTextureStorageMem2DEXT");
    static void (*p)(GLuint, GLsizei, GLenum, GLsizei, GLsizei, GLuint, GLuint64); if (!p) p = gl_proc("glTextureStorageMem2DEXT");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    GLenum a2 = (GLenum)arg32(&a);
    GLsizei a3 = (GLsizei)arg32(&a);
    GLsizei a4 = (GLsizei)arg32(&a);
    GLuint a5 = (GLuint)arg32(&a);
    GLuint64 a6 = (GLuint64)arg64(&a);
    p(a0, a1, a2, a3, a4, a5, a6);
}
void G_glTextureStorageMem2DMultisampleEXT(CPU *c) { RT_PRIMEIRA("glTextureStorageMem2DMultisampleEXT");
    static void (*p)(GLuint, GLsizei, GLenum, GLsizei, GLsizei, GLboolean, GLuint, GLuint64); if (!p) p = gl_proc("glTextureStorageMem2DMultisampleEXT");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    GLenum a2 = (GLenum)arg32(&a);
    GLsizei a3 = (GLsizei)arg32(&a);
    GLsizei a4 = (GLsizei)arg32(&a);
    GLboolean a5 = (GLboolean)arg32(&a);
    GLuint a6 = (GLuint)arg32(&a);
    GLuint64 a7 = (GLuint64)arg64(&a);
    p(a0, a1, a2, a3, a4, a5, a6, a7);
}
void G_glTextureStorageMem3DEXT(CPU *c) { RT_PRIMEIRA("glTextureStorageMem3DEXT");
    static void (*p)(GLuint, GLsizei, GLenum, GLsizei, GLsizei, GLsizei, GLuint, GLuint64); if (!p) p = gl_proc("glTextureStorageMem3DEXT");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    GLenum a2 = (GLenum)arg32(&a);
    GLsizei a3 = (GLsizei)arg32(&a);
    GLsizei a4 = (GLsizei)arg32(&a);
    GLsizei a5 = (GLsizei)arg32(&a);
    GLuint a6 = (GLuint)arg32(&a);
    GLuint64 a7 = (GLuint64)arg64(&a);
    p(a0, a1, a2, a3, a4, a5, a6, a7);
}
void G_glTextureStorageMem3DMultisampleEXT(CPU *c) { RT_PRIMEIRA("glTextureStorageMem3DMultisampleEXT");
    static void (*p)(GLuint, GLsizei, GLenum, GLsizei, GLsizei, GLsizei, GLboolean, GLuint, GLuint64); if (!p) p = gl_proc("glTextureStorageMem3DMultisampleEXT");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    GLenum a2 = (GLenum)arg32(&a);
    GLsizei a3 = (GLsizei)arg32(&a);
    GLsizei a4 = (GLsizei)arg32(&a);
    GLsizei a5 = (GLsizei)arg32(&a);
    GLboolean a6 = (GLboolean)arg32(&a);
    GLuint a7 = (GLuint)arg32(&a);
    GLuint64 a8 = (GLuint64)arg64(&a);
    p(a0, a1, a2, a3, a4, a5, a6, a7, a8);
}
void G_glTextureViewEXT(CPU *c) { RT_PRIMEIRA("glTextureViewEXT");
    static void (*p)(GLuint, GLenum, GLuint, GLenum, GLuint, GLuint, GLuint, GLuint); if (!p) p = gl_proc("glTextureViewEXT");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLuint a2 = (GLuint)arg32(&a);
    GLenum a3 = (GLenum)arg32(&a);
    GLuint a4 = (GLuint)arg32(&a);
    GLuint a5 = (GLuint)arg32(&a);
    GLuint a6 = (GLuint)arg32(&a);
    GLuint a7 = (GLuint)arg32(&a);
    p(a0, a1, a2, a3, a4, a5, a6, a7);
}
void G_glTextureViewOES(CPU *c) { RT_PRIMEIRA("glTextureViewOES");
    static void (*p)(GLuint, GLenum, GLuint, GLenum, GLuint, GLuint, GLuint, GLuint); if (!p) p = gl_proc("glTextureViewOES");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLuint a2 = (GLuint)arg32(&a);
    GLenum a3 = (GLenum)arg32(&a);
    GLuint a4 = (GLuint)arg32(&a);
    GLuint a5 = (GLuint)arg32(&a);
    GLuint a6 = (GLuint)arg32(&a);
    GLuint a7 = (GLuint)arg32(&a);
    p(a0, a1, a2, a3, a4, a5, a6, a7);
}
void G_glTransformPathNV(CPU *c) { RT_PRIMEIRA("glTransformPathNV");
    static void (*p)(GLuint, GLuint, GLenum, const GLfloat *); if (!p) p = gl_proc("glTransformPathNV");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLuint a1 = (GLuint)arg32(&a);
    GLenum a2 = (GLenum)arg32(&a);
    const GLfloat * a3 = (const GLfloat *)G2H(arg32(&a));
    p(a0, a1, a2, a3);
}
void G_glUniform1f(CPU *c) { RT_PRIMEIRA("glUniform1f");
    static void (*p)(GLint, GLfloat); if (!p) p = gl_proc("glUniform1f");
    Args a = args_de(c); (void)a;
    GLint a0 = (GLint)arg32(&a);
    GLfloat a1 = argf(&a);
    p(a0, a1);
}
void G_glUniform1fv(CPU *c) { RT_PRIMEIRA("glUniform1fv");
    static void (*p)(GLint, GLsizei, const GLfloat *); if (!p) p = gl_proc("glUniform1fv");
    Args a = args_de(c); (void)a;
    GLint a0 = (GLint)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    const GLfloat * a2 = (const GLfloat *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glUniform1i(CPU *c) { RT_PRIMEIRA("glUniform1i");
    static void (*p)(GLint, GLint); if (!p) p = gl_proc("glUniform1i");
    Args a = args_de(c); (void)a;
    GLint a0 = (GLint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    p(a0, a1);
}
void G_glUniform1i64NV(CPU *c) { RT_PRIMEIRA("glUniform1i64NV");
    static void (*p)(GLint, GLint64EXT); if (!p) p = gl_proc("glUniform1i64NV");
    Args a = args_de(c); (void)a;
    GLint a0 = (GLint)arg32(&a);
    GLint64EXT a1 = (GLint64EXT)arg64(&a);
    p(a0, a1);
}
void G_glUniform1i64vNV(CPU *c) { RT_PRIMEIRA("glUniform1i64vNV");
    static void (*p)(GLint, GLsizei, const GLint64EXT *); if (!p) p = gl_proc("glUniform1i64vNV");
    Args a = args_de(c); (void)a;
    GLint a0 = (GLint)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    const GLint64EXT * a2 = (const GLint64EXT *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glUniform1iv(CPU *c) { RT_PRIMEIRA("glUniform1iv");
    static void (*p)(GLint, GLsizei, const GLint *); if (!p) p = gl_proc("glUniform1iv");
    Args a = args_de(c); (void)a;
    GLint a0 = (GLint)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    const GLint * a2 = (const GLint *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glUniform1ui(CPU *c) { RT_PRIMEIRA("glUniform1ui");
    static void (*p)(GLint, GLuint); if (!p) p = gl_proc("glUniform1ui");
    Args a = args_de(c); (void)a;
    GLint a0 = (GLint)arg32(&a);
    GLuint a1 = (GLuint)arg32(&a);
    p(a0, a1);
}
void G_glUniform1ui64NV(CPU *c) { RT_PRIMEIRA("glUniform1ui64NV");
    static void (*p)(GLint, GLuint64EXT); if (!p) p = gl_proc("glUniform1ui64NV");
    Args a = args_de(c); (void)a;
    GLint a0 = (GLint)arg32(&a);
    GLuint64EXT a1 = (GLuint64EXT)arg64(&a);
    p(a0, a1);
}
void G_glUniform1ui64vNV(CPU *c) { RT_PRIMEIRA("glUniform1ui64vNV");
    static void (*p)(GLint, GLsizei, const GLuint64EXT *); if (!p) p = gl_proc("glUniform1ui64vNV");
    Args a = args_de(c); (void)a;
    GLint a0 = (GLint)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    const GLuint64EXT * a2 = (const GLuint64EXT *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glUniform1uiv(CPU *c) { RT_PRIMEIRA("glUniform1uiv");
    static void (*p)(GLint, GLsizei, const GLuint *); if (!p) p = gl_proc("glUniform1uiv");
    Args a = args_de(c); (void)a;
    GLint a0 = (GLint)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    const GLuint * a2 = (const GLuint *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glUniform2f(CPU *c) { RT_PRIMEIRA("glUniform2f");
    static void (*p)(GLint, GLfloat, GLfloat); if (!p) p = gl_proc("glUniform2f");
    Args a = args_de(c); (void)a;
    GLint a0 = (GLint)arg32(&a);
    GLfloat a1 = argf(&a);
    GLfloat a2 = argf(&a);
    p(a0, a1, a2);
}
void G_glUniform2fv(CPU *c) { RT_PRIMEIRA("glUniform2fv");
    static void (*p)(GLint, GLsizei, const GLfloat *); if (!p) p = gl_proc("glUniform2fv");
    Args a = args_de(c); (void)a;
    GLint a0 = (GLint)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    const GLfloat * a2 = (const GLfloat *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glUniform2i(CPU *c) { RT_PRIMEIRA("glUniform2i");
    static void (*p)(GLint, GLint, GLint); if (!p) p = gl_proc("glUniform2i");
    Args a = args_de(c); (void)a;
    GLint a0 = (GLint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLint a2 = (GLint)arg32(&a);
    p(a0, a1, a2);
}
void G_glUniform2i64NV(CPU *c) { RT_PRIMEIRA("glUniform2i64NV");
    static void (*p)(GLint, GLint64EXT, GLint64EXT); if (!p) p = gl_proc("glUniform2i64NV");
    Args a = args_de(c); (void)a;
    GLint a0 = (GLint)arg32(&a);
    GLint64EXT a1 = (GLint64EXT)arg64(&a);
    GLint64EXT a2 = (GLint64EXT)arg64(&a);
    p(a0, a1, a2);
}
void G_glUniform2i64vNV(CPU *c) { RT_PRIMEIRA("glUniform2i64vNV");
    static void (*p)(GLint, GLsizei, const GLint64EXT *); if (!p) p = gl_proc("glUniform2i64vNV");
    Args a = args_de(c); (void)a;
    GLint a0 = (GLint)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    const GLint64EXT * a2 = (const GLint64EXT *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glUniform2iv(CPU *c) { RT_PRIMEIRA("glUniform2iv");
    static void (*p)(GLint, GLsizei, const GLint *); if (!p) p = gl_proc("glUniform2iv");
    Args a = args_de(c); (void)a;
    GLint a0 = (GLint)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    const GLint * a2 = (const GLint *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glUniform2ui(CPU *c) { RT_PRIMEIRA("glUniform2ui");
    static void (*p)(GLint, GLuint, GLuint); if (!p) p = gl_proc("glUniform2ui");
    Args a = args_de(c); (void)a;
    GLint a0 = (GLint)arg32(&a);
    GLuint a1 = (GLuint)arg32(&a);
    GLuint a2 = (GLuint)arg32(&a);
    p(a0, a1, a2);
}
void G_glUniform2ui64NV(CPU *c) { RT_PRIMEIRA("glUniform2ui64NV");
    static void (*p)(GLint, GLuint64EXT, GLuint64EXT); if (!p) p = gl_proc("glUniform2ui64NV");
    Args a = args_de(c); (void)a;
    GLint a0 = (GLint)arg32(&a);
    GLuint64EXT a1 = (GLuint64EXT)arg64(&a);
    GLuint64EXT a2 = (GLuint64EXT)arg64(&a);
    p(a0, a1, a2);
}
void G_glUniform2ui64vNV(CPU *c) { RT_PRIMEIRA("glUniform2ui64vNV");
    static void (*p)(GLint, GLsizei, const GLuint64EXT *); if (!p) p = gl_proc("glUniform2ui64vNV");
    Args a = args_de(c); (void)a;
    GLint a0 = (GLint)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    const GLuint64EXT * a2 = (const GLuint64EXT *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glUniform2uiv(CPU *c) { RT_PRIMEIRA("glUniform2uiv");
    static void (*p)(GLint, GLsizei, const GLuint *); if (!p) p = gl_proc("glUniform2uiv");
    Args a = args_de(c); (void)a;
    GLint a0 = (GLint)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    const GLuint * a2 = (const GLuint *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glUniform3f(CPU *c) { RT_PRIMEIRA("glUniform3f");
    static void (*p)(GLint, GLfloat, GLfloat, GLfloat); if (!p) p = gl_proc("glUniform3f");
    Args a = args_de(c); (void)a;
    GLint a0 = (GLint)arg32(&a);
    GLfloat a1 = argf(&a);
    GLfloat a2 = argf(&a);
    GLfloat a3 = argf(&a);
    p(a0, a1, a2, a3);
}
void G_glUniform3fv(CPU *c) { RT_PRIMEIRA("glUniform3fv");
    static void (*p)(GLint, GLsizei, const GLfloat *); if (!p) p = gl_proc("glUniform3fv");
    Args a = args_de(c); (void)a;
    GLint a0 = (GLint)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    const GLfloat * a2 = (const GLfloat *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glUniform3i(CPU *c) { RT_PRIMEIRA("glUniform3i");
    static void (*p)(GLint, GLint, GLint, GLint); if (!p) p = gl_proc("glUniform3i");
    Args a = args_de(c); (void)a;
    GLint a0 = (GLint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLint a2 = (GLint)arg32(&a);
    GLint a3 = (GLint)arg32(&a);
    p(a0, a1, a2, a3);
}
void G_glUniform3i64NV(CPU *c) { RT_PRIMEIRA("glUniform3i64NV");
    static void (*p)(GLint, GLint64EXT, GLint64EXT, GLint64EXT); if (!p) p = gl_proc("glUniform3i64NV");
    Args a = args_de(c); (void)a;
    GLint a0 = (GLint)arg32(&a);
    GLint64EXT a1 = (GLint64EXT)arg64(&a);
    GLint64EXT a2 = (GLint64EXT)arg64(&a);
    GLint64EXT a3 = (GLint64EXT)arg64(&a);
    p(a0, a1, a2, a3);
}
void G_glUniform3i64vNV(CPU *c) { RT_PRIMEIRA("glUniform3i64vNV");
    static void (*p)(GLint, GLsizei, const GLint64EXT *); if (!p) p = gl_proc("glUniform3i64vNV");
    Args a = args_de(c); (void)a;
    GLint a0 = (GLint)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    const GLint64EXT * a2 = (const GLint64EXT *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glUniform3iv(CPU *c) { RT_PRIMEIRA("glUniform3iv");
    static void (*p)(GLint, GLsizei, const GLint *); if (!p) p = gl_proc("glUniform3iv");
    Args a = args_de(c); (void)a;
    GLint a0 = (GLint)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    const GLint * a2 = (const GLint *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glUniform3ui(CPU *c) { RT_PRIMEIRA("glUniform3ui");
    static void (*p)(GLint, GLuint, GLuint, GLuint); if (!p) p = gl_proc("glUniform3ui");
    Args a = args_de(c); (void)a;
    GLint a0 = (GLint)arg32(&a);
    GLuint a1 = (GLuint)arg32(&a);
    GLuint a2 = (GLuint)arg32(&a);
    GLuint a3 = (GLuint)arg32(&a);
    p(a0, a1, a2, a3);
}
void G_glUniform3ui64NV(CPU *c) { RT_PRIMEIRA("glUniform3ui64NV");
    static void (*p)(GLint, GLuint64EXT, GLuint64EXT, GLuint64EXT); if (!p) p = gl_proc("glUniform3ui64NV");
    Args a = args_de(c); (void)a;
    GLint a0 = (GLint)arg32(&a);
    GLuint64EXT a1 = (GLuint64EXT)arg64(&a);
    GLuint64EXT a2 = (GLuint64EXT)arg64(&a);
    GLuint64EXT a3 = (GLuint64EXT)arg64(&a);
    p(a0, a1, a2, a3);
}
void G_glUniform3ui64vNV(CPU *c) { RT_PRIMEIRA("glUniform3ui64vNV");
    static void (*p)(GLint, GLsizei, const GLuint64EXT *); if (!p) p = gl_proc("glUniform3ui64vNV");
    Args a = args_de(c); (void)a;
    GLint a0 = (GLint)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    const GLuint64EXT * a2 = (const GLuint64EXT *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glUniform3uiv(CPU *c) { RT_PRIMEIRA("glUniform3uiv");
    static void (*p)(GLint, GLsizei, const GLuint *); if (!p) p = gl_proc("glUniform3uiv");
    Args a = args_de(c); (void)a;
    GLint a0 = (GLint)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    const GLuint * a2 = (const GLuint *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glUniform4f(CPU *c) { RT_PRIMEIRA("glUniform4f");
    static void (*p)(GLint, GLfloat, GLfloat, GLfloat, GLfloat); if (!p) p = gl_proc("glUniform4f");
    Args a = args_de(c); (void)a;
    GLint a0 = (GLint)arg32(&a);
    GLfloat a1 = argf(&a);
    GLfloat a2 = argf(&a);
    GLfloat a3 = argf(&a);
    GLfloat a4 = argf(&a);
#ifdef MGS2_DEPURA
    { static int _n; if (_n++ < 40) { GLint pr = 0; glGetIntegerv(GL_CURRENT_PROGRAM, &pr); rt_log("glUniform4f(prog %d, loc %d) = %g %g %g %g", pr, a0, a1, a2, a3, a4); } }
#endif
    p(a0, a1, a2, a3, a4);
}
void G_glUniform4fv(CPU *c) { RT_PRIMEIRA("glUniform4fv");
    static void (*p)(GLint, GLsizei, const GLfloat *); if (!p) p = gl_proc("glUniform4fv");
    Args a = args_de(c); (void)a;
    GLint a0 = (GLint)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    const GLfloat * a2 = (const GLfloat *)G2H(arg32(&a));
#ifdef MGS2_DEPURA
    { static int _n; GLint pr = 0; glGetIntegerv(GL_CURRENT_PROGRAM, &pr);
      if ((pr == 5 || pr == 4) && _n < 6) { _n++; for (int k = 0; k < a1 && k < 12; k++) rt_log("prog %d uniform4fv loc %d [%d] = %g %g %g %g", pr, a0, k, a2[4*k], a2[4*k+1], a2[4*k+2], a2[4*k+3]); } }
#endif
    p(a0, a1, a2);
}
void G_glUniform4i(CPU *c) { RT_PRIMEIRA("glUniform4i");
    static void (*p)(GLint, GLint, GLint, GLint, GLint); if (!p) p = gl_proc("glUniform4i");
    Args a = args_de(c); (void)a;
    GLint a0 = (GLint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLint a2 = (GLint)arg32(&a);
    GLint a3 = (GLint)arg32(&a);
    GLint a4 = (GLint)arg32(&a);
    p(a0, a1, a2, a3, a4);
}
void G_glUniform4i64NV(CPU *c) { RT_PRIMEIRA("glUniform4i64NV");
    static void (*p)(GLint, GLint64EXT, GLint64EXT, GLint64EXT, GLint64EXT); if (!p) p = gl_proc("glUniform4i64NV");
    Args a = args_de(c); (void)a;
    GLint a0 = (GLint)arg32(&a);
    GLint64EXT a1 = (GLint64EXT)arg64(&a);
    GLint64EXT a2 = (GLint64EXT)arg64(&a);
    GLint64EXT a3 = (GLint64EXT)arg64(&a);
    GLint64EXT a4 = (GLint64EXT)arg64(&a);
    p(a0, a1, a2, a3, a4);
}
void G_glUniform4i64vNV(CPU *c) { RT_PRIMEIRA("glUniform4i64vNV");
    static void (*p)(GLint, GLsizei, const GLint64EXT *); if (!p) p = gl_proc("glUniform4i64vNV");
    Args a = args_de(c); (void)a;
    GLint a0 = (GLint)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    const GLint64EXT * a2 = (const GLint64EXT *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glUniform4iv(CPU *c) { RT_PRIMEIRA("glUniform4iv");
    static void (*p)(GLint, GLsizei, const GLint *); if (!p) p = gl_proc("glUniform4iv");
    Args a = args_de(c); (void)a;
    GLint a0 = (GLint)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    const GLint * a2 = (const GLint *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glUniform4ui(CPU *c) { RT_PRIMEIRA("glUniform4ui");
    static void (*p)(GLint, GLuint, GLuint, GLuint, GLuint); if (!p) p = gl_proc("glUniform4ui");
    Args a = args_de(c); (void)a;
    GLint a0 = (GLint)arg32(&a);
    GLuint a1 = (GLuint)arg32(&a);
    GLuint a2 = (GLuint)arg32(&a);
    GLuint a3 = (GLuint)arg32(&a);
    GLuint a4 = (GLuint)arg32(&a);
    p(a0, a1, a2, a3, a4);
}
void G_glUniform4ui64NV(CPU *c) { RT_PRIMEIRA("glUniform4ui64NV");
    static void (*p)(GLint, GLuint64EXT, GLuint64EXT, GLuint64EXT, GLuint64EXT); if (!p) p = gl_proc("glUniform4ui64NV");
    Args a = args_de(c); (void)a;
    GLint a0 = (GLint)arg32(&a);
    GLuint64EXT a1 = (GLuint64EXT)arg64(&a);
    GLuint64EXT a2 = (GLuint64EXT)arg64(&a);
    GLuint64EXT a3 = (GLuint64EXT)arg64(&a);
    GLuint64EXT a4 = (GLuint64EXT)arg64(&a);
    p(a0, a1, a2, a3, a4);
}
void G_glUniform4ui64vNV(CPU *c) { RT_PRIMEIRA("glUniform4ui64vNV");
    static void (*p)(GLint, GLsizei, const GLuint64EXT *); if (!p) p = gl_proc("glUniform4ui64vNV");
    Args a = args_de(c); (void)a;
    GLint a0 = (GLint)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    const GLuint64EXT * a2 = (const GLuint64EXT *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glUniform4uiv(CPU *c) { RT_PRIMEIRA("glUniform4uiv");
    static void (*p)(GLint, GLsizei, const GLuint *); if (!p) p = gl_proc("glUniform4uiv");
    Args a = args_de(c); (void)a;
    GLint a0 = (GLint)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    const GLuint * a2 = (const GLuint *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glUniformBlockBinding(CPU *c) { RT_PRIMEIRA("glUniformBlockBinding");
    static void (*p)(GLuint, GLuint, GLuint); if (!p) p = gl_proc("glUniformBlockBinding");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLuint a1 = (GLuint)arg32(&a);
    GLuint a2 = (GLuint)arg32(&a);
    p(a0, a1, a2);
}
void G_glUniformHandleui64IMG(CPU *c) { RT_PRIMEIRA("glUniformHandleui64IMG");
    static void (*p)(GLint, GLuint64); if (!p) p = gl_proc("glUniformHandleui64IMG");
    Args a = args_de(c); (void)a;
    GLint a0 = (GLint)arg32(&a);
    GLuint64 a1 = (GLuint64)arg64(&a);
    p(a0, a1);
}
void G_glUniformHandleui64NV(CPU *c) { RT_PRIMEIRA("glUniformHandleui64NV");
    static void (*p)(GLint, GLuint64); if (!p) p = gl_proc("glUniformHandleui64NV");
    Args a = args_de(c); (void)a;
    GLint a0 = (GLint)arg32(&a);
    GLuint64 a1 = (GLuint64)arg64(&a);
    p(a0, a1);
}
void G_glUniformHandleui64vIMG(CPU *c) { RT_PRIMEIRA("glUniformHandleui64vIMG");
    static void (*p)(GLint, GLsizei, const GLuint64 *); if (!p) p = gl_proc("glUniformHandleui64vIMG");
    Args a = args_de(c); (void)a;
    GLint a0 = (GLint)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    const GLuint64 * a2 = (const GLuint64 *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glUniformHandleui64vNV(CPU *c) { RT_PRIMEIRA("glUniformHandleui64vNV");
    static void (*p)(GLint, GLsizei, const GLuint64 *); if (!p) p = gl_proc("glUniformHandleui64vNV");
    Args a = args_de(c); (void)a;
    GLint a0 = (GLint)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    const GLuint64 * a2 = (const GLuint64 *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glUniformMatrix2fv(CPU *c) { RT_PRIMEIRA("glUniformMatrix2fv");
    static void (*p)(GLint, GLsizei, GLboolean, const GLfloat *); if (!p) p = gl_proc("glUniformMatrix2fv");
    Args a = args_de(c); (void)a;
    GLint a0 = (GLint)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    GLboolean a2 = (GLboolean)arg32(&a);
    const GLfloat * a3 = (const GLfloat *)G2H(arg32(&a));
    p(a0, a1, a2, a3);
}
void G_glUniformMatrix2x3fv(CPU *c) { RT_PRIMEIRA("glUniformMatrix2x3fv");
    static void (*p)(GLint, GLsizei, GLboolean, const GLfloat *); if (!p) p = gl_proc("glUniformMatrix2x3fv");
    Args a = args_de(c); (void)a;
    GLint a0 = (GLint)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    GLboolean a2 = (GLboolean)arg32(&a);
    const GLfloat * a3 = (const GLfloat *)G2H(arg32(&a));
    p(a0, a1, a2, a3);
}
void G_glUniformMatrix2x3fvNV(CPU *c) { RT_PRIMEIRA("glUniformMatrix2x3fvNV");
    static void (*p)(GLint, GLsizei, GLboolean, const GLfloat *); if (!p) p = gl_proc("glUniformMatrix2x3fvNV");
    Args a = args_de(c); (void)a;
    GLint a0 = (GLint)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    GLboolean a2 = (GLboolean)arg32(&a);
    const GLfloat * a3 = (const GLfloat *)G2H(arg32(&a));
    p(a0, a1, a2, a3);
}
void G_glUniformMatrix2x4fv(CPU *c) { RT_PRIMEIRA("glUniformMatrix2x4fv");
    static void (*p)(GLint, GLsizei, GLboolean, const GLfloat *); if (!p) p = gl_proc("glUniformMatrix2x4fv");
    Args a = args_de(c); (void)a;
    GLint a0 = (GLint)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    GLboolean a2 = (GLboolean)arg32(&a);
    const GLfloat * a3 = (const GLfloat *)G2H(arg32(&a));
    p(a0, a1, a2, a3);
}
void G_glUniformMatrix2x4fvNV(CPU *c) { RT_PRIMEIRA("glUniformMatrix2x4fvNV");
    static void (*p)(GLint, GLsizei, GLboolean, const GLfloat *); if (!p) p = gl_proc("glUniformMatrix2x4fvNV");
    Args a = args_de(c); (void)a;
    GLint a0 = (GLint)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    GLboolean a2 = (GLboolean)arg32(&a);
    const GLfloat * a3 = (const GLfloat *)G2H(arg32(&a));
    p(a0, a1, a2, a3);
}
void G_glUniformMatrix3fv(CPU *c) { RT_PRIMEIRA("glUniformMatrix3fv");
    static void (*p)(GLint, GLsizei, GLboolean, const GLfloat *); if (!p) p = gl_proc("glUniformMatrix3fv");
    Args a = args_de(c); (void)a;
    GLint a0 = (GLint)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    GLboolean a2 = (GLboolean)arg32(&a);
    const GLfloat * a3 = (const GLfloat *)G2H(arg32(&a));
    p(a0, a1, a2, a3);
}
void G_glUniformMatrix3x2fv(CPU *c) { RT_PRIMEIRA("glUniformMatrix3x2fv");
    static void (*p)(GLint, GLsizei, GLboolean, const GLfloat *); if (!p) p = gl_proc("glUniformMatrix3x2fv");
    Args a = args_de(c); (void)a;
    GLint a0 = (GLint)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    GLboolean a2 = (GLboolean)arg32(&a);
    const GLfloat * a3 = (const GLfloat *)G2H(arg32(&a));
    p(a0, a1, a2, a3);
}
void G_glUniformMatrix3x2fvNV(CPU *c) { RT_PRIMEIRA("glUniformMatrix3x2fvNV");
    static void (*p)(GLint, GLsizei, GLboolean, const GLfloat *); if (!p) p = gl_proc("glUniformMatrix3x2fvNV");
    Args a = args_de(c); (void)a;
    GLint a0 = (GLint)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    GLboolean a2 = (GLboolean)arg32(&a);
    const GLfloat * a3 = (const GLfloat *)G2H(arg32(&a));
    p(a0, a1, a2, a3);
}
void G_glUniformMatrix3x4fv(CPU *c) { RT_PRIMEIRA("glUniformMatrix3x4fv");
    static void (*p)(GLint, GLsizei, GLboolean, const GLfloat *); if (!p) p = gl_proc("glUniformMatrix3x4fv");
    Args a = args_de(c); (void)a;
    GLint a0 = (GLint)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    GLboolean a2 = (GLboolean)arg32(&a);
    const GLfloat * a3 = (const GLfloat *)G2H(arg32(&a));
    p(a0, a1, a2, a3);
}
void G_glUniformMatrix3x4fvNV(CPU *c) { RT_PRIMEIRA("glUniformMatrix3x4fvNV");
    static void (*p)(GLint, GLsizei, GLboolean, const GLfloat *); if (!p) p = gl_proc("glUniformMatrix3x4fvNV");
    Args a = args_de(c); (void)a;
    GLint a0 = (GLint)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    GLboolean a2 = (GLboolean)arg32(&a);
    const GLfloat * a3 = (const GLfloat *)G2H(arg32(&a));
    p(a0, a1, a2, a3);
}
void G_glUniformMatrix4fv(CPU *c) { RT_PRIMEIRA("glUniformMatrix4fv");
    static void (*p)(GLint, GLsizei, GLboolean, const GLfloat *); if (!p) p = gl_proc("glUniformMatrix4fv");
    Args a = args_de(c); (void)a;
    GLint a0 = (GLint)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    GLboolean a2 = (GLboolean)arg32(&a);
    const GLfloat * a3 = (const GLfloat *)G2H(arg32(&a));
    p(a0, a1, a2, a3);
}
void G_glUniformMatrix4x2fv(CPU *c) { RT_PRIMEIRA("glUniformMatrix4x2fv");
    static void (*p)(GLint, GLsizei, GLboolean, const GLfloat *); if (!p) p = gl_proc("glUniformMatrix4x2fv");
    Args a = args_de(c); (void)a;
    GLint a0 = (GLint)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    GLboolean a2 = (GLboolean)arg32(&a);
    const GLfloat * a3 = (const GLfloat *)G2H(arg32(&a));
    p(a0, a1, a2, a3);
}
void G_glUniformMatrix4x2fvNV(CPU *c) { RT_PRIMEIRA("glUniformMatrix4x2fvNV");
    static void (*p)(GLint, GLsizei, GLboolean, const GLfloat *); if (!p) p = gl_proc("glUniformMatrix4x2fvNV");
    Args a = args_de(c); (void)a;
    GLint a0 = (GLint)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    GLboolean a2 = (GLboolean)arg32(&a);
    const GLfloat * a3 = (const GLfloat *)G2H(arg32(&a));
    p(a0, a1, a2, a3);
}
void G_glUniformMatrix4x3fv(CPU *c) { RT_PRIMEIRA("glUniformMatrix4x3fv");
    static void (*p)(GLint, GLsizei, GLboolean, const GLfloat *); if (!p) p = gl_proc("glUniformMatrix4x3fv");
    Args a = args_de(c); (void)a;
    GLint a0 = (GLint)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    GLboolean a2 = (GLboolean)arg32(&a);
    const GLfloat * a3 = (const GLfloat *)G2H(arg32(&a));
    p(a0, a1, a2, a3);
}
void G_glUniformMatrix4x3fvNV(CPU *c) { RT_PRIMEIRA("glUniformMatrix4x3fvNV");
    static void (*p)(GLint, GLsizei, GLboolean, const GLfloat *); if (!p) p = gl_proc("glUniformMatrix4x3fvNV");
    Args a = args_de(c); (void)a;
    GLint a0 = (GLint)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    GLboolean a2 = (GLboolean)arg32(&a);
    const GLfloat * a3 = (const GLfloat *)G2H(arg32(&a));
    p(a0, a1, a2, a3);
}
void G_glUseProgram(CPU *c) { RT_PRIMEIRA("glUseProgram");
    static void (*p)(GLuint); if (!p) p = gl_proc("glUseProgram");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    p(a0);
}
void G_glUseProgramStages(CPU *c) { RT_PRIMEIRA("glUseProgramStages");
    static void (*p)(GLuint, GLbitfield, GLuint); if (!p) p = gl_proc("glUseProgramStages");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLbitfield a1 = (GLbitfield)arg32(&a);
    GLuint a2 = (GLuint)arg32(&a);
    p(a0, a1, a2);
}
void G_glUseProgramStagesEXT(CPU *c) { RT_PRIMEIRA("glUseProgramStagesEXT");
    static void (*p)(GLuint, GLbitfield, GLuint); if (!p) p = gl_proc("glUseProgramStagesEXT");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLbitfield a1 = (GLbitfield)arg32(&a);
    GLuint a2 = (GLuint)arg32(&a);
    p(a0, a1, a2);
}
void G_glValidateProgram(CPU *c) { RT_PRIMEIRA("glValidateProgram");
    static void (*p)(GLuint); if (!p) p = gl_proc("glValidateProgram");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    p(a0);
}
void G_glValidateProgramPipeline(CPU *c) { RT_PRIMEIRA("glValidateProgramPipeline");
    static void (*p)(GLuint); if (!p) p = gl_proc("glValidateProgramPipeline");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    p(a0);
}
void G_glValidateProgramPipelineEXT(CPU *c) { RT_PRIMEIRA("glValidateProgramPipelineEXT");
    static void (*p)(GLuint); if (!p) p = gl_proc("glValidateProgramPipelineEXT");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    p(a0);
}
void G_glVertexAttrib1f(CPU *c) { RT_PRIMEIRA("glVertexAttrib1f");
    static void (*p)(GLuint, GLfloat); if (!p) p = gl_proc("glVertexAttrib1f");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLfloat a1 = argf(&a);
    p(a0, a1);
}
void G_glVertexAttrib1fv(CPU *c) { RT_PRIMEIRA("glVertexAttrib1fv");
    static void (*p)(GLuint, const GLfloat *); if (!p) p = gl_proc("glVertexAttrib1fv");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    const GLfloat * a1 = (const GLfloat *)G2H(arg32(&a));
    p(a0, a1);
}
void G_glVertexAttrib2f(CPU *c) { RT_PRIMEIRA("glVertexAttrib2f");
    static void (*p)(GLuint, GLfloat, GLfloat); if (!p) p = gl_proc("glVertexAttrib2f");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLfloat a1 = argf(&a);
    GLfloat a2 = argf(&a);
    p(a0, a1, a2);
}
void G_glVertexAttrib2fv(CPU *c) { RT_PRIMEIRA("glVertexAttrib2fv");
    static void (*p)(GLuint, const GLfloat *); if (!p) p = gl_proc("glVertexAttrib2fv");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    const GLfloat * a1 = (const GLfloat *)G2H(arg32(&a));
    p(a0, a1);
}
void G_glVertexAttrib3f(CPU *c) { RT_PRIMEIRA("glVertexAttrib3f");
    static void (*p)(GLuint, GLfloat, GLfloat, GLfloat); if (!p) p = gl_proc("glVertexAttrib3f");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLfloat a1 = argf(&a);
    GLfloat a2 = argf(&a);
    GLfloat a3 = argf(&a);
    p(a0, a1, a2, a3);
}
void G_glVertexAttrib3fv(CPU *c) { RT_PRIMEIRA("glVertexAttrib3fv");
    static void (*p)(GLuint, const GLfloat *); if (!p) p = gl_proc("glVertexAttrib3fv");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    const GLfloat * a1 = (const GLfloat *)G2H(arg32(&a));
    p(a0, a1);
}
void G_glVertexAttrib4f(CPU *c) { RT_PRIMEIRA("glVertexAttrib4f");
    static void (*p)(GLuint, GLfloat, GLfloat, GLfloat, GLfloat); if (!p) p = gl_proc("glVertexAttrib4f");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLfloat a1 = argf(&a);
    GLfloat a2 = argf(&a);
    GLfloat a3 = argf(&a);
    GLfloat a4 = argf(&a);
    p(a0, a1, a2, a3, a4);
}
void G_glVertexAttrib4fv(CPU *c) { RT_PRIMEIRA("glVertexAttrib4fv");
    static void (*p)(GLuint, const GLfloat *); if (!p) p = gl_proc("glVertexAttrib4fv");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    const GLfloat * a1 = (const GLfloat *)G2H(arg32(&a));
    p(a0, a1);
}
void G_glVertexAttribBinding(CPU *c) { RT_PRIMEIRA("glVertexAttribBinding");
    static void (*p)(GLuint, GLuint); if (!p) p = gl_proc("glVertexAttribBinding");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLuint a1 = (GLuint)arg32(&a);
#ifdef MGS2_DEPURA
    { static int _n; if (_n++ < 40) rt_log("glVertexAttribBinding(%u -> %u)", a0,a1); }
#endif
    p(a0, a1);
}
void G_glVertexAttribDivisor(CPU *c) { RT_PRIMEIRA("glVertexAttribDivisor");
    static void (*p)(GLuint, GLuint); if (!p) p = gl_proc("glVertexAttribDivisor");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLuint a1 = (GLuint)arg32(&a);
    p(a0, a1);
}
void G_glVertexAttribDivisorANGLE(CPU *c) { RT_PRIMEIRA("glVertexAttribDivisorANGLE");
    static void (*p)(GLuint, GLuint); if (!p) p = gl_proc("glVertexAttribDivisorANGLE");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLuint a1 = (GLuint)arg32(&a);
    p(a0, a1);
}
void G_glVertexAttribDivisorEXT(CPU *c) { RT_PRIMEIRA("glVertexAttribDivisorEXT");
    static void (*p)(GLuint, GLuint); if (!p) p = gl_proc("glVertexAttribDivisorEXT");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLuint a1 = (GLuint)arg32(&a);
    p(a0, a1);
}
void G_glVertexAttribDivisorNV(CPU *c) { RT_PRIMEIRA("glVertexAttribDivisorNV");
    static void (*p)(GLuint, GLuint); if (!p) p = gl_proc("glVertexAttribDivisorNV");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLuint a1 = (GLuint)arg32(&a);
    p(a0, a1);
}
void G_glVertexAttribFormat(CPU *c) { RT_PRIMEIRA("glVertexAttribFormat");
    static void (*p)(GLuint, GLint, GLenum, GLboolean, GLuint); if (!p) p = gl_proc("glVertexAttribFormat");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLenum a2 = (GLenum)arg32(&a);
    GLboolean a3 = (GLboolean)arg32(&a);
    GLuint a4 = (GLuint)arg32(&a);
#ifdef MGS2_DEPURA
    { static int _n; if (_n++ < 40) rt_log("glVertexAttribFormat(%u tam %d tipo %x norm %d rel %u)", a0,a1,a2,a3,a4); }
#endif
    p(a0, a1, a2, a3, a4);
}
void G_glVertexAttribI4i(CPU *c) { RT_PRIMEIRA("glVertexAttribI4i");
    static void (*p)(GLuint, GLint, GLint, GLint, GLint); if (!p) p = gl_proc("glVertexAttribI4i");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLint a2 = (GLint)arg32(&a);
    GLint a3 = (GLint)arg32(&a);
    GLint a4 = (GLint)arg32(&a);
    p(a0, a1, a2, a3, a4);
}
void G_glVertexAttribI4iv(CPU *c) { RT_PRIMEIRA("glVertexAttribI4iv");
    static void (*p)(GLuint, const GLint *); if (!p) p = gl_proc("glVertexAttribI4iv");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    const GLint * a1 = (const GLint *)G2H(arg32(&a));
    p(a0, a1);
}
void G_glVertexAttribI4ui(CPU *c) { RT_PRIMEIRA("glVertexAttribI4ui");
    static void (*p)(GLuint, GLuint, GLuint, GLuint, GLuint); if (!p) p = gl_proc("glVertexAttribI4ui");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLuint a1 = (GLuint)arg32(&a);
    GLuint a2 = (GLuint)arg32(&a);
    GLuint a3 = (GLuint)arg32(&a);
    GLuint a4 = (GLuint)arg32(&a);
    p(a0, a1, a2, a3, a4);
}
void G_glVertexAttribI4uiv(CPU *c) { RT_PRIMEIRA("glVertexAttribI4uiv");
    static void (*p)(GLuint, const GLuint *); if (!p) p = gl_proc("glVertexAttribI4uiv");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    const GLuint * a1 = (const GLuint *)G2H(arg32(&a));
    p(a0, a1);
}
void G_glVertexAttribIFormat(CPU *c) { RT_PRIMEIRA("glVertexAttribIFormat");
    static void (*p)(GLuint, GLint, GLenum, GLuint); if (!p) p = gl_proc("glVertexAttribIFormat");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLenum a2 = (GLenum)arg32(&a);
    GLuint a3 = (GLuint)arg32(&a);
    p(a0, a1, a2, a3);
}
void G_glVertexBindingDivisor(CPU *c) { RT_PRIMEIRA("glVertexBindingDivisor");
    static void (*p)(GLuint, GLuint); if (!p) p = gl_proc("glVertexBindingDivisor");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLuint a1 = (GLuint)arg32(&a);
    p(a0, a1);
}
void G_glViewport(CPU *c) { RT_PRIMEIRA("glViewport");
    static void (*p)(GLint, GLint, GLsizei, GLsizei); if (!p) p = gl_proc("glViewport");
    Args a = args_de(c); (void)a;
    GLint a0 = (GLint)arg32(&a);
    GLint a1 = (GLint)arg32(&a);
    GLsizei a2 = (GLsizei)arg32(&a);
    GLsizei a3 = (GLsizei)arg32(&a);
#ifdef MGS2_DEPURA
    { static int _n; if (_n++ < 40) { GLint _fb = 0; glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &_fb); rt_log("glViewport(%d,%d %dx%d) fbo %d", a0, a1, a2, a3, _fb); } }
#endif
    p(a0, a1, a2, a3);
}
void G_glViewportArrayvNV(CPU *c) { RT_PRIMEIRA("glViewportArrayvNV");
    static void (*p)(GLuint, GLsizei, const GLfloat *); if (!p) p = gl_proc("glViewportArrayvNV");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    const GLfloat * a2 = (const GLfloat *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glViewportArrayvOES(CPU *c) { RT_PRIMEIRA("glViewportArrayvOES");
    static void (*p)(GLuint, GLsizei, const GLfloat *); if (!p) p = gl_proc("glViewportArrayvOES");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    const GLfloat * a2 = (const GLfloat *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glViewportIndexedfNV(CPU *c) { RT_PRIMEIRA("glViewportIndexedfNV");
    static void (*p)(GLuint, GLfloat, GLfloat, GLfloat, GLfloat); if (!p) p = gl_proc("glViewportIndexedfNV");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLfloat a1 = argf(&a);
    GLfloat a2 = argf(&a);
    GLfloat a3 = argf(&a);
    GLfloat a4 = argf(&a);
    p(a0, a1, a2, a3, a4);
}
void G_glViewportIndexedfOES(CPU *c) { RT_PRIMEIRA("glViewportIndexedfOES");
    static void (*p)(GLuint, GLfloat, GLfloat, GLfloat, GLfloat); if (!p) p = gl_proc("glViewportIndexedfOES");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLfloat a1 = argf(&a);
    GLfloat a2 = argf(&a);
    GLfloat a3 = argf(&a);
    GLfloat a4 = argf(&a);
    p(a0, a1, a2, a3, a4);
}
void G_glViewportIndexedfvNV(CPU *c) { RT_PRIMEIRA("glViewportIndexedfvNV");
    static void (*p)(GLuint, const GLfloat *); if (!p) p = gl_proc("glViewportIndexedfvNV");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    const GLfloat * a1 = (const GLfloat *)G2H(arg32(&a));
    p(a0, a1);
}
void G_glViewportIndexedfvOES(CPU *c) { RT_PRIMEIRA("glViewportIndexedfvOES");
    static void (*p)(GLuint, const GLfloat *); if (!p) p = gl_proc("glViewportIndexedfvOES");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    const GLfloat * a1 = (const GLfloat *)G2H(arg32(&a));
    p(a0, a1);
}
void G_glViewportPositionWScaleNV(CPU *c) { RT_PRIMEIRA("glViewportPositionWScaleNV");
    static void (*p)(GLuint, GLfloat, GLfloat); if (!p) p = gl_proc("glViewportPositionWScaleNV");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLfloat a1 = argf(&a);
    GLfloat a2 = argf(&a);
    p(a0, a1, a2);
}
void G_glViewportSwizzleNV(CPU *c) { RT_PRIMEIRA("glViewportSwizzleNV");
    static void (*p)(GLuint, GLenum, GLenum, GLenum, GLenum); if (!p) p = gl_proc("glViewportSwizzleNV");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLenum a1 = (GLenum)arg32(&a);
    GLenum a2 = (GLenum)arg32(&a);
    GLenum a3 = (GLenum)arg32(&a);
    GLenum a4 = (GLenum)arg32(&a);
    p(a0, a1, a2, a3, a4);
}
void G_glWaitSemaphoreEXT(CPU *c) { RT_PRIMEIRA("glWaitSemaphoreEXT");
    static void (*p)(GLuint, GLuint, const GLuint *, GLuint, const GLuint *, const GLenum *); if (!p) p = gl_proc("glWaitSemaphoreEXT");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLuint a1 = (GLuint)arg32(&a);
    const GLuint * a2 = (const GLuint *)G2H(arg32(&a));
    GLuint a3 = (GLuint)arg32(&a);
    const GLuint * a4 = (const GLuint *)G2H(arg32(&a));
    const GLenum * a5 = (const GLenum *)G2H(arg32(&a));
    p(a0, a1, a2, a3, a4, a5);
}
void G_glWaitVkSemaphoreNV(CPU *c) { RT_PRIMEIRA("glWaitVkSemaphoreNV");
    static void (*p)(GLuint64); if (!p) p = gl_proc("glWaitVkSemaphoreNV");
    Args a = args_de(c); (void)a;
    GLuint64 a0 = (GLuint64)arg64(&a);
    p(a0);
}
void G_glWeightPathsNV(CPU *c) { RT_PRIMEIRA("glWeightPathsNV");
    static void (*p)(GLuint, GLsizei, const GLuint *, const GLfloat *); if (!p) p = gl_proc("glWeightPathsNV");
    Args a = args_de(c); (void)a;
    GLuint a0 = (GLuint)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    const GLuint * a2 = (const GLuint *)G2H(arg32(&a));
    const GLfloat * a3 = (const GLfloat *)G2H(arg32(&a));
    p(a0, a1, a2, a3);
}
void G_glWindowRectanglesEXT(CPU *c) { RT_PRIMEIRA("glWindowRectanglesEXT");
    static void (*p)(GLenum, GLsizei, const GLint *); if (!p) p = gl_proc("glWindowRectanglesEXT");
    Args a = args_de(c); (void)a;
    GLenum a0 = (GLenum)arg32(&a);
    GLsizei a1 = (GLsizei)arg32(&a);
    const GLint * a2 = (const GLint *)G2H(arg32(&a));
    p(a0, a1, a2);
}
void G_glBindBuffer(CPU *c);
void G_glBufferStorageEXT(CPU *c);
void G_glClientWaitSync(CPU *c);
void G_glClientWaitSyncAPPLE(CPU *c);
void G_glCompressedTexImage2D(CPU *c);
void G_glCompressedTexImage3D(CPU *c);
void G_glCompressedTexImage3DOES(CPU *c);
void G_glCompressedTexSubImage2D(CPU *c);
void G_glCompressedTexSubImage3D(CPU *c);
void G_glCompressedTexSubImage3DOES(CPU *c);
void G_glDebugMessageCallback(CPU *c);
void G_glDebugMessageCallbackKHR(CPU *c);
void G_glDeleteSync(CPU *c);
void G_glDeleteSyncAPPLE(CPU *c);
void G_glDrawArraysIndirect(CPU *c);
void G_glDrawElements(CPU *c);
void G_glDrawElementsBaseVertex(CPU *c);
void G_glDrawElementsBaseVertexEXT(CPU *c);
void G_glDrawElementsBaseVertexOES(CPU *c);
void G_glDrawElementsIndirect(CPU *c);
void G_glDrawElementsInstanced(CPU *c);
void G_glDrawElementsInstancedANGLE(CPU *c);
void G_glDrawElementsInstancedBaseVertex(CPU *c);
void G_glDrawElementsInstancedBaseVertexEXT(CPU *c);
void G_glDrawElementsInstancedBaseVertexOES(CPU *c);
void G_glDrawElementsInstancedEXT(CPU *c);
void G_glDrawElementsInstancedNV(CPU *c);
void G_glDrawRangeElements(CPU *c);
void G_glDrawRangeElementsBaseVertex(CPU *c);
void G_glDrawRangeElementsBaseVertexEXT(CPU *c);
void G_glDrawRangeElementsBaseVertexOES(CPU *c);
void G_glEGLImageTargetRenderbufferStorageOES(CPU *c);
void G_glEGLImageTargetTexture2DOES(CPU *c);
void G_glFenceSync(CPU *c);
void G_glFenceSyncAPPLE(CPU *c);
void G_glFlushMappedBufferRange(CPU *c);
void G_glFlushMappedBufferRangeEXT(CPU *c);
void G_glGetBufferPointerv(CPU *c);
void G_glGetBufferPointervOES(CPU *c);
void G_glGetPointerv(CPU *c);
void G_glGetPointervKHR(CPU *c);
void G_glGetString(CPU *c);
void G_glGetStringi(CPU *c);
void G_glGetSynciv(CPU *c);
void G_glGetSyncivAPPLE(CPU *c);
void G_glGetUniformIndices(CPU *c);
void G_glGetVertexAttribPointerv(CPU *c);
void G_glIsSync(CPU *c);
void G_glIsSyncAPPLE(CPU *c);
void G_glMapBufferOES(CPU *c);
void G_glMapBufferRange(CPU *c);
void G_glMapBufferRangeEXT(CPU *c);
void G_glMultiDrawElementsBaseVertexEXT(CPU *c);
void G_glMultiDrawElementsEXT(CPU *c);
void G_glReadPixels(CPU *c);
void G_glShaderSource(CPU *c);
void G_glTexImage2D(CPU *c);
void G_glTexImage3D(CPU *c);
void G_glTexImage3DOES(CPU *c);
void G_glTexSubImage2D(CPU *c);
void G_glTexSubImage3D(CPU *c);
void G_glTexSubImage3DOES(CPU *c);
void G_glTransformFeedbackVaryings(CPU *c);
void G_glUnmapBuffer(CPU *c);
void G_glUnmapBufferOES(CPU *c);
void G_glVertexAttribIPointer(CPU *c);
void G_glVertexAttribPointer(CPU *c);
void G_glWaitSync(CPU *c);
void G_glWaitSyncAPPLE(CPU *c);

static const struct { const char *nome; Ponte fn; } tabela_gl[] = {
  {"glAcquireKeyedMutexWin32EXT", G_glAcquireKeyedMutexWin32EXT},
  {"glActiveShaderProgram", G_glActiveShaderProgram},
  {"glActiveShaderProgramEXT", G_glActiveShaderProgramEXT},
  {"glActiveTexture", G_glActiveTexture},
  {"glAlphaFuncQCOM", G_glAlphaFuncQCOM},
  {"glApplyFramebufferAttachmentCMAAINTEL", G_glApplyFramebufferAttachmentCMAAINTEL},
  {"glAttachShader", G_glAttachShader},
  {"glBeginConditionalRenderNV", G_glBeginConditionalRenderNV},
  {"glBeginPerfMonitorAMD", G_glBeginPerfMonitorAMD},
  {"glBeginPerfQueryINTEL", G_glBeginPerfQueryINTEL},
  {"glBeginQuery", G_glBeginQuery},
  {"glBeginQueryEXT", G_glBeginQueryEXT},
  {"glBeginTransformFeedback", G_glBeginTransformFeedback},
  {"glBindAttribLocation", G_glBindAttribLocation},
  {"glBindBuffer", G_glBindBuffer},
  {"glBindBufferBase", G_glBindBufferBase},
  {"glBindBufferRange", G_glBindBufferRange},
  {"glBindFragDataLocationEXT", G_glBindFragDataLocationEXT},
  {"glBindFragDataLocationIndexedEXT", G_glBindFragDataLocationIndexedEXT},
  {"glBindFramebuffer", G_glBindFramebuffer},
  {"glBindImageTexture", G_glBindImageTexture},
  {"glBindProgramPipeline", G_glBindProgramPipeline},
  {"glBindProgramPipelineEXT", G_glBindProgramPipelineEXT},
  {"glBindRenderbuffer", G_glBindRenderbuffer},
  {"glBindSampler", G_glBindSampler},
  {"glBindTexture", G_glBindTexture},
  {"glBindTransformFeedback", G_glBindTransformFeedback},
  {"glBindVertexArray", G_glBindVertexArray},
  {"glBindVertexArrayOES", G_glBindVertexArrayOES},
  {"glBindVertexBuffer", G_glBindVertexBuffer},
  {"glBlendBarrier", G_glBlendBarrier},
  {"glBlendBarrierKHR", G_glBlendBarrierKHR},
  {"glBlendBarrierNV", G_glBlendBarrierNV},
  {"glBlendColor", G_glBlendColor},
  {"glBlendEquation", G_glBlendEquation},
  {"glBlendEquationSeparate", G_glBlendEquationSeparate},
  {"glBlendEquationSeparatei", G_glBlendEquationSeparatei},
  {"glBlendEquationSeparateiEXT", G_glBlendEquationSeparateiEXT},
  {"glBlendEquationSeparateiOES", G_glBlendEquationSeparateiOES},
  {"glBlendEquationi", G_glBlendEquationi},
  {"glBlendEquationiEXT", G_glBlendEquationiEXT},
  {"glBlendEquationiOES", G_glBlendEquationiOES},
  {"glBlendFunc", G_glBlendFunc},
  {"glBlendFuncSeparate", G_glBlendFuncSeparate},
  {"glBlendFuncSeparatei", G_glBlendFuncSeparatei},
  {"glBlendFuncSeparateiEXT", G_glBlendFuncSeparateiEXT},
  {"glBlendFuncSeparateiOES", G_glBlendFuncSeparateiOES},
  {"glBlendFunci", G_glBlendFunci},
  {"glBlendFunciEXT", G_glBlendFunciEXT},
  {"glBlendFunciOES", G_glBlendFunciOES},
  {"glBlendParameteriNV", G_glBlendParameteriNV},
  {"glBlitFramebuffer", G_glBlitFramebuffer},
  {"glBlitFramebufferANGLE", G_glBlitFramebufferANGLE},
  {"glBlitFramebufferNV", G_glBlitFramebufferNV},
  {"glBufferData", G_glBufferData},
  {"glBufferStorageEXT", G_glBufferStorageEXT},
  {"glBufferStorageExternalEXT", G_glBufferStorageExternalEXT},
  {"glBufferStorageMemEXT", G_glBufferStorageMemEXT},
  {"glBufferSubData", G_glBufferSubData},
  {"glCheckFramebufferStatus", G_glCheckFramebufferStatus},
  {"glClear", G_glClear},
  {"glClearBufferfi", G_glClearBufferfi},
  {"glClearBufferfv", G_glClearBufferfv},
  {"glClearBufferiv", G_glClearBufferiv},
  {"glClearBufferuiv", G_glClearBufferuiv},
  {"glClearColor", G_glClearColor},
  {"glClearDepthf", G_glClearDepthf},
  {"glClearPixelLocalStorageuiEXT", G_glClearPixelLocalStorageuiEXT},
  {"glClearStencil", G_glClearStencil},
  {"glClearTexImageEXT", G_glClearTexImageEXT},
  {"glClearTexSubImageEXT", G_glClearTexSubImageEXT},
  {"glClientWaitSync", G_glClientWaitSync},
  {"glClientWaitSyncAPPLE", G_glClientWaitSyncAPPLE},
  {"glClipControlEXT", G_glClipControlEXT},
  {"glColorMask", G_glColorMask},
  {"glColorMaski", G_glColorMaski},
  {"glColorMaskiEXT", G_glColorMaskiEXT},
  {"glColorMaskiOES", G_glColorMaskiOES},
  {"glCompileShader", G_glCompileShader},
  {"glCompressedTexImage2D", G_glCompressedTexImage2D},
  {"glCompressedTexImage3D", G_glCompressedTexImage3D},
  {"glCompressedTexImage3DOES", G_glCompressedTexImage3DOES},
  {"glCompressedTexSubImage2D", G_glCompressedTexSubImage2D},
  {"glCompressedTexSubImage3D", G_glCompressedTexSubImage3D},
  {"glCompressedTexSubImage3DOES", G_glCompressedTexSubImage3DOES},
  {"glConservativeRasterParameteriNV", G_glConservativeRasterParameteriNV},
  {"glCopyBufferSubData", G_glCopyBufferSubData},
  {"glCopyBufferSubDataNV", G_glCopyBufferSubDataNV},
  {"glCopyImageSubData", G_glCopyImageSubData},
  {"glCopyImageSubDataEXT", G_glCopyImageSubDataEXT},
  {"glCopyImageSubDataOES", G_glCopyImageSubDataOES},
  {"glCopyPathNV", G_glCopyPathNV},
  {"glCopyTexImage2D", G_glCopyTexImage2D},
  {"glCopyTexSubImage2D", G_glCopyTexSubImage2D},
  {"glCopyTexSubImage3D", G_glCopyTexSubImage3D},
  {"glCopyTexSubImage3DOES", G_glCopyTexSubImage3DOES},
  {"glCopyTextureLevelsAPPLE", G_glCopyTextureLevelsAPPLE},
  {"glCoverFillPathInstancedNV", G_glCoverFillPathInstancedNV},
  {"glCoverFillPathNV", G_glCoverFillPathNV},
  {"glCoverStrokePathInstancedNV", G_glCoverStrokePathInstancedNV},
  {"glCoverStrokePathNV", G_glCoverStrokePathNV},
  {"glCoverageMaskNV", G_glCoverageMaskNV},
  {"glCoverageModulationNV", G_glCoverageModulationNV},
  {"glCoverageModulationTableNV", G_glCoverageModulationTableNV},
  {"glCoverageOperationNV", G_glCoverageOperationNV},
  {"glCreateMemoryObjectsEXT", G_glCreateMemoryObjectsEXT},
  {"glCreatePerfQueryINTEL", G_glCreatePerfQueryINTEL},
  {"glCreateProgram", G_glCreateProgram},
  {"glCreateShader", G_glCreateShader},
  {"glCreateShaderProgramv", G_glCreateShaderProgramv},
  {"glCreateShaderProgramvEXT", G_glCreateShaderProgramvEXT},
  {"glCullFace", G_glCullFace},
  {"glDebugMessageCallback", G_glDebugMessageCallback},
  {"glDebugMessageCallbackKHR", G_glDebugMessageCallbackKHR},
  {"glDebugMessageControl", G_glDebugMessageControl},
  {"glDebugMessageControlKHR", G_glDebugMessageControlKHR},
  {"glDebugMessageInsert", G_glDebugMessageInsert},
  {"glDebugMessageInsertKHR", G_glDebugMessageInsertKHR},
  {"glDeleteBuffers", G_glDeleteBuffers},
  {"glDeleteFencesNV", G_glDeleteFencesNV},
  {"glDeleteFramebuffers", G_glDeleteFramebuffers},
  {"glDeleteMemoryObjectsEXT", G_glDeleteMemoryObjectsEXT},
  {"glDeletePathsNV", G_glDeletePathsNV},
  {"glDeletePerfMonitorsAMD", G_glDeletePerfMonitorsAMD},
  {"glDeletePerfQueryINTEL", G_glDeletePerfQueryINTEL},
  {"glDeleteProgram", G_glDeleteProgram},
  {"glDeleteProgramPipelines", G_glDeleteProgramPipelines},
  {"glDeleteProgramPipelinesEXT", G_glDeleteProgramPipelinesEXT},
  {"glDeleteQueries", G_glDeleteQueries},
  {"glDeleteQueriesEXT", G_glDeleteQueriesEXT},
  {"glDeleteRenderbuffers", G_glDeleteRenderbuffers},
  {"glDeleteSamplers", G_glDeleteSamplers},
  {"glDeleteSemaphoresEXT", G_glDeleteSemaphoresEXT},
  {"glDeleteShader", G_glDeleteShader},
  {"glDeleteSync", G_glDeleteSync},
  {"glDeleteSyncAPPLE", G_glDeleteSyncAPPLE},
  {"glDeleteTextures", G_glDeleteTextures},
  {"glDeleteTransformFeedbacks", G_glDeleteTransformFeedbacks},
  {"glDeleteVertexArrays", G_glDeleteVertexArrays},
  {"glDeleteVertexArraysOES", G_glDeleteVertexArraysOES},
  {"glDepthFunc", G_glDepthFunc},
  {"glDepthMask", G_glDepthMask},
  {"glDepthRangeArrayfvNV", G_glDepthRangeArrayfvNV},
  {"glDepthRangeArrayfvOES", G_glDepthRangeArrayfvOES},
  {"glDepthRangeIndexedfNV", G_glDepthRangeIndexedfNV},
  {"glDepthRangeIndexedfOES", G_glDepthRangeIndexedfOES},
  {"glDepthRangef", G_glDepthRangef},
  {"glDetachShader", G_glDetachShader},
  {"glDisable", G_glDisable},
  {"glDisableDriverControlQCOM", G_glDisableDriverControlQCOM},
  {"glDisableVertexAttribArray", G_glDisableVertexAttribArray},
  {"glDisablei", G_glDisablei},
  {"glDisableiEXT", G_glDisableiEXT},
  {"glDisableiNV", G_glDisableiNV},
  {"glDisableiOES", G_glDisableiOES},
  {"glDiscardFramebufferEXT", G_glDiscardFramebufferEXT},
  {"glDispatchCompute", G_glDispatchCompute},
  {"glDispatchComputeIndirect", G_glDispatchComputeIndirect},
  {"glDrawArrays", G_glDrawArrays},
  {"glDrawArraysIndirect", G_glDrawArraysIndirect},
  {"glDrawArraysInstanced", G_glDrawArraysInstanced},
  {"glDrawArraysInstancedANGLE", G_glDrawArraysInstancedANGLE},
  {"glDrawArraysInstancedBaseInstanceEXT", G_glDrawArraysInstancedBaseInstanceEXT},
  {"glDrawArraysInstancedEXT", G_glDrawArraysInstancedEXT},
  {"glDrawArraysInstancedNV", G_glDrawArraysInstancedNV},
  {"glDrawBuffers", G_glDrawBuffers},
  {"glDrawBuffersEXT", G_glDrawBuffersEXT},
  {"glDrawBuffersIndexedEXT", G_glDrawBuffersIndexedEXT},
  {"glDrawBuffersNV", G_glDrawBuffersNV},
  {"glDrawElements", G_glDrawElements},
  {"glDrawElementsBaseVertex", G_glDrawElementsBaseVertex},
  {"glDrawElementsBaseVertexEXT", G_glDrawElementsBaseVertexEXT},
  {"glDrawElementsBaseVertexOES", G_glDrawElementsBaseVertexOES},
  {"glDrawElementsIndirect", G_glDrawElementsIndirect},
  {"glDrawElementsInstanced", G_glDrawElementsInstanced},
  {"glDrawElementsInstancedANGLE", G_glDrawElementsInstancedANGLE},
  {"glDrawElementsInstancedBaseInstanceEXT", G_glDrawElementsInstancedBaseInstanceEXT},
  {"glDrawElementsInstancedBaseVertex", G_glDrawElementsInstancedBaseVertex},
  {"glDrawElementsInstancedBaseVertexBaseInstanceEXT", G_glDrawElementsInstancedBaseVertexBaseInstanceEXT},
  {"glDrawElementsInstancedBaseVertexEXT", G_glDrawElementsInstancedBaseVertexEXT},
  {"glDrawElementsInstancedBaseVertexOES", G_glDrawElementsInstancedBaseVertexOES},
  {"glDrawElementsInstancedEXT", G_glDrawElementsInstancedEXT},
  {"glDrawElementsInstancedNV", G_glDrawElementsInstancedNV},
  {"glDrawRangeElements", G_glDrawRangeElements},
  {"glDrawRangeElementsBaseVertex", G_glDrawRangeElementsBaseVertex},
  {"glDrawRangeElementsBaseVertexEXT", G_glDrawRangeElementsBaseVertexEXT},
  {"glDrawRangeElementsBaseVertexOES", G_glDrawRangeElementsBaseVertexOES},
  {"glDrawTransformFeedbackEXT", G_glDrawTransformFeedbackEXT},
  {"glDrawTransformFeedbackInstancedEXT", G_glDrawTransformFeedbackInstancedEXT},
  {"glDrawVkImageNV", G_glDrawVkImageNV},
  {"glEGLImageTargetRenderbufferStorageOES", G_glEGLImageTargetRenderbufferStorageOES},
  {"glEGLImageTargetTexStorageEXT", G_glEGLImageTargetTexStorageEXT},
  {"glEGLImageTargetTexture2DOES", G_glEGLImageTargetTexture2DOES},
  {"glEGLImageTargetTextureStorageEXT", G_glEGLImageTargetTextureStorageEXT},
  {"glEnable", G_glEnable},
  {"glEnableDriverControlQCOM", G_glEnableDriverControlQCOM},
  {"glEnableVertexAttribArray", G_glEnableVertexAttribArray},
  {"glEnablei", G_glEnablei},
  {"glEnableiEXT", G_glEnableiEXT},
  {"glEnableiNV", G_glEnableiNV},
  {"glEnableiOES", G_glEnableiOES},
  {"glEndConditionalRenderNV", G_glEndConditionalRenderNV},
  {"glEndPerfMonitorAMD", G_glEndPerfMonitorAMD},
  {"glEndPerfQueryINTEL", G_glEndPerfQueryINTEL},
  {"glEndQuery", G_glEndQuery},
  {"glEndQueryEXT", G_glEndQueryEXT},
  {"glEndTilingQCOM", G_glEndTilingQCOM},
  {"glEndTransformFeedback", G_glEndTransformFeedback},
  {"glExtGetBufferPointervQCOM", G_glExtGetBufferPointervQCOM},
  {"glExtGetBuffersQCOM", G_glExtGetBuffersQCOM},
  {"glExtGetFramebuffersQCOM", G_glExtGetFramebuffersQCOM},
  {"glExtGetProgramBinarySourceQCOM", G_glExtGetProgramBinarySourceQCOM},
  {"glExtGetProgramsQCOM", G_glExtGetProgramsQCOM},
  {"glExtGetRenderbuffersQCOM", G_glExtGetRenderbuffersQCOM},
  {"glExtGetShadersQCOM", G_glExtGetShadersQCOM},
  {"glExtGetTexLevelParameterivQCOM", G_glExtGetTexLevelParameterivQCOM},
  {"glExtGetTexSubImageQCOM", G_glExtGetTexSubImageQCOM},
  {"glExtGetTexturesQCOM", G_glExtGetTexturesQCOM},
  {"glExtIsProgramBinaryQCOM", G_glExtIsProgramBinaryQCOM},
  {"glExtTexObjectStateOverrideiQCOM", G_glExtTexObjectStateOverrideiQCOM},
  {"glFenceSync", G_glFenceSync},
  {"glFenceSyncAPPLE", G_glFenceSyncAPPLE},
  {"glFinish", G_glFinish},
  {"glFinishFenceNV", G_glFinishFenceNV},
  {"glFlush", G_glFlush},
  {"glFlushMappedBufferRange", G_glFlushMappedBufferRange},
  {"glFlushMappedBufferRangeEXT", G_glFlushMappedBufferRangeEXT},
  {"glFragmentCoverageColorNV", G_glFragmentCoverageColorNV},
  {"glFramebufferFetchBarrierEXT", G_glFramebufferFetchBarrierEXT},
  {"glFramebufferFetchBarrierQCOM", G_glFramebufferFetchBarrierQCOM},
  {"glFramebufferFoveationConfigQCOM", G_glFramebufferFoveationConfigQCOM},
  {"glFramebufferFoveationParametersQCOM", G_glFramebufferFoveationParametersQCOM},
  {"glFramebufferParameteri", G_glFramebufferParameteri},
  {"glFramebufferPixelLocalStorageSizeEXT", G_glFramebufferPixelLocalStorageSizeEXT},
  {"glFramebufferRenderbuffer", G_glFramebufferRenderbuffer},
  {"glFramebufferSampleLocationsfvNV", G_glFramebufferSampleLocationsfvNV},
  {"glFramebufferTexture", G_glFramebufferTexture},
  {"glFramebufferTexture2D", G_glFramebufferTexture2D},
  {"glFramebufferTexture2DDownsampleIMG", G_glFramebufferTexture2DDownsampleIMG},
  {"glFramebufferTexture2DMultisampleEXT", G_glFramebufferTexture2DMultisampleEXT},
  {"glFramebufferTexture2DMultisampleIMG", G_glFramebufferTexture2DMultisampleIMG},
  {"glFramebufferTexture3DOES", G_glFramebufferTexture3DOES},
  {"glFramebufferTextureEXT", G_glFramebufferTextureEXT},
  {"glFramebufferTextureLayer", G_glFramebufferTextureLayer},
  {"glFramebufferTextureLayerDownsampleIMG", G_glFramebufferTextureLayerDownsampleIMG},
  {"glFramebufferTextureMultisampleMultiviewOVR", G_glFramebufferTextureMultisampleMultiviewOVR},
  {"glFramebufferTextureMultiviewOVR", G_glFramebufferTextureMultiviewOVR},
  {"glFramebufferTextureOES", G_glFramebufferTextureOES},
  {"glFrontFace", G_glFrontFace},
  {"glGenBuffers", G_glGenBuffers},
  {"glGenFencesNV", G_glGenFencesNV},
  {"glGenFramebuffers", G_glGenFramebuffers},
  {"glGenPathsNV", G_glGenPathsNV},
  {"glGenPerfMonitorsAMD", G_glGenPerfMonitorsAMD},
  {"glGenProgramPipelines", G_glGenProgramPipelines},
  {"glGenProgramPipelinesEXT", G_glGenProgramPipelinesEXT},
  {"glGenQueries", G_glGenQueries},
  {"glGenQueriesEXT", G_glGenQueriesEXT},
  {"glGenRenderbuffers", G_glGenRenderbuffers},
  {"glGenSamplers", G_glGenSamplers},
  {"glGenSemaphoresEXT", G_glGenSemaphoresEXT},
  {"glGenTextures", G_glGenTextures},
  {"glGenTransformFeedbacks", G_glGenTransformFeedbacks},
  {"glGenVertexArrays", G_glGenVertexArrays},
  {"glGenVertexArraysOES", G_glGenVertexArraysOES},
  {"glGenerateMipmap", G_glGenerateMipmap},
  {"glGetActiveAttrib", G_glGetActiveAttrib},
  {"glGetActiveUniform", G_glGetActiveUniform},
  {"glGetActiveUniformBlockName", G_glGetActiveUniformBlockName},
  {"glGetActiveUniformBlockiv", G_glGetActiveUniformBlockiv},
  {"glGetActiveUniformsiv", G_glGetActiveUniformsiv},
  {"glGetAttachedShaders", G_glGetAttachedShaders},
  {"glGetAttribLocation", G_glGetAttribLocation},
  {"glGetBooleani_v", G_glGetBooleani_v},
  {"glGetBooleanv", G_glGetBooleanv},
  {"glGetBufferParameteri64v", G_glGetBufferParameteri64v},
  {"glGetBufferParameteriv", G_glGetBufferParameteriv},
  {"glGetBufferPointerv", G_glGetBufferPointerv},
  {"glGetBufferPointervOES", G_glGetBufferPointervOES},
  {"glGetCoverageModulationTableNV", G_glGetCoverageModulationTableNV},
  {"glGetDebugMessageLog", G_glGetDebugMessageLog},
  {"glGetDebugMessageLogKHR", G_glGetDebugMessageLogKHR},
  {"glGetDriverControlStringQCOM", G_glGetDriverControlStringQCOM},
  {"glGetDriverControlsQCOM", G_glGetDriverControlsQCOM},
  {"glGetError", G_glGetError},
  {"glGetFenceivNV", G_glGetFenceivNV},
  {"glGetFirstPerfQueryIdINTEL", G_glGetFirstPerfQueryIdINTEL},
  {"glGetFloati_vNV", G_glGetFloati_vNV},
  {"glGetFloati_vOES", G_glGetFloati_vOES},
  {"glGetFloatv", G_glGetFloatv},
  {"glGetFragDataIndexEXT", G_glGetFragDataIndexEXT},
  {"glGetFragDataLocation", G_glGetFragDataLocation},
  {"glGetFramebufferAttachmentParameteriv", G_glGetFramebufferAttachmentParameteriv},
  {"glGetFramebufferParameteriv", G_glGetFramebufferParameteriv},
  {"glGetFramebufferPixelLocalStorageSizeEXT", G_glGetFramebufferPixelLocalStorageSizeEXT},
  {"glGetGraphicsResetStatus", G_glGetGraphicsResetStatus},
  {"glGetGraphicsResetStatusEXT", G_glGetGraphicsResetStatusEXT},
  {"glGetGraphicsResetStatusKHR", G_glGetGraphicsResetStatusKHR},
  {"glGetInteger64i_v", G_glGetInteger64i_v},
  {"glGetInteger64v", G_glGetInteger64v},
  {"glGetInteger64vAPPLE", G_glGetInteger64vAPPLE},
  {"glGetIntegeri_v", G_glGetIntegeri_v},
  {"glGetIntegeri_vEXT", G_glGetIntegeri_vEXT},
  {"glGetIntegerv", G_glGetIntegerv},
  {"glGetInternalformatSampleivNV", G_glGetInternalformatSampleivNV},
  {"glGetInternalformativ", G_glGetInternalformativ},
  {"glGetMemoryObjectParameterivEXT", G_glGetMemoryObjectParameterivEXT},
  {"glGetMultisamplefv", G_glGetMultisamplefv},
  {"glGetNextPerfQueryIdINTEL", G_glGetNextPerfQueryIdINTEL},
  {"glGetObjectLabel", G_glGetObjectLabel},
  {"glGetObjectLabelEXT", G_glGetObjectLabelEXT},
  {"glGetObjectLabelKHR", G_glGetObjectLabelKHR},
  {"glGetObjectPtrLabel", G_glGetObjectPtrLabel},
  {"glGetObjectPtrLabelKHR", G_glGetObjectPtrLabelKHR},
  {"glGetPathCommandsNV", G_glGetPathCommandsNV},
  {"glGetPathCoordsNV", G_glGetPathCoordsNV},
  {"glGetPathDashArrayNV", G_glGetPathDashArrayNV},
  {"glGetPathLengthNV", G_glGetPathLengthNV},
  {"glGetPathMetricRangeNV", G_glGetPathMetricRangeNV},
  {"glGetPathMetricsNV", G_glGetPathMetricsNV},
  {"glGetPathParameterfvNV", G_glGetPathParameterfvNV},
  {"glGetPathParameterivNV", G_glGetPathParameterivNV},
  {"glGetPathSpacingNV", G_glGetPathSpacingNV},
  {"glGetPerfCounterInfoINTEL", G_glGetPerfCounterInfoINTEL},
  {"glGetPerfMonitorCounterDataAMD", G_glGetPerfMonitorCounterDataAMD},
  {"glGetPerfMonitorCounterInfoAMD", G_glGetPerfMonitorCounterInfoAMD},
  {"glGetPerfMonitorCounterStringAMD", G_glGetPerfMonitorCounterStringAMD},
  {"glGetPerfMonitorCountersAMD", G_glGetPerfMonitorCountersAMD},
  {"glGetPerfMonitorGroupStringAMD", G_glGetPerfMonitorGroupStringAMD},
  {"glGetPerfMonitorGroupsAMD", G_glGetPerfMonitorGroupsAMD},
  {"glGetPerfQueryDataINTEL", G_glGetPerfQueryDataINTEL},
  {"glGetPerfQueryIdByNameINTEL", G_glGetPerfQueryIdByNameINTEL},
  {"glGetPerfQueryInfoINTEL", G_glGetPerfQueryInfoINTEL},
  {"glGetPointerv", G_glGetPointerv},
  {"glGetPointervKHR", G_glGetPointervKHR},
  {"glGetProgramBinary", G_glGetProgramBinary},
  {"glGetProgramBinaryOES", G_glGetProgramBinaryOES},
  {"glGetProgramInfoLog", G_glGetProgramInfoLog},
  {"glGetProgramInterfaceiv", G_glGetProgramInterfaceiv},
  {"glGetProgramPipelineInfoLog", G_glGetProgramPipelineInfoLog},
  {"glGetProgramPipelineInfoLogEXT", G_glGetProgramPipelineInfoLogEXT},
  {"glGetProgramPipelineiv", G_glGetProgramPipelineiv},
  {"glGetProgramPipelineivEXT", G_glGetProgramPipelineivEXT},
  {"glGetProgramResourceIndex", G_glGetProgramResourceIndex},
  {"glGetProgramResourceLocation", G_glGetProgramResourceLocation},
  {"glGetProgramResourceLocationIndexEXT", G_glGetProgramResourceLocationIndexEXT},
  {"glGetProgramResourceName", G_glGetProgramResourceName},
  {"glGetProgramResourcefvNV", G_glGetProgramResourcefvNV},
  {"glGetProgramResourceiv", G_glGetProgramResourceiv},
  {"glGetProgramiv", G_glGetProgramiv},
  {"glGetQueryObjecti64vEXT", G_glGetQueryObjecti64vEXT},
  {"glGetQueryObjectivEXT", G_glGetQueryObjectivEXT},
  {"glGetQueryObjectui64vEXT", G_glGetQueryObjectui64vEXT},
  {"glGetQueryObjectuiv", G_glGetQueryObjectuiv},
  {"glGetQueryObjectuivEXT", G_glGetQueryObjectuivEXT},
  {"glGetQueryiv", G_glGetQueryiv},
  {"glGetQueryivEXT", G_glGetQueryivEXT},
  {"glGetRenderbufferParameteriv", G_glGetRenderbufferParameteriv},
  {"glGetSamplerParameterIiv", G_glGetSamplerParameterIiv},
  {"glGetSamplerParameterIivEXT", G_glGetSamplerParameterIivEXT},
  {"glGetSamplerParameterIivOES", G_glGetSamplerParameterIivOES},
  {"glGetSamplerParameterIuiv", G_glGetSamplerParameterIuiv},
  {"glGetSamplerParameterIuivEXT", G_glGetSamplerParameterIuivEXT},
  {"glGetSamplerParameterIuivOES", G_glGetSamplerParameterIuivOES},
  {"glGetSamplerParameterfv", G_glGetSamplerParameterfv},
  {"glGetSamplerParameteriv", G_glGetSamplerParameteriv},
  {"glGetSemaphoreParameterui64vEXT", G_glGetSemaphoreParameterui64vEXT},
  {"glGetShaderInfoLog", G_glGetShaderInfoLog},
  {"glGetShaderPrecisionFormat", G_glGetShaderPrecisionFormat},
  {"glGetShaderSource", G_glGetShaderSource},
  {"glGetShaderiv", G_glGetShaderiv},
  {"glGetString", G_glGetString},
  {"glGetStringi", G_glGetStringi},
  {"glGetSynciv", G_glGetSynciv},
  {"glGetSyncivAPPLE", G_glGetSyncivAPPLE},
  {"glGetTexLevelParameterfv", G_glGetTexLevelParameterfv},
  {"glGetTexLevelParameteriv", G_glGetTexLevelParameteriv},
  {"glGetTexParameterIiv", G_glGetTexParameterIiv},
  {"glGetTexParameterIivEXT", G_glGetTexParameterIivEXT},
  {"glGetTexParameterIivOES", G_glGetTexParameterIivOES},
  {"glGetTexParameterIuiv", G_glGetTexParameterIuiv},
  {"glGetTexParameterIuivEXT", G_glGetTexParameterIuivEXT},
  {"glGetTexParameterIuivOES", G_glGetTexParameterIuivOES},
  {"glGetTexParameterfv", G_glGetTexParameterfv},
  {"glGetTexParameteriv", G_glGetTexParameteriv},
  {"glGetTransformFeedbackVarying", G_glGetTransformFeedbackVarying},
  {"glGetTranslatedShaderSourceANGLE", G_glGetTranslatedShaderSourceANGLE},
  {"glGetUniformBlockIndex", G_glGetUniformBlockIndex},
  {"glGetUniformIndices", G_glGetUniformIndices},
  {"glGetUniformLocation", G_glGetUniformLocation},
  {"glGetUniformfv", G_glGetUniformfv},
  {"glGetUniformi64vNV", G_glGetUniformi64vNV},
  {"glGetUniformiv", G_glGetUniformiv},
  {"glGetUniformuiv", G_glGetUniformuiv},
  {"glGetUnsignedBytei_vEXT", G_glGetUnsignedBytei_vEXT},
  {"glGetUnsignedBytevEXT", G_glGetUnsignedBytevEXT},
  {"glGetVertexAttribIiv", G_glGetVertexAttribIiv},
  {"glGetVertexAttribIuiv", G_glGetVertexAttribIuiv},
  {"glGetVertexAttribPointerv", G_glGetVertexAttribPointerv},
  {"glGetVertexAttribfv", G_glGetVertexAttribfv},
  {"glGetVertexAttribiv", G_glGetVertexAttribiv},
  {"glGetnUniformfv", G_glGetnUniformfv},
  {"glGetnUniformfvEXT", G_glGetnUniformfvEXT},
  {"glGetnUniformfvKHR", G_glGetnUniformfvKHR},
  {"glGetnUniformiv", G_glGetnUniformiv},
  {"glGetnUniformivEXT", G_glGetnUniformivEXT},
  {"glGetnUniformivKHR", G_glGetnUniformivKHR},
  {"glGetnUniformuiv", G_glGetnUniformuiv},
  {"glGetnUniformuivKHR", G_glGetnUniformuivKHR},
  {"glHint", G_glHint},
  {"glImportMemoryFdEXT", G_glImportMemoryFdEXT},
  {"glImportMemoryWin32HandleEXT", G_glImportMemoryWin32HandleEXT},
  {"glImportMemoryWin32NameEXT", G_glImportMemoryWin32NameEXT},
  {"glImportSemaphoreFdEXT", G_glImportSemaphoreFdEXT},
  {"glImportSemaphoreWin32HandleEXT", G_glImportSemaphoreWin32HandleEXT},
  {"glImportSemaphoreWin32NameEXT", G_glImportSemaphoreWin32NameEXT},
  {"glInsertEventMarkerEXT", G_glInsertEventMarkerEXT},
  {"glInterpolatePathsNV", G_glInterpolatePathsNV},
  {"glInvalidateFramebuffer", G_glInvalidateFramebuffer},
  {"glInvalidateSubFramebuffer", G_glInvalidateSubFramebuffer},
  {"glIsBuffer", G_glIsBuffer},
  {"glIsEnabled", G_glIsEnabled},
  {"glIsEnabledi", G_glIsEnabledi},
  {"glIsEnablediEXT", G_glIsEnablediEXT},
  {"glIsEnablediNV", G_glIsEnablediNV},
  {"glIsEnablediOES", G_glIsEnablediOES},
  {"glIsFenceNV", G_glIsFenceNV},
  {"glIsFramebuffer", G_glIsFramebuffer},
  {"glIsImageHandleResidentNV", G_glIsImageHandleResidentNV},
  {"glIsMemoryObjectEXT", G_glIsMemoryObjectEXT},
  {"glIsPathNV", G_glIsPathNV},
  {"glIsPointInFillPathNV", G_glIsPointInFillPathNV},
  {"glIsPointInStrokePathNV", G_glIsPointInStrokePathNV},
  {"glIsProgram", G_glIsProgram},
  {"glIsProgramPipeline", G_glIsProgramPipeline},
  {"glIsProgramPipelineEXT", G_glIsProgramPipelineEXT},
  {"glIsQuery", G_glIsQuery},
  {"glIsQueryEXT", G_glIsQueryEXT},
  {"glIsRenderbuffer", G_glIsRenderbuffer},
  {"glIsSampler", G_glIsSampler},
  {"glIsSemaphoreEXT", G_glIsSemaphoreEXT},
  {"glIsShader", G_glIsShader},
  {"glIsSync", G_glIsSync},
  {"glIsSyncAPPLE", G_glIsSyncAPPLE},
  {"glIsTexture", G_glIsTexture},
  {"glIsTextureHandleResidentNV", G_glIsTextureHandleResidentNV},
  {"glIsTransformFeedback", G_glIsTransformFeedback},
  {"glIsVertexArray", G_glIsVertexArray},
  {"glIsVertexArrayOES", G_glIsVertexArrayOES},
  {"glLabelObjectEXT", G_glLabelObjectEXT},
  {"glLineWidth", G_glLineWidth},
  {"glLinkProgram", G_glLinkProgram},
  {"glMakeImageHandleNonResidentNV", G_glMakeImageHandleNonResidentNV},
  {"glMakeImageHandleResidentNV", G_glMakeImageHandleResidentNV},
  {"glMakeTextureHandleNonResidentNV", G_glMakeTextureHandleNonResidentNV},
  {"glMakeTextureHandleResidentNV", G_glMakeTextureHandleResidentNV},
  {"glMapBufferOES", G_glMapBufferOES},
  {"glMapBufferRange", G_glMapBufferRange},
  {"glMapBufferRangeEXT", G_glMapBufferRangeEXT},
  {"glMatrixFrustumEXT", G_glMatrixFrustumEXT},
  {"glMatrixLoad3x2fNV", G_glMatrixLoad3x2fNV},
  {"glMatrixLoad3x3fNV", G_glMatrixLoad3x3fNV},
  {"glMatrixLoadIdentityEXT", G_glMatrixLoadIdentityEXT},
  {"glMatrixLoadTranspose3x3fNV", G_glMatrixLoadTranspose3x3fNV},
  {"glMatrixLoadTransposedEXT", G_glMatrixLoadTransposedEXT},
  {"glMatrixLoadTransposefEXT", G_glMatrixLoadTransposefEXT},
  {"glMatrixLoaddEXT", G_glMatrixLoaddEXT},
  {"glMatrixLoadfEXT", G_glMatrixLoadfEXT},
  {"glMatrixMult3x2fNV", G_glMatrixMult3x2fNV},
  {"glMatrixMult3x3fNV", G_glMatrixMult3x3fNV},
  {"glMatrixMultTranspose3x3fNV", G_glMatrixMultTranspose3x3fNV},
  {"glMatrixMultTransposedEXT", G_glMatrixMultTransposedEXT},
  {"glMatrixMultTransposefEXT", G_glMatrixMultTransposefEXT},
  {"glMatrixMultdEXT", G_glMatrixMultdEXT},
  {"glMatrixMultfEXT", G_glMatrixMultfEXT},
  {"glMatrixOrthoEXT", G_glMatrixOrthoEXT},
  {"glMatrixPopEXT", G_glMatrixPopEXT},
  {"glMatrixPushEXT", G_glMatrixPushEXT},
  {"glMatrixRotatedEXT", G_glMatrixRotatedEXT},
  {"glMatrixRotatefEXT", G_glMatrixRotatefEXT},
  {"glMatrixScaledEXT", G_glMatrixScaledEXT},
  {"glMatrixScalefEXT", G_glMatrixScalefEXT},
  {"glMatrixTranslatedEXT", G_glMatrixTranslatedEXT},
  {"glMatrixTranslatefEXT", G_glMatrixTranslatefEXT},
  {"glMaxShaderCompilerThreadsKHR", G_glMaxShaderCompilerThreadsKHR},
  {"glMemoryBarrier", G_glMemoryBarrier},
  {"glMemoryBarrierByRegion", G_glMemoryBarrierByRegion},
  {"glMemoryObjectParameterivEXT", G_glMemoryObjectParameterivEXT},
  {"glMinSampleShading", G_glMinSampleShading},
  {"glMinSampleShadingOES", G_glMinSampleShadingOES},
  {"glMultiDrawArraysEXT", G_glMultiDrawArraysEXT},
  {"glMultiDrawArraysIndirectEXT", G_glMultiDrawArraysIndirectEXT},
  {"glMultiDrawElementsBaseVertexEXT", G_glMultiDrawElementsBaseVertexEXT},
  {"glMultiDrawElementsEXT", G_glMultiDrawElementsEXT},
  {"glMultiDrawElementsIndirectEXT", G_glMultiDrawElementsIndirectEXT},
  {"glNamedBufferStorageExternalEXT", G_glNamedBufferStorageExternalEXT},
  {"glNamedBufferStorageMemEXT", G_glNamedBufferStorageMemEXT},
  {"glNamedFramebufferSampleLocationsfvNV", G_glNamedFramebufferSampleLocationsfvNV},
  {"glObjectLabel", G_glObjectLabel},
  {"glObjectLabelKHR", G_glObjectLabelKHR},
  {"glObjectPtrLabel", G_glObjectPtrLabel},
  {"glObjectPtrLabelKHR", G_glObjectPtrLabelKHR},
  {"glPatchParameteri", G_glPatchParameteri},
  {"glPatchParameteriEXT", G_glPatchParameteriEXT},
  {"glPatchParameteriOES", G_glPatchParameteriOES},
  {"glPathCommandsNV", G_glPathCommandsNV},
  {"glPathCoordsNV", G_glPathCoordsNV},
  {"glPathCoverDepthFuncNV", G_glPathCoverDepthFuncNV},
  {"glPathDashArrayNV", G_glPathDashArrayNV},
  {"glPathGlyphIndexArrayNV", G_glPathGlyphIndexArrayNV},
  {"glPathGlyphIndexRangeNV", G_glPathGlyphIndexRangeNV},
  {"glPathGlyphRangeNV", G_glPathGlyphRangeNV},
  {"glPathGlyphsNV", G_glPathGlyphsNV},
  {"glPathMemoryGlyphIndexArrayNV", G_glPathMemoryGlyphIndexArrayNV},
  {"glPathParameterfNV", G_glPathParameterfNV},
  {"glPathParameterfvNV", G_glPathParameterfvNV},
  {"glPathParameteriNV", G_glPathParameteriNV},
  {"glPathParameterivNV", G_glPathParameterivNV},
  {"glPathStencilDepthOffsetNV", G_glPathStencilDepthOffsetNV},
  {"glPathStencilFuncNV", G_glPathStencilFuncNV},
  {"glPathStringNV", G_glPathStringNV},
  {"glPathSubCommandsNV", G_glPathSubCommandsNV},
  {"glPathSubCoordsNV", G_glPathSubCoordsNV},
  {"glPauseTransformFeedback", G_glPauseTransformFeedback},
  {"glPixelStorei", G_glPixelStorei},
  {"glPointAlongPathNV", G_glPointAlongPathNV},
  {"glPolygonModeNV", G_glPolygonModeNV},
  {"glPolygonOffset", G_glPolygonOffset},
  {"glPolygonOffsetClampEXT", G_glPolygonOffsetClampEXT},
  {"glPopDebugGroup", G_glPopDebugGroup},
  {"glPopDebugGroupKHR", G_glPopDebugGroupKHR},
  {"glPopGroupMarkerEXT", G_glPopGroupMarkerEXT},
  {"glPrimitiveBoundingBox", G_glPrimitiveBoundingBox},
  {"glPrimitiveBoundingBoxEXT", G_glPrimitiveBoundingBoxEXT},
  {"glPrimitiveBoundingBoxOES", G_glPrimitiveBoundingBoxOES},
  {"glProgramBinary", G_glProgramBinary},
  {"glProgramBinaryOES", G_glProgramBinaryOES},
  {"glProgramParameteri", G_glProgramParameteri},
  {"glProgramParameteriEXT", G_glProgramParameteriEXT},
  {"glProgramPathFragmentInputGenNV", G_glProgramPathFragmentInputGenNV},
  {"glProgramUniform1f", G_glProgramUniform1f},
  {"glProgramUniform1fEXT", G_glProgramUniform1fEXT},
  {"glProgramUniform1fv", G_glProgramUniform1fv},
  {"glProgramUniform1fvEXT", G_glProgramUniform1fvEXT},
  {"glProgramUniform1i", G_glProgramUniform1i},
  {"glProgramUniform1i64NV", G_glProgramUniform1i64NV},
  {"glProgramUniform1i64vNV", G_glProgramUniform1i64vNV},
  {"glProgramUniform1iEXT", G_glProgramUniform1iEXT},
  {"glProgramUniform1iv", G_glProgramUniform1iv},
  {"glProgramUniform1ivEXT", G_glProgramUniform1ivEXT},
  {"glProgramUniform1ui", G_glProgramUniform1ui},
  {"glProgramUniform1ui64NV", G_glProgramUniform1ui64NV},
  {"glProgramUniform1ui64vNV", G_glProgramUniform1ui64vNV},
  {"glProgramUniform1uiEXT", G_glProgramUniform1uiEXT},
  {"glProgramUniform1uiv", G_glProgramUniform1uiv},
  {"glProgramUniform1uivEXT", G_glProgramUniform1uivEXT},
  {"glProgramUniform2f", G_glProgramUniform2f},
  {"glProgramUniform2fEXT", G_glProgramUniform2fEXT},
  {"glProgramUniform2fv", G_glProgramUniform2fv},
  {"glProgramUniform2fvEXT", G_glProgramUniform2fvEXT},
  {"glProgramUniform2i", G_glProgramUniform2i},
  {"glProgramUniform2i64NV", G_glProgramUniform2i64NV},
  {"glProgramUniform2i64vNV", G_glProgramUniform2i64vNV},
  {"glProgramUniform2iEXT", G_glProgramUniform2iEXT},
  {"glProgramUniform2iv", G_glProgramUniform2iv},
  {"glProgramUniform2ivEXT", G_glProgramUniform2ivEXT},
  {"glProgramUniform2ui", G_glProgramUniform2ui},
  {"glProgramUniform2ui64NV", G_glProgramUniform2ui64NV},
  {"glProgramUniform2ui64vNV", G_glProgramUniform2ui64vNV},
  {"glProgramUniform2uiEXT", G_glProgramUniform2uiEXT},
  {"glProgramUniform2uiv", G_glProgramUniform2uiv},
  {"glProgramUniform2uivEXT", G_glProgramUniform2uivEXT},
  {"glProgramUniform3f", G_glProgramUniform3f},
  {"glProgramUniform3fEXT", G_glProgramUniform3fEXT},
  {"glProgramUniform3fv", G_glProgramUniform3fv},
  {"glProgramUniform3fvEXT", G_glProgramUniform3fvEXT},
  {"glProgramUniform3i", G_glProgramUniform3i},
  {"glProgramUniform3i64NV", G_glProgramUniform3i64NV},
  {"glProgramUniform3i64vNV", G_glProgramUniform3i64vNV},
  {"glProgramUniform3iEXT", G_glProgramUniform3iEXT},
  {"glProgramUniform3iv", G_glProgramUniform3iv},
  {"glProgramUniform3ivEXT", G_glProgramUniform3ivEXT},
  {"glProgramUniform3ui", G_glProgramUniform3ui},
  {"glProgramUniform3ui64NV", G_glProgramUniform3ui64NV},
  {"glProgramUniform3ui64vNV", G_glProgramUniform3ui64vNV},
  {"glProgramUniform3uiEXT", G_glProgramUniform3uiEXT},
  {"glProgramUniform3uiv", G_glProgramUniform3uiv},
  {"glProgramUniform3uivEXT", G_glProgramUniform3uivEXT},
  {"glProgramUniform4f", G_glProgramUniform4f},
  {"glProgramUniform4fEXT", G_glProgramUniform4fEXT},
  {"glProgramUniform4fv", G_glProgramUniform4fv},
  {"glProgramUniform4fvEXT", G_glProgramUniform4fvEXT},
  {"glProgramUniform4i", G_glProgramUniform4i},
  {"glProgramUniform4i64NV", G_glProgramUniform4i64NV},
  {"glProgramUniform4i64vNV", G_glProgramUniform4i64vNV},
  {"glProgramUniform4iEXT", G_glProgramUniform4iEXT},
  {"glProgramUniform4iv", G_glProgramUniform4iv},
  {"glProgramUniform4ivEXT", G_glProgramUniform4ivEXT},
  {"glProgramUniform4ui", G_glProgramUniform4ui},
  {"glProgramUniform4ui64NV", G_glProgramUniform4ui64NV},
  {"glProgramUniform4ui64vNV", G_glProgramUniform4ui64vNV},
  {"glProgramUniform4uiEXT", G_glProgramUniform4uiEXT},
  {"glProgramUniform4uiv", G_glProgramUniform4uiv},
  {"glProgramUniform4uivEXT", G_glProgramUniform4uivEXT},
  {"glProgramUniformHandleui64IMG", G_glProgramUniformHandleui64IMG},
  {"glProgramUniformHandleui64NV", G_glProgramUniformHandleui64NV},
  {"glProgramUniformHandleui64vIMG", G_glProgramUniformHandleui64vIMG},
  {"glProgramUniformHandleui64vNV", G_glProgramUniformHandleui64vNV},
  {"glProgramUniformMatrix2fv", G_glProgramUniformMatrix2fv},
  {"glProgramUniformMatrix2fvEXT", G_glProgramUniformMatrix2fvEXT},
  {"glProgramUniformMatrix2x3fv", G_glProgramUniformMatrix2x3fv},
  {"glProgramUniformMatrix2x3fvEXT", G_glProgramUniformMatrix2x3fvEXT},
  {"glProgramUniformMatrix2x4fv", G_glProgramUniformMatrix2x4fv},
  {"glProgramUniformMatrix2x4fvEXT", G_glProgramUniformMatrix2x4fvEXT},
  {"glProgramUniformMatrix3fv", G_glProgramUniformMatrix3fv},
  {"glProgramUniformMatrix3fvEXT", G_glProgramUniformMatrix3fvEXT},
  {"glProgramUniformMatrix3x2fv", G_glProgramUniformMatrix3x2fv},
  {"glProgramUniformMatrix3x2fvEXT", G_glProgramUniformMatrix3x2fvEXT},
  {"glProgramUniformMatrix3x4fv", G_glProgramUniformMatrix3x4fv},
  {"glProgramUniformMatrix3x4fvEXT", G_glProgramUniformMatrix3x4fvEXT},
  {"glProgramUniformMatrix4fv", G_glProgramUniformMatrix4fv},
  {"glProgramUniformMatrix4fvEXT", G_glProgramUniformMatrix4fvEXT},
  {"glProgramUniformMatrix4x2fv", G_glProgramUniformMatrix4x2fv},
  {"glProgramUniformMatrix4x2fvEXT", G_glProgramUniformMatrix4x2fvEXT},
  {"glProgramUniformMatrix4x3fv", G_glProgramUniformMatrix4x3fv},
  {"glProgramUniformMatrix4x3fvEXT", G_glProgramUniformMatrix4x3fvEXT},
  {"glPushDebugGroup", G_glPushDebugGroup},
  {"glPushDebugGroupKHR", G_glPushDebugGroupKHR},
  {"glPushGroupMarkerEXT", G_glPushGroupMarkerEXT},
  {"glQueryCounterEXT", G_glQueryCounterEXT},
  {"glRasterSamplesEXT", G_glRasterSamplesEXT},
  {"glReadBuffer", G_glReadBuffer},
  {"glReadBufferIndexedEXT", G_glReadBufferIndexedEXT},
  {"glReadBufferNV", G_glReadBufferNV},
  {"glReadPixels", G_glReadPixels},
  {"glReadnPixels", G_glReadnPixels},
  {"glReadnPixelsEXT", G_glReadnPixelsEXT},
  {"glReadnPixelsKHR", G_glReadnPixelsKHR},
  {"glReleaseKeyedMutexWin32EXT", G_glReleaseKeyedMutexWin32EXT},
  {"glReleaseShaderCompiler", G_glReleaseShaderCompiler},
  {"glRenderbufferStorage", G_glRenderbufferStorage},
  {"glRenderbufferStorageMultisample", G_glRenderbufferStorageMultisample},
  {"glRenderbufferStorageMultisampleANGLE", G_glRenderbufferStorageMultisampleANGLE},
  {"glRenderbufferStorageMultisampleAPPLE", G_glRenderbufferStorageMultisampleAPPLE},
  {"glRenderbufferStorageMultisampleEXT", G_glRenderbufferStorageMultisampleEXT},
  {"glRenderbufferStorageMultisampleIMG", G_glRenderbufferStorageMultisampleIMG},
  {"glRenderbufferStorageMultisampleNV", G_glRenderbufferStorageMultisampleNV},
  {"glResolveDepthValuesNV", G_glResolveDepthValuesNV},
  {"glResolveMultisampleFramebufferAPPLE", G_glResolveMultisampleFramebufferAPPLE},
  {"glResumeTransformFeedback", G_glResumeTransformFeedback},
  {"glSampleCoverage", G_glSampleCoverage},
  {"glSampleMaski", G_glSampleMaski},
  {"glSamplerParameterIiv", G_glSamplerParameterIiv},
  {"glSamplerParameterIivEXT", G_glSamplerParameterIivEXT},
  {"glSamplerParameterIivOES", G_glSamplerParameterIivOES},
  {"glSamplerParameterIuiv", G_glSamplerParameterIuiv},
  {"glSamplerParameterIuivEXT", G_glSamplerParameterIuivEXT},
  {"glSamplerParameterIuivOES", G_glSamplerParameterIuivOES},
  {"glSamplerParameterf", G_glSamplerParameterf},
  {"glSamplerParameterfv", G_glSamplerParameterfv},
  {"glSamplerParameteri", G_glSamplerParameteri},
  {"glSamplerParameteriv", G_glSamplerParameteriv},
  {"glScissor", G_glScissor},
  {"glScissorArrayvNV", G_glScissorArrayvNV},
  {"glScissorArrayvOES", G_glScissorArrayvOES},
  {"glScissorIndexedNV", G_glScissorIndexedNV},
  {"glScissorIndexedOES", G_glScissorIndexedOES},
  {"glScissorIndexedvNV", G_glScissorIndexedvNV},
  {"glScissorIndexedvOES", G_glScissorIndexedvOES},
  {"glSelectPerfMonitorCountersAMD", G_glSelectPerfMonitorCountersAMD},
  {"glSemaphoreParameterui64vEXT", G_glSemaphoreParameterui64vEXT},
  {"glSetFenceNV", G_glSetFenceNV},
  {"glShaderBinary", G_glShaderBinary},
  {"glShaderSource", G_glShaderSource},
  {"glSignalSemaphoreEXT", G_glSignalSemaphoreEXT},
  {"glSignalVkFenceNV", G_glSignalVkFenceNV},
  {"glSignalVkSemaphoreNV", G_glSignalVkSemaphoreNV},
  {"glStartTilingQCOM", G_glStartTilingQCOM},
  {"glStencilFillPathInstancedNV", G_glStencilFillPathInstancedNV},
  {"glStencilFillPathNV", G_glStencilFillPathNV},
  {"glStencilFunc", G_glStencilFunc},
  {"glStencilFuncSeparate", G_glStencilFuncSeparate},
  {"glStencilMask", G_glStencilMask},
  {"glStencilMaskSeparate", G_glStencilMaskSeparate},
  {"glStencilOp", G_glStencilOp},
  {"glStencilOpSeparate", G_glStencilOpSeparate},
  {"glStencilStrokePathInstancedNV", G_glStencilStrokePathInstancedNV},
  {"glStencilStrokePathNV", G_glStencilStrokePathNV},
  {"glStencilThenCoverFillPathInstancedNV", G_glStencilThenCoverFillPathInstancedNV},
  {"glStencilThenCoverFillPathNV", G_glStencilThenCoverFillPathNV},
  {"glStencilThenCoverStrokePathInstancedNV", G_glStencilThenCoverStrokePathInstancedNV},
  {"glStencilThenCoverStrokePathNV", G_glStencilThenCoverStrokePathNV},
  {"glSubpixelPrecisionBiasNV", G_glSubpixelPrecisionBiasNV},
  {"glTestFenceNV", G_glTestFenceNV},
  {"glTexBuffer", G_glTexBuffer},
  {"glTexBufferEXT", G_glTexBufferEXT},
  {"glTexBufferOES", G_glTexBufferOES},
  {"glTexBufferRange", G_glTexBufferRange},
  {"glTexBufferRangeEXT", G_glTexBufferRangeEXT},
  {"glTexBufferRangeOES", G_glTexBufferRangeOES},
  {"glTexImage2D", G_glTexImage2D},
  {"glTexImage3D", G_glTexImage3D},
  {"glTexImage3DOES", G_glTexImage3DOES},
  {"glTexPageCommitmentEXT", G_glTexPageCommitmentEXT},
  {"glTexParameterIiv", G_glTexParameterIiv},
  {"glTexParameterIivEXT", G_glTexParameterIivEXT},
  {"glTexParameterIivOES", G_glTexParameterIivOES},
  {"glTexParameterIuiv", G_glTexParameterIuiv},
  {"glTexParameterIuivEXT", G_glTexParameterIuivEXT},
  {"glTexParameterIuivOES", G_glTexParameterIuivOES},
  {"glTexParameterf", G_glTexParameterf},
  {"glTexParameterfv", G_glTexParameterfv},
  {"glTexParameteri", G_glTexParameteri},
  {"glTexParameteriv", G_glTexParameteriv},
  {"glTexStorage1DEXT", G_glTexStorage1DEXT},
  {"glTexStorage2D", G_glTexStorage2D},
  {"glTexStorage2DEXT", G_glTexStorage2DEXT},
  {"glTexStorage2DMultisample", G_glTexStorage2DMultisample},
  {"glTexStorage3D", G_glTexStorage3D},
  {"glTexStorage3DEXT", G_glTexStorage3DEXT},
  {"glTexStorage3DMultisample", G_glTexStorage3DMultisample},
  {"glTexStorage3DMultisampleOES", G_glTexStorage3DMultisampleOES},
  {"glTexStorageMem2DEXT", G_glTexStorageMem2DEXT},
  {"glTexStorageMem2DMultisampleEXT", G_glTexStorageMem2DMultisampleEXT},
  {"glTexStorageMem3DEXT", G_glTexStorageMem3DEXT},
  {"glTexStorageMem3DMultisampleEXT", G_glTexStorageMem3DMultisampleEXT},
  {"glTexSubImage2D", G_glTexSubImage2D},
  {"glTexSubImage3D", G_glTexSubImage3D},
  {"glTexSubImage3DOES", G_glTexSubImage3DOES},
  {"glTextureFoveationParametersQCOM", G_glTextureFoveationParametersQCOM},
  {"glTextureStorage1DEXT", G_glTextureStorage1DEXT},
  {"glTextureStorage2DEXT", G_glTextureStorage2DEXT},
  {"glTextureStorage3DEXT", G_glTextureStorage3DEXT},
  {"glTextureStorageMem2DEXT", G_glTextureStorageMem2DEXT},
  {"glTextureStorageMem2DMultisampleEXT", G_glTextureStorageMem2DMultisampleEXT},
  {"glTextureStorageMem3DEXT", G_glTextureStorageMem3DEXT},
  {"glTextureStorageMem3DMultisampleEXT", G_glTextureStorageMem3DMultisampleEXT},
  {"glTextureViewEXT", G_glTextureViewEXT},
  {"glTextureViewOES", G_glTextureViewOES},
  {"glTransformFeedbackVaryings", G_glTransformFeedbackVaryings},
  {"glTransformPathNV", G_glTransformPathNV},
  {"glUniform1f", G_glUniform1f},
  {"glUniform1fv", G_glUniform1fv},
  {"glUniform1i", G_glUniform1i},
  {"glUniform1i64NV", G_glUniform1i64NV},
  {"glUniform1i64vNV", G_glUniform1i64vNV},
  {"glUniform1iv", G_glUniform1iv},
  {"glUniform1ui", G_glUniform1ui},
  {"glUniform1ui64NV", G_glUniform1ui64NV},
  {"glUniform1ui64vNV", G_glUniform1ui64vNV},
  {"glUniform1uiv", G_glUniform1uiv},
  {"glUniform2f", G_glUniform2f},
  {"glUniform2fv", G_glUniform2fv},
  {"glUniform2i", G_glUniform2i},
  {"glUniform2i64NV", G_glUniform2i64NV},
  {"glUniform2i64vNV", G_glUniform2i64vNV},
  {"glUniform2iv", G_glUniform2iv},
  {"glUniform2ui", G_glUniform2ui},
  {"glUniform2ui64NV", G_glUniform2ui64NV},
  {"glUniform2ui64vNV", G_glUniform2ui64vNV},
  {"glUniform2uiv", G_glUniform2uiv},
  {"glUniform3f", G_glUniform3f},
  {"glUniform3fv", G_glUniform3fv},
  {"glUniform3i", G_glUniform3i},
  {"glUniform3i64NV", G_glUniform3i64NV},
  {"glUniform3i64vNV", G_glUniform3i64vNV},
  {"glUniform3iv", G_glUniform3iv},
  {"glUniform3ui", G_glUniform3ui},
  {"glUniform3ui64NV", G_glUniform3ui64NV},
  {"glUniform3ui64vNV", G_glUniform3ui64vNV},
  {"glUniform3uiv", G_glUniform3uiv},
  {"glUniform4f", G_glUniform4f},
  {"glUniform4fv", G_glUniform4fv},
  {"glUniform4i", G_glUniform4i},
  {"glUniform4i64NV", G_glUniform4i64NV},
  {"glUniform4i64vNV", G_glUniform4i64vNV},
  {"glUniform4iv", G_glUniform4iv},
  {"glUniform4ui", G_glUniform4ui},
  {"glUniform4ui64NV", G_glUniform4ui64NV},
  {"glUniform4ui64vNV", G_glUniform4ui64vNV},
  {"glUniform4uiv", G_glUniform4uiv},
  {"glUniformBlockBinding", G_glUniformBlockBinding},
  {"glUniformHandleui64IMG", G_glUniformHandleui64IMG},
  {"glUniformHandleui64NV", G_glUniformHandleui64NV},
  {"glUniformHandleui64vIMG", G_glUniformHandleui64vIMG},
  {"glUniformHandleui64vNV", G_glUniformHandleui64vNV},
  {"glUniformMatrix2fv", G_glUniformMatrix2fv},
  {"glUniformMatrix2x3fv", G_glUniformMatrix2x3fv},
  {"glUniformMatrix2x3fvNV", G_glUniformMatrix2x3fvNV},
  {"glUniformMatrix2x4fv", G_glUniformMatrix2x4fv},
  {"glUniformMatrix2x4fvNV", G_glUniformMatrix2x4fvNV},
  {"glUniformMatrix3fv", G_glUniformMatrix3fv},
  {"glUniformMatrix3x2fv", G_glUniformMatrix3x2fv},
  {"glUniformMatrix3x2fvNV", G_glUniformMatrix3x2fvNV},
  {"glUniformMatrix3x4fv", G_glUniformMatrix3x4fv},
  {"glUniformMatrix3x4fvNV", G_glUniformMatrix3x4fvNV},
  {"glUniformMatrix4fv", G_glUniformMatrix4fv},
  {"glUniformMatrix4x2fv", G_glUniformMatrix4x2fv},
  {"glUniformMatrix4x2fvNV", G_glUniformMatrix4x2fvNV},
  {"glUniformMatrix4x3fv", G_glUniformMatrix4x3fv},
  {"glUniformMatrix4x3fvNV", G_glUniformMatrix4x3fvNV},
  {"glUnmapBuffer", G_glUnmapBuffer},
  {"glUnmapBufferOES", G_glUnmapBufferOES},
  {"glUseProgram", G_glUseProgram},
  {"glUseProgramStages", G_glUseProgramStages},
  {"glUseProgramStagesEXT", G_glUseProgramStagesEXT},
  {"glValidateProgram", G_glValidateProgram},
  {"glValidateProgramPipeline", G_glValidateProgramPipeline},
  {"glValidateProgramPipelineEXT", G_glValidateProgramPipelineEXT},
  {"glVertexAttrib1f", G_glVertexAttrib1f},
  {"glVertexAttrib1fv", G_glVertexAttrib1fv},
  {"glVertexAttrib2f", G_glVertexAttrib2f},
  {"glVertexAttrib2fv", G_glVertexAttrib2fv},
  {"glVertexAttrib3f", G_glVertexAttrib3f},
  {"glVertexAttrib3fv", G_glVertexAttrib3fv},
  {"glVertexAttrib4f", G_glVertexAttrib4f},
  {"glVertexAttrib4fv", G_glVertexAttrib4fv},
  {"glVertexAttribBinding", G_glVertexAttribBinding},
  {"glVertexAttribDivisor", G_glVertexAttribDivisor},
  {"glVertexAttribDivisorANGLE", G_glVertexAttribDivisorANGLE},
  {"glVertexAttribDivisorEXT", G_glVertexAttribDivisorEXT},
  {"glVertexAttribDivisorNV", G_glVertexAttribDivisorNV},
  {"glVertexAttribFormat", G_glVertexAttribFormat},
  {"glVertexAttribI4i", G_glVertexAttribI4i},
  {"glVertexAttribI4iv", G_glVertexAttribI4iv},
  {"glVertexAttribI4ui", G_glVertexAttribI4ui},
  {"glVertexAttribI4uiv", G_glVertexAttribI4uiv},
  {"glVertexAttribIFormat", G_glVertexAttribIFormat},
  {"glVertexAttribIPointer", G_glVertexAttribIPointer},
  {"glVertexAttribPointer", G_glVertexAttribPointer},
  {"glVertexBindingDivisor", G_glVertexBindingDivisor},
  {"glViewport", G_glViewport},
  {"glViewportArrayvNV", G_glViewportArrayvNV},
  {"glViewportArrayvOES", G_glViewportArrayvOES},
  {"glViewportIndexedfNV", G_glViewportIndexedfNV},
  {"glViewportIndexedfOES", G_glViewportIndexedfOES},
  {"glViewportIndexedfvNV", G_glViewportIndexedfvNV},
  {"glViewportIndexedfvOES", G_glViewportIndexedfvOES},
  {"glViewportPositionWScaleNV", G_glViewportPositionWScaleNV},
  {"glViewportSwizzleNV", G_glViewportSwizzleNV},
  {"glWaitSemaphoreEXT", G_glWaitSemaphoreEXT},
  {"glWaitSync", G_glWaitSync},
  {"glWaitSyncAPPLE", G_glWaitSyncAPPLE},
  {"glWaitVkSemaphoreNV", G_glWaitVkSemaphoreNV},
  {"glWeightPathsNV", G_glWeightPathsNV},
  {"glWindowRectanglesEXT", G_glWindowRectanglesEXT},
};

uint32_t gl_ponte_por_nome(const char *nome) {
    for (size_t k = 0; k < sizeof tabela_gl / sizeof tabela_gl[0]; k++)
        if (!strcmp(tabela_gl[k].nome, nome)) return ponte_nova(tabela_gl[k].fn, tabela_gl[k].nome);
    return egl_ponte_por_nome(nome);
}

void I_glAcquireKeyedMutexWin32EXT(CPU *c) { G_glAcquireKeyedMutexWin32EXT(c); }
void I_glActiveShaderProgram(CPU *c) { G_glActiveShaderProgram(c); }
void I_glActiveShaderProgramEXT(CPU *c) { G_glActiveShaderProgramEXT(c); }
void I_glActiveTexture(CPU *c) { G_glActiveTexture(c); }
void I_glAlphaFuncQCOM(CPU *c) { G_glAlphaFuncQCOM(c); }
void I_glApplyFramebufferAttachmentCMAAINTEL(CPU *c) { G_glApplyFramebufferAttachmentCMAAINTEL(c); }
void I_glAttachShader(CPU *c) { G_glAttachShader(c); }
void I_glBeginConditionalRenderNV(CPU *c) { G_glBeginConditionalRenderNV(c); }
void I_glBeginPerfMonitorAMD(CPU *c) { G_glBeginPerfMonitorAMD(c); }
void I_glBeginPerfQueryINTEL(CPU *c) { G_glBeginPerfQueryINTEL(c); }
void I_glBeginQuery(CPU *c) { G_glBeginQuery(c); }
void I_glBeginQueryEXT(CPU *c) { G_glBeginQueryEXT(c); }
void I_glBeginTransformFeedback(CPU *c) { G_glBeginTransformFeedback(c); }
void I_glBindAttribLocation(CPU *c) { G_glBindAttribLocation(c); }
void I_glBindBuffer(CPU *c) { G_glBindBuffer(c); }
void I_glBindBufferBase(CPU *c) { G_glBindBufferBase(c); }
void I_glBindBufferRange(CPU *c) { G_glBindBufferRange(c); }
void I_glBindFragDataLocationEXT(CPU *c) { G_glBindFragDataLocationEXT(c); }
void I_glBindFragDataLocationIndexedEXT(CPU *c) { G_glBindFragDataLocationIndexedEXT(c); }
void I_glBindFramebuffer(CPU *c) { G_glBindFramebuffer(c); }
void I_glBindImageTexture(CPU *c) { G_glBindImageTexture(c); }
void I_glBindProgramPipeline(CPU *c) { G_glBindProgramPipeline(c); }
void I_glBindProgramPipelineEXT(CPU *c) { G_glBindProgramPipelineEXT(c); }
void I_glBindRenderbuffer(CPU *c) { G_glBindRenderbuffer(c); }
void I_glBindSampler(CPU *c) { G_glBindSampler(c); }
void I_glBindTexture(CPU *c) { G_glBindTexture(c); }
void I_glBindTransformFeedback(CPU *c) { G_glBindTransformFeedback(c); }
void I_glBindVertexArray(CPU *c) { G_glBindVertexArray(c); }
void I_glBindVertexArrayOES(CPU *c) { G_glBindVertexArrayOES(c); }
void I_glBindVertexBuffer(CPU *c) { G_glBindVertexBuffer(c); }
void I_glBlendBarrier(CPU *c) { G_glBlendBarrier(c); }
void I_glBlendBarrierKHR(CPU *c) { G_glBlendBarrierKHR(c); }
void I_glBlendBarrierNV(CPU *c) { G_glBlendBarrierNV(c); }
void I_glBlendColor(CPU *c) { G_glBlendColor(c); }
void I_glBlendEquation(CPU *c) { G_glBlendEquation(c); }
void I_glBlendEquationSeparate(CPU *c) { G_glBlendEquationSeparate(c); }
void I_glBlendEquationSeparatei(CPU *c) { G_glBlendEquationSeparatei(c); }
void I_glBlendEquationSeparateiEXT(CPU *c) { G_glBlendEquationSeparateiEXT(c); }
void I_glBlendEquationSeparateiOES(CPU *c) { G_glBlendEquationSeparateiOES(c); }
void I_glBlendEquationi(CPU *c) { G_glBlendEquationi(c); }
void I_glBlendEquationiEXT(CPU *c) { G_glBlendEquationiEXT(c); }
void I_glBlendEquationiOES(CPU *c) { G_glBlendEquationiOES(c); }
void I_glBlendFunc(CPU *c) { G_glBlendFunc(c); }
void I_glBlendFuncSeparate(CPU *c) { G_glBlendFuncSeparate(c); }
void I_glBlendFuncSeparatei(CPU *c) { G_glBlendFuncSeparatei(c); }
void I_glBlendFuncSeparateiEXT(CPU *c) { G_glBlendFuncSeparateiEXT(c); }
void I_glBlendFuncSeparateiOES(CPU *c) { G_glBlendFuncSeparateiOES(c); }
void I_glBlendFunci(CPU *c) { G_glBlendFunci(c); }
void I_glBlendFunciEXT(CPU *c) { G_glBlendFunciEXT(c); }
void I_glBlendFunciOES(CPU *c) { G_glBlendFunciOES(c); }
void I_glBlendParameteriNV(CPU *c) { G_glBlendParameteriNV(c); }
void I_glBlitFramebuffer(CPU *c) { G_glBlitFramebuffer(c); }
void I_glBlitFramebufferANGLE(CPU *c) { G_glBlitFramebufferANGLE(c); }
void I_glBlitFramebufferNV(CPU *c) { G_glBlitFramebufferNV(c); }
void I_glBufferData(CPU *c) { G_glBufferData(c); }
void I_glBufferStorageEXT(CPU *c) { G_glBufferStorageEXT(c); }
void I_glBufferStorageExternalEXT(CPU *c) { G_glBufferStorageExternalEXT(c); }
void I_glBufferStorageMemEXT(CPU *c) { G_glBufferStorageMemEXT(c); }
void I_glBufferSubData(CPU *c) { G_glBufferSubData(c); }
void I_glCheckFramebufferStatus(CPU *c) { G_glCheckFramebufferStatus(c); }
void I_glClear(CPU *c) { G_glClear(c); }
void I_glClearBufferfi(CPU *c) { G_glClearBufferfi(c); }
void I_glClearBufferfv(CPU *c) { G_glClearBufferfv(c); }
void I_glClearBufferiv(CPU *c) { G_glClearBufferiv(c); }
void I_glClearBufferuiv(CPU *c) { G_glClearBufferuiv(c); }
void I_glClearColor(CPU *c) { G_glClearColor(c); }
void I_glClearDepthf(CPU *c) { G_glClearDepthf(c); }
void I_glClearPixelLocalStorageuiEXT(CPU *c) { G_glClearPixelLocalStorageuiEXT(c); }
void I_glClearStencil(CPU *c) { G_glClearStencil(c); }
void I_glClearTexImageEXT(CPU *c) { G_glClearTexImageEXT(c); }
void I_glClearTexSubImageEXT(CPU *c) { G_glClearTexSubImageEXT(c); }
void I_glClientWaitSync(CPU *c) { G_glClientWaitSync(c); }
void I_glClientWaitSyncAPPLE(CPU *c) { G_glClientWaitSyncAPPLE(c); }
void I_glClipControlEXT(CPU *c) { G_glClipControlEXT(c); }
void I_glColorMask(CPU *c) { G_glColorMask(c); }
void I_glColorMaski(CPU *c) { G_glColorMaski(c); }
void I_glColorMaskiEXT(CPU *c) { G_glColorMaskiEXT(c); }
void I_glColorMaskiOES(CPU *c) { G_glColorMaskiOES(c); }
void I_glCompileShader(CPU *c) { G_glCompileShader(c); }
void I_glCompressedTexImage2D(CPU *c) { G_glCompressedTexImage2D(c); }
void I_glCompressedTexImage3D(CPU *c) { G_glCompressedTexImage3D(c); }
void I_glCompressedTexImage3DOES(CPU *c) { G_glCompressedTexImage3DOES(c); }
void I_glCompressedTexSubImage2D(CPU *c) { G_glCompressedTexSubImage2D(c); }
void I_glCompressedTexSubImage3D(CPU *c) { G_glCompressedTexSubImage3D(c); }
void I_glCompressedTexSubImage3DOES(CPU *c) { G_glCompressedTexSubImage3DOES(c); }
void I_glConservativeRasterParameteriNV(CPU *c) { G_glConservativeRasterParameteriNV(c); }
void I_glCopyBufferSubData(CPU *c) { G_glCopyBufferSubData(c); }
void I_glCopyBufferSubDataNV(CPU *c) { G_glCopyBufferSubDataNV(c); }
void I_glCopyImageSubData(CPU *c) { G_glCopyImageSubData(c); }
void I_glCopyImageSubDataEXT(CPU *c) { G_glCopyImageSubDataEXT(c); }
void I_glCopyImageSubDataOES(CPU *c) { G_glCopyImageSubDataOES(c); }
void I_glCopyPathNV(CPU *c) { G_glCopyPathNV(c); }
void I_glCopyTexImage2D(CPU *c) { G_glCopyTexImage2D(c); }
void I_glCopyTexSubImage2D(CPU *c) { G_glCopyTexSubImage2D(c); }
void I_glCopyTexSubImage3D(CPU *c) { G_glCopyTexSubImage3D(c); }
void I_glCopyTexSubImage3DOES(CPU *c) { G_glCopyTexSubImage3DOES(c); }
void I_glCopyTextureLevelsAPPLE(CPU *c) { G_glCopyTextureLevelsAPPLE(c); }
void I_glCoverFillPathInstancedNV(CPU *c) { G_glCoverFillPathInstancedNV(c); }
void I_glCoverFillPathNV(CPU *c) { G_glCoverFillPathNV(c); }
void I_glCoverStrokePathInstancedNV(CPU *c) { G_glCoverStrokePathInstancedNV(c); }
void I_glCoverStrokePathNV(CPU *c) { G_glCoverStrokePathNV(c); }
void I_glCoverageMaskNV(CPU *c) { G_glCoverageMaskNV(c); }
void I_glCoverageModulationNV(CPU *c) { G_glCoverageModulationNV(c); }
void I_glCoverageModulationTableNV(CPU *c) { G_glCoverageModulationTableNV(c); }
void I_glCoverageOperationNV(CPU *c) { G_glCoverageOperationNV(c); }
void I_glCreateMemoryObjectsEXT(CPU *c) { G_glCreateMemoryObjectsEXT(c); }
void I_glCreatePerfQueryINTEL(CPU *c) { G_glCreatePerfQueryINTEL(c); }
void I_glCreateProgram(CPU *c) { G_glCreateProgram(c); }
void I_glCreateShader(CPU *c) { G_glCreateShader(c); }
void I_glCreateShaderProgramv(CPU *c) { G_glCreateShaderProgramv(c); }
void I_glCreateShaderProgramvEXT(CPU *c) { G_glCreateShaderProgramvEXT(c); }
void I_glCullFace(CPU *c) { G_glCullFace(c); }
void I_glDebugMessageCallback(CPU *c) { G_glDebugMessageCallback(c); }
void I_glDebugMessageCallbackKHR(CPU *c) { G_glDebugMessageCallbackKHR(c); }
void I_glDebugMessageControl(CPU *c) { G_glDebugMessageControl(c); }
void I_glDebugMessageControlKHR(CPU *c) { G_glDebugMessageControlKHR(c); }
void I_glDebugMessageInsert(CPU *c) { G_glDebugMessageInsert(c); }
void I_glDebugMessageInsertKHR(CPU *c) { G_glDebugMessageInsertKHR(c); }
void I_glDeleteBuffers(CPU *c) { G_glDeleteBuffers(c); }
void I_glDeleteFencesNV(CPU *c) { G_glDeleteFencesNV(c); }
void I_glDeleteFramebuffers(CPU *c) { G_glDeleteFramebuffers(c); }
void I_glDeleteMemoryObjectsEXT(CPU *c) { G_glDeleteMemoryObjectsEXT(c); }
void I_glDeletePathsNV(CPU *c) { G_glDeletePathsNV(c); }
void I_glDeletePerfMonitorsAMD(CPU *c) { G_glDeletePerfMonitorsAMD(c); }
void I_glDeletePerfQueryINTEL(CPU *c) { G_glDeletePerfQueryINTEL(c); }
void I_glDeleteProgram(CPU *c) { G_glDeleteProgram(c); }
void I_glDeleteProgramPipelines(CPU *c) { G_glDeleteProgramPipelines(c); }
void I_glDeleteProgramPipelinesEXT(CPU *c) { G_glDeleteProgramPipelinesEXT(c); }
void I_glDeleteQueries(CPU *c) { G_glDeleteQueries(c); }
void I_glDeleteQueriesEXT(CPU *c) { G_glDeleteQueriesEXT(c); }
void I_glDeleteRenderbuffers(CPU *c) { G_glDeleteRenderbuffers(c); }
void I_glDeleteSamplers(CPU *c) { G_glDeleteSamplers(c); }
void I_glDeleteSemaphoresEXT(CPU *c) { G_glDeleteSemaphoresEXT(c); }
void I_glDeleteShader(CPU *c) { G_glDeleteShader(c); }
void I_glDeleteSync(CPU *c) { G_glDeleteSync(c); }
void I_glDeleteSyncAPPLE(CPU *c) { G_glDeleteSyncAPPLE(c); }
void I_glDeleteTextures(CPU *c) { G_glDeleteTextures(c); }
void I_glDeleteTransformFeedbacks(CPU *c) { G_glDeleteTransformFeedbacks(c); }
void I_glDeleteVertexArrays(CPU *c) { G_glDeleteVertexArrays(c); }
void I_glDeleteVertexArraysOES(CPU *c) { G_glDeleteVertexArraysOES(c); }
void I_glDepthFunc(CPU *c) { G_glDepthFunc(c); }
void I_glDepthMask(CPU *c) { G_glDepthMask(c); }
void I_glDepthRangeArrayfvNV(CPU *c) { G_glDepthRangeArrayfvNV(c); }
void I_glDepthRangeArrayfvOES(CPU *c) { G_glDepthRangeArrayfvOES(c); }
void I_glDepthRangeIndexedfNV(CPU *c) { G_glDepthRangeIndexedfNV(c); }
void I_glDepthRangeIndexedfOES(CPU *c) { G_glDepthRangeIndexedfOES(c); }
void I_glDepthRangef(CPU *c) { G_glDepthRangef(c); }
void I_glDetachShader(CPU *c) { G_glDetachShader(c); }
void I_glDisable(CPU *c) { G_glDisable(c); }
void I_glDisableDriverControlQCOM(CPU *c) { G_glDisableDriverControlQCOM(c); }
void I_glDisableVertexAttribArray(CPU *c) { G_glDisableVertexAttribArray(c); }
void I_glDisablei(CPU *c) { G_glDisablei(c); }
void I_glDisableiEXT(CPU *c) { G_glDisableiEXT(c); }
void I_glDisableiNV(CPU *c) { G_glDisableiNV(c); }
void I_glDisableiOES(CPU *c) { G_glDisableiOES(c); }
void I_glDiscardFramebufferEXT(CPU *c) { G_glDiscardFramebufferEXT(c); }
void I_glDispatchCompute(CPU *c) { G_glDispatchCompute(c); }
void I_glDispatchComputeIndirect(CPU *c) { G_glDispatchComputeIndirect(c); }
void I_glDrawArrays(CPU *c) { G_glDrawArrays(c); }
void I_glDrawArraysIndirect(CPU *c) { G_glDrawArraysIndirect(c); }
void I_glDrawArraysInstanced(CPU *c) { G_glDrawArraysInstanced(c); }
void I_glDrawArraysInstancedANGLE(CPU *c) { G_glDrawArraysInstancedANGLE(c); }
void I_glDrawArraysInstancedBaseInstanceEXT(CPU *c) { G_glDrawArraysInstancedBaseInstanceEXT(c); }
void I_glDrawArraysInstancedEXT(CPU *c) { G_glDrawArraysInstancedEXT(c); }
void I_glDrawArraysInstancedNV(CPU *c) { G_glDrawArraysInstancedNV(c); }
void I_glDrawBuffers(CPU *c) { G_glDrawBuffers(c); }
void I_glDrawBuffersEXT(CPU *c) { G_glDrawBuffersEXT(c); }
void I_glDrawBuffersIndexedEXT(CPU *c) { G_glDrawBuffersIndexedEXT(c); }
void I_glDrawBuffersNV(CPU *c) { G_glDrawBuffersNV(c); }
void I_glDrawElements(CPU *c) { G_glDrawElements(c); }
void I_glDrawElementsBaseVertex(CPU *c) { G_glDrawElementsBaseVertex(c); }
void I_glDrawElementsBaseVertexEXT(CPU *c) { G_glDrawElementsBaseVertexEXT(c); }
void I_glDrawElementsBaseVertexOES(CPU *c) { G_glDrawElementsBaseVertexOES(c); }
void I_glDrawElementsIndirect(CPU *c) { G_glDrawElementsIndirect(c); }
void I_glDrawElementsInstanced(CPU *c) { G_glDrawElementsInstanced(c); }
void I_glDrawElementsInstancedANGLE(CPU *c) { G_glDrawElementsInstancedANGLE(c); }
void I_glDrawElementsInstancedBaseInstanceEXT(CPU *c) { G_glDrawElementsInstancedBaseInstanceEXT(c); }
void I_glDrawElementsInstancedBaseVertex(CPU *c) { G_glDrawElementsInstancedBaseVertex(c); }
void I_glDrawElementsInstancedBaseVertexBaseInstanceEXT(CPU *c) { G_glDrawElementsInstancedBaseVertexBaseInstanceEXT(c); }
void I_glDrawElementsInstancedBaseVertexEXT(CPU *c) { G_glDrawElementsInstancedBaseVertexEXT(c); }
void I_glDrawElementsInstancedBaseVertexOES(CPU *c) { G_glDrawElementsInstancedBaseVertexOES(c); }
void I_glDrawElementsInstancedEXT(CPU *c) { G_glDrawElementsInstancedEXT(c); }
void I_glDrawElementsInstancedNV(CPU *c) { G_glDrawElementsInstancedNV(c); }
void I_glDrawRangeElements(CPU *c) { G_glDrawRangeElements(c); }
void I_glDrawRangeElementsBaseVertex(CPU *c) { G_glDrawRangeElementsBaseVertex(c); }
void I_glDrawRangeElementsBaseVertexEXT(CPU *c) { G_glDrawRangeElementsBaseVertexEXT(c); }
void I_glDrawRangeElementsBaseVertexOES(CPU *c) { G_glDrawRangeElementsBaseVertexOES(c); }
void I_glDrawTransformFeedbackEXT(CPU *c) { G_glDrawTransformFeedbackEXT(c); }
void I_glDrawTransformFeedbackInstancedEXT(CPU *c) { G_glDrawTransformFeedbackInstancedEXT(c); }
void I_glDrawVkImageNV(CPU *c) { G_glDrawVkImageNV(c); }
void I_glEGLImageTargetRenderbufferStorageOES(CPU *c) { G_glEGLImageTargetRenderbufferStorageOES(c); }
void I_glEGLImageTargetTexStorageEXT(CPU *c) { G_glEGLImageTargetTexStorageEXT(c); }
void I_glEGLImageTargetTexture2DOES(CPU *c) { G_glEGLImageTargetTexture2DOES(c); }
void I_glEGLImageTargetTextureStorageEXT(CPU *c) { G_glEGLImageTargetTextureStorageEXT(c); }
void I_glEnable(CPU *c) { G_glEnable(c); }
void I_glEnableDriverControlQCOM(CPU *c) { G_glEnableDriverControlQCOM(c); }
void I_glEnableVertexAttribArray(CPU *c) { G_glEnableVertexAttribArray(c); }
void I_glEnablei(CPU *c) { G_glEnablei(c); }
void I_glEnableiEXT(CPU *c) { G_glEnableiEXT(c); }
void I_glEnableiNV(CPU *c) { G_glEnableiNV(c); }
void I_glEnableiOES(CPU *c) { G_glEnableiOES(c); }
void I_glEndConditionalRenderNV(CPU *c) { G_glEndConditionalRenderNV(c); }
void I_glEndPerfMonitorAMD(CPU *c) { G_glEndPerfMonitorAMD(c); }
void I_glEndPerfQueryINTEL(CPU *c) { G_glEndPerfQueryINTEL(c); }
void I_glEndQuery(CPU *c) { G_glEndQuery(c); }
void I_glEndQueryEXT(CPU *c) { G_glEndQueryEXT(c); }
void I_glEndTilingQCOM(CPU *c) { G_glEndTilingQCOM(c); }
void I_glEndTransformFeedback(CPU *c) { G_glEndTransformFeedback(c); }
void I_glExtGetBufferPointervQCOM(CPU *c) { G_glExtGetBufferPointervQCOM(c); }
void I_glExtGetBuffersQCOM(CPU *c) { G_glExtGetBuffersQCOM(c); }
void I_glExtGetFramebuffersQCOM(CPU *c) { G_glExtGetFramebuffersQCOM(c); }
void I_glExtGetProgramBinarySourceQCOM(CPU *c) { G_glExtGetProgramBinarySourceQCOM(c); }
void I_glExtGetProgramsQCOM(CPU *c) { G_glExtGetProgramsQCOM(c); }
void I_glExtGetRenderbuffersQCOM(CPU *c) { G_glExtGetRenderbuffersQCOM(c); }
void I_glExtGetShadersQCOM(CPU *c) { G_glExtGetShadersQCOM(c); }
void I_glExtGetTexLevelParameterivQCOM(CPU *c) { G_glExtGetTexLevelParameterivQCOM(c); }
void I_glExtGetTexSubImageQCOM(CPU *c) { G_glExtGetTexSubImageQCOM(c); }
void I_glExtGetTexturesQCOM(CPU *c) { G_glExtGetTexturesQCOM(c); }
void I_glExtIsProgramBinaryQCOM(CPU *c) { G_glExtIsProgramBinaryQCOM(c); }
void I_glExtTexObjectStateOverrideiQCOM(CPU *c) { G_glExtTexObjectStateOverrideiQCOM(c); }
void I_glFenceSync(CPU *c) { G_glFenceSync(c); }
void I_glFenceSyncAPPLE(CPU *c) { G_glFenceSyncAPPLE(c); }
void I_glFinish(CPU *c) { G_glFinish(c); }
void I_glFinishFenceNV(CPU *c) { G_glFinishFenceNV(c); }
void I_glFlush(CPU *c) { G_glFlush(c); }
void I_glFlushMappedBufferRange(CPU *c) { G_glFlushMappedBufferRange(c); }
void I_glFlushMappedBufferRangeEXT(CPU *c) { G_glFlushMappedBufferRangeEXT(c); }
void I_glFragmentCoverageColorNV(CPU *c) { G_glFragmentCoverageColorNV(c); }
void I_glFramebufferFetchBarrierEXT(CPU *c) { G_glFramebufferFetchBarrierEXT(c); }
void I_glFramebufferFetchBarrierQCOM(CPU *c) { G_glFramebufferFetchBarrierQCOM(c); }
void I_glFramebufferFoveationConfigQCOM(CPU *c) { G_glFramebufferFoveationConfigQCOM(c); }
void I_glFramebufferFoveationParametersQCOM(CPU *c) { G_glFramebufferFoveationParametersQCOM(c); }
void I_glFramebufferParameteri(CPU *c) { G_glFramebufferParameteri(c); }
void I_glFramebufferPixelLocalStorageSizeEXT(CPU *c) { G_glFramebufferPixelLocalStorageSizeEXT(c); }
void I_glFramebufferRenderbuffer(CPU *c) { G_glFramebufferRenderbuffer(c); }
void I_glFramebufferSampleLocationsfvNV(CPU *c) { G_glFramebufferSampleLocationsfvNV(c); }
void I_glFramebufferTexture(CPU *c) { G_glFramebufferTexture(c); }
void I_glFramebufferTexture2D(CPU *c) { G_glFramebufferTexture2D(c); }
void I_glFramebufferTexture2DDownsampleIMG(CPU *c) { G_glFramebufferTexture2DDownsampleIMG(c); }
void I_glFramebufferTexture2DMultisampleEXT(CPU *c) { G_glFramebufferTexture2DMultisampleEXT(c); }
void I_glFramebufferTexture2DMultisampleIMG(CPU *c) { G_glFramebufferTexture2DMultisampleIMG(c); }
void I_glFramebufferTexture3DOES(CPU *c) { G_glFramebufferTexture3DOES(c); }
void I_glFramebufferTextureEXT(CPU *c) { G_glFramebufferTextureEXT(c); }
void I_glFramebufferTextureLayer(CPU *c) { G_glFramebufferTextureLayer(c); }
void I_glFramebufferTextureLayerDownsampleIMG(CPU *c) { G_glFramebufferTextureLayerDownsampleIMG(c); }
void I_glFramebufferTextureMultisampleMultiviewOVR(CPU *c) { G_glFramebufferTextureMultisampleMultiviewOVR(c); }
void I_glFramebufferTextureMultiviewOVR(CPU *c) { G_glFramebufferTextureMultiviewOVR(c); }
void I_glFramebufferTextureOES(CPU *c) { G_glFramebufferTextureOES(c); }
void I_glFrontFace(CPU *c) { G_glFrontFace(c); }
void I_glGenBuffers(CPU *c) { G_glGenBuffers(c); }
void I_glGenFencesNV(CPU *c) { G_glGenFencesNV(c); }
void I_glGenFramebuffers(CPU *c) { G_glGenFramebuffers(c); }
void I_glGenPathsNV(CPU *c) { G_glGenPathsNV(c); }
void I_glGenPerfMonitorsAMD(CPU *c) { G_glGenPerfMonitorsAMD(c); }
void I_glGenProgramPipelines(CPU *c) { G_glGenProgramPipelines(c); }
void I_glGenProgramPipelinesEXT(CPU *c) { G_glGenProgramPipelinesEXT(c); }
void I_glGenQueries(CPU *c) { G_glGenQueries(c); }
void I_glGenQueriesEXT(CPU *c) { G_glGenQueriesEXT(c); }
void I_glGenRenderbuffers(CPU *c) { G_glGenRenderbuffers(c); }
void I_glGenSamplers(CPU *c) { G_glGenSamplers(c); }
void I_glGenSemaphoresEXT(CPU *c) { G_glGenSemaphoresEXT(c); }
void I_glGenTextures(CPU *c) { G_glGenTextures(c); }
void I_glGenTransformFeedbacks(CPU *c) { G_glGenTransformFeedbacks(c); }
void I_glGenVertexArrays(CPU *c) { G_glGenVertexArrays(c); }
void I_glGenVertexArraysOES(CPU *c) { G_glGenVertexArraysOES(c); }
void I_glGenerateMipmap(CPU *c) { G_glGenerateMipmap(c); }
void I_glGetActiveAttrib(CPU *c) { G_glGetActiveAttrib(c); }
void I_glGetActiveUniform(CPU *c) { G_glGetActiveUniform(c); }
void I_glGetActiveUniformBlockName(CPU *c) { G_glGetActiveUniformBlockName(c); }
void I_glGetActiveUniformBlockiv(CPU *c) { G_glGetActiveUniformBlockiv(c); }
void I_glGetActiveUniformsiv(CPU *c) { G_glGetActiveUniformsiv(c); }
void I_glGetAttachedShaders(CPU *c) { G_glGetAttachedShaders(c); }
void I_glGetAttribLocation(CPU *c) { G_glGetAttribLocation(c); }
void I_glGetBooleani_v(CPU *c) { G_glGetBooleani_v(c); }
void I_glGetBooleanv(CPU *c) { G_glGetBooleanv(c); }
void I_glGetBufferParameteri64v(CPU *c) { G_glGetBufferParameteri64v(c); }
void I_glGetBufferParameteriv(CPU *c) { G_glGetBufferParameteriv(c); }
void I_glGetBufferPointerv(CPU *c) { G_glGetBufferPointerv(c); }
void I_glGetBufferPointervOES(CPU *c) { G_glGetBufferPointervOES(c); }
void I_glGetCoverageModulationTableNV(CPU *c) { G_glGetCoverageModulationTableNV(c); }
void I_glGetDebugMessageLog(CPU *c) { G_glGetDebugMessageLog(c); }
void I_glGetDebugMessageLogKHR(CPU *c) { G_glGetDebugMessageLogKHR(c); }
void I_glGetDriverControlStringQCOM(CPU *c) { G_glGetDriverControlStringQCOM(c); }
void I_glGetDriverControlsQCOM(CPU *c) { G_glGetDriverControlsQCOM(c); }
void I_glGetError(CPU *c) { G_glGetError(c); }
void I_glGetFenceivNV(CPU *c) { G_glGetFenceivNV(c); }
void I_glGetFirstPerfQueryIdINTEL(CPU *c) { G_glGetFirstPerfQueryIdINTEL(c); }
void I_glGetFloati_vNV(CPU *c) { G_glGetFloati_vNV(c); }
void I_glGetFloati_vOES(CPU *c) { G_glGetFloati_vOES(c); }
void I_glGetFloatv(CPU *c) { G_glGetFloatv(c); }
void I_glGetFragDataIndexEXT(CPU *c) { G_glGetFragDataIndexEXT(c); }
void I_glGetFragDataLocation(CPU *c) { G_glGetFragDataLocation(c); }
void I_glGetFramebufferAttachmentParameteriv(CPU *c) { G_glGetFramebufferAttachmentParameteriv(c); }
void I_glGetFramebufferParameteriv(CPU *c) { G_glGetFramebufferParameteriv(c); }
void I_glGetFramebufferPixelLocalStorageSizeEXT(CPU *c) { G_glGetFramebufferPixelLocalStorageSizeEXT(c); }
void I_glGetGraphicsResetStatus(CPU *c) { G_glGetGraphicsResetStatus(c); }
void I_glGetGraphicsResetStatusEXT(CPU *c) { G_glGetGraphicsResetStatusEXT(c); }
void I_glGetGraphicsResetStatusKHR(CPU *c) { G_glGetGraphicsResetStatusKHR(c); }
void I_glGetInteger64i_v(CPU *c) { G_glGetInteger64i_v(c); }
void I_glGetInteger64v(CPU *c) { G_glGetInteger64v(c); }
void I_glGetInteger64vAPPLE(CPU *c) { G_glGetInteger64vAPPLE(c); }
void I_glGetIntegeri_v(CPU *c) { G_glGetIntegeri_v(c); }
void I_glGetIntegeri_vEXT(CPU *c) { G_glGetIntegeri_vEXT(c); }
void I_glGetIntegerv(CPU *c) { G_glGetIntegerv(c); }
void I_glGetInternalformatSampleivNV(CPU *c) { G_glGetInternalformatSampleivNV(c); }
void I_glGetInternalformativ(CPU *c) { G_glGetInternalformativ(c); }
void I_glGetMemoryObjectParameterivEXT(CPU *c) { G_glGetMemoryObjectParameterivEXT(c); }
void I_glGetMultisamplefv(CPU *c) { G_glGetMultisamplefv(c); }
void I_glGetNextPerfQueryIdINTEL(CPU *c) { G_glGetNextPerfQueryIdINTEL(c); }
void I_glGetObjectLabel(CPU *c) { G_glGetObjectLabel(c); }
void I_glGetObjectLabelEXT(CPU *c) { G_glGetObjectLabelEXT(c); }
void I_glGetObjectLabelKHR(CPU *c) { G_glGetObjectLabelKHR(c); }
void I_glGetObjectPtrLabel(CPU *c) { G_glGetObjectPtrLabel(c); }
void I_glGetObjectPtrLabelKHR(CPU *c) { G_glGetObjectPtrLabelKHR(c); }
void I_glGetPathCommandsNV(CPU *c) { G_glGetPathCommandsNV(c); }
void I_glGetPathCoordsNV(CPU *c) { G_glGetPathCoordsNV(c); }
void I_glGetPathDashArrayNV(CPU *c) { G_glGetPathDashArrayNV(c); }
void I_glGetPathLengthNV(CPU *c) { G_glGetPathLengthNV(c); }
void I_glGetPathMetricRangeNV(CPU *c) { G_glGetPathMetricRangeNV(c); }
void I_glGetPathMetricsNV(CPU *c) { G_glGetPathMetricsNV(c); }
void I_glGetPathParameterfvNV(CPU *c) { G_glGetPathParameterfvNV(c); }
void I_glGetPathParameterivNV(CPU *c) { G_glGetPathParameterivNV(c); }
void I_glGetPathSpacingNV(CPU *c) { G_glGetPathSpacingNV(c); }
void I_glGetPerfCounterInfoINTEL(CPU *c) { G_glGetPerfCounterInfoINTEL(c); }
void I_glGetPerfMonitorCounterDataAMD(CPU *c) { G_glGetPerfMonitorCounterDataAMD(c); }
void I_glGetPerfMonitorCounterInfoAMD(CPU *c) { G_glGetPerfMonitorCounterInfoAMD(c); }
void I_glGetPerfMonitorCounterStringAMD(CPU *c) { G_glGetPerfMonitorCounterStringAMD(c); }
void I_glGetPerfMonitorCountersAMD(CPU *c) { G_glGetPerfMonitorCountersAMD(c); }
void I_glGetPerfMonitorGroupStringAMD(CPU *c) { G_glGetPerfMonitorGroupStringAMD(c); }
void I_glGetPerfMonitorGroupsAMD(CPU *c) { G_glGetPerfMonitorGroupsAMD(c); }
void I_glGetPerfQueryDataINTEL(CPU *c) { G_glGetPerfQueryDataINTEL(c); }
void I_glGetPerfQueryIdByNameINTEL(CPU *c) { G_glGetPerfQueryIdByNameINTEL(c); }
void I_glGetPerfQueryInfoINTEL(CPU *c) { G_glGetPerfQueryInfoINTEL(c); }
void I_glGetPointerv(CPU *c) { G_glGetPointerv(c); }
void I_glGetPointervKHR(CPU *c) { G_glGetPointervKHR(c); }
void I_glGetProgramBinary(CPU *c) { G_glGetProgramBinary(c); }
void I_glGetProgramBinaryOES(CPU *c) { G_glGetProgramBinaryOES(c); }
void I_glGetProgramInfoLog(CPU *c) { G_glGetProgramInfoLog(c); }
void I_glGetProgramInterfaceiv(CPU *c) { G_glGetProgramInterfaceiv(c); }
void I_glGetProgramPipelineInfoLog(CPU *c) { G_glGetProgramPipelineInfoLog(c); }
void I_glGetProgramPipelineInfoLogEXT(CPU *c) { G_glGetProgramPipelineInfoLogEXT(c); }
void I_glGetProgramPipelineiv(CPU *c) { G_glGetProgramPipelineiv(c); }
void I_glGetProgramPipelineivEXT(CPU *c) { G_glGetProgramPipelineivEXT(c); }
void I_glGetProgramResourceIndex(CPU *c) { G_glGetProgramResourceIndex(c); }
void I_glGetProgramResourceLocation(CPU *c) { G_glGetProgramResourceLocation(c); }
void I_glGetProgramResourceLocationIndexEXT(CPU *c) { G_glGetProgramResourceLocationIndexEXT(c); }
void I_glGetProgramResourceName(CPU *c) { G_glGetProgramResourceName(c); }
void I_glGetProgramResourcefvNV(CPU *c) { G_glGetProgramResourcefvNV(c); }
void I_glGetProgramResourceiv(CPU *c) { G_glGetProgramResourceiv(c); }
void I_glGetProgramiv(CPU *c) { G_glGetProgramiv(c); }
void I_glGetQueryObjecti64vEXT(CPU *c) { G_glGetQueryObjecti64vEXT(c); }
void I_glGetQueryObjectivEXT(CPU *c) { G_glGetQueryObjectivEXT(c); }
void I_glGetQueryObjectui64vEXT(CPU *c) { G_glGetQueryObjectui64vEXT(c); }
void I_glGetQueryObjectuiv(CPU *c) { G_glGetQueryObjectuiv(c); }
void I_glGetQueryObjectuivEXT(CPU *c) { G_glGetQueryObjectuivEXT(c); }
void I_glGetQueryiv(CPU *c) { G_glGetQueryiv(c); }
void I_glGetQueryivEXT(CPU *c) { G_glGetQueryivEXT(c); }
void I_glGetRenderbufferParameteriv(CPU *c) { G_glGetRenderbufferParameteriv(c); }
void I_glGetSamplerParameterIiv(CPU *c) { G_glGetSamplerParameterIiv(c); }
void I_glGetSamplerParameterIivEXT(CPU *c) { G_glGetSamplerParameterIivEXT(c); }
void I_glGetSamplerParameterIivOES(CPU *c) { G_glGetSamplerParameterIivOES(c); }
void I_glGetSamplerParameterIuiv(CPU *c) { G_glGetSamplerParameterIuiv(c); }
void I_glGetSamplerParameterIuivEXT(CPU *c) { G_glGetSamplerParameterIuivEXT(c); }
void I_glGetSamplerParameterIuivOES(CPU *c) { G_glGetSamplerParameterIuivOES(c); }
void I_glGetSamplerParameterfv(CPU *c) { G_glGetSamplerParameterfv(c); }
void I_glGetSamplerParameteriv(CPU *c) { G_glGetSamplerParameteriv(c); }
void I_glGetSemaphoreParameterui64vEXT(CPU *c) { G_glGetSemaphoreParameterui64vEXT(c); }
void I_glGetShaderInfoLog(CPU *c) { G_glGetShaderInfoLog(c); }
void I_glGetShaderPrecisionFormat(CPU *c) { G_glGetShaderPrecisionFormat(c); }
void I_glGetShaderSource(CPU *c) { G_glGetShaderSource(c); }
void I_glGetShaderiv(CPU *c) { G_glGetShaderiv(c); }
void I_glGetString(CPU *c) { G_glGetString(c); }
void I_glGetStringi(CPU *c) { G_glGetStringi(c); }
void I_glGetSynciv(CPU *c) { G_glGetSynciv(c); }
void I_glGetSyncivAPPLE(CPU *c) { G_glGetSyncivAPPLE(c); }
void I_glGetTexLevelParameterfv(CPU *c) { G_glGetTexLevelParameterfv(c); }
void I_glGetTexLevelParameteriv(CPU *c) { G_glGetTexLevelParameteriv(c); }
void I_glGetTexParameterIiv(CPU *c) { G_glGetTexParameterIiv(c); }
void I_glGetTexParameterIivEXT(CPU *c) { G_glGetTexParameterIivEXT(c); }
void I_glGetTexParameterIivOES(CPU *c) { G_glGetTexParameterIivOES(c); }
void I_glGetTexParameterIuiv(CPU *c) { G_glGetTexParameterIuiv(c); }
void I_glGetTexParameterIuivEXT(CPU *c) { G_glGetTexParameterIuivEXT(c); }
void I_glGetTexParameterIuivOES(CPU *c) { G_glGetTexParameterIuivOES(c); }
void I_glGetTexParameterfv(CPU *c) { G_glGetTexParameterfv(c); }
void I_glGetTexParameteriv(CPU *c) { G_glGetTexParameteriv(c); }
void I_glGetTransformFeedbackVarying(CPU *c) { G_glGetTransformFeedbackVarying(c); }
void I_glGetTranslatedShaderSourceANGLE(CPU *c) { G_glGetTranslatedShaderSourceANGLE(c); }
void I_glGetUniformBlockIndex(CPU *c) { G_glGetUniformBlockIndex(c); }
void I_glGetUniformIndices(CPU *c) { G_glGetUniformIndices(c); }
void I_glGetUniformLocation(CPU *c) { G_glGetUniformLocation(c); }
void I_glGetUniformfv(CPU *c) { G_glGetUniformfv(c); }
void I_glGetUniformi64vNV(CPU *c) { G_glGetUniformi64vNV(c); }
void I_glGetUniformiv(CPU *c) { G_glGetUniformiv(c); }
void I_glGetUniformuiv(CPU *c) { G_glGetUniformuiv(c); }
void I_glGetUnsignedBytei_vEXT(CPU *c) { G_glGetUnsignedBytei_vEXT(c); }
void I_glGetUnsignedBytevEXT(CPU *c) { G_glGetUnsignedBytevEXT(c); }
void I_glGetVertexAttribIiv(CPU *c) { G_glGetVertexAttribIiv(c); }
void I_glGetVertexAttribIuiv(CPU *c) { G_glGetVertexAttribIuiv(c); }
void I_glGetVertexAttribPointerv(CPU *c) { G_glGetVertexAttribPointerv(c); }
void I_glGetVertexAttribfv(CPU *c) { G_glGetVertexAttribfv(c); }
void I_glGetVertexAttribiv(CPU *c) { G_glGetVertexAttribiv(c); }
void I_glGetnUniformfv(CPU *c) { G_glGetnUniformfv(c); }
void I_glGetnUniformfvEXT(CPU *c) { G_glGetnUniformfvEXT(c); }
void I_glGetnUniformfvKHR(CPU *c) { G_glGetnUniformfvKHR(c); }
void I_glGetnUniformiv(CPU *c) { G_glGetnUniformiv(c); }
void I_glGetnUniformivEXT(CPU *c) { G_glGetnUniformivEXT(c); }
void I_glGetnUniformivKHR(CPU *c) { G_glGetnUniformivKHR(c); }
void I_glGetnUniformuiv(CPU *c) { G_glGetnUniformuiv(c); }
void I_glGetnUniformuivKHR(CPU *c) { G_glGetnUniformuivKHR(c); }
void I_glHint(CPU *c) { G_glHint(c); }
void I_glImportMemoryFdEXT(CPU *c) { G_glImportMemoryFdEXT(c); }
void I_glImportMemoryWin32HandleEXT(CPU *c) { G_glImportMemoryWin32HandleEXT(c); }
void I_glImportMemoryWin32NameEXT(CPU *c) { G_glImportMemoryWin32NameEXT(c); }
void I_glImportSemaphoreFdEXT(CPU *c) { G_glImportSemaphoreFdEXT(c); }
void I_glImportSemaphoreWin32HandleEXT(CPU *c) { G_glImportSemaphoreWin32HandleEXT(c); }
void I_glImportSemaphoreWin32NameEXT(CPU *c) { G_glImportSemaphoreWin32NameEXT(c); }
void I_glInsertEventMarkerEXT(CPU *c) { G_glInsertEventMarkerEXT(c); }
void I_glInterpolatePathsNV(CPU *c) { G_glInterpolatePathsNV(c); }
void I_glInvalidateFramebuffer(CPU *c) { G_glInvalidateFramebuffer(c); }
void I_glInvalidateSubFramebuffer(CPU *c) { G_glInvalidateSubFramebuffer(c); }
void I_glIsBuffer(CPU *c) { G_glIsBuffer(c); }
void I_glIsEnabled(CPU *c) { G_glIsEnabled(c); }
void I_glIsEnabledi(CPU *c) { G_glIsEnabledi(c); }
void I_glIsEnablediEXT(CPU *c) { G_glIsEnablediEXT(c); }
void I_glIsEnablediNV(CPU *c) { G_glIsEnablediNV(c); }
void I_glIsEnablediOES(CPU *c) { G_glIsEnablediOES(c); }
void I_glIsFenceNV(CPU *c) { G_glIsFenceNV(c); }
void I_glIsFramebuffer(CPU *c) { G_glIsFramebuffer(c); }
void I_glIsImageHandleResidentNV(CPU *c) { G_glIsImageHandleResidentNV(c); }
void I_glIsMemoryObjectEXT(CPU *c) { G_glIsMemoryObjectEXT(c); }
void I_glIsPathNV(CPU *c) { G_glIsPathNV(c); }
void I_glIsPointInFillPathNV(CPU *c) { G_glIsPointInFillPathNV(c); }
void I_glIsPointInStrokePathNV(CPU *c) { G_glIsPointInStrokePathNV(c); }
void I_glIsProgram(CPU *c) { G_glIsProgram(c); }
void I_glIsProgramPipeline(CPU *c) { G_glIsProgramPipeline(c); }
void I_glIsProgramPipelineEXT(CPU *c) { G_glIsProgramPipelineEXT(c); }
void I_glIsQuery(CPU *c) { G_glIsQuery(c); }
void I_glIsQueryEXT(CPU *c) { G_glIsQueryEXT(c); }
void I_glIsRenderbuffer(CPU *c) { G_glIsRenderbuffer(c); }
void I_glIsSampler(CPU *c) { G_glIsSampler(c); }
void I_glIsSemaphoreEXT(CPU *c) { G_glIsSemaphoreEXT(c); }
void I_glIsShader(CPU *c) { G_glIsShader(c); }
void I_glIsSync(CPU *c) { G_glIsSync(c); }
void I_glIsSyncAPPLE(CPU *c) { G_glIsSyncAPPLE(c); }
void I_glIsTexture(CPU *c) { G_glIsTexture(c); }
void I_glIsTextureHandleResidentNV(CPU *c) { G_glIsTextureHandleResidentNV(c); }
void I_glIsTransformFeedback(CPU *c) { G_glIsTransformFeedback(c); }
void I_glIsVertexArray(CPU *c) { G_glIsVertexArray(c); }
void I_glIsVertexArrayOES(CPU *c) { G_glIsVertexArrayOES(c); }
void I_glLabelObjectEXT(CPU *c) { G_glLabelObjectEXT(c); }
void I_glLineWidth(CPU *c) { G_glLineWidth(c); }
void I_glLinkProgram(CPU *c) { G_glLinkProgram(c); }
void I_glMakeImageHandleNonResidentNV(CPU *c) { G_glMakeImageHandleNonResidentNV(c); }
void I_glMakeImageHandleResidentNV(CPU *c) { G_glMakeImageHandleResidentNV(c); }
void I_glMakeTextureHandleNonResidentNV(CPU *c) { G_glMakeTextureHandleNonResidentNV(c); }
void I_glMakeTextureHandleResidentNV(CPU *c) { G_glMakeTextureHandleResidentNV(c); }
void I_glMapBufferOES(CPU *c) { G_glMapBufferOES(c); }
void I_glMapBufferRange(CPU *c) { G_glMapBufferRange(c); }
void I_glMapBufferRangeEXT(CPU *c) { G_glMapBufferRangeEXT(c); }
void I_glMatrixFrustumEXT(CPU *c) { G_glMatrixFrustumEXT(c); }
void I_glMatrixLoad3x2fNV(CPU *c) { G_glMatrixLoad3x2fNV(c); }
void I_glMatrixLoad3x3fNV(CPU *c) { G_glMatrixLoad3x3fNV(c); }
void I_glMatrixLoadIdentityEXT(CPU *c) { G_glMatrixLoadIdentityEXT(c); }
void I_glMatrixLoadTranspose3x3fNV(CPU *c) { G_glMatrixLoadTranspose3x3fNV(c); }
void I_glMatrixLoadTransposedEXT(CPU *c) { G_glMatrixLoadTransposedEXT(c); }
void I_glMatrixLoadTransposefEXT(CPU *c) { G_glMatrixLoadTransposefEXT(c); }
void I_glMatrixLoaddEXT(CPU *c) { G_glMatrixLoaddEXT(c); }
void I_glMatrixLoadfEXT(CPU *c) { G_glMatrixLoadfEXT(c); }
void I_glMatrixMult3x2fNV(CPU *c) { G_glMatrixMult3x2fNV(c); }
void I_glMatrixMult3x3fNV(CPU *c) { G_glMatrixMult3x3fNV(c); }
void I_glMatrixMultTranspose3x3fNV(CPU *c) { G_glMatrixMultTranspose3x3fNV(c); }
void I_glMatrixMultTransposedEXT(CPU *c) { G_glMatrixMultTransposedEXT(c); }
void I_glMatrixMultTransposefEXT(CPU *c) { G_glMatrixMultTransposefEXT(c); }
void I_glMatrixMultdEXT(CPU *c) { G_glMatrixMultdEXT(c); }
void I_glMatrixMultfEXT(CPU *c) { G_glMatrixMultfEXT(c); }
void I_glMatrixOrthoEXT(CPU *c) { G_glMatrixOrthoEXT(c); }
void I_glMatrixPopEXT(CPU *c) { G_glMatrixPopEXT(c); }
void I_glMatrixPushEXT(CPU *c) { G_glMatrixPushEXT(c); }
void I_glMatrixRotatedEXT(CPU *c) { G_glMatrixRotatedEXT(c); }
void I_glMatrixRotatefEXT(CPU *c) { G_glMatrixRotatefEXT(c); }
void I_glMatrixScaledEXT(CPU *c) { G_glMatrixScaledEXT(c); }
void I_glMatrixScalefEXT(CPU *c) { G_glMatrixScalefEXT(c); }
void I_glMatrixTranslatedEXT(CPU *c) { G_glMatrixTranslatedEXT(c); }
void I_glMatrixTranslatefEXT(CPU *c) { G_glMatrixTranslatefEXT(c); }
void I_glMaxShaderCompilerThreadsKHR(CPU *c) { G_glMaxShaderCompilerThreadsKHR(c); }
void I_glMemoryBarrier(CPU *c) { G_glMemoryBarrier(c); }
void I_glMemoryBarrierByRegion(CPU *c) { G_glMemoryBarrierByRegion(c); }
void I_glMemoryObjectParameterivEXT(CPU *c) { G_glMemoryObjectParameterivEXT(c); }
void I_glMinSampleShading(CPU *c) { G_glMinSampleShading(c); }
void I_glMinSampleShadingOES(CPU *c) { G_glMinSampleShadingOES(c); }
void I_glMultiDrawArraysEXT(CPU *c) { G_glMultiDrawArraysEXT(c); }
void I_glMultiDrawArraysIndirectEXT(CPU *c) { G_glMultiDrawArraysIndirectEXT(c); }
void I_glMultiDrawElementsBaseVertexEXT(CPU *c) { G_glMultiDrawElementsBaseVertexEXT(c); }
void I_glMultiDrawElementsEXT(CPU *c) { G_glMultiDrawElementsEXT(c); }
void I_glMultiDrawElementsIndirectEXT(CPU *c) { G_glMultiDrawElementsIndirectEXT(c); }
void I_glNamedBufferStorageExternalEXT(CPU *c) { G_glNamedBufferStorageExternalEXT(c); }
void I_glNamedBufferStorageMemEXT(CPU *c) { G_glNamedBufferStorageMemEXT(c); }
void I_glNamedFramebufferSampleLocationsfvNV(CPU *c) { G_glNamedFramebufferSampleLocationsfvNV(c); }
void I_glObjectLabel(CPU *c) { G_glObjectLabel(c); }
void I_glObjectLabelKHR(CPU *c) { G_glObjectLabelKHR(c); }
void I_glObjectPtrLabel(CPU *c) { G_glObjectPtrLabel(c); }
void I_glObjectPtrLabelKHR(CPU *c) { G_glObjectPtrLabelKHR(c); }
void I_glPatchParameteri(CPU *c) { G_glPatchParameteri(c); }
void I_glPatchParameteriEXT(CPU *c) { G_glPatchParameteriEXT(c); }
void I_glPatchParameteriOES(CPU *c) { G_glPatchParameteriOES(c); }
void I_glPathCommandsNV(CPU *c) { G_glPathCommandsNV(c); }
void I_glPathCoordsNV(CPU *c) { G_glPathCoordsNV(c); }
void I_glPathCoverDepthFuncNV(CPU *c) { G_glPathCoverDepthFuncNV(c); }
void I_glPathDashArrayNV(CPU *c) { G_glPathDashArrayNV(c); }
void I_glPathGlyphIndexArrayNV(CPU *c) { G_glPathGlyphIndexArrayNV(c); }
void I_glPathGlyphIndexRangeNV(CPU *c) { G_glPathGlyphIndexRangeNV(c); }
void I_glPathGlyphRangeNV(CPU *c) { G_glPathGlyphRangeNV(c); }
void I_glPathGlyphsNV(CPU *c) { G_glPathGlyphsNV(c); }
void I_glPathMemoryGlyphIndexArrayNV(CPU *c) { G_glPathMemoryGlyphIndexArrayNV(c); }
void I_glPathParameterfNV(CPU *c) { G_glPathParameterfNV(c); }
void I_glPathParameterfvNV(CPU *c) { G_glPathParameterfvNV(c); }
void I_glPathParameteriNV(CPU *c) { G_glPathParameteriNV(c); }
void I_glPathParameterivNV(CPU *c) { G_glPathParameterivNV(c); }
void I_glPathStencilDepthOffsetNV(CPU *c) { G_glPathStencilDepthOffsetNV(c); }
void I_glPathStencilFuncNV(CPU *c) { G_glPathStencilFuncNV(c); }
void I_glPathStringNV(CPU *c) { G_glPathStringNV(c); }
void I_glPathSubCommandsNV(CPU *c) { G_glPathSubCommandsNV(c); }
void I_glPathSubCoordsNV(CPU *c) { G_glPathSubCoordsNV(c); }
void I_glPauseTransformFeedback(CPU *c) { G_glPauseTransformFeedback(c); }
void I_glPixelStorei(CPU *c) { G_glPixelStorei(c); }
void I_glPointAlongPathNV(CPU *c) { G_glPointAlongPathNV(c); }
void I_glPolygonModeNV(CPU *c) { G_glPolygonModeNV(c); }
void I_glPolygonOffset(CPU *c) { G_glPolygonOffset(c); }
void I_glPolygonOffsetClampEXT(CPU *c) { G_glPolygonOffsetClampEXT(c); }
void I_glPopDebugGroup(CPU *c) { G_glPopDebugGroup(c); }
void I_glPopDebugGroupKHR(CPU *c) { G_glPopDebugGroupKHR(c); }
void I_glPopGroupMarkerEXT(CPU *c) { G_glPopGroupMarkerEXT(c); }
void I_glPrimitiveBoundingBox(CPU *c) { G_glPrimitiveBoundingBox(c); }
void I_glPrimitiveBoundingBoxEXT(CPU *c) { G_glPrimitiveBoundingBoxEXT(c); }
void I_glPrimitiveBoundingBoxOES(CPU *c) { G_glPrimitiveBoundingBoxOES(c); }
void I_glProgramBinary(CPU *c) { G_glProgramBinary(c); }
void I_glProgramBinaryOES(CPU *c) { G_glProgramBinaryOES(c); }
void I_glProgramParameteri(CPU *c) { G_glProgramParameteri(c); }
void I_glProgramParameteriEXT(CPU *c) { G_glProgramParameteriEXT(c); }
void I_glProgramPathFragmentInputGenNV(CPU *c) { G_glProgramPathFragmentInputGenNV(c); }
void I_glProgramUniform1f(CPU *c) { G_glProgramUniform1f(c); }
void I_glProgramUniform1fEXT(CPU *c) { G_glProgramUniform1fEXT(c); }
void I_glProgramUniform1fv(CPU *c) { G_glProgramUniform1fv(c); }
void I_glProgramUniform1fvEXT(CPU *c) { G_glProgramUniform1fvEXT(c); }
void I_glProgramUniform1i(CPU *c) { G_glProgramUniform1i(c); }
void I_glProgramUniform1i64NV(CPU *c) { G_glProgramUniform1i64NV(c); }
void I_glProgramUniform1i64vNV(CPU *c) { G_glProgramUniform1i64vNV(c); }
void I_glProgramUniform1iEXT(CPU *c) { G_glProgramUniform1iEXT(c); }
void I_glProgramUniform1iv(CPU *c) { G_glProgramUniform1iv(c); }
void I_glProgramUniform1ivEXT(CPU *c) { G_glProgramUniform1ivEXT(c); }
void I_glProgramUniform1ui(CPU *c) { G_glProgramUniform1ui(c); }
void I_glProgramUniform1ui64NV(CPU *c) { G_glProgramUniform1ui64NV(c); }
void I_glProgramUniform1ui64vNV(CPU *c) { G_glProgramUniform1ui64vNV(c); }
void I_glProgramUniform1uiEXT(CPU *c) { G_glProgramUniform1uiEXT(c); }
void I_glProgramUniform1uiv(CPU *c) { G_glProgramUniform1uiv(c); }
void I_glProgramUniform1uivEXT(CPU *c) { G_glProgramUniform1uivEXT(c); }
void I_glProgramUniform2f(CPU *c) { G_glProgramUniform2f(c); }
void I_glProgramUniform2fEXT(CPU *c) { G_glProgramUniform2fEXT(c); }
void I_glProgramUniform2fv(CPU *c) { G_glProgramUniform2fv(c); }
void I_glProgramUniform2fvEXT(CPU *c) { G_glProgramUniform2fvEXT(c); }
void I_glProgramUniform2i(CPU *c) { G_glProgramUniform2i(c); }
void I_glProgramUniform2i64NV(CPU *c) { G_glProgramUniform2i64NV(c); }
void I_glProgramUniform2i64vNV(CPU *c) { G_glProgramUniform2i64vNV(c); }
void I_glProgramUniform2iEXT(CPU *c) { G_glProgramUniform2iEXT(c); }
void I_glProgramUniform2iv(CPU *c) { G_glProgramUniform2iv(c); }
void I_glProgramUniform2ivEXT(CPU *c) { G_glProgramUniform2ivEXT(c); }
void I_glProgramUniform2ui(CPU *c) { G_glProgramUniform2ui(c); }
void I_glProgramUniform2ui64NV(CPU *c) { G_glProgramUniform2ui64NV(c); }
void I_glProgramUniform2ui64vNV(CPU *c) { G_glProgramUniform2ui64vNV(c); }
void I_glProgramUniform2uiEXT(CPU *c) { G_glProgramUniform2uiEXT(c); }
void I_glProgramUniform2uiv(CPU *c) { G_glProgramUniform2uiv(c); }
void I_glProgramUniform2uivEXT(CPU *c) { G_glProgramUniform2uivEXT(c); }
void I_glProgramUniform3f(CPU *c) { G_glProgramUniform3f(c); }
void I_glProgramUniform3fEXT(CPU *c) { G_glProgramUniform3fEXT(c); }
void I_glProgramUniform3fv(CPU *c) { G_glProgramUniform3fv(c); }
void I_glProgramUniform3fvEXT(CPU *c) { G_glProgramUniform3fvEXT(c); }
void I_glProgramUniform3i(CPU *c) { G_glProgramUniform3i(c); }
void I_glProgramUniform3i64NV(CPU *c) { G_glProgramUniform3i64NV(c); }
void I_glProgramUniform3i64vNV(CPU *c) { G_glProgramUniform3i64vNV(c); }
void I_glProgramUniform3iEXT(CPU *c) { G_glProgramUniform3iEXT(c); }
void I_glProgramUniform3iv(CPU *c) { G_glProgramUniform3iv(c); }
void I_glProgramUniform3ivEXT(CPU *c) { G_glProgramUniform3ivEXT(c); }
void I_glProgramUniform3ui(CPU *c) { G_glProgramUniform3ui(c); }
void I_glProgramUniform3ui64NV(CPU *c) { G_glProgramUniform3ui64NV(c); }
void I_glProgramUniform3ui64vNV(CPU *c) { G_glProgramUniform3ui64vNV(c); }
void I_glProgramUniform3uiEXT(CPU *c) { G_glProgramUniform3uiEXT(c); }
void I_glProgramUniform3uiv(CPU *c) { G_glProgramUniform3uiv(c); }
void I_glProgramUniform3uivEXT(CPU *c) { G_glProgramUniform3uivEXT(c); }
void I_glProgramUniform4f(CPU *c) { G_glProgramUniform4f(c); }
void I_glProgramUniform4fEXT(CPU *c) { G_glProgramUniform4fEXT(c); }
void I_glProgramUniform4fv(CPU *c) { G_glProgramUniform4fv(c); }
void I_glProgramUniform4fvEXT(CPU *c) { G_glProgramUniform4fvEXT(c); }
void I_glProgramUniform4i(CPU *c) { G_glProgramUniform4i(c); }
void I_glProgramUniform4i64NV(CPU *c) { G_glProgramUniform4i64NV(c); }
void I_glProgramUniform4i64vNV(CPU *c) { G_glProgramUniform4i64vNV(c); }
void I_glProgramUniform4iEXT(CPU *c) { G_glProgramUniform4iEXT(c); }
void I_glProgramUniform4iv(CPU *c) { G_glProgramUniform4iv(c); }
void I_glProgramUniform4ivEXT(CPU *c) { G_glProgramUniform4ivEXT(c); }
void I_glProgramUniform4ui(CPU *c) { G_glProgramUniform4ui(c); }
void I_glProgramUniform4ui64NV(CPU *c) { G_glProgramUniform4ui64NV(c); }
void I_glProgramUniform4ui64vNV(CPU *c) { G_glProgramUniform4ui64vNV(c); }
void I_glProgramUniform4uiEXT(CPU *c) { G_glProgramUniform4uiEXT(c); }
void I_glProgramUniform4uiv(CPU *c) { G_glProgramUniform4uiv(c); }
void I_glProgramUniform4uivEXT(CPU *c) { G_glProgramUniform4uivEXT(c); }
void I_glProgramUniformHandleui64IMG(CPU *c) { G_glProgramUniformHandleui64IMG(c); }
void I_glProgramUniformHandleui64NV(CPU *c) { G_glProgramUniformHandleui64NV(c); }
void I_glProgramUniformHandleui64vIMG(CPU *c) { G_glProgramUniformHandleui64vIMG(c); }
void I_glProgramUniformHandleui64vNV(CPU *c) { G_glProgramUniformHandleui64vNV(c); }
void I_glProgramUniformMatrix2fv(CPU *c) { G_glProgramUniformMatrix2fv(c); }
void I_glProgramUniformMatrix2fvEXT(CPU *c) { G_glProgramUniformMatrix2fvEXT(c); }
void I_glProgramUniformMatrix2x3fv(CPU *c) { G_glProgramUniformMatrix2x3fv(c); }
void I_glProgramUniformMatrix2x3fvEXT(CPU *c) { G_glProgramUniformMatrix2x3fvEXT(c); }
void I_glProgramUniformMatrix2x4fv(CPU *c) { G_glProgramUniformMatrix2x4fv(c); }
void I_glProgramUniformMatrix2x4fvEXT(CPU *c) { G_glProgramUniformMatrix2x4fvEXT(c); }
void I_glProgramUniformMatrix3fv(CPU *c) { G_glProgramUniformMatrix3fv(c); }
void I_glProgramUniformMatrix3fvEXT(CPU *c) { G_glProgramUniformMatrix3fvEXT(c); }
void I_glProgramUniformMatrix3x2fv(CPU *c) { G_glProgramUniformMatrix3x2fv(c); }
void I_glProgramUniformMatrix3x2fvEXT(CPU *c) { G_glProgramUniformMatrix3x2fvEXT(c); }
void I_glProgramUniformMatrix3x4fv(CPU *c) { G_glProgramUniformMatrix3x4fv(c); }
void I_glProgramUniformMatrix3x4fvEXT(CPU *c) { G_glProgramUniformMatrix3x4fvEXT(c); }
void I_glProgramUniformMatrix4fv(CPU *c) { G_glProgramUniformMatrix4fv(c); }
void I_glProgramUniformMatrix4fvEXT(CPU *c) { G_glProgramUniformMatrix4fvEXT(c); }
void I_glProgramUniformMatrix4x2fv(CPU *c) { G_glProgramUniformMatrix4x2fv(c); }
void I_glProgramUniformMatrix4x2fvEXT(CPU *c) { G_glProgramUniformMatrix4x2fvEXT(c); }
void I_glProgramUniformMatrix4x3fv(CPU *c) { G_glProgramUniformMatrix4x3fv(c); }
void I_glProgramUniformMatrix4x3fvEXT(CPU *c) { G_glProgramUniformMatrix4x3fvEXT(c); }
void I_glPushDebugGroup(CPU *c) { G_glPushDebugGroup(c); }
void I_glPushDebugGroupKHR(CPU *c) { G_glPushDebugGroupKHR(c); }
void I_glPushGroupMarkerEXT(CPU *c) { G_glPushGroupMarkerEXT(c); }
void I_glQueryCounterEXT(CPU *c) { G_glQueryCounterEXT(c); }
void I_glRasterSamplesEXT(CPU *c) { G_glRasterSamplesEXT(c); }
void I_glReadBuffer(CPU *c) { G_glReadBuffer(c); }
void I_glReadBufferIndexedEXT(CPU *c) { G_glReadBufferIndexedEXT(c); }
void I_glReadBufferNV(CPU *c) { G_glReadBufferNV(c); }
void I_glReadPixels(CPU *c) { G_glReadPixels(c); }
void I_glReadnPixels(CPU *c) { G_glReadnPixels(c); }
void I_glReadnPixelsEXT(CPU *c) { G_glReadnPixelsEXT(c); }
void I_glReadnPixelsKHR(CPU *c) { G_glReadnPixelsKHR(c); }
void I_glReleaseKeyedMutexWin32EXT(CPU *c) { G_glReleaseKeyedMutexWin32EXT(c); }
void I_glReleaseShaderCompiler(CPU *c) { G_glReleaseShaderCompiler(c); }
void I_glRenderbufferStorage(CPU *c) { G_glRenderbufferStorage(c); }
void I_glRenderbufferStorageMultisample(CPU *c) { G_glRenderbufferStorageMultisample(c); }
void I_glRenderbufferStorageMultisampleANGLE(CPU *c) { G_glRenderbufferStorageMultisampleANGLE(c); }
void I_glRenderbufferStorageMultisampleAPPLE(CPU *c) { G_glRenderbufferStorageMultisampleAPPLE(c); }
void I_glRenderbufferStorageMultisampleEXT(CPU *c) { G_glRenderbufferStorageMultisampleEXT(c); }
void I_glRenderbufferStorageMultisampleIMG(CPU *c) { G_glRenderbufferStorageMultisampleIMG(c); }
void I_glRenderbufferStorageMultisampleNV(CPU *c) { G_glRenderbufferStorageMultisampleNV(c); }
void I_glResolveDepthValuesNV(CPU *c) { G_glResolveDepthValuesNV(c); }
void I_glResolveMultisampleFramebufferAPPLE(CPU *c) { G_glResolveMultisampleFramebufferAPPLE(c); }
void I_glResumeTransformFeedback(CPU *c) { G_glResumeTransformFeedback(c); }
void I_glSampleCoverage(CPU *c) { G_glSampleCoverage(c); }
void I_glSampleMaski(CPU *c) { G_glSampleMaski(c); }
void I_glSamplerParameterIiv(CPU *c) { G_glSamplerParameterIiv(c); }
void I_glSamplerParameterIivEXT(CPU *c) { G_glSamplerParameterIivEXT(c); }
void I_glSamplerParameterIivOES(CPU *c) { G_glSamplerParameterIivOES(c); }
void I_glSamplerParameterIuiv(CPU *c) { G_glSamplerParameterIuiv(c); }
void I_glSamplerParameterIuivEXT(CPU *c) { G_glSamplerParameterIuivEXT(c); }
void I_glSamplerParameterIuivOES(CPU *c) { G_glSamplerParameterIuivOES(c); }
void I_glSamplerParameterf(CPU *c) { G_glSamplerParameterf(c); }
void I_glSamplerParameterfv(CPU *c) { G_glSamplerParameterfv(c); }
void I_glSamplerParameteri(CPU *c) { G_glSamplerParameteri(c); }
void I_glSamplerParameteriv(CPU *c) { G_glSamplerParameteriv(c); }
void I_glScissor(CPU *c) { G_glScissor(c); }
void I_glScissorArrayvNV(CPU *c) { G_glScissorArrayvNV(c); }
void I_glScissorArrayvOES(CPU *c) { G_glScissorArrayvOES(c); }
void I_glScissorIndexedNV(CPU *c) { G_glScissorIndexedNV(c); }
void I_glScissorIndexedOES(CPU *c) { G_glScissorIndexedOES(c); }
void I_glScissorIndexedvNV(CPU *c) { G_glScissorIndexedvNV(c); }
void I_glScissorIndexedvOES(CPU *c) { G_glScissorIndexedvOES(c); }
void I_glSelectPerfMonitorCountersAMD(CPU *c) { G_glSelectPerfMonitorCountersAMD(c); }
void I_glSemaphoreParameterui64vEXT(CPU *c) { G_glSemaphoreParameterui64vEXT(c); }
void I_glSetFenceNV(CPU *c) { G_glSetFenceNV(c); }
void I_glShaderBinary(CPU *c) { G_glShaderBinary(c); }
void I_glShaderSource(CPU *c) { G_glShaderSource(c); }
void I_glSignalSemaphoreEXT(CPU *c) { G_glSignalSemaphoreEXT(c); }
void I_glSignalVkFenceNV(CPU *c) { G_glSignalVkFenceNV(c); }
void I_glSignalVkSemaphoreNV(CPU *c) { G_glSignalVkSemaphoreNV(c); }
void I_glStartTilingQCOM(CPU *c) { G_glStartTilingQCOM(c); }
void I_glStencilFillPathInstancedNV(CPU *c) { G_glStencilFillPathInstancedNV(c); }
void I_glStencilFillPathNV(CPU *c) { G_glStencilFillPathNV(c); }
void I_glStencilFunc(CPU *c) { G_glStencilFunc(c); }
void I_glStencilFuncSeparate(CPU *c) { G_glStencilFuncSeparate(c); }
void I_glStencilMask(CPU *c) { G_glStencilMask(c); }
void I_glStencilMaskSeparate(CPU *c) { G_glStencilMaskSeparate(c); }
void I_glStencilOp(CPU *c) { G_glStencilOp(c); }
void I_glStencilOpSeparate(CPU *c) { G_glStencilOpSeparate(c); }
void I_glStencilStrokePathInstancedNV(CPU *c) { G_glStencilStrokePathInstancedNV(c); }
void I_glStencilStrokePathNV(CPU *c) { G_glStencilStrokePathNV(c); }
void I_glStencilThenCoverFillPathInstancedNV(CPU *c) { G_glStencilThenCoverFillPathInstancedNV(c); }
void I_glStencilThenCoverFillPathNV(CPU *c) { G_glStencilThenCoverFillPathNV(c); }
void I_glStencilThenCoverStrokePathInstancedNV(CPU *c) { G_glStencilThenCoverStrokePathInstancedNV(c); }
void I_glStencilThenCoverStrokePathNV(CPU *c) { G_glStencilThenCoverStrokePathNV(c); }
void I_glSubpixelPrecisionBiasNV(CPU *c) { G_glSubpixelPrecisionBiasNV(c); }
void I_glTestFenceNV(CPU *c) { G_glTestFenceNV(c); }
void I_glTexBuffer(CPU *c) { G_glTexBuffer(c); }
void I_glTexBufferEXT(CPU *c) { G_glTexBufferEXT(c); }
void I_glTexBufferOES(CPU *c) { G_glTexBufferOES(c); }
void I_glTexBufferRange(CPU *c) { G_glTexBufferRange(c); }
void I_glTexBufferRangeEXT(CPU *c) { G_glTexBufferRangeEXT(c); }
void I_glTexBufferRangeOES(CPU *c) { G_glTexBufferRangeOES(c); }
void I_glTexImage2D(CPU *c) { G_glTexImage2D(c); }
void I_glTexImage3D(CPU *c) { G_glTexImage3D(c); }
void I_glTexImage3DOES(CPU *c) { G_glTexImage3DOES(c); }
void I_glTexPageCommitmentEXT(CPU *c) { G_glTexPageCommitmentEXT(c); }
void I_glTexParameterIiv(CPU *c) { G_glTexParameterIiv(c); }
void I_glTexParameterIivEXT(CPU *c) { G_glTexParameterIivEXT(c); }
void I_glTexParameterIivOES(CPU *c) { G_glTexParameterIivOES(c); }
void I_glTexParameterIuiv(CPU *c) { G_glTexParameterIuiv(c); }
void I_glTexParameterIuivEXT(CPU *c) { G_glTexParameterIuivEXT(c); }
void I_glTexParameterIuivOES(CPU *c) { G_glTexParameterIuivOES(c); }
void I_glTexParameterf(CPU *c) { G_glTexParameterf(c); }
void I_glTexParameterfv(CPU *c) { G_glTexParameterfv(c); }
void I_glTexParameteri(CPU *c) { G_glTexParameteri(c); }
void I_glTexParameteriv(CPU *c) { G_glTexParameteriv(c); }
void I_glTexStorage1DEXT(CPU *c) { G_glTexStorage1DEXT(c); }
void I_glTexStorage2D(CPU *c) { G_glTexStorage2D(c); }
void I_glTexStorage2DEXT(CPU *c) { G_glTexStorage2DEXT(c); }
void I_glTexStorage2DMultisample(CPU *c) { G_glTexStorage2DMultisample(c); }
void I_glTexStorage3D(CPU *c) { G_glTexStorage3D(c); }
void I_glTexStorage3DEXT(CPU *c) { G_glTexStorage3DEXT(c); }
void I_glTexStorage3DMultisample(CPU *c) { G_glTexStorage3DMultisample(c); }
void I_glTexStorage3DMultisampleOES(CPU *c) { G_glTexStorage3DMultisampleOES(c); }
void I_glTexStorageMem2DEXT(CPU *c) { G_glTexStorageMem2DEXT(c); }
void I_glTexStorageMem2DMultisampleEXT(CPU *c) { G_glTexStorageMem2DMultisampleEXT(c); }
void I_glTexStorageMem3DEXT(CPU *c) { G_glTexStorageMem3DEXT(c); }
void I_glTexStorageMem3DMultisampleEXT(CPU *c) { G_glTexStorageMem3DMultisampleEXT(c); }
void I_glTexSubImage2D(CPU *c) { G_glTexSubImage2D(c); }
void I_glTexSubImage3D(CPU *c) { G_glTexSubImage3D(c); }
void I_glTexSubImage3DOES(CPU *c) { G_glTexSubImage3DOES(c); }
void I_glTextureFoveationParametersQCOM(CPU *c) { G_glTextureFoveationParametersQCOM(c); }
void I_glTextureStorage1DEXT(CPU *c) { G_glTextureStorage1DEXT(c); }
void I_glTextureStorage2DEXT(CPU *c) { G_glTextureStorage2DEXT(c); }
void I_glTextureStorage3DEXT(CPU *c) { G_glTextureStorage3DEXT(c); }
void I_glTextureStorageMem2DEXT(CPU *c) { G_glTextureStorageMem2DEXT(c); }
void I_glTextureStorageMem2DMultisampleEXT(CPU *c) { G_glTextureStorageMem2DMultisampleEXT(c); }
void I_glTextureStorageMem3DEXT(CPU *c) { G_glTextureStorageMem3DEXT(c); }
void I_glTextureStorageMem3DMultisampleEXT(CPU *c) { G_glTextureStorageMem3DMultisampleEXT(c); }
void I_glTextureViewEXT(CPU *c) { G_glTextureViewEXT(c); }
void I_glTextureViewOES(CPU *c) { G_glTextureViewOES(c); }
void I_glTransformFeedbackVaryings(CPU *c) { G_glTransformFeedbackVaryings(c); }
void I_glTransformPathNV(CPU *c) { G_glTransformPathNV(c); }
void I_glUniform1f(CPU *c) { G_glUniform1f(c); }
void I_glUniform1fv(CPU *c) { G_glUniform1fv(c); }
void I_glUniform1i(CPU *c) { G_glUniform1i(c); }
void I_glUniform1i64NV(CPU *c) { G_glUniform1i64NV(c); }
void I_glUniform1i64vNV(CPU *c) { G_glUniform1i64vNV(c); }
void I_glUniform1iv(CPU *c) { G_glUniform1iv(c); }
void I_glUniform1ui(CPU *c) { G_glUniform1ui(c); }
void I_glUniform1ui64NV(CPU *c) { G_glUniform1ui64NV(c); }
void I_glUniform1ui64vNV(CPU *c) { G_glUniform1ui64vNV(c); }
void I_glUniform1uiv(CPU *c) { G_glUniform1uiv(c); }
void I_glUniform2f(CPU *c) { G_glUniform2f(c); }
void I_glUniform2fv(CPU *c) { G_glUniform2fv(c); }
void I_glUniform2i(CPU *c) { G_glUniform2i(c); }
void I_glUniform2i64NV(CPU *c) { G_glUniform2i64NV(c); }
void I_glUniform2i64vNV(CPU *c) { G_glUniform2i64vNV(c); }
void I_glUniform2iv(CPU *c) { G_glUniform2iv(c); }
void I_glUniform2ui(CPU *c) { G_glUniform2ui(c); }
void I_glUniform2ui64NV(CPU *c) { G_glUniform2ui64NV(c); }
void I_glUniform2ui64vNV(CPU *c) { G_glUniform2ui64vNV(c); }
void I_glUniform2uiv(CPU *c) { G_glUniform2uiv(c); }
void I_glUniform3f(CPU *c) { G_glUniform3f(c); }
void I_glUniform3fv(CPU *c) { G_glUniform3fv(c); }
void I_glUniform3i(CPU *c) { G_glUniform3i(c); }
void I_glUniform3i64NV(CPU *c) { G_glUniform3i64NV(c); }
void I_glUniform3i64vNV(CPU *c) { G_glUniform3i64vNV(c); }
void I_glUniform3iv(CPU *c) { G_glUniform3iv(c); }
void I_glUniform3ui(CPU *c) { G_glUniform3ui(c); }
void I_glUniform3ui64NV(CPU *c) { G_glUniform3ui64NV(c); }
void I_glUniform3ui64vNV(CPU *c) { G_glUniform3ui64vNV(c); }
void I_glUniform3uiv(CPU *c) { G_glUniform3uiv(c); }
void I_glUniform4f(CPU *c) { G_glUniform4f(c); }
void I_glUniform4fv(CPU *c) { G_glUniform4fv(c); }
void I_glUniform4i(CPU *c) { G_glUniform4i(c); }
void I_glUniform4i64NV(CPU *c) { G_glUniform4i64NV(c); }
void I_glUniform4i64vNV(CPU *c) { G_glUniform4i64vNV(c); }
void I_glUniform4iv(CPU *c) { G_glUniform4iv(c); }
void I_glUniform4ui(CPU *c) { G_glUniform4ui(c); }
void I_glUniform4ui64NV(CPU *c) { G_glUniform4ui64NV(c); }
void I_glUniform4ui64vNV(CPU *c) { G_glUniform4ui64vNV(c); }
void I_glUniform4uiv(CPU *c) { G_glUniform4uiv(c); }
void I_glUniformBlockBinding(CPU *c) { G_glUniformBlockBinding(c); }
void I_glUniformHandleui64IMG(CPU *c) { G_glUniformHandleui64IMG(c); }
void I_glUniformHandleui64NV(CPU *c) { G_glUniformHandleui64NV(c); }
void I_glUniformHandleui64vIMG(CPU *c) { G_glUniformHandleui64vIMG(c); }
void I_glUniformHandleui64vNV(CPU *c) { G_glUniformHandleui64vNV(c); }
void I_glUniformMatrix2fv(CPU *c) { G_glUniformMatrix2fv(c); }
void I_glUniformMatrix2x3fv(CPU *c) { G_glUniformMatrix2x3fv(c); }
void I_glUniformMatrix2x3fvNV(CPU *c) { G_glUniformMatrix2x3fvNV(c); }
void I_glUniformMatrix2x4fv(CPU *c) { G_glUniformMatrix2x4fv(c); }
void I_glUniformMatrix2x4fvNV(CPU *c) { G_glUniformMatrix2x4fvNV(c); }
void I_glUniformMatrix3fv(CPU *c) { G_glUniformMatrix3fv(c); }
void I_glUniformMatrix3x2fv(CPU *c) { G_glUniformMatrix3x2fv(c); }
void I_glUniformMatrix3x2fvNV(CPU *c) { G_glUniformMatrix3x2fvNV(c); }
void I_glUniformMatrix3x4fv(CPU *c) { G_glUniformMatrix3x4fv(c); }
void I_glUniformMatrix3x4fvNV(CPU *c) { G_glUniformMatrix3x4fvNV(c); }
void I_glUniformMatrix4fv(CPU *c) { G_glUniformMatrix4fv(c); }
void I_glUniformMatrix4x2fv(CPU *c) { G_glUniformMatrix4x2fv(c); }
void I_glUniformMatrix4x2fvNV(CPU *c) { G_glUniformMatrix4x2fvNV(c); }
void I_glUniformMatrix4x3fv(CPU *c) { G_glUniformMatrix4x3fv(c); }
void I_glUniformMatrix4x3fvNV(CPU *c) { G_glUniformMatrix4x3fvNV(c); }
void I_glUnmapBuffer(CPU *c) { G_glUnmapBuffer(c); }
void I_glUnmapBufferOES(CPU *c) { G_glUnmapBufferOES(c); }
void I_glUseProgram(CPU *c) { G_glUseProgram(c); }
void I_glUseProgramStages(CPU *c) { G_glUseProgramStages(c); }
void I_glUseProgramStagesEXT(CPU *c) { G_glUseProgramStagesEXT(c); }
void I_glValidateProgram(CPU *c) { G_glValidateProgram(c); }
void I_glValidateProgramPipeline(CPU *c) { G_glValidateProgramPipeline(c); }
void I_glValidateProgramPipelineEXT(CPU *c) { G_glValidateProgramPipelineEXT(c); }
void I_glVertexAttrib1f(CPU *c) { G_glVertexAttrib1f(c); }
void I_glVertexAttrib1fv(CPU *c) { G_glVertexAttrib1fv(c); }
void I_glVertexAttrib2f(CPU *c) { G_glVertexAttrib2f(c); }
void I_glVertexAttrib2fv(CPU *c) { G_glVertexAttrib2fv(c); }
void I_glVertexAttrib3f(CPU *c) { G_glVertexAttrib3f(c); }
void I_glVertexAttrib3fv(CPU *c) { G_glVertexAttrib3fv(c); }
void I_glVertexAttrib4f(CPU *c) { G_glVertexAttrib4f(c); }
void I_glVertexAttrib4fv(CPU *c) { G_glVertexAttrib4fv(c); }
void I_glVertexAttribBinding(CPU *c) { G_glVertexAttribBinding(c); }
void I_glVertexAttribDivisor(CPU *c) { G_glVertexAttribDivisor(c); }
void I_glVertexAttribDivisorANGLE(CPU *c) { G_glVertexAttribDivisorANGLE(c); }
void I_glVertexAttribDivisorEXT(CPU *c) { G_glVertexAttribDivisorEXT(c); }
void I_glVertexAttribDivisorNV(CPU *c) { G_glVertexAttribDivisorNV(c); }
void I_glVertexAttribFormat(CPU *c) { G_glVertexAttribFormat(c); }
void I_glVertexAttribI4i(CPU *c) { G_glVertexAttribI4i(c); }
void I_glVertexAttribI4iv(CPU *c) { G_glVertexAttribI4iv(c); }
void I_glVertexAttribI4ui(CPU *c) { G_glVertexAttribI4ui(c); }
void I_glVertexAttribI4uiv(CPU *c) { G_glVertexAttribI4uiv(c); }
void I_glVertexAttribIFormat(CPU *c) { G_glVertexAttribIFormat(c); }
void I_glVertexAttribIPointer(CPU *c) { G_glVertexAttribIPointer(c); }
void I_glVertexAttribPointer(CPU *c) { G_glVertexAttribPointer(c); }
void I_glVertexBindingDivisor(CPU *c) { G_glVertexBindingDivisor(c); }
void I_glViewport(CPU *c) { G_glViewport(c); }
void I_glViewportArrayvNV(CPU *c) { G_glViewportArrayvNV(c); }
void I_glViewportArrayvOES(CPU *c) { G_glViewportArrayvOES(c); }
void I_glViewportIndexedfNV(CPU *c) { G_glViewportIndexedfNV(c); }
void I_glViewportIndexedfOES(CPU *c) { G_glViewportIndexedfOES(c); }
void I_glViewportIndexedfvNV(CPU *c) { G_glViewportIndexedfvNV(c); }
void I_glViewportIndexedfvOES(CPU *c) { G_glViewportIndexedfvOES(c); }
void I_glViewportPositionWScaleNV(CPU *c) { G_glViewportPositionWScaleNV(c); }
void I_glViewportSwizzleNV(CPU *c) { G_glViewportSwizzleNV(c); }
void I_glWaitSemaphoreEXT(CPU *c) { G_glWaitSemaphoreEXT(c); }
void I_glWaitSync(CPU *c) { G_glWaitSync(c); }
void I_glWaitSyncAPPLE(CPU *c) { G_glWaitSyncAPPLE(c); }
void I_glWaitVkSemaphoreNV(CPU *c) { G_glWaitVkSemaphoreNV(c); }
void I_glWeightPathsNV(CPU *c) { G_glWeightPathsNV(c); }
void I_glWindowRectanglesEXT(CPU *c) { G_glWindowRectanglesEXT(c); }
#endif