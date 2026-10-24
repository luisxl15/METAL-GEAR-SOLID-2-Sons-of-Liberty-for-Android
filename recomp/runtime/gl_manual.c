/* GL/EGL com semantica especial: deslocamento x ponteiro, vetores de
 * ponteiros, retorno de ponteiro (strings e buffers mapeados), GLsync e os
 * objetos EGL/ANativeWindow (ponteiros de 64 bits -> handles de 32). */
#ifndef _WIN32
#include "gl_ponte.h"
#define GL_GLEXT_PROTOTYPES
#include <GLES2/gl2ext.h>
#include <EGL/eglext.h>
#include <android/native_window.h>
#include <android/native_window_jni.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <dlfcn.h>
#include "jni_ponte.h"

volatile long long g_est[12];   /* medicao de custo (ver gl_estat_log) */
int g_jan_w, g_jan_h;   /* tamanho de janela que o jogo pediu (ver ANativeWindow_setBuffersGeometry) */

/* ---- funcoes reais ------------------------------------------------------- */
static void *lib_gles;
void *gl_proc(const char *nome) {
    if (!lib_gles) lib_gles = dlopen("libGLESv2.so", RTLD_NOW);
    void *p = lib_gles ? dlsym(lib_gles, nome) : NULL;
    if (!p) p = (void *)eglGetProcAddress(nome);
    if (!p) rt_log("GL: %s nao existe neste driver", nome);
    return p;
}

/* ---- handles de objetos EGL / janela / GLsync --------------------------- */
#define MAX_OBJ 4096
static void *objs[MAX_OBJ];
static Trava trava_obj;
static int obj_ok;
uint32_t egl_handle(void *p) {
    if (!p) return 0;
    if (!obj_ok) { trava_inicia(&trava_obj); obj_ok = 1; }
    trava(&trava_obj);
    uint32_t livre = 0;
    for (uint32_t k = 1; k < MAX_OBJ; k++) {
        if (objs[k] == p) { destrava(&trava_obj); return 0x300000u + 4 * k; }
        if (!objs[k] && !livre) livre = k;
    }
    if (!livre) rt_fatal("handles EGL esgotados");
    objs[livre] = p;
    destrava(&trava_obj);
    return 0x300000u + 4 * livre;
}
void *egl_obj(uint32_t h) {
    if (!h) return NULL;
    uint32_t k = (h - 0x300000u) / 4;
    return k < MAX_OBJ ? objs[k] : NULL;
}
static void egl_esquece(uint32_t h) { uint32_t k = (h - 0x300000u) / 4; if (k && k < MAX_OBJ) objs[k] = NULL; }
GLsync gl_sync(uint32_t h) { return (GLsync)egl_obj(h); }

/* ---- estado por thread (contexto GL e corrente por thread) --------------- */
static __thread GLuint t_array_buf, t_unpack_buf, t_pack_buf, t_indirect_buf;

void G_glBindBuffer(CPU *c) {
    GLenum alvo = c->r[0]; GLuint b = c->r[1];
    if (alvo == GL_ARRAY_BUFFER) t_array_buf = b;
    else if (alvo == GL_PIXEL_UNPACK_BUFFER) t_unpack_buf = b;
    else if (alvo == GL_PIXEL_PACK_BUFFER) t_pack_buf = b;
    else if (alvo == GL_DRAW_INDIRECT_BUFFER) t_indirect_buf = b;
    glBindBuffer(alvo, b);
}
int pq_desenha(void);   /* pulo de quadros (pulo.c) */
static GLuint elem_buf(void) { GLint b = 0; glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &b); return (GLuint)b; }
#define PTR_OU_OFF(buf, g) ((buf) ? (const void *)(uintptr_t)(g) : (const void *)G2H(g))

/* ---- strings ------------------------------------------------------------- */
static struct { GLenum nome; GLuint idx; uint32_t g; } strs[2048];
static int n_strs;
static uint32_t str_jogo(GLenum nome, GLuint idx, const GLubyte *s) {
    for (int k = 0; k < n_strs; k++) if (strs[k].nome == nome && strs[k].idx == idx) return strs[k].g;
    uint32_t g = guest_strdup(s ? (const char *)s : "");
    if (n_strs < 2048) { strs[n_strs].nome = nome; strs[n_strs].idx = idx; strs[n_strs].g = g; n_strs++; }
    return g;
}
/* A camada escolhe caminhos pelo que o GL diz ser. Com "OpenGL ES 3.2" e so nomes
 * de extensao do GLES, ela cai nos caminhos mais antigos do desktop (glMapBuffer do
 * buffer INTEIRO a cada desenho: 602 mapas de 5,6 MB por quadro = 0,3 quadro/s).
 * Dizemos "OpenGL 3.3" e acrescentamos as extensoes ARB que o GLES 3.2 cobre de
 * verdade (mesmas funcoes do nucleo; nomes com sufixo caem no do nucleo). */
