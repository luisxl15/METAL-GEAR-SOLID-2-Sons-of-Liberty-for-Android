"""Compila o runtime + o C gerado para o PC (Windows x64) e liga teste_pc.exe.
Pontes ainda nao escritas viram stubs que param com o nome (pontes_faltando.c)."""
import glob, os, re, subprocess, sys, concurrent.futures as cf
AQUI = os.path.dirname(os.path.abspath(__file__))
import caminhos
CLANG = caminhos.exe(caminhos.LLVM_PC, 'clang')
OBJ = os.path.join(AQUI, 'build', 'pc')
os.makedirs(OBJ, exist_ok=True)
OPT = sys.argv[1] if len(sys.argv) > 1 else '-O1'
EXTRA = sys.argv[2:]

def stubs():
    pedidas = re.findall(r'void (I_\w+)\(CPU \*c\);', open(os.path.join(AQUI, 'saida', 'funcoes.h')).read())
    feitas = set()
    for f in glob.glob(os.path.join(AQUI, 'runtime', '*.c')):
        if os.path.basename(f) in ('pontes_faltando.c', 'gl_auto.c', 'gl_manual.c', 'jni_auto.c', 'sles.c', 'android.c'): continue
        feitas |= set(re.findall(r'void (I_\w+)\(CPU \*c\)', open(f, encoding='utf-8').read()))
    falta = [p for p in pedidas if p not in feitas]
    with open(os.path.join(AQUI, 'runtime', 'pontes_faltando.c'), 'w') as o:
        o.write('#include "runtime.h"\n')
        for p in falta:
            o.write(f'void {p}(CPU *c) {{ (void)c; rt_fatal("ponte nao implementada: {p[2:]}"); }}\n')
        o.write('#ifdef _WIN32\nvoid rt_quadro(void) {}\nuint32_t gl_ponte_por_nome(const char *n) { (void)n; return 0; }\n'
                'uint32_t jni_tabela_jogo(void) { return 0; }\nuint32_t jni_tabela_vm_jogo(void) { return 0; }\n#endif\n')
    print(f'pontes: {len(pedidas)} pedidas, {len(pedidas) - len(falta)} feitas, {len(falta)} stubs')

def compila(src):
    obj = os.path.join(OBJ, os.path.basename(src).replace('.c', '.o'))
    if os.path.exists(obj) and os.path.getmtime(obj) > os.path.getmtime(src) and 'saida' in src:
        return None
    r = subprocess.run([CLANG, OPT, *EXTRA, '-c', '-w', '-ffp-contract=off', '-fno-strict-aliasing', '-fwrapv',
                        '-I', os.path.join(AQUI, 'runtime'), '-I', os.path.join(AQUI, 'saida'), src, '-o', obj],
                       capture_output=True, text=True)
    return (src, r.stderr) if r.returncode else None

stubs()
fontes = glob.glob(os.path.join(AQUI, 'runtime', '*.c')) + glob.glob(os.path.join(AQUI, 'saida', '*.c'))
with cf.ThreadPoolExecutor(max_workers=os.cpu_count()) as ex:
    erros = [r for r in ex.map(compila, fontes) if r]
for s, e in erros[:5]:
    print('ERRO', s); print(e[:3000])
if erros:
    sys.exit(1)
objs = glob.glob(os.path.join(OBJ, '*.o'))
r = subprocess.run([CLANG, *objs, '-o', os.path.join(AQUI, 'build', 'teste_pc.exe'), '-Wl,/STACK:268435456'], capture_output=True, text=True)
print(r.stderr[:3000] or 'ligado: build/teste_pc.exe')
