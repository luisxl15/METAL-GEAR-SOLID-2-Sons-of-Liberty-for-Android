"""Teste diferencial por instrucao: Unicorn (referencia) x C gerado.

Para cada forma de instrucao do binario (amostras.json), pega as instrucoes
REAIS nos seus enderecos, gera o C de cada uma sozinha, compila tudo para o
PC numa DLL e compara, com varios estados aleatorios:
registradores do nucleo, bandeiras, os 32 registradores d, as bandeiras do
FPSCR e a janela de memoria.

    python diferencial.py [--lib libMGS2HD.so] [--rodadas 8] [--so forma]
"""
import argparse, ctypes, json, os, random, struct, subprocess, sys, collections
import capstone as cs
from unicorn import Uc, UcError, UC_ARCH_ARM, UC_MODE_ARM, UC_MODE_THUMB
from unicorn import arm_const as U
from elf32 import Elf
from gerar import Gerador
import ual

JANELA = 0x70000000
TAM_JANELA = 0x40000
AQUI = os.path.dirname(os.path.abspath(__file__))
import caminhos
CLANG = caminhos.exe(caminhos.LLVM_PC, 'clang')

CONTROLE = {'b', 'bl', 'blx', 'bx', 'cbz', 'cbnz', 'tbb', 'tbh', 'it', 'udf', 'svc', 'bkpt',
            'cdp', 'cdp2', 'ldc', 'ldc2', 'ldcl', 'ldc2l', 'stc', 'stcl', 'stc2l', 'mcr', 'mcr2', 'mrc',
            'ldrex', 'strex', 'ldrexb', 'strexb'}  # exclusivos: semantica testada a parte


class CPU(ctypes.Structure):
    _fields_ = [('r', ctypes.c_uint32 * 16), ('n', ctypes.c_uint32), ('z', ctypes.c_uint32),
                ('c', ctypes.c_uint32), ('v', ctypes.c_uint32), ('vfp', ctypes.c_uint32 * 64),
                ('fpnzcv', ctypes.c_uint32), ('fpscr', ctypes.c_uint32),
                ('ex_a', ctypes.c_uint32), ('ex_v', ctypes.c_uint32), ('ex_ok', ctypes.c_uint32),
                ('pilha_base', ctypes.c_uint32), ('pilha_tam', ctypes.c_uint32), ('extra', ctypes.c_void_p)]


RUNTIME_TESTE = r'''
#include "cpu.h"
#include <windows.h>
#include <stdio.h>
uint8_t *g_mem;
__declspec(dllexport) volatile int g_evento;
void despacha(CPU *c, uint32_t a) { (void)c; (void)a; g_evento = 1; }
void falha_tabela(uint32_t o, uint32_t i) { (void)o; (void)i; g_evento = 2; }
void nao_suportado(CPU *c, uint32_t o) { (void)c; (void)o; g_evento = 3; }
void armadilha(CPU *c, uint32_t o) { (void)c; (void)o; g_evento = 4; }
__declspec(dllexport) uint8_t *inicia(uint32_t janela, uint32_t tam, uint32_t tam_img) {
    g_mem = VirtualAlloc(NULL, 1ull << 32, MEM_RESERVE, PAGE_NOACCESS);
    VirtualAlloc(g_mem + janela, tam, MEM_COMMIT, PAGE_READWRITE);
    VirtualAlloc(g_mem, tam_img, MEM_COMMIT, PAGE_READWRITE);
    return g_mem;
}
'''


def eh_memoria(ops):
    return any(isinstance(o, ual.Mem) for o in ops)


