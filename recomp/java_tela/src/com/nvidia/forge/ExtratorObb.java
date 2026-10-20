package com.nvidia.forge;

import android.content.Context;
import android.os.StatFs;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.RandomAccessFile;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.channels.Channels;
import java.nio.channels.FileChannel;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.atomic.AtomicLong;
import java.util.concurrent.atomic.AtomicReference;
import java.util.zip.CRC32;
import java.util.zip.Inflater;
import java.util.zip.InflaterInputStream;

/**
 * Tira os arquivos de dentro das OBBs (main.14 e patch.14) para files/, no proprio celular,
 * na primeira vez que o jogo e aberto. O motor le os arquivos SOLTOS de files/ (a Forge do
 * SHIELD montava as OBBs com mountObb, que o Android atual nao tem mais).
 *
 * Igual ao extrair_obb.py do PC: os cabecalhos locais destas OBBs tem o NOME VAZIO (so o
 * diretorio central tem os nomes) e o ZipFile do Android recusa; lemos pelo deslocamento.
 * Medido no PC: sem ZIP64, sem nomes repetidos entre main e patch, quase tudo deflate.
 *
 * Varias threads, CRC32 conferido em cada arquivo, grava em .tmp e renomeia. Retoma: um
 * arquivo que ja esta la com o tamanho certo e pulado (extracao interrompida continua).
 * No fim grava files/.extraido (o mesmo marcador que o instalar.sh do PC usa).
 */
final class ExtratorObb {
    static final String[] OBBS = { "main.14.jp.konami.mgs2hd.shield.obb", "patch.14.jp.konami.mgs2hd.shield.obb" };
    static final String MARCA = ".extraido";

    interface Progresso { void andou(long feito, long total, int arquivos, int totalArquivos); }

    private static final class Entrada {
        String nome; int metodo; long crc, comprimido, tamanho, local; File obb;
    }

    private ExtratorObb() { }

    static File destino(Context c) { return c.getExternalFilesDir(null); }

    /** os dados ja estao em files/ (extraidos aqui ou empurrados pelo PC)? */
    static boolean pronto(Context c) {
        File d = destino(c);
        return d != null && new File(d, MARCA).isFile();
    }

    /** as OBBs que existem (pasta obb do app); vazio = nao copiaram as OBBs */
    static List<File> obbs(Context c) {
        List<File> r = new ArrayList<>();
        File d = c.getObbDir();
        for (String n : OBBS) {
            File f = d == null ? null : new File(d, n);
            if (f != null && f.isFile()) r.add(f);
        }
        return r;
    }

    // ---------------------------------------------------------------- leitura do ZIP

    private static List<Entrada> diretorio(File obb) throws IOException {
        try (RandomAccessFile raf = new RandomAccessFile(obb, "r"); FileChannel ch = raf.getChannel()) {
            long tam = ch.size();
            int janela = (int) Math.min(tam, 65557);
            ByteBuffer fim = ByteBuffer.allocate(janela).order(ByteOrder.LITTLE_ENDIAN);
            ch.read(fim, tam - janela);
            int eocd = -1;
            for (int i = janela - 22; i >= 0; i--) if (fim.getInt(i) == 0x06054b50) { eocd = i; break; }
            if (eocd < 0) throw new IOException(obb.getName() + ": fim do diretorio central nao encontrado");
            int n = fim.getShort(eocd + 10) & 0xffff;
            long cdTam = fim.getInt(eocd + 12) & 0xffffffffL, cdIni = fim.getInt(eocd + 16) & 0xffffffffL;
            ByteBuffer cd = ByteBuffer.allocate((int) cdTam).order(ByteOrder.LITTLE_ENDIAN);
            while (cd.hasRemaining()) if (ch.read(cd, cdIni + cd.position()) < 0) throw new IOException("diretorio central truncado");
            List<Entrada> l = new ArrayList<>(n);
            int p = 0;
            byte[] nome = new byte[1024];
            for (int k = 0; k < n; k++) {
                if (cd.getInt(p) != 0x02014b50) throw new IOException(obb.getName() + ": entrada " + k + " invalida");
                Entrada e = new Entrada();
                e.metodo = cd.getShort(p + 10) & 0xffff;
                e.crc = cd.getInt(p + 16) & 0xffffffffL;
                e.comprimido = cd.getInt(p + 20) & 0xffffffffL;
                e.tamanho = cd.getInt(p + 24) & 0xffffffffL;
                int ln = cd.getShort(p + 28) & 0xffff, lx = cd.getShort(p + 30) & 0xffff, lc = cd.getShort(p + 32) & 0xffff;
                e.local = cd.getInt(p + 42) & 0xffffffffL;
                cd.position(p + 46); cd.get(nome, 0, ln);
                e.nome = new String(nome, 0, ln, "UTF-8");
                e.obb = obb;
                p += 46 + ln + lx + lc;
                if (e.nome.endsWith("/")) continue;                         // pasta
                if (e.nome.startsWith("/") || e.nome.contains("..")) throw new IOException("nome perigoso no ZIP: " + e.nome);
                if (e.metodo != 0 && e.metodo != 8) throw new IOException(e.nome + ": compressao " + e.metodo);
                l.add(e);
            }
            return l;
        }
    }

