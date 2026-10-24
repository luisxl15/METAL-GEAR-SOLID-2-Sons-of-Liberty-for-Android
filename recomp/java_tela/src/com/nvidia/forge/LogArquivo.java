package com.nvidia.forge;

import android.content.Context;
import android.os.Build;
import java.io.File;
import java.io.FileWriter;
import java.io.PrintWriter;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Locale;

/**
 * O log em arquivo: Android/data/<pacote>/files/mgs2_log.txt, para quem nao tem PC com adb
 * mandar o log de um problema (o logcat e um buffer em memoria que some em minutos).
 *
 * Aqui, uma vez por abertura do app: o log da vez anterior vira mgs2_log_anterior.txt (e o
 * que interessa depois de um crash) e as excecoes Java nao tratadas sao anexadas ao arquivo.
 * As linhas do jogo (MGS2-RT, inclusive os sinais fatais) sao escritas pelo lado nativo.
 */
final class LogArquivo {
    static final String NOME = "mgs2_log.txt", ANTERIOR = "mgs2_log_anterior.txt";
    private static File arquivo;

    private LogArquivo() { }

    static void inicia(Context c) {
        File dir = c.getExternalFilesDir(null);
        if (dir == null) return;
        arquivo = new File(dir, NOME);
        File ant = new File(dir, ANTERIOR);
        if (arquivo.exists()) { ant.delete(); arquivo.renameTo(ant); }
        String versao = "?";
        try { versao = c.getPackageManager().getPackageInfo(c.getPackageName(), 0).versionName; } catch (Exception e) { }
        anexa("==== app aberto: " + Build.MANUFACTURER + " " + Build.MODEL + ", Android " + Build.VERSION.RELEASE
                + " (SDK " + Build.VERSION.SDK_INT + "), versao " + versao + " ====");
        final Thread.UncaughtExceptionHandler antes = Thread.getDefaultUncaughtExceptionHandler();
        Thread.setDefaultUncaughtExceptionHandler(new Thread.UncaughtExceptionHandler() {
            @Override public void uncaughtException(Thread t, Throwable e) {
                try {
                    FileWriter w = new FileWriter(arquivo, true);
                    PrintWriter p = new PrintWriter(w);
                    p.println(hora() + " ERRO FATAL (Java) na thread " + t.getName() + ":");
                    e.printStackTrace(p);
                    p.close();
                } catch (Throwable ignora) { }
                if (antes != null) antes.uncaughtException(t, e);
            }
        });
    }

    static void anexa(String linha) {
        if (arquivo == null) return;
        try {
            FileWriter w = new FileWriter(arquivo, true);
            w.write(hora() + " " + linha + "\n");
            w.close();
        } catch (Exception e) { }
    }

    private static String hora() { return new SimpleDateFormat("HH:mm:ss.SSS", Locale.ROOT).format(new Date()); }
}
