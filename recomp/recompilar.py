"""Recompilador estatico ARM32 -> C das duas bibliotecas do MGS2 do SHIELD.

Mapa do espaco de 32 bits do jogo:
  0x00001000-0x00f00000  (vazio: ponteiro nulo cai aqui)
  0x00f00000             importados de DADOS (stdout, __sF, SL_IID_*...), 0x100 cada
  0x01000000             libgnustl_shared.so (Thumb-2)
  0x02000000             libMGS2HD.so (ARM)
  0x04000000-0xefffffff  heap e pilhas (runtime)
  0xfff00000             enderecos falsos das funcoes importadas (8 bytes cada)

Saida em saida/:
  f_<lib>_NNN.c    funcoes F_xxxxxxxx(CPU*)
  funcoes.h        prototipos (F_ e I_)
  tabela.c         enderecos -> funcoes (despacho), importacoes, dados importados
  <lib>.img        imagem ja relocada (o runtime so copia), + tamanho do bss

    python recompilar.py            (tudo)
    python recompilar.py --so-analise
"""
import argparse, bisect, collections, json, os, pickle, struct, sys, time
import capstone as cs
from capstone import arm as A
from elf32 import Elf
from ins import Ins
from gerar import Gerador
import ual

AQUI = os.path.dirname(os.path.abspath(__file__))
SAIDA = os.path.join(AQUI, 'saida')
BASES = {'libgnustl_shared.so': 0x01000000, 'libMGS2HD.so': 0x02000000}
THUMB = {'libgnustl_shared.so': True, 'libMGS2HD.so': False}
DADOS_BASE = 0x00f00000
IMPORT_BASE = 0xfff00000
POR_ARQUIVO = 350

SEMRETORNO_IMPORT = {'_exit', 'exit', 'abort', '__cxa_pure_virtual', '__stack_chk_fail',
                     'pthread_exit', 'longjmp', 'siglongjmp', '__cxa_throw', '__cxa_rethrow',
                     '__cxa_bad_cast', '__cxa_bad_typeid', '_Unwind_Resume'}


class Lib:
    def __init__(self, nome):
        self.nome = nome
        self.e = Elf(os.path.join(AQUI, 'libs', nome))
        self.base = BASES[nome]
        self.thumb = THUMB[nome]
        self.img = bytes(self.e.imagem())
        t = self.e.sec['.text']
        self.t0, self.t1 = self.base + t['va'], self.base + t['va'] + t['tam']
        self.fim_rx = self.base + min(l['va'] for l in self.e.loads if l['va'] > 0)
        self.relocados = {self.base + o for o, _, _ in self.e.rels}
        self.exports = {}
        for s in self.e.dynsyms:
            if s['shn'] and s['nome']:
                self.exports[s['nome']] = (self.base + (s['va'] & ~1), s['tipo'])
        self.plt = self._plt()

    def _plt(self):
        """endereco do stub na PLT -> nome importado"""
        slots = {}
        for o, ty, s in self.e.rels:
            if ty == 22:
                slots[o] = s
        p = self.e.sec['.plt']
        out = {}
        a = p['va']
        img = self.img
        def imm(w):
            r = (w >> 8) & 0xf; v = w & 0xff
            return ((v >> (2 * r)) | (v << (32 - 2 * r))) & 0xffffffff
        while a < p['va'] + p['tam']:
            w0, w1, w2 = struct.unpack_from('<3I', img, a)
            if w0 & 0xfffff000 == 0xe28fc000 and w2 & 0xfffff000 == 0xe5bcf000:
                got = (a + 8 + imm(w0) + imm(w1) + (w2 & 0xfff)) & 0xffffffff
                if got in slots:
                    out[self.base + a] = slots[got]
                a += 12
            else:
                a += 4
        return out

    def u32(self, addr):
        return struct.unpack_from('<I', self.img, addr - self.base)[0]

    def constante(self, addr, larg):
        if not (self.base <= addr and addr + larg <= self.fim_rx):
            return None
        if any(addr - k in self.relocados for k in range(4)) or any(addr + k in self.relocados for k in range(larg)):
            return None
        return int.from_bytes(self.img[addr - self.base:addr - self.base + larg], 'little')


