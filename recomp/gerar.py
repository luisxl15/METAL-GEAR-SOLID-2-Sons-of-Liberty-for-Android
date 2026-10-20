"""Gerador ARM32 (ARM e Thumb-2) -> C.

Cada funcao do jogo vira  void F_xxxxxxxx(CPU *c).  Os registradores do nucleo
e as bandeiras viram variaveis locais (o clang os poe em registradores do
ARM64); o VFP/NEON fica em c->v.  A memoria do jogo e  m + endereco_de_32_bits.

Chamadas: os registradores sao salvos em c antes (SALVA_CH). Depois, se o alvo
segue a ABI (medir_abi.py), so r0-r3/r12/lr voltam de c (CARREGA_ABI): r4-r11 e sp
ficam nos registradores do ARM64. Alvos fora da ABI (fragmentos Thumb-1 da gnustl)
recarregam tudo.
Retorno: 'goto sai', que salva em c.  Desvio indireto que cai no endereco de
retorno com que a funcao entrou (lr0) tambem e retorno.
"""
import re
import struct
from capstone import arm as A
import ual
from ual import Reg, Imm, FImm, Mem, Lista

COND = {
    A.ARM_CC_EQ: 'fz', A.ARM_CC_NE: '!fz', A.ARM_CC_HS: 'fc', A.ARM_CC_LO: '!fc',
    A.ARM_CC_MI: 'fn', A.ARM_CC_PL: '!fn', A.ARM_CC_VS: 'fv', A.ARM_CC_VC: '!fv',
    A.ARM_CC_HI: '(fc && !fz)', A.ARM_CC_LS: '(!fc || fz)', A.ARM_CC_GE: '(fn == fv)',
    A.ARM_CC_LT: '(fn != fv)', A.ARM_CC_GT: '(!fz && fn == fv)', A.ARM_CC_LE: '(fz || fn != fv)',
}
RN = ['r0', 'r1', 'r2', 'r3', 'r4', 'r5', 'r6', 'r7', 'r8', 'r9', 'r10', 'r11', 'r12', 'sp', 'lr', 'PC']
# atribuicao a um registrador do nucleo no C emitido (=, op=, ++, --); 'lr0' e '=='
# nao casam. Na duvida casa a mais (gravar a mais e seguro).
RE_ESCRITA = re.compile(r'(?<![\w.>\[])(r1[0-2]|r[0-9]|sp|lr)\s*(?:=(?!=)|\+=|-=|\*=|/=|%=|\|=|&=|\^=|<<=|>>=|\+\+|--)'
                        r'|(?:\+\+|--)(r1[0-2]|r[0-9]|sp|lr)\b')


# nomes antigos (pre-UAL) que o capstone ainda usa para algumas formas VFP
APELIDOS = {'fconsts': 'vmov', 'fconstd': 'vmov', 'fmdhr': 'vmov', 'fmdlr': 'vmov',
            'fmstat': 'vmrs', 'hint': 'nop', 'yield': 'nop', 'movs': 'mov'}


class NaoSuportado(Exception):
    pass


def h(v):
    return f'0x{v & 0xffffffff:08x}u'


