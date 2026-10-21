"""Desenha as imagens dos controles na tela (assets/controles/pad_*.png).

Arte propria do projeto (Pillow), no visual do codec do MGS2: vidro escuro, aro verde e
letras com a cor de cada botao. Mesmos nomes e tamanhos que o ControleNaTela.java espera.
Os analogicos sao desenhados pelo proprio Java (nao tem imagem).

    python recomp/java_tela/gerar_botoes.py   ->  recomp/java_tela/assets/controles/
"""
import os
from PIL import Image, ImageDraw, ImageFilter, ImageFont

AQUI = os.path.dirname(os.path.abspath(__file__))
SAIDA = os.path.join(AQUI, 'assets', 'controles')
SS = 4                                            # superamostragem (bordas suaves)
VERDE = (127, 214, 160)
FUNDO = (8, 16, 12)
CORES = {'A': (96, 200, 92), 'B': (226, 84, 72), 'X': (78, 150, 236), 'Y': (240, 196, 60)}


def fonte(px):
    for nome in ('arialbd.ttf', 'DejaVuSans-Bold.ttf', 'LiberationSans-Bold.ttf', 'Arial Bold.ttf'):
        try:
            return ImageFont.truetype(nome, px)
        except OSError:
            continue
    return ImageFont.load_default()


def tela(w, h):
    return Image.new('RGBA', (w * SS, h * SS), (0, 0, 0, 0))


def finaliza(im, w, h, nome):
    im = im.resize((w, h), Image.LANCZOS)
    im.save(os.path.join(SAIDA, nome + '.png'), optimize=True)


def vidro(d, caixa, raio, aro, preenche=(*FUNDO, 175), largura=3):
    """forma de vidro escuro com aro colorido e um brilho no topo"""
    x0, y0, x1, y1 = caixa
    d.rounded_rectangle(caixa, raio, fill=preenche, outline=(*aro, 235), width=largura * SS)
    brilho = (x0 + largura * SS * 2, y0 + largura * SS * 2, x1 - largura * SS * 2, y0 + (y1 - y0) * 0.45)
    d.rounded_rectangle(brilho, max(1, raio - largura * SS * 2), fill=(255, 255, 255, 22))


def texto(d, cx, cy, t, px, cor):
    f = fonte(px)
    b = d.textbbox((0, 0), t, font=f)
    x, y = cx - (b[0] + b[2]) / 2, cy - (b[1] + b[3]) / 2
    d.text((x + SS, y + SS * 1.5), t, font=f, fill=(0, 0, 0, 140))
    d.text((x, y), t, font=f, fill=(*cor, 255))


