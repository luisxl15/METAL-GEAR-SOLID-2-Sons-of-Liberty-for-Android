"""Compila para Android ARM64: libMGS2HD.so (runtime + C gerado), libjava_util.so, libnvsi.so.

    python construir_android.py                 -> sabor adreno (S25+ / Snapdragon)
    MGS2_SABOR=mali python construir_android.py  -> sabor mali (MediaTek Dimensity / GPU Mali)
    MGS2_DEPURA=1 ...                            -> liga os diagnosticos (logs, KHR_debug, amostras)

Saida em build/android/libs_<sabor>[_dep]/. Cada combinacao tem a PROPRIA pasta de
objetos com o carimbo das opcoes: mudar uma opcao recompila tudo (antes o C gerado
era reaproveitado so pela data e misturava objetos de opcoes diferentes).
"""
import glob, hashlib, os, shutil, subprocess, sys, concurrent.futures as cf
AQUI = os.path.dirname(os.path.abspath(__file__))
import caminhos
NDK = caminhos.NDK_BIN
CC = caminhos.exe(NDK, 'clang')
CXX = caminhos.exe(NDK, 'clang++')
ALVO = '--target=aarch64-linux-android26'

SABOR = os.environ.get('MGS2_SABOR', 'adreno')
DEPURA = os.environ.get('MGS2_DEPURA') == '1'
if SABOR not in ('adreno', 'mali'):
    sys.exit(f'MGS2_SABOR desconhecido: {SABOR}')
NOME = SABOR + ('_dep' if DEPURA else '')
OBJ = os.path.join(AQUI, 'build', 'android', 'obj_' + NOME)
LIBS = os.path.join(AQUI, 'build', 'android', 'libs_' + NOME)
os.makedirs(OBJ, exist_ok=True); os.makedirs(LIBS, exist_ok=True)

# ARMv8.2 + fp16 + dotprod: qualquer SoC Android de 2019 para ca (Snapdragon 855+,
# Dimensity 700+). O sabor mali afina o agendamento para os Cortex-A715/A720/X dos
# Dimensity 8000/9000; o adreno fica generico (Oryon nao tem modelo neste clang).
CPU = ['-march=armv8.2-a+fp16+dotprod']
if SABOR == 'mali':
    CPU += ['-mtune=cortex-a715', '-DMGS2_MALI']
DEF = ['-DMGS2_DEPURA'] if DEPURA else []
OPT = os.environ.get('MGS2_OPT', '-O2')
# -fomit-frame-pointer: o NDK reserva x29 em toda funcao nao-folha; o codigo gerado
# mantem c, m, r4-r11 e sp vivos atraves das chamadas (11 valores) e x19-x28 sao 10.
# -ffunction-sections + --icf=all: o lld funde corpos identicos (menos cache de instrucao).
FLAGS = [ALVO, OPT, *CPU, *DEF, '-fPIC', '-w', '-ffp-contract=off', '-fno-strict-aliasing', '-fwrapv',
         '-fvisibility=hidden', '-fomit-frame-pointer', '-ffunction-sections', '-I', os.path.join(AQUI, 'runtime'), '-I', os.path.join(AQUI, 'saida')]

carimbo = hashlib.sha1(' '.join(FLAGS).encode()).hexdigest()
arq_carimbo = os.path.join(OBJ, 'opcoes.txt')
if not os.path.exists(arq_carimbo) or open(arq_carimbo).read() != carimbo:
    for f in glob.glob(os.path.join(OBJ, '*.o')):
        os.remove(f)
    open(arq_carimbo, 'w').write(carimbo)
print(f'sabor {SABOR}{" (depuracao)" if DEPURA else ""}: {" ".join(CPU + DEF + [OPT])}')


def objeto(src):
    return os.path.join(OBJ, os.path.splitext(os.path.basename(src))[0] + '.o')


def compila(src):
    obj = objeto(src)
    if os.path.exists(obj) and os.path.getmtime(obj) > os.path.getmtime(src) and 'saida' in src:
        return None
    if src.endswith('.cpp'):   # geracao de quadros (lsfg_vk.cpp): C++20, sem excecoes
        cmd = [CXX, *[f for f in FLAGS if f not in ('-fwrapv',)], '-std=c++20', '-fno-exceptions', '-fno-rtti', '-c', src, '-o', obj]
    else:
        cmd = [CC, *FLAGS, '-c', src, '-o', obj]
    r = subprocess.run(cmd, capture_output=True, text=True)
    return (src, r.stderr) if r.returncode else None


# o teste do PC e os stubs do PC ficam de fora
fontes = [f for f in glob.glob(os.path.join(AQUI, 'runtime', '*.c')) if os.path.basename(f) not in ('teste_pc.c', 'pontes_faltando.c')]
fontes += glob.glob(os.path.join(AQUI, 'runtime', '*.cpp'))
fontes += glob.glob(os.path.join(AQUI, 'saida', '*.c'))
with cf.ThreadPoolExecutor(max_workers=os.cpu_count()) as ex:
    erros = [r for r in ex.map(compila, fontes) if r]
for s, e in erros[:6]:
    print('ERRO', s); print(e[:2500])
if erros:
    sys.exit(1)
objs = [objeto(f) for f in fontes]
r = subprocess.run([CXX, ALVO, '-shared', '-static-libstdc++', '-o', os.path.join(LIBS, 'libMGS2HD.so'), *objs,
                    '-Wl,-z,max-page-size=16384', '-Wl,--gc-sections', '-Wl,--icf=all', '-Wl,-O1', '-Wl,-soname,libMGS2HD.so',
                    '-lEGL', '-lGLESv2', '-lvulkan', '-lnativewindow', '-lOpenSLES', '-landroid', '-llog', '-ldl', '-lm'], capture_output=True, text=True)
if r.returncode:
    print(r.stderr[:5000]); sys.exit(1)
for nome, src, extra in (('libjava_util.so', os.path.join(AQUI, 'java_util', 'java_util.c'), []),
                         ('libnvsi.so', os.path.join(AQUI, '..', 'nvsi', 'libnvsi.c'), ['-llog'])):
    if not os.path.exists(src):   # componente nao incluido neste repositorio (ver README)
        print(f'aviso: {src} nao existe; {nome} nao foi gerada'); continue
    r = subprocess.run([CC, ALVO, '-O2', '-fPIC', '-shared', '-w', '-o', os.path.join(LIBS, nome), src,
                        '-Wl,-z,max-page-size=16384', *extra], capture_output=True, text=True)
    if r.returncode:
        print(nome, r.stderr[:2000]); sys.exit(1)
for nome, img in (('libmgs2img_gnustl.so', 'libgnustl_shared.img'), ('libmgs2img_jogo.so', 'libMGS2HD.img')):
    shutil.copy(os.path.join(AQUI, 'saida', img), os.path.join(LIBS, nome))
for f in sorted(os.listdir(LIBS)):
    print(f'{f:28} {os.path.getsize(os.path.join(LIBS, f)) / 1e6:8.1f} MB')
print('libs em', LIBS)
