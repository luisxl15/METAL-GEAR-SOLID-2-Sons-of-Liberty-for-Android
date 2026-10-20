package com.nvidia.forge;

import android.app.Activity;
import android.app.Application;
import android.content.Context;
import android.content.Intent;
import android.graphics.Color;
import android.graphics.Typeface;
import android.graphics.drawable.GradientDrawable;
import android.hardware.input.InputManager;
import android.os.Build;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.view.Gravity;
import android.view.Surface;
import android.view.SurfaceView;
import android.view.View;
import android.view.ViewGroup;
import android.view.Window;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.FrameLayout;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.SeekBar;
import android.widget.TextView;

/**
 * Tela de entrada do MGS2 no celular (o LAUNCHER do manifesto: o nome desta classe
 * substituiu o da ForgeDownloaderActivity, mesmo tamanho de string).
 *
 *   Jogar     -> video da NVIDIA (NvidiaSplashVideoActivity) -> MainActivity (o jogo)
 *   Ajustes   -> limite de quadros, controles na tela, vibracao, opacidade
 *   Controles -> editor da disposicao dos botoes (arrastar / pinca), como no MGR
 *
 * E registra, para TODAS as telas do app: tela cheia imersiva (sem barras do
 * sistema), recorte da camera, video da abertura centrado e, no jogo, os
 * controles na tela (somem sozinhos com um controle de verdade ligado).
 */
public class ArranqueTelaCheiaMGS2HD extends Activity {
    private static boolean registrado;
    private static final String SPLASH = "com.nvidia.forge.NvidiaSplashVideoActivity";
    private static final String JOGO = "com.nvidia.forge.MainActivity";

    // ------------------------------------------------------------ tela cheia

    static void telaCheia(Activity a) {
        Window w = a.getWindow();
        w.setBackgroundDrawableResource(android.R.color.black);
        w.addFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN | WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
        if (Build.VERSION.SDK_INT >= 28) {
            WindowManager.LayoutParams lp = w.getAttributes();
            lp.layoutInDisplayCutoutMode = WindowManager.LayoutParams.LAYOUT_IN_DISPLAY_CUTOUT_MODE_SHORT_EDGES;
            w.setAttributes(lp);
        }
        imersivo(w.getDecorView());
    }

    @SuppressWarnings("deprecation")
    static void imersivo(View d) {
        d.setSystemUiVisibility(View.SYSTEM_UI_FLAG_IMMERSIVE_STICKY
                | View.SYSTEM_UI_FLAG_HIDE_NAVIGATION
                | View.SYSTEM_UI_FLAG_FULLSCREEN
                | View.SYSTEM_UI_FLAG_LAYOUT_STABLE
                | View.SYSTEM_UI_FLAG_LAYOUT_HIDE_NAVIGATION
                | View.SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN);
    }

    /** O video da abertura (16:9) ficava encostado a esquerda: centraliza. */
    static void centralizaVideo(Activity a) {
        int id = a.getResources().getIdentifier("videoview", "id", a.getPackageName());
        View v = id != 0 ? a.findViewById(id) : null;
        if (v != null && v.getLayoutParams() instanceof FrameLayout.LayoutParams) {
            FrameLayout.LayoutParams lp = (FrameLayout.LayoutParams) v.getLayoutParams();
            if (lp.gravity != Gravity.CENTER) { lp.gravity = Gravity.CENTER; v.setLayoutParams(lp); }
        }
        View raiz = a.findViewById(android.R.id.content);
        if (raiz != null) raiz.setBackgroundColor(Color.BLACK);
    }

    // ------------------------------------------------ controles dentro do jogo

    private static ControleNaTela sobreposto;
    private static InputManager.InputDeviceListener ouvinte;

    static void atualizaControles(Activity a) {
        if (sobreposto == null) return;
        String modo = AjustesMGS2.controles(a);
        boolean mostra = AjustesMGS2.CONTROLES_SEMPRE.equals(modo)
                || (AjustesMGS2.CONTROLES_AUTO.equals(modo) && !ControleMGS2.temControleFisico());
        if (!mostra && sobreposto.getVisibility() == View.VISIBLE) { ControleMGS2.solta(); ControleMGS2.esquece(); }
        if (mostra) ControleMGS2.conecta();
        sobreposto.setVisibility(mostra ? View.VISIBLE : View.GONE);
    }