static const char *const EXTRAS[] = {
    "GL_ARB_map_buffer_range", "GL_ARB_vertex_buffer_object", "GL_ARB_pixel_buffer_object",
    "GL_ARB_vertex_array_object", "GL_ARB_framebuffer_object", "GL_EXT_framebuffer_object",
    "GL_EXT_framebuffer_blit", "GL_EXT_framebuffer_multisample", "GL_ARB_texture_non_power_of_two",
    "GL_ARB_texture_float", "GL_ARB_half_float_pixel", "GL_ARB_half_float_vertex", "GL_ARB_texture_rg",
    "GL_ARB_depth_texture", "GL_ARB_shadow", "GL_ARB_sync", "GL_ARB_copy_buffer",
    "GL_ARB_draw_elements_base_vertex", "GL_ARB_instanced_arrays", "GL_ARB_draw_instanced",
    "GL_ARB_sampler_objects", "GL_ARB_texture_compression_rgtc", "GL_EXT_texture_compression_s3tc",
    "GL_ARB_multitexture", "GL_ARB_vertex_shader", "GL_ARB_fragment_shader", "GL_ARB_shader_objects",
    "GL_ARB_shading_language_100", "GL_ARB_draw_buffers", "GL_EXT_blend_func_separate",
    "GL_EXT_blend_equation_separate", "GL_EXT_blend_minmax", "GL_EXT_stencil_two_side",
    "GL_ARB_texture_border_clamp", "GL_EXT_texture_filter_anisotropic", "GL_ARB_ES2_compatibility",
};
static const char *ext_lista[512]; static int n_ext = -1;
static void monta_exts(void) {
    if (n_ext >= 0) return;
    n_ext = 0;
    GLint n = 0; glGetIntegerv(GL_NUM_EXTENSIONS, &n);
    for (GLint i = 0; i < n && n_ext < 480; i++) ext_lista[n_ext++] = (const char *)glGetStringi(GL_EXTENSIONS, (GLuint)i);
    for (size_t k = 0; k < sizeof EXTRAS / sizeof EXTRAS[0]; k++) ext_lista[n_ext++] = EXTRAS[k];
}
int gl_num_exts(void) { monta_exts(); return n_ext; }
void G_glGetString(CPU *c) {
    const GLubyte *s = glGetString(c->r[0]);
    static char junta[16384];
    if (c->r[0] == GL_VERSION) s = (const GLubyte *)"3.3.0 (GLES 3.2 Adreno sob MGS2-ARM64)";
    else if (c->r[0] == GL_SHADING_LANGUAGE_VERSION) s = (const GLubyte *)"3.30";
    else if (c->r[0] == GL_EXTENSIONS) {
        if (!junta[0]) {
            monta_exts(); size_t k = 0;
            for (int i = 0; i < n_ext; i++) { size_t m = strlen(ext_lista[i]); if (k + m + 2 < sizeof junta) { memcpy(junta + k, ext_lista[i], m); k += m; junta[k++] = ' '; } }
            junta[k] = 0;
        }
        s = (const GLubyte *)junta;
    }
#ifdef MGS2_DEPURA
    rt_log("glGetString(%04x): %.120s", c->r[0], s ? (const char *)s : "?");
#endif
    ret32(c, s ? str_jogo(c->r[0], 0xffffffffu, s) : 0);
}
void G_glGetStringi(CPU *c) {
    const GLubyte *s;
    if (c->r[0] == GL_EXTENSIONS) { monta_exts(); s = c->r[1] < (GLuint)n_ext ? (const GLubyte *)ext_lista[c->r[1]] : NULL; }
    else s = glGetStringi(c->r[0], c->r[1]);
    ret32(c, s ? str_jogo(c->r[0], c->r[1], s) : 0);
}

/* ---- vetores de ponteiros ------------------------------------------------ */
void G_glShaderSource(CPU *c) {
    GLsizei n = (GLsizei)c->r[1];
    const GLchar *v[256]; const GLchar **pv = n <= 256 ? v : malloc(sizeof(char *) * (size_t)n);
    for (GLsizei k = 0; k < n; k++) { uint32_t g; memcpy(&g, g_mem + c->r[2] + 4 * k, 4); pv[k] = G2H(g); }
    /* GLSL de desktop -> GLSL ES 3.20 (gl_shader.c) */
    void gl_shader_fonte(GLuint sh, GLsizei n, const GLchar *const *v, const GLint *lens);
    gl_shader_fonte(c->r[0], n, pv, c->r[3] ? (const GLint *)G2H(c->r[3]) : NULL);
    if (pv != v) free(pv);
}
void G_glTransformFeedbackVaryings(CPU *c) {
    GLsizei n = (GLsizei)c->r[1];
    const GLchar *v[64];
    for (GLsizei k = 0; k < n && k < 64; k++) { uint32_t g; memcpy(&g, g_mem + c->r[2] + 4 * k, 4); v[k] = G2H(g); }
    glTransformFeedbackVaryings(c->r[0], n, v, c->r[3]);
}
void G_glGetUniformIndices(CPU *c) {
    GLsizei n = (GLsizei)c->r[1];
    const GLchar *v[64];
    for (GLsizei k = 0; k < n && k < 64; k++) { uint32_t g; memcpy(&g, g_mem + c->r[2] + 4 * k, 4); v[k] = G2H(g); }
    glGetUniformIndices(c->r[0], n, v, G2H(c->r[3]));
}

