package com.nvidia.forge;

import android.app.Activity;
import android.graphics.Typeface;
import android.os.Handler;
import android.os.Looper;
import android.os.SystemClock;
import android.view.Gravity;
import android.view.View;
import android.view.ViewGroup;
import android.widget.FrameLayout;
import android.widget.TextView;

/**
 * Medidor de FPS por cima do jogo, no canto superior esquerdo.
 *
 * Os numeros vem do runtime nativo (libMGS2HD.so, android.c), NAO do Choreographer da
 * interface: "FPS" sao os quadros que chegaram a tela (com o LSFG, reais + gerados);
 * "VELOCIDADE" e o ritmo da logica do jogo sobre 60 (os eglSwapBuffers, pulados ou nao).
 */
final class MedidorFps {
    private static final long PERIODO_MS = 500;
    private static final Object MARCA = new Object();

    /** contadores acumulados: [jogo, tela, gerados, lsfg ligado] (ver android.c) */
    static native long[] contadores();

    private MedidorFps() { }

    static void poe(final Activity a) {
        if (!AjustesMGS2.medidorFps(a)) return;
        final ViewGroup raiz = (ViewGroup) a.getWindow().getDecorView();
        for (int i = 0; i < raiz.getChildCount(); i++)
            if (raiz.getChildAt(i).getTag() == MARCA) return;     // ja esta na tela

        final float d = a.getResources().getDisplayMetrics().density;
        final TextView tv = new TextView(a);
        tv.setTag(MARCA);
        tv.setTypeface(Typeface.MONOSPACE, Typeface.BOLD);
        tv.setTextSize(12);
        tv.setTextColor(TelaAjustes.VERDE);
        tv.setShadowLayer(2 * d, 0, 0, 0xFF000000);
        tv.setBackground(TelaAjustes.caixa(0x99050806, 0x557FD6A0, 6, d));
        tv.setPadding((int) (8 * d), (int) (4 * d), (int) (8 * d), (int) (4 * d));
        tv.setText("FPS ...");
        tv.setClickable(false);
        tv.setFocusable(false);
        tv.setImportantForAccessibility(View.IMPORTANT_FOR_ACCESSIBILITY_NO);
        FrameLayout.LayoutParams lp = new FrameLayout.LayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT,
                ViewGroup.LayoutParams.WRAP_CONTENT, Gravity.TOP | Gravity.START);
        lp.leftMargin = (int) (14 * d);
        lp.topMargin = (int) (10 * d);
        raiz.addView(tv, lp);

        final Handler h = new Handler(Looper.getMainLooper());
        h.post(new Runnable() {
            long[] antes;
            long tAntes;

            @Override public void run() {
                if (tv.getParent() == null) return;                 // a tela saiu: para
                long[] c = null;
                try { c = contadores(); } catch (Throwable t) { /* a biblioteca ainda nao subiu */ }
                long t = SystemClock.elapsedRealtimeNanos();
                if (c != null && antes != null && t > tAntes) {
                    double s = (t - tAntes) / 1e9;
                    double jogo = (c[0] - antes[0]) / s, tela = (c[1] - antes[1]) / s, ger = (c[2] - antes[2]) / s;
                    /* o numero de cima e o que se ve (quadros na tela); embaixo, a velocidade do
                     * jogo: o MGS2 anda um passo por quadro e foi feito para 60. Com a velocidade
                     * constante a tela pode estar em 30 e o jogo em 100%; sem ela, 30 = 50%. */
                    String txt = String.format(java.util.Locale.ROOT, "FPS %3.0f  %4.1f ms", tela, tela > 0 ? 1000 / tela : 0);
                    if (c[3] != 0) txt += String.format(java.util.Locale.ROOT, "  LSFG +%.0f", ger);
                    txt += String.format(java.util.Locale.ROOT, "\n%s %3.0f%%", Textos.t("VELOCIDADE"), Math.min(100, jogo * 100 / 60));
                    tv.setText(txt);
                }
                if (c != null) { antes = c; tAntes = t; }
                h.postDelayed(this, PERIODO_MS);
            }
        });
    }
}
