/* Formatos de textura do OpenGL de DESKTOP -> GLES 3.2 (Adreno).
 *
 * O desktop converte qualquer (formato interno, formato, tipo) em silencio; o GLES
 * so aceita as combinacoes da tabela da especificacao. A camada D3D9->GL da
 * TransGaming usa as do desktop para os formatos do D3D:
 *   A8R8G8B8  = RGBA8 + BGRA + 8_8_8_8_REV     X8R8G8B8 = RGB8 + BGRA + ...
 *   A1R5G5B5  = RGB5_A1 + BGRA + 1_5_5_5_REV   X1R5G5B5 = RGB5 + BGR(A) + 1_5_5_5_REV
 *   A4R4G4B4  = RGBA4 + BGRA + 4_4_4_4_REV     A2R10G10B10 = RGB10_A2 + BGRA + 2_10_10_10_REV
 * Aqui cada combinacao vira uma valida no GLES, convertendo os pixels quando a
 * ordem dos bits muda (o tamanho do pixel nunca muda, entao o layout da linha e
 * as opcoes de UNPACK do jogo continuam valendo). Formatos "X" (sem alfa)
 * guardam RGBA com swizzle A=1 na textura.
 * S3TC/RGTC/BPTC/norm16/BGRA8888 a Adreno 830 tem de verdade: passam direto. */
#ifndef _WIN32
#include "gl_ponte.h"
#include <GLES2/gl2ext.h>
#include <string.h>
#include <stdlib.h>

enum { CV_NADA, CV_TROCA_RB32, CV_ARGB1555, CV_XRGB1555, CV_ARGB4444, CV_XRGB4444, CV_A2RGB10_TROCA, CV_RGB565_REV, CV_U16_MEIO };

typedef struct { GLint fi; GLenum f, t; int conv, alfa1; } Fmt;

static int eh_sem_alfa(GLint fi) {
    switch (fi) {
    case GL_RGB: case GL_RGB8: case 0x8C41 /* SRGB8 */: case 0x8C40 /* SRGB */: case 0x804F /* RGB4 */:
    case 0x8050 /* RGB5 */: case 0x8052: case 0x8053: case 0x8054: return 1;
    default: return 0;
    }
}
static int eh_srgb(GLint fi) { return fi == 0x8C40 || fi == 0x8C41 || fi == 0x8C42 || fi == 0x8C43; }

/* ---- o que a GPU tem de verdade ------------------------------------------- */
int aj_int(const char *chave, int padrao);
static int cap_s3tc = -1, cap_rgtc = -1, cap_norm16 = -1;
static int tem_ext(const char *nome) {
    GLint n = 0; glGetIntegerv(GL_NUM_EXTENSIONS, &n);
    for (GLint i = 0; i < n; i++) { const char *e = (const char *)glGetStringi(GL_EXTENSIONS, (GLuint)i); if (e && !strcmp(e, nome)) return 1; }
    return 0;
}
static void caps(void) {
    if (cap_s3tc >= 0) return;
    /* dxt_cpu=1 (ajuste de teste) forca a descompressao no processador mesmo numa GPU com DXT */
    int forca = aj_int("dxt_cpu", 0);
    cap_s3tc = !forca && tem_ext("GL_EXT_texture_compression_s3tc");
    cap_rgtc = !forca && tem_ext("GL_EXT_texture_compression_rgtc");
    cap_norm16 = tem_ext("GL_EXT_texture_norm16");
    rt_log("GPU: DXT %s, RGTC %s, norm16 %s, sRGB_write_control %s", cap_s3tc ? "nativo" : "DESCOMPRIMIDO NA CPU",
           cap_rgtc ? "nativo" : "DESCOMPRIMIDO NA CPU", cap_norm16 ? "sim" : "nao (vira half float)",
           tem_ext("GL_EXT_sRGB_write_control") ? "sim" : "NAO (alvos sRGB podem clarear)");
}
int fmt_dxt_na_cpu(void) { caps(); return !cap_s3tc; }
int fmt_rgtc_na_cpu(void) { caps(); return !cap_rgtc; }

