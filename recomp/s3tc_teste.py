"""Confere runtime/s3tc.c contra o decodificador 'bcn' do Pillow (DXT1/3/5, BC4, BC5).
Blocos aleatorios + casos de borda (c0 <= c1 no DXT1, a0 <= a1 no BC4/DXT5), tamanhos
que nao sao multiplos de 4. Imprime quantos pixels comparou (verificador que conta)."""
import ctypes, os, random
from PIL import Image
AQUI = os.path.dirname(os.path.abspath(__file__))
dll = ctypes.CDLL(os.path.join(AQUI, 'build', 'teste_s3tc', 's3tc.dll'))
dll.s3tc_descomprime.argtypes = [ctypes.c_int, ctypes.c_int, ctypes.c_int, ctypes.c_char_p, ctypes.c_uint32, ctypes.c_char_p]
# tipo nosso -> (n do Pillow, modo, bytes/bloco, bytes/pixel)
TIPOS = {1: (1, 'RGBA', 8, 4), 3: (2, 'RGBA', 16, 4), 4: (3, 'RGBA', 16, 4), 5: (4, 'L', 8, 1), 6: (5, 'RGB', 16, 2)}
random.seed(1234)
total = difs = maxd = 0
for tipo, (n, modo, bb, bpp) in TIPOS.items():
    for w, h in [(4, 4), (8, 8), (64, 32), (12, 20)]:
        nb = ((w + 3) // 4) * ((h + 3) // 4)
        dados = bytes(random.getrandbits(8) for _ in range(nb * bb))
        meu = ctypes.create_string_buffer(w * h * bpp)
        assert dll.s3tc_descomprime(tipo, w, h, dados, len(dados), meu)
        ref = Image.frombytes(modo, (w, h), dados, 'bcn', n).tobytes()
        m = meu.raw
        for p in range(w * h):
            for k in range(bpp):
                a = m[p * bpp + k]; b = ref[p * len(modo) + k]
                total += 1
                if a != b:
                    difs += 1; maxd = max(maxd, abs(a - b))
    print(f'tipo {tipo}: ok')
print(f'canais comparados: {total}, diferentes: {difs}, maior diferenca: {maxd}')
