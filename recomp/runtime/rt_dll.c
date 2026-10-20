/* DLL de teste (PC): o Python chama funcoes recompiladas com estado arbitrario. */
#ifdef RT_DLL
#include "runtime.h"
#include <setjmp.h>
#include <string.h>
extern jmp_buf *g_fatal_jmp;
void mem_compromete(uint32_t ini, uint32_t tam);
__declspec(dllexport) uint8_t *dll_inicia(void) {
    mem_inicia(); heap_inicia();
    mem_compromete(0x70000000u, 0x100000u);     /* janela dos testes */
    return g_mem;
}
/* regs: r0..r15, depois n z c v; devolve 0 ok, 1 rt_fatal */
__declspec(dllexport) int dll_chama(uint32_t fn, uint32_t *regs) {
    CPU *c = cpu_atual();
    memcpy(c->r, regs, 64);
    c->fn = regs[16]; c->fz = regs[17]; c->fc = regs[18]; c->fv = regs[19];
    c->r[14] = 0xfffffff0u;
    memset(&c->v, 0, sizeof c->v); c->fpnzcv = 0; c->fpscr = 0; c->ex_ok = 0;
    jmp_buf j;
    if (setjmp(j)) { g_fatal_jmp = NULL; return 1; }
    g_fatal_jmp = &j;
    despacha(c, fn);
    g_fatal_jmp = NULL;
    memcpy(regs, c->r, 64);
    regs[16] = c->fn; regs[17] = c->fz; regs[18] = c->fc; regs[19] = c->fv;
    return 0;
}
#endif