class Gerador:
    """Traduz as instrucoes de UMA funcao.  Quem chama fornece:
       - ehfuncao(endereco) -> nome C da funcao que comeca ali, ou None
       - importacao(endereco_plt) -> nome C da ponte, ou None
       - constante(endereco) -> valor de 32 bits de um endereco somente-leitura, ou None
    """

    def __init__(self, thumb, ehfuncao, importacao, constante, semretorno):
        self.n_chamadas = {True: 0, False: 0}     # chamadas com / sem recarga de bandeiras
        self._insns_atual, self._indice_atual, self._vivas_cache = [], {}, {}
        self.thumb = thumb
        self.ehfuncao = ehfuncao
        self.importacao = importacao
        self.constante = constante
        self.semretorno = semretorno
        self.faltas = {}
        # ABI dos registradores preservados (medir_abi.py): depois de chamar quem a
        # segue, r4-r11/sp nao mudaram e nao precisam voltar de c (CARREGA_ABI)
        self.segue_abi = lambda alvo: False
        self.eh_jogo = False                       # funcoes do jogo nao devolvem bandeiras
        self.n_abi = {True: 0, False: 0}
        self.n_gravados = [0, 0]                  # registradores gravados por funcao (soma, n)

    # ------------------------------------------------------------ operandos
    def pc(self, i):
        return i.address + (4 if self.thumb else 8)

    def reg(self, r, i):
        """valor lido de um registrador do nucleo"""
        if r.tipo != 'r':
            raise NaoSuportado(f'reg {r.nome}')
        if r.n == 15:
            return h(self.pc(i))
        return RN[r.n]

    def shift_expr(self, v, sh, carry=False):
        """devolve (expr, expr_carry ou None)"""
        tipo, q = sh
        if tipo == 'rrx':
            return (f'(({v}) >> 1 | (fc << 31))', f'(({v}) & 1)')
        if isinstance(q, int):
            if tipo == 'lsl':
                if q == 0:
                    return (v, None)
                return (f'(({v}) << {q})', f'((({v}) >> {32 - q}) & 1)')
            if tipo == 'lsr':
                if q == 32 or q == 0:
                    return ('0u', f'(({v}) >> 31)')
                return (f'(({v}) >> {q})', f'((({v}) >> {q - 1}) & 1)')
            if tipo == 'asr':
                if q == 32 or q == 0:
                    return (f'(uint32_t)((int32_t)({v}) >> 31)', f'(({v}) >> 31)')
                return (f'(uint32_t)((int32_t)({v}) >> {q})', f'((({v}) >> {q - 1}) & 1)')
            if tipo == 'ror':
                return (f'ROR32({v}, {q})', f'((({v}) >> {q - 1}) & 1)')
        else:
            if q.n == 15:
                raise NaoSuportado('deslocamento por pc')
            s = f'({RN[q.n]} & 0xff)'
            f = {'lsl': 'SHL_R', 'lsr': 'SHR_R', 'asr': 'SAR_R', 'ror': 'ROR_R'}[tipo]
            return (f'{f}({v}, {s})', f'{f}_C({v}, {s}, fc)')
        raise NaoSuportado(f'shift {sh}')

    def op2(self, o, i, precisa_carry=False):
        """segundo operando (imediato ou registrador com deslocamento)."""
        if isinstance(o, Imm):
            v = o.v & 0xffffffff
            car = None
            if precisa_carry:
                car = self.carry_imm(i, v)
            return (h(v), car)
        if isinstance(o, Reg):
            v = self.reg(o, i)
            if o.shift:
                return self.shift_expr(v, o.shift)
            return (v, None)
        raise NaoSuportado(f'op2 {o}')

    def carry_imm(self, i, v):
        """carry de imediato modificado: so muda se houve rotacao"""
        b = bytes(i.bytes)
        if not self.thumb:
            w = struct.unpack('<I', b)[0]
            rot = (w >> 8) & 0xf
            return None if rot == 0 else str((v >> 31) & 1)
        if len(b) == 4:
            h1, h2 = struct.unpack('<HH', b)
            ii = (h1 >> 10) & 1
            imm3 = (h2 >> 12) & 7
            a = (h2 >> 7) & 1
            if (ii << 4 | imm3 << 1 | a) >= 8:
                return str((v >> 31) & 1)
        return None

    # ------------------------------------------------------------ utilitarios
    def dst(self, r, expr, i, sai):
        """escreve num registrador; pc = desvio"""
        if r.n == 15:
            sai.append(self.desvio_indireto(expr, i))
        else:
            sai.append(f'{RN[r.n]} = {expr};')

    def desvio_indireto(self, alvo, i, eh_pop=False):
        """escrita em pc que nao e tabela: retorno ou salto/chamada indireta"""
        prox = i.address + i.size
        carrega = 'CARREGA_CHF' if self.bandeiras_vivas_apos(i) else 'CARREGA_CH'
        return (f'{{ uint32_t _t = {alvo}; '
                f'if (_t == lr0) goto sai; '
                f'if (lr == {h(prox)}) {{ SALVA_CH; despacha(c, _t); {carrega}; }} '
                f'else {{ SALVA; despacha(c, _t); return; }} }}')

    def nzs(self, res):
        return f'fn = {res} >> 31; fz = {res} == 0;'

    def endereco(self, mm, i):
        """(expr do endereco efetivo, expr do novo valor da base ou None)"""
        b = mm.base
        if b.n == 15:
            base = h(self.pc(i) & ~3 if self.thumb else self.pc(i))
        else:
            base = RN[b.n]
        def off_expr(o):
            if o is None:
                return None
            if isinstance(o, Imm):
                return (o.v, None)
            v = self.reg(o, i)
            if o.shift:
                v = self.shift_expr(v, o.shift)[0]
            return (None, ('-' if o.neg else '+') + f' ({v})')
        if b.n == 15 and (mm.post is not None or mm.pre_wb):
            raise NaoSuportado('escrita de volta em pc')
        if mm.post is not None:
            o = off_expr(mm.post)
            if o[0] is not None:
                novo = f'({base} + {h(o[0])})'
            else:
                novo = f'({base} {o[1]})'
            return base, novo
        o = off_expr(mm.off)
        if o is None:
            ea = base
        elif o[0] is not None:
            ea = f'({base} + {h(o[0])})' if o[0] else base
        else:
            ea = f'({base} {o[1]})'
        return ea, (ea if mm.pre_wb else None)

    # ------------------------------------------------------------ traducao
    def traduzir(self, i, ops, rotulos):
        """devolve lista de linhas C (sem a condicao)."""
        nome = i.insn_name()
        base, dts = ual.partir_mnemonico(i.mnemonic)
        # o bit S sai do texto: o capstone liga update_flags em adc/sbc sem 's'
        resto = base[len(nome):] if base.startswith(nome) else ''
        S = resto.startswith('s') or nome == 'movs'
        nome = APELIDOS.get(nome, nome)
        f = getattr(self, 'i_' + nome, None)
        if f is None:
            from gerar_vfp import VFP
            f = VFP.tabela.get(nome)
            if f is None:
                raise NaoSuportado(nome)
            return f(self, i, ops, dts, rotulos)
        return f(i, ops, S, dts, rotulos)

    # ---- processamento de dados
    def _logica(self, i, ops, S, oper):
        d = ops[0]
        if len(ops) == 2:
            a = None if oper in ('mov', 'mvn') else self.reg(ops[0], i)
            b = ops[1]
        else:
            a, b = self.reg(ops[1], i), ops[2]
        v, car = self.op2(b, i, precisa_carry=S)
        sai = []
        if oper == 'mov':
            e = v
        elif oper == 'mvn':
            e = f'~({v})'
        elif oper == 'bic':
            e = f'({a} & ~({v}))'
        else:
            e = f'({a} {oper} ({v}))'
        if d.n == 15:
            if S:
                raise NaoSuportado('S com pc')
            sai.append(self.desvio_indireto(e, i))
            return sai
        if S:
            sai.append(f'{{ uint32_t _r = {e}; {"fc = " + car + ";" if car else ""} {RN[d.n]} = _r; {self.nzs("_r")} }}')
        else:
            sai.append(f'{RN[d.n]} = {e};')
        return sai

    def i_mov(self, i, ops, S, dts, rot): return self._logica(i, ops, S, 'mov')
    def i_mvn(self, i, ops, S, dts, rot): return self._logica(i, ops, S, 'mvn')
    def i_and(self, i, ops, S, dts, rot): return self._logica(i, ops, S, '&')
    def i_orr(self, i, ops, S, dts, rot): return self._logica(i, ops, S, '|')
    def i_eor(self, i, ops, S, dts, rot): return self._logica(i, ops, S, '^')
    def i_bic(self, i, ops, S, dts, rot): return self._logica(i, ops, S, 'bic')

    def i_orn(self, i, ops, S, dts, rot):
        d = ops[0]
        a = self.reg(ops[1] if len(ops) == 3 else ops[0], i)
        v, car = self.op2(ops[-1], i, S)
        return self._fim_logica(d, f'({a} | ~({v}))', S, car)

    def _fim_logica(self, d, e, S, car):
        if S:
            return [f'{{ uint32_t _r = {e}; {"fc = " + car + ";" if car else ""} {RN[d.n]} = _r; {self.nzs("_r")} }}']
        return [f'{RN[d.n]} = {e};']

    def _desloc(self, i, ops, S, tipo):
        # lsl r0, r1, #2  /  lsl r0, r1, r2  (formas UAL de mov com deslocamento)
        d = ops[0]
        if len(ops) == 2:
            src, q = ops[0], ops[1]
        else:
            src, q = ops[1], ops[2]
        v = self.reg(src, i)
        if isinstance(q, Imm):
            e, car = self.shift_expr(v, (tipo, q.v))
        else:
            e, car = self.shift_expr(v, (tipo, q))
        return self._fim_logica(d, e, S, car)

    def i_lsl(self, i, ops, S, dts, rot): return self._desloc(i, ops, S, 'lsl')
    def i_lsr(self, i, ops, S, dts, rot): return self._desloc(i, ops, S, 'lsr')
    def i_asr(self, i, ops, S, dts, rot): return self._desloc(i, ops, S, 'asr')
    def i_ror(self, i, ops, S, dts, rot): return self._desloc(i, ops, S, 'ror')

    def i_rrx(self, i, ops, S, dts, rot):
        e, car = self.shift_expr(self.reg(ops[1], i), ('rrx', 1))
        return self._fim_logica(ops[0], e, S, car)

    def _arit(self, i, ops, S, tipo, rot=None):
        d = ops[0]
        if len(ops) == 2:
            a, b = self.reg(ops[0], i), ops[1]
        else:
            a, b = self.reg(ops[1], i), ops[2]
        v, _ = self.op2(b, i)
        if tipo == 'rsb':
            a, v = v, a
            tipo = 'sub'
        elif tipo == 'rsc':
            a, v = v, a
            tipo = 'sbc'
        cin = {'add': '0', 'sub': '1', 'adc': 'fc', 'sbc': 'fc'}[tipo]
        bb = v if tipo in ('add', 'adc') else f'~({v})'
        if d.n == 15:
            if S:
                raise NaoSuportado('S com pc')
            e = {'add': f'({a} + {v})', 'sub': f'({a} - {v})', 'adc': f'({a} + {v} + fc)', 'sbc': f'({a} - {v} - !fc)'}[tipo]
            return self._pc_aritmetico(i, e, rot)
        if not S:
            e = {'add': f'{a} + {v}', 'sub': f'{a} - {v}', 'adc': f'{a} + {v} + fc', 'sbc': f'{a} - {v} - !fc'}[tipo]
            return [f'{RN[d.n]} = {e};']
        return [f'{{ uint32_t _a = {a}, _b = {bb}; uint64_t _s = (uint64_t)_a + _b + {cin}; uint32_t _r = (uint32_t)_s; '
                f'fc = (uint32_t)(_s >> 32); fv = ((~(_a ^ _b)) & (_a ^ _r)) >> 31; {RN[d.n]} = _r; {self.nzs("_r")} }}']

    def _pc_aritmetico(self, i, e, rot):
        # tabela de salto:  addls pc, pc, rN, lsl #2  (tratada no laco da funcao)
        tab = (rot or {}).get(('tabela', i.address))
        if tab is not None:
            idx = tab['indice']
            linhas = [f'switch ({idx}) {{']
            for k, alvo in enumerate(tab['casos']):
                linhas.append(f'case {k}: {self.salto(alvo, i)}')
            linhas.append(f'default: FALHA_TABELA({h(i.address)}, {idx}); }}')
            return linhas
        return [self.desvio_indireto(e, i)]

    def i_add(self, i, ops, S, dts, rot): return self._arit(i, ops, S, 'add', rot)
    def i_sub(self, i, ops, S, dts, rot): return self._arit(i, ops, S, 'sub', rot)
    def i_rsb(self, i, ops, S, dts, rot): return self._arit(i, ops, S, 'rsb', rot)
    def i_adc(self, i, ops, S, dts, rot): return self._arit(i, ops, S, 'adc', rot)
    def i_sbc(self, i, ops, S, dts, rot): return self._arit(i, ops, S, 'sbc', rot)
    def i_rsc(self, i, ops, S, dts, rot): return self._arit(i, ops, S, 'rsc', rot)

    def i_addw(self, i, ops, S, dts, rot): return self._arit(i, ops, False, 'add')
    def i_subw(self, i, ops, S, dts, rot): return self._arit(i, ops, False, 'sub')

    def i_adr(self, i, ops, S, dts, rot):
        # thumb: adr rd, #rotulo  -> Align(pc,4) + imm (capstone mostra o deslocamento)
        return [f'{RN[ops[0].n]} = {h((self.pc(i) & ~3) + ops[1].v)};']

    def _cmp(self, i, ops, tipo):
        a = self.reg(ops[0], i)
        v, car = self.op2(ops[1], i, precisa_carry=tipo in ('tst', 'teq'))
        if tipo == 'tst':
            return [f'{{ uint32_t _r = {a} & ({v}); {"fc = " + car + ";" if car else ""} {self.nzs("_r")} }}']
        if tipo == 'teq':
            return [f'{{ uint32_t _r = {a} ^ ({v}); {"fc = " + car + ";" if car else ""} {self.nzs("_r")} }}']
        bb, cin = (v, '0') if tipo == 'cmn' else (f'~({v})', '1')
        return [f'{{ uint32_t _a = {a}, _b = {bb}; uint64_t _s = (uint64_t)_a + _b + {cin}; uint32_t _r = (uint32_t)_s; '
                f'fc = (uint32_t)(_s >> 32); fv = ((~(_a ^ _b)) & (_a ^ _r)) >> 31; {self.nzs("_r")} }}']

    def i_cmp(self, i, ops, S, dts, rot): return self._cmp(i, ops, 'cmp')
    def i_cmn(self, i, ops, S, dts, rot): return self._cmp(i, ops, 'cmn')
    def i_tst(self, i, ops, S, dts, rot): return self._cmp(i, ops, 'tst')
    def i_teq(self, i, ops, S, dts, rot): return self._cmp(i, ops, 'teq')

    def i_movw(self, i, ops, S, dts, rot):
        return [f'{RN[ops[0].n]} = {h(ops[1].v & 0xffff)};']

    def i_movt(self, i, ops, S, dts, rot):
        d = RN[ops[0].n]
        return [f'{d} = ({d} & 0xffffu) | {h((ops[1].v & 0xffff) << 16)};']

    # ---- multiplicacao
    def i_mul(self, i, ops, S, dts, rot):
        d, a = ops[0], self.reg(ops[1], i)
        b = self.reg(ops[2], i) if len(ops) > 2 else RN[ops[0].n]
        e = f'{a} * {b}'
        if S:
            return [f'{{ uint32_t _r = {e}; {RN[d.n]} = _r; {self.nzs("_r")} }}']
        return [f'{RN[d.n]} = {e};']

    def i_mla(self, i, ops, S, dts, rot):
        d, a, b, acc = ops[0], self.reg(ops[1], i), self.reg(ops[2], i), self.reg(ops[3], i)
        e = f'{a} * {b} + {acc}'
        if S:
            return [f'{{ uint32_t _r = {e}; {RN[d.n]} = _r; {self.nzs("_r")} }}']
        return [f'{RN[d.n]} = {e};']

    def i_mls(self, i, ops, S, dts, rot):
        d, a, b, acc = ops[0], self.reg(ops[1], i), self.reg(ops[2], i), self.reg(ops[3], i)
        return [f'{RN[d.n]} = {acc} - {a} * {b};']

    def _longa(self, i, ops, S, sinal, acumula):
        lo, hi, a, b = RN[ops[0].n], RN[ops[1].n], self.reg(ops[2], i), self.reg(ops[3], i)
        if sinal:
            p = f'(uint64_t)((int64_t)(int32_t){a} * (int32_t){b})'
        else:
            p = f'((uint64_t){a} * {b})'
        if acumula:
            p = f'({p} + (((uint64_t){hi} << 32) | {lo}))'
        s = f'{{ uint64_t _p = {p}; {lo} = (uint32_t)_p; {hi} = (uint32_t)(_p >> 32);'
        if S:
            s += ' fn = (uint32_t)(_p >> 63); fz = _p == 0;'
        return [s + ' }']

    def i_umull(self, i, ops, S, dts, rot): return self._longa(i, ops, S, False, False)
    def i_smull(self, i, ops, S, dts, rot): return self._longa(i, ops, S, True, False)
    def i_umlal(self, i, ops, S, dts, rot): return self._longa(i, ops, S, False, True)
    def i_smlal(self, i, ops, S, dts, rot): return self._longa(i, ops, S, True, True)

    def i_umaal(self, i, ops, S, dts, rot):
        lo, hi, a, b = RN[ops[0].n], RN[ops[1].n], self.reg(ops[2], i), self.reg(ops[3], i)
        return [f'{{ uint64_t _p = (uint64_t){a} * {b} + {lo} + {hi}; {lo} = (uint32_t)_p; {hi} = (uint32_t)(_p >> 32); }}']

    def _meia(self, x, qual):
        return f'(int32_t)(int16_t)({x})' if qual == 'b' else f'(int32_t)(int16_t)(({x}) >> 16)'

    def _smulxy(self, i, ops, xy, acumula):
        d, a, b = RN[ops[0].n], self.reg(ops[1], i), self.reg(ops[2], i)
        p = f'({self._meia(a, xy[0])} * {self._meia(b, xy[1])})'
        if acumula:
            acc = self.reg(ops[3], i)
            # Q (saturacao) nao e usado pelo jogo
            return [f'{d} = (uint32_t)({p} + (int32_t){acc});']
        return [f'{d} = (uint32_t){p};']

    def i_smulbb(self, i, ops, S, dts, rot): return self._smulxy(i, ops, 'bb', False)
    def i_smulbt(self, i, ops, S, dts, rot): return self._smulxy(i, ops, 'bt', False)
    def i_smultb(self, i, ops, S, dts, rot): return self._smulxy(i, ops, 'tb', False)
    def i_smultt(self, i, ops, S, dts, rot): return self._smulxy(i, ops, 'tt', False)
    def i_smlabb(self, i, ops, S, dts, rot): return self._smulxy(i, ops, 'bb', True)
    def i_smlabt(self, i, ops, S, dts, rot): return self._smulxy(i, ops, 'bt', True)
    def i_smlatb(self, i, ops, S, dts, rot): return self._smulxy(i, ops, 'tb', True)
    def i_smlatt(self, i, ops, S, dts, rot): return self._smulxy(i, ops, 'tt', True)

    def i_smlalbb(self, i, ops, S, dts, rot):
        lo, hi, a, b = RN[ops[0].n], RN[ops[1].n], self.reg(ops[2], i), self.reg(ops[3], i)
        return [f'{{ uint64_t _p = (uint64_t)(int64_t)({self._meia(a, "b")} * {self._meia(b, "b")}) + (((uint64_t){hi} << 32) | {lo}); {lo} = (uint32_t)_p; {hi} = (uint32_t)(_p >> 32); }}']

    def i_udiv(self, i, ops, S, dts, rot):
        d, a, b = RN[ops[0].n], self.reg(ops[1], i), self.reg(ops[2], i)
        return [f'{d} = {b} ? {a} / {b} : 0;']

    def i_sdiv(self, i, ops, S, dts, rot):
        d, a, b = RN[ops[0].n], self.reg(ops[1], i), self.reg(ops[2], i)
        return [f'{d} = SDIV32({a}, {b});']

    # ---- bits
    def i_clz(self, i, ops, S, dts, rot):
        a = self.reg(ops[1], i)
        return [f'{RN[ops[0].n]} = {a} ? (uint32_t)__builtin_clz({a}) : 32u;']

    def i_rbit(self, i, ops, S, dts, rot):
        return [f'{RN[ops[0].n]} = RBIT32({self.reg(ops[1], i)});']

    def i_rev(self, i, ops, S, dts, rot):
        return [f'{RN[ops[0].n]} = __builtin_bswap32({self.reg(ops[1], i)});']

    def i_rev16(self, i, ops, S, dts, rot):
        a = self.reg(ops[1], i)
        return [f'{RN[ops[0].n]} = (({a} & 0x00ff00ffu) << 8) | (({a} >> 8) & 0x00ff00ffu);']

    def i_ubfx(self, i, ops, S, dts, rot):
        a, lsb, w = self.reg(ops[1], i), ops[2].v, ops[3].v
        mask = (1 << w) - 1
        return [f'{RN[ops[0].n]} = ({a} >> {lsb}) & {h(mask)};']

    def i_sbfx(self, i, ops, S, dts, rot):
        a, lsb, w = self.reg(ops[1], i), ops[2].v, ops[3].v
        return [f'{RN[ops[0].n]} = (uint32_t)((int32_t)({a} << {32 - lsb - w}) >> {32 - w});']

    def i_bfi(self, i, ops, S, dts, rot):
        d, a, lsb, w = RN[ops[0].n], self.reg(ops[1], i), ops[2].v, ops[3].v
        mask = ((1 << w) - 1) << lsb
        return [f'{d} = ({d} & {h(~mask)}) | (({a} << {lsb}) & {h(mask)});']

    def i_bfc(self, i, ops, S, dts, rot):
        d, lsb, w = RN[ops[0].n], ops[1].v, ops[2].v
        mask = ((1 << w) - 1) << lsb
        return [f'{d} &= {h(~mask)};']

    def _ext(self, i, ops, tipo, soma):
        d = RN[ops[0].n]
        if soma:
            acc, src = self.reg(ops[1], i), ops[2]
        else:
            acc, src = None, ops[1]
        v = self.reg(src, i)
        if src.shift:
            v = f'ROR32({v}, {src.shift[1]})'
        e = {'uxtb': f'(uint32_t)(uint8_t)({v})', 'uxth': f'(uint32_t)(uint16_t)({v})',
             'sxtb': f'(uint32_t)(int32_t)(int8_t)({v})', 'sxth': f'(uint32_t)(int32_t)(int16_t)({v})'}[tipo]
        return [f'{d} = {acc + " + " if acc else ""}{e};']

    def i_uxtb(self, i, ops, S, dts, rot): return self._ext(i, ops, 'uxtb', False)
    def i_uxth(self, i, ops, S, dts, rot): return self._ext(i, ops, 'uxth', False)
    def i_sxtb(self, i, ops, S, dts, rot): return self._ext(i, ops, 'sxtb', False)
    def i_sxth(self, i, ops, S, dts, rot): return self._ext(i, ops, 'sxth', False)
    def i_uxtab(self, i, ops, S, dts, rot): return self._ext(i, ops, 'uxtb', True)
    def i_uxtah(self, i, ops, S, dts, rot): return self._ext(i, ops, 'uxth', True)
    def i_sxtab(self, i, ops, S, dts, rot): return self._ext(i, ops, 'sxtb', True)
    def i_sxtah(self, i, ops, S, dts, rot): return self._ext(i, ops, 'sxth', True)

    def i_usat(self, i, ops, S, dts, rot):
        d, sat, src = RN[ops[0].n], ops[1].v, ops[2]
        v = self.reg(src, i)
        if src.shift:
            v = self.shift_expr(v, src.shift)[0]
        mx = (1 << sat) - 1
        return [f'{{ int32_t _x = (int32_t)({v}); {d} = _x < 0 ? 0u : (_x > {mx} ? {mx}u : (uint32_t)_x); }}']

    def i_ssat(self, i, ops, S, dts, rot):
        d, sat, src = RN[ops[0].n], ops[1].v, ops[2]
        v = self.reg(src, i)
        if src.shift:
            v = self.shift_expr(v, src.shift)[0]
        mx, mn = (1 << (sat - 1)) - 1, -(1 << (sat - 1))
        return [f'{{ int32_t _x = (int32_t)({v}); {d} = (uint32_t)(_x < {mn} ? {mn} : (_x > {mx} ? {mx} : _x)); }}']

    def i_qadd(self, i, ops, S, dts, rot):
        d, a, b = RN[ops[0].n], self.reg(ops[1], i), self.reg(ops[2], i)
        return [f'{{ int64_t _s = (int64_t)(int32_t){a} + (int32_t){b}; {d} = (uint32_t)(_s > 0x7fffffff ? 0x7fffffff : (_s < -0x7fffffffLL - 1 ? 0x80000000u : _s)); }}']

    # ---- memoria
    def _ld(self, i, ops, larg, sinal, rot):
        d = ops[0]
        mm = ops[1]
        ea, novo = self.endereco(mm, i)
        # literal: carga de pc sem escrita -> constante
        if mm.base.n == 15 and mm.post is None and not mm.pre_wb and isinstance(mm.off, (Imm, type(None))):
            addr = ((self.pc(i) & ~3) if self.thumb else self.pc(i)) + (mm.off.v if mm.off else 0)
            k = self.constante(addr, larg)
            if k is not None:
                if sinal:
                    k = k - (1 << (8 * larg)) if k >> (8 * larg - 1) else k
                if d.n == 15:
                    return [self.desvio_indireto(h(k), i)]
                return [f'{RN[d.n]} = {h(k)};']
        f = {(4, 0): 'L32', (2, 0): 'L16', (1, 0): 'L8', (2, 1): 'L16S', (1, 1): 'L8S'}[(larg, sinal)]
        sai = [f'{{ uint32_t _ea = {ea}; uint32_t _v = {f}(_ea);']
        if novo is not None and mm.base.n != d.n:
            sai.append(f'{RN[mm.base.n]} = {"_ea" if novo == ea else novo};')
        if d.n == 15:
            sai.append(self.desvio_indireto('_v', i) + ' }')
            return sai
        sai.append(f'{RN[d.n]} = _v; }}')
        return [' '.join(sai)]

    def i_ldr(self, i, ops, S, dts, rot): return self._ld(i, ops, 4, 0, rot)
    def i_ldrb(self, i, ops, S, dts, rot): return self._ld(i, ops, 1, 0, rot)
    def i_ldrh(self, i, ops, S, dts, rot): return self._ld(i, ops, 2, 0, rot)
    def i_ldrsb(self, i, ops, S, dts, rot): return self._ld(i, ops, 1, 1, rot)
    def i_ldrsh(self, i, ops, S, dts, rot): return self._ld(i, ops, 2, 1, rot)
    i_ldrt = i_ldr
    i_ldrbt = i_ldrb
    i_ldrht = i_ldrh
    i_ldrsbt = i_ldrsb
    i_ldrsht = i_ldrsh

    def _st(self, i, ops, larg):
        s = ops[0]
        mm = ops[1]
        ea, novo = self.endereco(mm, i)
        v = self.reg(s, i)
        f = {4: 'S32', 2: 'S16', 1: 'S8'}[larg]
        linha = f'{{ uint32_t _ea = {ea}; {f}(_ea, {v});'
        if novo is not None:
            linha += f' {RN[mm.base.n]} = {"_ea" if novo == ea else novo};'
        return [linha + ' }']

    def i_str(self, i, ops, S, dts, rot): return self._st(i, ops, 4)
    def i_strb(self, i, ops, S, dts, rot): return self._st(i, ops, 1)
    def i_strh(self, i, ops, S, dts, rot): return self._st(i, ops, 2)
    i_strt = i_str
    i_strbt = i_strb
    i_strht = i_strh

    def i_ldrd(self, i, ops, S, dts, rot):
        a, b, mm = ops[0], ops[1], ops[2]
        if a.n == 15 or b.n == 15:
            raise NaoSuportado('ldrd em pc')
        ea, novo = self.endereco(mm, i)
        linha = f'{{ uint32_t _ea = {ea}; uint32_t _a = L32(_ea), _b = L32(_ea + 4);'
        if novo is not None:
            linha += f' {RN[mm.base.n]} = {novo};'
        return [linha + f' {RN[a.n]} = _a; {RN[b.n]} = _b; }}']

    def i_strd(self, i, ops, S, dts, rot):
        a, b, mm = ops[0], ops[1], ops[2]
        ea, novo = self.endereco(mm, i)
        linha = f'{{ uint32_t _ea = {ea}; S32(_ea, {self.reg(a, i)}); S32(_ea + 4, {self.reg(b, i)});'
        if novo is not None:
            linha += f' {RN[mm.base.n]} = {novo};'
        return [linha + ' }']

    def _ldm_stm(self, i, ops, carga, modo, base_reg=None, wb=None):
        plano = []
        for o in ops:
            plano.extend(o.regs if isinstance(o, Lista) else [o])
        if base_reg is None:
            base_reg = plano[0]
            regs = plano[1:]
            wb = base_reg.wb
        else:
            regs = plano
        regs = sorted(regs, key=lambda r: r.n)
        n = len(regs)
        b = RN[base_reg.n]
        ini = {'ia': '0', 'ib': '4', 'da': f'-{4 * n - 4}', 'db': f'-{4 * n}'}[modo]
        fim = {'ia': f'+{4 * n}', 'ib': f'+{4 * n}', 'da': f'-{4 * n}', 'db': f'-{4 * n}'}[modo]
        linhas = [f'{{ uint32_t _ea = {b} + (uint32_t)({ini});']
        pc_carregado = False
        for k, r in enumerate(regs):
            if carga:
                if r.n == 15:
                    linhas.append(f'uint32_t _pc = L32(_ea + {4 * k});')
                    pc_carregado = True
                elif r.n == base_reg.n:
                    linhas.append(f'uint32_t _bv = L32(_ea + {4 * k});')
                else:
                    linhas.append(f'{RN[r.n]} = L32(_ea + {4 * k});')
            else:
                linhas.append(f'S32(_ea + {4 * k}, {self.reg(r, i)});')
        base_na_lista = any(r.n == base_reg.n for r in regs)
        if wb and not (carga and base_na_lista):
            linhas.append(f'{b} = {b} + (uint32_t)({fim});')
        if carga and base_na_lista:
            linhas.append(f'{b} = _bv;')
        if pc_carregado:
            linhas.append(self.desvio_indireto('_pc', i, eh_pop=True))
        linhas.append('}')
        return [' '.join(linhas)]

    def i_ldm(self, i, ops, S, dts, rot): return self._ldm_stm(i, ops, True, 'ia')
    def i_ldmib(self, i, ops, S, dts, rot): return self._ldm_stm(i, ops, True, 'ib')
    def i_ldmda(self, i, ops, S, dts, rot): return self._ldm_stm(i, ops, True, 'da')
    def i_ldmdb(self, i, ops, S, dts, rot): return self._ldm_stm(i, ops, True, 'db')
    def i_stm(self, i, ops, S, dts, rot): return self._ldm_stm(i, ops, False, 'ia')
    def i_stmib(self, i, ops, S, dts, rot): return self._ldm_stm(i, ops, False, 'ib')
    def i_stmda(self, i, ops, S, dts, rot): return self._ldm_stm(i, ops, False, 'da')
    def i_stmdb(self, i, ops, S, dts, rot): return self._ldm_stm(i, ops, False, 'db')

    def i_push(self, i, ops, S, dts, rot):
        return self._ldm_stm(i, ops, False, 'db', base_reg=Reg('sp'), wb=True)

    def i_pop(self, i, ops, S, dts, rot):
        return self._ldm_stm(i, ops, True, 'ia', base_reg=Reg('sp'), wb=True)

    def i_ldrex(self, i, ops, S, dts, rot):
        ea, _ = self.endereco(ops[1], i)
        return [f'{{ uint32_t _ea = {ea}; {RN[ops[0].n]} = c->ex_v = L32(_ea); c->ex_a = _ea; c->ex_ok = 1; }}']

    def i_ldrexb(self, i, ops, S, dts, rot):
        ea, _ = self.endereco(ops[1], i)
        return [f'{{ uint32_t _ea = {ea}; {RN[ops[0].n]} = c->ex_v = L8(_ea); c->ex_a = _ea; c->ex_ok = 1; }}']

    def i_strex(self, i, ops, S, dts, rot):
        ea, _ = self.endereco(ops[2], i)
        return [f'{RN[ops[0].n]} = STREX32(c, {ea}, {self.reg(ops[1], i)});']

    def i_strexb(self, i, ops, S, dts, rot):
        ea, _ = self.endereco(ops[2], i)
        return [f'{RN[ops[0].n]} = STREX8(c, {ea}, {self.reg(ops[1], i)});']

    def i_clrex(self, i, ops, S, dts, rot): return ['c->ex_ok = 0;']
    def i_dmb(self, i, ops, S, dts, rot): return ['BARREIRA();']
    def i_dsb(self, i, ops, S, dts, rot): return ['BARREIRA();']
    def i_pld(self, i, ops, S, dts, rot): return []
    def i_nop(self, i, ops, S, dts, rot): return []
    def i_it(self, i, ops, S, dts, rot): return []
    def i_udf(self, i, ops, S, dts, rot): return [f'ARMADILHA(c, {h(i.address)});']
    def i_svc(self, i, ops, S, dts, rot): return [f'ARMADILHA(c, {h(i.address)});']
    i_bkpt = i_udf

    # ---- desvios
    def salto(self, alvo, i):
        """goto para rotulo local, ou salto de cauda para outra funcao"""
        if ('rotulo', alvo) in self.rotulos_validos:
            return f'goto L_{alvo:08x};'
        fn = self.ehfuncao(alvo) or self.importacao(alvo)
        if fn:
            return f'{{ SALVA; {fn}(c); return; }}'
        return f'{{ SALVA; despacha(c, {h(alvo)}); return; }}'

    def i_b(self, i, ops, S, dts, rot):
        return [self.salto(ops[0].v, i)]

    def chamada(self, alvo_expr, i, direto=None):
        prox = i.address + i.size
        ret = h(prox | (1 if self.thumb else 0))
        carrega = 'CARREGA_CHF' if self.bandeiras_vivas_apos(i) else 'CARREGA_CH'
        abi = self.segue_abi(int(alvo_expr[:-1], 16)) if direto else self.eh_jogo
        self.n_abi[abi] += 1
        if abi:
            carrega = 'CARREGA_ABI'
        if direto:
            s = f'lr = {ret}; SALVA_CH; {direto}(c); {carrega};'
        else:
            s = f'{{ uint32_t _t = {alvo_expr}; lr = {ret}; SALVA_CH; despacha(c, _t); {carrega}; }}'
        return [s]

    def i_bl(self, i, ops, S, dts, rot):
        alvo = ops[0].v
        fn = self.ehfuncao(alvo) or self.importacao(alvo)
        s = self.chamada(h(alvo), i, fn)
        if alvo in self.semretorno:
            s.append('goto sai;')
        return s

    def i_blx(self, i, ops, S, dts, rot):
        o = ops[0]
        if isinstance(o, Imm):
            alvo = o.v
            fn = self.ehfuncao(alvo) or self.importacao(alvo)
            return self.chamada(h(alvo), i, fn)
        return self.chamada(self.reg(o, i), i)

    def i_bx(self, i, ops, S, dts, rot):
        r = ops[0]
        return [self.desvio_indireto(self.reg(r, i), i)]

    def i_cbz(self, i, ops, S, dts, rot):
        return [f'if ({self.reg(ops[0], i)} == 0) {self.salto(ops[1].v, i)}']

    def i_cbnz(self, i, ops, S, dts, rot):
        return [f'if ({self.reg(ops[0], i)} != 0) {self.salto(ops[1].v, i)}']

    def _tb(self, i, ops, larg, rot):
        tab = rot.get(('tabela', i.address))
        if tab is None:
            raise NaoSuportado('tbb sem tabela')
        idx = tab['indice']
        linhas = [f'switch ({idx}) {{']
        for k, alvo in enumerate(tab['casos']):
            linhas.append(f'case {k}: {self.salto(alvo, i)}')
        linhas.append(f'default: FALHA_TABELA({h(i.address)}, {idx}); }}')
        return linhas

    def i_tbb(self, i, ops, S, dts, rot): return self._tb(i, ops, 1, rot)
    def i_tbh(self, i, ops, S, dts, rot): return self._tb(i, ops, 2, rot)

    # ------------------------------------------------------------ funcao
    def funcao(self, nome, ini, insns, rotulos, tabelas, proxima=None, seguinte_nome=None, teste=False):
        """insns: lista ordenada de instrucoes capstone ja decodificadas.
        rotulos: enderecos alvo de desvio dentro da funcao.
        proxima: endereco logo apos a ultima instrucao alcancavel de cada bloco
        que cai para fora do intervalo (queda na funcao seguinte)."""
        rotulos = set(rotulos) | {ini}
        self.rotulos_validos = {('rotulo', a) for a in rotulos}
        self._insns_atual = insns
        self._indice_atual = {x.address: k for k, x in enumerate(insns)}
        self._vivas_cache = {}
        rot = dict(((('tabela', a), t) for a, t in tabelas.items()))
        corpo = []
        fora = 0
        enderecos = {i.address for i in insns}
        for k, i in enumerate(insns):
            if i.address in rotulos:
                corpo.append(f'L_{i.address:08x}:;')
            try:
                ops = ual.parse(i.op_str)
                linhas = self.traduzir(i, ops, rot)
            except NaoSuportado as ex:
                chave = f'{i.insn_name()}:{ex}'
                self.faltas[chave] = self.faltas.get(chave, 0) + 1
                linhas = [f'NAO_SUPORTADO(c, {h(i.address)}); /* {i.mnemonic} {i.op_str} : {ex} */']
            except Exception as ex:
                chave = f'{i.insn_name()}:ERRO {type(ex).__name__}'
                self.faltas[chave] = self.faltas.get(chave, 0) + 1
                linhas = [f'NAO_SUPORTADO(c, {h(i.address)}); /* {i.mnemonic} {i.op_str} : {type(ex).__name__} {ex} */']
            cond = COND.get(i.cc)
            texto = f'/* {i.address:08x}: {i.mnemonic} {i.op_str} */'
            if cond and i.insn_name() not in ('it',):
                corpo.append(f'if ({cond}) {{ {" ".join(linhas)} }} {texto}')
            else:
                corpo.append(f'{" ".join(linhas)} {texto}')
            # queda para fora: proxima instrucao nao decodificada nesta funcao
            prox = i.address + i.size
            termina = self.termina(i)
            if not termina and prox not in enderecos:
                corpo.append(('goto sai;' if teste else self.salto(prox, i)) + ' /* queda */')
        # restrict: a CPU (heap do hospedeiro) nunca e alcancada pela memoria do jogo,
        # entao o clang pode manter c->v (VFP/NEON) em registradores entre loads/stores
        #
        # Gravacao parcial: ENTRA carrega os 15 registradores de c e toda chamada os
        # recarrega de c depois. Logo um registrador que o corpo NUNCA atribui tem
        # sempre o mesmo valor do local e de c, e nao precisa ser gravado antes de
        # chamada nem no retorno. O conjunto sai do texto C emitido (a fonte da
        # verdade), nao das instrucoes ARM. Um getter de 2 instrucoes gravava 15.
        texto = '\n'.join(l.split(' /* ')[0] for l in corpo)
        escritos = sorted({RN.index(a or b) for a, b in RE_ESCRITA.findall(texto)})
        self.n_gravados[0] += len(escritos); self.n_gravados[1] += 1
        sw = ' '.join(f'c->r[{k}] = {RN[k]};' for k in escritos)
        band = 'c->fn = fn; c->fz = fz; c->fc = fc; c->fv = fv;'
        corpo = [l.replace('SALVA_CH;', 'SALVA_W;').replace('SALVA;', f'SALVA_W; {band}') for l in corpo]
        if self.eh_jogo and not teste:
            sai = 'SALVA_W; return;'                  # funcao do jogo: sem bandeiras (SAI_ABI)
        else:
            sai = f'SALVA_W; {band} return;'
        return (f'#ifdef MGS2_CARREGA_TUDO\n#define SALVA_W SALVA_CH\n#else\n'
                f'#define SALVA_W do {{ {sw} }} while (0)\n#endif\n'
                f'void {nome}(CPU *restrict c) {{\n'
                f'    ENTRA;\n'
                f'    goto L_{ini:08x};\n'
                + '\n'.join('    ' + l for l in corpo)
                + f'\nsai:\n    {sai}\n}}\n#undef SALVA_W\n')

    # ------------------------------------------------ bandeiras depois de chamada
    # Pela ABI do ARM as bandeiras NAO sobrevivem a uma chamada: quem chama nao
    # conta com elas depois, e quem e chamado nao as le na entrada. Entao SALVA_CH
    # nao grava fn/fz/fc/fv (e o compilador pode descartar as contas de bandeira que
    # ninguem le). Recarregar depois da chamada so e preciso quando o codigo seguinte
    # LE bandeira antes de reescreve-la -- caso dos ajudantes __aeabi_cdcmple /
    # __aeabi_cfcmple, que devolvem o resultado nas bandeiras. Varredura conservadora:
    # desvio, retorno ou fim de janela antes de uma escrita completa = recarrega.
    MATA_NZCV = {'cmp', 'cmn', 'adds', 'subs', 'rsbs', 'negs'}
    LE_C = {'adc', 'adcs', 'sbc', 'sbcs', 'rsc', 'rscs', 'rrx', 'rrxs', 'mrs'}

    def _bandeiras_vivas(self, k):
        insns = self._insns_atual
        prox = insns[k].address + insns[k].size
        for j in range(k + 1, min(len(insns), k + 41)):
            i = insns[j]
            if i.address != prox:
                return True                     # descontinuo: nao sei quem segue
            prox = i.address + i.size
            if i.cc not in (A.ARM_CC_AL, A.ARM_CC_INVALID):
                return True                     # condicional le as bandeiras
            base = i.mnemonic.split('.')[0].lower()
            if base == 'it' or base in self.LE_C or 'rrx' in i.op_str:
                return True
            if base in ('bl', 'blx'):
                return False                    # outra chamada: as bandeiras de agora morrem nela
            if base in self.MATA_NZCV or (base == 'vmrs' and i.op_str.lower().startswith('apsr_nzcv')):
                return False
            if self.termina(i) or base in ('bx', 'tbb', 'tbh', 'cbz', 'cbnz', 'svc', 'udf', 'bkpt'):
                return True
            if 'pc' in i.op_str.split(',')[0]:
                return True                     # escrita em pc
        return True

    def bandeiras_vivas_apos(self, i):
        k = self._indice_atual.get(i.address)
        if k is None:
            return True
        v = self._vivas_cache.get(k)
        if v is None:
            v = self._vivas_cache[k] = self._bandeiras_vivas(k)
        self.n_chamadas[v] += 1
        return v

    def termina(self, i):
        """a instrucao incondicional nunca cai na seguinte?"""
        if i.cc not in (A.ARM_CC_AL, A.ARM_CC_INVALID):
            return False
        n = i.insn_name()
        if n in ('b', 'bx', 'tbb', 'tbh', 'udf'):
            return True
        if n == 'bl' and ual.parse(i.op_str)[0].v in self.semretorno:
            return True
        ops = ual.parse(i.op_str)
        plano = []
        for o in ops:
            plano.extend(o.regs if isinstance(o, Lista) else [o])
        if n in ('pop', 'ldm', 'ldmib', 'ldmda', 'ldmdb') and any(isinstance(o, Reg) and o.tipo == 'r' and o.n == 15 for o in plano[(0 if n == 'pop' else 1):]):
            return True
        if ops and isinstance(ops[0], Reg) and ops[0].tipo == 'r' and ops[0].n == 15 and n not in (
                'str', 'strb', 'strh', 'cmp', 'cmn', 'tst', 'teq', 'push', 'stm', 'stmdb', 'stmib', 'stmda', 'bl', 'blx'):
            return True
        return False
