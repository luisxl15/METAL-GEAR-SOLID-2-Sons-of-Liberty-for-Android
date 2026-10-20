"""VFP (ponto flutuante escalar) e NEON (vetorial) -> C.

Banco de registradores em c->v, uniao little-endian:
  s[n] = bytes 4n..4n+3,  d[n] = bytes 8n..,  q[n] = bytes 16n..
Os vetores sao tratados elemento a elemento em laços que o clang vetoriza.
Operacoes que leem e escrevem registradores sobrepostos passam por um
temporario (_t) antes de gravar.
"""
from ual import Reg, Imm, FImm, Mem, Lista
from gerar import NaoSuportado, h, RN

TIPOS = {  # nome C do elemento por (sinal, bits)
    ('u', 8): 'uint8_t', ('u', 16): 'uint16_t', ('u', 32): 'uint32_t', ('u', 64): 'uint64_t',
    ('s', 8): 'int8_t', ('s', 16): 'int16_t', ('s', 32): 'int32_t', ('s', 64): 'int64_t',
    ('f', 32): 'float', ('f', 64): 'double',
}
ARR = {  # vetor em c->v por tipo
    'uint8_t': 'u8', 'uint16_t': 'u16', 'uint32_t': 'u32', 'uint64_t': 'u64',
    'int8_t': 's8', 'int16_t': 's16', 'int32_t': 's32', 'int64_t': 's64',
    'float': 'f32', 'double': 'f64',
}


def byte_ini(r):
    return {'s': 4, 'd': 8, 'q': 16}[r.tipo] * r.n


def nbytes(r):
    return {'s': 4, 'd': 8, 'q': 16}[r.tipo]


def tipo_dt(dt, padrao='u'):
    """'f32'->('f',32) 'i16'->('u',16) 's8' 'u64' '32'->('u',32) 'p8'->('u',8)"""
    if dt[0] in 'fsu':
        return (dt[0], int(dt[1:]))
    if dt[0] in 'ip':
        return (padrao, int(dt[1:]))
    return (padrao, int(dt))


def el(r, ct, k):
    """elemento k (do tipo C ct) do registrador r"""
    tam = {'uint8_t': 1, 'int8_t': 1, 'uint16_t': 2, 'int16_t': 2, 'uint32_t': 4, 'int32_t': 4,
           'float': 4, 'uint64_t': 8, 'int64_t': 8, 'double': 8}[ct]
    return f'c->v.{ARR[ct]}[{byte_ini(r) // tam} + {k}]'


def S(n): return f'c->v.f32[{n}]'
def SU(n): return f'c->v.u32[{n}]'
def D(n): return f'c->v.f64[{n}]'
def DU(n): return f'c->v.u64[{n}]'


def fval(r):
    """valor escalar de ponto flutuante de s/d"""
    return S(r.n) if r.tipo == 's' else D(r.n)


class VFP:
    tabela = {}


def reg(nome):
    def deco(f):
        for n in nome.split():
            VFP.tabela[n] = f
        return f
    return deco


def escalar(ops):
    return all(isinstance(o, Reg) and o.tipo in 'sd' and o.lane is None for o in ops if isinstance(o, Reg))


def eh_neon(ops, dts):
    """vetor: registrador q, ou d com tipo que nao seja f64, ou pista"""
    for o in ops:
        if isinstance(o, Reg):
            if o.tipo == 'q' or o.lane is not None:
                return True
            if o.tipo == 'd' and dts and dts[-1] not in ('f64',):
                return True
    return False


# ------------------------------------------------------------- memoria VFP
def _ea(g, i, mm):
    ea, novo = g.endereco(mm, i)
    return ea, novo


@reg('vldr')
def vldr(g, i, ops, dts, rot):
    r, mm = ops[0], ops[1]
    if mm.base.n == 15:
        addr = ((g.pc(i) & ~3)) + (mm.off.v if mm.off else 0)
        if r.tipo == 's':
            k = g.constante(addr, 4)
            if k is not None:
                return [f'{SU(r.n)} = {h(k)};']
        else:
            a, b = g.constante(addr, 4), g.constante(addr + 4, 4)
            if a is not None and b is not None:
                return [f'{DU(r.n)} = 0x{(b << 32) | a:016x}ull;']
    ea, _ = _ea(g, i, mm)
    if r.tipo == 's':
        return [f'{SU(r.n)} = L32({ea});']
    return [f'{DU(r.n)} = L64({ea});']


@reg('vstr')
def vstr(g, i, ops, dts, rot):
    r, mm = ops[0], ops[1]
    ea, _ = _ea(g, i, mm)
    if r.tipo == 's':
        return [f'S32({ea}, {SU(r.n)});']
    return [f'S64({ea}, {DU(r.n)});']


def _lista(ops):
    out = []
    for o in ops:
        if isinstance(o, Lista):
            out.extend(o.regs)
    return out


