"""Gera runtime/gl_auto.c: pontes de toda a API GLES 3.2 + extensoes do gl2ext.h.

Cada G_nome(CPU*) le os argumentos na convencao do jogo (softfp), converte
ponteiros (G2H) e chama a funcao real, obtida por eglGetProcAddress na
primeira chamada.  As funcoes com semantica especial (deslocamento em vez de
ponteiro, vetor de ponteiros, retorno de ponteiro, GLsync) ficam em
gl_manual.c: o gerador pula os nomes listados em ESPECIAIS.
Tambem gera a tabela nome -> ponte usada por eglGetProcAddress/dlsym.
"""
import os, re

AQUI = os.path.dirname(os.path.abspath(__file__))
import caminhos
INC = caminhos.NDK_SYSROOT_INC

ESPECIAIS = {
    'glGetString', 'glGetStringi', 'glShaderSource', 'glMapBufferRange', 'glMapBufferRangeEXT', 'glMapBufferOES',
    'glUnmapBuffer', 'glUnmapBufferOES', 'glFlushMappedBufferRange', 'glFlushMappedBufferRangeEXT',
    'glVertexAttribPointer', 'glVertexAttribIPointer', 'glDrawElements', 'glDrawElementsInstanced',
    'glDrawElementsInstancedEXT', 'glDrawElementsInstancedANGLE', 'glDrawElementsInstancedNV', 'glDrawRangeElements',
    'glGetPointerv', 'glGetPointervKHR', 'glGetVertexAttribPointerv', 'glGetBufferPointerv', 'glGetBufferPointervOES',
    'glFenceSync', 'glDeleteSync', 'glClientWaitSync', 'glWaitSync', 'glIsSync', 'glGetSynciv',
    'glFenceSyncAPPLE', 'glDeleteSyncAPPLE', 'glClientWaitSyncAPPLE', 'glWaitSyncAPPLE', 'glIsSyncAPPLE', 'glGetSyncivAPPLE',
    'glDebugMessageCallback', 'glDebugMessageCallbackKHR', 'glTransformFeedbackVaryings', 'glGetUniformIndices',
    'glBindBuffer', 'glBufferStorageEXT', 'glDrawElementsBaseVertex', 'glDrawElementsInstancedBaseVertex',
    'glDrawRangeElementsBaseVertex', 'glDrawElementsBaseVertexEXT', 'glDrawElementsInstancedBaseVertexEXT',
    'glDrawRangeElementsBaseVertexEXT', 'glDrawElementsBaseVertexOES', 'glDrawElementsInstancedBaseVertexOES',
    'glDrawRangeElementsBaseVertexOES', 'glMultiDrawElementsEXT', 'glMultiDrawElementsBaseVertexEXT',
    'glDrawElementsIndirect', 'glDrawArraysIndirect', 'glEGLImageTargetTexture2DOES', 'glEGLImageTargetRenderbufferStorageOES',
    'glTexImage2D', 'glTexSubImage2D', 'glTexImage3D', 'glTexSubImage3D', 'glCompressedTexImage2D',
    'glCompressedTexSubImage2D', 'glCompressedTexImage3D', 'glCompressedTexSubImage3D', 'glReadPixels',
    'glTexImage3DOES', 'glTexSubImage3DOES', 'glCompressedTexImage3DOES', 'glCompressedTexSubImage3DOES',
}

T64 = {'GLint64', 'GLuint64', 'GLint64EXT', 'GLuint64EXT'}
TPTR = {'GLintptr', 'GLsizeiptr', 'GLintptrEXT', 'GLsizeiptrEXT'}
TF = {'GLfloat', 'GLclampf'}


def prototipos():
    vistos = {}
    for arq in ('GLES3/gl32.h', 'GLES2/gl2ext.h'):
        t = open(os.path.join(INC, arq)).read()
        for m in re.finditer(r'GL_APICALL\s+(.+?)\s*GL_APIENTRY\s+(\w+)\s*\(([^;]*?)\);', t, re.S):
            ret, nome, params = m.group(1).strip(), m.group(2), ' '.join(m.group(3).split())
            if nome in vistos:
                continue
            ps = [] if params in ('void', '') else [p.strip() for p in params.split(',')]
            vistos[nome] = (ret, ps)
    return vistos