    /** extrai um arquivo; o canal e da thread (posicoes absolutas, sem estado compartilhado) */
    private static void extraiUm(FileChannel ch, Entrada e, File dst, byte[] buf, AtomicLong feito) throws IOException {
        ByteBuffer cab = ByteBuffer.allocate(30).order(ByteOrder.LITTLE_ENDIAN);
        ch.read(cab, e.local);
        if (cab.getInt(0) != 0x04034b50) throw new IOException(e.nome + ": cabecalho local invalido");
        long dados = e.local + 30 + (cab.getShort(26) & 0xffff) + (cab.getShort(28) & 0xffff);
        File tmp = new File(dst.getPath() + ".tmp");
        CRC32 crc = new CRC32();
        long escrito = 0;
        InputStream bruto = new LimitadoEm(ch, dados, e.comprimido);
        Inflater inf = e.metodo == 8 ? new Inflater(true) : null;
        try (InputStream in = inf != null ? new InflaterInputStream(bruto, inf, 1 << 16) : bruto;
             FileOutputStream out = new FileOutputStream(tmp)) {
            int r;
            while ((r = in.read(buf)) > 0) {
                out.write(buf, 0, r); crc.update(buf, 0, r); escrito += r; feito.addAndGet(r);
            }
        } finally {
            if (inf != null) inf.end();
        }
        if (escrito != e.tamanho || crc.getValue() != e.crc) {
            tmp.delete();
            throw new IOException(e.nome + ": CRC/tamanho errado (" + escrito + " de " + e.tamanho + ")");
        }
        if (dst.exists()) dst.delete();
        if (!tmp.renameTo(dst)) throw new IOException("nao renomeou " + tmp);
    }

    /** InputStream sobre um trecho do arquivo, por posicao absoluta (thread-safe por canal) */
    private static final class LimitadoEm extends InputStream {
        private final FileChannel ch; private long pos; private long resta;
        LimitadoEm(FileChannel ch, long ini, long tam) { this.ch = ch; pos = ini; resta = tam; }
        @Override public int read() throws IOException { byte[] b = new byte[1]; return read(b, 0, 1) < 0 ? -1 : b[0] & 0xff; }
        @Override public int read(byte[] b, int o, int n) throws IOException {
            if (resta <= 0) return -1;
            int r = ch.read(ByteBuffer.wrap(b, o, (int) Math.min(n, resta)), pos);
            if (r <= 0) return -1;
            pos += r; resta -= r; return r;
        }
    }

    // ---------------------------------------------------------------- extracao