def _vldm(g, i, ops, carga, modo, base=None):
    if base is None:
        base = ops[0]
        wb = base.wb
    else:
        wb = True
    regs = _lista(ops)
    tam = sum(nbytes(r) for r in regs)
    b = RN[base.n]
    ini = '0' if modo == 'ia' else f'-{tam}'
    linhas = [f'{{ uint32_t _ea = {b} + (uint32_t)({ini});']
    off = 0
    for r in regs:
        if r.tipo == 's':
            linhas.append(f'{SU(r.n)} = L32(_ea + {off});' if carga else f'S32(_ea + {off}, {SU(r.n)});')
        else:
            linhas.append(f'{DU(r.n)} = L64(_ea + {off});' if carga else f'S64(_ea + {off}, {DU(r.n)});')
        off += nbytes(r)
    if wb:
        linhas.append(f'{b} = {b} + (uint32_t)({"+" if modo == "ia" else "-"}{tam});')
    return [' '.join(linhas) + ' }']


reg('vldmia')(lambda g, i, ops, dts, rot: _vldm(g, i, ops, True, 'ia'))
reg('vstmia')(lambda g, i, ops, dts, rot: _vldm(g, i, ops, False, 'ia'))
reg('vldmdb')(lambda g, i, ops, dts, rot: _vldm(g, i, ops, True, 'db'))
reg('vstmdb')(lambda g, i, ops, dts, rot: _vldm(g, i, ops, False, 'db'))
reg('vpush')(lambda g, i, ops, dts, rot: _vldm(g, i, ops, False, 'db', base=Reg('sp')))
reg('vpop')(lambda g, i, ops, dts, rot: _vldm(g, i, ops, True, 'ia', base=Reg('sp')))


# ------------------------------------------------------------- vmov
def _imm_neon(v, dts):
    """imediato de vmov/vorr/vmvn/vbic NEON -> padrao de 64 bits"""
    dt = dts[-1] if dts else 'i32'
    t, b = tipo_dt(dt)
    if t == 'f':
        import struct
        v = struct.unpack('<I', struct.pack('<f', v))[0]
        b = 32
    v &= (1 << b) - 1
    rep = 64 // b
    x = 0
    for k in range(rep):
        x |= v << (b * k)
    return x


@reg('vmov')
def vmov(g, i, ops, dts, rot):
    a = ops[0]
    # core <- s / s <- core
    if len(ops) == 2 and isinstance(a, Reg) and isinstance(ops[1], Reg):
        b = ops[1]
        if a.tipo == 'r' and b.tipo == 's':
            return [f'{RN[a.n]} = {SU(b.n)};']
        if a.tipo == 's' and b.tipo == 'r':
            return [f'{SU(a.n)} = {g.reg(b, i)};']
        if a.tipo == 's' and b.tipo == 's':
            return [f'{SU(a.n)} = {SU(b.n)};']
        if a.tipo in 'dq' and b.tipo == a.tipo and a.lane is None and b.lane is None:
            if a.tipo == 'd':
                return [f'{DU(a.n)} = {DU(b.n)};']
            return [f'{{ uint64_t _x = {DU(2 * b.n)}, _y = {DU(2 * b.n + 1)}; {DU(2 * a.n)} = _x; {DU(2 * a.n + 1)} = _y; }}']
        # escalar NEON: vmov.32 r0, d1[1]  /  vmov.u8 r0, d0[3]  /  vmov.32 d0[1], r0
        dt = dts[-1] if dts else '32'
        if a.tipo == 'r' and b.lane is not None:
            t, bits = tipo_dt(dt)
            ct = TIPOS[('s' if t == 's' else 'u', bits)]
            return [f'{RN[a.n]} = (uint32_t)({ "(int32_t)" if t == "s" else ""}{el(b, ct, b.lane)});']
        if a.lane is not None and b.tipo == 'r':
            t, bits = tipo_dt(dt)
            ct = TIPOS[('u', bits)]
            return [f'{el(a, ct, a.lane)} = ({ct}){g.reg(b, i)};']
    # dN <- r, r   /   r, r <- dN
    if len(ops) == 3:
        if ops[0].tipo == 'd':
            return [f'{DU(ops[0].n)} = ((uint64_t){g.reg(ops[2], i)} << 32) | {g.reg(ops[1], i)};']
        if ops[2].tipo == 'd':
            return [f'{{ uint64_t _x = {DU(ops[2].n)}; {RN[ops[0].n]} = (uint32_t)_x; {RN[ops[1].n]} = (uint32_t)(_x >> 32); }}']
    if len(ops) == 4:
        if ops[0].tipo == 's':   # vmov s0, s1, r0, r1
            return [f'{SU(ops[0].n)} = {g.reg(ops[2], i)}; {SU(ops[1].n)} = {g.reg(ops[3], i)};']
        return [f'{{ uint32_t _a = {SU(ops[2].n)}, _b = {SU(ops[3].n)}; {RN[ops[0].n]} = _a; {RN[ops[1].n]} = _b; }}']
    # imediatos
    if len(ops) == 2 and isinstance(ops[1], (FImm, Imm)):
        v = ops[1].v
        if a.tipo == 's':
            import struct
            return [f'{SU(a.n)} = {h(struct.unpack("<I", struct.pack("<f", float(v)))[0])};']
        if a.tipo == 'd' and dts and dts[-1] == 'f64':
            import struct
            return [f'{DU(a.n)} = 0x{struct.unpack("<Q", struct.pack("<d", float(v)))[0]:016x}ull;']
        x = _imm_neon(v, dts)
        if dts and dts[-1] == 'i64':
            x = v & 0xffffffffffffffff
        return [f'{DU(k)} = 0x{x:016x}ull;' for k in _dregs(a)]
    raise NaoSuportado('vmov ' + repr(ops))


