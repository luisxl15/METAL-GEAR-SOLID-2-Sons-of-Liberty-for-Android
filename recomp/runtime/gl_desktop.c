/* OpenGL de DESKTOP sobre GLES 3.2.
 *
 * A camada D3D9->GL da TransGaming (dentro do libMGS2HD.so) pede EGL_OPENGL_API,
 * como no Tegra do SHIELD, que tem OpenGL completo. A Adreno so tem GLES; o
 * eglBindAPI/eglCreateContext trocam para GLES 3.2 (gl_manual.c) e aqui ficam as
 * funcoes de desktop que a camada procura por nome.
 *
 * Regra: so as funcoes do NUCLEO (sem sufixo) ganham ponte. A camada trata essas
 * como obrigatorias (chama sem testar NULL). As de extensao (ARB/NV/APPLE/...)
 * continuam NULL, para a camada nao escolher caminhos que o GLES nao tem.
 *   - com equivalente: implementadas;
 *   - sem equivalente (pipeline fixo, etc.): viram nada, e a PRIMEIRA chamada de
 *     cada uma vai para o log, para sabermos se alguma importa. */
#ifndef _WIN32
#include "gl_ponte.h"
#include <GLES2/gl2ext.h>
#include <string.h>
#include <stdlib.h>

void G_glMapBufferOES(CPU *c);
void G_glBufferStorageEXT(CPU *c);

#define AVISA(nome) do { static int _v; if (!__atomic_exchange_n(&_v, 1, __ATOMIC_RELAXED)) rt_log("GL desktop chamado: %s", nome); } while (0)

