package com.nvidia.forge;

import java.io.File;
import java.util.Collections;

/** Roda o ExtratorObb do APK (o MESMO .java) no JDK do PC sobre uma OBB real.
 *  java -cp <classes> com.nvidia.forge.TesteExtrator <obb> <pasta destino> */
public class TesteExtrator {
    public static void main(String[] a) {
        final long t0 = System.currentTimeMillis();
        final long[] ult = { 0 };
        String erro = ExtratorObb.extraiObbs(Collections.singletonList(new File(a[0])), new File(a[1]),
                new ExtratorObb.Progresso() {
                    @Override public void andou(long feito, long total, int arq, int tot) {
                        long t = System.currentTimeMillis();
                        if (t - ult[0] > 5000 || feito == total) {
                            ult[0] = t;
                            System.out.printf("  %.2f / %.2f GB, %d / %d arquivos%n", feito / 1e9, total / 1e9, arq, tot);
                        }
                    }
                });
        System.out.printf("%s em %.0f s%n", erro == null ? "OK" : "ERRO: " + erro, (System.currentTimeMillis() - t0) / 1000.0);
        System.exit(erro == null ? 0 : 1);
    }
}