def _dregs(r):
    return [r.n] if r.tipo == 'd' else [2 * r.n, 2 * r.n + 1]


@reg('vmvn')
def vmvn(g, i, ops, dts, rot):
    a, b = ops
    if isinstance(b, Imm):
        x = _imm_neon(b.v, dts) ^ 0xffffffffffffffff
        return [f'{DU(k)} = 0x{x:016x}ull;' for k in _dregs(a)]
    return [f'{DU(x)} = ~{DU(y)};' for x, y in zip(_dregs(a), _dregs(b))]


# ------------------------------------------------------------- aritmetica escalar
def _bin_escalar(op):
    def f(g, i, ops, dts, rot):
        if eh_neon(ops, dts):
            return neon_bin(g, i, ops, dts, op)
        d = ops[0]
        a, b = (ops[0], ops[1]) if len(ops) == 2 else (ops[1], ops[2])
        return [f'{fval(d)} = {fval(a)} {op} {fval(b)};']
    return f


reg('vadd')(_bin_escalar('+'))
reg('vsub')(_bin_escalar('-'))
reg('vmul')(_bin_escalar('*'))
reg('vdiv')(_bin_escalar('/'))


def _mac(sinal_prod, neg_acc):
    def f(g, i, ops, dts, rot):
        if eh_neon(ops, dts):
            return neon_mac(g, i, ops, dts, sinal_prod)
        d, a, b = ops
        tp = 'float' if d.tipo == 's' else 'double'
        acc = f'-{fval(d)}' if neg_acc else fval(d)
        # VFP: produto arredondado antes da soma (nao fundido). -ffp-contract=off ja
        # garante isso; o volatile antigo so forcava ida e volta na pilha
        return [f'{{ {tp} _p = {fval(a)} * {fval(b)}; {fval(d)} = {acc} {sinal_prod} _p; }}']
    return f


reg('vmla')(_mac('+', False))
reg('vmls')(_mac('-', False))
reg('vnmla')(_mac('-', True))
reg('vnmls')(_mac('+', True))


@reg('vnmul')
def vnmul(g, i, ops, dts, rot):
    d, a, b = ops
    return [f'{fval(d)} = -({fval(a)} * {fval(b)});']


def _un_escalar(cf, ci):
    def f(g, i, ops, dts, rot):
        if eh_neon(ops, dts):
            return neon_un(g, i, ops, dts, cf, ci)
        d, a = ops
        if d.tipo == 's':
            return [f'{S(d.n)} = {cf.replace("X", S(a.n)).replace("sqrt(", "sqrtf(").replace("fabs(", "fabsf(")};']
        return [f'{D(d.n)} = {cf.replace("X", D(a.n))};']
    return f


reg('vneg')(_un_escalar('-(X)', '-X'))
reg('vabs')(_un_escalar('fabs(X)', 'ABS'))
reg('vsqrt')(_un_escalar('sqrt(X)', None))


def _vcmp(g, i, ops, dts, rot):
    a, b = ops
    bv = '0.0' if isinstance(b, (Imm, FImm)) else fval(b)
    return [f'c->fpnzcv = FCMP({fval(a)}, {bv});']


reg('vcmp')(_vcmp)
reg('vcmpe')(_vcmp)


@reg('vmrs')
def vmrs(g, i, ops, dts, rot):
    d = ops[0]
    if d.nome == 'apsr_nzcv':
        return ['fn = c->fpnzcv >> 3 & 1; fz = c->fpnzcv >> 2 & 1; fc = c->fpnzcv >> 1 & 1; fv = c->fpnzcv & 1;']
    return [f'{RN[d.n]} = (c->fpscr & 0x0fffffffu) | (c->fpnzcv << 28);']


@reg('vmsr')
def vmsr(g, i, ops, dts, rot):
    v = g.reg(ops[1], i)
    return [f'c->fpscr = {v}; c->fpnzcv = {v} >> 28;']