def estado_aleatorio(rnd, insn, ops, thumb):
    mem = eh_memoria(ops) or insn.insn_name() in (
        'ldm', 'ldmib', 'ldmda', 'ldmdb', 'stm', 'stmib', 'stmda', 'stmdb', 'push', 'pop',
        'vpush', 'vpop', 'vldmia', 'vstmia', 'vldmdb', 'vstmdb')
    especiais = [0, 1, 2, 0x80000000, 0x7fffffff, 0xffffffff, 0xfffffffe, 31, 32, 33, 255, 256]
    regs = []
    for k in range(15):
        if mem:
            regs.append(rnd.choice([rnd.randrange(0, 64) * 4, rnd.randrange(0, 16), 0]))
        else:
            regs.append(rnd.choice(especiais) if rnd.random() < 0.25 else rnd.getrandbits(32))
    if mem:
        bases = set()
        for o in ops:
            if isinstance(o, ual.Mem):
                bases.add(o.base.n)
        n = insn.insn_name()
        if n in ('ldm', 'ldmib', 'ldmda', 'ldmdb', 'stm', 'stmib', 'stmda', 'stmdb', 'vldmia', 'vstmia', 'vldmdb', 'vstmdb'):
            bases.add(ops[0].n)
        bases.add(13)
        for b in bases:
            if b < 15:
                regs[b] = JANELA + 0x10000 + rnd.randrange(0, 256) * 8
    flags = [rnd.getrandbits(1) for _ in range(4)]
    vfp = []
    for d in range(32):
        tipo = rnd.random()
        if tipo < 0.4:
            a, b = (struct.unpack('<I', struct.pack('<f', rnd.choice([rnd.uniform(-1e4, 1e4), rnd.uniform(-2, 2), float(rnd.randint(-100, 100)), 0.0])))[0] for _ in range(2))
            vfp += [a, b]
        elif tipo < 0.7:
            x = struct.unpack('<Q', struct.pack('<d', rnd.choice([rnd.uniform(-1e6, 1e6), rnd.uniform(-2, 2), float(rnd.randint(-1000, 1000))])))[0]
            vfp += [x & 0xffffffff, x >> 32]
        else:
            vfp += [rnd.getrandbits(32), rnd.getrandbits(32)]
    fpnzcv = rnd.getrandbits(4)
    return regs, flags, vfp, fpnzcv


