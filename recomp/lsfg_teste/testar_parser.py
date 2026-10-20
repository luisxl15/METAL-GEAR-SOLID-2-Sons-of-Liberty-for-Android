"""Testa o leitor de Lossless.dll do runtime contra o DLL de teste.

Confere, para CADA modulo devolvido:
  - spirv-val aceita o modulo renumerado;
  - os bindings viraram 0..n-1, na MESMA ordem dos originais (1, 4, 7...);
  - n = a quantidade de descritores que o passe declara (fazer_dll_teste.PASSES).
Controles (tem de RECUSAR): um DLL sem os recursos (o lld-link sem .res) e um arquivo
que nao e PE. Imprime quantos itens mediu em cada verificacao.
"""
import os, struct, subprocess, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import fazer_dll_teste as F

AQUI = os.path.dirname(os.path.abspath(__file__))
CLANG = F.caminhos.exe(F.LLVM, 'clang++')


def bindings(path):
    w = open(path, 'rb').read()
    w = struct.unpack(f'<{len(w) // 4}I', w)
    out, o = [], 5
    while o < len(w):
        n, op = w[o] >> 16, w[o] & 0xffff
        if op == 54:
            break
        if op == 71 and n >= 4 and w[o + 2] == 33:
            out.append(w[o + 3])
        o += n
    return out


def main():
    exe = os.path.join(AQUI, 'obra', 'teste_parser.exe')
    subprocess.run([CLANG, '-std=c++20', '-O1', '-w', os.path.join(AQUI, 'teste_parser.cpp'), '-o', exe], check=True)
    saida = os.path.join(AQUI, 'obra', 'adotados')
    os.makedirs(saida, exist_ok=True)
    for f in os.listdir(saida):
        os.remove(os.path.join(saida, f))
    r = subprocess.run([exe, os.path.join(AQUI, 'Lossless_teste.dll'), saida], capture_output=True, text=True)
    print('DLL de teste:', r.stdout.strip())
    if r.returncode:
        sys.exit(1)
    ruins = 0; medidos = 0
    for id_, layout in sorted(F.PASSES.items()):
        p = os.path.join(saida, f'{id_}.spv')
        if not os.path.exists(p):
            print(f'  {id_}: FALTA'); ruins += 1; continue
        medidos += 1
        v = subprocess.run([F.SPIRV_VAL, '--target-env', 'vulkan1.2', p], capture_output=True, text=True)
        b = bindings(p)
        orig = bindings(os.path.join(AQUI, 'obra', f's{id_}.spv'))
        esperado = sum(n for n, _ in layout)
        ordem_ok = [sorted(orig).index(x) for x in orig] == b
        if v.returncode or sorted(b) != list(range(esperado)) or not ordem_ok:
            ruins += 1
            print(f'  {id_}: val={v.returncode} bindings={b} originais={orig} esperado 0..{esperado - 1}')
    print(f'modulos medidos: {medidos} de {len(F.PASSES)}; com problema: {ruins}')
    # controles
    vazio = os.path.join(AQUI, 'obra', 'sem_recursos.dll')
    subprocess.run([os.path.join(F.LLVM, 'lld-link.exe'), '/dll', '/noentry', '/machine:x64', f'/out:{vazio}',
                    os.path.join(AQUI, 'obra', 'teste.res').replace('teste.res', 'nada.res')], capture_output=True)
    if not os.path.exists(vazio):   # lld-link nao liga sem entrada: usa o proprio exe do teste (PE sem os recursos)
        vazio = exe
    texto = os.path.join(AQUI, 'obra', 'nao_pe.dll')
    open(texto, 'wb').write(b'isto nao e um PE' * 100000)
    for nome, arq in (('PE sem os shaders', vazio), ('arquivo que nao e PE', texto)):
        r = subprocess.run([exe, arq, saida], capture_output=True, text=True)
        print(f'controle ({nome}): {r.stdout.strip()}  ->', 'OK' if r.returncode == 1 else 'FALHOU (aceitou!)')
        ruins += r.returncode != 1
    sys.exit(1 if ruins else 0)


if __name__ == '__main__':
    main()
