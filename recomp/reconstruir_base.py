"""Reconstroi o base.apk do SHIELD (Java da Forge, recursos, assets) a partir de um APK
nosso ja montado, para o empacotar.py nao depender da pasta original do jogo na Area de
Trabalho (ela sumiu em 20/10/2026).

Tira o que o empacotar.py acrescenta (lib/arm64-v8a, classes2.dex, assets/controles,
assinatura) e desfaz a troca do LAUNCHER no manifesto (mesmo tamanho, 40 letras).
O assets/config fica como esta: o empacotar.py reescreve PersistentVBO e DebugMsg sempre.
O original tinha lib/armeabi-v7a/, que o empacotar.py descarta de qualquer jeito.

    python reconstruir_base.py [apk nosso]  ->  base_shield.apk
"""
import os, sys, zipfile
import manifesto

AQUI = os.path.dirname(os.path.abspath(__file__))
ORIGEM = sys.argv[1] if len(sys.argv) > 1 else os.path.join(AQUI, 'build', 'MGS2-ARM64-v1.apk')
DESTINO = os.path.join(AQUI, 'base_shield.apk')
NOSSO, ORIG = 'com.nvidia.forge.ArranqueTelaCheiaMGS2HD', 'com.nvidia.forge.ForgeDownloaderActivity'


def nosso(n):
    return (n.startswith('lib/') or n == 'classes2.dex' or n.startswith('assets/controles/')
            or n.startswith('META-INF/') and n.split('.')[-1] in ('RSA', 'SF', 'MF', 'DSA', 'EC'))


def main():
    tirados = mantidos = 0
    with zipfile.ZipFile(ORIGEM) as zi, zipfile.ZipFile(DESTINO, 'w') as zo:
        for it in zi.infolist():
            if nosso(it.filename):
                tirados += 1
                continue
            dados = zi.read(it.filename)
            if it.filename == 'AndroidManifest.xml':
                dados = manifesto.renomeia_string(dados, NOSSO, ORIG)
            zo.writestr(it, dados, compress_type=it.compress_type)
            mantidos += 1
    # conferencia: nada nosso e o manifesto com o nome original
    with zipfile.ZipFile(DESTINO) as z:
        sobra = [n for n in z.namelist() if nosso(n)]
        man = z.read('AndroidManifest.xml')
        tem_orig = ORIG.encode('utf-16-le') in man or ORIG.encode() in man
        tem_nosso = NOSSO.encode('utf-16-le') in man or NOSSO.encode() in man
        tem_dex = 'classes.dex' in z.namelist()
    print(f'{ORIGEM} -> {DESTINO}: {mantidos} entradas mantidas, {tirados} tiradas')
    print(f'  conferencia: sobras nossas {len(sobra)}, manifesto com o nome original {tem_orig}, '
          f'com o nosso {tem_nosso}, classes.dex da Forge {tem_dex}')
    if sobra or not tem_orig or tem_nosso or not tem_dex:
        sys.exit('RECONSTRUCAO RUIM')


if __name__ == '__main__':
    main()
