"""Instrucao leve (o que o gerador usa), independente do capstone."""


class Ins:
    __slots__ = ('address', 'size', 'bytes', 'mnemonic', 'op_str', 'cc', 'nome')

    def __init__(self, address, size, bytes_, mnemonic, op_str, cc, nome):
        self.address, self.size, self.bytes = address, size, bytes_
        self.mnemonic, self.op_str, self.cc, self.nome = mnemonic, op_str, cc, nome

    def insn_name(self):
        return self.nome

    @classmethod
    def de(cls, i):
        return cls(i.address, i.size, bytes(i.bytes), i.mnemonic, i.op_str, i.cc, i.insn_name())