/* fi < 0: so o par (formato, tipo) de um TexSubImage/ReadPixels */
static Fmt traduz(GLint fi, GLenum f, GLenum t) {
    Fmt r = { fi, f, t, CV_NADA, 0 };
    if (t == 0x8367 /* 8_8_8_8_REV */) r.t = t = GL_UNSIGNED_BYTE;            /* little-endian: mesmos bytes */
    if (t == 0x8D61 /* HALF_FLOAT_OES */) r.t = t = GL_HALF_FLOAT;
    if (f == GL_BGRA_EXT && t == GL_UNSIGNED_BYTE) {
        r.f = GL_RGBA; r.conv = CV_TROCA_RB32;
        if (fi >= 0) { r.alfa1 = eh_sem_alfa(fi); r.fi = eh_srgb(fi) ? GL_SRGB8_ALPHA8 : GL_RGBA8; }
    } else if ((f == GL_BGRA_EXT || f == 0x80E0 /* BGR */) && t == 0x8366 /* 1_5_5_5_REV */) {
        r.f = GL_RGBA; r.t = GL_UNSIGNED_SHORT_5_5_5_1;
        int x = (fi >= 0 && (fi == 0x8050 || eh_sem_alfa(fi))) || f == 0x80E0;
        r.conv = x ? CV_XRGB1555 : CV_ARGB1555;
        if (fi >= 0) r.fi = GL_RGB5_A1;
    } else if (f == GL_BGRA_EXT && t == 0x8365 /* 4_4_4_4_REV */) {
        r.f = GL_RGBA; r.t = GL_UNSIGNED_SHORT_4_4_4_4;
        r.conv = (fi >= 0 && eh_sem_alfa(fi)) ? CV_XRGB4444 : CV_ARGB4444;
        if (fi >= 0) r.fi = GL_RGBA4;
    } else if (f == GL_BGRA_EXT && t == GL_UNSIGNED_INT_2_10_10_10_REV) {
        r.f = GL_RGBA; r.conv = CV_A2RGB10_TROCA;
        if (fi >= 0) r.fi = GL_RGB10_A2;
    } else if (f == GL_RGB && t == 0x8364 /* 5_6_5_REV */) {
        r.t = GL_UNSIGNED_SHORT_5_6_5; r.conv = CV_RGB565_REV;
        if (fi >= 0) r.fi = GL_RGB565;
    }
    if (t == GL_UNSIGNED_SHORT && (f == GL_RED || f == GL_RG || f == GL_RGBA)) {
        caps();
        if (!cap_norm16) {   /* sem EXT_texture_norm16: unorm16 -> half (mesmo tamanho de pixel) */
            r.t = GL_HALF_FLOAT; r.conv = CV_U16_MEIO;
            if (fi >= 0) r.fi = f == GL_RED ? GL_R16F : f == GL_RG ? GL_RG16F : GL_RGBA16F;
            return r;
        }
    }
    if (fi < 0) return r;
    /* interno sem tamanho: no desktop o que manda na conversao e o formato dos
     * dados (RGBA alimentado com RGB = alfa 1); o GLES exige que batam */
    if ((r.fi == GL_RGBA || r.fi == GL_RGB || r.fi == 3 || r.fi == 4) && (r.f == GL_RGB || r.f == GL_RGBA))
        r.fi = r.f;
    /* formato interno: os sem tamanho e os que so existem no desktop */
    switch (r.fi) {
    case GL_RGBA: case 4:
        r.fi = r.t == GL_FLOAT ? GL_RGBA32F : r.t == GL_HALF_FLOAT ? GL_RGBA16F : r.t == GL_UNSIGNED_SHORT ? GL_RGBA16_EXT :
               r.t == GL_UNSIGNED_SHORT_4_4_4_4 ? GL_RGBA4 : r.t == GL_UNSIGNED_SHORT_5_5_5_1 ? GL_RGB5_A1 :
               r.t == GL_UNSIGNED_INT_2_10_10_10_REV ? GL_RGB10_A2 : GL_RGBA8; break;
    case GL_RGB: case 3:
        r.fi = r.t == GL_FLOAT ? GL_RGB32F : r.t == GL_HALF_FLOAT ? GL_RGB16F : r.t == GL_UNSIGNED_SHORT ? GL_RGB16_EXT :
               r.t == GL_UNSIGNED_SHORT_5_6_5 ? GL_RGB565 : GL_RGB8; break;
    case GL_RED: case 1:
        r.fi = r.t == GL_FLOAT ? GL_R32F : r.t == GL_HALF_FLOAT ? GL_R16F : r.t == GL_UNSIGNED_SHORT ? GL_R16_EXT : GL_R8; break;
    case GL_RG: case 2:
        r.fi = r.t == GL_FLOAT ? GL_RG32F : r.t == GL_HALF_FLOAT ? GL_RG16F : r.t == GL_UNSIGNED_SHORT ? GL_RG16_EXT : GL_RG8; break;
    case GL_DEPTH_COMPONENT:
        r.fi = r.t == GL_FLOAT ? GL_DEPTH_COMPONENT32F : r.t == GL_UNSIGNED_SHORT ? GL_DEPTH_COMPONENT16 : GL_DEPTH_COMPONENT24; break;
    case 0x81A7 /* DEPTH_COMPONENT32 */: r.fi = r.t == GL_FLOAT ? GL_DEPTH_COMPONENT32F : GL_DEPTH_COMPONENT24; break;
    case GL_DEPTH_STENCIL: r.fi = GL_DEPTH24_STENCIL8; break;
    case 0x804F /* RGB4 */: case 0x8056 /* RGBA4 */: if (r.t == GL_UNSIGNED_BYTE) r.fi = GL_RGBA8; else r.fi = GL_RGBA4; break;
    case 0x8050 /* RGB5 */: r.fi = r.t == GL_UNSIGNED_SHORT_5_6_5 ? GL_RGB565 : r.t == GL_UNSIGNED_BYTE ? GL_RGB8 : GL_RGB5_A1; break;
    case 0x8052: case 0x8053: case 0x8054: r.fi = GL_RGB16_EXT; break;           /* RGB10/12/16 */
    case 0x805A: r.fi = GL_RGBA16_EXT; break;                                    /* RGBA12 */
    case GL_RGB8: if (r.t == GL_UNSIGNED_BYTE && r.f == GL_RGBA) r.fi = GL_RGBA8; break;
    case 0x8C41 /* SRGB8 */: if (r.f == GL_RGBA) r.fi = GL_SRGB8_ALPHA8; break;
    case 0x8C40 /* SRGB */: r.fi = r.f == GL_RGBA ? GL_SRGB8_ALPHA8 : GL_SRGB8; break;
    case 0x8C42 /* SRGB_ALPHA */: r.fi = GL_SRGB8_ALPHA8; break;
    }
    /* DEPTH_COMPONENT24 no GLES so aceita UNSIGNED_INT */
    if (r.fi == GL_DEPTH_COMPONENT24 && r.f == GL_DEPTH_COMPONENT && r.t != GL_UNSIGNED_INT) r.t = GL_UNSIGNED_INT;
    if (r.fi == GL_RGB8 && r.f == GL_RGB && r.t != GL_UNSIGNED_BYTE) r.fi = GL_RGB;   /* deixa o driver escolher */
    return r;
}