# --------------------------------------------------------------- analise
class Funcao:
    __slots__ = ('ini', 'fim', 'insns', 'rotulos', 'tabelas', 'externos', 'chamados', 'literais', 'sai', 'problemas', 'thumb', 'veneer', 'troca_modo', 'ponteiros')


def eh_tabela_arm(ins, ops):
    return (ins.nome == 'add' and len(ops) == 3 and isinstance(ops[0], ual.Reg) and ops[0].n == 15
            and isinstance(ops[1], ual.Reg) and ops[1].n == 15 and isinstance(ops[2], ual.Reg)
            and ops[2].shift == ('lsl', 2))


def descer(lib, md, ini, fim, literais, semretorno, gen, thumb):
    f = Funcao()
    f.ini, f.fim = ini, fim
    f.insns, f.rotulos, f.tabelas = {}, set(), {}
    f.externos, f.chamados, f.literais = set(), set(), set()
    f.sai = False          # tem algum caminho que sai (retorno/cauda/indireto)?
    f.problemas = []
    f.thumb = thumb
    f.veneer = None
    f.troca_modo = set()   # alvos de blx imediato (mudam de modo)
    f.ponteiros = set()    # enderecos de codigo montados com ldr literal + add pc
    lit_reg = {}           # registrador -> valor do ultimo ldr literal
    img, base = lib.img, lib.base
    pend = [ini]
    pre = {}               # instrucoes de blocos IT, decodificadas junto com o IT
    while pend:
        a = pend.pop()
        while ini <= a < fim and a not in f.insns and a not in literais:
            off = a - base
            if a in pre:
                ins = pre[a]
            else:
                i = next(md.disasm(img[off:off + 4], a, 1), None)
                if i is None:
                    f.problemas.append((a, 'indecodificavel'))
                    break
                ins = Ins.de(i)
                if ins.nome == 'it':
                    # o capstone so aplica a condicao do IT se decodificar o bloco na mesma chamada
                    n_it = len(ins.mnemonic.split()[0]) - 1
                    bloco = list(md.disasm(img[off:off + 2 + 4 * n_it], a, n_it + 1))
                    for j in bloco[1:]:
                        pre[j.address] = Ins.de(j)
            f.insns[a] = ins
            try:
                ops = ual.parse(ins.op_str)
            except Exception:
                f.problemas.append((a, 'parse'))
                ops = []
            cond = ins.cc not in (A.ARM_CC_AL, A.ARM_CC_INVALID)
            n = ins.nome
            # literais lidos por pc
            for o in ops:
                if isinstance(o, ual.Mem) and o.base.tipo == 'r' and o.base.n == 15 and o.post is None and not o.pre_wb \
                        and (o.off is None or isinstance(o.off, ual.Imm)):
                    pcv = ((a + 4) & ~3) if thumb else a + 8
                    la = pcv + (o.off.v if o.off else 0)
                    larg = 8 if n in ('ldrd', 'vldr') and ops[0].tipo in ('r', 'd') and n != 'ldr' else 4
                    if n == 'vldr' and ops[0].tipo == 's':
                        larg = 4
                    for k in range(0, larg, 2 if thumb else 4):
                        f.literais.add(la + k)
                    if n == 'ldr' and ops[0].tipo == 'r':
                        lit_reg[ops[0].n] = lib.constante(la, 4)
            # ponteiro de funcao: ldr rX, =L ; add rD, pc, rX  (so chega por ponteiro)
            if n == 'add' and len(ops) == 3 and all(isinstance(o, ual.Reg) and o.tipo == 'r' and not o.shift for o in ops[1:]):
                r1, r2 = ops[1].n, ops[2].n
                outro = r2 if r1 == 15 else r1 if r2 == 15 else None
                if outro is not None and outro in lit_reg and lit_reg[outro] is not None:
                    pcv = ((a + 4) & ~3) if thumb else a + 8
                    v = (pcv + lit_reg[outro]) & 0xffffffff
                    if not (lib.thumb and not v & 1):   # numa lib Thumb, par seria ARM: ignora
                        f.ponteiros.add(v)
            prox = a + ins.size
            if n == 'b':
                t = ops[0].v
                if ini <= t < fim:
                    f.rotulos.add(t); pend.append(t)
                else:
                    f.externos.add(t); f.sai = True
                if not cond:
                    break
            elif n in ('cbz', 'cbnz'):
                t = ops[1].v
                if ini <= t < fim:
                    f.rotulos.add(t); pend.append(t)
                else:
                    f.externos.add(t); f.sai = True
            elif n in ('bl', 'blx') and ops and isinstance(ops[0], ual.Imm):
                t = ops[0].v
                f.chamados.add(t)
                if n == 'blx':
                    f.troca_modo.add(t & ~1)
                if t in semretorno and not cond:
                    break
            elif n in ('tbb', 'tbh'):
                tab = tabela_thumb(lib, f, ins, ops)
                if tab is None:
                    f.problemas.append((a, 'tbb sem limite'))
                    break
                f.tabelas[a] = tab
                for t in tab['casos']:
                    if ini <= t < fim:
                        f.rotulos.add(t); pend.append(t)
                    else:
                        f.externos.add(t)
                larg = 1 if n == 'tbb' else 2
                for k in range(len(tab['casos']) * larg):
                    literais.add(a + 4 + k)
                break
            elif eh_tabela_arm(ins, ops):
                casos = []
                k = a + 8
                while True:
                    j = next(md.disasm(img[k - base:k - base + 4], k, 1), None)
                    if j is None or j.insn_name() != 'b' or j.cc != A.ARM_CC_AL:
                        break
                    casos.append(j.operands[0].imm)
                    k += 4
                idx = ual.parse(ins.op_str)[2]
                f.tabelas[a] = {'indice': gen.reg(ual.Reg(idx.nome), ins), 'casos': casos}
                for t in casos:
                    if ini <= t < fim:
                        f.rotulos.add(t); pend.append(t)
                    else:
                        f.externos.add(t)
                if not cond:
                    break
            elif gen.termina(ins):
                f.sai = True
                break
            elif n in ('bx',) or (ops and isinstance(ops[0], ual.Reg) and ops[0].tipo == 'r' and ops[0].n == 15
                                  and n not in ('str', 'strb', 'strh', 'cmp', 'cmn', 'tst', 'teq', 'push', 'stm', 'stmdb', 'bl', 'blx')):
                f.sai = True   # condicional que escreve pc
            a = prox
        else:
            if ini <= a and a >= fim and a not in literais:
                f.sai = True   # queda para a funcao seguinte
    return f