/* ---- com equivalente ----------------------------------------------------- */
static void D_glClearDepth(CPU *c) { Args a = args_de(c); glClearDepthf((GLfloat)argd(&a)); }
static void D_glDepthRange(CPU *c) { Args a = args_de(c); double n = argd(&a), f = argd(&a); glDepthRangef((GLfloat)n, (GLfloat)f); }
static void D_glDrawBuffer(CPU *c) {
    GLenum m = c->r[0];
    GLint fbo = 0; glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &fbo);
    if (!fbo) { if (m == GL_FRONT || m == 0x0402 /* BACK_LEFT */ || m == 0x0400 /* FRONT_LEFT */) m = GL_BACK; if (m != GL_BACK && m != GL_NONE) m = GL_BACK; }
    else if (m != GL_NONE && (m < GL_COLOR_ATTACHMENT0 || m > GL_COLOR_ATTACHMENT0 + 15)) m = GL_COLOR_ATTACHMENT0;
    if (fbo && m >= GL_COLOR_ATTACHMENT0 && m <= GL_COLOR_ATTACHMENT0 + 15) {
        /* GLES: o i-esimo item tem de ser COLOR_ATTACHMENTi */
        GLenum v[16]; int k = (int)(m - GL_COLOR_ATTACHMENT0);
        for (int i = 0; i < k; i++) v[i] = GL_NONE;
        v[k] = m;
        glDrawBuffers(k + 1, v);
    } else glDrawBuffers(1, &m);
}
static void D_glMapBuffer(CPU *c) {
    G_glMapBufferOES(c);   /* mapeia o buffer inteiro (leitura e escrita, copia na memoria do jogo) */
}
static void D_glGetBufferSubData(CPU *c) {
    GLenum t = c->r[0]; GLintptr o = (GLintptr)(int32_t)c->r[1]; GLsizeiptr n = (GLsizeiptr)(int32_t)c->r[2];
    void *p = glMapBufferRange(t, o, n, GL_MAP_READ_BIT);
    if (p) { memcpy(g_mem + c->r[3], p, (size_t)n); glUnmapBuffer(t); }
}
static void D_glGetQueryObjectiv(CPU *c) { GLuint v = 0; glGetQueryObjectuiv(c->r[0], c->r[1], &v); memcpy(g_mem + c->r[2], &v, 4); }
static void D_glGetQueryObjectui64v(CPU *c) { GLuint v = 0; glGetQueryObjectuiv(c->r[0], c->r[1], &v); uint64_t w = v; memcpy(g_mem + c->r[2], &w, 8); }
static void D_glGetDoublev(CPU *c) {
    GLfloat f[16]; for (int i = 0; i < 16; i++) f[i] = 0;
    glGetFloatv(c->r[0], f);
    double d[16]; for (int i = 0; i < 16; i++) d[i] = f[i];
    /* sem saber quantos a enum devolve: copia 1 (as que a camada pede sao escalares) */
    memcpy(g_mem + c->r[1], d, 8);
}
static void D_glBufferStorage(CPU *c) { G_glBufferStorageEXT(c); }
static void D_glFramebufferTexture3D(CPU *c) {
    Args a = args_de(c);
    GLenum t = arg32(&a), at = arg32(&a), tt = arg32(&a); GLuint tex = arg32(&a); GLint lv = (GLint)arg32(&a), z = (GLint)arg32(&a);
    (void)tt; glFramebufferTextureLayer(t, at, tex, lv, z);
}
static void D_glGetActiveUniformName(CPU *c) {
    Args a = args_de(c);
    GLuint p = arg32(&a), i = arg32(&a); GLsizei n = (GLsizei)arg32(&a); uint32_t len = arg32(&a), nome = arg32(&a);
    GLint tam; GLenum tipo; GLsizei l = 0;
    glGetActiveUniform(p, i, n, &l, &tam, &tipo, G2H(nome));
    if (len) memcpy(g_mem + len, &l, 4);
}
static void D_glVertexAttrib4Nub(CPU *c) {
    Args a = args_de(c); GLuint i = arg32(&a);
    float v[4]; for (int k = 0; k < 4; k++) v[k] = (float)(arg32(&a) & 0xff) / 255.0f;
    glVertexAttrib4fv(i, v);
}
static void D_glVertexAttrib4Nubv(CPU *c) {
    const uint8_t *s = g_mem + c->r[1]; float v[4]; for (int k = 0; k < 4; k++) v[k] = s[k] / 255.0f;
    glVertexAttrib4fv(c->r[0], v);
}
static void D_glVertexAttrib4ubv(CPU *c) {
    const uint8_t *s = g_mem + c->r[1]; float v[4]; for (int k = 0; k < 4; k++) v[k] = s[k];
    glVertexAttrib4fv(c->r[0], v);
}
static void D_glVertexAttrib4dv(CPU *c) {
    double d[4]; memcpy(d, g_mem + c->r[1], 32); float v[4] = { (float)d[0], (float)d[1], (float)d[2], (float)d[3] };
    glVertexAttrib4fv(c->r[0], v);
}
static void D_glVertexAttrib4sv(CPU *c) {
    int16_t s[4]; memcpy(s, g_mem + c->r[1], 8); float v[4] = { s[0], s[1], s[2], s[3] };
    glVertexAttrib4fv(c->r[0], v);
}
static void D_glVertexAttrib4Nsv(CPU *c) {
    int16_t s[4]; memcpy(s, g_mem + c->r[1], 8); float v[4];
    for (int k = 0; k < 4; k++) { v[k] = s[k] / 32767.0f; if (v[k] < -1) v[k] = -1; }
    glVertexAttrib4fv(c->r[0], v);
}
/* estados sem efeito no GLES (valor padrao do GL igual ao do GLES ou irrelevante) */
static void D_glPolygonMode(CPU *c) { if (c->r[1] != 0x1B02 /* GL_FILL */) AVISA("glPolygonMode (nao FILL)"); }
static void D_glClampColor(CPU *c) { (void)c; }
static void D_glPointSize(CPU *c) { (void)c; }
static void D_glProvokingVertex(CPU *c) { if (c->r[0] != 0x8E4E /* LAST */) AVISA("glProvokingVertex(FIRST)"); }
static void D_glPointParameterf(CPU *c) { (void)c; }
static void D_glPointParameterfv(CPU *c) { (void)c; }

