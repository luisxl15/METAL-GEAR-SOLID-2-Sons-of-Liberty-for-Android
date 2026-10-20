"""Descida recursiva por funcao (inicio pelo .ARM.exidx), com capstone."""
import capstone as cs
from capstone import arm as A
from elf32 import Elf

class Funcao:
    __slots__ = ('ini', 'fim', 'thumb', 'insns', 'alvos_int', 'problemas', 'tabelas')

def descer(e, ini, fim, thumb, md):
    """devolve dict endereco->insn, conjunto de rotulos, lista de problemas"""
    img = e.imagem_cache
    insns = {}
    pend = [ini]
    probs = []
    tabelas = {}
    while pend:
        a = pend.pop()
        while ini <= a < fim and a not in insns:
            i = next(md.disasm(bytes(img[a:a + 4]), a, 1), None)
            if i is None:
                probs.append((a, 'indecodificavel')); break
            insns[a] = i
            prox = a + i.size
            g = i.group
            ehbranch = i.id in (A.ARM_INS_B, A.ARM_INS_BX, A.ARM_INS_CBZ, A.ARM_INS_CBNZ, A.ARM_INS_TBB, A.ARM_INS_TBH)
            escreve_pc = False
            if i.id in (A.ARM_INS_POP, A.ARM_INS_LDM) or (i.id == A.ARM_INS_LDR and i.operands[0].reg == A.ARM_REG_PC):
                escreve_pc = any(op.type == A.ARM_OP_REG and op.reg == A.ARM_REG_PC for op in i.operands)
            elif i.id not in (A.ARM_INS_B, A.ARM_INS_BL, A.ARM_INS_BLX, A.ARM_INS_BX, A.ARM_INS_STR, A.ARM_INS_STM, A.ARM_INS_PUSH, A.ARM_INS_CMP, A.ARM_INS_CMN, A.ARM_INS_TST, A.ARM_INS_TEQ) and i.operands and i.operands[0].type == A.ARM_OP_REG and i.operands[0].reg == A.ARM_REG_PC:
                escreve_pc = True
            cond = i.cc not in (A.ARM_CC_AL, A.ARM_CC_INVALID)
            if i.id == A.ARM_INS_B:
                t = i.operands[0].imm
                if ini <= t < fim: pend.append(t)
                else: probs.append((a, 'b_fora'))   # salto de cauda
                if not cond: break
            elif i.id in (A.ARM_INS_CBZ, A.ARM_INS_CBNZ):
                pend.append(i.operands[1].imm)
            elif i.id == A.ARM_INS_BX:
                if i.operands[0].reg == A.ARM_REG_LR:
                    if not cond: break
                else:
                    probs.append((a, 'bx_reg'))
                    if not cond: break
            elif i.id in (A.ARM_INS_TBB, A.ARM_INS_TBH):
                probs.append((a, 'tbb')); break
            elif escreve_pc:
                # tabela de salto ARM: addls pc, pc, rN, lsl #2 ; b default ; b caso0 ...
                if i.id == A.ARM_INS_ADD and len(i.operands) >= 3 and i.operands[1].reg == A.ARM_REG_PC:
                    tabelas[a] = True
                    # o b logo a seguir e o default; os casos seguem ate acabar a sequencia de b
                    k = a + 8
                    casos = []
                    while True:
                        j = next(md.disasm(bytes(img[k:k + 4]), k, 1), None)
                        if j is None or j.id != A.ARM_INS_B or j.cc != A.ARM_CC_AL: break
                        insns[k] = j; casos.append(j.operands[0].imm); k += 4
                    pend.extend(c for c in casos if ini <= c < fim)
                    tabelas[a] = casos
                    break
                elif i.id in (A.ARM_INS_POP, A.ARM_INS_LDM, A.ARM_INS_LDR) and not cond:
                    break  # retorno (pop {..pc} / ldr pc,[sp],#4)
                elif i.id == A.ARM_INS_LDR:
                    probs.append((a, 'ldr_pc_' + ('cond' if cond else 'reg'))); 
                    if not cond: break
                else:
                    probs.append((a, 'escreve_pc:' + i.mnemonic)); break
            a = prox
    return insns, probs, tabelas

def analisar(caminho, thumb):
    e = Elf(caminho)
    e.imagem_cache = e.imagem()
    md = cs.Cs(cs.CS_ARCH_ARM, cs.CS_MODE_THUMB if thumb else cs.CS_MODE_ARM)
    md.detail = True
    inis = sorted(set(e.exidx()))
    t = e.sec['.text']
    fims = inis[1:] + [t['va'] + t['tam']]
    fs = []
    for ini, fim in zip(inis, fims):
        insns, probs, tabs = descer(e, ini, fim, thumb, md)
        fs.append((ini, fim, insns, probs, tabs))
    return e, fs

if __name__ == '__main__':
    import sys, collections, pickle
    nome, thumb = sys.argv[1], sys.argv[2] == 't'
    e, fs = analisar('libs/' + nome, thumb)
    mn = collections.Counter(); pr = collections.Counter(); ntab = 0; cob = 0
    for ini, fim, insns, probs, tabs in fs:
        for i in insns.values(): mn[i.mnemonic.split('.')[0]] += 1
        for a, p in probs: pr[p] += 1
        ntab += len(tabs); cob += sum(i.size for i in insns.values())
    tot = sum(f[1] - f[0] for f in fs)
    print(f'{nome}: {len(fs)} funcoes, {sum(len(f[2]) for f in fs)} instrucoes, cobertura {100*cob/tot:.1f}% dos bytes, {ntab} tabelas de salto')
    print('problemas:', dict(pr))
    print('mnemonicos distintos:', len(mn))
    print(' '.join(f'{k}:{v}' for k, v in mn.most_common()))
