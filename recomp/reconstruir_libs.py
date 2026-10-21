"""Reconstroi as duas bibliotecas ARM32 (recomp/libs/) a partir das imagens relocadas que vao
dentro de um APK nosso (lib/arm64-v8a/libmgs2img_{gnustl,jogo}.so), para recompilar sem o
base.apk original do SHIELD.

A imagem e o ELF carregado na base fixa (0x01000000 / 0x02000000) com as relocacoes ja
aplicadas. Os segmentos PT_LOAD estao inteiros nela; so os cabecalhos de secao ficaram de
fora (vem depois do ultimo segmento no arquivo). Daqui:
  - desfaz as relocacoes (RELATIVE: tira a base; ABS32: tira o endereco resolvido;
    GLOB_DAT/JUMP_SLOT: 0, o recompilador nao le o valor original);
  - remonta as secoes que o elf32.py le, pelo PT_DYNAMIC e pelo PT_ARM_EXIDX:
    .dynsym .dynstr .rel.dyn .rel.plt .plt .text .init_array .ARM.exidx
    .text vai do fim da .plt (PLT ARM: 20 + 12 por JUMP_SLOT) ao inicio da .ARM.extab
    (menor alvo de entrada nao-inline da exidx);
  - confere: imagem_relocada() do recompilador sobre a reconstrucao tem de dar a imagem
    do APK byte a byte.

    python recomp/reconstruir_libs.py [apk nosso]  ->  recomp/libs/libMGS2HD.so, libgnustl_shared.so
"""
import os, struct, sys, zipfile

AQUI = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, AQUI)
LIBS = os.path.join(AQUI, 'libs')
BASES = {'libgnustl_shared.so': 0x01000000, 'libMGS2HD.so': 0x02000000}
IMG = {'libgnustl_shared.so': 'lib/arm64-v8a/libmgs2img_gnustl.so', 'libMGS2HD.so': 'lib/arm64-v8a/libmgs2img_jogo.so'}
DADOS_BASE, IMPORT_BASE = 0x00f00000, 0xfff00000


def u32(d, a):
    return struct.unpack_from('<I', d, a)[0]


