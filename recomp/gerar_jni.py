"""Gera runtime/jni_auto.c:
 - a tabela JNINativeInterface do jogo (233 enderecos-ponte, ordem do jni.h)
 - as familias regulares: Call*Method[V|A], CallNonvirtual*, CallStatic*,
   Get/Set*Field, GetStatic/SetStatic*Field, New*Array,
   Get/Release*ArrayElements, Get/Set*ArrayRegion
 - a tabela JNIInvokeInterface (JavaVM) do jogo
 - as funcoes Java_* exportadas para o Java (ARM64), que chamam o jogo
"""
import json, os, re

AQUI = os.path.dirname(os.path.abspath(__file__))
import caminhos
JNI_H = os.path.join(caminhos.NDK_SYSROOT_INC, 'jni.h')

TIPOS = {'Object': ('L', 'jobject'), 'Boolean': ('Z', 'jboolean'), 'Byte': ('B', 'jbyte'), 'Char': ('C', 'jchar'),
         'Short': ('S', 'jshort'), 'Int': ('I', 'jint'), 'Long': ('J', 'jlong'), 'Float': ('F', 'jfloat'),
         'Double': ('D', 'jdouble'), 'Void': ('V', 'void')}


def membros():
    t = open(JNI_H).read()
    i = t.index('struct JNINativeInterface {'); j = t.index('};', i)
    env = re.findall(r'\(\*(\w+)\)\s*\(', t[i:j])
    i = t.index('struct JNIInvokeInterface {'); j = t.index('};', i)
    vm = re.findall(r'\(\*(\w+)\)', t[i:j])
    return env, vm


def ret_de(letra, expr):
    return {'L': f'ret32(c, jh_local({expr}));', 'Z': f'ret32(c, (uint8_t)({expr}));', 'B': f'ret32(c, (uint32_t)(int32_t)({expr}));',
            'C': f'ret32(c, (uint16_t)({expr}));', 'S': f'ret32(c, (uint32_t)(int32_t)({expr}));', 'I': f'ret32(c, (uint32_t)({expr}));',
            'J': f'ret64(c, (uint64_t)({expr}));', 'F': f'retf(c, {expr});', 'D': f'retd(c, {expr});', 'V': f'{expr};'}[letra]