@reg('vcvt')
def vcvt(g, i, ops, dts, rot):
    para, de = dts[0], dts[1]
    regs = [o for o in ops if isinstance(o, Reg)]
    neon = any(r.tipo == 'q' for r in regs) or (all(r.tipo == 'd' for r in regs) and 'f64' not in dts)
    if neon:
        return neon_cvt(g, i, ops, para, de)
    d, a = ops[0], ops[1]
    if len(ops) == 3:
        # ponto fixo: o operando e o proprio registrador (s, ou metade baixa de d)
        fb = ops[2].v
        if para in ('f32', 'f64'):
            src = SU(d.n) if d.tipo == 's' else f'(uint32_t){DU(d.n)}'
            ival = {'s32': f'(double)(int32_t){src}', 'u32': f'(double)(uint32_t){src}',
                    's16': f'(double)(int16_t){src}', 'u16': f'(double)(uint16_t){src}'}[de]
            e = f'({ival} / {float(1 << fb)!r})'
            if para == 'f32':
                return [f'{S(d.n)} = (float){e};']
            return [f'{D(d.n)} = {e};']
        val = f'((double){fval(d)} * {float(1 << fb)!r})'
        conv = {'s32': f'(uint32_t)CVT_S32({val})', 'u32': f'CVT_U32({val})',
                's16': f'(uint32_t)(int32_t)CVT_S16({val})', 'u16': f'CVT_U16({val})'}[para]
        if d.tipo == 's':
            return [f'{SU(d.n)} = {conv};']
        return [f'{DU(d.n)} = (uint64_t)(uint32_t){conv} | ({DU(d.n)} & 0xffffffff00000000ull);']
    fonte = {'f32': S(a.n), 'f64': D(a.n), 's32': f'(int32_t){SU(a.n)}', 'u32': SU(a.n)}[de]
    if para == 'f32':
        return [f'{S(d.n)} = (float)({fonte});']
    if para == 'f64':
        return [f'{D(d.n)} = (double)({fonte});']
    if para == 's32':
        return [f'{SU(d.n)} = (uint32_t)CVT_S32({fonte});']
    if para == 'u32':
        return [f'{SU(d.n)} = CVT_U32({fonte});']
    raise NaoSuportado('vcvt ' + '.'.join(dts))


@reg('vcvtr')
def vcvtr(g, i, ops, dts, rot):
    # arredonda pelo modo do FPSCR (o jogo nunca muda: mais proximo)
    para, de = dts[0], dts[1]
    d, a = ops
    fonte = S(a.n) if de == 'f32' else D(a.n)
    return [f'{SU(d.n)} = {"(uint32_t)CVT_S32" if para == "s32" else "CVT_U32"}(RINT({fonte}));']


# ------------------------------------------------------------- NEON
def _elementos(r, bits):
    return nbytes(r) * 8 // bits


def neon_bin(g, i, ops, dts, op):
    d = ops[0]
    a, b = (ops[0], ops[1]) if len(ops) == 2 else (ops[1], ops[2])
    t, bits = tipo_dt(dts[-1])
    ct = TIPOS[(t, bits)]
    n = _elementos(d, bits)
    if isinstance(b, Reg) and b.lane is not None:
        bexp = el(b, ct, b.lane)
        if t == 'f':
            return [f'{{ {ct} _s = FTZ({bexp}); for (int _k = 0; _k < {n}; _k++) {el(d, ct, "_k")} = FTZ(FTZ({el(a, ct, "_k")}) {op} _s); }}']
        return [f'{{ {ct} _s = {bexp}; for (int _k = 0; _k < {n}; _k++) {el(d, ct, "_k")} = ({ct})({el(a, ct, "_k")} {op} _s); }}']
    if t == 'f':
        return [f'for (int _k = 0; _k < {n}; _k++) {el(d, ct, "_k")} = FTZ(FTZ({el(a, ct, "_k")}) {op} FTZ({el(b, ct, "_k")}));']
    return [f'for (int _k = 0; _k < {n}; _k++) {el(d, ct, "_k")} = ({ct})({el(a, ct, "_k")} {op} {el(b, ct, "_k")});']


def neon_mac(g, i, ops, dts, sinal):
    d, a, b = ops
    t, bits = tipo_dt(dts[-1])
    ct = TIPOS[(t, bits)]
    n = _elementos(d, bits)
    bexp = el(b, ct, b.lane) if b.lane is not None else el(b, ct, '_k')
    if t == 'f':
        return [f'{{ {ct} _t[{n}]; for (int _k = 0; _k < {n}; _k++) {{ float _p = FTZ(FTZ({el(a, ct, "_k")}) * FTZ({bexp})); _t[_k] = FTZ(FTZ({el(d, ct, "_k")}) {sinal} _p); }} '
                f'for (int _k = 0; _k < {n}; _k++) {el(d, ct, "_k")} = _t[_k]; }}']
    return [f'{{ {ct} _t[{n}]; for (int _k = 0; _k < {n}; _k++) _t[_k] = ({ct})({el(d, ct, "_k")} {sinal} {el(a, ct, "_k")} * {bexp}); '
            f'for (int _k = 0; _k < {n}; _k++) {el(d, ct, "_k")} = _t[_k]; }}']


def neon_un(g, i, ops, dts, cf, ci):
    d, a = ops
    t, bits = tipo_dt(dts[-1], 's')
    ct = TIPOS[(t, bits)]
    n = _elementos(d, bits)
    if t == 'f':
        e = cf.replace('X', el(a, ct, '_k')).replace('fabs(', 'fabsf(')
    elif ci == 'ABS':
        x = el(a, ct, '_k')
        e = f'({ct})({x} < 0 ? -{x} : {x})'
    else:
        e = f'({ct})(-{el(a, ct, "_k")})'
    return [f'for (int _k = 0; _k < {n}; _k++) {el(d, ct, "_k")} = {e};']