/* ---- conversao de pixels (mesmo tamanho de pixel) ------------------------
 * Copia da memoria do jogo e converte no mesmo passe (antes: memcpy e depois a troca byte a
 * byte, dois passes por textura). BGRA8 -> RGBA8 em palavras de 32 bits (o clang vetoriza). */
static void converte(int cv, uint8_t *d, const uint8_t *o, size_t n) {
    switch (cv) {
    case CV_TROCA_RB32: {
        size_t i = 0;
        for (; i + 4 <= n; i += 4) {
            uint32_t v; memcpy(&v, o + i, 4);
            v = (v & 0xff00ff00u) | ((v >> 16) & 0xffu) | ((v & 0xffu) << 16);
            memcpy(d + i, &v, 4);
        }
    } break;
    case CV_ARGB1555: case CV_XRGB1555:
        for (size_t i = 0; i + 2 <= n; i += 2) {
            uint16_t v; memcpy(&v, o + i, 2);
            uint16_t a = cv == CV_XRGB1555 ? 1 : (v >> 15);
            v = (uint16_t)(((v & 0x7fff) << 1) | a); memcpy(d + i, &v, 2);
        } break;
    case CV_ARGB4444: case CV_XRGB4444:
        for (size_t i = 0; i + 2 <= n; i += 2) {
            uint16_t v; memcpy(&v, o + i, 2);
            uint16_t a = cv == CV_XRGB4444 ? 0xf : (v >> 12);
            v = (uint16_t)(((v & 0x0fff) << 4) | a); memcpy(d + i, &v, 2);
        } break;
    case CV_A2RGB10_TROCA:
        for (size_t i = 0; i + 4 <= n; i += 4) {
            uint32_t v; memcpy(&v, o + i, 4);
            uint32_t r = (v >> 20) & 0x3ff, b = v & 0x3ff;   /* BGRA: B nos bits baixos */
            v = (v & 0xc00ffc00u) | (b << 20) | r; memcpy(d + i, &v, 4);
        } break;
    case CV_U16_MEIO:      /* unorm16 -> binary16 de v/65535 */
        for (size_t i = 0; i + 2 <= n; i += 2) {
            uint16_t v; memcpy(&v, o + i, 2);
            float f = v / 65535.0f;
            uint32_t u; memcpy(&u, &f, 4);
            uint16_t hh;
            if (f < 6.103515625e-05f) hh = (uint16_t)(f / 5.9604644775390625e-08f + 0.5f);      /* subnormal */
            else hh = (uint16_t)((((u >> 23) - 112) << 10) | ((u >> 13) & 0x3ff));
            memcpy(d + i, &hh, 2);
        } break;
    case CV_RGB565_REV:
        for (size_t i = 0; i + 2 <= n; i += 2) {
            uint16_t v; memcpy(&v, o + i, 2);
            v = (uint16_t)(((v & 0x1f) << 11) | (v & 0x7e0) | (v >> 11)); memcpy(d + i, &v, 2);
        } break;
    default: memcpy(d, o, n);
    }
    /* sobra que nao fecha um pixel (o buffer pedido inclui folga): copiada como estava */
    size_t u = (cv == CV_TROCA_RB32 || cv == CV_A2RGB10_TROCA) ? 4 : cv == CV_NADA ? 1 : 2;
    if (n % u) memcpy(d + n - n % u, o + n - n % u, n % u);
}