def familia(nome):
    """devolve o corpo C se o nome for de uma familia regular"""
    m = re.fullmatch(r'Call(Nonvirtual|Static)?(\w+?)Method([VA]?)', nome)
    if m and m.group(2) in TIPOS:
        tipo_chamada, T, var = m.group(1), m.group(2), m.group(3)
        L = TIPOS[T][0]
        modo = {'': 0, 'V': 1, 'A': 2}[var]
        linhas = ['JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);']
        if tipo_chamada == 'Static':
            linhas.append('jclass alvo = jh_obj(arg32(&a));')
        else:
            linhas.append('jobject alvo = jh_obj(arg32(&a));')
            if tipo_chamada == 'Nonvirtual':
                linhas.append('jclass kl = jh_obj(arg32(&a));')
        linhas.append('const char *sig; jmethodID m = jh_id(arg32(&a), &sig);')
        linhas.append(f'uint32_t ptr = {"arg32(&a)" if modo else "0"};')
        linhas.append(f'jvalue v[64]; jh_args(sig, {modo}, &a, ptr, v);')
        if tipo_chamada == 'Static':
            chamada = f'(*e)->CallStatic{T}MethodA(e, alvo, m, v)'
        elif tipo_chamada == 'Nonvirtual':
            chamada = f'(*e)->CallNonvirtual{T}MethodA(e, alvo, kl, m, v)'
        else:
            chamada = f'(*e)->Call{T}MethodA(e, alvo, m, v)'
        linhas.append(ret_de(L, chamada))
        return '\n    '.join(linhas)
    m = re.fullmatch(r'(Get|Set)(Static)?(\w+?)Field', nome)
    if m and m.group(3) in TIPOS:
        gs, est, T = m.group(1), m.group(2), m.group(3)
        L, ct = TIPOS[T]
        linhas = ['JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);',
                  f'{"jclass" if est else "jobject"} alvo = jh_obj(arg32(&a));',
                  'jfieldID f = jh_id(arg32(&a), NULL);']
        pre = 'Static' if est else ''
        if gs == 'Get':
            linhas.append(ret_de(L, f'(*e)->Get{pre}{T}Field(e, alvo, f)'))
        else:
            val = {'L': 'jh_obj(arg32(&a))', 'J': '(jlong)arg64(&a)', 'D': 'argd(&a)', 'F': 'argf(&a)'}.get(L, f'({ct})arg32(&a)')
            linhas.append(f'(*e)->Set{pre}{T}Field(e, alvo, f, {val});')
        return '\n    '.join(linhas)
    m = re.fullmatch(r'New(\w+)Array', nome)
    if m and m.group(1) in TIPOS and m.group(1) not in ('Object', 'Void'):
        return f'JNIEnv *e = jh_env(); ret32(c, jh_local((*e)->New{m.group(1)}Array(e, (jsize)c->r[1])));'
    m = re.fullmatch(r'(Get|Set)(\w+)ArrayRegion', nome)
    if m and m.group(2) in TIPOS:
        gs, T = m.group(1), m.group(2)
        ct = TIPOS[T][1]
        return (f'JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);\n    '
                f'uint32_t arr = arg32(&a), ini = arg32(&a), n = arg32(&a), buf = arg32(&a);\n    '
                f'(*e)->{gs}{T}ArrayRegion(e, jh_obj(arr), (jsize)ini, (jsize)n, ({ct} *)G2H(buf));')
    m = re.fullmatch(r'Get(\w+)ArrayElements', nome)
    if m and m.group(1) in TIPOS:
        T = m.group(1); ct = TIPOS[T][1]
        return (f'JNIEnv *e = jh_env(); jarray arr = jh_obj(c->r[1]);\n    '
                f'jsize n = (*e)->GetArrayLength(e, arr);\n    '
                f'uint32_t g = heap_malloc((uint32_t)n * sizeof({ct}) + 8);\n    '
                f'(*e)->Get{T}ArrayRegion(e, arr, 0, n, ({ct} *)G2H(g));\n    '
                f'if (c->r[2]) g_mem[c->r[2]] = 1;\n    ret32(c, g);')
    m = re.fullmatch(r'Release(\w+)ArrayElements', nome)
    if m and m.group(1) in TIPOS:
        T = m.group(1); ct = TIPOS[T][1]
        return (f'JNIEnv *e = jh_env(); jarray arr = jh_obj(c->r[1]);\n    '
                f'if (c->r[3] != JNI_ABORT) {{ jsize n = (*e)->GetArrayLength(e, arr); (*e)->Set{T}ArrayRegion(e, arr, 0, n, ({ct} *)G2H(c->r[2])); }}\n    '
                f'if (c->r[3] != JNI_COMMIT) heap_free(c->r[2]);')
    return None


