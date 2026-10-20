/* Descompressao de DXT1/DXT3/DXT5 (BC1-3) e BC4/BC5 (RGTC) para RGBA8 / R8 / RG8.
 *
 * Para GPUs sem GL_EXT_texture_compression_s3tc / _rgtc no GLES (Mali, PowerVR):
 * as texturas do MGS2 sao DXT. Sem isto o glCompressedTexImage2D falha e a camada
 * fica sem textura. Validado contra o decodificador "bcn" do Pillow (s3tc_teste.py).
 *
 * Sem dependencia de GL: compila no PC para o teste. */
#include <stdint.h>
#include <string.h>

static void cor565(uint16_t c, uint8_t *o) {
    uint32_t r = (c >> 11) & 31, g = (c >> 5) & 63, b = c & 31;
    o[0] = (uint8_t)((r << 3) | (r >> 2));
    o[1] = (uint8_t)((g << 2) | (g >> 4));
    o[2] = (uint8_t)((b << 3) | (b >> 2));
}

/* bloco de cor (8 bytes) -> 16 pixels RGBA. dxt1: com o modo de 3 cores + transparente */
static void bloco_cor(const uint8_t *b, uint8_t px[16][4], int dxt1) {
    uint16_t c0 = (uint16_t)(b[0] | b[1] << 8), c1 = (uint16_t)(b[2] | b[3] << 8);
    uint8_t p[4][4];
    cor565(c0, p[0]); cor565(c1, p[1]);
    p[0][3] = p[1][3] = 255;
    if (c0 > c1 || !dxt1) {
        for (int k = 0; k < 3; k++) {
            p[2][k] = (uint8_t)((2 * p[0][k] + p[1][k]) / 3);
            p[3][k] = (uint8_t)((p[0][k] + 2 * p[1][k]) / 3);
        }
        p[2][3] = p[3][3] = 255;
    } else {
        for (int k = 0; k < 3; k++) { p[2][k] = (uint8_t)((p[0][k] + p[1][k]) / 2); p[3][k] = 0; }
        p[2][3] = 255; p[3][3] = 0;
    }
    uint32_t idx = (uint32_t)b[4] | (uint32_t)b[5] << 8 | (uint32_t)b[6] << 16 | (uint32_t)b[7] << 24;
    for (int i = 0; i < 16; i++) memcpy(px[i], p[(idx >> (2 * i)) & 3], 4);
}

/* bloco de canal unico BC4/alfa do DXT5 (8 bytes) -> 16 valores */
static void bloco_canal(const uint8_t *b, uint8_t v[16]) {
    uint32_t a0 = b[0], a1 = b[1];
    uint8_t t[8];
    t[0] = (uint8_t)a0; t[1] = (uint8_t)a1;
    if (a0 > a1) {
        for (int k = 1; k <= 6; k++) t[k + 1] = (uint8_t)(((7 - k) * a0 + k * a1) / 7);
    } else {
        for (int k = 1; k <= 4; k++) t[k + 1] = (uint8_t)(((5 - k) * a0 + k * a1) / 5);
        t[6] = 0; t[7] = 255;
    }
    uint64_t idx = 0;
    for (int k = 0; k < 6; k++) idx |= (uint64_t)b[2 + k] << (8 * k);
    for (int i = 0; i < 16; i++) v[i] = t[(idx >> (3 * i)) & 7];
}

/* formato GL -> codigo: 1 DXT1 rgb, 2 DXT1 rgba, 3 DXT3, 4 DXT5, 5 BC4, 6 BC5 (0 = nao e) */
int s3tc_tipo(uint32_t fmt) {
    switch (fmt) {
    case 0x83F0: case 0x8C4C: return 1;      /* COMPRESSED_RGB_S3TC_DXT1 (e sRGB) */
    case 0x83F1: case 0x8C4D: return 2;      /* RGBA_DXT1 */
    case 0x83F2: case 0x8C4E: return 3;      /* DXT3 */
    case 0x83F3: case 0x8C4F: return 4;      /* DXT5 */
    case 0x8DBB: return 5;                   /* RED_RGTC1 (BC4 unorm) */
    case 0x8DBD: return 6;                   /* RG_RGTC2 (BC5 unorm) */
    }
    return 0;
}
int s3tc_srgb(uint32_t fmt) { return fmt >= 0x8C4C && fmt <= 0x8C4F; }
/* bytes por pixel da saida: 4 (RGBA8), 1 (R8) ou 2 (RG8) */
int s3tc_bpp_saida(int tipo) { return tipo == 5 ? 1 : tipo == 6 ? 2 : 4; }
/* tamanho dos dados comprimidos de uma imagem w x h */
uint32_t s3tc_tamanho(int tipo, int w, int h) {
    uint32_t bw = (uint32_t)(w + 3) / 4, bh = (uint32_t)(h + 3) / 4;
    return bw * bh * ((tipo == 1 || tipo == 2 || tipo == 5) ? 8u : 16u);
}

/* descomprime w x h de 'src' para 'dst' (linhas contiguas, s3tc_bpp_saida bytes/pixel).
 * Devolve 0 se 'n' (bytes disponiveis) nao bastar. */
int s3tc_descomprime(int tipo, int w, int h, const uint8_t *src, uint32_t n, uint8_t *dst) {
    if (!tipo || n < s3tc_tamanho(tipo, w, h)) return 0;
    int bpp = s3tc_bpp_saida(tipo);
    uint32_t passo = (tipo == 1 || tipo == 2 || tipo == 5) ? 8 : 16;
    const uint8_t *b = src;
    for (int by = 0; by < h; by += 4)
        for (int bx = 0; bx < w; bx += 4, b += passo) {
            uint8_t px[16][4];
            if (tipo <= 2) {
                bloco_cor(b, px, 1);
            } else if (tipo == 3) {
                bloco_cor(b + 8, px, 0);
                for (int i = 0; i < 16; i++) { uint32_t a = (b[i / 2] >> (4 * (i & 1))) & 15; px[i][3] = (uint8_t)(a * 17); }
            } else if (tipo == 4) {
                uint8_t a[16];
                bloco_cor(b + 8, px, 0);
                bloco_canal(b, a);
                for (int i = 0; i < 16; i++) px[i][3] = a[i];
            } else if (tipo == 5) {
                uint8_t r[16]; bloco_canal(b, r);
                for (int i = 0; i < 16; i++) px[i][0] = r[i];
            } else {
                uint8_t r[16], g[16]; bloco_canal(b, r); bloco_canal(b + 8, g);
                for (int i = 0; i < 16; i++) { px[i][0] = r[i]; px[i][1] = g[i]; }
            }
            for (int y = 0; y < 4 && by + y < h; y++)
                for (int x = 0; x < 4 && bx + x < w; x++)
                    memcpy(dst + ((size_t)(by + y) * (size_t)w + (size_t)(bx + x)) * (size_t)bpp, px[y * 4 + x], (size_t)bpp);
        }
    return 1;
}