/* ---- vertices e desenho --------------------------------------------------- */
/* medicao: os primeiros vertices do atributo 0 nos primeiros desenhos */
static __thread GLuint t_a0_buf; static __thread uint32_t t_a0_off; static __thread GLsizei t_a0_passo;
#ifdef MGS2_DEPURA
void gl_mostra_vertices(const char *fn, GLint primeiro) {
    static int n; if (n >= 40 || !t_a0_buf || t_a0_passo < 20) return; n++;
    GLint ant = 0; glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &ant);
    glBindBuffer(GL_ARRAY_BUFFER, t_a0_buf);
    GLint tam = 0; glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &tam);
    GLintptr o = (GLintptr)t_a0_off + (GLintptr)primeiro * t_a0_passo; GLsizeiptr q = 4 * t_a0_passo;
    if (o + q <= tam) {
        const float *v = glMapBufferRange(GL_ARRAY_BUFFER, o, q, GL_MAP_READ_BIT);
        if (v) {
            int k = t_a0_passo / 4;
            GLint prog = 0; glGetIntegerv(GL_CURRENT_PROGRAM, &prog);
            static int salvos[64]; int ja = 0;
            for (int q2 = 0; q2 < 64 && salvos[q2]; q2++) if (salvos[q2] == prog) ja = 1;
            if (!ja && prog) {
                for (int q2 = 0; q2 < 64; q2++) if (!salvos[q2]) { salvos[q2] = prog; break; }
                GLuint sh[4]; GLsizei nsh = 0; glGetAttachedShaders((GLuint)prog, 4, &nsh, sh);
                char nome[160]; snprintf(nome, sizeof nome, "/sdcard/Android/data/jp.konami.mgs2hd.shield/files/prog_%d.txt", prog);
                FILE *f = fopen(nome, "wb");
                for (GLsizei k2 = 0; f && k2 < nsh; k2++) {
                    GLint n2 = 0; glGetShaderiv(sh[k2], GL_SHADER_SOURCE_LENGTH, &n2);
                    char *fo = malloc((size_t)n2 + 1); glGetShaderSource(sh[k2], n2 + 1, NULL, fo); fputs(fo, f); fputs("\n/* ======== */\n", f); free(fo);
                }
                if (f) fclose(f);
            }
            {   GLint vp[4], fb = 0, tipo = 0, obj = 0, lw = 0, lh = 0;
                glGetIntegerv(GL_VIEWPORT, vp); glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &fb);
                if (fb) {
                    glGetFramebufferAttachmentParameteriv(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE, &tipo);
                    glGetFramebufferAttachmentParameteriv(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME, &obj);
                    if (tipo == GL_TEXTURE) { GLint at = 0; glGetIntegerv(GL_TEXTURE_BINDING_2D, &at); glBindTexture(GL_TEXTURE_2D, (GLuint)obj);
                        glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &lw); glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &lh);
                        glBindTexture(GL_TEXTURE_2D, (GLuint)at); }
                    else if (tipo == GL_RENDERBUFFER) { GLint ar = 0; glGetIntegerv(GL_RENDERBUFFER_BINDING, &ar); glBindRenderbuffer(GL_RENDERBUFFER, (GLuint)obj);
                        glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_WIDTH, &lw); glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_HEIGHT, &lh);
                        glBindRenderbuffer(GL_RENDERBUFFER, (GLuint)ar); }
                }
                GLint tex0 = 0; glGetIntegerv(GL_TEXTURE_BINDING_2D, &tex0);
                rt_log("  estado: vp %d,%d %dx%d fbo %d cor %s %d (%dx%d) tex ativa %d", vp[0], vp[1], vp[2], vp[3], fb,
                       tipo == GL_TEXTURE ? "tex" : tipo == GL_RENDERBUFFER ? "rb" : "-", obj, lw, lh, tex0);
            }
            rt_log("%s prog %d buf %u passo %d: v0 (%g %g %g | %g %g) v1 (%g %g %g | %g %g) v2 (%g %g %g | %g %g)", fn, prog, t_a0_buf, t_a0_passo,
                   v[0], v[1], v[2], v[3], v[4], v[k], v[k+1], v[k+2], v[k+3], v[k+4], v[2*k], v[2*k+1], v[2*k+2], v[2*k+3], v[2*k+4]);
            glUnmapBuffer(GL_ARRAY_BUFFER);
        }
    }
    glBindBuffer(GL_ARRAY_BUFFER, (GLuint)ant);
}
#else
void gl_mostra_vertices(const char *fn, GLint primeiro) { (void)fn; (void)primeiro; }
#endif
void G_glVertexAttribPointer(CPU *c) {
    Args a = args_de(c);
    GLuint i = arg32(&a); GLint s = (GLint)arg32(&a); GLenum t = arg32(&a); GLboolean nz = (GLboolean)arg32(&a);
    GLsizei st = (GLsizei)arg32(&a); uint32_t p = arg32(&a);
    if (i == 0) { t_a0_buf = t_array_buf; t_a0_off = p; t_a0_passo = st; }
    glVertexAttribPointer(i, s, t, nz, st, PTR_OU_OFF(t_array_buf, p));
}
void G_glVertexAttribIPointer(CPU *c) {
    Args a = args_de(c);
    GLuint i = arg32(&a); GLint s = (GLint)arg32(&a); GLenum t = arg32(&a); GLsizei st = (GLsizei)arg32(&a); uint32_t p = arg32(&a);
    glVertexAttribIPointer(i, s, t, st, PTR_OU_OFF(t_array_buf, p));
}
void G_glDrawElements(CPU *c) { if (!pq_desenha()) return; g_est[4]++; gl_mostra_vertices("DrawElements", 0); glDrawElements(c->r[0], (GLsizei)c->r[1], c->r[2], PTR_OU_OFF(elem_buf(), c->r[3])); }
static void inst_(CPU *c) {
    if (!pq_desenha()) return;
    Args a = args_de(c);
    GLenum m = arg32(&a); GLsizei n = (GLsizei)arg32(&a); GLenum t = arg32(&a); uint32_t p = arg32(&a); GLsizei ic = (GLsizei)arg32(&a);
    glDrawElementsInstanced(m, n, t, PTR_OU_OFF(elem_buf(), p), ic);
}
void G_glDrawElementsInstanced(CPU *c) { inst_(c); }
void G_glDrawElementsInstancedEXT(CPU *c) { inst_(c); }
void G_glDrawElementsInstancedANGLE(CPU *c) { inst_(c); }
void G_glDrawElementsInstancedNV(CPU *c) { inst_(c); }
void G_glDrawRangeElements(CPU *c) { if (!pq_desenha()) return; g_est[4]++; gl_mostra_vertices("DrawRangeElements", 0);
    Args a = args_de(c);
    GLenum m = arg32(&a); GLuint s = arg32(&a), e = arg32(&a); GLsizei n = (GLsizei)arg32(&a); GLenum t = arg32(&a); uint32_t p = arg32(&a);
    glDrawRangeElements(m, s, e, n, t, PTR_OU_OFF(elem_buf(), p));
}
static void base_(CPU *c) {
    if (!pq_desenha()) return;
    Args a = args_de(c);
    GLenum m = arg32(&a); GLsizei n = (GLsizei)arg32(&a); GLenum t = arg32(&a); uint32_t p = arg32(&a); GLint bv = (GLint)arg32(&a);
    glDrawElementsBaseVertex(m, n, t, PTR_OU_OFF(elem_buf(), p), bv);
}
void G_glDrawElementsBaseVertex(CPU *c) { base_(c); }
void G_glDrawElementsBaseVertexEXT(CPU *c) { base_(c); }
void G_glDrawElementsBaseVertexOES(CPU *c) { base_(c); }
static void inst_base_(CPU *c) {
    if (!pq_desenha()) return;
    Args a = args_de(c);
    GLenum m = arg32(&a); GLsizei n = (GLsizei)arg32(&a); GLenum t = arg32(&a); uint32_t p = arg32(&a);
    GLsizei ic = (GLsizei)arg32(&a); GLint bv = (GLint)arg32(&a);
    glDrawElementsInstancedBaseVertex(m, n, t, PTR_OU_OFF(elem_buf(), p), ic, bv);
}
void G_glDrawElementsInstancedBaseVertex(CPU *c) { inst_base_(c); }
void G_glDrawElementsInstancedBaseVertexEXT(CPU *c) { inst_base_(c); }
void G_glDrawElementsInstancedBaseVertexOES(CPU *c) { inst_base_(c); }
static void range_base_(CPU *c) {
    if (!pq_desenha()) return;
    Args a = args_de(c);
    GLenum m = arg32(&a); GLuint s = arg32(&a), e = arg32(&a); GLsizei n = (GLsizei)arg32(&a); GLenum t = arg32(&a);
    uint32_t p = arg32(&a); GLint bv = (GLint)arg32(&a);
    glDrawRangeElementsBaseVertex(m, s, e, n, t, PTR_OU_OFF(elem_buf(), p), bv);
}
void G_glDrawRangeElementsBaseVertex(CPU *c) { range_base_(c); }
void G_glDrawRangeElementsBaseVertexEXT(CPU *c) { range_base_(c); }
void G_glDrawRangeElementsBaseVertexOES(CPU *c) { range_base_(c); }
void G_glMultiDrawElementsEXT(CPU *c) { (void)c; rt_fatal("glMultiDrawElementsEXT nao suportado"); }
void G_glMultiDrawElementsBaseVertexEXT(CPU *c) { (void)c; rt_fatal("glMultiDrawElementsBaseVertexEXT nao suportado"); }
void G_glDrawElementsIndirect(CPU *c) { if (!pq_desenha()) return; glDrawElementsIndirect(c->r[0], c->r[1], (const void *)(uintptr_t)c->r[2]); }
void G_glDrawArraysIndirect(CPU *c) { if (!pq_desenha()) return; glDrawArraysIndirect(c->r[0], (const void *)(uintptr_t)c->r[1]); }

