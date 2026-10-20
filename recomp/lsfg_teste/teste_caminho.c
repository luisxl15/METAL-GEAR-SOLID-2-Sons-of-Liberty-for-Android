/* Teste do runtime/caminho.c NO ANDROID (o PC nao tem dirent no MSVC):
 *   adb push teste_caminho /data/local/tmp/ && adb shell /data/local/tmp/teste_caminho
 * Cria arvore com maiusculas em /data/local/tmp/tc e confere rt_caminho. */
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
void rt_log(const char *f, ...) { va_list a; va_start(a, f); vprintf(f, a); va_end(a); printf("\n"); }
const char *rt_caminho(const char *p, char *buf, size_t n);

static int ruins, medidos;
static void confere(const char *pedido, const char *esperado) {
    char b[1024];
    const char *r = rt_caminho(pedido, b, sizeof b);
    medidos++;
    int ok = !strcmp(r, esperado);
    if (!ok) ruins++;
    printf("%s  %s -> %s%s%s\n", ok ? "ok  " : "FALHA", pedido, r, ok ? "" : "  (esperado ", ok ? "" : esperado);
}

int main(void) {
    system("rm -rf /data/local/tmp/tc && mkdir -p /data/local/tmp/tc/EngineSupport/Fonts && "
           "echo x > /data/local/tmp/tc/EngineSupport/Fonts/console.cfon && echo y > /data/local/tmp/tc/minusculo.txt");
    struct stat st;
    int sensivel = stat("/data/local/tmp/tc/enginesupport", &st) != 0;
    printf("este armazenamento %s maiusculas\n", sensivel ? "DIFERENCIA" : "nao diferencia");
    confere("/data/local/tmp/tc/minusculo.txt", "/data/local/tmp/tc/minusculo.txt");                      /* existe: o mesmo */
    confere("/data/local/tmp/tc/enginesupport/fonts/console.cfon", "/data/local/tmp/tc/EngineSupport/Fonts/console.cfon");
    confere("/data/local/tmp/tc/ENGINESUPPORT/FONTS/CONSOLE.CFON", "/data/local/tmp/tc/EngineSupport/Fonts/console.cfon");
    confere("/data/local/tmp/tc/enginesupport/fonts/console.cfon", "/data/local/tmp/tc/EngineSupport/Fonts/console.cfon"); /* cache */
    /* controle: nao existe com caixa nenhuma -> diretorios corrigidos, nome como pedido */
    confere("/data/local/tmp/tc/enginesupport/fonts/nao_existe.bin", "/data/local/tmp/tc/EngineSupport/Fonts/nao_existe.bin");
    confere("/data/local/tmp/tc/pasta_nova/x.sav", "/data/local/tmp/tc/pasta_nova/x.sav");
    confere("relativo/Arquivo", "relativo/Arquivo");
    printf("%d casos medidos, %d falhas\n", medidos, ruins);
    system("rm -rf /data/local/tmp/tc");
    return ruins != 0;
}
