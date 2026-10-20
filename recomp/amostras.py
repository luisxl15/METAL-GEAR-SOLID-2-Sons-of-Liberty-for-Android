"""Junta amostras de cada FORMA de instrucao alcancavel nos dois binarios.
forma = nome + tipos + desenho dos operandos (registradores por classe,
numeros trocados por N).  Grava amostras.json."""
import json, re, collections
from descer import analisar

def forma(i):
    base = i.mnemonic.split('.')
    dts = '.'.join(base[1:])
    s = re.sub(r'\b(r\d+|sb|sl|fp|ip|sp|lr)\b', 'R', i.op_str)
    s = re.sub(r'\bpc\b', 'PC', s)
    s = re.sub(r'\bs\d+\b', 'S', s); s = re.sub(r'\bd\d+\b', 'D', s); s = re.sub(r'\bq\d+\b', 'Q', s)
    s = re.sub(r'#-?(0x[0-9a-f]+|[0-9.e+-]+)', '#N', s)
    s = re.sub(r'\[\d+\]', '[k]', s)
    return f'{i.insn_name()}{"." + dts if dts else ""}{"S" if i.update_flags else ""} {s}'

saida = {}
for lib, t in (('libMGS2HD.so', False), ('libgnustl_shared.so', True)):
    e, fs = analisar('libs/' + lib, t)
    grupos = collections.defaultdict(list)
    for ini, fim, insns, probs, tabs in fs:
        dentro_it = set()
        for a, i in insns.items():
            if i.insn_name() == 'it':
                n = len(i.mnemonic) - 1          # it, itt, itte...
                k = a + i.size
                for _ in range(n):
                    if k in insns:
                        dentro_it.add(k); k += insns[k].size
        for a, i in insns.items():
            f = forma(i)
            if len(grupos[f]) < 12:
                grupos[f].append((a, a in dentro_it))
    saida[lib] = grupos
    print(lib, len(grupos), 'formas')
json.dump(saida, open('amostras.json', 'w'))