    /** Extrai tudo (bloqueante; chame fora da thread da interface). Devolve null = ok, ou o erro. */
    static String extrai(Context c, final Progresso prog) {
        final File dst = destino(c);
        if (dst == null) return Textos.t("Armazenamento do app indisponível.");
        List<File> obbs = obbs(c);
        if (obbs.size() < OBBS.length)
            return Textos.t("Faltam as OBBs do jogo. Copie main.14 e patch.14 para Android/obb/jp.konami.mgs2hd.shield/ e abra de novo.");
        final List<Entrada> todas = new ArrayList<>();
        long total = 0, falta = 0;
        try {
            for (File o : obbs) todas.addAll(diretorio(o));
        } catch (IOException e) {
            return Textos.f("OBB ilegível: %s", e.getMessage());
        }
        for (Entrada e : todas) {
            total += e.tamanho;
            File f = new File(dst, e.nome);
            if (!(f.isFile() && f.length() == e.tamanho)) falta += e.tamanho;
        }
        long livre = new StatFs(dst.getPath()).getAvailableBytes();
        if (livre < falta + (256L << 20))
            return Textos.f("Espaço insuficiente: precisa de %.1f GB livres, há %.1f GB.",
                    (falta + (256L << 20)) / 1e9, livre / 1e9);
        return extraiPara(todas, dst, total, prog);
    }

    /** O mesmo caminho sem nada do Android (teste no PC: lsfg_teste/TesteExtrator.java). */
    static String extraiObbs(List<File> obbs, File dst, Progresso prog) {
        List<Entrada> todas = new ArrayList<>();
        long total = 0;
        try {
            for (File o : obbs) todas.addAll(diretorio(o));
        } catch (IOException e) {
            return Textos.f("OBB ilegível: %s", e.getMessage());
        }
        for (Entrada e : todas) total += e.tamanho;
        return extraiPara(todas, dst, total, prog);
    }

    private static String extraiPara(final List<Entrada> todas, final File dst, long total, final Progresso prog) {
        // maiores primeiro: as threads terminam juntas
        Collections.sort(todas, new Comparator<Entrada>() {
            @Override public int compare(Entrada a, Entrada b) { return Long.compare(b.tamanho, a.tamanho); }
        });
        final long totalF = total;
        final AtomicLong feito = new AtomicLong();
        final AtomicInteger proxima = new AtomicInteger(), arquivos = new AtomicInteger();
        final AtomicReference<String> erro = new AtomicReference<>();
        int nThreads = Math.max(2, Math.min(4, Runtime.getRuntime().availableProcessors()));
        Thread[] ts = new Thread[nThreads];
        for (int t = 0; t < nThreads; t++) {
            ts[t] = new Thread(new Runnable() {
                @Override public void run() {
                    byte[] buf = new byte[1 << 17];
                    java.util.Map<File, FileChannel> canais = new java.util.HashMap<>();
                    try {
                        int k;
                        while (erro.get() == null && (k = proxima.getAndIncrement()) < todas.size()) {
                            Entrada e = todas.get(k);
                            File f = new File(dst, e.nome);
                            if (f.isFile() && f.length() == e.tamanho) { feito.addAndGet(e.tamanho); arquivos.incrementAndGet(); continue; }
                            File pai = f.getParentFile();
                            if (pai != null && !pai.isDirectory() && !pai.mkdirs() && !pai.isDirectory()) throw new IOException("nao criou " + pai);
                            FileChannel ch = canais.get(e.obb);
                            if (ch == null) { ch = new RandomAccessFile(e.obb, "r").getChannel(); canais.put(e.obb, ch); }
                            extraiUm(ch, e, f, buf, feito);
                            arquivos.incrementAndGet();
                        }
                    } catch (Throwable x) {
                        erro.compareAndSet(null, x.getMessage() != null ? x.getMessage() : x.toString());
                    } finally {
                        for (FileChannel ch : canais.values()) try { ch.close(); } catch (IOException ignorado) { }
                    }
                }
            }, "MGS2 extrai OBB " + t);
            ts[t].start();
        }
        while (true) {
            boolean vivo = false;
            for (Thread t : ts) vivo |= t.isAlive();
            if (prog != null) prog.andou(feito.get(), totalF, arquivos.get(), todas.size());
            if (!vivo) break;
            try { Thread.sleep(250); } catch (InterruptedException ignorado) { }
        }
        if (erro.get() != null) return Textos.f("Falha ao extrair: %s", erro.get());
        try (FileOutputStream m = new FileOutputStream(new File(dst, MARCA))) {
            m.write(("main.14 + patch.14 (extraido no aparelho, " + todas.size() + " arquivos)\n").getBytes("UTF-8"));
        } catch (IOException e) {
            return Textos.f("Não gravou o marcador: %s", e.getMessage());
        }
        return null;
    }
}