def tipo_param(p):
    """(tipo C sem nome, eh_ponteiro)"""
    m = re.match(r'(.*?)(\w+)\s*\[\d*\]$', p)
    if m:                                   # vetor como parametro: e ponteiro
        return m.group(1).strip() + ' *', True
    m = re.match(r'(.*?)(\w+)$', p)
    t = m.group(1).strip() if m and '*' not in m.group(2) else p
    return t, '*' in t


def main():
    protos = prototipos()
    linhas = ['/* GERADO por gerar_gl.py */', '#ifndef _WIN32', '#include "runtime.h"', '#include <EGL/egl.h>',
              '#define GL_GLEXT_PROTOTYPES', '#include <GLES3/gl32.h>', '#include <GLES2/gl2ext.h>', '#include <string.h>',
              '#include "gl_ponte.h"', '']
    nomes = []
    pulados = []
    for nome, (ret, ps) in sorted(protos.items()):
        if nome in ESPECIAIS:
            nomes.append(nome)
            continue
        tipos = [tipo_param(p) for p in ps]
        if any('GLDEBUGPROC' in t for t, _ in tipos) or ret not in ('void', 'GLuint', 'GLint', 'GLenum', 'GLboolean', 'GLbitfield', 'GLsizei', 'GLfloat'):
            pulados.append(nome)
            continue
        corpo = [f'static PFN_{nome} p; if (!p) p = (PFN_{nome})gl_proc("{nome}");' if False else
                 f'static {ret} (*p)({", ".join(t for t, _ in tipos) or "void"}); if (!p) p = gl_proc("{nome}");',
                 'Args a = args_de(c); (void)a;']
        args = []
        for k, (t, ptr) in enumerate(tipos):
            if ptr:
                corpo.append(f'{t} a{k} = ({t})G2H(arg32(&a));')
            elif t in T64:
                corpo.append(f'{t} a{k} = ({t})arg64(&a);')
            elif t in TPTR:
                corpo.append(f'{t} a{k} = ({t})(int32_t)arg32(&a);')
            elif t in TF:
                corpo.append(f'{t} a{k} = argf(&a);')
            elif t == 'GLsync':
                corpo.append(f'GLsync a{k} = gl_sync(arg32(&a));')
            elif t in ('GLeglImageOES', 'GLeglClientBufferEXT'):
                corpo.append(f'{t} a{k} = ({t})egl_obj(arg32(&a));')
            else:
                corpo.append(f'{t} a{k} = ({t})arg32(&a);')
            args.append(f'a{k}')
        ch = f'p({", ".join(args)})'
        if ret == 'void':
            corpo.append(f'{ch};')
        elif ret == 'GLfloat':
            corpo.append(f'retf(c, {ch});')
        else:
            corpo.append(f'ret32(c, (uint32_t){ch});')
        linhas.append(f'void G_{nome}(CPU *c) {{\n    ' + '\n    '.join(corpo) + '\n}')
        nomes.append(nome)
    # tabela nome -> ponte
    for n in nomes:
        if n in ESPECIAIS:
            linhas.append(f'void G_{n}(CPU *c);')
    linhas.append('\nstatic const struct { const char *nome; Ponte fn; } tabela_gl[] = {')
    for n in sorted(nomes):
        linhas.append(f'  {{"{n}", G_{n}}},')
    linhas.append('};\n')
    linhas.append('uint32_t gl_ponte_por_nome(const char *nome) {\n'
                  '    for (size_t k = 0; k < sizeof tabela_gl / sizeof tabela_gl[0]; k++)\n'
                  '        if (!strcmp(tabela_gl[k].nome, nome)) return ponte_nova(tabela_gl[k].fn, tabela_gl[k].nome);\n'
                  '    return egl_ponte_por_nome(nome);\n}\n')
    # as importadas diretas (I_glX) chamam a mesma ponte
    for n in nomes:
        linhas.append(f'void I_{n}(CPU *c) {{ G_{n}(c); }}')
    linhas.append('#endif')
    open(os.path.join(AQUI, 'runtime', 'gl_auto.c'), 'w').write('\n'.join(linhas))
    print(f'GL: {len(nomes)} pontes ({len(ESPECIAIS & set(nomes))} especiais a mao), puladas: {pulados}')


if __name__ == '__main__':
    main()