/* ---- texturas (buffer de pixels ligado = deslocamento) ------------------- */
/* formatos do desktop -> GLES (gl_formato.c) */
void fmt_tex_image2d(GLenum, GLint, GLint, GLsizei, GLsizei, GLint, GLenum, GLenum, uint32_t, GLuint);
void fmt_tex_sub_image2d(GLenum, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, uint32_t, GLuint);
void fmt_tex_image3d(GLenum, GLint, GLint, GLsizei, GLsizei, GLsizei, GLint, GLenum, GLenum, uint32_t, GLuint);
void fmt_tex_sub_image3d(GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLenum, uint32_t, GLuint);
void fmt_read_pixels(GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, uint32_t, GLuint);
void G_glTexImage2D(CPU *c) {
    Args a = args_de(c);
    GLenum t = arg32(&a); GLint l = (GLint)arg32(&a), fi = (GLint)arg32(&a); GLsizei w = (GLsizei)arg32(&a), hh = (GLsizei)arg32(&a);
    GLint b = (GLint)arg32(&a); GLenum f = arg32(&a), ty = arg32(&a); uint32_t p = arg32(&a);
    fmt_tex_image2d(t, l, fi, w, hh, b, f, ty, p, t_unpack_buf);
}
void G_glTexSubImage2D(CPU *c) {
    Args a = args_de(c);
    GLenum t = arg32(&a); GLint l = (GLint)arg32(&a), x = (GLint)arg32(&a), y = (GLint)arg32(&a);
    GLsizei w = (GLsizei)arg32(&a), hh = (GLsizei)arg32(&a); GLenum f = arg32(&a), ty = arg32(&a); uint32_t p = arg32(&a);
    fmt_tex_sub_image2d(t, l, x, y, w, hh, f, ty, p, t_unpack_buf);
}
static void tex3d_(CPU *c) {
    Args a = args_de(c);
    GLenum t = arg32(&a); GLint l = (GLint)arg32(&a), fi = (GLint)arg32(&a);
    GLsizei w = (GLsizei)arg32(&a), hh = (GLsizei)arg32(&a), d = (GLsizei)arg32(&a); GLint b = (GLint)arg32(&a);
    GLenum f = arg32(&a), ty = arg32(&a); uint32_t p = arg32(&a);
    fmt_tex_image3d(t, l, fi, w, hh, d, b, f, ty, p, t_unpack_buf);
}
void G_glTexImage3D(CPU *c) { tex3d_(c); }
void G_glTexImage3DOES(CPU *c) { tex3d_(c); }
static void texsub3d_(CPU *c) {
    Args a = args_de(c);
    GLenum t = arg32(&a); GLint l = (GLint)arg32(&a), x = (GLint)arg32(&a), y = (GLint)arg32(&a), z = (GLint)arg32(&a);
    GLsizei w = (GLsizei)arg32(&a), hh = (GLsizei)arg32(&a), d = (GLsizei)arg32(&a); GLenum f = arg32(&a), ty = arg32(&a); uint32_t p = arg32(&a);
    fmt_tex_sub_image3d(t, l, x, y, z, w, hh, d, f, ty, p, t_unpack_buf);
}
void G_glTexSubImage3D(CPU *c) { texsub3d_(c); }
void G_glTexSubImage3DOES(CPU *c) { texsub3d_(c); }
void G_glCompressedTexImage2D(CPU *c) {
    Args a = args_de(c);
    GLenum t = arg32(&a); GLint l = (GLint)arg32(&a); GLenum fi = arg32(&a); GLsizei w = (GLsizei)arg32(&a), hh = (GLsizei)arg32(&a);
    GLint b = (GLint)arg32(&a); GLsizei n = (GLsizei)arg32(&a); uint32_t p = arg32(&a);
    int fmt_comprimida2d(GLenum, GLint, GLenum, GLsizei, GLsizei, GLint, GLsizei, uint32_t, GLuint);
    if (fmt_comprimida2d(t, l, fi, w, hh, b, n, p, t_unpack_buf)) return;   /* GPU sem DXT/RGTC */
    glCompressedTexImage2D(t, l, fi, w, hh, b, n, PTR_OU_OFF(t_unpack_buf, p));
}
void G_glCompressedTexSubImage2D(CPU *c) {
    Args a = args_de(c);
    GLenum t = arg32(&a); GLint l = (GLint)arg32(&a), x = (GLint)arg32(&a), y = (GLint)arg32(&a);
    GLsizei w = (GLsizei)arg32(&a), hh = (GLsizei)arg32(&a); GLenum f = arg32(&a); GLsizei n = (GLsizei)arg32(&a); uint32_t p = arg32(&a);
    int fmt_comprimida_sub2d(GLenum, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLsizei, uint32_t, GLuint);
    if (fmt_comprimida_sub2d(t, l, x, y, w, hh, f, n, p, t_unpack_buf)) return;
    glCompressedTexSubImage2D(t, l, x, y, w, hh, f, n, PTR_OU_OFF(t_unpack_buf, p));
}
static void ctex3d_(CPU *c) {
    Args a = args_de(c);
    GLenum t = arg32(&a); GLint l = (GLint)arg32(&a); GLenum fi = arg32(&a);
    GLsizei w = (GLsizei)arg32(&a), hh = (GLsizei)arg32(&a), d = (GLsizei)arg32(&a); GLint b = (GLint)arg32(&a);
    GLsizei n = (GLsizei)arg32(&a); uint32_t p = arg32(&a);
    int fmt_comprimida3d(GLenum, GLint, GLenum, GLsizei, GLsizei, GLsizei, GLint, GLsizei, uint32_t, GLuint);
    if (fmt_comprimida3d(t, l, fi, w, hh, d, b, n, p, t_unpack_buf)) return;
    glCompressedTexImage3D(t, l, fi, w, hh, d, b, n, PTR_OU_OFF(t_unpack_buf, p));
}
void G_glCompressedTexImage3D(CPU *c) { ctex3d_(c); }
void G_glCompressedTexImage3DOES(CPU *c) { ctex3d_(c); }
static void ctexsub3d_(CPU *c) {
    Args a = args_de(c);
    GLenum t = arg32(&a); GLint l = (GLint)arg32(&a), x = (GLint)arg32(&a), y = (GLint)arg32(&a), z = (GLint)arg32(&a);
    GLsizei w = (GLsizei)arg32(&a), hh = (GLsizei)arg32(&a), d = (GLsizei)arg32(&a); GLenum f = arg32(&a);
    GLsizei n = (GLsizei)arg32(&a); uint32_t p = arg32(&a);
    int fmt_comprimida_sub3d(GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLsizei, uint32_t, GLuint);
    if (fmt_comprimida_sub3d(t, l, x, y, z, w, hh, d, f, n, p, t_unpack_buf)) return;
    glCompressedTexSubImage3D(t, l, x, y, z, w, hh, d, f, n, PTR_OU_OFF(t_unpack_buf, p));
}
void G_glCompressedTexSubImage3D(CPU *c) { ctexsub3d_(c); }
void G_glCompressedTexSubImage3DOES(CPU *c) { ctexsub3d_(c); }
void G_glReadPixels(CPU *c) {
    Args a = args_de(c);
    GLint x = (GLint)arg32(&a), y = (GLint)arg32(&a); GLsizei w = (GLsizei)arg32(&a), hh = (GLsizei)arg32(&a);
    GLenum f = arg32(&a), t = arg32(&a); uint32_t p = arg32(&a);
    fmt_read_pixels(x, y, w, hh, f, t, p, t_pack_buf);
}