def eh_nan32(u): return (u & 0x7f800000) == 0x7f800000 and (u & 0x7fffff)
def eh_nan64(u): return (u >> 52 & 0x7ff) == 0x7ff and (u & 0xfffffffffffff)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--lib', default='libMGS2HD.so')
    ap.add_argument('--rodadas', type=int, default=8)
    ap.add_argument('--so', default=None)
    ap.add_argument('--semente', type=int, default=2001)
    ap.add_argument('--it', action='store_true', help='testa blocos IT inteiros (Thumb)')
    a = ap.parse_args()
    thumb = 'gnustl' in a.lib
    e = Elf(os.path.join(AQUI, 'libs', a.lib))
    img = e.imagem()
    fim_rx = min(l['va'] for l in e.loads if l['va'] > 0)
    relocados = {o for o, t, s in e.rels}

    def constante(addr, larg):
        if addr + larg > fim_rx or any(addr - k in relocados for k in range(4)):
            return None
        return int.from_bytes(img[addr:addr + larg], 'little')

    md = cs.Cs(cs.CS_ARCH_ARM, cs.CS_MODE_THUMB if thumb else cs.CS_MODE_ARM)
    md.detail = True
    g = Gerador(thumb, lambda x: None, lambda x: None, constante, set())

    amostras = json.load(open(os.path.join(AQUI, 'amostras.json')))[a.lib]
    testes = []
    if a.it:
        import pickle, recompilar
        sys.modules['__main__'].Funcao = recompilar.Funcao
        todas, _ = pickle.load(open(os.path.join(AQUI, 'saida', 'analise.pkl'), 'rb'))
        from ins import Ins
        base = recompilar.BASES[a.lib]
        vistos = collections.Counter()
        for f in todas[a.lib].values():
            for ad, ii in f.insns.items():
                if ii.nome != 'it':
                    continue
                n = len(ii.mnemonic) - 1
                bloco = [ii]; k = ad + ii.size
                for _ in range(n):
                    j = f.insns.get(k)
                    if j is None: break
                    bloco.append(j); k += j.size
                if len(bloco) != n + 1 or any(j.nome in CONTROLE or g.termina(j) for j in bloco[1:]):
                    continue
                if any('pc' in j.op_str for j in bloco[1:]):
                    continue
                chave = ' | '.join(j.mnemonic for j in bloco)
                if vistos[chave] >= 3:
                    continue
                vistos[chave] += 1
                testes.append((chave, bloco[0].address - base, bloco))
        print(f'{len(testes)} blocos IT')
    for forma, lista in ([] if a.it else sorted(amostras.items())):
        if a.so and a.so not in forma:
            continue
        for addr, dentro_it in lista:
            if dentro_it:
                continue
            i = next(md.disasm(bytes(img[addr:addr + 4]), addr, 1), None)
            if i is None or i.insn_name() in CONTROLE:
                continue
            ops = ual.parse(i.op_str)
            if g.termina(i):
                continue
            plano = []
            for o in ops:
                plano.extend(o.regs if isinstance(o, ual.Lista) else [o])
            if any(isinstance(o, ual.Reg) and o.tipo == 'r' and o.n == 15 for o in plano[:1]) and i.insn_name() not in ('str', 'strb', 'strh', 'cmp', 'cmn', 'tst', 'teq'):
                continue   # escreve pc
            if any(isinstance(o, ual.Reg) and o.tipo == 'r' and o.n == 15 for o in plano) and i.insn_name() in ('pop', 'ldm', 'ldmib', 'ldmdb', 'ldmda'):
                continue
            testes.append((forma, addr, i))

    # ---- gera e compila
    fonte = [RUNTIME_TESTE]
    for k, (forma, addr, i) in enumerate(testes):
        insns = i if isinstance(i, list) else [i]
        if a.it:
            insns = [Ins(x.address - recompilar.BASES[a.lib], x.size, x.bytes, x.mnemonic, x.op_str, x.cc, x.nome) for x in insns]
            testes[k] = (forma, addr, insns)
        fonte.append(g.funcao(f't_{k}', addr, insns, set(), {}, teste=True))
    fonte.append('__declspec(dllexport) FuncJogo TESTES[] = {' + ','.join(f't_{k}' for k in range(len(testes))) + '};')
    dll = os.path.join(AQUI, 'build', f'dif_{a.lib}.dll')
    os.makedirs(os.path.dirname(dll), exist_ok=True)
    cfile = dll.replace('.dll', '.c')
    open(cfile, 'w').write('\n'.join(fonte))
    r = subprocess.run([CLANG, '-O1', '-shared', '-w', '-ffp-contract=off', '-fno-strict-aliasing',
                        '-I', os.path.join(AQUI, 'runtime'), cfile, '-o', dll], capture_output=True, text=True)
    if r.returncode:
        print(r.stderr[:4000]); sys.exit(1)
    lib = ctypes.CDLL(dll)
    lib.inicia.restype = ctypes.c_void_p
    gm = lib.inicia(JANELA, TAM_JANELA, len(img))
    ctypes.memmove(gm, bytes(img), len(img))
    evento = ctypes.c_int.in_dll(lib, 'g_evento')
    TESTES = (ctypes.CFUNCTYPE(None, ctypes.POINTER(CPU)) * len(testes)).in_dll(lib, 'TESTES')

    uc = Uc(UC_ARCH_ARM, UC_MODE_THUMB if thumb else UC_MODE_ARM)
    uc.reg_write(U.UC_ARM_REG_C1_C0_2, uc.reg_read(U.UC_ARM_REG_C1_C0_2) | (0xf << 20))
    uc.reg_write(U.UC_ARM_REG_FPEXC, 0x40000000)
    uc.mem_map(0, (len(img) + 0xfff) & ~0xfff)
    uc.mem_write(0, bytes(img))
    uc.mem_map(JANELA, TAM_JANELA)

    rnd = random.Random(a.semente)
    resultado = collections.OrderedDict()
    nfalhas = 0
    medidos = 0
    for k, (forma, addr, i) in enumerate(testes):
        ops = [o for x in (i if isinstance(i, list) else [i]) for o in ual.parse(x.op_str)]
        i0 = i[1] if isinstance(i, list) else i
        st = resultado.setdefault(forma, {'ok': 0, 'falha': 0, 'uc_erro': 0, 'nao_sup': 0, 'ex': None})
        for rod in range(a.rodadas):
            regs, flags, vfp, fpnzcv = estado_aleatorio(rnd, i0, ops, thumb)
            memoria = rnd.randbytes(TAM_JANELA)
            # unicorn
            for n in range(13):
                uc.reg_write(U.UC_ARM_REG_R0 + n, regs[n])
            uc.reg_write(U.UC_ARM_REG_SP, regs[13]); uc.reg_write(U.UC_ARM_REG_LR, regs[14])
            cpsr = uc.reg_read(U.UC_ARM_REG_CPSR) & 0x0fffffff
            cpsr |= flags[0] << 31 | flags[1] << 30 | flags[2] << 29 | flags[3] << 28
            uc.reg_write(U.UC_ARM_REG_CPSR, cpsr)
            for d in range(32):
                uc.reg_write(U.UC_ARM_REG_D0 + d, vfp[2 * d] | vfp[2 * d + 1] << 32)
            uc.reg_write(U.UC_ARM_REG_FPSCR, fpnzcv << 28)
            uc.mem_write(JANELA, memoria)
            try:
                if isinstance(i, list):
                    fim = i[-1].address + i[-1].size
                    uc.emu_start(addr | (1 if thumb else 0), fim, count=64)
                else:
                    uc.emu_start(addr | (1 if thumb else 0), 0xffffffff, count=1)
            except UcError as ex:
                st['uc_erro'] += 1
                continue
            # C
            c = CPU()
            for n in range(15):
                c.r[n] = regs[n]
            c.n, c.z, c.c, c.v = flags
            for w in range(64):
                c.vfp[w] = vfp[w]
            c.fpnzcv = fpnzcv
            ctypes.memmove(gm + JANELA, memoria, TAM_JANELA)
            evento.value = 0
            try:
                TESTES[k](ctypes.byref(c))
            except OSError as ex:
                st['falha'] += 1; nfalhas += 1
                st['ex'] = st['ex'] or f'{addr:#x} {forma}: C caiu ({ex})'
                continue
            if evento.value == 3:
                st['nao_sup'] += 1
                continue
            medidos += 1
            dif = []
            for n in range(15):
                u = uc.reg_read(U.UC_ARM_REG_R0 + n if n < 13 else (U.UC_ARM_REG_SP if n == 13 else U.UC_ARM_REG_LR))
                if u != c.r[n]:
                    dif.append(f'r{n} uc={u:#x} c={c.r[n]:#x}')
            cp = uc.reg_read(U.UC_ARM_REG_CPSR)
            fu = [(cp >> 31) & 1, (cp >> 30) & 1, (cp >> 29) & 1, (cp >> 28) & 1]
            if fu != [c.n, c.z, c.c, c.v]:
                dif.append(f'nzcv uc={fu} c={[c.n, c.z, c.c, c.v]}')
            for d in range(32):
                u = uc.reg_read(U.UC_ARM_REG_D0 + d)
                x = c.vfp[2 * d] | c.vfp[2 * d + 1] << 32
                if u != x:
                    lo_ok = (u & 0xffffffff) == (x & 0xffffffff) or (eh_nan32(u & 0xffffffff) and eh_nan32(x & 0xffffffff))
                    hi_ok = (u >> 32) == (x >> 32) or (eh_nan32(u >> 32) and eh_nan32(x >> 32))
                    if not ((lo_ok and hi_ok) or (eh_nan64(u) and eh_nan64(x))):
                        dif.append(f'd{d} uc={u:#018x} c={x:#018x}')
            fps = uc.reg_read(U.UC_ARM_REG_FPSCR) >> 28
            if fps != c.fpnzcv:
                dif.append(f'fpnzcv uc={fps:#x} c={c.fpnzcv:#x}')
            mu = bytes(uc.mem_read(JANELA, TAM_JANELA))
            mc = ctypes.string_at(gm + JANELA, TAM_JANELA)
            if mu != mc:
                p = next(j for j in range(TAM_JANELA) if mu[j] != mc[j])
                dif.append(f'mem +{p:#x} uc={mu[p]:#x} c={mc[p]:#x}')
            if dif:
                st['falha'] += 1; nfalhas += 1
                if st['ex'] is None:
                    st['ex'] = f'{addr:#x} {forma}: ' + '; '.join(dif[:4])
            else:
                st['ok'] += 1

    ruins = {f: s for f, s in resultado.items() if s["falha"] or s["nao_sup"] or (s["ok"] == 0)}
    if os.environ.get("LISTAR"):
        for f, s in resultado.items(): print("  ", f, s["ok"])
    for f, s in ruins.items():
        print(f"{f:44} ok={s['ok']} falha={s['falha']} nao_sup={s['nao_sup']} uc_erro={s['uc_erro']}  {s['ex'] or ''}")
    print(f"\n{a.lib}: {len(testes)} instrucoes em {len(resultado)} formas, {medidos} execucoes comparadas, "
          f"{nfalhas} falhas, {len(resultado) - len(ruins)} formas limpas")


if __name__ == '__main__':
    main()
