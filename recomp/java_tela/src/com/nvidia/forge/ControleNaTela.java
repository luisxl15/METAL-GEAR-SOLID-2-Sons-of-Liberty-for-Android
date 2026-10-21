package com.nvidia.forge;

import android.content.Context;
import android.content.SharedPreferences;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Paint;
import android.graphics.RectF;
import android.view.HapticFeedbackConstants;
import android.view.MotionEvent;
import android.view.View;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

/**
 * Os controles na tela: porte para Java do ControleNaTela.kt do MGR (mesma
 * disposicao do controle do Xbox 360, mesmas imagens oficiais da Microsoft, que
 * aqui vem de assets/controles/ porque o APK do jogo ja tem os recursos
 * compilados). O toque vira bits do XInput em ControleMGS2.
 *
 * Multitoque: cada dedo e seguido pelo identificador, nao pela ordem.
 * No editor (editando = true): arrastar move, pinca redimensiona, nada vai ao jogo.
 */
public class ControleNaTela extends View {

    public static final int OPACIDADE_PADRAO = 62;
    public static final String[] NOMES = { "A", "B", "X", "Y", "LB", "RB", "LT", "RT", "START", "BACK",
            "L3", "R3", "DPAD", "ANALOG_E", "ANALOG_D" };

    public static String rotulo(String n) {
        switch (n) {
            case "DPAD": return Textos.t("Direcional");
            case "ANALOG_E": return Textos.t("Analógico esquerdo");
            case "ANALOG_D": return Textos.t("Analógico direito");
            case "START": return "Start";
            case "BACK": return "Back";
            default: return Textos.f("Botão %s", n);
        }
    }

    private static final class Area {
        final String nome; final Bitmap bitmap; final int bit; final Boolean gatilhoEsquerdo;
        final RectF caixa = new RectF();
        int dedo = -1;
        Area(String n, Bitmap b, int bit, Boolean g) { nome = n; bitmap = b; this.bit = bit; gatilhoEsquerdo = g; }
    }

    private static final class Personal {
        float cx = Float.NaN, cy = Float.NaN, escala = 1f;
    }

    public final boolean editando;
    private final List<Area> areas = new ArrayList<>();
    private final Bitmap dpad, dpadCima, dpadBaixo, dpadEsq, dpadDir;
    private int dpadFace = 0;
    private final RectF caixaDpad = new RectF(), caixaAnalogE = new RectF(), caixaAnalogD = new RectF();
    private final HashMap<String, RectF> padrao = new HashMap<>();
    private final HashMap<String, Personal> personal = new HashMap<>();
    private float larg, alt;
    private float escalaGeral = 1f;
    private int opacidade = OPACIDADE_PADRAO;
    private String selecionado;
    public interface AoSelecionar { void selecionou(String nome); }
    public AoSelecionar aoSelecionar;

    private int dedoDpad = -1, dedoAnalogE = -1, dedoAnalogD = -1;
    private float analogEx, analogEy, analogDx, analogDy;
    private final Paint p = new Paint(Paint.ANTI_ALIAS_FLAG);
    private final Paint pm = new Paint(Paint.ANTI_ALIAS_FLAG);
    private final float dens;
    private boolean vibrar;

    public ControleNaTela(Context ctx, boolean editando) {
        super(ctx);
        this.editando = editando;
        dens = getResources().getDisplayMetrics().density;
        p.setFilterBitmap(true);
        areas.add(new Area("A", bm("pad_a"), ControleMGS2.A, null));
        areas.add(new Area("B", bm("pad_b"), ControleMGS2.B, null));
        areas.add(new Area("X", bm("pad_x"), ControleMGS2.X, null));
        areas.add(new Area("Y", bm("pad_y"), ControleMGS2.Y, null));
        areas.add(new Area("LB", bm("pad_lb"), ControleMGS2.LB, null));
        areas.add(new Area("RB", bm("pad_rb"), ControleMGS2.RB, null));
        areas.add(new Area("LT", bm("pad_lt"), 0, Boolean.TRUE));
        areas.add(new Area("RT", bm("pad_rt"), 0, Boolean.FALSE));
        areas.add(new Area("START", bm("pad_start"), ControleMGS2.START, null));
        areas.add(new Area("BACK", bm("pad_back"), ControleMGS2.BACK, null));
        areas.add(new Area("L3", bm("pad_l3"), ControleMGS2.ANALOG_E, null));   // apertar o analogico
        areas.add(new Area("R3", bm("pad_r3"), ControleMGS2.ANALOG_D, null));
        dpad = bm("pad_dpad"); dpadCima = bm("pad_dpad_cima"); dpadBaixo = bm("pad_dpad_baixo");
        dpadEsq = bm("pad_dpad_esq"); dpadDir = bm("pad_dpad_dir");
        vibrar = AjustesMGS2.vibrar(ctx);
        carregar();
    }