/* ---- buffers mapeados: sombra na memoria do jogo ------------------------- */
typedef struct { GLenum alvo; void *h; uint32_t g; GLsizeiptr off, tam; GLbitfield acesso; } Mapa;
static __thread Mapa t_mapas[8];
static Mapa *mapa_de(GLenum alvo, int cria) {
    for (int k = 0; k < 8; k++) if (t_mapas[k].g && t_mapas[k].alvo == alvo) return &t_mapas[k];
    if (!cria) return NULL;
    for (int k = 0; k < 8; k++) if (!t_mapas[k].g) return &t_mapas[k];
    rt_fatal("buffers mapeados demais");
}
/* medicao de custo por janela de 2 s (impresso junto com os quadros/s) */
/* g_est: 0 mapas, 1 bytes lidos p/ sombra, 2 bytes escritos da sombra, 3 mapas c/ READ,
                                   4 desenhos, 5 bufferdata bytes, 6 bufsubdata bytes, 7 teximagem bytes, 8 compilacoes,
          9 ReadPixels, 10 pastas lidas (caminho.c), 11 fopen (libc_manual.c); quadro lento em android.c */
void gl_estat_log(void) {
    rt_log("custo/2s: mapas %lld (READ %lld), sombra lida %lld KB, escrita %lld KB, desenhos %lld, BufferData %lld KB, BufferSubData %lld KB, texturas %lld KB, compilacoes %lld",
           g_est[0], g_est[3], g_est[1] >> 10, g_est[2] >> 10, g_est[4], g_est[5] >> 10, g_est[6] >> 10, g_est[7] >> 10, g_est[8]);
    for (int i = 0; i < 12; i++) g_est[i] = 0;
}
static uint32_t mapeia(GLenum alvo, GLintptr off, GLsizeiptr tam, GLbitfield acesso) {
    g_est[0]++; if (acesso & GL_MAP_READ_BIT) g_est[3]++;
#ifdef MGS2_DEPURA
    { static int n; if (n++ < 8) rt_log("glMapBufferRange(alvo %x, desloc %ld, tam %ld, acesso %x)", alvo, (long)off, (long)tam, acesso); }
#endif
    void *h = glMapBufferRange(alvo, off, tam, acesso);
    if (!h) return 0;
    Mapa *m = mapa_de(alvo, 1);
    m->alvo = alvo; m->h = h; m->off = off; m->tam = tam; m->acesso = acesso;
    m->g = heap_malloc((uint32_t)tam + 16);
    if (acesso & GL_MAP_READ_BIT) { memcpy(g_mem + m->g, h, (size_t)tam); g_est[1] += tam; }
    /* sem leitura, com FLUSH_EXPLICIT so os trechos passados a glFlushMappedBufferRange
     * voltam para o buffer: o resto da sombra nunca e lido, nao precisa ser copiado
     * (a camada mapeia o anel inteiro de 5,6 MB por desenho e escreve uns poucos KB) */
    else if (!(acesso & (GL_MAP_INVALIDATE_RANGE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT | GL_MAP_FLUSH_EXPLICIT_BIT))) { memcpy(g_mem + m->g, h, (size_t)tam); g_est[1] += tam; }
    if (acesso & GL_MAP_PERSISTENT_BIT_EXT) rt_log("AVISO: mapa persistente de buffer (a sombra nao acompanha)");
    return m->g;
}
void G_glMapBufferRange(CPU *c) { ret32(c, mapeia(c->r[0], (GLintptr)(int32_t)c->r[1], (GLsizeiptr)(int32_t)c->r[2], c->r[3])); }
void G_glMapBufferRangeEXT(CPU *c) { G_glMapBufferRange(c); }
void G_glMapBufferOES(CPU *c) {
    GLint tam = 0; glGetBufferParameteriv(c->r[0], GL_BUFFER_SIZE, &tam);
    ret32(c, mapeia(c->r[0], 0, tam, GL_MAP_WRITE_BIT | GL_MAP_READ_BIT));
}
static void desmapeia(CPU *c) {
    Mapa *m = mapa_de(c->r[0], 0);
    if (m) {
        if ((m->acesso & GL_MAP_WRITE_BIT) && !(m->acesso & GL_MAP_FLUSH_EXPLICIT_BIT)) { memcpy(m->h, g_mem + m->g, (size_t)m->tam); g_est[2] += m->tam; }
        heap_free(m->g); m->g = 0;
    }
    ret32(c, glUnmapBuffer(c->r[0]));
}
void G_glUnmapBuffer(CPU *c) { desmapeia(c); }
void G_glUnmapBufferOES(CPU *c) { desmapeia(c); }
void G_glFlushMappedBufferRange(CPU *c) {
    Mapa *m = mapa_de(c->r[0], 0);
    GLintptr o = (GLintptr)(int32_t)c->r[1]; GLsizeiptr n = (GLsizeiptr)(int32_t)c->r[2];
    if (m) { memcpy((uint8_t *)m->h + o, g_mem + m->g + o, (size_t)n); g_est[2] += n; }
    glFlushMappedBufferRange(c->r[0], o, n);
}
void G_glFlushMappedBufferRangeEXT(CPU *c) { G_glFlushMappedBufferRange(c); }
void G_glBufferStorageEXT(CPU *c) {
    GLbitfield f = c->r[3];
    if (f & (GL_MAP_PERSISTENT_BIT_EXT | GL_MAP_COHERENT_BIT_EXT)) rt_log("glBufferStorageEXT persistente: retirado (PersistentVBO deve ser N)");
    f &= ~(GLbitfield)(GL_MAP_PERSISTENT_BIT_EXT | GL_MAP_COHERENT_BIT_EXT);
    static void (*p)(GLenum, GLsizeiptr, const void *, GLbitfield);
    if (!p) p = gl_proc("glBufferStorageEXT");
    p(c->r[0], (GLsizeiptr)(int32_t)c->r[1], G2H(c->r[2]), f);
}
void G_glGetBufferPointerv(CPU *c) { Mapa *m = mapa_de(c->r[0], 0); uint32_t v = m ? m->g : 0; memcpy(g_mem + c->r[2], &v, 4); }
void G_glGetBufferPointervOES(CPU *c) { G_glGetBufferPointerv(c); }
void G_glGetPointerv(CPU *c) { uint32_t z = 0; memcpy(g_mem + c->r[1], &z, 4); }
void G_glGetPointervKHR(CPU *c) { G_glGetPointerv(c); }
void G_glGetVertexAttribPointerv(CPU *c) {
    void *p = NULL; glGetVertexAttribPointerv(c->r[0], c->r[1], &p);
    uint32_t v = (uint32_t)(uintptr_t)p;   /* com buffer ligado e deslocamento */
    if ((uint8_t *)p >= g_mem && (uint8_t *)p < g_mem + (1ull << 32)) v = H2G(p);
    memcpy(g_mem + c->r[2], &v, 4);
}

