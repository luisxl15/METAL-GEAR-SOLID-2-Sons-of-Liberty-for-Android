"""Extrai as OBBs (ZIP) do MGS2 do SHIELD numa pasta, patch por cima do main.

Por que: a Forge tentava montar as OBBs com StorageManager.mountObb (o Android
atual nao monta mais, e estas OBBs sao ZIP); na versao 21.21 o downloader
Lightspeed deixava os dados SOLTOS em /sdcard/Android/data/<pacote>/files/, e e
de la que o motor le (em minusculas, mas o armazenamento externo do Android nao
diferencia maiusculas). O unzip do toybox no celular falha no main ("Inconsistent
information"), entao extraimos no PC e o instalar.sh empurra com adb push.

    python extrair_obb.py            -> dados_jogo/ (uns 5 GB)
"""
import os, struct, sys, time, zipfile, zlib

AQUI = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(AQUI, 'recomp'))
import caminhos
ORIGEM = caminhos.JOGO   # pasta jogo/ com as OBBs (ou MGS2_JOGO)
DESTINO = os.path.join(AQUI, 'dados_jogo')


def dados_de(f, i):
    """Os cabecalhos locais destas OBBs tem o NOME VAZIO (so o diretorio central
    tem os nomes): o zipfile e o unzip do toybox recusam. Lemos pelo deslocamento."""
    f.seek(i.header_offset)
    h = f.read(30)
    if h[:4] != b'PK\x03\x04':
        raise ValueError(f'cabecalho local invalido em {i.filename}')
    n_nome, n_extra = struct.unpack('<HH', h[26:30])
    f.seek(i.header_offset + 30 + n_nome + n_extra)
    bruto = f.read(i.compress_size)
    if i.compress_type == 0:
        return bruto
    if i.compress_type == 8:
        return zlib.decompress(bruto, -15)
    raise ValueError(f'compressao {i.compress_type} em {i.filename}')


def extrai(obb):
    z = zipfile.ZipFile(obb)
    f = open(obb, 'rb')
    itens = [i for i in z.infolist() if not i.is_dir()]
    total = sum(i.file_size for i in itens)
    feito, t0, ult = 0, time.time(), 0
    for i in itens:
        d = dados_de(f, i)
        if len(d) != i.file_size or (zlib.crc32(d) & 0xffffffff) != i.CRC:
            raise ValueError(f'CRC/tamanho errado em {i.filename}')
        dst = os.path.join(DESTINO, *i.filename.split('/'))
        os.makedirs(os.path.dirname(dst), exist_ok=True)
        with open(dst, 'wb') as o:
            o.write(d)
        feito += i.file_size
        if time.time() - ult > 5:
            ult = time.time()
            print(f'  {os.path.basename(obb)}: {feito / 1e9:.2f}/{total / 1e9:.2f} GB ({feito * 100 // max(total, 1)}%)', flush=True)
    print(f'  {os.path.basename(obb)}: {len(itens)} arquivos, {total / 1e9:.2f} GB em {time.time() - t0:.0f}s', flush=True)


def main():
    os.makedirs(DESTINO, exist_ok=True)
    for nome in ('main.14.jp.konami.mgs2hd.shield.obb', 'patch.14.jp.konami.mgs2hd.shield.obb'):
        extrai(os.path.join(ORIGEM, nome))
    open(os.path.join(DESTINO, '.extraido'), 'w').write('main.14 + patch.14\n')
    print('pronto:', DESTINO)


if __name__ == '__main__':
    main()
