"""Mede quais funcoes DEVOLVEM resultado nas bandeiras (NZCV).

Pela ABI do ARM as bandeiras nao sobrevivem a uma chamada. A excecao sao os
ajudantes de comparacao (__aeabi_cfcmple, __aeabi_cdcmple...), que devolvem o
resultado nelas. Este script varre TODAS as chamadas e classifica o que vem
logo depois:
  le      - instrucao condicional / it / adc... antes de qualquer escrita completa
  mata    - cmp/adds/... ou outra chamada antes de qualquer leitura
  incerto - desvio, retorno, descontinuidade ou fim de janela antes das duas
Imprime quantas chamadas mediu em cada classe e os alvos das que LEEM.

    python medir_bandeiras.py   -> grava saida/devolve_bandeiras.json
"""
import collections, json, os, pickle, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import __main__, recompilar, ual
from capstone import arm as A
__main__.Funcao = recompilar.Funcao

AQUI = os.path.dirname(os.path.abspath(__file__))
MATA = {'cmp', 'cmn', 'adds', 'subs', 'rsbs', 'negs'}
LE_C = {'adc', 'adcs', 'sbc', 'sbcs', 'rsc', 'rscs', 'rrx', 'rrxs', 'mrs'}


LE_COND = {A.ARM_CC_EQ: 'Z', A.ARM_CC_NE: 'Z', A.ARM_CC_HS: 'C', A.ARM_CC_LO: 'C', A.ARM_CC_MI: 'N',
           A.ARM_CC_PL: 'N', A.ARM_CC_VS: 'V', A.ARM_CC_VC: 'V', A.ARM_CC_HI: 'CZ', A.ARM_CC_LS: 'CZ',
           A.ARM_CC_GE: 'NV', A.ARM_CC_LT: 'NV', A.ARM_CC_GT: 'ZNV', A.ARM_CC_LE: 'ZNV'}
NZCV_S = {'add', 'sub', 'rsb', 'adc', 'sbc', 'rsc', 'cmp', 'cmn'}     # S aritmetico: escreve as 4


def escreve(i):
    """bandeiras que a instrucao (incondicional) escreve"""
    nome = i.nome
    base = i.mnemonic.split('.')[0].lower()
    if i.cc not in (A.ARM_CC_AL, A.ARM_CC_INVALID):
        base = base[:-2]
    s = nome in ('cmp', 'cmn', 'tst', 'teq') or base == nome + 's' or base in ('negs', 'lsls', 'lsrs', 'asrs', 'rors', 'muls', 'mlas')
    if nome in ('vmrs', 'fmstat') and i.op_str.lower().startswith('apsr_nzcv'):
        return 'NZCV'
    if not s:
        return ''
    if nome in NZCV_S or base == 'negs':
        return 'NZCV'
    return 'NZ'          # logicas/deslocamentos/mul: C do deslocador fica de fora (conservador)


def classifica(insns, k):
    """'le' so se uma leitura alcanca uma bandeira que ninguem reescreveu desde a chamada"""
    prox = insns[k].address + insns[k].size
    escritas = set()
    for j in range(k + 1, min(len(insns), k + 41)):
        i = insns[j]
        if i.address != prox:
            return 'incerto'
        prox = i.address + i.size
        base = i.mnemonic.split('.')[0].lower()
        if i.nome == 'it':
            continue                            # a leitura conta nas instrucoes do bloco
        lidas = set(LE_COND.get(i.cc, ''))
        if i.nome in ('adc', 'sbc', 'rsc', 'rrx') or 'rrx' in i.op_str:
            lidas.add('C')
        if i.nome == 'mrs':
            lidas |= set('NZCV')
        if lidas - escritas:
            return 'le'
        if i.nome in ('bl', 'blx'):
            return 'mata'
        if i.cc in (A.ARM_CC_AL, A.ARM_CC_INVALID):
            escritas |= set(escreve(i))
        if escritas >= set('NZCV'):
            return 'mata'
        if i.nome in ('b', 'bx', 'tbb', 'tbh', 'cbz', 'cbnz', 'pop', 'ldm', 'svc', 'udf', 'bkpt') or 'pc' in i.op_str.split(',')[0]:
            return 'incerto'
    return 'incerto'


def main():
    todas, _ = pickle.load(open(os.path.join(AQUI, 'saida', 'analise.pkl'), 'rb'))
    libs = {n: recompilar.Lib(n) for n in todas}
    nome_de = {}
    for lib in libs.values():
        for n, (ad, t) in lib.exports.items():
            nome_de.setdefault(ad, n)
        for ad, n in lib.plt.items():
            nome_de.setdefault(ad, 'PLT:' + n)
    total = collections.Counter()
    leitores = collections.Counter()          # alvo -> chamadas que leem depois
    exemplos = {}
    indiretas_le = 0
    for nlib, funcs in todas.items():
        for ini, f in funcs.items():
            insns = [f.insns[x] for x in sorted(f.insns)]
            for k, i in enumerate(insns):
                if i.nome not in ('bl', 'blx'):
                    continue
                cl = classifica(insns, k)
                total[cl] += 1
                if cl != 'le':
                    continue
                ops = ual.parse(i.op_str)
                if isinstance(ops[0], ual.Imm):
                    alvo = ops[0].v & ~1
                    leitores[alvo] += 1
                    exemplos.setdefault(alvo, i.address)
                else:
                    indiretas_le += 1
    print(f'chamadas medidas: {sum(total.values())}  ({dict(total)})')
    print(f'indiretas que leem bandeiras depois: {indiretas_le}')
    print(f'alvos diretos que deixam bandeiras lidas: {len(leitores)}')
    for alvo, n in leitores.most_common():
        print(f'  {alvo:08x} {n:6}  {nome_de.get(alvo, "?")}   ex.: chamada em {exemplos[alvo]:08x}')
    json.dump(sorted(leitores), open(os.path.join(AQUI, 'saida', 'devolve_bandeiras.json'), 'w'))


if __name__ == '__main__':
    main()