/* ---- sincronizacao --------------------------------------------------------- */
void G_glFenceSync(CPU *c) { ret32(c, egl_handle(glFenceSync(c->r[0], c->r[1]))); }
void G_glDeleteSync(CPU *c) { glDeleteSync(gl_sync(c->r[0])); egl_esquece(c->r[0]); }
void G_glIsSync(CPU *c) { ret32(c, glIsSync(gl_sync(c->r[0]))); }
void G_glClientWaitSync(CPU *c) { Args a = args_de(c); uint32_t s = arg32(&a), f = arg32(&a); uint64_t t = arg64(&a); ret32(c, glClientWaitSync(gl_sync(s), f, t)); }
void G_glWaitSync(CPU *c) { Args a = args_de(c); uint32_t s = arg32(&a), f = arg32(&a); uint64_t t = arg64(&a); glWaitSync(gl_sync(s), f, t); }
void G_glGetSynciv(CPU *c) {
    Args a = args_de(c); uint32_t s = arg32(&a), pn = arg32(&a), n = arg32(&a), len = arg32(&a), val = arg32(&a);
    glGetSynciv(gl_sync(s), pn, (GLsizei)n, G2H(len), G2H(val));
}
void G_glFenceSyncAPPLE(CPU *c) { G_glFenceSync(c); }
void G_glDeleteSyncAPPLE(CPU *c) { G_glDeleteSync(c); }
void G_glIsSyncAPPLE(CPU *c) { G_glIsSync(c); }
void G_glClientWaitSyncAPPLE(CPU *c) { G_glClientWaitSync(c); }
void G_glWaitSyncAPPLE(CPU *c) { G_glWaitSync(c); }
void G_glGetSyncivAPPLE(CPU *c) { G_glGetSynciv(c); }
void G_glDebugMessageCallback(CPU *c) { (void)c; }
void G_glDebugMessageCallbackKHR(CPU *c) { (void)c; }
void G_glEGLImageTargetTexture2DOES(CPU *c) { glEGLImageTargetTexture2DOES(c->r[0], egl_obj(c->r[1])); }
void G_glEGLImageTargetRenderbufferStorageOES(CPU *c) { glEGLImageTargetRenderbufferStorageOES(c->r[0], egl_obj(c->r[1])); }

/* ======================================================================== */
/* EGL                                                                       */
void I_eglGetDisplay(CPU *c) { RT_PRIMEIRA("eglGetDisplay"); ret32(c, egl_handle(eglGetDisplay(EGL_DEFAULT_DISPLAY))); (void)c->r[0]; }
void I_eglInitialize(CPU *c) { RT_PRIMEIRA("eglInitialize");
    EGLint ma, mi;
    EGLBoolean r = eglInitialize(egl_obj(c->r[0]), &ma, &mi);
    if (c->r[1]) memcpy(g_mem + c->r[1], &ma, 4);
    if (c->r[2]) memcpy(g_mem + c->r[2], &mi, 4);
    ret32(c, r);
}
void I_eglTerminate(CPU *c) { RT_PRIMEIRA("eglTerminate"); ret32(c, eglTerminate(egl_obj(c->r[0]))); }
/* A camada da TransGaming pede OpenGL de DESKTOP (EGL_OPENGL_API, como no Tegra do
 * SHIELD). A Adreno so tem GLES: por ora pedimos GLES 3.2 no lugar e registramos o
 * que a camada pede, para medir o que falta. */