    private Bitmap bm(String n) {
        try {
            InputStream in = getContext().getAssets().open("controles/" + n + ".png");
            Bitmap b = BitmapFactory.decodeStream(in);
            in.close();
            return b;
        } catch (Exception e) { return null; }
    }

    private float dp(float v) { return v * dens; }

    private RectF caixa(String n) {
        switch (n) {
            case "DPAD": return caixaDpad;
            case "ANALOG_E": return caixaAnalogE;
            case "ANALOG_D": return caixaAnalogD;
        }
        for (Area a : areas) if (a.nome.equals(n)) return a.caixa;
        return new RectF();
    }

    // ------------------------------------------------ disposicao do usuario

    public float escalaGeral() { return escalaGeral; }
    public void setEscalaGeral(float v) { escalaGeral = Math.max(0.5f, Math.min(2f, v)); aplicar(); invalidate(); }
    public int opacidade() { return opacidade; }
    public void setOpacidade(int v) { opacidade = Math.max(10, Math.min(100, v)); invalidate(); }
    public String selecionado() { return selecionado; }

    public float escalaDe(String n) { Personal pp = personal.get(n); return pp == null ? 1f : pp.escala; }

    public void definirEscala(String n, float e) {
        Personal pp = personal.get(n);
        if (pp == null) { pp = new Personal(); personal.put(n, pp); }
        pp.escala = Math.max(0.4f, Math.min(2.5f, e));
        aplicar(); invalidate();
    }

    public void restaurar() {
        personal.clear(); escalaGeral = 1f; opacidade = OPACIDADE_PADRAO;
        aplicar(); invalidate();
    }

    public void salvar() {
        SharedPreferences.Editor ed = AjustesMGS2.de(getContext()).edit();
        for (String n : NOMES) ed.remove("ctl_p_" + n);
        for (String n : personal.keySet()) {
            Personal pp = personal.get(n);
            ed.putString("ctl_p_" + n, pp.cx + ";" + pp.cy + ";" + pp.escala);
        }
        ed.putFloat("ctl_geral", escalaGeral);
        ed.putInt("ctl_opacidade", opacidade);
        ed.apply();
    }

    private void carregar() {
        SharedPreferences pr = AjustesMGS2.de(getContext());
        for (String n : NOMES) {
            String v = pr.getString("ctl_p_" + n, null);
            if (v == null) continue;
            String[] s = v.split(";");
            if (s.length != 3) continue;
            Personal pp = new Personal();
            try { pp.cx = Float.parseFloat(s[0]); } catch (Exception e) { }
            try { pp.cy = Float.parseFloat(s[1]); } catch (Exception e) { }
            try { pp.escala = Float.parseFloat(s[2]); } catch (Exception e) { }
            personal.put(n, pp);
        }
        escalaGeral = pr.getFloat("ctl_geral", 1f);
        opacidade = pr.getInt("ctl_opacidade", OPACIDADE_PADRAO);
    }

    private void aplicar() {
        if (larg <= 0f) return;
        for (String n : NOMES) {
            RectF d = padrao.get(n);
            if (d == null) continue;
            Personal pp = personal.get(n);
            float e = (pp == null ? 1f : pp.escala) * escalaGeral;
            float w = d.width() * e, h = d.height() * e;
            float cx = (pp != null && !Float.isNaN(pp.cx)) ? pp.cx * larg : d.centerX();
            float cy = (pp != null && !Float.isNaN(pp.cy)) ? pp.cy * alt : d.centerY();
            cx = Math.max(w / 2, Math.min(Math.max(w / 2, larg - w / 2), cx));
            cy = Math.max(h / 2, Math.min(Math.max(h / 2, alt - h / 2), cy));
            caixa(n).set(cx - w / 2, cy - h / 2, cx + w / 2, cy + h / 2);
        }
    }

    @Override protected void onSizeChanged(int l, int a, int ol, int oa) {
        super.onSizeChanged(l, a, ol, oa);
        posicionar(l, a);
    }

