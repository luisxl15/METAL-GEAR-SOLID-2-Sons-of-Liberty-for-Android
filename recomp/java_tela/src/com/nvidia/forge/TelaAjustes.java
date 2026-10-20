package com.nvidia.forge;

import android.app.Activity;
import android.graphics.Color;
import android.graphics.Typeface;
import android.graphics.drawable.ColorDrawable;
import android.graphics.drawable.GradientDrawable;
import android.graphics.drawable.StateListDrawable;
import android.util.DisplayMetrics;
import android.view.Gravity;
import android.view.View;
import android.view.ViewGroup;
import android.widget.FrameLayout;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.ScrollView;
import android.widget.SeekBar;
import android.widget.Switch;
import android.widget.TextView;

/**
 * Tela de ajustes, no visual do codec do MGS2: fundo escuro esverdeado, cartoes
 * com borda fina, destaque verde. Responsiva: conteudo centrado com largura
 * maxima, rolagem quando a altura nao cabe, e o seletor desce para baixo do texto
 * em telas estreitas. Barra de baixo (Voltar / Salvar) sempre visivel.
 *
 * Nada e gravado ate "Salvar"; "Voltar" descarta.
 */
final class TelaAjustes {
    static final int FUNDO = 0xFF070B09, CARTAO = 0xF0101714, BORDA = 0xFF20302A;
    static final int VERDE = 0xFF7FD6A0, VERDE_ESCURO = 0xFF1C3A2A, TEXTO = 0xFFE8EFEB, TEXTO2 = 0xFF95A59D;

    interface AoSair { void saiu(); }

    private final Activity a;
    private final float dens;
    private final boolean estreita;

    // valores em edicao
    private int fps;
    private boolean esticar, vibrar, medidor;
    private String controles;
    private int opacidade;
    private int lsfg, lsfgFluxo;

    // ---- Lossless.dll (o do usuario, copiado da instalacao do Lossless Scaling no PC)
    static final int PEDIDO_DLL = 0x4c53;
    private static TextView statusDll;   // a tela aberta, para atualizar depois da importacao

    static String textoDll(Activity a) {
        return AjustesMGS2.temDll(a)
                ? Textos.t("Instalado. Os shaders são lidos do seu arquivo, nunca executados.")
                : Textos.t("Não instalado. Copie o Lossless.dll da pasta do Lossless Scaling no PC (Steam > Lossless Scaling > Gerenciar > Ver arquivos locais) para o celular e importe aqui.");
    }

    static void pedeDll(Activity a) {
        android.content.Intent i = new android.content.Intent(android.content.Intent.ACTION_OPEN_DOCUMENT);
        i.addCategory(android.content.Intent.CATEGORY_OPENABLE);
        i.setType("*/*");
        try { a.startActivityForResult(i, PEDIDO_DLL); }
        catch (Exception e) { android.widget.Toast.makeText(a, Textos.f("Sem seletor de arquivos: %s", e), android.widget.Toast.LENGTH_LONG).show(); }
    }

    /** copia o arquivo escolhido para files/Lossless.dll (so confere o cabecalho PE "MZ") */
    static void recebeDll(Activity a, android.net.Uri uri) {
        String msg;
        java.io.File dst = AjustesMGS2.arquivoDll(a);
        try (java.io.InputStream in = a.getContentResolver().openInputStream(uri)) {
            if (in == null || dst == null) throw new java.io.IOException(Textos.t("arquivo inacessível"));
            java.io.File tmp = new java.io.File(dst.getPath() + ".tmp");
            long n = 0; byte[] cab = new byte[2]; boolean pe;
            try (java.io.OutputStream out = new java.io.FileOutputStream(tmp)) {
                byte[] buf = new byte[1 << 16]; int r;
                while ((r = in.read(buf)) > 0) { if (n == 0 && r >= 2) { cab[0] = buf[0]; cab[1] = buf[1]; } out.write(buf, 0, r); n += r; }
            }
            pe = cab[0] == 'M' && cab[1] == 'Z';
            if (!pe || n < 1024 * 1024) { tmp.delete(); throw new java.io.IOException("não é o Lossless.dll (" + n + " bytes)"); }
            if (dst.exists()) dst.delete();
            if (!tmp.renameTo(dst)) throw new java.io.IOException("não consegui gravar em " + dst);
            msg = Textos.f("Lossless.dll importado (%d KB).", n / 1024);
        } catch (Exception e) {
            msg = Textos.f("Falhou: %s", e.getMessage());
        }
        android.widget.Toast.makeText(a, msg, android.widget.Toast.LENGTH_LONG).show();
        if (statusDll != null) {
            statusDll.setText(textoDll(a));
            statusDll.setTextColor(AjustesMGS2.temDll(a) ? VERDE : 0xFFE0B060);
        }
    }