def neon_cvt(g, i, ops, para, de):
    d, a = ops[0], ops[1]
    if len(ops) == 3:
        raise NaoSuportado('vcvt neon ponto fixo')
    n = _elementos(d, 32)
    src = {'f32': el(a, 'float', '_k'), 's32': el(a, 'int32_t', '_k'), 'u32': el(a, 'uint32_t', '_k')}[de]
    if para == 'f32':
        return [f'for (int _k = 0; _k < {n}; _k++) {el(d, "float", "_k")} = (float)({src});']
    if para == 's32':
        return [f'for (int _k = 0; _k < {n}; _k++) {el(d, "int32_t", "_k")} = CVT_S32(FTZ({src}));']
    if para == 'u32':
        return [f'for (int _k = 0; _k < {n}; _k++) {el(d, "uint32_t", "_k")} = CVT_U32(FTZ({src}));']
    raise NaoSuportado('vcvt neon')


def _bitwise(expr):
    def f(g, i, ops, dts, rot):
        d = ops[0]
        if len(ops) == 2 and isinstance(ops[1], Imm):   # vorr.i32 q8, #imm / vbic.i16
            x = _imm_neon(ops[1].v, dts)
            e = expr.replace('A', 'D').replace('B', f'0x{x:016x}ull')
            return [f'{DU(k)} = {e.replace("D", DU(k))};' for k in _dregs(d)]
        a, b = (ops[1], ops[2]) if len(ops) == 3 else (ops[0], ops[1])
        linhas = []
        for kd, ka, kb in zip(_dregs(d), _dregs(a), _dregs(b)):
            linhas.append(f'{{ uint64_t _d = {DU(kd)}, _a = {DU(ka)}, _b = {DU(kb)}; {DU(kd)} = {expr.replace("D", "_d").replace("A", "_a").replace("B", "_b")}; }}')
        return linhas
    return f


reg('vorr')(_bitwise('(A | B)'))
reg('vorn')(_bitwise('(A | ~B)'))
reg('vand')(_bitwise('(A & B)'))
reg('veor')(_bitwise('(A ^ B)'))
reg('vbic')(_bitwise('(A & ~B)'))
reg('vbsl')(_bitwise('((A & D) | (B & ~D))'))
reg('vbit')(_bitwise('((D & ~B) | (A & B))'))
reg('vbif')(_bitwise('((D & B) | (A & ~B))'))


def _cmp(op, padrao='s'):
    def f(g, i, ops, dts, rot):
        d, a = ops[0], ops[1]
        b = ops[2] if len(ops) > 2 else None
        t, bits = tipo_dt(dts[-1], padrao)
        ct = TIPOS[(t, bits)]
        mt = TIPOS[('u', bits)]
        n = _elementos(d, bits)
        bexp = '0' if b is None or isinstance(b, (Imm, FImm)) else el(b, ct, '_k')
        aexp = el(a, ct, '_k')
        if t == 'f':
            aexp, bexp = f'FTZ({aexp})', f'FTZ({bexp})'
        return [f'{{ {mt} _t[{n}]; for (int _k = 0; _k < {n}; _k++) _t[_k] = ({aexp} {op} {bexp}) ? ({mt})~0ull : 0; '
                f'for (int _k = 0; _k < {n}; _k++) {el(d, mt, "_k")} = _t[_k]; }}']
    return f


reg('vceq')(_cmp('==', 'u'))
reg('vcge')(_cmp('>='))
reg('vcgt')(_cmp('>'))
reg('vcle')(_cmp('<='))
reg('vclt')(_cmp('<'))


def _minmax(op):
    def f(g, i, ops, dts, rot):
        d, a, b = ops
        t, bits = tipo_dt(dts[-1], 's')
        ct = TIPOS[(t, bits)]
        n = _elementos(d, bits)
        if t == 'f':
            fn = 'FMIN_NEON' if op == '<' else 'FMAX_NEON'
            return [f'for (int _k = 0; _k < {n}; _k++) {el(d, ct, "_k")} = {fn}({el(a, ct, "_k")}, {el(b, ct, "_k")});']
        return [f'for (int _k = 0; _k < {n}; _k++) {{ {ct} _x = {el(a, ct, "_k")}, _y = {el(b, ct, "_k")}; {el(d, ct, "_k")} = _x {op} _y ? _x : _y; }}']
    return f


reg('vmin')(_minmax('<'))
reg('vmax')(_minmax('>'))


