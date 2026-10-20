"""Onde estao as ferramentas e os arquivos do jogo (um lugar so para todos os scripts).

Ferramentas (descobertas sozinhas; variaveis de ambiente sobrepoem):
  ANDROID_HOME / ANDROID_SDK_ROOT   SDK do Android   (padrao: %LOCALAPPDATA%/Android/Sdk)
  ANDROID_NDK_HOME                  NDK              (padrao: o NDK mais novo dentro do SDK)
  JAVA_HOME                         JDK 17+          (padrao: o java/javac do PATH)

Arquivos do SEU jogo (nunca vao para o repositorio):
  MGS2_JOGO   pasta com base.apk, main.14.jp.konami.mgs2hd.shield.obb e
              patch.14.jp.konami.mgs2hd.shield.obb      (padrao: <repositorio>/jogo)
"""
import glob, os, shutil

AQUI = os.path.dirname(os.path.abspath(__file__))
RAIZ = os.path.dirname(AQUI)
PKG = 'jp.konami.mgs2hd.shield'


def _primeiro(*c):
    for x in c:
        if x and os.path.isdir(x):
            return x.replace('\\', '/')
    return None


SDK = _primeiro(os.environ.get('ANDROID_HOME'), os.environ.get('ANDROID_SDK_ROOT'),
                os.path.join(os.environ.get('LOCALAPPDATA', ''), 'Android', 'Sdk'),
                os.path.expanduser('~/Android/Sdk'), os.path.expanduser('~/Library/Android/sdk'))


def _mais_novo(padrao):
    def chave(p):
        return [int(x) if x.isdigit() else 0 for x in os.path.basename(p).replace('-', '.').split('.')]
    achados = sorted(glob.glob(padrao), key=chave)
    return achados[-1].replace('\\', '/') if achados else None


NDK_RAIZ = _primeiro(os.environ.get('ANDROID_NDK_HOME')) or (_mais_novo(os.path.join(SDK, 'ndk', '*')) if SDK else None)
_hosts = glob.glob(os.path.join(NDK_RAIZ, 'toolchains', 'llvm', 'prebuilt', '*')) if NDK_RAIZ else []
NDK_LLVM = _hosts[0].replace('\\', '/') if _hosts else None
NDK_BIN = NDK_LLVM + '/bin' if NDK_LLVM else None                       # clang, clang++, llvm-*
NDK_SYSROOT_INC = NDK_LLVM + '/sysroot/usr/include' if NDK_LLVM else None
NDK_SHADERS = _mais_novo(os.path.join(NDK_RAIZ, 'shader-tools', '*')) if NDK_RAIZ else None   # glslc, spirv-val
BUILD_TOOLS = _mais_novo(os.path.join(SDK, 'build-tools', '*')) if SDK else None             # zipalign, apksigner, d8
PLATAFORMA = _mais_novo(os.path.join(SDK, 'platforms', 'android-*')) if SDK else None        # android.jar

_java = os.environ.get('JAVA_HOME')
JDK_BIN = (os.path.join(_java, 'bin') if _java else os.path.dirname(shutil.which('javac') or shutil.which('java') or '')).replace('\\', '/')

LLVM_PC = _primeiro(os.environ.get('LLVM_HOME') and os.path.join(os.environ['LLVM_HOME'], 'bin'),
                    os.path.dirname(shutil.which('clang') or ''), 'C:/Program Files/LLVM/bin')   # clang do PC (testes)

JOGO = (os.environ.get('MGS2_JOGO') or os.path.join(RAIZ, 'jogo')).replace('\\', '/')
APK_ORIGINAL = os.path.join(JOGO, 'base.apk').replace('\\', '/')
OBBS = [os.path.join(JOGO, f'{n}.14.{PKG}.obb').replace('\\', '/') for n in ('main', 'patch')]


def exe(pasta, nome):
    """caminho do executavel nome (com .exe/.bat no Windows) dentro de pasta"""
    for ext in ('', '.exe', '.bat', '.cmd'):
        p = os.path.join(pasta or '', nome + ext)
        if os.path.exists(p):
            return p.replace('\\', '/')
    return os.path.join(pasta or '', nome).replace('\\', '/')


if __name__ == '__main__':
    for k in ('SDK', 'NDK_RAIZ', 'NDK_BIN', 'NDK_SHADERS', 'BUILD_TOOLS', 'PLATAFORMA', 'JDK_BIN', 'JOGO', 'APK_ORIGINAL'):
        v = globals()[k]
        print(f'{k:14} {v}  {"" if v and os.path.exists(v) else "<- NAO ENCONTRADO"}')