static int bpp_de(GLenum f, GLenum t) {
    switch (t) {
    case GL_UNSIGNED_SHORT_5_5_5_1: case GL_UNSIGNED_SHORT_4_4_4_4: case GL_UNSIGNED_SHORT_5_6_5: return 2;
    case GL_UNSIGNED_INT_2_10_10_10_REV: return 4;
    case GL_UNSIGNED_BYTE: return f == GL_RGBA ? 4 : f == GL_RGB ? 3 : f == GL_RG ? 2 : 1;
    case GL_UNSIGNED_SHORT: case GL_HALF_FLOAT: return f == GL_RGBA ? 8 : f == GL_RGB ? 6 : f == GL_RG ? 4 : 2;
    }
    return 4;
}

/* devolve o ponteiro de pixels para o driver (copia convertida se preciso; *livre = copia) */
extern volatile long long g_est[12];
static const void *pixels(const Fmt *x, uint32_t p, GLsizei w, GLsizei h, GLsizei d, GLuint pbo, void **livre) {
    *livre = NULL;
    g_est[7] += (long long)w * h * d * 4;
    if (pbo) {
        if (x->conv) { static int v; if (!v++) rt_log("textura: conversao de formato com PBO ligado ainda nao feita"); }
        return (const void *)(uintptr_t)p;
    }
    if (!p) return NULL;
    if (!x->conv) return g_mem + p;
    GLint rl = 0, al = 4, sr = 0, sp = 0, ih = 0, si = 0;
    glGetIntegerv(GL_UNPACK_ROW_LENGTH, &rl); glGetIntegerv(GL_UNPACK_ALIGNMENT, &al);
    glGetIntegerv(GL_UNPACK_SKIP_ROWS, &sr); glGetIntegerv(GL_UNPACK_SKIP_PIXELS, &sp);
    glGetIntegerv(GL_UNPACK_IMAGE_HEIGHT, &ih); glGetIntegerv(GL_UNPACK_SKIP_IMAGES, &si);
    int bpp = bpp_de(x->f, x->t);
    size_t linha = (size_t)(rl ? rl : w) * (size_t)bpp;
    linha = (linha + (size_t)al - 1) / (size_t)al * (size_t)al;
    size_t alt = (size_t)(ih ? ih : h);
    size_t n = linha * alt * (size_t)(d + si) + linha * (size_t)sr + (size_t)sp * (size_t)bpp + linha;
    uint8_t *c = malloc(n);
    converte(x->conv, c, g_mem + p, n);
    *livre = c;
    return c;
}