    /** Disposicao do controle do Xbox 360 visto de cima (a mesma do MGR). */
    private void posicionar(float L, float A) {
        float m = dp(16f);
        float analog = dp(76f), cruz = dp(70f), botao = dp(38f);
        float ombroL = dp(70f), ombroA = dp(28f), gatL = dp(40f), gatA = dp(56f), menu = dp(30f), clique = dp(34f);

        pos("LT", m + dp(10f), m, gatL, gatA);
        pos("LB", m, m + gatA + dp(6f), ombroL, ombroA);
        pos("RT", L - m - gatL - dp(10f), m, gatL, gatA);
        pos("RB", L - m - ombroL, m + gatA + dp(6f), ombroL, ombroA);

        float baseE = A - m;
        caixaAnalogE.set(m, baseE - analog - cruz - dp(16f), m + analog, baseE - cruz - dp(16f));
        caixaDpad.set(m + dp(20f), baseE - cruz, m + dp(20f) + cruz, baseE);

        float cxd = L - m - dp(62f);
        float cyd = A - m - analog - dp(16f) - dp(50f);
        pos("Y", cxd - botao / 2, cyd - dp(32f) - botao / 2, botao, botao);
        pos("A", cxd - botao / 2, cyd + dp(32f) - botao / 2, botao, botao);
        pos("X", cxd - dp(34f) - botao / 2, cyd - botao / 2, botao, botao);
        pos("B", cxd + dp(34f) - botao / 2, cyd - botao / 2, botao, botao);

        caixaAnalogD.set(L - m - analog - dp(28f), A - m - analog, L - m - dp(28f), A - m);

        // L3/R3 ao lado de cada analogico, por dentro (do lado do centro da tela), na altura do meio dele
        pos("L3", caixaAnalogE.right + dp(10f), caixaAnalogE.centerY() - clique / 2, clique, clique);
        pos("R3", caixaAnalogD.left - dp(10f) - clique, caixaAnalogD.centerY() - clique / 2, clique, clique);

        pos("BACK", L / 2 - menu - dp(14f), A - m - menu, menu, menu);
        pos("START", L / 2 + dp(14f), A - m - menu, menu, menu);

        larg = L; alt = A;
        for (String n : NOMES) padrao.put(n, new RectF(caixa(n)));
        aplicar();
    }

    private void pos(String nome, float x, float y, float w, float h) { caixa(nome).set(x, y, x + w, y + h); }

    // ------------------------------------------------------------- desenho

    private void desenhar(Canvas c, Bitmap b, RectF r, boolean apertado) {
        if (b == null) return;
        p.setAlpha(apertado ? 255 : Math.max(0, Math.min(255, opacidade * 255 / 100)));
        float enc = apertado ? r.width() * 0.06f : 0f;
        c.drawBitmap(b, null, new RectF(r.left + enc, r.top + enc, r.right - enc, r.bottom - enc), p);
    }

    @Override protected void onDraw(Canvas c) {
        for (Area a : areas) desenhar(c, a.bitmap, a.caixa, a.dedo >= 0);
        Bitmap face = dpadFace == 1 ? dpadCima : dpadFace == 2 ? dpadBaixo : dpadFace == 3 ? dpadEsq : dpadFace == 4 ? dpadDir : dpad;
        desenhar(c, face, caixaDpad, dedoDpad >= 0);
        analogico(c, caixaAnalogE, analogEx, analogEy, dedoAnalogE >= 0);
        analogico(c, caixaAnalogD, analogDx, analogDy, dedoAnalogD >= 0);
        if (editando) molduras(c);
    }

    private void molduras(Canvas c) {
        pm.setStyle(Paint.Style.STROKE);
        for (String n : NOMES) {
            RectF r = caixa(n);
            boolean sel = n.equals(selecionado);
            pm.setStrokeWidth(dp(sel ? 2.5f : 1f));
            pm.setColor(sel ? 0xFF4FC3F7 : 0x66FFFFFF);
            c.drawRoundRect(r, dp(6f), dp(6f), pm);
            if (sel) {
                pm.setStyle(Paint.Style.FILL);
                pm.setTextSize(dp(11f));
                pm.setTextAlign(Paint.Align.CENTER);
                String txt = rotulo(n) + "  " + (int) (escalaDe(n) * escalaGeral * 100) + "%";
                float ty = r.top > dp(20f) ? r.top - dp(6f) : r.bottom + dp(14f);
                c.drawText(txt, r.centerX(), ty, pm);
                pm.setStyle(Paint.Style.STROKE);
            }
        }
    }

    private int alfa(int base, float a) { return (Math.max(0, Math.min(255, (int) (base * a))) << 24); }

