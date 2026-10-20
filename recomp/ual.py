"""Parser do texto UAL que o capstone imprime (op_str).

O texto e confiavel; a estrutura de detalhes do capstone nao e (perde o sinal e
o deslocamento do indice em [r1, -r2, lsl #2], as pistas d1[1], mistura
pos-indice). Tudo que o gerador precisa sai daqui.
"""
import re

REG_CORE = {f'r{i}': i for i in range(13)}
REG_CORE.update(sp=13, lr=14, pc=15, sb=9, sl=10, fp=11, ip=12)


class Reg:
    __slots__ = ('nome', 'tipo', 'n', 'lane', 'neg', 'shift', 'wb')

    def __init__(self, nome, lane=None, neg=False):
        self.wb = nome.endswith('!')
        nome = nome.rstrip('!')
        self.nome, self.lane, self.neg, self.shift = nome, lane, neg, None
        if nome in REG_CORE:
            self.tipo, self.n = 'r', REG_CORE[nome]
        elif re.fullmatch(r'[sdq]\d+', nome):
            self.tipo, self.n = nome[0], int(nome[1:])
        else:
            self.tipo, self.n = 'sys', nome

    def __repr__(self):
        return f'{"-" if self.neg else ""}{self.nome}{"" if self.lane is None else f"[{self.lane}]"}{"" if not self.shift else f",{self.shift}"}'


class Imm:
    __slots__ = ('v',)

    def __init__(self, v): self.v = v
    def __repr__(self): return f'#{self.v}'


class FImm:
    __slots__ = ('v',)

    def __init__(self, v): self.v = v
    def __repr__(self): return f'#{self.v}f'


class Mem:
    __slots__ = ('base', 'align', 'off', 'pre_wb', 'post')

    def __init__(self):
        self.base, self.align, self.off, self.pre_wb, self.post = None, None, None, False, None

    def __repr__(self):
        return f'[{self.base}{":" + str(self.align) if self.align else ""}{", " + repr(self.off) if self.off is not None else ""}]{"!" if self.pre_wb else ""}{" post " + repr(self.post) if self.post is not None else ""}'


class Lista:
    __slots__ = ('regs', 'lane')

    def __init__(self, regs, lane=None): self.regs, self.lane = regs, lane
    def __repr__(self): return '{' + ','.join(map(repr, self.regs)) + '}' + ('' if self.lane is None else f'[{self.lane}]')


def _num(t):
    t = t.strip()
    if t.startswith('#'):
        t = t[1:]
    neg = t.startswith('-')
    if neg:
        t = t[1:]
    v = int(t, 0)
    return -v if neg else v


def _split(s):
    """separa por virgulas de topo (fora de [] e {})."""
    out, prof, cur = [], 0, ''
    for ch in s:
        if ch in '[{':
            prof += 1
        elif ch in ']}':
            prof -= 1
        if ch == ',' and prof == 0:
            out.append(cur.strip()); cur = ''
        else:
            cur += ch
    if cur.strip():
        out.append(cur.strip())
    return out


SHIFTS = ('lsl', 'lsr', 'asr', 'ror', 'rrx')


def _shift(t):
    t = t.strip()
    if t == 'rrx':
        return ('rrx', 1)
    tipo, arg = t.split(None, 1)
    arg = arg.strip()
    if arg.startswith('#'):
        return (tipo, _num(arg))
    return (tipo, Reg(arg))


def _reg(t):
    t = t.strip()
    neg = t.startswith('-')
    if neg:
        t = t[1:]
    m = re.fullmatch(r'([a-z_]+\d*)\[(\d*)\]', t)
    if m:
        return Reg(m.group(1), int(m.group(2)) if m.group(2) else 'all', neg)
    return Reg(t, None, neg)


def _mem(t):
    m = Mem()
    corpo = t[1:t.index(']')]
    resto = t[t.index(']') + 1:].strip()
    if resto == '!':
        m.pre_wb = True
    partes = _split(corpo)
    b = partes[0]
    if ':' in b:
        b, al = b.split(':')
        m.align = int(al, 0)
    m.base = Reg(b.strip())
    if len(partes) > 1:
        o = partes[1]
        if o.startswith('#'):
            m.off = Imm(_num(o))
        else:
            r = _reg(o)
            if len(partes) > 2:
                r.shift = _shift(partes[2])
            m.off = r
    return m


def parse(op_str):
    ops = []
    for t in _split(op_str):
        if not t:
            continue
        if t.startswith('['):
            ops.append(_mem(t))
        elif t.startswith('{'):
            fim = t.index('}')
            regs = [_reg(x) for x in t[1:fim].split(',') if x.strip()]
            lane = None
            m = re.fullmatch(r'\[(\d*)\]', t[fim + 1:].strip())
            if m:
                lane = int(m.group(1)) if m.group(1) else 'all'
            # os regs da lista podem trazer a pista cada um: {d0[1], d1[1]}
            if lane is None and regs and regs[0].lane is not None:
                lane = regs[0].lane
            ops.append(Lista(regs, lane))
        elif t.startswith('#'):
            if re.search(r'[.e]', t[1:]) and not t[1:].lower().startswith(('0x', '-0x')):
                ops.append(FImm(float(t[1:])))
            else:
                ops.append(Imm(_num(t)))
        elif t.split(None, 1)[0] in SHIFTS and ops and isinstance(ops[-1], Reg):
            ops[-1].shift = _shift(t)
        elif t.split(None, 1)[0] in SHIFTS and ops and isinstance(ops[-1], Mem):
            ops[-1].post.shift = _shift(t)
        else:
            ops.append(_reg(t))
    # pos-indice: o que vem depois de um Mem vira o deslocamento posterior
    for k, o in enumerate(ops):
        if isinstance(o, Mem) and k + 1 < len(ops):
            o.post = ops[k + 1]
            del ops[k + 1:]
            break
    return ops


def partir_mnemonico(mn):
    """'vcvt.s32.f32' -> ('vcvt', ['s32','f32']); cond/S ficam no capstone."""
    p = mn.split('.')
    return p[0], p[1:]