/* ---- erros atribuidos a chamada que os causou ----------------------------
 * glGetError espera o driver (thread propria na Adreno e na Mali) esvaziar a fila: antes,
 * DOIS por subida de textura, e a CPU parava justo onde mais se sobe textura (videos, codec,
 * troca de area). Agora so na primeira vez de cada combinacao (chamada, interno, formato, tipo),
 * que e quando um formato sem suporte aparece; depois o erro, se houver, fica para o jogo. */
__thread GLenum t_erro_gl_pendente;    /* devolvido pelo proximo glGetError do jogo */
#define COMBOS 512
static uint64_t combos[COMBOS];
static int combo_nova(int chamada, GLint fi, GLenum f, GLenum t) {
    uint64_t k = ((uint64_t)(uint32_t)chamada << 60) ^ ((uint64_t)(uint32_t)fi << 32) ^ ((uint64_t)(f & 0xffff) << 16) ^ (t & 0xffff) ^ 1;
    unsigned h = (unsigned)((k * 0x9E3779B97F4A7C15ull) >> 55) & (COMBOS - 1);
    for (unsigned i = 0; i < COMBOS; i++, h = (h + 1) & (COMBOS - 1)) {
        uint64_t v = __atomic_load_n(&combos[h], __ATOMIC_RELAXED);
        if (v == k) return 0;
        if (!v) { uint64_t z = 0; if (__atomic_compare_exchange_n(&combos[h], &z, k, 0, __ATOMIC_RELAXED, __ATOMIC_RELAXED)) return 1;
                  if (z == k) return 0; }
    }
    return 0;                          /* tabela cheia: para de conferir */
}
static void confere(const char *fn, GLint fi, GLenum f, GLenum t, const Fmt *x) {
    GLenum e = glGetError();
    if (!e) return;
    if (!t_erro_gl_pendente) t_erro_gl_pendente = e;
    static int n; if (__atomic_fetch_add(&n, 1, __ATOMIC_RELAXED) < 120)
        rt_log("%s: erro %x com int %x fmt %x tipo %x (pedido: int %x fmt %x tipo %x)", fn, e, x->fi, x->f, x->t, fi, f, t);
}
static void alfa_um(GLenum alvo) {
    GLenum a = (alvo >= GL_TEXTURE_CUBE_MAP_POSITIVE_X && alvo <= GL_TEXTURE_CUBE_MAP_NEGATIVE_Z) ? GL_TEXTURE_CUBE_MAP : alvo;
    glTexParameteri(a, GL_TEXTURE_SWIZZLE_A, GL_ONE);
}

