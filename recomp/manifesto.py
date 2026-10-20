"""Edita o AndroidManifest.xml binario (AXML) no lugar.

troca_nomes(dados, a, b): nos elementos cujo android:name e a string `a`,
passa a ser `b`, e vice-versa.  So troca indices do pool de strings (4 bytes
em cada atributo), sem mexer em tamanhos: o arquivo continua valido.

Uso no MGS2: o intent-filter LAUNCHER esta no elemento da
ForgeDownloaderActivity (o downloader "Lightspeed", que depende de um servidor
da NVIDIA que nao existe mais).  Trocando o nome dela com o da
NvidiaSplashVideoActivity, o icone abre o video da NVIDIA -> MainActivity
(que chama PreferencesManager.initPaths sozinha).
"""
import struct

ATTR_NAME = 0x01010003


def pool(dados):
    """devolve lista de strings do pool (UTF-16 ou UTF-8)"""
    tipo, cab, tam = struct.unpack_from('<HHI', dados, 8)
    assert tipo == 0x0001, 'pool de strings nao encontrado'
    n, nest, flags, ini_str, ini_est = struct.unpack_from('<IIIII', dados, 8 + 8)
    utf8 = flags & 0x100
    offs = struct.unpack_from(f'<{n}I', dados, 8 + cab)
    base = 8 + ini_str
    out = []
    for o in offs:
        p = base + o
        if utf8:
            l = dados[p]; p += 2 if l & 0x80 else 1
            l2 = dados[p]
            if l2 & 0x80:
                l2 = ((l2 & 0x7f) << 8) | dados[p + 1]; p += 2
            else:
                p += 1
            out.append(dados[p:p + l2].decode('utf-8'))
        else:
            l = struct.unpack_from('<H', dados, p)[0]; p += 2
            if l & 0x8000:
                l = ((l & 0x7fff) << 16) | struct.unpack_from('<H', dados, p)[0]; p += 2
            out.append(dados[p:p + 2 * l].decode('utf-16-le'))
    return out, 8 + tam


def ids_recurso(dados, fim_pool):
    tipo, cab, tam = struct.unpack_from('<HHI', dados, fim_pool)
    if tipo != 0x0180:
        return [], fim_pool
    n = (tam - cab) // 4
    return list(struct.unpack_from(f'<{n}I', dados, fim_pool + cab)), fim_pool + tam


def renomeia_string(dados, velho, novo):
    """Troca o TEXTO de uma string do pool por outro de mesmo tamanho (nenhum
    deslocamento muda). Usado para apontar o LAUNCHER para uma classe nossa."""
    assert len(velho) == len(novo), f'{novo!r} precisa ter {len(velho)} caracteres'
    d = bytearray(dados)
    tipo, cab, tam = struct.unpack_from('<HHI', d, 8)
    n, nest, flags, ini_str, ini_est = struct.unpack_from('<IIIII', d, 16)
    cod = 'utf-8' if flags & 0x100 else 'utf-16-le'
    a, b = velho.encode(cod), novo.encode(cod)
    base, fim = 8 + ini_str, 8 + (ini_est if ini_est else tam)
    k = d.find(a, base, fim)
    assert k >= 0 and d.find(a, k + 1, fim) < 0, f'{velho!r} nao achado (ou repetido) no pool'
    d[k:k + len(a)] = b
    return bytes(d)


def troca_nomes(dados, a, b):
    d = bytearray(dados)
    strs, fim = pool(d)
    ia, ib = strs.index(a), strs.index(b)
    ids, p = ids_recurso(d, fim)
    trocas = 0
    while p < len(d):
        tipo, cab, tam = struct.unpack_from('<HHI', d, p)
        if tipo == 0x0102:     # inicio de elemento
            n_attr = struct.unpack_from('<H', d, p + 16 + 12)[0]
            ini_attr = struct.unpack_from('<H', d, p + 16 + 8)[0]
            passo = struct.unpack_from('<H', d, p + 16 + 10)[0]
            for k in range(n_attr):
                q = p + 16 + ini_attr + k * passo
                ns, nome, cru, vtam, _, vtipo, vdado = struct.unpack_from('<IIIHBBI', d, q)
                if nome < len(ids) and ids[nome] == ATTR_NAME and vtipo == 0x03 and vdado in (ia, ib):
                    novo = ib if vdado == ia else ia
                    struct.pack_into('<I', d, q + 8, novo)     # valor cru
                    struct.pack_into('<I', d, q + 16, novo)    # valor tipado
                    trocas += 1
        p += tam
    return bytes(d), trocas


if __name__ == '__main__':
    import sys, zipfile
    z = zipfile.ZipFile(sys.argv[1])
    m = z.read('AndroidManifest.xml')
    novo, n = troca_nomes(m, 'com.nvidia.forge.ForgeDownloaderActivity', 'com.nvidia.forge.NvidiaSplashVideoActivity')
    print('trocas:', n)
    open(sys.argv[2], 'wb').write(novo)
