/* GLSL de desktop (o que a camada D3D9->GL da TransGaming gera: "#version 450",
 * ou 1xx/3xx) -> GLSL ES 3.20 da Adreno. Reescrita de texto:
 *   - #version N [core|compatibility]  ->  #version 320 es + precisoes
 *   - #extension de desktop: removidas (as do GLES que a Adreno tem ficam)
 *   - texture2D/texture2DLod/shadow2D/... -> texture/textureLod/...
 *   - gl_FragColor / gl_FragData[n] (compatibilidade) -> saidas declaradas
 *   - noperspective -> removido (so com extensao NV no GLES)
 * Os fontes originais e traduzidos das primeiras N compilacoes com erro vao
 * para o log e para /sdcard/Android/data/<pacote>/files/ (medicao). */
#ifndef _WIN32
#include "gl_ponte.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

typedef struct { char *p; size_t n, cap; } Buf;
static void bput(Buf *b, const char *s, size_t n) {
    if (b->n + n + 1 > b->cap) { b->cap = (b->n + n + 1) * 2; b->p = realloc(b->p, b->cap); }
    memcpy(b->p + b->n, s, n); b->n += n; b->p[b->n] = 0;
}
static void bputs(Buf *b, const char *s) { bput(b, s, strlen(s)); }

static int eh_id(char ch) { return isalnum((unsigned char)ch) || ch == '_'; }

/* troca identificadores inteiros (nao pedaco de outro nome) */
static char *troca_ids(const char *src, const char *const (*pares)[2], int np) {
    Buf b = {0};
    const char *s = src;
    while (*s) {
        if (eh_id(*s) && (s == src || !eh_id(s[-1]))) {
            const char *e = s; while (eh_id(*e)) e++;
            size_t n = (size_t)(e - s);
            int achou = 0;
            for (int k = 0; k < np; k++)
                if (strlen(pares[k][0]) == n && !memcmp(s, pares[k][0], n)) { bputs(&b, pares[k][1]); achou = 1; break; }
            if (!achou) bput(&b, s, n);
            s = e;
        } else { bput(&b, s, 1); s++; }
    }
    if (!b.p) { b.p = malloc(1); b.p[0] = 0; }
    return b.p;
}

static const char *const IDS[][2] = {
    { "texture2D", "texture" }, { "texture2DLod", "textureLod" }, { "texture2DProj", "textureProj" },
    { "texture2DProjLod", "textureProjLod" }, { "texture2DGrad", "textureGrad" }, { "texture2DGradARB", "textureGrad" },
    { "texture2DLodARB", "textureLod" }, { "texture2DProjLodARB", "textureProjLod" },
    { "texture3D", "texture" }, { "texture3DLod", "textureLod" }, { "texture3DProj", "textureProj" },
    { "textureCube", "texture" }, { "textureCubeLod", "textureLod" }, { "textureCubeLodARB", "textureLod" },
    { "textureCubeGradARB", "textureGrad" },
    { "shadow2D", "texture" }, { "shadow2DProj", "textureProj" }, { "shadow2DLod", "textureLod" },
    { "noperspective", "" },
    { "gl_FragColor", "tg_FragColor" }, { "gl_FragData", "tg_FragData" },
};

/* a linha [s, s+n) ja apareceu inteira (como linha) em ja? */
static int linha_repetida(const char *ja, const char *s, size_t n) {
    const char *t = s, *fim = s + n;
    while (t < fim && (*t == ' ' || *t == '\t')) t++;
    while (fim > t && (fim[-1] == '\n' || fim[-1] == '\r' || fim[-1] == ' ' || fim[-1] == '\t')) fim--;
    size_t m = (size_t)(fim - t);
    if (!m) return 0;
    for (const char *p = ja; p; p = strchr(p, '\n')) {
        if (*p == '\n') p++;
        const char *q = p; while (*q == ' ' || *q == '\t') q++;
        if (!strncmp(q, t, m) && (q[m] == '\n' || q[m] == '\r' || q[m] == 0)) return 1;
    }
    return 0;
}

