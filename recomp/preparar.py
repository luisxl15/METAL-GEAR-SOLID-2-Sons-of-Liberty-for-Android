"""Tira do base.apk do SEU jogo (pasta jogo/) as duas bibliotecas ARM32 que o recompilador le.

    python recomp/preparar.py   ->  recomp/libs/libMGS2HD.so e recomp/libs/libgnustl_shared.so
"""
import os, sys, zipfile
import caminhos

AQUI = os.path.dirname(os.path.abspath(__file__))
LIBS = os.path.join(AQUI, 'libs')


def main():
    apk = caminhos.APK_ORIGINAL
    if not os.path.exists(apk):
        sys.exit(f'nao achei {apk}\ncoloque o base.apk do MGS2 HD do SHIELD (21.21.1219.GM) na pasta jogo/ (ver README)')
    os.makedirs(LIBS, exist_ok=True)
    with zipfile.ZipFile(apk) as z:
        for nome in ('libMGS2HD.so', 'libgnustl_shared.so'):
            dados = z.read('lib/armeabi-v7a/' + nome)
            open(os.path.join(LIBS, nome), 'wb').write(dados)
            print(f'  {nome}: {len(dados) / 1e6:.1f} MB')
    print('pronto:', LIBS)


if __name__ == '__main__':
    main()
