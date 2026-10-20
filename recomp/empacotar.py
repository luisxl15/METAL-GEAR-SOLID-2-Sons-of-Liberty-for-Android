"""Monta o APK do MGS2 recompilado para ARM64.

Parte do base.apk do SHIELD (Java da Forge, recursos, assets) e:
  - tira lib/armeabi-v7a/* e a assinatura antiga (META-INF);
  - poe lib/arm64-v8a/* de build/android/libs;
  - assets/config: PersistentVBO = N (o mapa persistente de buffer nao cabe
    na sombra de memoria do jogo);
  - zipalign + assinatura com chave propria (assinatura.jks).

    python empacotar.py        ->  build/MGS2-ARM64.apk
"""
import os, re, subprocess, sys, zipfile

AQUI = os.path.dirname(os.path.abspath(__file__))
import caminhos
APK_ORIG = caminhos.APK_ORIGINAL                 # o base.apk do SEU jogo (jogo/base.apk)
if not os.path.exists(APK_ORIG):                 # ou uma copia reconstruida (reconstruir_base.py)
    APK_ORIG = os.path.join(AQUI, 'base_shield.apk')
BT = caminhos.BUILD_TOOLS
JDK = caminhos.JDK_BIN
# sabor (ver construir_android.py): adreno -> MGS2-ARM64.apk, mali -> MGS2-ARM64-Mali.apk
SABOR = os.environ.get('MGS2_SABOR', 'adreno')
DEPURA = os.environ.get('MGS2_DEPURA') == '1'
NOME = SABOR + ('_dep' if DEPURA else '')
LIBS = os.path.join(AQUI, 'build', 'android', 'libs_' + NOME)
CRU = os.path.join(AQUI, 'build', f'MGS2-{NOME}-cru.apk')
ALI = os.path.join(AQUI, 'build', f'MGS2-{NOME}-alinhado.apk')
FINAL = os.path.join(AQUI, 'build', 'MGS2-ARM64' + ('-Mali' if SABOR == 'mali' else '') + ('-depuracao' if DEPURA else '') + '.apk')
CHAVE = os.path.join(AQUI, 'assinatura.jks')


def config_novo(txt):
    txt, n = re.subn(r'"PersistentVBO"\s*=\s*"Y"', '"PersistentVBO" = "N"', txt)
    print(f'  assets/config: PersistentVBO -> N ({n} troca)')
    # diagnostico: canais de log da camada da TransGaming (derivada do Wine).
    # So na depuracao (MGS2_DEPURA=1); MGS2_DEBUGMSG sobrepoe.
    dm = os.environ.get('MGS2_DEBUGMSG', 'err+all,warn+all' if DEPURA else '-all')
    txt, n = re.subn(r'"DebugMsg"\s*=\s*"[^"]*"', f'"DebugMsg" = "{dm}"', txt)
    print(f'  assets/config: DebugMsg -> {dm} ({n} troca)')
    # resolucao de desenho do jogo: chave da Forge [droiddrv] SupportedResolutions
    res = os.environ.get('MGS2_RES')
    if res:
        txt = txt.rstrip() + f'\n\n[droiddrv]\n"SupportedResolutions" = "{res}"\n'
        print(f'  assets/config: [droiddrv] SupportedResolutions = {res}')
    return txt


def main():
    faltam = [f for f in ('libMGS2HD.so', 'libjava_util.so', 'libmgs2img_gnustl.so', 'libmgs2img_jogo.so')
              if not os.path.exists(os.path.join(LIBS, f))]
    if faltam:
        sys.exit(f'faltam em build/android/libs: {faltam} (rode construir_android.py)')
    with zipfile.ZipFile(APK_ORIG) as zi, zipfile.ZipFile(CRU, 'w') as zo:
        for it in zi.infolist():
            n = it.filename
            if n.startswith('lib/') or n.startswith('META-INF/') and n.split('/')[-1].split('.')[-1] in ('RSA', 'SF', 'MF', 'DSA', 'EC'):
                continue
            dados = zi.read(n)
            if n == 'assets/config':
                dados = config_novo(dados.decode('latin-1')).encode('latin-1')
            if n == 'AndroidManifest.xml':
                # O LAUNCHER estava no ForgeDownloaderActivity (downloader Lightspeed,
                # servidor morto da NVIDIA). O nome dele (40 letras) vira o da nossa
                # classe (java_tela/, classes2.dex), subclasse do Splash que poe tudo
                # em tela cheia/imersivo e centraliza o video: icone -> nossa classe
                # (= Splash) -> MainActivity.
                import manifesto
                dados = manifesto.renomeia_string(dados, 'com.nvidia.forge.ForgeDownloaderActivity',
                                                  'com.nvidia.forge.ArranqueTelaCheiaMGS2HD')
                print('  AndroidManifest: LAUNCHER -> ArranqueTelaCheiaMGS2HD')
            # resources.arsc e os demais mantem o metodo original
            zo.writestr(it, dados, compress_type=it.compress_type)
        dex2 = os.path.join(AQUI, 'java_tela', 'classes2.dex')
        if not os.path.exists(dex2):
            sys.exit('falta java_tela/classes2.dex (rode bash java_tela/compilar.sh)')
        zo.write(dex2, 'classes2.dex', compress_type=zipfile.ZIP_DEFLATED)
        print('  + classes2.dex (tela cheia, menu, ajustes, controles na tela)')
        pasta = os.path.join(AQUI, 'java_tela', 'assets')
        for base, _, arqs in os.walk(pasta):
            for a in sorted(arqs):
                f = os.path.join(base, a)
                zo.write(f, 'assets/' + os.path.relpath(f, pasta).replace(os.sep, '/'), compress_type=zipfile.ZIP_STORED)
        print('  + assets/controles/ (imagens dos botoes, as mesmas do MGR)')
        for f in sorted(os.listdir(LIBS)):
            zo.write(os.path.join(LIBS, f), f'lib/arm64-v8a/{f}', compress_type=zipfile.ZIP_DEFLATED)
            print(f'  + lib/arm64-v8a/{f}')
    if not os.path.exists(CHAVE):
        subprocess.run([caminhos.exe(JDK, 'keytool'), '-genkeypair', '-keystore', CHAVE, '-storepass', 'mgs2arm64',
                        '-keypass', 'mgs2arm64', '-alias', 'mgs2', '-keyalg', 'RSA', '-keysize', '2048', '-validity', '10000',
                        '-dname', 'CN=MGS2 ARM64'], check=True)
    subprocess.run([caminhos.exe(BT, 'zipalign'), '-f', '-p', '4', CRU, ALI], check=True)
    subprocess.run([caminhos.exe(BT, 'apksigner'), 'sign', '--ks', CHAVE, '--ks-pass', 'pass:mgs2arm64',
                    '--out', FINAL, ALI], check=True, shell=True)
    os.remove(CRU); os.remove(ALI)
    print(f'pronto: {FINAL} ({os.path.getsize(FINAL) / 1e6:.0f} MB)')


if __name__ == '__main__':
    main()