/* ---- sem equivalente: registra a primeira chamada ------------------------ */
#define SEM(n) static void D_##n(CPU *c) { AVISA(#n); ret32(c, 0); }
#define SEM_LISTA(X) \
    X(glAlphaFunc) X(glArrayElement) X(glBegin) X(glEnd) X(glClientActiveTexture) X(glClipPlane) \
    X(glColor4f) X(glColor4ubv) X(glColorMaterial) X(glColorPointer) X(glColorTable) \
    X(glCompressedTexImage1D) X(glCompressedTexSubImage1D) X(glDisableClientState) X(glEnableClientState) \
    X(glDrawPixels) X(glFogCoordPointer) X(glFogCoordf) X(glFogf) X(glFogfv) X(glFramebufferTexture1D) \
    X(glGetCompressedTexImage) X(glGetTexEnviv) X(glGetTexImage) X(glGetVertexAttribdv) \
    X(glGetQueryObjecti64v) X(glQueryCounter) \
    X(glLightModelf) X(glLightModelfv) X(glLightModeli) X(glLightf) X(glLightfv) \
    X(glLoadIdentity) X(glLoadMatrixf) X(glLoadTransposeMatrixd) X(glLoadTransposeMatrixf) \
    X(glMaterialf) X(glMaterialfv) X(glMatrixMode) X(glMultTransposeMatrixd) X(glMultTransposeMatrixf) \
    X(glNormal3f) X(glNormalPointer) X(glOrtho) X(glPixelMapfv) X(glPixelZoom) \
    X(glPopAttrib) X(glPopClientAttrib) X(glPopMatrix) X(glPushAttrib) X(glPushClientAttrib) X(glPushMatrix) \
    X(glRasterPos2i) X(glSecondaryColor3f) X(glSecondaryColor3ub) X(glSecondaryColorPointer) X(glShadeModel) \
    X(glTexCoord2f) X(glTexCoord4f) X(glTexCoordPointer) X(glTexEnvfv) X(glTexEnvi) X(glTexGenfv) X(glTexGeni) \
    X(glVertex2f) X(glVertexPointer) X(glClipPlanef) X(glShaderStorageBlockBinding) \
    X(glGetProgramResourceLocationIndex) \
    X(glMultiTexCoord1d) X(glMultiTexCoord1dv) X(glMultiTexCoord1f) X(glMultiTexCoord1fv) X(glMultiTexCoord1i) X(glMultiTexCoord1iv) X(glMultiTexCoord1s) X(glMultiTexCoord1sv) \
    X(glMultiTexCoord2d) X(glMultiTexCoord2dv) X(glMultiTexCoord2f) X(glMultiTexCoord2fv) X(glMultiTexCoord2i) X(glMultiTexCoord2iv) X(glMultiTexCoord2s) X(glMultiTexCoord2sv) \
    X(glMultiTexCoord3d) X(glMultiTexCoord3dv) X(glMultiTexCoord3f) X(glMultiTexCoord3fv) X(glMultiTexCoord3i) X(glMultiTexCoord3iv) X(glMultiTexCoord3s) X(glMultiTexCoord3sv) \
    X(glMultiTexCoord4d) X(glMultiTexCoord4dv) X(glMultiTexCoord4f) X(glMultiTexCoord4fv) X(glMultiTexCoord4i) X(glMultiTexCoord4iv) X(glMultiTexCoord4s) X(glMultiTexCoord4sv) \
    X(glProgramUniform1d) X(glProgramUniform1dv) X(glProgramUniform2d) X(glProgramUniform2dv) X(glProgramUniform3d) X(glProgramUniform3dv) X(glProgramUniform4d) X(glProgramUniform4dv) \
    X(glProgramUniformMatrix2dv) X(glProgramUniformMatrix2x3dv) X(glProgramUniformMatrix2x4dv) X(glProgramUniformMatrix3dv) X(glProgramUniformMatrix3x2dv) \
    X(glProgramUniformMatrix3x4dv) X(glProgramUniformMatrix4dv) X(glProgramUniformMatrix4x2dv) X(glProgramUniformMatrix4x3dv) \
    X(glVertexAttrib1d) X(glVertexAttrib1dv) X(glVertexAttrib1s) X(glVertexAttrib1sv) X(glVertexAttrib2d) X(glVertexAttrib2dv) X(glVertexAttrib2s) X(glVertexAttrib2sv) \
    X(glVertexAttrib3d) X(glVertexAttrib3dv) X(glVertexAttrib3s) X(glVertexAttrib3sv) X(glVertexAttrib4Nbv) X(glVertexAttrib4Niv) X(glVertexAttrib4Nuiv) \
    X(glVertexAttrib4Nusv) X(glVertexAttrib4bv) X(glVertexAttrib4d) X(glVertexAttrib4iv) X(glVertexAttrib4s) X(glVertexAttrib4uiv) X(glVertexAttrib4usv)
SEM_LISTA(SEM)

static const struct { const char *nome; Ponte fn; } tabela[] = {
#define ITEM(n) { #n, D_##n },
    ITEM(glClearDepth) ITEM(glDepthRange) ITEM(glDrawBuffer) ITEM(glMapBuffer) ITEM(glGetBufferSubData)
    ITEM(glGetQueryObjectiv) ITEM(glGetQueryObjectui64v) ITEM(glGetDoublev) ITEM(glBufferStorage)
    ITEM(glFramebufferTexture3D) ITEM(glGetActiveUniformName)
    ITEM(glVertexAttrib4Nub) ITEM(glVertexAttrib4Nubv) ITEM(glVertexAttrib4ubv) ITEM(glVertexAttrib4dv)
    ITEM(glVertexAttrib4sv) ITEM(glVertexAttrib4Nsv)
    ITEM(glPolygonMode) ITEM(glClampColor) ITEM(glPointSize) ITEM(glProvokingVertex)
    ITEM(glPointParameterf) ITEM(glPointParameterfv)
    SEM_LISTA(ITEM)
#undef ITEM
};

uint32_t gl_desktop_por_nome(const char *nome) {
    for (size_t k = 0; k < sizeof tabela / sizeof tabela[0]; k++)
        if (!strcmp(tabela[k].nome, nome)) return ponte_nova(tabela[k].fn, tabela[k].nome);
    return 0;
}
#endif