def _pares(op):
    def f(g, i, ops, dts, rot):
        d, a, b = ops
        t, bits = tipo_dt(dts[-1], 's')
        ct = TIPOS[(t, bits)]
        n = _elementos(d, bits)
        h2 = n // 2
        if op == '+' and t == 'f':
            e = lambda x, y: f'FTZ(FTZ({x}) + FTZ({y}))'
        elif op == '+':
            e = lambda x, y: f'({ct})({x} + {y})'
        elif op == 'min':
            e = (lambda x, y: f'FMIN_NEON({x}, {y})') if t == 'f' else (lambda x, y: f'({x} < {y} ? {x} : {y})')
        else:
            e = (lambda x, y: f'FMAX_NEON({x}, {y})') if t == 'f' else (lambda x, y: f'({x} > {y} ? {x} : {y})')
        partes = [f'{{ {ct} _t[{n}];']
        for k in range(h2):
            partes.append(f'_t[{k}] = {e(el(a, ct, 2 * k), el(a, ct, 2 * k + 1))};')
            partes.append(f'_t[{h2 + k}] = {e(el(b, ct, 2 * k), el(b, ct, 2 * k + 1))};')
        partes.append(f'for (int _k = 0; _k < {n}; _k++) {el(d, ct, "_k")} = _t[_k]; }}')
        return [' '.join(partes)]
    return f


reg('vpadd')(_pares('+'))
reg('vpmin')(_pares('min'))
reg('vpmax')(_pares('max'))


@reg('vdup')
def vdup(g, i, ops, dts, rot):
    d, s = ops
    bits = int(dts[-1])
    ct = TIPOS[('u', bits)]
    n = _elementos(d, bits)
    v = f'({ct}){g.reg(s, i)}' if s.tipo == 'r' else el(s, ct, s.lane)
    return [f'{{ {ct} _s = {v}; for (int _k = 0; _k < {n}; _k++) {el(d, ct, "_k")} = _s; }}']


@reg('vmovl')
def vmovl(g, i, ops, dts, rot):
    d, a = ops
    t, bits = tipo_dt(dts[-1])
    ci, co = TIPOS[(t, bits)], TIPOS[(t, bits * 2)]
    n = _elementos(a, bits)
    return [f'{{ {co} _t[{n}]; for (int _k = 0; _k < {n}; _k++) _t[_k] = ({co}){el(a, ci, "_k")}; '
            f'for (int _k = 0; _k < {n}; _k++) {el(d, co, "_k")} = _t[_k]; }}']


@reg('vshll')
def vshll(g, i, ops, dts, rot):
    d, a, sh = ops
    t, bits = tipo_dt(dts[-1])
    ci, co = TIPOS[(t, bits)], TIPOS[(t, bits * 2)]
    n = _elementos(a, bits)
    return [f'{{ {co} _t[{n}]; for (int _k = 0; _k < {n}; _k++) _t[_k] = ({co})(({co}){el(a, ci, "_k")} << {sh.v}); '
            f'for (int _k = 0; _k < {n}; _k++) {el(d, co, "_k")} = _t[_k]; }}']