    /** O analogico, desenhado: mascara escura, aro claro e o manipulo que segue o dedo. */
    private void analogico(Canvas c, RectF r, float dx, float dy, boolean ativo) {
        float cx = r.centerX(), cy = r.centerY();
        float raio = Math.min(r.width(), r.height()) / 2f;
        float a = (opacidade / 100f) * (ativo ? 1.0f : 0.68f);
        p.setAlpha(255);
        p.setStyle(Paint.Style.FILL);
        p.setColor(alfa(190, a));
        c.drawCircle(cx, cy, raio, p);
        p.setStyle(Paint.Style.STROKE);
        p.setStrokeWidth(dp(1.6f));
        p.setColor(alfa(120, a) | 0xCFD6DD);
        c.drawCircle(cx, cy, raio - dp(1f), p);
        float passeio = raio * 0.40f;
        float kx = cx + dx * passeio, ky = cy + dy * passeio, raioK = raio * 0.52f;
        p.setStyle(Paint.Style.FILL);
        p.setColor(alfa(150, a) | 0x20262E);
        c.drawCircle(kx, ky, raioK, p);
        p.setStyle(Paint.Style.STROKE);
        p.setStrokeWidth(dp(1.4f));
        p.setColor(alfa(190, a) | 0xE6ECF2);
        c.drawCircle(kx, ky, raioK - dp(0.8f), p);
        p.setStyle(Paint.Style.FILL);
    }

    // -------------------------------------------------------------- toque

    private boolean acerta(RectF r, float x, float y) {
        float f = dp(8f);
        return x >= r.left - f && x <= r.right + f && y >= r.top - f && y <= r.bottom + f;
    }

    // editor
    private int dedoArrasto = -1;
    private float arrDx, arrDy;
    private boolean pincando;
    private float pincaDist0 = 1f, pincaEsc0 = 1f;

    private String acharElemento(float x, float y) {
        for (int i = NOMES.length - 1; i >= 0; i--) if (caixa(NOMES[i]).contains(x, y)) return NOMES[i];
        for (int i = NOMES.length - 1; i >= 0; i--) if (acerta(caixa(NOMES[i]), x, y)) return NOMES[i];
        return null;
    }

    private static float distancia(MotionEvent e) {
        return e.getPointerCount() < 2 ? 0f : (float) Math.hypot(e.getX(0) - e.getX(1), e.getY(0) - e.getY(1));
    }

    private boolean editarToque(MotionEvent e) {
        switch (e.getActionMasked()) {
            case MotionEvent.ACTION_DOWN: {
                String n = acharElemento(e.getX(), e.getY());
                selecionado = n;
                if (aoSelecionar != null) aoSelecionar.selecionou(n);
                if (n != null) {
                    RectF r = caixa(n);
                    dedoArrasto = e.getPointerId(0);
                    arrDx = r.centerX() - e.getX(); arrDy = r.centerY() - e.getY();
                }
                break;
            }
            case MotionEvent.ACTION_POINTER_DOWN:
                if (selecionado != null && e.getPointerCount() == 2) {
                    pincando = true;
                    pincaDist0 = Math.max(1f, distancia(e));
                    pincaEsc0 = escalaDe(selecionado);
                }
                break;
            case MotionEvent.ACTION_MOVE: {
                String n = selecionado;
                if (n == null) return true;
                if (pincando && e.getPointerCount() >= 2) {
                    definirEscala(n, pincaEsc0 * distancia(e) / pincaDist0);
                    if (aoSelecionar != null) aoSelecionar.selecionou(n);
                } else if (!pincando && dedoArrasto >= 0) {
                    int i = e.findPointerIndex(dedoArrasto);
                    if (i >= 0 && larg > 0f) {
                        Personal pp = personal.get(n);
                        if (pp == null) { pp = new Personal(); personal.put(n, pp); }
                        pp.cx = Math.max(0f, Math.min(1f, (e.getX(i) + arrDx) / larg));
                        pp.cy = Math.max(0f, Math.min(1f, (e.getY(i) + arrDy) / alt));
                        aplicar();
                    }
                }
                break;
            }
            case MotionEvent.ACTION_POINTER_UP:
                if (e.getPointerCount() - 1 < 2) { pincando = false; dedoArrasto = -1; }
                break;
            case MotionEvent.ACTION_UP: case MotionEvent.ACTION_CANCEL:
                pincando = false; dedoArrasto = -1;
                break;
        }
        invalidate();
        return true;
    }

    @Override public boolean onTouchEvent(MotionEvent e) {
        if (editando) return editarToque(e);
        switch (e.getActionMasked()) {
            case MotionEvent.ACTION_DOWN: case MotionEvent.ACTION_POINTER_DOWN: {
                int i = e.getActionIndex();
                pegar(e.getPointerId(i), e.getX(i), e.getY(i));
                break;
            }
            case MotionEvent.ACTION_MOVE:
                for (int i = 0; i < e.getPointerCount(); i++) mover(e.getPointerId(i), e.getX(i), e.getY(i));
                break;
            case MotionEvent.ACTION_UP: case MotionEvent.ACTION_POINTER_UP: case MotionEvent.ACTION_CANCEL: {
                int i = e.getActionIndex();
                soltar(e.getPointerId(i));
                if (e.getActionMasked() == MotionEvent.ACTION_CANCEL) ControleMGS2.solta();
                break;
            }
        }
        invalidate();
        return true;
    }