def tabela_thumb(lib, f, ins, ops):
    """tbb [pc, rN] / tbh [pc, rN, lsl #1]: limite pelo cmp anterior"""
    mm = ops[0]
    idx = mm.off
    if not isinstance(idx, ual.Reg):
        return None
    # procura cmp idx, #N nas instrucoes anteriores ja decodificadas
    limite = None
    a = ins.address
    for back in range(2, 24, 2):
        j = f.insns.get(a - back)
        if j is None:
            continue
        if j.nome == 'cmp':
            o = ual.parse(j.op_str)
            if isinstance(o[0], ual.Reg) and o[0].n == idx.n and isinstance(o[1], ual.Imm):
                limite = o[1].v + 1
                break
    if limite is None:
        return None
    larg = 1 if ins.nome == 'tbb' else 2
    casos = []
    for k in range(limite):
        v = int.from_bytes(lib.img[a + 4 + larg * k - lib.base:a + 4 + larg * (k + 1) - lib.base], 'little')
        casos.append(a + 4 + 2 * v)
    return {'indice': f'r{idx.n}' if idx.n < 13 else ['sp', 'lr'][idx.n - 13], 'casos': casos}


def veneers(lib):
    """trampolins Thumb->ARM do linker: bx pc; nop; ldr ip,[pc]; add pc,ip,pc; .word"""
    out = {}
    img = lib.img
    for x in range(lib.t0 - lib.base, lib.t1 - lib.base - 16, 2):
        if img[x:x + 4] == bytes.fromhex('7847c046') and struct.unpack_from('<2I', img, x + 4) == (0xe59fc000, 0xe08cf00f):
            off = struct.unpack_from('<I', img, x + 12)[0]
            out[lib.base + x] = (lib.base + ((off + x + 16) & 0xffffffff)) & 0xffffffff
    return out


