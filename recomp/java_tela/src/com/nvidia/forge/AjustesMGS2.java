package com.nvidia.forge;

import android.content.Context;
import android.content.SharedPreferences;
import java.io.File;
import java.io.FileOutputStream;

/**
 * Ajustes do usuario. Ficam em SharedPreferences e os que o runtime nativo usa
 * (limite de quadros) sao gravados tambem em
 * files/mgs2_ajustes.txt da pasta externa (runtime/ajustes.c le no arranque).
 */
public final class AjustesMGS2 {
    public static final String CONTROLES_AUTO = "auto", CONTROLES_SEMPRE = "sempre", CONTROLES_NUNCA = "nunca";

    private AjustesMGS2() { }

    public static SharedPreferences de(Context c) {
        return c.getSharedPreferences("mgs2_ajustes", Context.MODE_PRIVATE);
    }

    /** limite de quadros: 30, 60 ou 0 (sem limite). O jogo foi feito para 60. */
    public static int fps(Context c) { return de(c).getInt("fps", 60); }
    public static String controles(Context c) { return de(c).getString("controles", CONTROLES_AUTO); }
    public static boolean vibrar(Context c) { return de(c).getBoolean("vibrar", true); }
    /** imagem esticada para a tela inteira (padrao: 16:9 original com faixas pretas) */
    public static boolean esticar(Context c) { return de(c).getBoolean("esticar", false); }
    /** geracao de quadros LSFG: 0 desligada, 1 = 2x (um quadro gerado por quadro do jogo) */
    public static int lsfg(Context c) { return de(c).getInt("lsfg", 0); }
    /** medidor de FPS (jogo / tela) no canto da tela durante o jogo */
    public static boolean medidorFps(Context c) { return de(c).getBoolean("medidor_fps", true); }
    /** escala do fluxo optico em %: menor = mais leve para a GPU, menos preciso */
    public static int lsfgFluxo(Context c) { return de(c).getInt("lsfg_fluxo", 100); }

    /** onde o runtime le os shaders do Lossless Scaling (o Lossless.dll do usuario) */
    public static File arquivoDll(Context c) {
        File d = c.getExternalFilesDir(null);
        return d == null ? null : new File(d, "Lossless.dll");
    }
    public static boolean temDll(Context c) {
        File f = arquivoDll(c);
        return f != null && f.isFile() && f.length() > 1024 * 1024;
    }

    /** taxa que a tela deve usar: com a geracao, o limite do jogo vezes (geracoes + 1) */
    public static int taxaTela(Context c) {
        int f = fps(c);
        if (f > 0 && lsfg(c) > 0 && temDll(c)) return f * (lsfg(c) + 1);
        return f;
    }

    public static void gravaNativo(Context c) {
        try {
            File d = c.getExternalFilesDir(null);
            if (d == null) return;
            String txt = "fps=" + fps(c) + "\nesticar=" + (esticar(c) ? 1 : 0)
                    + "\nlsfg=" + lsfg(c) + "\nlsfg_fluxo=" + lsfgFluxo(c) + "\n";
            FileOutputStream o = new FileOutputStream(new File(d, "mgs2_ajustes.txt"));
            o.write(txt.getBytes("UTF-8"));
            o.close();
        } catch (Exception e) {
            android.util.Log.w("MGS2-Ajustes", "nao gravou mgs2_ajustes.txt: " + e);
        }
    }
}