char *glsl_para_es(const char *src, GLenum tipo) {
    Buf cab = {0}, corpo = {0};
    bputs(&cab, "#version 320 es\n");
    /* a camada costuma definir as proprias saidas (#define gl_FragData TG_fragData) */
    int usa_fragcolor = strstr(src, "gl_FragColor") != NULL && !strstr(src, "#define gl_FragColor");
    int usa_fragdata = strstr(src, "gl_FragData") != NULL && !strstr(src, "#define gl_FragData");
    /* linha a linha: #version e #extension */
    const char *s = src;
    while (*s) {
        const char *e = strchr(s, '\n'); size_t n = e ? (size_t)(e - s) + 1 : strlen(s);
        const char *t = s; while (*t == ' ' || *t == '\t') t++;
        if (!strncmp(t, "#version", 8)) { /* descartada */ }
        else if (!strncmp(t, "#extension", 10)) {
            if ((strstr(t, "GL_EXT_") || strstr(t, "GL_OES_") || strstr(t, "GL_KHR_")) && !strstr(t, "GL_EXT_draw_buffers"))
                bput(&cab, s, n);   /* draw_buffers e nucleo no ES 3 */
        } else if ((!strncmp(t, "in ", 3) || !strncmp(t, "out ", 4) || !strncmp(t, "uniform ", 8)) &&
                   corpo.p && strstr(corpo.p, "\n") && n > 1 && linha_repetida(corpo.p, s, n)) {
            /* a camada as vezes declara a mesma entrada duas vezes ("in vec4 gen0;");
             * o compilador da NVIDIA aceita, o da Adreno nao */
        } else bput(&corpo, s, n);
        s += n;
    }
    bputs(&cab, "precision highp float;\nprecision highp int;\n"
                "precision highp sampler2D;\nprecision highp samplerCube;\nprecision highp sampler3D;\n"
                "precision highp sampler2DShadow;\nprecision highp sampler2DArray;\nprecision highp samplerCubeShadow;\n"
                "precision highp isampler2D;\nprecision highp usampler2D;\n");
    if (tipo == GL_FRAGMENT_SHADER) {
        if (usa_fragcolor) bputs(&cab, "layout(location = 0) out highp vec4 tg_FragColor;\n");
        if (usa_fragdata) bputs(&cab, "layout(location = 0) out highp vec4 tg_FragData[4];\n");
    }
    char *c2 = troca_ids(corpo.p ? corpo.p : "", IDS, (int)(sizeof IDS / sizeof IDS[0]));
    if (tipo == GL_VERTEX_SHADER) {
        /* A camada supoe vertex_attribN no local N (o compilador da NVIDIA atribui
         * assim); a Adreno atribui em outra ordem e a posicao trocava de lugar com
         * a coordenada de textura. Local explicito: "in vec4 vertex_attribN;" ->
         * "layout(location = N) in vec4 vertex_attribN;" */
        Buf b2 = {0};
        const char *p = c2;
        while (*p) {
            const char *e = strchr(p, '\n'); size_t n = e ? (size_t)(e - p) + 1 : strlen(p);
            const char *t = p; while (*t == ' ' || *t == '\t') t++;
            const char *v = strstr(t, "vertex_attrib");
            int num = -1;
            if (!strncmp(t, "in ", 3) && v && v < p + n && isdigit((unsigned char)v[13])) num = atoi(v + 13);
            if (num >= 0 && !strstr(t, "layout")) {
                char pre[40]; snprintf(pre, sizeof pre, "layout(location = %d) ", num);
                bputs(&b2, pre);
            }
            bput(&b2, p, n);
            p += n;
        }
        free(c2);
        c2 = b2.p ? b2.p : calloc(1, 1);
    }
    bputs(&cab, c2);
    free(c2); free(corpo.p);
    return cab.p;
}

/* ---- ponte de glShaderSource / diagnostico -------------------------------- */
#ifdef MGS2_DEPURA
static int n_amostra;
#endif
void gl_shader_fonte(GLuint sh, GLsizei n, const GLchar *const *v, const GLint *lens) {
    Buf b = {0};
    for (GLsizei i = 0; i < n; i++) {
        if (lens && lens[i] >= 0) bput(&b, v[i], (size_t)lens[i]); else bputs(&b, v[i]);
    }
    if (!b.p) bputs(&b, "");
    GLint tipo = 0; glGetShaderiv(sh, GL_SHADER_TYPE, &tipo);
    char *es = glsl_para_es(b.p, (GLenum)tipo);
#ifdef MGS2_DEPURA
    int k = __atomic_fetch_add(&n_amostra, 1, __ATOMIC_RELAXED);
    if (k < 30) {
        char nome[160]; snprintf(nome, sizeof nome, "/sdcard/Android/data/jp.konami.mgs2hd.shield/files/shader_%03d_%s.txt", k, tipo == GL_FRAGMENT_SHADER ? "fs" : "vs");
        FILE *f = fopen(nome, "wb");
        if (f) { fputs(b.p, f); fputs("\n/* ======== traduzido ======== */\n", f); fputs(es, f); fclose(f); }
    }
#endif
    const GLchar *um = es;
    glShaderSource(sh, 1, &um, NULL);
    free(es); free(b.p);
}
#endif
