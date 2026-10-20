"""Fuzz de funcoes inteiras: Unicorn (binario original) x C recompilado.

Sorteia funcoes-folha do jogo (sem chamadas e sem saltos para fora), roda cada
uma com estados aleatorios nos dois lados, sobre as mesmas imagens relocadas e
a mesma janela de memoria, e compara r0-r13, bandeiras, a janela e a area de
dados do jogo.  Valida fluxo de controle (rotulos, tabelas de salto, literais,
quedas), que o teste por instrucao nao cobre.

    python fuzz_funcoes.py [--n 400] [--rodadas 6] [--lib libMGS2HD.so]
"""
import argparse, ctypes, hashlib, os, pickle, random, struct, subprocess, sys
from unicorn import Uc, UcError, UC_ARCH_ARM, UC_MODE_ARM, UC_MODE_THUMB
from unicorn import arm_const as U
import recompilar
from recompilar import BASES

AQUI = os.path.dirname(os.path.abspath(__file__))
import caminhos
CLANG = caminhos.exe(caminhos.LLVM_PC, 'clang')
JANELA, TAM_J = 0x70000000, 0x40000
MAGICO = 0xfffffff0


def dll():
    obj = os.path.join(AQUI, 'build', 'pc')
    alvo = os.path.join(AQUI, 'build', 'rt_teste.dll')
    o = os.path.join(obj, 'rt_dll_ativo.o')
    subprocess.run([CLANG, '-O1', '-DRT_DLL', '-c', '-w', '-I', os.path.join(AQUI, 'runtime'),
                    os.path.join(AQUI, 'runtime', 'rt_dll.c'), '-o', o], check=True)
    objs = [os.path.join(obj, f) for f in os.listdir(obj) if f.endswith('.o') and f not in ('teste_pc.o', 'rt_dll.o')]
    r = subprocess.run([CLANG, '-shared', *objs, '-o', alvo], capture_output=True, text=True)
    if r.returncode:
        sys.exit(r.stderr[:3000])
    return alvo


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--n', type=int, default=400)
    ap.add_argument('--rodadas', type=int, default=6)
    ap.add_argument('--lib', default='libMGS2HD.so')
    ap.add_argument('--semente', type=int, default=17)
    ap.add_argument('--fn', default=None, help='so esta funcao (hex), com detalhes')
    a = ap.parse_args()
    sys.modules['__main__'].Funcao = recompilar.Funcao
    todas, _ = pickle.load(open(os.path.join(AQUI, 'saida', 'analise.pkl'), 'rb'))
    funcs = todas[a.lib]
    cands = []
    for ini, f in funcs.items():
        if f.veneer is not None or f.problemas or f.chamados or f.externos or not f.insns or len(f.insns) > 600:
            continue
        nomes = {i.nome for i in f.insns.values()}
        if nomes & {'ldrex', 'strex', 'ldrexb', 'strexb', 'udf', 'svc', 'mrs', 'msr', 'blx', 'bl'}:
            continue
        if any(i.nome == 'bx' and i.op_str.strip() != 'lr' for i in f.insns.values()):
            continue
        cands.append(ini)
    rnd = random.Random(a.semente)
    rnd.shuffle(cands)
    cands = cands[:a.n]
    if a.fn:
        cands = [int(a.fn, 16)]
    print(f'{len(cands)} funcoes-folha sorteadas')

    lib = ctypes.CDLL(dll())
    lib.dll_inicia.restype = ctypes.c_void_p
    gm = lib.dll_inicia()
    imgs = {}
    for nome in ('libgnustl_shared.so', 'libMGS2HD.so'):
        d = open(os.path.join(AQUI, 'saida', nome.replace('.so', '.img')), 'rb').read()
        imgs[nome] = d
        ctypes.memmove(gm + BASES[nome], d, len(d))

    uc = Uc(UC_ARCH_ARM, UC_MODE_ARM)
    uc.reg_write(U.UC_ARM_REG_C1_C0_2, uc.reg_read(U.UC_ARM_REG_C1_C0_2) | (0xf << 20))
    uc.reg_write(U.UC_ARM_REG_FPEXC, 0x40000000)
    for nome, d in imgs.items():
        uc.mem_map(BASES[nome], (len(d) + 0xfff) & ~0xfff)
        uc.mem_write(BASES[nome], d)
    uc.mem_map(JANELA, TAM_J)
    uc.mem_map(0xfffff000, 0x1000)

    # area de dados do jogo (RW) para comparar
    e = recompilar.Lib(a.lib)
    rw = [l for l in e.e.loads if l['flags'] & 2][0]
    rw0, rwn = BASES[a.lib] + rw['va'], rw['msz']

    thumb = recompilar.THUMB[a.lib]
    falhas = 0; medidas = 0; puladas = 0; nans = [0]
    exemplos = []
    for fn in cands:
        f = funcs[fn]
        for rod in range(a.rodadas):
            regs = []
            for k in range(13):
                x = rnd.random()
                if k < 4 and x < 0.5:
                    regs.append(JANELA + 0x1000 + rnd.randrange(0, 0x8000) * 4)
                elif x < 0.75:
                    regs.append(rnd.randrange(0, 64))
                else:
                    regs.append(rnd.getrandbits(32))
            sp = JANELA + 0x30000
            flags = [rnd.getrandbits(1) for _ in range(4)]
            janela = rnd.randbytes(TAM_J)
            # Unicorn
            uc.mem_write(JANELA, janela)
            for k in range(13):
                uc.reg_write(U.UC_ARM_REG_R0 + k, regs[k])
            uc.reg_write(U.UC_ARM_REG_SP, sp); uc.reg_write(U.UC_ARM_REG_LR, MAGICO)
            for d in range(32):
                uc.reg_write(U.UC_ARM_REG_D0 + d, 0)
            uc.reg_write(U.UC_ARM_REG_FPSCR, 0)
            cpsr = (uc.reg_read(U.UC_ARM_REG_CPSR) & 0x0fffffdf) | flags[0] << 31 | flags[1] << 30 | flags[2] << 29 | flags[3] << 28
            uc.reg_write(U.UC_ARM_REG_CPSR, cpsr)
            try:
                uc.emu_start(fn | (1 if f.thumb else 0), MAGICO, count=200000)
                ok_uc = uc.reg_read(U.UC_ARM_REG_PC) & ~1 == MAGICO
            except UcError:
                ok_uc = False
            if not ok_uc:
                # o Unicorn pode ter escrito nos globais antes de sair: iguala o C
                ctypes.memmove(gm + rw0, bytes(uc.mem_read(rw0, rwn)), rwn)
                puladas += 1; continue
            # C
            ctypes.memmove(gm + JANELA, janela, TAM_J)
            v = (ctypes.c_uint32 * 20)(*(regs + [sp, MAGICO, 0] + flags))
            try:
                r = lib.dll_chama(fn, v)
            except OSError as ex:
                falhas += 1
                exemplos.append(f'{fn:#x}: C caiu ({ex})')
                break
            if r:
                falhas += 1
                exemplos.append(f'{fn:#x}: rt_fatal no C')
                break
            medidas += 1
            dif = []
            for k in range(14):
                u = uc.reg_read(U.UC_ARM_REG_R0 + k if k < 13 else U.UC_ARM_REG_SP)
                if u != v[k]:
                    eh_nan = lambda x: (x & 0x7f800000) == 0x7f800000 and (x & 0x7fffff)
                    if eh_nan(u) and eh_nan(v[k]):
                        nans[0] += 1; continue
                    dif.append(f'r{k} uc={u:#x} c={v[k]:#x}')
            mu = bytes(uc.mem_read(JANELA, TAM_J))
            mc = ctypes.string_at(gm + JANELA, TAM_J)
            if mu != mc:
                # NaN padrao: ARM gera 0x7fc00000, o x86 do teste 0xffc00000 (no ARM64 e igual)
                ps = []
                for j in range(TAM_J):
                    if mu[j] != mc[j]:
                        w = j & ~3
                        fu, fc_ = struct.unpack_from('<I', mu, w)[0], struct.unpack_from('<I', mc, w)[0]
                        eh_nan = lambda x: (x & 0x7f800000) == 0x7f800000 and (x & 0x7fffff)
                        if eh_nan(fu) and eh_nan(fc_):
                            nans[0] += 1; continue
                        ps.append(j)
                if not ps:
                    mu = mc
                if ps: dif.append(f'janela +{ps[0]:#x} ({len(ps)} bytes)')
                if ps and len(exemplos) < 6:
                    print(f'  {fn:#x} rodada {rod}: janela difere em {len(ps)} bytes')
                    for j in ps[:16]:
                        print(f'    +{j:#x}: uc={mu[j]:02x} c={mc[j]:02x}')
            du = hashlib.md5(bytes(uc.mem_read(rw0, rwn))).digest()
            dc = hashlib.md5(ctypes.string_at(gm + rw0, rwn)).digest()
            if du != dc:
                bu, bc = bytes(uc.mem_read(rw0, rwn)), ctypes.string_at(gm + rw0, rwn)
                eh_nan = lambda x: (x & 0x7f800000) == 0x7f800000 and (x & 0x7fffff)
                ps = []
                for j in range(rwn):
                    if bu[j] != bc[j]:
                        w = j & ~3
                        if eh_nan(struct.unpack_from('<I', bu, w)[0]) and eh_nan(struct.unpack_from('<I', bc, w)[0]):
                            nans[0] += 1; continue
                        ps.append(j)
                if ps: dif.append(f'dados do jogo diferentes em {rw0 + ps[0]:#x} ({len(ps)} bytes)')
                if ps and len(exemplos) < 6:
                    print(f'  {fn:#x} rodada {rod}: dados diferem em {len(ps)} bytes')
                    for j in ps[:16]:
                        print(f'    {rw0 + j:#x}: uc={bu[j]:02x} c={bc[j]:02x}')
                # iguala para nao contaminar os proximos
                ctypes.memmove(gm + rw0, bytes(uc.mem_read(rw0, rwn)), rwn)
            if dif and len(exemplos) < 6:
                print(f'  {fn:#x} rodada {rod}: regs de entrada ' + ' '.join(f'{x:#x}' for x in regs[:4]) + f' | {dif[:3]}')
            if dif:
                falhas += 1
                exemplos.append(f'{fn:#x}: ' + '; '.join(dif[:4]))
                break
    print(f'bytes de NaN com so o sinal diferente (x86 x ARM), ignorados: {nans[0]}')
    print(f'{len(cands)} funcoes, {medidas} execucoes comparadas, {puladas} puladas (Unicorn saiu da janela), {falhas} funcoes com divergencia')
    for x in exemplos[:30]:
        print('  ', x)


if __name__ == '__main__':
    main()
