"""Gera runtime/pontes_auto.c: pontes das importacoes de assinatura simples.

Tipos:  v void | i int32 | u uint32 | z size_t | p ponteiro do jogo (entra)
        P ponteiro que SAI e aponta para memoria do jogo | f float | d double
        l int64 | L uint64
"""
import os

SIG = '''
d acos d | d asin d | d atan d | d atan2 dd | d cbrt d | d ceil d | d cos d | d cosh d
d exp d | d floor d | d fmod dd | d log d | d log10 d | d pow dd | d sin d | d sinh d
d sqrt d | d tan d | d tanh d
f acosf f | f asinf f | f atanf f | f atan2f ff | f cbrtf f | f ceilf f | f cosf f
f floorf f | f fmodf ff | f logf f | f powf ff | f sinf f | f tanf f
i abs i
i isalnum i | i isalpha i | i iscntrl i | i islower i | i isprint i | i ispunct i
i isspace i | i isupper i | i isxdigit i | i tolower i | i toupper i
i iswalpha u | i iswcntrl u | i iswdigit u | i iswlower u | i iswprint u | i iswpunct u
i iswspace u | i iswupper u | i iswxdigit u | u towlower u | u towupper u
u btowc i | i wctob u | u wctype p | i iswctype uu
z strlen p | i strcmp pp | i strncmp ppz | i strcasecmp pp | i strncasecmp ppz
P strcpy pp | P strncpy ppz | P strcat pp | P strncat ppz | P stpcpy pp
P strchr pi | P strrchr pi | P strstr pp | P strcasestr pp | P strpbrk pp
z strcspn pp | i strcoll pp | z strxfrm ppz | P strtok pp
P memcpy ppz | P memmove ppz | P memset piz | P memchr piz | i memcmp ppz
i atoi p | d atof p
z wcslen p | i wcscoll pp | z wcsxfrm ppz
P wmemchr puz | i wmemcmp ppz | P wmemcpy ppz | P wmemmove ppz | P wmemset puz
i rand v | v srand u
i close i | i dup i | i access pi | i mkdir pu | i rmdir p | i unlink p | i remove p
i rename pp | i chdir p | i fsync i | i ftruncate ii | i getpid v | i kill ii
i lseek iii | l lseek64 ili
i raise i | i sched_yield v | i usleep u | i getpagesize v | i gethostname pz
i open piu | i read ipz | i write ipz | i pread ipzi | i pwrite ipzi | i poll pui
i isatty i
'''


POSIX = {'poll', 'pread', 'pwrite', 'kill', 'gethostname'}
CAMINHOS = {'access', 'mkdir', 'rmdir', 'unlink', 'remove', 'chdir', 'open', 'rename'}
POSIX_ANTIGO = {'fsync', 'getpagesize', 'sched_yield', 'usleep',
         'lseek64', 'ftruncate', 'getpid', 'isatty', 'dup', 'close', 'read', 'write', 'open', 'lseek', 'access',
         'mkdir', 'rmdir', 'unlink', 'chdir', 'srand', 'rand'}


def args_c(tipos):
    out = []
    for k, t in enumerate(tipos):
        if t == 'v':
            continue
        x = {'i': '(int32_t)arg32(&a)', 'u': 'arg32(&a)', 'z': '(size_t)arg32(&a)', 'p': 'G2H(arg32(&a))',
             'f': 'argf(&a)', 'd': 'argd(&a)', 'l': '(int64_t)arg64(&a)', 'L': 'arg64(&a)'}[t]
        ctipo = {'i': 'int32_t', 'u': 'uint32_t', 'z': 'size_t', 'p': 'void *', 'f': 'float', 'd': 'double',
                 'l': 'int64_t', 'L': 'uint64_t'}[t]
        out.append((f'a{k}', ctipo, x))
    return out


def gerar():
    linhas = ['/* GERADO por pontes.py */', '#include "runtime.h"', '#include <math.h>', '#include <string.h>',
              '#include <stdlib.h>', '#include <stdio.h>', '#include <signal.h>', '#include <ctype.h>', '#include <wctype.h>', '#include <wchar.h>',
              '#include <fcntl.h>', '#include "compat_pc.h"',
              'const char *rt_caminho(const char *p, char *buf, size_t n);   /* caminho.c */',
              '#include <sys/stat.h>', '#ifndef _WIN32', '#include <unistd.h>', '#include <sched.h>', '#include <poll.h>', '#endif', '']
    nomes = []
    for item in SIG.replace('\n', '|').split('|'):
        item = item.strip()
        if not item:
            continue
        ret, nome, tipos = item.split()
        nomes.append(nome)
        av = args_c(tipos)
        corpo = ['    Args a = args_de(c); (void)a;']
        for k, (v, ct, x) in enumerate(av):
            # caminhos: sem diferenciar maiusculas (runtime/caminho.c; o jogo veio do SHIELD)
            if nome in CAMINHOS and (k == 0 or nome == 'rename') and ct == 'void *':
                corpo.append(f'    char _b{k}[1024]; const char * {v} = rt_caminho({x}, _b{k}, sizeof _b{k});')
                continue
            corpo.append(f'    {ct} {v} = {x};')
        # casts por funcao (tipos exatos da libc)
        chamada_args = ', '.join(v for v, _, _ in av)
        chamada = f'{nome}({chamada_args})'
        if nome in ('wmemchr', 'wmemset'):
            chamada = f'{nome}(a0, (wchar_t)a1, a2)'
        if nome in ('iswctype',):
            chamada = f'iswctype((wint_t)a0, (wctype_t)a1)'
        if nome == 'open':
            chamada = f'open(a0, a1, (int)a2)'
        if nome == 'poll':
            chamada = f'poll((struct pollfd *)a0, (nfds_t)a1, a2)'
        if ret == 'v':
            corpo.append(f'    {chamada};')
        elif ret in 'iu':
            corpo.append(f'    ret32(c, (uint32_t)({chamada}));')
        elif ret == 'z':
            corpo.append(f'    ret32(c, (uint32_t)({chamada}));')
        elif ret == 'P':
            corpo.append(f'    ret32(c, H2G({chamada}));')
        elif ret == 'f':
            corpo.append(f'    retf(c, {chamada});')
        elif ret == 'd':
            corpo.append(f'    retd(c, {chamada});')
        elif ret in 'lL':
            corpo.append(f'    ret64(c, (uint64_t)({chamada}));')
        so_posix = nome in POSIX
        if so_posix:
            linhas.append('#ifdef _WIN32')
            linhas.append(f'void I_{nome}(CPU *c) {{ (void)c; rt_fatal("{nome} no PC"); }}')
            linhas.append('#else')
        linhas.append(f'void I_{nome}(CPU *c) {{\n' + '\n'.join(corpo) + '\n}\n')
        if so_posix:
            linhas.append('#endif')
    open(os.path.join(os.path.dirname(os.path.abspath(__file__)), 'runtime', 'pontes_auto.c'), 'w').write('\n'.join(linhas))
    return nomes


if __name__ == '__main__':
    n = gerar()
    print(len(n), 'pontes automaticas')