def face(nome, letra):
    w = h = 80
    im = tela(w, h); d = ImageDraw.Draw(im)
    m = 4 * SS
    vidro(d, (m, m, w * SS - m, h * SS - m), (w * SS) // 2, CORES[letra])
    texto(d, w * SS / 2, h * SS / 2, letra, 40 * SS, CORES[letra])
    finaliza(im, w, h, nome)


def ombro(nome, rot):
    w, h = 218, 92
    im = tela(w, h); d = ImageDraw.Draw(im)
    m = 5 * SS
    vidro(d, (m, m, w * SS - m, h * SS - m), 34 * SS, VERDE)
    texto(d, w * SS / 2, h * SS / 2, rot, 38 * SS, VERDE)
    finaliza(im, w, h, nome)


def gatilho(nome, rot):
    w, h = 88, 169
    im = tela(w, h); d = ImageDraw.Draw(im)
    m = 5 * SS
    vidro(d, (m, m, w * SS - m, h * SS - m), 30 * SS, VERDE)
    texto(d, w * SS / 2, h * SS * 0.42, rot, 34 * SS, VERDE)
    for k in range(3):                                   # sulcos de apoio do dedo
        y = h * SS * (0.62 + 0.09 * k)
        d.line((w * SS * 0.3, y, w * SS * 0.7, y), fill=(*VERDE, 110), width=3 * SS)
    finaliza(im, w, h, nome)


def clique(nome, rot):
    """L3/R3 (apertar o analogico): redondo, com o anel do topo do analogico em volta do rotulo"""
    w = h = 80
    im = tela(w, h); d = ImageDraw.Draw(im)
    m = 4 * SS
    vidro(d, (m, m, w * SS - m, h * SS - m), (w * SS) // 2, VERDE)
    r = 25 * SS
    d.ellipse((w * SS / 2 - r, h * SS / 2 - r, w * SS / 2 + r, h * SS / 2 + r), outline=(*VERDE, 120), width=2 * SS)
    texto(d, w * SS / 2, h * SS / 2, rot, 30 * SS, VERDE)
    finaliza(im, w, h, nome)


def menu(nome, w, h, desenho):
    im = tela(w, h); d = ImageDraw.Draw(im)
    m = 5 * SS
    vidro(d, (m, m, w * SS - m, h * SS - m), (min(w, h) * SS) // 2, VERDE)
    desenho(d, w * SS / 2, h * SS / 2)
    finaliza(im, w, h, nome)


def start(d, cx, cy):                                    # triangulo "play"
    s = 15 * SS
    d.polygon([(cx - s * 0.7, cy - s), (cx - s * 0.7, cy + s), (cx + s, cy)], fill=(*VERDE, 255))


def back(d, cx, cy):                                     # duas janelas sobrepostas
    s = 11 * SS
    d.rectangle((cx - s - 4 * SS, cy - s, cx + s - 4 * SS, cy + s - 6 * SS), outline=(*VERDE, 255), width=3 * SS)
    d.rectangle((cx - s + 4 * SS, cy - s + 6 * SS, cx + s + 4 * SS, cy + s), fill=(*FUNDO, 255), outline=(*VERDE, 255), width=3 * SS)


def dpad(nome, aceso):
    w, h = 227, 230
    im = tela(w, h); d = ImageDraw.Draw(im)
    cx, cy = w * SS / 2, h * SS / 2
    braco, larg = 104 * SS, 70 * SS
    cruz = [(cx - larg / 2, cy - braco), (cx + larg / 2, cy - braco), (cx + larg / 2, cy - larg / 2),
            (cx + braco, cy - larg / 2), (cx + braco, cy + larg / 2), (cx + larg / 2, cy + larg / 2),
            (cx + larg / 2, cy + braco), (cx - larg / 2, cy + braco), (cx - larg / 2, cy + larg / 2),
            (cx - braco, cy + larg / 2), (cx - braco, cy - larg / 2), (cx - larg / 2, cy - larg / 2)]
    sombra = tela(w, h); ImageDraw.Draw(sombra).polygon(cruz, fill=(0, 0, 0, 120))
    im.alpha_composite(sombra.filter(ImageFilter.GaussianBlur(6 * SS)))
    d.polygon(cruz, fill=(*FUNDO, 185), outline=(*VERDE, 235), width=3 * SS)
    setas = {'cima': (0, -1), 'baixo': (0, 1), 'esq': (-1, 0), 'dir': (1, 0)}
    for lado, (vx, vy) in setas.items():
        px, py = cx + vx * braco * 0.62, cy + vy * braco * 0.62
        if lado == aceso:                                # braco apertado: preenchido de verde
            r = larg * 0.42
            d.rounded_rectangle((px - r, py - r, px + r, py + r), 10 * SS, fill=(*VERDE, 150))
        s = 13 * SS
        tri = [(px + vx * s, py + vy * s), (px - vy * s * 0.9 - vx * s * 0.6, py + vx * s * 0.9 - vy * s * 0.6),
               (px + vy * s * 0.9 - vx * s * 0.6, py - vx * s * 0.9 - vy * s * 0.6)]
        d.polygon(tri, fill=(*(FUNDO if lado == aceso else VERDE), 255))
    d.ellipse((cx - 14 * SS, cy - 14 * SS, cx + 14 * SS, cy + 14 * SS), outline=(*VERDE, 120), width=2 * SS)
    finaliza(im, w, h, nome)


def main():
    os.makedirs(SAIDA, exist_ok=True)
    for l in 'ABXY':
        face('pad_' + l.lower(), l)
    ombro('pad_lb', 'LB'); ombro('pad_rb', 'RB')
    gatilho('pad_lt', 'LT'); gatilho('pad_rt', 'RT')
    menu('pad_start', 86, 78, start); menu('pad_back', 83, 79, back)
    clique('pad_l3', 'L3'); clique('pad_r3', 'R3')
    dpad('pad_dpad', None)
    for lado in ('cima', 'baixo', 'esq', 'dir'):
        dpad('pad_dpad_' + lado, lado)
    print(len(os.listdir(SAIDA)), 'imagens em', SAIDA)


if __name__ == '__main__':
    main()