def java_nativos():
    nativos = json.load(open(os.path.join(AQUI, 'nativos.json')))
    exps = json.load(open(os.path.join(AQUI, 'saida', 'exportados_jogo.json')))
    por_nome = {}
    for cls, met, sig, est in nativos:
        mang = 'Java_' + cls.replace('_', '_1').replace('/', '_') + '_' + met.replace('_', '_1')
        por_nome[mang] = (sig, est)
    saida = []
    for nome, ad in sorted(exps.items()):
        if not nome.startswith('Java_'):
            continue
        if nome not in por_nome:
            saida.append(f'/* {nome}: sem assinatura no dex */')
            continue
        sig, est = por_nome[nome]
        params = re.findall(r'\[*(?:L[^;]+;|[ZBCSIJFD])', sig[1:sig.index(')')])
        ret = sig[sig.index(')') + 1:]
        C = {'Z': 'jboolean', 'B': 'jbyte', 'C': 'jchar', 'S': 'jshort', 'I': 'jint', 'J': 'jlong', 'F': 'jfloat', 'D': 'jdouble', 'V': 'void'}
        rct = C.get(ret, 'jobject')
        decl = ', '.join(['JNIEnv *e', 'jclass self' if est else 'jobject self'] +
                         [f'{C.get(p, "jobject") if p[0] != "[" else "jobject"} p{k}' for k, p in enumerate(params)])
        corpo = ['rt_garante();', 'jh_define_env(e);', 'int marca = jh_marca_locais();',
                 'uint32_t a[24]; int n = 0;', 'a[n++] = jh_env_jogo();', 'a[n++] = jh_local(self);']
        for k, p in enumerate(params):
            if p in ('J', 'D'):
                corpo.append('if (n & 1) a[n++] = 0;')
                corpo.append(f'{{ uint64_t q; memcpy(&q, &p{k}, 8); a[n++] = (uint32_t)q; a[n++] = (uint32_t)(q >> 32); }}')
            elif p == 'F':
                corpo.append(f'{{ uint32_t w; memcpy(&w, &p{k}, 4); a[n++] = w; }}')
            elif p in ('Z', 'B', 'C', 'S', 'I'):
                corpo.append(f'a[n++] = (uint32_t)(int32_t)p{k};')
            else:
                corpo.append(f'a[n++] = jh_local(p{k});')
        corpo.append(f'CPU *c = cpu_atual();')
        corpo.append(f'uint32_t r = jogo_chama_v(c, 0x{ad:08x}u, n, a); (void)r;')
        if rct == 'void':
            corpo.append('jh_solta_locais(marca);')
        elif rct == 'jobject':
            corpo.append('jobject o = jh_obj(r); if (o) o = (*e)->NewLocalRef(e, o);')
            corpo.append('jh_solta_locais(marca);')
            corpo.append('return o;')
        elif rct in ('jlong', 'jdouble'):
            corpo.append(f'uint64_t q = r | (uint64_t)c->r[1] << 32; {rct} v; memcpy(&v, &q, 8);')
            corpo.append('jh_solta_locais(marca);'); corpo.append('return v;')
        elif rct == 'jfloat':
            corpo.append('float v; memcpy(&v, &r, 4); jh_solta_locais(marca); return v;')
        else:
            corpo.append(f'jh_solta_locais(marca); return ({rct})r;')
        saida.append(f'JNIEXPORT {rct} JNICALL {nome}({decl}) {{\n    ' + '\n    '.join(corpo) + '\n}\n')
    return saida


def main():
    env, vm = membros()
    feitas = set(re.findall(r'void J_(\w+)\(CPU \*c\)', open(os.path.join(AQUI, 'runtime', 'jni_ponte.c'), encoding='utf-8').read()))
    linhas = ['/* GERADO por gerar_jni.py */', '#ifndef _WIN32', '#include "jni_ponte.h"', '#include <string.h>', '',
              'void rt_garante(void);', '']
    auto = 0
    stubs = 0
    for n in env:
        if n in feitas:
            continue
        corpo = familia(n)
        if corpo:
            auto += 1
            linhas.append(f'void J_{n}(CPU *c) {{\n    {corpo}\n}}\n')
        else:
            stubs += 1
            linhas.append(f'void J_{n}(CPU *c) {{ (void)c; rt_fatal("JNI nao implementado: {n}"); }}\n')
    for n in env:
        if n in feitas:
            linhas.append(f'void J_{n}(CPU *c);')
    linhas.append('\nuint32_t jni_tabela_jogo(void) {\n    static uint32_t tab;\n    if (tab) return tab;\n'
                  f'    tab = heap_calloc({4 + len(env)}, 4);\n    uint32_t *t = (uint32_t *)G2H(tab);')
    for k, n in enumerate(env):
        linhas.append(f'    t[{4 + k}] = ponte_nova(J_{n}, "JNI:{n}");')
    linhas.append('    return tab;\n}\n')
    for n in vm:
        linhas.append(f'void V_{n}(CPU *c);')
    linhas.append('uint32_t jni_tabela_vm_jogo(void) {\n    static uint32_t tab;\n    if (tab) return tab;\n'
                  f'    tab = heap_calloc({3 + len(vm)}, 4);\n    uint32_t *t = (uint32_t *)G2H(tab);')
    for k, n in enumerate(vm):
        linhas.append(f'    t[{3 + k}] = ponte_nova(V_{n}, "JavaVM:{n}");')
    linhas.append('    return tab;\n}\n')
    linhas.extend(java_nativos())
    linhas.append('#endif')
    open(os.path.join(AQUI, 'runtime', 'jni_auto.c'), 'w').write('\n'.join(linhas))
    print(f'JNI: {len(env)} funcoes, {len(feitas)} a mao, {auto} geradas, {stubs} stubs')


if __name__ == '__main__':
    main()