void I_eglBindAPI(CPU *c) { RT_PRIMEIRA("eglBindAPI");
    uint32_t api = c->r[0];
    if (api == EGL_OPENGL_API) { rt_log("eglBindAPI(OPENGL) -> OPENGL_ES"); api = EGL_OPENGL_ES_API; }
    ret32(c, eglBindAPI(api));
}
void I_eglGetError(CPU *c) { RT_PRIMEIRA("eglGetError"); ret32(c, (uint32_t)eglGetError()); }
void I_eglChooseConfig(CPU *c) { RT_PRIMEIRA("eglChooseConfig");
    Args a = args_de(c);
    EGLDisplay d = egl_obj(arg32(&a)); uint32_t attr = arg32(&a), cfgs = arg32(&a); EGLint n = (EGLint)arg32(&a); uint32_t pn = arg32(&a);
    EGLConfig tmp[256]; EGLint achados = 0;
    EGLint at[128]; int na = 0;
    if (attr) {
        const EGLint *o = G2H(attr);
        while (na < 126 && o[na] != EGL_NONE) {
            at[na] = o[na]; at[na + 1] = o[na + 1];
            rt_log("eglChooseConfig: %04x = %d", o[na], o[na + 1]);
            if (at[na] == EGL_RENDERABLE_TYPE && (at[na + 1] & EGL_OPENGL_BIT)) at[na + 1] = EGL_OPENGL_ES3_BIT_KHR;
            na += 2;
        }
    }
    at[na] = EGL_NONE;
    EGLBoolean r = eglChooseConfig(d, at, cfgs ? tmp : NULL, n > 256 ? 256 : n, &achados);
    rt_log("eglChooseConfig -> %d, %d configs", r, achados);
    if (cfgs) for (EGLint k = 0; k < achados; k++) { uint32_t h = egl_handle(tmp[k]); memcpy(g_mem + cfgs + 4 * k, &h, 4); }
    if (pn) memcpy(g_mem + pn, &achados, 4);
    ret32(c, r);
}
void I_eglGetConfigAttrib(CPU *c) { RT_PRIMEIRA("eglGetConfigAttrib"); EGLint v = 0; EGLBoolean r = eglGetConfigAttrib(egl_obj(c->r[0]), egl_obj(c->r[1]), (EGLint)c->r[2], &v); memcpy(g_mem + c->r[3], &v, 4); ret32(c, r); }
void I_eglCreateContext(CPU *c) { RT_PRIMEIRA("eglCreateContext");
    if (c->r[3]) { const EGLint *o = G2H(c->r[3]); for (int i = 0; i < 32 && o[i] != EGL_NONE; i += 2) rt_log("eglCreateContext: %04x = %d", o[i], o[i + 1]); }
    /* Em ordem, ate um dar certo. EGL_CONTEXT_OPENGL_DEBUG e do EGL 1.5: o Mali-G76 do Helio
     * G90 (Realme 6, Android 11, EGL 1.4 + KHR_create_context) recusa com EGL_BAD_ATTRIBUTE, e
     * sem contexto o jogo morria num strstr(NULL) de glGetString(GL_EXTENSIONS). Ele so serve ao
     * KHR_debug do build de depuracao. CLIENT_VERSION 3 cobre driver sem KHR_create_context. */
    static const EGLint tentativas[][7] = {
#ifdef MGS2_DEPURA
        { EGL_CONTEXT_MAJOR_VERSION_KHR, 3, EGL_CONTEXT_MINOR_VERSION_KHR, 2, 0x31B0 /* EGL_CONTEXT_OPENGL_DEBUG */, EGL_TRUE, EGL_NONE },
#endif
        { EGL_CONTEXT_MAJOR_VERSION_KHR, 3, EGL_CONTEXT_MINOR_VERSION_KHR, 2, EGL_NONE },
        { EGL_CONTEXT_CLIENT_VERSION, 3, EGL_NONE },
    };
    static const char *nomes[] = {
#ifdef MGS2_DEPURA
        "3.2 depuracao",
#endif
        "3.2", "3 (CLIENT_VERSION)" };
    EGLContext k = EGL_NO_CONTEXT;
    for (unsigned t = 0; t < sizeof tentativas / sizeof tentativas[0] && !k; t++) {
        k = eglCreateContext(egl_obj(c->r[0]), egl_obj(c->r[1]), egl_obj(c->r[2]), tentativas[t]);
        if (!k) rt_log("eglCreateContext (GLES %s) falhou: %x", nomes[t], eglGetError());
        else if (t) rt_log("eglCreateContext: GLES %s", nomes[t]);
    }
    if (!k) rt_fatal("sem contexto OpenGL ES 3: o driver de video recusou todas as tentativas");
    ret32(c, egl_handle(k));
}
void I_eglDestroyContext(CPU *c) { RT_PRIMEIRA("eglDestroyContext"); EGLBoolean r = eglDestroyContext(egl_obj(c->r[0]), egl_obj(c->r[1])); egl_esquece(c->r[1]); ret32(c, r); }
/* geracao de quadros (lsfg_gl.c / lsfg_vk.cpp): com ela ligada o Vulkan fica com a janela */
EGLSurface fg_cria_superficie(EGLDisplay d, EGLConfig cfg, ANativeWindow *jan);
int fg_destroi_superficie(EGLSurface s);
int fg_tamanho(EGLSurface s, EGLint atr, EGLint *v);
int fg_troca(EGLDisplay d, EGLSurface s);
void I_eglCreateWindowSurface(CPU *c) { RT_PRIMEIRA("eglCreateWindowSurface");
    EGLSurface fg = fg_cria_superficie(egl_obj(c->r[0]), egl_obj(c->r[1]), (ANativeWindow *)egl_obj(c->r[2]));
    if (fg != EGL_NO_SURFACE) { ret32(c, egl_handle(fg)); return; }
    EGLSurface s = eglCreateWindowSurface(egl_obj(c->r[0]), egl_obj(c->r[1]), (EGLNativeWindowType)egl_obj(c->r[2]), G2H(c->r[3]));
    if (!s) rt_log("eglCreateWindowSurface falhou: %x", eglGetError());
    ret32(c, egl_handle(s));
}
void I_eglDestroySurface(CPU *c) { RT_PRIMEIRA("eglDestroySurface");
    if (fg_destroi_superficie(egl_obj(c->r[1]))) { egl_esquece(c->r[1]); ret32(c, EGL_TRUE); return; }
    EGLBoolean r = eglDestroySurface(egl_obj(c->r[0]), egl_obj(c->r[1])); egl_esquece(c->r[1]); ret32(c, r); }
