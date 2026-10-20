"""Monta um Lossless.dll DE TESTE (nao e o do Lossless Scaling) para validar a geracao de
quadros sem o arquivo do usuario.

Mesmos recursos RCDATA que o runtime procura (id do shader + 49), cada um com um compute
shader SPIR-V PROPRIO, com os bindings na mesma ordem de tipos que cada passe da cadeia
declara (lsfg_vk.cpp, igual ao Eden). Os numeros de binding vem ESPALHADOS (1, 4, 7...)
de proposito, para exercitar a renumeracao do adota_spirv.

Os passes so escrevem zero nas saidas; o "generate" mistura os dois quadros 50/50. Na
tela isso vira um meio-termo borrado entre os quadros: prova o caminho inteiro (PE,
pipelines, AHardwareBuffer, fences, swapchain), nao a qualidade do LSFG.

    python lsfg_teste/fazer_dll_teste.py  ->  lsfg_teste/Lossless_teste.dll
"""
import os, subprocess, sys

AQUI = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.dirname(AQUI))
import caminhos
GLSLC = caminhos.exe(caminhos.NDK_SHADERS, 'glslc')
SPIRV_VAL = caminhos.exe(caminhos.NDK_SHADERS, 'spirv-val')
LLVM = caminhos.LLVM_PC
U, S, T, I = 'ubo', 'sampler', 'textura', 'imagem'

# (id, [(quantidade, tipo)...]) - a mesma tabela dos LsfgPass do lsfg_vk.cpp
PASSES = {
    255: [(1, U), (1, S), (1, T), (7, I)],                       # mipmaps
    256: [(1, U), (2, S), (5, T), (1, I)],                       # generate
    290: [(1, S), (1, T), (1, I)], 291: [(1, S), (1, T), (1, I)],
    292: [(1, S), (1, T), (2, I)], 293: [(1, S), (2, T), (2, I)],   # alpha
    298: [(1, S), (6, T), (2, I)], 299: [(1, S), (2, T), (2, I)], 300: [(1, S), (2, T), (2, I)],
    301: [(1, S), (2, T), (2, I)], 302: [(1, U), (1, S), (2, T), (6, I)],   # beta
    280: [(1, U), (2, S), (5, T), (3, I)],                       # gamma[0] = delta[0]
    282: [(1, S), (3, T), (2, I)], 283: [(1, S), (2, T), (2, I)], 284: [(1, S), (2, T), (2, I)],
    285: [(1, U), (2, S), (4, T), (1, I)],                       # gamma
    286: [(1, S), (3, T), (2, I)], 287: [(1, S), (2, T), (2, I)], 288: [(1, S), (2, T), (2, I)],
    289: [(1, U), (2, S), (4, T), (1, I)], 281: [(1, U), (2, S), (6, T), (1, I)],
    294: [(1, S), (1, T), (1, I)], 295: [(1, S), (1, T), (1, I)], 296: [(1, S), (1, T), (1, I)],
    297: [(1, U), (2, S), (2, T), (1, I)],                       # delta
}


