"""Confere as traducoes da casca Java (Textos.java):
  - cada Textos.t("..")/Textos.f("..") do codigo tem a chave na tabela;
  - cada linha da tabela tem os 7 idiomas;
  - os marcadores %... de cada traducao batem com os do portugues (senao String.format quebra).
Imprime quantos itens mediu em cada verificacao.

    python java_tela/conferir_textos.py
"""
import glob, os, re, sys

D = os.path.join(os.path.dirname(os.path.abspath(__file__)), 'src', 'com', 'nvidia', 'forge')
CADEIA = r'"((?:[^"\\]|\\.)*)"'
txt = open(os.path.join(D, 'Textos.java'), encoding='utf-8').read()
tab = txt[txt.index('private static final String[][] T'):txt.index('private static Map')]
linhas = []
SEM_GRUPO = r'"(?:[^"\\]|\\.)*"'
for bloco in re.findall(r'\{\s*(' + SEM_GRUPO + r'(?:\s*,\s*' + SEM_GRUPO + r')*)\s*\}', tab):
    linhas.append(re.findall(CADEIA, bloco))
chaves = {l[0] for l in linhas}
ruim = 0
incompletas = [l[0] for l in linhas if len(l) != 7]
for k in incompletas:
    print('  linha sem 7 idiomas:', k[:60]); ruim += 1
marca = lambda s: sorted(re.findall(r'%[-+ 0#]*\d*(?:\.\d+)?[sdf]', s))
fmt = 0
for l in linhas:
    for v in l[1:]:
        fmt += 1
        if marca(v) != marca(l[0]):
            print(f'  marcadores diferentes: {l[0][:40]!r} -> {v[:40]!r}'); ruim += 1
usos = 0
for f in glob.glob(os.path.join(D, '*.java')):
    if f.endswith('Textos.java'):
        continue
    for k in re.findall(r'Textos\.[tf]\(' + CADEIA, open(f, encoding='utf-8').read()):
        usos += 1
        if k not in chaves:
            print(f'  {os.path.basename(f)}: chave fora da tabela: {k[:60]!r}'); ruim += 1
print(f'{len(linhas)} linhas na tabela, {usos} usos no codigo, {fmt} traducoes com marcadores conferidos; problemas: {ruim}')
sys.exit(1 if ruim or not usos or not linhas else 0)