void fmt_tex_image2d(GLenum alvo, GLint l, GLint fi, GLsizei w, GLsizei h, GLint b, GLenum f, GLenum t, uint32_t p, GLuint pbo) {
    int nova = combo_nova(1, fi, f, t);
    if (nova) glGetError();
    Fmt x = traduz(fi, f, t);
    void *livre; const void *px = pixels(&x, p, w, h, 1, pbo, &livre);
    glTexImage2D(alvo, l, x.fi, w, h, b, x.f, x.t, px);
    free(livre);
    if (nova) confere("glTexImage2D", fi, f, t, &x);
    if (x.alfa1 && l == 0) alfa_um(alvo);
}
void fmt_tex_sub_image2d(GLenum alvo, GLint l, GLint xo, GLint yo, GLsizei w, GLsizei h, GLenum f, GLenum t, uint32_t p, GLuint pbo) {
    int nova = combo_nova(2, -1, f, t);
    if (nova) glGetError();
    Fmt x = traduz(-1, f, t);
    void *livre; const void *px = pixels(&x, p, w, h, 1, pbo, &livre);
    glTexSubImage2D(alvo, l, xo, yo, w, h, x.f, x.t, px);
    free(livre);
    if (nova) confere("glTexSubImage2D", -1, f, t, &x);
}
void fmt_tex_image3d(GLenum alvo, GLint l, GLint fi, GLsizei w, GLsizei h, GLsizei d, GLint b, GLenum f, GLenum t, uint32_t p, GLuint pbo) {
    int nova = combo_nova(3, fi, f, t);
    if (nova) glGetError();
    Fmt x = traduz(fi, f, t);
    void *livre; const void *px = pixels(&x, p, w, h, d, pbo, &livre);
    glTexImage3D(alvo, l, x.fi, w, h, d, b, x.f, x.t, px);
    free(livre);
    if (nova) confere("glTexImage3D", fi, f, t, &x);
    if (x.alfa1 && l == 0) alfa_um(alvo);
}
void fmt_tex_sub_image3d(GLenum alvo, GLint l, GLint xo, GLint yo, GLint zo, GLsizei w, GLsizei h, GLsizei d, GLenum f, GLenum t, uint32_t p, GLuint pbo) {
    int nova = combo_nova(4, -1, f, t);
    if (nova) glGetError();
    Fmt x = traduz(-1, f, t);
    void *livre; const void *px = pixels(&x, p, w, h, d, pbo, &livre);
    glTexSubImage3D(alvo, l, xo, yo, zo, w, h, d, x.f, x.t, px);
    free(livre);
    if (nova) confere("glTexSubImage3D", -1, f, t, &x);
}
/* formato interno de armazenamento (TexStorage / Renderbuffer): so o nome */
GLenum fmt_interno(GLenum fi, int renderbuffer) {
    caps();
    if (!cap_norm16) { if (fi == 0x822A) return GL_R16F; if (fi == 0x822C) return GL_RG16F; if (fi == 0x805B) return GL_RGBA16F; }
    if (!cap_s3tc && !renderbuffer) {   /* TexStorage em formato DXT: armazena RGBA8 (ver fmt_comprimida*) */
        switch (fi) { case 0x83F0: case 0x83F1: case 0x83F2: case 0x83F3: return GL_RGBA8;
                      case 0x8C4C: case 0x8C4D: case 0x8C4E: case 0x8C4F: return GL_SRGB8_ALPHA8; }
    }
    if (!cap_rgtc && !renderbuffer) { if (fi == 0x8DBB) return GL_R8; if (fi == 0x8DBD) return GL_RG8; }
    /* renderbuffer sRGB (o backbuffer da camada): no desktop, com GL_FRAMEBUFFER_SRGB
     * desligado (a camada nunca liga), nao ha conversao nem ao escrever nem no blit.
     * No GLES o blit de um alvo sRGB DECODIFICA sempre (imagem escura) -> RGBA8 puro. */
    if (renderbuffer && (fi == 0x8C40 || fi == 0x8C41 || fi == 0x8C42 || fi == 0x8C43)) return GL_RGBA8;
    switch (fi) {
    case GL_RGBA: case 0x8056: return renderbuffer ? GL_RGBA8 : fi == GL_RGBA ? GL_RGBA8 : GL_RGBA4;
    case GL_RGB: return GL_RGB8;
    case 0x804F: return GL_RGBA4;                 /* RGB4 */
    case 0x8050: return GL_RGB565;                /* RGB5 */
    case GL_DEPTH_COMPONENT: case 0x81A7: return GL_DEPTH_COMPONENT24;
    case GL_DEPTH_STENCIL: return GL_DEPTH24_STENCIL8;
    case 0x8C40: return renderbuffer ? GL_SRGB8_ALPHA8 : GL_SRGB8;
    case 0x8C41: return renderbuffer ? GL_SRGB8_ALPHA8 : GL_SRGB8;   /* SRGB8 nao e renderizavel no GLES */
    case GL_RGB8: return renderbuffer ? GL_RGB8 : GL_RGB8;
    case 0x8C42: return GL_SRGB8_ALPHA8;
    case 0x8052: case 0x8053: case 0x8054: return GL_RGB16_EXT;
    case 0x805A: return GL_RGBA16_EXT;
    }
    return fi;
}
void fmt_read_pixels(GLint x0, GLint y0, GLsizei w, GLsizei h, GLenum f, GLenum t, uint32_t p, GLuint pbo) {
    GLenum t2 = t == 0x8367 ? GL_UNSIGNED_BYTE : t;   /* BGRA+REV = BGRA_EXT+UBYTE (EXT_read_format_bgra) */
    g_est[9]++;                                       /* leitura da GPU pela CPU: espera a GPU */
    glReadPixels(x0, y0, w, h, f, t2, pbo ? (void *)(uintptr_t)p : (void *)(g_mem + p));
}