    static void poeControles(final Activity a) {
        if (sobreposto != null && sobreposto.getContext() == a) { atualizaControles(a); return; }
        if (AjustesMGS2.CONTROLES_NUNCA.equals(AjustesMGS2.controles(a))) return;
        sobreposto = new ControleNaTela(a, false);
        a.addContentView(sobreposto, new ViewGroup.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT));
        InputManager im = (InputManager) a.getSystemService(Context.INPUT_SERVICE);
        if (im != null && ouvinte == null) {
            ouvinte = new InputManager.InputDeviceListener() {
                @Override public void onInputDeviceAdded(int id) { atualizaControles(a); }
                @Override public void onInputDeviceRemoved(int id) { atualizaControles(a); }
                @Override public void onInputDeviceChanged(int id) { atualizaControles(a); }
            };
            im.registerInputDeviceListener(ouvinte, new Handler(Looper.getMainLooper()));
        }
        atualizaControles(a);
    }

    /** Pede a taxa da tela igual ao limite de quadros (a do S25+ e 120 Hz); com a geracao de
     *  quadros ligada, o dobro (60 do jogo + 60 gerados = 120). */
    static void taxaDaTela(Activity a) {
        if (Build.VERSION.SDK_INT < 30) return;
        int fps = AjustesMGS2.taxaTela(a);
        int id = a.getResources().getIdentifier("surfaceview", "id", a.getPackageName());
        View v = id != 0 ? a.findViewById(id) : null;
        if (!(v instanceof SurfaceView)) v = acharSurface(a.getWindow().getDecorView());
        if (v instanceof SurfaceView) {
            Surface s = ((SurfaceView) v).getHolder().getSurface();
            try { if (s != null && s.isValid()) s.setFrameRate(fps > 0 ? fps : 0f, Surface.FRAME_RATE_COMPATIBILITY_DEFAULT); }
            catch (Throwable t) { }
        }
    }

    private static View acharSurface(View v) {
        if (v instanceof SurfaceView) return v;
        if (v instanceof ViewGroup) {
            ViewGroup g = (ViewGroup) v;
            for (int i = 0; i < g.getChildCount(); i++) { View r = acharSurface(g.getChildAt(i)); if (r != null) return r; }
        }
        return null;
    }

    private static void registra(Application app) {
        if (registrado) return;
        registrado = true;
        app.registerActivityLifecycleCallbacks(new Application.ActivityLifecycleCallbacks() {
            @Override public void onActivityCreated(Activity a, Bundle b) { telaCheia(a); }
            @Override public void onActivityStarted(Activity a) { }
            @Override public void onActivityResumed(final Activity a) {
                final View d = a.getWindow().getDecorView();
                imersivo(d);
                d.setOnSystemUiVisibilityChangeListener(new View.OnSystemUiVisibilityChangeListener() {
                    @Override public void onSystemUiVisibilityChange(int v) {
                        if ((v & View.SYSTEM_UI_FLAG_FULLSCREEN) == 0) imersivo(d);
                    }
                });
                final String nome = a.getClass().getName();
                /* o onResume da propria tela ainda vai montar o conteudo: depois dele */
                d.post(new Runnable() { @Override public void run() {
                    if (SPLASH.equals(nome)) centralizaVideo(a);
                    if (JOGO.equals(nome)) { poeControles(a); taxaDaTela(a); MedidorFps.poe(a); }
                    imersivo(d);
                } });
            }
            @Override public void onActivityPaused(Activity a) {
                if (JOGO.equals(a.getClass().getName())) ControleMGS2.solta();
            }
            @Override public void onActivityStopped(Activity a) { }
            @Override public void onActivitySaveInstanceState(Activity a, Bundle b) { }
            @Override public void onActivityDestroyed(Activity a) {
                if (sobreposto != null && sobreposto.getContext() == a) sobreposto = null;
            }
        });
    }

    // --------------------------------------------------------- tela de entrada

    private FrameLayout raiz;
    private float dens;

    private int dp(float v) { return (int) (v * dens + 0.5f); }

    private Button botao(String txt, boolean principal) {
        Button b = new Button(this);
        b.setText(txt);
        b.setAllCaps(true);
        b.setTextColor(principal ? 0xFF06110B : 0xFFE8EFEB);
        b.setTextSize(principal ? 18 : 15);
        b.setTypeface(Typeface.create("sans-serif-condensed", Typeface.BOLD));
        b.setLetterSpacing(0.12f);
        b.setStateListAnimator(null);
        android.graphics.drawable.StateListDrawable st = new android.graphics.drawable.StateListDrawable();
        st.addState(new int[] { android.R.attr.state_pressed }, TelaAjustes.caixa(principal ? 0xFF5FB883 : 0xFF1C2A24, TelaAjustes.VERDE, 8, dens));
        st.addState(new int[] { android.R.attr.state_focused }, TelaAjustes.caixa(principal ? TelaAjustes.VERDE : 0xFF1C2A24, 0xFFFFFFFF, 8, dens));
        st.addState(new int[] {}, TelaAjustes.caixa(principal ? TelaAjustes.VERDE : 0xC0070B09, principal ? 0 : 0xFF3A4A42, 8, dens));
        b.setBackground(st);
        b.setPadding(dp(30), dp(12), dp(30), dp(12));
        b.setMinWidth(dp(150));
        return b;
    }

    @Override
    protected void onCreate(Bundle b) {
        registra(getApplication());
        super.onCreate(b);
        telaCheia(this);
        dens = getResources().getDisplayMetrics().density;
        AjustesMGS2.gravaNativo(this);
        montaMenu();
    }

    private void montaMenu() {
        noMenu = true;
        raiz = new FrameLayout(this);
        raiz.setBackgroundColor(Color.BLACK);

        int arte = getResources().getIdentifier("splash", "drawable", getPackageName());
        if (arte != 0) {
            ImageView iv = new ImageView(this);
            iv.setImageResource(arte);
            iv.setScaleType(ImageView.ScaleType.FIT_CENTER);
            FrameLayout.LayoutParams lp = new FrameLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT);
            lp.bottomMargin = dp(70);
            raiz.addView(iv, lp);
        }

        LinearLayout linha = new LinearLayout(this);
        linha.setOrientation(LinearLayout.HORIZONTAL);
        linha.setGravity(Gravity.CENTER);
        Button jogar = botao(Textos.t("Jogar"), true);
        Button ajustes = botao(Textos.t("Ajustes"), false);
        Button controles = botao(Textos.t("Controles na tela"), false);
        LinearLayout.LayoutParams m = new LinearLayout.LayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT);
        m.setMargins(dp(10), 0, dp(10), 0);
        linha.addView(ajustes, m);
        linha.addView(jogar, m);
        linha.addView(controles, m);
        FrameLayout.LayoutParams lpl = new FrameLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT,
                Gravity.BOTTOM | Gravity.CENTER_HORIZONTAL);
        lpl.bottomMargin = dp(22);
        raiz.addView(linha, lpl);

        setContentView(raiz);
        jogar.requestFocus();

        jogar.setOnClickListener(new View.OnClickListener() { @Override public void onClick(View v) { jogar(); } });
        ajustes.setOnClickListener(new View.OnClickListener() { @Override public void onClick(View v) { abreAjustes(); } });
        controles.setOnClickListener(new View.OnClickListener() { @Override public void onClick(View v) { abreEditor(); } });
    }

    private void jogar() {
        AjustesMGS2.gravaNativo(this);
        if (!ExtratorObb.pronto(this)) { preparaDados(); return; }   // 1a vez: tira os arquivos das OBBs
        Intent i = new Intent();
        i.setClassName(this, SPLASH);
        startActivity(i);
        finish();
    }

    // ------------------------------------------------- dados do jogo (1a vez)

    /** Tela de preparo: extrai as OBBs para files/ (ExtratorObb) e depois abre o jogo. */
    private void preparaDados() {
        noMenu = false;
        getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
        FrameLayout tela = new FrameLayout(this);
        tela.setBackgroundColor(TelaAjustes.FUNDO);
        LinearLayout col = new LinearLayout(this);
        col.setOrientation(LinearLayout.VERTICAL);
        col.setGravity(Gravity.CENTER_HORIZONTAL);
        col.setPadding(dp(32), dp(24), dp(32), dp(24));
        final TextView tit = new TextView(this);
        tit.setText(Textos.t("PREPARANDO OS DADOS DO JOGO"));
        tit.setTextColor(TelaAjustes.TEXTO);
        tit.setTextSize(22);
        tit.setLetterSpacing(0.12f);
        tit.setTypeface(Typeface.create("sans-serif-condensed", Typeface.BOLD));
        tit.setGravity(Gravity.CENTER);
        col.addView(tit);
        final TextView sub = new TextView(this);
        sub.setText(Textos.t("Só na primeira vez: tirando os arquivos de dentro das OBBs (cerca de 7 GB). Deixe o app aberto."));
        sub.setTextColor(TelaAjustes.TEXTO2);
        sub.setTextSize(13);
        sub.setGravity(Gravity.CENTER);
        sub.setPadding(0, dp(8), 0, dp(22));
        col.addView(sub);
        final android.widget.ProgressBar barra = new android.widget.ProgressBar(this, null, android.R.attr.progressBarStyleHorizontal);
        barra.setMax(1000);
        barra.getProgressDrawable().setTint(TelaAjustes.VERDE);
        col.addView(barra, new LinearLayout.LayoutParams(Math.min(dp(560), getResources().getDisplayMetrics().widthPixels - dp(64)), dp(10)));
        final TextView num = new TextView(this);
        num.setTextColor(TelaAjustes.VERDE);
        num.setTextSize(14);
        num.setTypeface(Typeface.MONOSPACE, Typeface.BOLD);
        num.setGravity(Gravity.CENTER);
        num.setPadding(0, dp(12), 0, 0);
        num.setText(Textos.t("lendo as OBBs..."));
        col.addView(num);
        tela.addView(col, new FrameLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT, Gravity.CENTER));
        setContentView(tela);
        imersivo(getWindow().getDecorView());

        final Handler h = new Handler(Looper.getMainLooper());
        final long t0 = android.os.SystemClock.elapsedRealtime();
        new Thread(new Runnable() { @Override public void run() {
            final String erro = ExtratorObb.extrai(ArranqueTelaCheiaMGS2HD.this, new ExtratorObb.Progresso() {
                @Override public void andou(final long feito, final long total, final int arq, final int totArq) {
                    h.post(new Runnable() { @Override public void run() {
                        double fr = total > 0 ? (double) feito / total : 0;
                        barra.setProgress((int) (fr * 1000));
                        long seg = (android.os.SystemClock.elapsedRealtime() - t0) / 1000;
                        String resta = fr > 0.02 && seg > 2 ? Textos.f("  ·  falta ~%d s", (long) (seg / fr - seg)) : "";
                        num.setText(Textos.f("%.1f / %.1f GB  ·  %d / %d arquivos%s",
                                feito / 1e9, total / 1e9, arq, totArq, resta));
                    } });
                }
            });
            h.post(new Runnable() { @Override public void run() {
                getWindow().clearFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
                if (erro == null) { jogar(); return; }
                tit.setText(Textos.t("NÃO FOI POSSÍVEL PREPARAR"));
                sub.setText(erro);
                sub.setTextColor(0xFFE0B060);
                Button tenta = botao(Textos.t("Tentar de novo"), true), volta = botao(Textos.t("Voltar"), false);
                LinearLayout bts = new LinearLayout(ArranqueTelaCheiaMGS2HD.this);
                bts.setGravity(Gravity.CENTER);
                LinearLayout.LayoutParams m = new LinearLayout.LayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT);
                m.setMargins(dp(10), dp(18), dp(10), 0);
                bts.addView(volta, m); bts.addView(tenta, m);
                ((LinearLayout) num.getParent()).addView(bts);
                tenta.setOnClickListener(new View.OnClickListener() { @Override public void onClick(View v) { preparaDados(); } });
                volta.setOnClickListener(new View.OnClickListener() { @Override public void onClick(View v) { montaMenu(); } });
                tenta.requestFocus();
            } });
        } }, "MGS2 prepara dados").start();
    }

    // ---------------------------------------------------------------- ajustes


    private TextView nota(String t) {
        TextView tv = new TextView(this);
        tv.setText(t);
        tv.setTextColor(0xFFB0B8B4);
        tv.setTextSize(12);
        return tv;
    }


    private boolean noMenu = true;

    private void abreAjustes() {
        noMenu = false;
        setContentView(TelaAjustes.monta(this, new TelaAjustes.AoSair() { @Override public void saiu() { montaMenu(); } }));
        imersivo(getWindow().getDecorView());
    }

    /** volta do seletor de arquivos: o Lossless.dll escolhido nos ajustes */
    @Override
    protected void onActivityResult(int pedido, int resultado, Intent dados) {
        super.onActivityResult(pedido, resultado, dados);
        if (pedido == TelaAjustes.PEDIDO_DLL && resultado == RESULT_OK && dados != null && dados.getData() != null)
            TelaAjustes.recebeDll(this, dados.getData());
        imersivo(getWindow().getDecorView());
    }

    @Override
    public void onBackPressed() {
        if (!noMenu) { montaMenu(); return; }
        super.onBackPressed();
    }

    // ----------------------------------------------------------------- editor

    private void abreEditor() {
        noMenu = false;
        final FrameLayout ed = new FrameLayout(this);
        ed.setBackgroundColor(0xFF15191C);
        final ControleNaTela ctl = new ControleNaTela(this, true);
        ed.addView(ctl, new FrameLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT));

        LinearLayout barra = new LinearLayout(this);
        barra.setOrientation(LinearLayout.VERTICAL);
        barra.setGravity(Gravity.CENTER_HORIZONTAL);
        barra.setBackgroundColor(0xCC000000);
        barra.setPadding(dp(12), dp(6), dp(12), dp(6));

        final TextView info = nota(Textos.t("Toque num botão para escolher. Arraste para mover, pinça para mudar o tamanho."));
        info.setGravity(Gravity.CENTER);
        barra.addView(info);

        LinearLayout tam = new LinearLayout(this);
        tam.setGravity(Gravity.CENTER_VERTICAL);
        TextView lt = nota(Textos.t("Tamanho geral  "));
        tam.addView(lt);
        final SeekBar sTam = new SeekBar(this);
        sTam.setMax(150);
        sTam.setProgress((int) (ctl.escalaGeral() * 100) - 50);
        tam.addView(sTam, new LinearLayout.LayoutParams(dp(220), ViewGroup.LayoutParams.WRAP_CONTENT));
        TextView lo = nota(Textos.t("   Opacidade  "));
        tam.addView(lo);
        final SeekBar sOp = new SeekBar(this);
        sOp.setMax(90);
        sOp.setProgress(ctl.opacidade() - 10);
        tam.addView(sOp, new LinearLayout.LayoutParams(dp(160), ViewGroup.LayoutParams.WRAP_CONTENT));
        barra.addView(tam);

        LinearLayout bts = new LinearLayout(this);
        bts.setGravity(Gravity.CENTER);
        Button salvar = botao(Textos.t("Salvar"), true), restaurar = botao(Textos.t("Restaurar padrão"), false), voltar = botao(Textos.t("Voltar"), false);
        LinearLayout.LayoutParams m = new LinearLayout.LayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT);
        m.setMargins(dp(8), dp(4), dp(8), 0);
        bts.addView(voltar, m); bts.addView(restaurar, m); bts.addView(salvar, m);
        barra.addView(bts);

        FrameLayout.LayoutParams lpb = new FrameLayout.LayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT,
                Gravity.TOP | Gravity.CENTER_HORIZONTAL);
        lpb.topMargin = dp(90);
        ed.addView(barra, lpb);

        ctl.aoSelecionar = new ControleNaTela.AoSelecionar() {
            @Override public void selecionou(String n) {
                info.setText(n == null ? Textos.t("Nenhum selecionado. Toque num botão.")
                        : ControleNaTela.rotulo(n) + Textos.t(" — arraste para mover, pinça para o tamanho"));
            }
        };
        sTam.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override public void onProgressChanged(SeekBar s, int v, boolean u) { if (u) ctl.setEscalaGeral((v + 50) / 100f); }
            @Override public void onStartTrackingTouch(SeekBar s) { }
            @Override public void onStopTrackingTouch(SeekBar s) { }
        });
        sOp.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override public void onProgressChanged(SeekBar s, int v, boolean u) { if (u) ctl.setOpacidade(v + 10); }
            @Override public void onStartTrackingTouch(SeekBar s) { }
            @Override public void onStopTrackingTouch(SeekBar s) { }
        });
        salvar.setOnClickListener(new View.OnClickListener() { @Override public void onClick(View v) { ctl.salvar(); montaMenu(); } });
        restaurar.setOnClickListener(new View.OnClickListener() { @Override public void onClick(View v) {
            ctl.restaurar(); sTam.setProgress(50); sOp.setProgress(ctl.opacidade() - 10); } });
        voltar.setOnClickListener(new View.OnClickListener() { @Override public void onClick(View v) { montaMenu(); } });

        setContentView(ed);
        imersivo(getWindow().getDecorView());
    }

    @Override
    public void onWindowFocusChanged(boolean foco) {
        super.onWindowFocusChanged(foco);
        if (foco) imersivo(getWindow().getDecorView());
    }
}