def glsl(id_, layout):
    linhas = ['#version 450', 'layout(local_size_x = 8, local_size_y = 8) in;']
    b = 1
    nomes = {U: [], S: [], T: [], I: []}
    for n, tipo in layout:
        for _ in range(n):
            nome = f'{tipo}{len(nomes[tipo])}'
            nomes[tipo].append(nome)
            if tipo == U:
                linhas.append(f'layout(set = 0, binding = {b}) uniform U{b} {{ uvec2 off; uint fi, fis, ack, hdr; float inv_escala, instante, limiar; }} {nome};')
            elif tipo == S:
                linhas.append(f'layout(set = 0, binding = {b}) uniform sampler {nome};')
            elif tipo == T:
                linhas.append(f'layout(set = 0, binding = {b}) uniform texture2D {nome};')
            else:
                linhas.append(f'layout(set = 0, binding = {b}) writeonly uniform image2D {nome};')
            b += 3                                    # espalhado: forca a renumeracao
    # o runtime despacha como o Eden: cada grupo cobre um bloco de 2^shift pixels por eixo
    # (mipmaps 64, generate 16, ultimo beta 32, o resto 8); cada invocacao faz o seu pedaco
    lado = {255: 64, 256: 16, 302: 32}.get(id_, 8)
    linhas.append('void corpo(ivec2 p) {')
    if id_ == 256:
        # generate: textura0/1 = os dois quadros; mistura 50/50 na saida
        linhas.append('  ivec2 t = imageSize(imagem0);')
        linhas.append('  if (p.x >= t.x || p.y >= t.y) return;')
        linhas.append('  vec2 uv = (vec2(p) + 0.5) / vec2(t);')
        linhas.append('  vec4 a = textureLod(sampler2D(textura0, sampler0), uv, 0.0);')
        linhas.append('  vec4 c = textureLod(sampler2D(textura1, sampler0), uv, 0.0);')
        linhas.append('  imageStore(imagem0, p, mix(a, c, 0.5));')
    else:
        for nome in nomes[I]:
            linhas.append(f'  if (all(lessThan(p, imageSize({nome})))) imageStore({nome}, p, vec4(0.0));')
    # toca nos outros recursos para o compilador nao os descartar
    usa = []
    for nome in nomes[U]:
        usa.append(f'{nome}.instante')
    for k, nome in enumerate(nomes[T]):
        usa.append(f'texelFetch(sampler2D({nome}, {nomes[S][0] if nomes[S] else "x"}), ivec2(0), 0).x')
    for nome in nomes[S][1:]:   # todo sampler usado: o otimizador descarta binding sem uso
        usa.append(f'textureLod(sampler2D({nomes[T][0]}, {nome}), vec2(0.5), 0.0).x')
    if usa:
        linhas.append(f'  if (p.x < 0) {{ float z = {" + ".join(usa)}; if (z == 12345.0) return; }}')
    linhas.append('}')
    passo = lado // 8
    linhas.append('void main() {')
    linhas.append(f'  ivec2 base = ivec2(gl_WorkGroupID.xy) * {lado} + ivec2(gl_LocalInvocationID.xy) * {passo};')
    linhas.append(f'  for (int j = 0; j < {passo}; j++) for (int i = 0; i < {passo}; i++) corpo(base + ivec2(i, j));')
    linhas.append('}')
    return '\n'.join(linhas) + '\n'


def main():
    obra = os.path.join(AQUI, 'obra')
    os.makedirs(obra, exist_ok=True)
    rc = []
    for id_, layout in sorted(PASSES.items()):
        src = os.path.join(obra, f's{id_}.comp')
        spv = os.path.join(obra, f's{id_}.spv')
        open(src, 'w').write(glsl(id_, layout))
        r = subprocess.run([GLSLC, '--target-env=vulkan1.2', '-O', src, '-o', spv], capture_output=True, text=True)
        if r.returncode:
            sys.exit(f'glslc {id_}:\n{r.stderr}')
        r = subprocess.run([SPIRV_VAL, '--target-env', 'vulkan1.2', spv], capture_output=True, text=True)
        if r.returncode:
            sys.exit(f'spirv-val {id_}:\n{r.stderr}')
        rc.append(f'{id_ + 49} RCDATA "{spv.replace(os.sep, "/")}"')
    # recheio para o arquivo passar de 1 MB (o Java so aceita Lossless.dll > 1 MB)
    recheio = os.path.join(obra, 'recheio.bin')
    open(recheio, 'wb').write(b'\0' * (1536 * 1024))
    rc.append(f'1 RCDATA "{recheio.replace(os.sep, "/")}"')
    open(os.path.join(obra, 'teste.rc'), 'w').write('\n'.join(rc) + '\n')
    subprocess.run([os.path.join(LLVM, 'llvm-rc.exe'), '/fo', os.path.join(obra, 'teste.res'), os.path.join(obra, 'teste.rc')], check=True)
    dll = os.path.join(AQUI, 'Lossless_teste.dll')
    subprocess.run([os.path.join(LLVM, 'lld-link.exe'), '/dll', '/noentry', '/machine:x64', f'/out:{dll}',
                    os.path.join(obra, 'teste.res')], check=True)
    print(f'{len(PASSES)} shaders compilados e validados (spirv-val) -> {dll} ({os.path.getsize(dll) // 1024} KB)')


if __name__ == '__main__':
    main()