def analisar(lib, semretorno_global, log):
    mds = {}
    for t in (True, False):
        mds[t] = cs.Cs(cs.CS_ARCH_ARM, cs.CS_MODE_THUMB if t else cs.CS_MODE_ARM)
        mds[t].detail = True
    gens = {t: Gerador(t, lambda x: None, lambda x: None, lib.constante, set()) for t in (True, False)}
    ven = veneers(lib) if lib.thumb else {}
    arm = set()          # numa biblioteca Thumb: funcoes em modo ARM
    if lib.thumb:
        for nome, (ad, tipo) in lib.exports.items():
            if tipo == 2 and lib.t0 <= ad < lib.t1:
                sym = next(s for s in lib.e.dynsyms if s['nome'] == nome)
                if not sym['va'] & 1:
                    arm.add(ad)
        for o, ty, s_ in lib.e.rels:
            if ty == 23:
                v = lib.u32(lib.base + o)
                if lib.t0 <= lib.base + v < lib.t1 and not v & 1:
                    arm.add(lib.base + v)
        for x, t in ven.items():
            if t not in lib.plt and lib.t0 <= t < lib.t1:
                arm.add(t)
        log(f'  {lib.nome}: {len(ven)} trampolins Thumb->ARM, {len(arm)} funcoes ARM iniciais')
    inicios = {lib.base + a for a in lib.e.exidx()}
    for nome, (ad, tipo) in lib.exports.items():
        if tipo == 2 and lib.t0 <= ad < lib.t1:
            inicios.add(ad)
    for o, ty, s in lib.e.rels:
        if ty == 23:
            v = lib.base + (lib.u32(lib.base + o) & ~1)
            if lib.t0 <= v < lib.t1:
                inicios.add(v)
    inicios |= set(ven) | arm
    inicios = {a for a in inicios if lib.t0 <= a < lib.t1}
    literais = set()
    semretorno = set(semretorno_global)
    for rodada in range(40):
        t_ini = time.time()
        ordem = sorted(inicios)
        fins = ordem[1:] + [lib.t1]
        funcs = {}
        novos = set()
        for ini, fim in zip(ordem, fins):
            if ini in ven:
                f = Funcao()
                f.ini, f.fim, f.insns, f.rotulos, f.tabelas = ini, fim, {}, set(), {}
                f.externos, f.chamados, f.literais, f.sai, f.problemas = set(), set(), set(), True, []
                f.thumb, f.veneer, f.troca_modo, f.ponteiros = True, ven[ini], set(), set()
                funcs[ini] = f
                continue
            t = lib.thumb and ini not in arm
            f = descer(lib, mds[t], ini, fim, literais, semretorno, gens[t], t)
            funcs[ini] = f
        # blx imediato troca o modo do alvo
        for f in funcs.values():
            for x in f.troca_modo:
                if lib.thumb and f.thumb and lib.t0 <= x < lib.t1 and x not in arm and x not in ven:
                    arm.add(x); novos_modo = True
        # literais achados nesta rodada valem para a proxima (e para as vizinhas)
        antes = len(literais)
        for f in funcs.values():
            literais |= f.literais
        for f in funcs.values():
            for x in f.externos | f.chamados | f.ponteiros:
                x &= ~1
                if lib.t0 <= x < lib.t1 and x not in inicios and x not in literais:
                    novos.add(x)
        # funcoes que nunca saem: todo caminho termina em chamada sem retorno
        sr_novas = {ini for ini, f in funcs.items() if not f.sai and f.insns and ini not in semretorno
                    and not f.problemas and ({c & ~1 for c in f.chamados} & semretorno)}
        log(f'  {lib.nome} rodada {rodada}: {len(funcs)} funcoes, {sum(len(f.insns) for f in funcs.values())} instrucoes, '
            f'{len(novos)} inicios novos, {len(literais) - antes} literais novos, {len(sr_novas)} sem retorno novas ({time.time() - t_ini:.0f}s)')
        n_arm = len(arm)
        if not novos and len(literais) == antes and not sr_novas and n_arm == getattr(analisar, '_arm', -1):
            break
        analisar._arm = n_arm
        inicios |= novos
        semretorno |= sr_novas
    return funcs, semretorno


