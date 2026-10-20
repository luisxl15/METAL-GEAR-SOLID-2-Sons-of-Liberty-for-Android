"""Roda uma funcao do jogo no Unicorn (referencia) sobre um instantaneo de
memoria gravado pelo teste do PC.  As importacoes (enderecos falsos
0xfff00000+) sao atendidas por implementacoes em Python das funcoes puras.

    python uc_instantaneo.py build/inst.bin 104e611 10b5dc4 10ad8d4 10ad7e4 0 [--rastro]

--rastro imprime cada funcao do jogo em que entra (primeira instrucao de
cada funcao conhecida), para comparar com o rastro do C recompilado.
"""
import re, struct, sys
from unicorn import Uc, UC_ARCH_ARM, UC_MODE_ARM, UC_MODE_THUMB, UC_HOOK_CODE, UC_HOOK_MEM_UNMAPPED
from unicorn import arm_const as U

arq = sys.argv[1]
fn = int(sys.argv[2], 16)
args = [int(x, 16) for x in sys.argv[3:] if not x.startswith('--')]
rastro = '--rastro' in sys.argv

tab = open('saida/tabela.c').read()
imports = {int(a, 16): n for n, a in re.findall(r'\{"(\w+)", 0x([0-9a-f]{8})u\}', tab.split('g_importacoes')[1].split('g_n_importacoes')[0])}
funcs = {int(a, 16) for a in re.findall(r'\{0x([0-9a-f]{8})u, F_', tab)}

uc = Uc(UC_ARCH_ARM, UC_MODE_ARM)
uc.reg_write(U.UC_ARM_REG_C1_C0_2, uc.reg_read(U.UC_ARM_REG_C1_C0_2) | (0xf << 20))
uc.reg_write(U.UC_ARM_REG_FPEXC, 0x40000000)
dados = open(arq, 'rb').read()
BASE = 0x00f00000
tam = (len(dados) + 0xfff) & ~0xfff
uc.mem_map(BASE, tam)
uc.mem_write(BASE, dados)
PILHA = 0x60000000
uc.mem_map(PILHA, 0x100000)
uc.mem_map(0xfff00000, 0x100000)
uc.mem_write(0xfff00000, b'\x1e\xff\x2f\xe1' * (0x100000 // 4))   # bx lr em todo endereco falso
FIM = 0xfffff000


def cstr(a):
    b = bytearray()
    while True:
        ch = uc.mem_read(a, 1)[0]
        if not ch:
            return bytes(b)
        b.append(ch); a += 1


def importacao(uc, end, tam, _):
    nome = imports.get(end)
    if end == FIM:
        return
    r0, r1, r2 = (uc.reg_read(U.UC_ARM_REG_R0 + k) for k in range(3))
    if nome == 'strcmp':
        a, b = cstr(r0), cstr(r1)
        v = (a > b) - (a < b)
        uc.reg_write(U.UC_ARM_REG_R0, v & 0xffffffff)
    elif nome == 'strlen':
        uc.reg_write(U.UC_ARM_REG_R0, len(cstr(r0)))
    elif nome == 'memcmp':
        a, b = bytes(uc.mem_read(r0, r2)), bytes(uc.mem_read(r1, r2))
        uc.reg_write(U.UC_ARM_REG_R0, ((a > b) - (a < b)) & 0xffffffff)
    elif nome in ('memcpy', 'memmove'):
        uc.mem_write(r0, bytes(uc.mem_read(r1, r2)))
    elif nome == 'memset':
        uc.mem_write(r0, bytes([r1 & 0xff]) * r2)
    else:
        print(f'importacao sem implementacao: {nome}')
        uc.emu_stop()
        return
    if rastro:
        print(f'  <import {nome}>')


uc.hook_add(UC_HOOK_CODE, importacao, begin=0xfff00000, end=0xfffffff0)
if rastro:
    def entra(uc, end, tam, _):
        if end in funcs:
            print(f'  F_{end:08x}')
    uc.hook_add(UC_HOOK_CODE, entra, begin=0x01000000, end=0x04000000)

for k, a in enumerate(args[:4]):
    uc.reg_write(U.UC_ARM_REG_R0 + k, a)
uc.reg_write(U.UC_ARM_REG_SP, PILHA + 0xf0000)
uc.reg_write(U.UC_ARM_REG_LR, FIM)
try:
    uc.emu_start(fn, FIM, count=5_000_000)
except Exception as ex:
    print('erro no unicorn:', ex, hex(uc.reg_read(U.UC_ARM_REG_PC)))
print(f'r0={uc.reg_read(U.UC_ARM_REG_R0):08x}')
