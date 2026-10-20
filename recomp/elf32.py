"""Leitor minimo de ELF32 ARM (o que o recompilador precisa)."""
import struct

class Elf:
    def __init__(self, caminho):
        self.caminho = caminho
        self.d = d = open(caminho, 'rb').read()
        shoff, = struct.unpack_from('<I', d, 0x20)
        shnum, shstr = struct.unpack_from('<HH', d, 0x30)
        phoff, = struct.unpack_from('<I', d, 0x1c)
        phnum, = struct.unpack_from('<H', d, 0x2c)
        self.secs = []
        for i in range(shnum):
            s = struct.unpack_from('<10I', d, shoff + 40 * i)
            self.secs.append(s)
        so = self.secs[shstr][4]
        def nome(o): return d[so + o:d.index(b'\0', so + o)].decode()
        self.sec = {nome(s[0]): dict(tipo=s[1], flags=s[2], va=s[3], off=s[4], tam=s[5], link=s[6], ent=s[9]) for s in self.secs}
        self.loads = []
        for i in range(phnum):
            tipo, off, va, _, fsz, msz, flags, _ = struct.unpack_from('<8I', d, phoff + 32 * i)
            if tipo == 1:
                self.loads.append(dict(off=off, va=va, fsz=fsz, msz=msz, flags=flags))
        self.tamanho_imagem = max(l['va'] + l['msz'] for l in self.loads)
        self._syms()
        self._rels()

    def off(self, va):
        for l in self.loads:
            if l['va'] <= va < l['va'] + l['fsz']:
                return va - l['va'] + l['off']
        return None

    def u32(self, va):
        return struct.unpack_from('<I', self.d, self.off(va))[0]

    def imagem(self):
        """bytes da imagem carregada (va 0 .. tamanho), bss zerado."""
        m = bytearray(self.tamanho_imagem)
        for l in self.loads:
            m[l['va']:l['va'] + l['fsz']] = self.d[l['off']:l['off'] + l['fsz']]
        return m

    def _syms(self):
        ds = self.sec['.dynsym']; st = self.sec['.dynstr']
        self.dynsyms = []
        for i in range(ds['tam'] // 16):
            n, v, sz, info, oth, shn = struct.unpack_from('<IIIBBH', self.d, ds['off'] + 16 * i)
            nm = self.d[st['off'] + n:self.d.index(b'\0', st['off'] + n)].decode()
            self.dynsyms.append(dict(nome=nm, va=v, tam=sz, tipo=info & 0xf, bind=info >> 4, shn=shn))

    def _rels(self):
        self.rels = []
        for nm in ('.rel.dyn', '.rel.plt'):
            s = self.sec.get(nm)
            if not s: continue
            for k in range(s['tam'] // 8):
                onde, info = struct.unpack_from('<II', self.d, s['off'] + 8 * k)
                self.rels.append((onde, info & 0xff, self.dynsyms[info >> 8]['nome'] if info >> 8 else None))

    def exidx(self):
        """inicios de funcao pela tabela de excecoes (prel31)."""
        s = self.sec['.ARM.exidx']
        r = []
        for k in range(s['tam'] // 8):
            o = s['va'] + 8 * k
            w, = struct.unpack_from('<I', self.d, s['off'] + 8 * k)
            off = w & 0x7fffffff
            if off & 0x40000000: off -= 0x80000000
            r.append((o + off) & 0xffffffff)
        return r