    private TelaAjustes(Activity a) {
        this.a = a;
        DisplayMetrics dm = a.getResources().getDisplayMetrics();
        dens = dm.density;
        estreita = dm.widthPixels / dens < 640;
        fps = AjustesMGS2.fps(a);
        esticar = AjustesMGS2.esticar(a);
        medidor = AjustesMGS2.medidorFps(a);
        vibrar = AjustesMGS2.vibrar(a);
        controles = AjustesMGS2.controles(a);
        opacidade = AjustesMGS2.de(a).getInt("ctl_opacidade", ControleNaTela.OPACIDADE_PADRAO);
        lsfg = AjustesMGS2.lsfg(a);
        lsfgFluxo = AjustesMGS2.lsfgFluxo(a);
    }

    private int dp(float v) { return (int) (v * dens + 0.5f); }

    static View monta(Activity a, AoSair aoSair) { return new TelaAjustes(a).constroi(aoSair); }

    // ------------------------------------------------------------ pecas visuais

    static GradientDrawable caixa(int cor, int borda, float raio, float dens) {
        GradientDrawable g = new GradientDrawable();
        g.setColor(cor);
        g.setCornerRadius(raio * dens);
        if (borda != 0) g.setStroke((int) (dens + 0.5f), borda);
        return g;
    }

    private TextView texto(String t, float sp, int cor, boolean negrito) {
        TextView v = new TextView(a);
        v.setText(t);
        v.setTextSize(sp);
        v.setTextColor(cor);
        if (negrito) v.setTypeface(Typeface.create("sans-serif-condensed", Typeface.BOLD));
        return v;
    }

    private TextView rotuloSecao(String t) {
        TextView v = texto(t, 12, VERDE, true);
        v.setLetterSpacing(0.18f);
        v.setPadding(dp(4), dp(18), 0, dp(8));
        return v;
    }

    private LinearLayout cartao() {
        LinearLayout c = new LinearLayout(a);
        c.setOrientation(LinearLayout.VERTICAL);
        c.setBackground(caixa(CARTAO, BORDA, 10, dens));
        c.setPadding(dp(16), dp(4), dp(16), dp(4));
        return c;
    }