/* diagnostico: mensagens do driver (KHR_debug) no log, com teto por contagem */
static void GL_APIENTRY gl_msg(GLenum src, GLenum tipo, GLuint id, GLenum sev, GLsizei n, const GLchar *m, const void *u) {
    (void)src; (void)n; (void)u;
    if (sev == GL_DEBUG_SEVERITY_NOTIFICATION) return;
    static int cont; if (__atomic_fetch_add(&cont, 1, __ATOMIC_RELAXED) >= 200) return;
    rt_log("GL[%x/%x/%u]: %s", tipo, sev, id, m);
}
static void gl_liga_depuracao(void) {
    static __thread void *feito;
    EGLContext k = eglGetCurrentContext();
    if (feito == k) return;
    feito = k;
    /* sRGB: no desktop a escrita em alvo sRGB so converte com GL_FRAMEBUFFER_SRGB ligado
     * (padrao DESLIGADO); no GLES converte sempre, e a imagem saia lavada/cinza.
     * EXT_sRGB_write_control: comeca desligado como no desktop; se a camada ligar,
     * o glEnable dela chega ao driver normalmente. */
    glDisable(0x8DB9 /* GL_FRAMEBUFFER_SRGB_EXT */);
#ifdef MGS2_DEPURA
    /* saida de depuracao SINCRONA: cada chamada GL espera a validacao do driver */
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(gl_msg, NULL);
#endif
}
void I_eglMakeCurrent(CPU *c) { RT_PRIMEIRA("eglMakeCurrent");
    EGLBoolean r = eglMakeCurrent(egl_obj(c->r[0]), egl_obj(c->r[1]), egl_obj(c->r[2]), egl_obj(c->r[3]));
    if (r && c->r[3]) gl_liga_depuracao();
#ifdef MGS2_DEPURA
    static int n; if (__atomic_fetch_add(&n, 1, __ATOMIC_RELAXED) < 40)
        rt_log("eglMakeCurrent(tid %d, dpy %x, draw %x, read %x, ctx %x) -> %d (erro %x)", gettid(), c->r[0], c->r[1], c->r[2], c->r[3], r, r ? 0 : eglGetError());
#endif
    ret32(c, r);
}
void I_eglGetCurrentContext(CPU *c) { RT_PRIMEIRA("eglGetCurrentContext"); ret32(c, egl_handle(eglGetCurrentContext())); }
void I_eglGetCurrentSurface(CPU *c) { RT_PRIMEIRA("eglGetCurrentSurface"); ret32(c, egl_handle(eglGetCurrentSurface(c->r[0]))); }
void I_eglQuerySurface(CPU *c) { RT_PRIMEIRA("eglQuerySurface"); EGLint v = 0; EGLBoolean r = eglQuerySurface(egl_obj(c->r[0]), egl_obj(c->r[1]), (EGLint)c->r[2], &v);
    fg_tamanho(egl_obj(c->r[1]), (EGLint)c->r[2], &v);              /* pbuffer da geracao: tamanho da janela */
    if (g_jan_w > 0 && c->r[2] == EGL_WIDTH) v = g_jan_w;          /* o jogo ve o tamanho que pediu */
    if (g_jan_h > 0 && c->r[2] == EGL_HEIGHT) v = g_jan_h;
    memcpy(g_mem + c->r[3], &v, 4);
#ifdef MGS2_DEPURA
    { static int n; if (n++ < 20) rt_log("eglQuerySurface(%x) = %d", c->r[2], v); }
#endif
    ret32(c, r);
}
void rt_quadro(void);   /* contador de quadros / ritmo (android.c) */
int pq_troca(void);     /* ritmo da logica e pulo de quadros (pulo.c) */
void I_eglSwapBuffers(CPU *c) { RT_PRIMEIRA("eglSwapBuffers");
    int mostra = pq_troca(); rt_quadro();
    if (!mostra) { ret32(c, EGL_TRUE); return; }   /* quadro pulado: nada novo para a tela */
    if (fg_troca(egl_obj(c->r[0]), egl_obj(c->r[1]))) { ret32(c, EGL_TRUE); return; }
    ret32(c, eglSwapBuffers(egl_obj(c->r[0]), egl_obj(c->r[1]))); }
void I_eglSwapInterval(CPU *c) { RT_PRIMEIRA("eglSwapInterval"); ret32(c, eglSwapInterval(egl_obj(c->r[0]), (EGLint)c->r[1])); }
uint32_t gl_ponte_por_nome(const char *nome);
void I_eglGetProcAddress(CPU *c) { RT_PRIMEIRA("eglGetProcAddress");
    const char *n = G2H(c->r[0]);
    uint32_t p = gl_ponte_por_nome(n);
    if (!p) rt_log("eglGetProcAddress(%s): sem ponte", n);
    ret32(c, p);
}
uint32_t egl_ponte_por_nome(const char *nome) {
    static const struct { const char *n; Ponte f; } t[] = {
        {"eglSwapInterval", I_eglSwapInterval}, {"eglGetCurrentContext", I_eglGetCurrentContext},
        {"eglGetCurrentSurface", I_eglGetCurrentSurface}, {"eglSwapBuffers", I_eglSwapBuffers},
        {"eglMakeCurrent", I_eglMakeCurrent}, {"eglGetError", I_eglGetError}, {"eglQuerySurface", I_eglQuerySurface},
    };
    for (size_t k = 0; k < sizeof t / sizeof t[0]; k++) if (!strcmp(t[k].n, nome)) return ponte_nova(t[k].f, t[k].n);
    uint32_t gl_desktop_por_nome(const char *nome);
    uint32_t r = gl_desktop_por_nome(nome);   /* OpenGL de desktop sobre GLES (gl_desktop.c) */
    if (r) return r;
    /* glXxxARB / glXxxEXT que a Adreno nao tem: a funcao do nucleo de mesmo nome */
    size_t n = strlen(nome);
    if (n > 5 && (!strcmp(nome + n - 3, "ARB") || !strcmp(nome + n - 3, "EXT"))) {
        char base[128]; if (n - 3 < sizeof base) { memcpy(base, nome, n - 3); base[n - 3] = 0;
            uint32_t gl_ponte_por_nome(const char *nome);
            r = gl_ponte_por_nome(base);
            if (r) { static int k; if (k++ < 60) rt_log("GL: %s -> %s", nome, base); return r; } }
    }
    return 0;
}

/* ======================================================================== */
/* ANativeWindow                                                             */
void I_ANativeWindow_fromSurface(CPU *c) { RT_PRIMEIRA("ANativeWindow_fromSurface");
    ANativeWindow *w = ANativeWindow_fromSurface(jh_env(), jh_obj(c->r[1]));
    rt_log("ANativeWindow_fromSurface -> %p", (void *)w);
    ret32(c, egl_handle(w));
}
void I_ANativeWindow_acquire(CPU *c) { RT_PRIMEIRA("ANativeWindow_acquire"); ANativeWindow_acquire(egl_obj(c->r[0])); }
/* Proporcao: o jogo pede buffers de 1280x720 e o Android esticava isso para a tela
 * inteira (19,5:9 no S25+). A janela fica no tamanho nativo; o jogo continua vendo
 * 1280x720 (eglQuerySurface) e o blit final vai para um retangulo 16:9 centrado,
 * com faixas pretas (gl_auto.c, G_glBlitFramebuffer). */
void I_ANativeWindow_setBuffersGeometry(CPU *c) { RT_PRIMEIRA("ANativeWindow_setBuffersGeometry");
    rt_log("ANativeWindow_setBuffersGeometry(%d x %d, fmt %d): janela fica no tamanho nativo (lr %08x)", (int32_t)c->r[1], (int32_t)c->r[2], (int32_t)c->r[3], c->r[14]);
    g_jan_w = (int32_t)c->r[1]; g_jan_h = (int32_t)c->r[2];
    ret32(c, (uint32_t)ANativeWindow_setBuffersGeometry(egl_obj(c->r[0]), 0, 0, (int32_t)c->r[3]));
}
#endif
