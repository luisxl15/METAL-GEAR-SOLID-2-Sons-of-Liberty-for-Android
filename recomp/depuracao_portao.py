"""Poe atras de #ifdef MGS2_DEPURA os diagnosticos acrescentados a mao no runtime
durante o arranque do jogo no aparelho (logs com glGetIntegerv a cada chamada,
GL debug output sincrono, amostras de shader, vertices, despejo do FBO...).

Idempotente: so embrulha o que ainda nao esta embrulhado. Imprime QUANTOS blocos
embrulhou por arquivo (um verificador que nao conta mente "0 problemas").

    python depuracao_portao.py
"""
import os, re

AQUI = os.path.dirname(os.path.abspath(__file__))
RT = os.path.join(AQUI, 'runtime')

UMA_LINHA = [
    re.compile(r'^\s*\{ static int _?n;.*\brt_log\('),            # { static int n; if (..) rt_log(...); }
    re.compile(r'^\s*if \(a0 == 0x8DB9\) \{ static int n;'),      # glEnable/glDisable(GL_FRAMEBUFFER_SRGB)
    re.compile(r'^\s*\{ void gl_mostra_vertices'),                # chamada da amostra de vertices
    re.compile(r'^\s*rt_log\("(DeviceState\.setState|DeviceInfo\.addDevice)'),
    re.compile(r'^\s*\{ static int n; if \(n\+\+ < \d+\) rt_log\("(eglMakeCurrent|eglQuerySurface)'),
]
DUAS_LINHAS = [re.compile(r'^\s*\{ static int _n; GLint pr = 0; glGetIntegerv\(GL_CURRENT_PROGRAM')]
BLOCO = re.compile(r'^(\s*)\{\s+/\* (medicao|amostra)')     # bloco "{ /* medicao ... }" ate o "}" de mesmo recuo


def embrulha(linhas):
    out, n, i = [], 0, 0
    while i < len(linhas):
        l = linhas[i]
        ja = i > 0 and linhas[i - 1].strip() == '#ifdef MGS2_DEPURA'
        if not ja and any(r.search(l) for r in UMA_LINHA):
            out += ['#ifdef MGS2_DEPURA\n', l, '#endif\n']; n += 1; i += 1; continue
        if not ja and any(r.search(l) for r in DUAS_LINHAS):
            out += ['#ifdef MGS2_DEPURA\n', l, linhas[i + 1], '#endif\n']; n += 1; i += 2; continue
        m = BLOCO.match(l)
        if m and not ja:
            recuo = m.group(1)
            j = i + 1
            while j < len(linhas) and linhas[j].rstrip('\r\n') != recuo + '}':
                j += 1
            out += ['#ifdef MGS2_DEPURA\n'] + linhas[i:j + 1] + ['#endif\n']; n += 1; i = j + 1; continue
        out.append(l); i += 1
    return out, n


def main():
    total = 0
    for nome in ('gl_auto.c', 'gl_manual.c', 'jni_auto.c', 'libc_manual.c', 'pontes_auto.c', 'gl_formato.c'):
        p = os.path.join(RT, nome)
        with open(p, encoding='utf-8', newline='') as f:
            linhas = f.readlines()
        novas, n = embrulha(linhas)
        if n:
            with open(p, 'w', encoding='utf-8', newline='') as f:
                f.writelines(novas)
        print(f'  {nome}: {n} blocos de diagnostico embrulhados')
        total += n
    print(f'total: {total}')


if __name__ == '__main__':
    main()