    private View divisoria() {
        View v = new View(a);
        v.setBackgroundColor(BORDA);
        v.setLayoutParams(new LinearLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, Math.max(1, dp(1) / 2)));
        return v;
    }

    /** Uma linha: titulo + explicacao a esquerda, controle a direita (ou embaixo, em tela estreita). */
    private LinearLayout linha(String titulo, String explica, View controle) {
        LinearLayout l = new LinearLayout(a);
        l.setOrientation(estreita ? LinearLayout.VERTICAL : LinearLayout.HORIZONTAL);
        l.setGravity(estreita ? Gravity.START : Gravity.CENTER_VERTICAL);
        l.setPadding(0, dp(14), 0, dp(14));
        LinearLayout txt = new LinearLayout(a);
        txt.setOrientation(LinearLayout.VERTICAL);
        txt.addView(texto(titulo, 16, TEXTO, true));
        if (explica != null) {
            TextView e = texto(explica, 12.5f, TEXTO2, false);
            e.setPadding(0, dp(3), dp(12), 0);
            txt.addView(e);
        }
        if (estreita) {
            l.addView(txt);
            LinearLayout.LayoutParams lp = new LinearLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT);
            lp.topMargin = dp(10);
            l.addView(controle, lp);
        } else {
            l.addView(txt, new LinearLayout.LayoutParams(0, ViewGroup.LayoutParams.WRAP_CONTENT, 1f));
            l.addView(controle, new LinearLayout.LayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT));
        }
        return l;
    }

    interface AoEscolher { void escolheu(int i); }

    /** Seletor segmentado: pilulas lado a lado, a escolhida preenchida de verde. */
    private LinearLayout segmentado(final String[] opcoes, int marcada, final AoEscolher ao) {
        final LinearLayout g = new LinearLayout(a);
        g.setOrientation(LinearLayout.HORIZONTAL);
        g.setBackground(caixa(0xFF0A100D, BORDA, 22, dens));
        g.setPadding(dp(3), dp(3), dp(3), dp(3));
        final TextView[] bts = new TextView[opcoes.length];
        for (int i = 0; i < opcoes.length; i++) {
            final int k = i;
            TextView b = texto(opcoes[i], 14, TEXTO, true);
            b.setGravity(Gravity.CENTER);
            b.setPadding(dp(16), dp(9), dp(16), dp(9));
            b.setMinWidth(dp(estreita ? 0 : 84));
            b.setFocusable(true);
            b.setClickable(true);
            bts[i] = b;
            LinearLayout.LayoutParams lp = estreita
                    ? new LinearLayout.LayoutParams(0, ViewGroup.LayoutParams.WRAP_CONTENT, 1f)
                    : new LinearLayout.LayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT);
            g.addView(b, lp);
            b.setOnClickListener(new View.OnClickListener() { @Override public void onClick(View v) {
                marca(bts, k); ao.escolheu(k);
            } });
        }
        marca(bts, marcada);
        return g;
    }

    private void marca(TextView[] bts, int k) {
        for (int i = 0; i < bts.length; i++) {
            boolean s = i == k;
            StateListDrawable st = new StateListDrawable();
            st.addState(new int[] { android.R.attr.state_focused }, caixa(s ? VERDE : 0xFF1A2A22, s ? 0 : VERDE, 19, dens));
            st.addState(new int[] {}, s ? caixa(VERDE, 0, 19, dens) : new ColorDrawable(Color.TRANSPARENT));
            bts[i].setBackground(st);
            bts[i].setTextColor(s ? 0xFF06110B : TEXTO);
        }
    }

    private TextView botao(String t, boolean principal) {
        TextView b = texto(t, 15, principal ? 0xFF06110B : TEXTO, true);
        b.setAllCaps(true);
        b.setLetterSpacing(0.1f);
        b.setGravity(Gravity.CENTER);
        b.setPadding(dp(26), dp(11), dp(26), dp(11));
        b.setMinWidth(dp(130));
        StateListDrawable st = new StateListDrawable();
        st.addState(new int[] { android.R.attr.state_pressed }, caixa(principal ? 0xFF5FB883 : 0xFF1C2A24, VERDE, 8, dens));
        st.addState(new int[] { android.R.attr.state_focused }, caixa(principal ? VERDE : 0xFF1C2A24, 0xFFFFFFFF, 8, dens));
        st.addState(new int[] {}, caixa(principal ? VERDE : 0x00000000, principal ? 0 : 0xFF3A4A42, 8, dens));
        b.setBackground(st);
        b.setFocusable(true);
        b.setClickable(true);
        return b;
    }

    // ------------------------------------------------------------------ tela

    private View constroi(final AoSair aoSair) {
        FrameLayout raiz = new FrameLayout(a);
        raiz.setBackgroundColor(FUNDO);

        /* a arte do jogo, bem apagada, ao fundo */
        int arte = a.getResources().getIdentifier("splash", "drawable", a.getPackageName());
        if (arte != 0) {
            ImageView iv = new ImageView(a);
            iv.setImageResource(arte);
            iv.setScaleType(ImageView.ScaleType.CENTER_CROP);
            iv.setAlpha(0.07f);
            raiz.addView(iv, new FrameLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT));
        }

        LinearLayout coluna = new LinearLayout(a);
        coluna.setOrientation(LinearLayout.VERTICAL);
        raiz.addView(coluna, new FrameLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT));

        // cabecalho
        LinearLayout cab = new LinearLayout(a);
        cab.setGravity(Gravity.CENTER_VERTICAL);
        cab.setPadding(dp(28), dp(16), dp(28), dp(8));
        TextView tit = texto(Textos.t("AJUSTES"), 26, TEXTO, true);
        tit.setLetterSpacing(0.14f);
        cab.addView(tit);
        TextView sub = texto("   METAL GEAR SOLID 2 · HD EDITION", 12, TEXTO2, true);
        sub.setLetterSpacing(0.12f);
        cab.addView(sub);
        coluna.addView(cab);
        View linhaVerde = new View(a);
        linhaVerde.setBackgroundColor(0x557FD6A0);
        LinearLayout.LayoutParams lpv = new LinearLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, Math.max(1, dp(1)));
        lpv.leftMargin = dp(28); lpv.rightMargin = dp(28);
        coluna.addView(linhaVerde, lpv);

        // conteudo rolavel, centrado, com largura maxima
        ScrollView sv = new ScrollView(a);
        sv.setFillViewport(true);
        sv.setVerticalScrollBarEnabled(false);
        FrameLayout centro = new FrameLayout(a);
        LinearLayout cont = new LinearLayout(a);
        cont.setOrientation(LinearLayout.VERTICAL);
        cont.setPadding(dp(20), dp(4), dp(20), dp(20));
        FrameLayout.LayoutParams lpc = new FrameLayout.LayoutParams(Math.min(dp(760), a.getResources().getDisplayMetrics().widthPixels),
                ViewGroup.LayoutParams.WRAP_CONTENT, Gravity.CENTER_HORIZONTAL);
        centro.addView(cont, lpc);
        sv.addView(centro);
        coluna.addView(sv, new LinearLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, 0, 1f));

        // --- VIDEO
        cont.addView(rotuloSecao(Textos.t("VÍDEO")));
        LinearLayout c1 = cartao();
        final int[] fpsVal = { 30, 60, 0 };
        c1.addView(linha(Textos.t("Limite de quadros"), Textos.t("O MGS2 foi feito para 60. Sem limite segue a tela (até 120 Hz) e pode acelerar o jogo."),
                segmentado(new String[] { "30", "60", Textos.t("Sem limite") }, fps == 30 ? 0 : fps == 60 ? 1 : 2,
                        new AoEscolher() { @Override public void escolheu(int i) { fps = fpsVal[i]; } })));
        c1.addView(divisoria());
        c1.addView(linha(Textos.t("Imagem"), Textos.t("16:9 mantém a proporção do jogo. Esticar ocupa a tela toda, deformando um pouco."),
                segmentado(new String[] { "16:9", Textos.t("Esticar") }, esticar ? 1 : 0,
                        new AoEscolher() { @Override public void escolheu(int i) { esticar = i == 1; } })));
        c1.addView(divisoria());
        Switch swFps = new Switch(a);
        swFps.setChecked(medidor);
        swFps.getThumbDrawable().setTint(VERDE);
        swFps.setOnCheckedChangeListener(new android.widget.CompoundButton.OnCheckedChangeListener() {
            @Override public void onCheckedChanged(android.widget.CompoundButton b, boolean v) { medidor = v; }
        });
        c1.addView(linha(Textos.t("Medidor de FPS"), Textos.t("No canto da tela: quadros do jogo e, com a geração ligada, quadros na tela (reais + gerados)."), swFps));
        cont.addView(c1);

        // --- GERACAO DE QUADROS (LSFG, como no emulador Eden)
        cont.addView(rotuloSecao(Textos.t("GERAÇÃO DE QUADROS (LSFG)")));
        LinearLayout c3 = cartao();
        c3.addView(linha(Textos.t("Geração de quadros"), Textos.t("Cria um quadro intermediário entre cada quadro do jogo: 60 viram 120 sem acelerar o jogo. Usa os shaders do Lossless Scaling (Steam) e acrescenta cerca de 1 quadro de atraso no controle."),
                segmentado(new String[] { Textos.t("Desligada"), "2x (120)" }, lsfg > 0 ? 1 : 0,
                        new AoEscolher() { @Override public void escolheu(int i) { lsfg = i; } })));
        c3.addView(divisoria());
        final int[] fluxoVal = { 100, 75, 50 };
        c3.addView(linha(Textos.t("Precisão do movimento"), Textos.t("Menor deixa a GPU mais livre, com mais erro nas bordas de objetos rápidos."),
                segmentado(new String[] { "100%", "75%", "50%" }, lsfgFluxo >= 100 ? 0 : lsfgFluxo >= 75 ? 1 : 2,
                        new AoEscolher() { @Override public void escolheu(int i) { lsfgFluxo = fluxoVal[i]; } })));
        c3.addView(divisoria());
        TextView importar = botao(Textos.t("Importar"), false);
        importar.setOnClickListener(new View.OnClickListener() { @Override public void onClick(View v) { pedeDll(a); } });
        statusDll = texto(textoDll(a), 12.5f, AjustesMGS2.temDll(a) ? VERDE : 0xFFE0B060, false);
        LinearLayout ld = linha("Lossless.dll", null, importar);
        ((LinearLayout) ld.getChildAt(0)).addView(statusDll);
        c3.addView(ld);
        cont.addView(c3);

        // --- CONTROLES
        cont.addView(rotuloSecao(Textos.t("CONTROLES NA TELA")));
        LinearLayout c2 = cartao();
        final String[] ctlVal = { AjustesMGS2.CONTROLES_AUTO, AjustesMGS2.CONTROLES_SEMPRE, AjustesMGS2.CONTROLES_NUNCA };
        c2.addView(linha(Textos.t("Mostrar"), Textos.t("Automático esconde os botões quando um controle Bluetooth ou USB está ligado."),
                segmentado(new String[] { Textos.t("Automático"), Textos.t("Sempre"), Textos.t("Nunca") },
                        AjustesMGS2.CONTROLES_SEMPRE.equals(controles) ? 1 : AjustesMGS2.CONTROLES_NUNCA.equals(controles) ? 2 : 0,
                        new AoEscolher() { @Override public void escolheu(int i) { controles = ctlVal[i]; } })));
        c2.addView(divisoria());

        LinearLayout op = new LinearLayout(a);
        op.setGravity(Gravity.CENTER_VERTICAL);
        final TextView valor = texto(opacidade + "%", 14, VERDE, true);
        valor.setMinWidth(dp(48));
        valor.setGravity(Gravity.END);
        SeekBar sb = new SeekBar(a);
        sb.setMax(90);
        sb.setProgress(opacidade - 10);
        sb.getProgressDrawable().setTint(VERDE);
        sb.getThumb().setTint(VERDE);
        sb.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override public void onProgressChanged(SeekBar s, int v, boolean u) { opacidade = v + 10; valor.setText(opacidade + "%"); }
            @Override public void onStartTrackingTouch(SeekBar s) { }
            @Override public void onStopTrackingTouch(SeekBar s) { }
        });
        op.addView(sb, new LinearLayout.LayoutParams(estreita ? 0 : dp(220), ViewGroup.LayoutParams.WRAP_CONTENT, estreita ? 1f : 0f));
        op.addView(valor);
        c2.addView(linha(Textos.t("Opacidade dos botões"), Textos.t("Mais baixo deixa os botões discretos por cima do jogo."), op));
        c2.addView(divisoria());

        Switch sw = new Switch(a);
        sw.setChecked(vibrar);
        sw.getThumbDrawable().setTint(VERDE);
        sw.setOnCheckedChangeListener(new android.widget.CompoundButton.OnCheckedChangeListener() {
            @Override public void onCheckedChanged(android.widget.CompoundButton b, boolean v) { vibrar = v; }
        });
        c2.addView(linha(Textos.t("Vibrar ao tocar"), Textos.t("Um toque curto de vibração em cada botão."), sw));
        cont.addView(c2);

        TextView dica = texto(Textos.t("A posição e o tamanho de cada botão se ajustam em \"Controles na tela\", na tela inicial."), 12, TEXTO2, false);
        dica.setPadding(dp(4), dp(14), dp(4), 0);
        cont.addView(dica);

        // barra de baixo, fixa
        LinearLayout barra = new LinearLayout(a);
        barra.setGravity(Gravity.CENTER_VERTICAL | Gravity.END);
        barra.setBackgroundColor(0xF0050806);
        barra.setPadding(dp(28), dp(10), dp(28), dp(12));
        TextView voltar = botao(Textos.t("Voltar"), false), salvar = botao(Textos.t("Salvar"), true);
        LinearLayout.LayoutParams lb = new LinearLayout.LayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT);
        lb.leftMargin = dp(12);
        barra.addView(voltar, lb);
        barra.addView(salvar, lb);
        View topoBarra = new View(a);
        topoBarra.setBackgroundColor(BORDA);
        coluna.addView(topoBarra, new LinearLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, Math.max(1, dp(1))));
        coluna.addView(barra, new LinearLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT));

        voltar.setOnClickListener(new View.OnClickListener() { @Override public void onClick(View v) { aoSair.saiu(); } });
        salvar.setOnClickListener(new View.OnClickListener() { @Override public void onClick(View v) {
            AjustesMGS2.de(a).edit()
                    .putInt("fps", fps)
                    .putBoolean("esticar", esticar)
                    .putBoolean("medidor_fps", medidor)
                    .putString("controles", controles)
                    .putInt("ctl_opacidade", opacidade)
                    .putBoolean("vibrar", vibrar)
                    .putInt("lsfg", lsfg)
                    .putInt("lsfg_fluxo", lsfgFluxo)
                    .apply();
            AjustesMGS2.gravaNativo(a);
            aoSair.saiu();
        } });
        salvar.requestFocus();
        return raiz;
    }
}