/* ---- DXT / RGTC sem suporte na GPU (Mali, PowerVR) --------------------------
 * Descomprime no processador (s3tc.c, conferido contra o Pillow) e sobe como
 * RGBA8 / R8 / RG8. Devolve 1 se tratou; 0 = a GPU aceita, sobe comprimido. */
int s3tc_tipo(uint32_t fmt);
int s3tc_srgb(uint32_t fmt);
int s3tc_bpp_saida(int tipo);
uint32_t s3tc_tamanho(int tipo, int w, int h);
int s3tc_descomprime(int tipo, int w, int h, const uint8_t *src, uint32_t n, uint8_t *dst);

static int precisa_cpu(GLenum fmt, int *tipo) {
    *tipo = s3tc_tipo(fmt);
    if (!*tipo) return 0;
    caps();
    return *tipo <= 4 ? !cap_s3tc : !cap_rgtc;
}
static void fmt_saida(int tipo, GLenum fmt, GLint *fi, GLenum *f) {
    if (tipo == 5) { *fi = GL_R8; *f = GL_RED; }
    else if (tipo == 6) { *fi = GL_RG8; *f = GL_RG; }
    else { *fi = s3tc_srgb(fmt) ? GL_SRGB8_ALPHA8 : GL_RGBA8; *f = GL_RGBA; }
}
/* le os dados comprimidos (memoria do jogo ou PBO ligado) e descomprime d fatias */
static uint8_t *descomprime_dados(int tipo, GLsizei w, GLsizei h, GLsizei d, uint32_t p, GLsizei n, GLuint pbo) {
    const uint8_t *src = NULL; void *mapa = NULL;
    if (pbo) {
        mapa = glMapBufferRange(GL_PIXEL_UNPACK_BUFFER, (GLintptr)p, n, GL_MAP_READ_BIT);
        src = mapa;
    } else if (p) src = g_mem + p;
    if (!src) return NULL;
    if (d < 1) d = 1;
    uint32_t fatia = s3tc_tamanho(tipo, w, h);
    size_t saida = (size_t)w * (size_t)h * (size_t)s3tc_bpp_saida(tipo);
    uint8_t *dst = malloc(saida * (size_t)d);
    int ok = dst != NULL;
    for (GLsizei z = 0; z < d && ok; z++)
        ok = (uint32_t)n >= (uint32_t)(z + 1) * fatia &&
             s3tc_descomprime(tipo, w, h, src + (size_t)z * fatia, fatia, dst + (size_t)z * saida);
    if (mapa) glUnmapBuffer(GL_PIXEL_UNPACK_BUFFER);
    if (!ok) { free(dst); return NULL; }
    return dst;
}
/* sobe dados ja descomprimidos: linhas justas, sem PBO ligado, depois restaura */
#define SOBE(expr) do { \
    GLint al = 4, rl = 0, sr = 0, sp = 0; \
    glGetIntegerv(GL_UNPACK_ALIGNMENT, &al); glGetIntegerv(GL_UNPACK_ROW_LENGTH, &rl); \
    glGetIntegerv(GL_UNPACK_SKIP_ROWS, &sr); glGetIntegerv(GL_UNPACK_SKIP_PIXELS, &sp); \
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); glPixelStorei(GL_UNPACK_ROW_LENGTH, 0); \
    glPixelStorei(GL_UNPACK_SKIP_ROWS, 0); glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0); \
    if (pbo) glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0); \
    expr; \
    if (pbo) glBindBuffer(GL_PIXEL_UNPACK_BUFFER, pbo); \
    glPixelStorei(GL_UNPACK_ALIGNMENT, al); glPixelStorei(GL_UNPACK_ROW_LENGTH, rl); \
    glPixelStorei(GL_UNPACK_SKIP_ROWS, sr); glPixelStorei(GL_UNPACK_SKIP_PIXELS, sp); } while (0)