class Imagem:
    def __init__(self, nome, d):
        self.nome, self.d, self.base = nome, d, BASES[nome]
        phoff, phnum = u32(d, 0x1c), struct.unpack_from('<H', d, 0x2c)[0]
        self.ph = [struct.unpack_from('<8I', d, phoff + 32 * i) for i in range(phnum)]
        self.loads = [p for p in self.ph if p[0] == 1]
        din = next(p for p in self.ph if p[0] == 2)
        self.dyn = {}
        for a in range(din[2], din[2] + din[4], 8):
            t, v = struct.unpack_from('<II', d, a)
            if t == 0:
                break
            self.dyn.setdefault(t, v)
        self.exidx = next(p for p in self.ph if p[0] == 0x70000001)
        ds, st = self.dyn[6], self.dyn[5]
        nsym = u32(d, self.dyn[4] + 4)                 # nchain do DT_HASH
        self.syms = []
        for i in range(nsym):
            n, v, sz, info, oth, shn = struct.unpack_from('<IIIBBH', d, ds + 16 * i)
            self.syms.append(dict(nome=d[st + n:d.index(b'\0', st + n)].decode(), va=v, tipo=info & 0xf, shn=shn))
        self.rels = []
        for ini, tam in ((self.dyn[17], self.dyn[18]), (self.dyn[23], self.dyn[2])):
            for k in range(tam // 8):
                onde, info = struct.unpack_from('<II', d, ini + 8 * k)
                self.rels.append((onde, info & 0xff, self.syms[info >> 8]['nome'] if info >> 8 else None))
        self.exports = {s['nome']: (s['va'] & ~1, s['tipo']) for s in self.syms if s['shn'] and s['nome']}

    def secoes(self):
        d, dy = self.d, self.dyn
        n_plt = dy[2] // 8
        plt = (dy[23] + dy[2] + 3) & ~3
        if u32(d, plt) != 0xe52de004:                  # push {lr}: PLT0
            raise SystemExit(f'{self.nome}: PLT0 nao esta em {plt:#x}')
        t0 = plt + 20 + 12 * n_plt
        ex0, exn = self.exidx[2], self.exidx[5]
        extab = []
        for k in range(exn // 8):
            w = u32(d, ex0 + 8 * k + 4)
            if w != 1 and not w & 0x80000000:
                o = w & 0x7fffffff
                extab.append((ex0 + 8 * k + 4 + (o - 0x80000000 if o & 0x40000000 else o)) & 0xffffffff)
        t1 = min(extab)
        return [  # nome, tipo, flags, va, tam, ent
            ('.dynsym', 11, 2, dy[6], 16 * len(self.syms), 16),
            ('.dynstr', 3, 2, dy[5], dy[10], 0),
            ('.rel.dyn', 9, 2, dy[17], dy[18], 8),
            ('.rel.plt', 9, 2, dy[23], dy[2], 8),
            ('.plt', 1, 6, plt, t0 - plt, 0),
            ('.text', 1, 6, t0, t1 - t0, 0),
            ('.ARM.exidx', 0x70000001, 0x82, ex0, exn, 8),
            ('.init_array', 14, 3, dy[25], dy[27], 4),
        ]


def resolvedor(gnu, jogo):
    """o mesmo resolve() do recompilar.py"""
    nomes_import, dados_import = set(), set()
    for lib in (gnu, jogo):
        for s in lib.syms:
            if s['shn'] or not s['nome'] or lib is jogo and s['nome'] in gnu.exports:
                continue
            (dados_import if s['tipo'] == 1 else nomes_import).add(s['nome'])
    end_import = {n: IMPORT_BASE + 8 * k for k, n in enumerate(sorted(nomes_import))}
    end_dados = {n: DADOS_BASE + 0x100 * k for k, n in enumerate(sorted(dados_import))}

    def resolve(nome, lib):
        if lib is jogo and nome in gnu.exports:
            ad, t = gnu.exports[nome]
            return gnu.base + ad | (1 if t == 2 else 0)
        if nome in end_dados:
            return end_dados[nome]
        if nome in end_import:
            return end_import[nome]
        ad, t = lib.exports[nome]
        return lib.base + ad | (1 if (t == 2 and lib.nome.startswith('libgnustl')) else 0)
    return resolve


def remonta(lib, resolve):
    img = bytearray(lib.d)
    for o, ty, s in lib.rels:
        v = u32(img, o)
        if ty == 23:
            v -= lib.base
        elif ty == 2:
            v -= resolve(s, lib)
        elif ty in (21, 22):
            v = 0
        else:
            raise SystemExit(f'relocacao {ty} nao tratada')
        struct.pack_into('<I', img, o, v & 0xffffffff)
    fim = max(p[1] + p[4] for p in lib.loads)
    arq = bytearray(fim)
    for p in lib.loads:
        arq[p[1]:p[1] + p[4]] = img[p[2]:p[2] + p[4]]

    def off(va):
        p = next(p for p in lib.loads if p[2] <= va < p[2] + p[4])
        return va - p[2] + p[1]
    secs = lib.secoes()
    shstr = b'\0' + b''.join(n.encode() + b'\0' for n, *_ in secs) + b'.shstrtab\0'
    while len(arq) % 4:
        arq.append(0)
    o_shstr = len(arq)
    arq += shstr
    while len(arq) % 4:
        arq.append(0)
    shoff = len(arq)
    arq += bytes(40)                                   # secao 0
    idx = {n: i + 1 for i, (n, *_) in enumerate(secs)}
    for n, tipo, flags, va, tam, ent in secs:
        link = idx['.dynstr'] if n in ('.dynsym',) else idx['.dynsym'] if n.startswith('.rel') else 0
        arq += struct.pack('<10I', shstr.index(b'\0' + n.encode() + b'\0') + 1, tipo, flags, va, off(va), tam, link, 0, 4, ent)
    arq += struct.pack('<10I', shstr.index(b'.shstrtab'), 3, 0, 0, o_shstr, len(shstr), 0, 0, 1, 0)
    struct.pack_into('<I', arq, 0x20, shoff)
    struct.pack_into('<HHH', arq, 0x2e, 40, len(secs) + 2, len(secs) + 1)
    return bytes(arq)


def main():
    apk = sys.argv[1] if len(sys.argv) > 1 else os.path.join(os.path.dirname(AQUI), 'jogo', 'MGS2-ARM64.apk')
    with zipfile.ZipFile(apk) as z:
        libs = {n: Imagem(n, z.read(IMG[n])) for n in BASES}
    gnu, jogo = libs['libgnustl_shared.so'], libs['libMGS2HD.so']
    resolve = resolvedor(gnu, jogo)
    os.makedirs(LIBS, exist_ok=True)
    for n, lib in libs.items():
        open(os.path.join(LIBS, n), 'wb').write(remonta(lib, resolve))
        print(f'{n}: {len(lib.syms)} simbolos, {len(lib.rels)} relocacoes, secoes',
              ', '.join(f'{s[0]} {s[3]:#x}+{s[4]:#x}' for s in lib.secoes() if s[0] in ('.plt', '.text')))

    # conferencia: o recompilador le a reconstrucao e reloca de volta para a imagem do APK
    # (fora e_shoff/e_shnum/e_shstrndx, que sao nossos)
    import recompilar
    ruins = 0
    for n in BASES:
        lib = recompilar.Lib(n)
        nova = bytearray(recompilar.imagem_relocada(lib, lambda nome, l: resolve(nome, libs[l.nome])))
        nova[0x20:0x24], nova[0x2e:0x34] = libs[n].d[0x20:0x24], libs[n].d[0x2e:0x34]
        iguais = nova == libs[n].d
        print(f'  conferencia {n}: imagem relocada {"IGUAL" if iguais else "DIFERENTE"} a do APK '
              f'({len(nova)} x {len(libs[n].d)} bytes), plt {len(lib.plt)} stubs')
        ruins += not iguais
    if ruins:
        sys.exit('RECONSTRUCAO RUIM')


if __name__ == '__main__':
    main()