    private void toque() { if (vibrar) performHapticFeedback(HapticFeedbackConstants.VIRTUAL_KEY); }

    private void pegar(int dedo, float x, float y) {
        if (acerta(caixaDpad, x, y)) { dedoDpad = dedo; cruzeta(x, y); toque(); return; }
        if (acerta(caixaAnalogE, x, y)) { dedoAnalogE = dedo; mover(dedo, x, y); return; }
        if (acerta(caixaAnalogD, x, y)) { dedoAnalogD = dedo; mover(dedo, x, y); return; }
        for (Area a : areas) if (acerta(a.caixa, x, y) && a.dedo < 0) {
            a.dedo = dedo;
            if (a.gatilhoEsquerdo != null) ControleMGS2.gatilho(a.gatilhoEsquerdo, 1f);
            else ControleMGS2.botao(a.bit, true);
            toque();
            return;
        }
    }

    private void mover(int dedo, float x, float y) {
        if (dedo == dedoDpad) cruzeta(x, y);
        else if (dedo == dedoAnalogE) {
            analogEx = clamp((x - caixaAnalogE.centerX()) / (caixaAnalogE.width() / 2));
            analogEy = clamp((y - caixaAnalogE.centerY()) / (caixaAnalogE.height() / 2));
            limitar(true);
        } else if (dedo == dedoAnalogD) {
            analogDx = clamp((x - caixaAnalogD.centerX()) / (caixaAnalogD.width() / 2));
            analogDy = clamp((y - caixaAnalogD.centerY()) / (caixaAnalogD.height() / 2));
            limitar(false);
        }
    }

    private static float clamp(float v) { return Math.max(-1f, Math.min(1f, v)); }

    /** Mantem o vetor dentro do circulo (na diagonal o quadrado daria 1,41). */
    private void limitar(boolean esquerdo) {
        float x = esquerdo ? analogEx : analogDx, y = esquerdo ? analogEy : analogDy;
        float m = (float) Math.hypot(x, y);
        if (m > 1f) { x /= m; y /= m; }
        if (esquerdo) { analogEx = x; analogEy = y; } else { analogDx = x; analogDy = y; }
        ControleMGS2.analogico(esquerdo, x, y);
    }

    private void cruzeta(float x, float y) {
        float fx = (x - caixaDpad.centerX()) / (caixaDpad.width() / 2);
        float fy = (y - caixaDpad.centerY()) / (caixaDpad.height() / 2);
        float lim = 0.32f;
        ControleMGS2.botao(ControleMGS2.ESQUERDA, fx < -lim);
        ControleMGS2.botao(ControleMGS2.DIREITA, fx > lim);
        ControleMGS2.botao(ControleMGS2.CIMA, fy < -lim);
        ControleMGS2.botao(ControleMGS2.BAIXO, fy > lim);
        if (Math.abs(fx) < lim && Math.abs(fy) < lim) dpadFace = 0;
        else if (Math.abs(fx) >= Math.abs(fy)) dpadFace = fx < 0 ? 3 : 4;
        else dpadFace = fy < 0 ? 1 : 2;
    }

    private void soltar(int dedo) {
        if (dedo == dedoDpad) {
            dedoDpad = -1; dpadFace = 0;
            ControleMGS2.botao(ControleMGS2.ESQUERDA, false); ControleMGS2.botao(ControleMGS2.DIREITA, false);
            ControleMGS2.botao(ControleMGS2.CIMA, false); ControleMGS2.botao(ControleMGS2.BAIXO, false);
        }
        if (dedo == dedoAnalogE) { dedoAnalogE = -1; analogEx = 0f; analogEy = 0f; ControleMGS2.analogico(true, 0f, 0f); }
        if (dedo == dedoAnalogD) { dedoAnalogD = -1; analogDx = 0f; analogDy = 0f; ControleMGS2.analogico(false, 0f, 0f); }
        for (Area a : areas) if (a.dedo == dedo) {
            a.dedo = -1;
            if (a.gatilhoEsquerdo != null) ControleMGS2.gatilho(a.gatilhoEsquerdo, 0f);
            else ControleMGS2.botao(a.bit, false);
        }
    }
}
