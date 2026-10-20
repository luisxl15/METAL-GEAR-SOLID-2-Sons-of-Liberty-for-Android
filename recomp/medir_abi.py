"""Mede quais funcoes NAO seguem a ABI dos registradores preservados (r4-r11).

Uma funcao de verdade (AAPCS) nao le r4-r11 antes de escreve-los (a nao ser para
guarda-los na pilha) e, se os escreve, guardou-os antes. Quem viola isso e
continuacao de outra funcao: o truque do Thumb-1 de usar `bl` como salto longo
(demangler da gnustl) ou fragmento que a analise separou.

Depois de chamar uma funcao que SEGUE a ABI, o codigo gerado nao precisa
recarregar r4-r11/sp de c (CARREGA_ABI). As que violam ficam com a recarga
completa. Varredura linear por endereco (conservadora: duvida = viola).

    python medir_abi.py   -> grava saida/fora_da_abi.json e imprime as contagens
"""
import collections, json, os, pickle, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import __main__, recompilar, ual
from capstone import arm as A
__main__.Funcao = recompilar.Funcao

AQUI = os.path.dirname(os.path.abspath(__file__))
PRES = set(range(4, 12))                 # r4-r11
SO_LE = {'str', 'strb', 'strh', 'strd', 'strex', 'strexb', 'strexh', 'stm', 'stmdb', 'stmib', 'stmda', 'push',
         'cmp', 'cmn', 'tst', 'teq', 'b', 'bx', 'bl', 'blx', 'cbz', 'cbnz', 'tbb', 'tbh', 'pld', 'pli',
         'vstr', 'vstmia', 'vstmdb', 'vpush', 'vst1', 'vst2', 'vst3', 'vst4', 'mcr', 'mcrr', 'svc', 'it',
         'nop', 'dmb', 'dsb', 'isb', 'bkpt', 'udf', 'vmsr', 'msr'}
ACUMULA = {'umlal', 'smlal', 'mla', 'mls', 'smlabb', 'smlalbb', 'umaal', 'bfi', 'bfc', 'movt'}   # destino tambem e lido


def regs_de(o):
    """registradores do nucleo lidos dentro de um operando"""
    if isinstance(o, ual.Reg):
        out = {o.n} if o.tipo == 'r' else set()
        if o.shift and isinstance(o.shift, tuple) and len(o.shift) > 1 and isinstance(o.shift[1], ual.Reg):
            out.add(o.shift[1].n)
        elif o.shift is not None and not isinstance(o.shift, tuple):
            s = str(o.shift)
            for nm, n in ual.REG_CORE.items():
                if nm in s.replace(',', ' ').split():
                    out.add(n)
        return out
    if isinstance(o, ual.Mem):
        out = set()
        if o.base is not None:
            out |= regs_de(o.base)
        for x in (o.off, o.post):
            if isinstance(x, ual.Reg):
                out |= regs_de(x)
        return out
    if isinstance(o, ual.Lista):
        return {r.n for r in o.regs if r.tipo == 'r'}
    return set()