@reg('vmovn')
def vmovn(g, i, ops, dts, rot):
    d, a = ops
    t, bits = tipo_dt(dts[-1])     # i32 -> 16 bits
    ci, co = TIPOS[('u', bits)], TIPOS[('u', bits // 2)]
    n = _elementos(d, bits // 2)
    return [f'{{ {co} _t[{n}]; for (int _k = 0; _k < {n}; _k++) _t[_k] = ({co}){el(a, ci, "_k")}; '
            f'for (int _k = 0; _k < {n}; _k++) {el(d, co, "_k")} = _t[_k]; }}']


def _qmovn(sem_sinal_saida):
    def f(g, i, ops, dts, rot):
        d, a = ops
        t, bits = tipo_dt(dts[-1])     # s32 / u32 / s16...
        ci = TIPOS[(t, bits)]
        tout = 'u' if (sem_sinal_saida or t == 'u') else 's'
        co = TIPOS[(tout, bits // 2)]
        lo = 0 if tout == 'u' else -(1 << (bits // 2 - 1))
        hi = (1 << (bits // 2)) - 1 if tout == 'u' else (1 << (bits // 2 - 1)) - 1
        n = _elementos(d, bits // 2)
        return [f'{{ {co} _t[{n}]; for (int _k = 0; _k < {n}; _k++) {{ {ci} _x = {el(a, ci, "_k")}; '
                f'_t[_k] = ({co})(_x < {lo} ? {lo} : (_x > {hi} ? {hi} : _x)); }} '
                f'for (int _k = 0; _k < {n}; _k++) {el(d, co, "_k")} = _t[_k]; }}']
    return f


reg('vqmovn')(_qmovn(False))
reg('vqmovun')(_qmovn(True))


def _vsh(dir_):
    def f(g, i, ops, dts, rot):
        d = ops[0]
        a, b = (ops[1], ops[2]) if len(ops) == 3 else (ops[0], ops[1])
        t, bits = tipo_dt(dts[-1])
        ct = TIPOS[(t, bits)]
        n = _elementos(d, bits)
        if isinstance(b, Imm):
            s = b.v
            if dir_ == '>>' and s == bits:
                e = f'({ct})({el(a, ct, "_k")} >> {bits - 1} >> 1)' if t == 's' else '0'
            else:
                e = f'({ct})({el(a, ct, "_k")} {dir_} {s})'
            return [f'for (int _k = 0; _k < {n}; _k++) {el(d, ct, "_k")} = {e};']
        # vshl por registrador: deslocamento com sinal no byte baixo de cada elemento
        st = TIPOS[('s', bits)]
        return [f'{{ {ct} _t[{n}]; for (int _k = 0; _k < {n}; _k++) _t[_k] = ({ct})VSHL_{t.upper()}{bits}({el(a, ct, "_k")}, (int8_t){el(b, st, "_k")}); '
                f'for (int _k = 0; _k < {n}; _k++) {el(d, ct, "_k")} = _t[_k]; }}']
    return f


reg('vshl')(_vsh('<<'))
reg('vshr')(_vsh('>>'))


@reg('vmull')
def vmull(g, i, ops, dts, rot):
    d, a, b = ops
    t, bits = tipo_dt(dts[-1])
    if t == 'p' or dts[-1].startswith('p'):
        raise NaoSuportado('vmull.p8')
    ci, co = TIPOS[(t, bits)], TIPOS[(t, bits * 2)]
    n = _elementos(a, bits)
    bexp = el(b, ci, b.lane) if b.lane is not None else el(b, ci, '_k')
    return [f'{{ {co} _t[{n}]; for (int _k = 0; _k < {n}; _k++) _t[_k] = ({co}){el(a, ci, "_k")} * ({co}){bexp}; '
            f'for (int _k = 0; _k < {n}; _k++) {el(d, co, "_k")} = _t[_k]; }}']


@reg('vext')
def vext(g, i, ops, dts, rot):
    d, a, b, k = ops
    nb = nbytes(d)
    bits = int(dts[-1]) if dts else 8
    off = k.v * bits // 8
    return [f'{{ uint8_t _t[{2 * nb}]; memcpy(_t, &c->v.u8[{byte_ini(a)}], {nb}); memcpy(_t + {nb}, &c->v.u8[{byte_ini(b)}], {nb}); '
            f'memcpy(&c->v.u8[{byte_ini(d)}], _t + {off}, {nb}); }}']


@reg('vtbl')
def vtbl(g, i, ops, dts, rot):
    d, lst, m = ops
    nt = 8 * len(lst.regs)
    partes = [f'{{ uint8_t _tab[{nt}], _r[8];']
    for k, r in enumerate(lst.regs):
        partes.append(f'memcpy(_tab + {8 * k}, &c->v.u8[{byte_ini(r)}], 8);')
    partes.append(f'for (int _k = 0; _k < 8; _k++) {{ uint8_t _x = c->v.u8[{byte_ini(m)} + _k]; _r[_k] = _x < {nt} ? _tab[_x] : 0; }}')
    partes.append(f'memcpy(&c->v.u8[{byte_ini(d)}], _r, 8); }}')
    return [' '.join(partes)]


def _zip_uzp(tipo):
    def f(g, i, ops, dts, rot):
        a, b = ops
        bits = int(dts[-1])
        ct = TIPOS[('u', bits)]
        n = _elementos(a, bits)
        partes = [f'{{ {ct} _x[{2 * n}], _o[{2 * n}];']
        partes.append(f'for (int _k = 0; _k < {n}; _k++) {{ _x[_k] = {el(a, ct, "_k")}; _x[{n} + _k] = {el(b, ct, "_k")}; }}')
        if tipo == 'uzp':   # pares em a, impares em b
            partes.append(f'for (int _k = 0; _k < {n}; _k++) {{ _o[_k] = _x[2 * _k]; _o[{n} + _k] = _x[2 * _k + 1]; }}')
        else:               # intercala
            partes.append(f'for (int _k = 0; _k < {n}; _k++) {{ _o[2 * _k] = _x[_k]; _o[2 * _k + 1] = _x[{n} + _k]; }}')
        partes.append(f'for (int _k = 0; _k < {n}; _k++) {{ {el(a, ct, "_k")} = _o[_k]; {el(b, ct, "_k")} = _o[{n} + _k]; }} }}')
        return [' '.join(partes)]
    return f


reg('vuzp')(_zip_uzp('uzp'))
reg('vzip')(_zip_uzp('zip'))


@reg('vtrn')
def vtrn(g, i, ops, dts, rot):
    a, b = ops
    bits = int(dts[-1])
    ct = TIPOS[('u', bits)]
    n = _elementos(a, bits)
    return [f'for (int _k = 0; _k < {n}; _k += 2) {{ {ct} _t = {el(a, ct, "_k + 1")}; {el(a, ct, "_k + 1")} = {el(b, ct, "_k")}; {el(b, ct, "_k")} = _t; }}']


@reg('vrev64 vrev32 vrev16')
def vrev(g, i, ops, dts, rot):
    raise NaoSuportado('vrev')


@reg('vrecpe')
def vrecpe(g, i, ops, dts, rot):
    d, a = ops
    n = _elementos(d, 32)
    return [f'for (int _k = 0; _k < {n}; _k++) {el(d, "float", "_k")} = RECPE({el(a, "float", "_k")});']


@reg('vrecps')
def vrecps(g, i, ops, dts, rot):
    d, a, b = ops
    n = _elementos(d, 32)
    return [f'for (int _k = 0; _k < {n}; _k++) {el(d, "float", "_k")} = RECPS({el(a, "float", "_k")}, {el(b, "float", "_k")});']


@reg('vrsqrte')
def vrsqrte(g, i, ops, dts, rot):
    d, a = ops
    n = _elementos(d, 32)
    return [f'for (int _k = 0; _k < {n}; _k++) {el(d, "float", "_k")} = RSQRTE({el(a, "float", "_k")});']


@reg('vrsqrts')
def vrsqrts(g, i, ops, dts, rot):
    d, a, b = ops
    n = _elementos(d, 32)
    return [f'for (int _k = 0; _k < {n}; _k++) {el(d, "float", "_k")} = RSQRTS({el(a, "float", "_k")}, {el(b, "float", "_k")});']


# ------------------------------------------------------------- vld/vst NEON
def _vldst(g, i, ops, dts, carga, n_intercala):
    lst, mm = ops[0], ops[1]
    bits = int(tipo_dt(dts[-1])[1])
    ct = TIPOS[('u', bits)]
    eb = bits // 8
    regs = lst.regs
    b = RN[mm.base.n]
    partes = [f'{{ uint32_t _ea = {b};']
    total = 0
    if lst.lane is None:
        # multiplos elementos: vld1 = copia direta; vldN = desintercala
        if n_intercala == 1:
            for k, r in enumerate(regs):
                if carga:
                    partes.append(f'{DU(r.n)} = L64(_ea + {8 * k});')
                else:
                    partes.append(f'S64(_ea + {8 * k}, {DU(r.n)});')
            total = 8 * len(regs)
        else:
            ne = 8 // eb                   # elementos por registrador d
            grupos = len(regs) // n_intercala
            for gr in range(grupos):
                rs = regs[gr * n_intercala:(gr + 1) * n_intercala] if grupos == 1 else regs[gr::grupos]
                baseoff = gr * 8 * n_intercala
                for j in range(ne):
                    for r_i, r in enumerate(rs):
                        off = baseoff + (j * n_intercala + r_i) * eb
                        e = el(r, ct, j)
                        if carga:
                            partes.append(f'{e} = ({ct})L{bits}(_ea + {off});')
                        else:
                            partes.append(f'S{bits}(_ea + {off}, {e});')
            total = 8 * len(regs)
    elif lst.lane == 'all':
        # replica um elemento (ou N) em todas as pistas
        ne = 8 // eb
        for r_i, r in enumerate(regs if n_intercala > 1 else regs[:1]):
            partes.append(f'{{ {ct} _s = ({ct})L{bits}(_ea + {r_i * eb}); for (int _k = 0; _k < {ne}; _k++) {el(r, ct, "_k")} = _s; }}')
        if n_intercala == 1:
            for r in regs[1:]:
                partes.append(f'{DU(r.n)} = {DU(regs[0].n)};')
            total = eb
        else:
            total = eb * len(regs)
    else:
        for r_i, r in enumerate(regs):
            e = el(r, ct, lst.lane)
            if carga:
                partes.append(f'{e} = ({ct})L{bits}(_ea + {r_i * eb});')
            else:
                partes.append(f'S{bits}(_ea + {r_i * eb}, {e});')
        total = eb * len(regs)
    if mm.pre_wb or mm.base.wb:
        partes.append(f'{b} = _ea + {total};')
    elif mm.post is not None:
        partes.append(f'{b} = _ea + {g.reg(mm.post, i)};')
    partes.append('}')
    return [' '.join(partes)]


for _n in (1, 2, 3, 4):
    reg(f'vld{_n}')((lambda n: lambda g, i, ops, dts, rot: _vldst(g, i, ops, dts, True, n))(_n))
    reg(f'vst{_n}')((lambda n: lambda g, i, ops, dts, rot: _vldst(g, i, ops, dts, False, n))(_n))


@reg('vaddl vsubl')
def vaddl(g, i, ops, dts, rot):
    d, a, b = ops
    t, bits = tipo_dt(dts[-1])
    ci, co = TIPOS[(t, bits)], TIPOS[(t, bits * 2)]
    n = _elementos(a, bits)
    op = '+' if i.insn_name() == 'vaddl' else '-'
    return [f'{{ {co} _t[{n}]; for (int _k = 0; _k < {n}; _k++) _t[_k] = ({co})(({co}){el(a, ci, "_k")} {op} ({co}){el(b, ci, "_k")}); '
            f'for (int _k = 0; _k < {n}; _k++) {el(d, co, "_k")} = _t[_k]; }}']


@reg('vhadd')
def vhadd(g, i, ops, dts, rot):
    d, a, b = ops
    t, bits = tipo_dt(dts[-1])
    ct = TIPOS[(t, bits)]
    n = _elementos(d, bits)
    return [f'for (int _k = 0; _k < {n}; _k++) {el(d, ct, "_k")} = ({ct})(((int64_t){el(a, ct, "_k")} + (int64_t){el(b, ct, "_k")}) >> 1);']