static void avisa(int tipo) {
    static int n; if (!n++) rt_log("textura comprimida (tipo %d) descomprimida na CPU: a GPU nao tem o formato", tipo);
}
int fmt_comprimida2d(GLenum alvo, GLint l, GLenum fmt, GLsizei w, GLsizei h, GLint b, GLsizei n, uint32_t p, GLuint pbo) {
    int tipo; if (!precisa_cpu(fmt, &tipo)) return 0;
    avisa(tipo);
    GLint fi; GLenum f; fmt_saida(tipo, fmt, &fi, &f);
    uint8_t *px = descomprime_dados(tipo, w, h, 1, p, n, pbo);
    SOBE(glTexImage2D(alvo, l, fi, w, h, b, f, GL_UNSIGNED_BYTE, px));
    free(px);
    return 1;
}
int fmt_comprimida_sub2d(GLenum alvo, GLint l, GLint x, GLint y, GLsizei w, GLsizei h, GLenum fmt, GLsizei n, uint32_t p, GLuint pbo) {
    int tipo; if (!precisa_cpu(fmt, &tipo)) return 0;
    GLint fi; GLenum f; fmt_saida(tipo, fmt, &fi, &f);
    uint8_t *px = descomprime_dados(tipo, w, h, 1, p, n, pbo);
    if (px) SOBE(glTexSubImage2D(alvo, l, x, y, w, h, f, GL_UNSIGNED_BYTE, px));
    free(px);
    return 1;
}
int fmt_comprimida3d(GLenum alvo, GLint l, GLenum fmt, GLsizei w, GLsizei h, GLsizei d, GLint b, GLsizei n, uint32_t p, GLuint pbo) {
    int tipo; if (!precisa_cpu(fmt, &tipo)) return 0;
    avisa(tipo);
    GLint fi; GLenum f; fmt_saida(tipo, fmt, &fi, &f);
    uint8_t *px = descomprime_dados(tipo, w, h, d, p, n, pbo);
    SOBE(glTexImage3D(alvo, l, fi, w, h, d, b, f, GL_UNSIGNED_BYTE, px));
    free(px);
    return 1;
}
int fmt_comprimida_sub3d(GLenum alvo, GLint l, GLint x, GLint y, GLint z, GLsizei w, GLsizei h, GLsizei d, GLenum fmt, GLsizei n, uint32_t p, GLuint pbo) {
    int tipo; if (!precisa_cpu(fmt, &tipo)) return 0;
    GLint fi; GLenum f; fmt_saida(tipo, fmt, &fi, &f);
    uint8_t *px = descomprime_dados(tipo, w, h, d, p, n, pbo);
    if (px) SOBE(glTexSubImage3D(alvo, l, x, y, z, w, h, d, f, GL_UNSIGNED_BYTE, px));
    free(px);
    return 1;
}
#endif