# --------------------------------------------------------------- imagem relocada
def imagem_relocada(lib, resolve):
    img = bytearray(lib.img)
    for o, ty, s in lib.e.rels:
        if ty == 23:        # RELATIVE
            v = struct.unpack_from('<I', img, o)[0]
            struct.pack_into('<I', img, o, (v + lib.base) & 0xffffffff)
        elif ty in (2, 21, 22):   # ABS32 / GLOB_DAT / JUMP_SLOT
            v = struct.unpack_from('<I', img, o)[0] if ty == 2 else 0
            struct.pack_into('<I', img, o, (resolve(s, lib) + v) & 0xffffffff)
        else:
            raise SystemExit(f'relocacao {ty} nao tratada')
    return bytes(img)


# --------------------------------------------------------------- principal
def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--so-analise', action='store_true')
    ap.add_argument('--comentarios', action='store_true')
    ap.add_argument('--cache', action='store_true', help='reusa saida/analise.pkl')
    a = ap.parse_args()
    os.makedirs(SAIDA, exist_ok=True)
    rel = open(os.path.join(SAIDA, 'relatorio.txt'), 'w', encoding='utf-8')
    def log(s):
        print(s); rel.write(s + '\n'); rel.flush()

    libs = {n: Lib(n) for n in ('libgnustl_shared.so', 'libMGS2HD.so')}
    gnu, jogo = libs['libgnustl_shared.so'], libs['libMGS2HD.so']

    # ---- importacoes: quem resolve cada nome
    funcs_gnu = {n: ad for n, (ad, t) in gnu.exports.items() if t == 2}
    objs_gnu = {n: ad for n, (ad, t) in gnu.exports.items() if t == 1}
    nomes_import = set()
    dados_import = set()
    for lib in libs.values():
        for s in lib.e.dynsyms:
            if s['shn'] or not s['nome']:
                continue
            if lib is jogo and s['nome'] in gnu.exports:
                continue
            if s['tipo'] == 1:
                dados_import.add(s['nome'])
            else:
                nomes_import.add(s['nome'])
    nomes_import = sorted(nomes_import)
    dados_import = sorted(dados_import)
    end_import = {n: IMPORT_BASE + 8 * k for k, n in enumerate(nomes_import)}
    end_dados = {n: DADOS_BASE + 0x100 * k for k, n in enumerate(dados_import)}
    log(f'importacoes de funcao: {len(nomes_import)}, de dados: {len(dados_import)} {dados_import}')

    def resolve(nome, lib):
        if lib is jogo and nome in gnu.exports:
            ad, t = gnu.exports[nome]
            return ad | (1 if t == 2 else 0)        # funcao Thumb: bit 0
        if nome in end_dados:
            return end_dados[nome]
        if nome in end_import:
            return end_import[nome]
        if nome in lib.exports:
            ad, t = lib.exports[nome]
            return ad | (1 if (t == 2 and lib.thumb) else 0)
        raise SystemExit('sem resolver: ' + nome)

    # ---- sem retorno: PLTs de importacoes sem retorno + std::__throw_* da gnustl
    semretorno = set()
    for lib in libs.values():
        for ad, nome in lib.plt.items():
            if nome in SEMRETORNO_IMPORT or nome.startswith('_ZSt') and '__throw_' in nome:
                semretorno.add(ad)
    for n, ad in funcs_gnu.items():
        if '__throw_' in n or n in ('__cxa_throw', '__cxa_rethrow', '_ZSt9terminatev'):
            semretorno.add(ad)

    cache = os.path.join(SAIDA, 'analise.pkl')
    if a.cache and os.path.exists(cache):
        todas, semretorno = pickle.load(open(cache, 'rb'))
        log('analise lida do cache')
    else:
        todas = {}
        for lib in (gnu, jogo):
            log(f'analisando {lib.nome} (base {lib.base:#x}, {"Thumb" if lib.thumb else "ARM"})')
            funcs, semretorno = analisar(lib, semretorno, log)
            todas[lib.nome] = funcs
        pickle.dump((todas, semretorno), open(cache, 'wb'))
    if a.so_analise:
        return

    inicio_de = {}
    for lib in libs.values():
        for ini in todas[lib.nome]:
            inicio_de[ini] = f'F_{ini:08x}'

    def ehfuncao(x):
        return inicio_de.get(x & ~1)

    def importacao_de(lib):
        def f(x):
            nome = lib.plt.get(x)
            if nome is None:
                return None
            if lib is jogo and nome in funcs_gnu:
                return f'F_{funcs_gnu[nome]:08x}'
            return f'I_{nome}'
        return f

    # ---- ABI dos registradores preservados (ver medir_abi.py): fragmentos que leem
    # r4-r11 do chamador (bl como salto longo no Thumb-1 da gnustl, captura de
    # contexto) recarregam tudo depois da chamada; os exportados sao funcoes de verdade
    import medir_abi
    exportadas = {ad for lib in libs.values() for ad, t in lib.exports.values() if t == 2}
    fora_abi = {ini for funcs in todas.values() for ini, f in funcs.items()
                if f.veneer is None and f.insns and medir_abi.avalia(f) is not None} - exportadas
    log(f'fora da ABI (recarga completa depois da chamada): {len(fora_abi)} funcoes')

    def segue_abi(alvo):
        return (alvo & ~1) not in fora_abi

    # ---- emissao
    faltas = collections.Counter()
    arquivos = []
    for lib in libs.values():
        gens = {t: Gerador(t, ehfuncao, importacao_de(lib), lib.constante, semretorno) for t in (True, False)}
        for g in gens.values():
            g.segue_abi = segue_abi
            g.eh_jogo = lib is jogo
        funcs = todas[lib.nome]
        ordem = sorted(funcs)
        curto = 'gnu' if lib.thumb else 'jogo'
        for k in range(0, len(ordem), POR_ARQUIVO):
            nome_arq = f'f_{curto}_{k // POR_ARQUIVO:03d}.c'
            partes = ['#include "cpu.h"\n#include "funcoes.h"\n']
            for ini in ordem[k:k + POR_ARQUIVO]:
                f = funcs[ini]
                gen = gens[f.thumb]
                if f.veneer is not None:
                    alvo = importacao_de(lib)(f.veneer) or ehfuncao(f.veneer)
                    if alvo:
                        partes.append(f'void F_{ini:08x}(CPU *c) {{ {alvo}(c); }}\n')
                    else:
                        partes.append(f'void F_{ini:08x}(CPU *c) {{ despacha(c, 0x{f.veneer:08x}u); }}\n')
                    continue
                insns = [f.insns[x] for x in sorted(f.insns)]
                if not insns:
                    partes.append(f'void F_{ini:08x}(CPU *c) {{ nao_suportado(c, 0x{ini:08x}u); }}\n')
                    continue
                txt = gen.funcao(f'F_{ini:08x}', ini, insns, f.rotulos, f.tabelas)
                if not a.comentarios:
                    txt = '\n'.join(l.split(' /* ')[0] if ' /* ' in l and not l.lstrip().startswith('NAO_SUPORTADO') else l
                                    for l in txt.split('\n'))
                partes.append(txt)
            open(os.path.join(SAIDA, nome_arq), 'w').write('\n'.join(partes))
            arquivos.append(nome_arq)
        faltas.update(gens[True].faltas); faltas.update(gens[False].faltas)
        log(f'{lib.nome}: {len(ordem)} funcoes emitidas')
        cv = sum(g.n_chamadas[True] for g in gens.values()); cm = sum(g.n_chamadas[False] for g in gens.values())
        log(f'  chamadas: {cm} sem recarga de bandeiras, {cv} com (codigo seguinte as le, ou incerto)')
        ca = sum(g.n_abi[True] for g in gens.values()); cf_ = sum(g.n_abi[False] for g in gens.values())
        log(f'  chamadas: {ca} para alvos que seguem a ABI, {cf_} para fora da ABI')
        gs = sum(g.n_gravados[0] for g in gens.values()); gn = sum(g.n_gravados[1] for g in gens.values())
        log(f'  gravacao parcial: {gs / max(gn, 1):.1f} de 15 registradores por funcao (media em {gn})')

    # ---- funcoes.h e tabela.c
    with open(os.path.join(SAIDA, 'funcoes.h'), 'w') as h:
        h.write('#pragma once\n#include "cpu.h"\n')
        for ini in sorted(inicio_de):
            h.write(f'void F_{ini:08x}(CPU *c);\n')
        for n in nomes_import:
            h.write(f'void I_{n}(CPU *c);\n')
    with open(os.path.join(SAIDA, 'tabela.c'), 'w') as t:
        t.write('#include "funcoes.h"\n#include "tabela.h"\n\n')
        entradas = sorted([(ini, f'F_{ini:08x}') for ini in inicio_de] + [(end_import[n], f'I_{n}') for n in nomes_import])
        t.write(f'const EntradaDespacho g_despacho[{len(entradas)}] = {{\n')
        for ad, fn in entradas:
            t.write(f'  {{0x{ad:08x}u, {fn}}},\n')
        t.write(f'}};\nconst uint32_t g_n_despacho = {len(entradas)};\n\n')
        t.write(f'const Importacao g_importacoes[{len(nomes_import)}] = {{\n')
        for n in nomes_import:
            t.write(f'  {{"{n}", 0x{end_import[n]:08x}u}},\n')
        t.write(f'}};\nconst uint32_t g_n_importacoes = {len(nomes_import)};\n\n')
        t.write(f'const Importacao g_dados_importados[{len(dados_import)}] = {{\n')
        for n in dados_import:
            t.write(f'  {{"{n}", 0x{end_dados[n]:08x}u}},\n')
        t.write(f'}};\nconst uint32_t g_n_dados_importados = {len(dados_import)};\n\n')
        t.write('const ImagemLib g_libs[2] = {\n')
        for lib in (gnu, jogo):
            ini_arr = lib.e.sec.get('.init_array')
            t.write(f'  {{"{lib.nome}", 0x{lib.base:08x}u, {lib.e.tamanho_imagem}u, '
                    f'0x{lib.base + ini_arr["va"]:08x}u, {ini_arr["tam"] // 4}u}},\n')
        t.write('};\n')
        exp = [(n, ad) for n, (ad, tipo) in sorted(jogo.exports.items()) if tipo == 2]
        t.write(f'const Importacao g_exportados_jogo[{len(exp)}] = {{\n')
        for n, ad in exp:
            t.write(f'  {{"{n}", 0x{ad:08x}u}},\n')
        t.write(f'}};\nconst uint32_t g_n_exportados_jogo = {len(exp)};\n')
        for lib in (gnu, jogo):
            ex = lib.e.sec['.ARM.exidx']
            t.write(f'const uint32_t g_exidx_{"gnu" if lib.thumb else "jogo"}[2] = '
                    f'{{0x{lib.base + ex["va"]:08x}u, {ex["tam"] // 8}u}};\n')
    json.dump({n: ad for n, (ad, tipo) in jogo.exports.items() if tipo == 2},
              open(os.path.join(SAIDA, 'exportados_jogo.json'), 'w'), indent=1)

    for lib in libs.values():
        open(os.path.join(SAIDA, lib.nome.replace('.so', '.img')), 'wb').write(imagem_relocada(lib, resolve))

    log(f'\narquivos C: {len(arquivos)}')
    log(f'instrucoes nao suportadas: {sum(faltas.values())} em {len(faltas)} tipos')
    for k, v in faltas.most_common(60):
        log(f'  {v:7} {k}')


if __name__ == '__main__':
    main()