def efeito(i, ops):
    """(lidos, escritos, guardados) entre os registradores do nucleo"""
    n = i.nome
    base = i.mnemonic.split('.')[0].lower()
    lidos, escritos, guardados = set(), set(), set()
    eh_pilha = any(isinstance(o, ual.Mem) and o.base is not None and o.base.n == 13 for o in ops) or \
        (ops and isinstance(ops[0], ual.Reg) and ops[0].n == 13 and n.startswith('stm'))
    if n in ('push', 'vpush') or (n.startswith('stm') or n.startswith('str')) and eh_pilha:
        for o in ops:
            if isinstance(o, ual.Lista):
                guardados |= regs_de(o)
            elif isinstance(o, ual.Reg) and o.tipo == 'r' and o.n != 13:
                guardados.add(o.n)
            elif isinstance(o, ual.Mem):
                lidos |= regs_de(o)
        return lidos, escritos, guardados
    if n in ('pop',):
        return set(), regs_de(ops[0]), set()
    if n.startswith('ldm') or n.startswith('vldm'):
        lidos |= regs_de(ops[0]) if isinstance(ops[0], ual.Reg) and ops[0].tipo == 'r' else set()
        for o in ops[1:]:
            if isinstance(o, ual.Lista):
                escritos |= regs_de(o)
        if ops[0].wb and isinstance(ops[0], ual.Reg):
            escritos.add(ops[0].n)
        return lidos, escritos, guardados
    if n.startswith('ld') or n.startswith('vld'):
        k = 0
        for o in ops:
            if isinstance(o, ual.Mem):
                lidos |= regs_de(o)
                if (o.pre_wb or o.post is not None) and o.base is not None:
                    escritos.add(o.base.n)
            elif isinstance(o, ual.Reg) and o.tipo == 'r':
                escritos.add(o.n)
        return lidos, escritos, guardados
    if n in SO_LE or n.startswith('st') or n.startswith('vst'):
        for o in ops:
            lidos |= regs_de(o)
            if isinstance(o, ual.Mem) and (o.pre_wb or o.post is not None) and o.base is not None:
                escritos.add(o.base.n)
            if isinstance(o, ual.Reg) and o.wb:
                escritos.add(o.n)
        return lidos, escritos, guardados
    # vmov: destino(s) do nucleo so se o 1o operando for do nucleo
    if n in ('vmov', 'fmrs', 'fmsr', 'fmrrd', 'fmdrr', 'vmrs', 'fmstat'):
        if ops and isinstance(ops[0], ual.Reg) and ops[0].tipo == 'r':
            escritos.add(ops[0].n)
            if len(ops) > 1 and isinstance(ops[1], ual.Reg) and ops[1].tipo == 'r' and len(ops) == 3 and ops[2].tipo != 'r':
                escritos.add(ops[1].n)
            for o in ops[1:]:
                if isinstance(o, ual.Reg) and o.tipo == 'r' and o.n not in escritos:
                    lidos.add(o.n)
        else:
            for o in ops:
                lidos |= regs_de(o)
        return lidos, escritos, guardados
    # forma geral: 1o operando destino, o resto lido
    nd = 2 if n in ('umull', 'smull', 'umlal', 'smlal', 'umaal') else 1
    for o in ops[:nd]:
        if isinstance(o, ual.Reg) and o.tipo == 'r':
            escritos.add(o.n)
            if n in ACUMULA or base in ACUMULA:
                lidos.add(o.n)
    for o in ops[nd:]:
        lidos |= regs_de(o)
    if len(ops) == nd:                         # ex.: 'neg r0' sem fonte explicita
        lidos |= escritos
    return lidos, escritos, guardados


def avalia(f):
    insns = [f.insns[x] for x in sorted(f.insns)]
    escritos, guardados = set(), set()
    motivo = None
    for i in insns:
        try:
            ops = ual.parse(i.op_str)
        except Exception:
            return 'nao analisavel'
        le, esc, gu = efeito(i, ops)
        cond = i.cc not in (A.ARM_CC_AL, A.ARM_CC_INVALID)
        guardados |= gu & PRES - escritos
        lidos = (le & PRES) - escritos - guardados
        if lidos:
            return f'le r{min(lidos)} antes de escrever em {i.address:08x} ({i.mnemonic} {i.op_str})'
        if not cond:
            escritos |= esc
        sem_guardar = (esc & PRES) - guardados
        if sem_guardar and motivo is None:
            motivo = f'escreve r{min(sem_guardar)} sem guardar em {i.address:08x} ({i.mnemonic} {i.op_str})'
    return motivo


def main():
    todas, _ = pickle.load(open(os.path.join(AQUI, 'saida', 'analise.pkl'), 'rb'))
    fora = []
    for nlib, funcs in todas.items():
        cont = collections.Counter()
        ex = collections.defaultdict(list)
        for ini, f in funcs.items():
            if f.veneer is not None or not f.insns:
                cont['veneer/vazia'] += 1
                continue
            m = avalia(f)
            if m is None:
                cont['segue a ABI'] += 1
            else:
                tipo = m.split(' r')[0] if not m.startswith('nao') else m
                cont[tipo] += 1
                ex[tipo].append((ini, m))
                fora.append(ini)
        print(f'{nlib}: {sum(cont.values())} funcoes medidas  {dict(cont)}')
        for tipo, l in ex.items():
            for ini, m in l[:6]:
                print(f'   {ini:08x}  {m}')
    json.dump(sorted(fora), open(os.path.join(AQUI, 'saida', 'fora_da_abi.json'), 'w'))
    print(f'{len(fora)} funcoes fora da ABI -> saida/fora_da_abi.json')


if __name__ == '__main__':
    main()
