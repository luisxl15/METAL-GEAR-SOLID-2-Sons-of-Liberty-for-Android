/* Ponte JNI: o jogo (32 bits) conversa com a JVM do Android (64 bits).
 *
 *  - jobject/jclass/jstring...: handle de 32 bits = indice numa tabela de
 *    referencias do hospedeiro.  Locais criadas durante uma chamada vinda do
 *    Java sao soltas quando ela volta (como no JNI de verdade).
 *  - jmethodID/jfieldID: handle com a assinatura guardada (para ler os
 *    argumentos variaveis do jogo).
 *  - JNIEnv do jogo: celula de 4 bytes na memoria do jogo que aponta para a
 *    tabela de 233 enderecos-ponte (jni_auto.c).  Um por thread.
 */
#include "runtime.h"
#include "jni_ponte.h"
#include <stdlib.h>
#include <string.h>

#ifndef _WIN32
JavaVM *g_vm;
static jobject g_carregador;       /* ClassLoader do app (FindClass em threads nativas) */
static jmethodID g_loadClass;
#endif

/* ---- handles de objeto ---------------------------------------------------- */
#define MAX_REF (1 << 18)
typedef struct { void *h; uint8_t global, usado; } Ref;
static Ref refs[MAX_REF];
static uint32_t livre_ref = 1;
static Trava trava_ref;
static int ref_ok;

#define LOCAIS_MAX 4096
static __thread uint32_t t_locais[LOCAIS_MAX];
static __thread int t_n_locais;
static __thread int t_profundidade;   /* >0: dentro de uma chamada vinda do Java */

static uint32_t ref_nova(void *h, int global) {
    if (!h) return 0;
    if (!ref_ok) { trava_inicia(&trava_ref); ref_ok = 1; }
    trava(&trava_ref);
    uint32_t k = livre_ref;
    for (uint32_t t = 0; t < MAX_REF && refs[k].usado; t++) k = k + 1 < MAX_REF ? k + 1 : 1;
    if (refs[k].usado) rt_fatal("JNI: tabela de referencias cheia");
    refs[k].h = h; refs[k].global = (uint8_t)global; refs[k].usado = 1;
    livre_ref = k + 1 < MAX_REF ? k + 1 : 1;
    destrava(&trava_ref);
    return k * 4 + 0x100000u;          /* nunca zero, nunca parece endereco pequeno */
}

void *jh_obj(uint32_t h) {
    if (!h) return NULL;
    uint32_t k = (h - 0x100000u) / 4;
    if (k >= MAX_REF || !refs[k].usado) { rt_log("JNI: handle invalido %08x", h); return NULL; }
    return refs[k].h;
}

uint32_t jh_local(void *o) {
    if (!o) return 0;
    uint32_t h = ref_nova(o, 0);
    if (t_n_locais < LOCAIS_MAX) t_locais[t_n_locais++] = h;
    return h;
}
uint32_t jh_global(void *o) { return ref_nova(o, 1); }

void jh_solta(uint32_t h) {
    if (!h) return;
    uint32_t k = (h - 0x100000u) / 4;
    if (k >= MAX_REF || !refs[k].usado) return;
#ifndef _WIN32
    JNIEnv *e = jh_env();
    if (refs[k].global) (*e)->DeleteGlobalRef(e, refs[k].h);
    else (*e)->DeleteLocalRef(e, refs[k].h);
#endif
    refs[k].usado = 0;
}

int jh_marca_locais(void) { t_profundidade++; return t_n_locais; }
void jh_solta_locais(int marca) {
    while (t_n_locais > marca) {
        uint32_t h = t_locais[--t_n_locais];
        uint32_t k = (h - 0x100000u) / 4;
        /* a referencia local do hospedeiro morre sozinha na volta ao Java */
        if (k < MAX_REF && refs[k].usado && !refs[k].global) refs[k].usado = 0;
    }
    t_profundidade--;
}

/* ---- ids de metodo e campo ----------------------------------------------- */
#define MAX_ID 16384
typedef struct { void *id; char *sig; int campo; } Id;
static Id ids[MAX_ID];
static uint32_t n_ids = 1;

uint32_t jh_id_novo(void *id, const char *sig, int campo) {
    if (!id) return 0;
    trava(&trava_ref);
    for (uint32_t k = 1; k < n_ids; k++)
        if (ids[k].id == id) { destrava(&trava_ref); return k * 4 + 0x200000u; }
    if (n_ids >= MAX_ID) rt_fatal("JNI: ids esgotados");
    uint32_t k = n_ids++;
    ids[k].id = id; ids[k].sig = strdup(sig ? sig : ""); ids[k].campo = campo;
    destrava(&trava_ref);
    return k * 4 + 0x200000u;
}
void *jh_id(uint32_t h, const char **sig) {
    uint32_t k = (h - 0x200000u) / 4;
    if (!h || k >= n_ids) { rt_log("JNI: id invalido %08x", h); if (sig) *sig = "()V"; return NULL; }
    if (sig) *sig = ids[k].sig;
    return ids[k].id;
}

#ifndef _WIN32
/* ---- argumentos de metodo a partir da assinatura ------------------------ */
/* modo 0: variadico (regs + pilha: float vira double, 64 bits alinhado)
 * modo 1: va_list do jogo (ponteiro; 64 bits alinhado a 8)
 * modo 2: vetor de jvalue do jogo (8 bytes cada)                           */
int jh_args(const char *sig, int modo, Args *a, uint32_t ptr, jvalue *v) {
    const char *p = sig;
    if (*p == '(') p++;
    int n = 0;
    while (*p && *p != ')') {
        char t = *p;
        while (*p == '[') p++;
        if (*p == 'L') { p = strchr(p, ';'); }
        p++;
        if (t == '[') t = 'L';
        if (modo == 2) {
            uint8_t *e = g_mem + ptr + 8 * n;
            switch (t) {
            case 'Z': v[n].z = e[0]; break;
            case 'B': v[n].b = (jbyte)e[0]; break;
            case 'C': { uint16_t x; memcpy(&x, e, 2); v[n].c = x; break; }
            case 'S': { int16_t x; memcpy(&x, e, 2); v[n].s = x; break; }
            case 'I': { int32_t x; memcpy(&x, e, 4); v[n].i = x; break; }
            case 'F': { float x; memcpy(&x, e, 4); v[n].f = x; break; }
            case 'J': { int64_t x; memcpy(&x, e, 8); v[n].j = x; break; }
            case 'D': { double x; memcpy(&x, e, 8); v[n].d = x; break; }
            default: { uint32_t x; memcpy(&x, e, 4); v[n].l = jh_obj(x); break; }
            }
        } else {
            uint32_t w; uint64_t q;
            int larga = (t == 'J' || t == 'D' || t == 'F');   /* F: promovido a double */
            if (modo == 0) {
                if (larga) q = arg64(a); else w = arg32(a);
            } else {
                if (larga) { ptr = (ptr + 7) & ~7u; memcpy(&q, g_mem + ptr, 8); ptr += 8; }
                else { memcpy(&w, g_mem + ptr, 4); ptr += 4; }
            }
            switch (t) {
            case 'Z': v[n].z = (jboolean)(w & 0xff); break;
            case 'B': v[n].b = (jbyte)w; break;
            case 'C': v[n].c = (jchar)w; break;
            case 'S': v[n].s = (jshort)w; break;
            case 'I': v[n].i = (jint)w; break;
            case 'F': { double d; memcpy(&d, &q, 8); v[n].f = (float)d; break; }
            case 'J': v[n].j = (jlong)q; break;
            case 'D': memcpy(&v[n].d, &q, 8); break;
            default: v[n].l = jh_obj(w); break;
            }
        }
        n++;
        if (n >= 64) break;
    }
    return n;
}

#endif

/* ---- JNIEnv / JavaVM do jogo --------------------------------------------- */
uint32_t jni_tabela_jogo(void);        /* jni_auto.c */
uint32_t jni_tabela_vm_jogo(void);
static uint32_t g_vm_jogo;
static __thread uint32_t t_env_jogo;
#ifndef _WIN32
static __thread JNIEnv *t_env;

JNIEnv *jh_env(void) {
    if (t_env) return t_env;
    JNIEnv *e = NULL;
    if ((*g_vm)->GetEnv(g_vm, (void **)&e, JNI_VERSION_1_6) != JNI_OK) {
        (*g_vm)->AttachCurrentThread(g_vm, &e, NULL);
    }
    t_env = e;
    return e;
}
void jh_define_env(JNIEnv *e) { t_env = e; }
#endif

uint32_t jh_env_jogo(void) {
    if (t_env_jogo) return t_env_jogo;
    uint32_t cel = heap_malloc(4);
    uint32_t tab = jni_tabela_jogo();
    memcpy(g_mem + cel, &tab, 4);
    t_env_jogo = cel;
    return cel;
}
uint32_t jh_vm_jogo(void) {
    if (!g_vm_jogo) {
        uint32_t cel = heap_malloc(4);
        uint32_t tab = jni_tabela_vm_jogo();
        memcpy(g_mem + cel, &tab, 4);
        g_vm_jogo = cel;
    }
    return g_vm_jogo;
}

/* ---- funcoes da tabela escritas a mao ------------------------------------ */
#ifndef _WIN32
void J_GetVersion(CPU *c) { ret32(c, JNI_VERSION_1_6); }

void J_FindClass(CPU *c) {
    JNIEnv *e = jh_env();
    const char *nome = G2H(c->r[1]);
    jclass k = (*e)->FindClass(e, nome);
    if (!k && g_carregador) {
        (*e)->ExceptionClear(e);
        char pontos[512]; snprintf(pontos, sizeof pontos, "%s", nome);
        for (char *q = pontos; *q; q++) if (*q == '/') *q = '.';
        jstring s = (*e)->NewStringUTF(e, pontos);
        k = (*e)->CallObjectMethod(e, g_carregador, g_loadClass, s);
        (*e)->DeleteLocalRef(e, s);
        if ((*e)->ExceptionCheck(e)) { (*e)->ExceptionClear(e); k = NULL; }
    }
    if (!k) rt_log("JNI FindClass(%s) falhou", nome);
    ret32(c, jh_local(k));
}
void J_GetObjectClass(CPU *c) { JNIEnv *e = jh_env(); ret32(c, jh_local((*e)->GetObjectClass(e, jh_obj(c->r[1])))); }
void J_GetSuperclass(CPU *c) { JNIEnv *e = jh_env(); ret32(c, jh_local((*e)->GetSuperclass(e, jh_obj(c->r[1])))); }
void J_IsInstanceOf(CPU *c) { JNIEnv *e = jh_env(); ret32(c, (*e)->IsInstanceOf(e, jh_obj(c->r[1]), jh_obj(c->r[2]))); }
void J_IsSameObject(CPU *c) { JNIEnv *e = jh_env(); ret32(c, (*e)->IsSameObject(e, jh_obj(c->r[1]), jh_obj(c->r[2]))); }
void J_IsAssignableFrom(CPU *c) { JNIEnv *e = jh_env(); ret32(c, (*e)->IsAssignableFrom(e, jh_obj(c->r[1]), jh_obj(c->r[2]))); }

static void ids_(CPU *c, int estatico, int campo) {
    JNIEnv *e = jh_env();
    jclass k = jh_obj(c->r[1]);
    const char *n = G2H(c->r[2]), *s = G2H(c->r[3]);
    void *id;
    if (campo) id = estatico ? (void *)(*e)->GetStaticFieldID(e, k, n, s) : (void *)(*e)->GetFieldID(e, k, n, s);
    else id = estatico ? (void *)(*e)->GetStaticMethodID(e, k, n, s) : (void *)(*e)->GetMethodID(e, k, n, s);
    if (!id) { rt_log("JNI: %s %s%s nao achado", campo ? "campo" : "metodo", n, s); (*e)->ExceptionClear(e); }
    ret32(c, jh_id_novo(id, s, campo));
}
void J_GetMethodID(CPU *c) { ids_(c, 0, 0); }
void J_GetStaticMethodID(CPU *c) { ids_(c, 1, 0); }
void J_GetFieldID(CPU *c) { ids_(c, 0, 1); }
void J_GetStaticFieldID(CPU *c) { ids_(c, 1, 1); }

void J_NewGlobalRef(CPU *c) { JNIEnv *e = jh_env(); ret32(c, jh_global((*e)->NewGlobalRef(e, jh_obj(c->r[1])))); }
void J_NewWeakGlobalRef(CPU *c) { JNIEnv *e = jh_env(); ret32(c, jh_global((*e)->NewGlobalRef(e, jh_obj(c->r[1])))); }
void J_NewLocalRef(CPU *c) { JNIEnv *e = jh_env(); ret32(c, jh_local((*e)->NewLocalRef(e, jh_obj(c->r[1])))); }
void J_DeleteGlobalRef(CPU *c) { jh_solta(c->r[1]); }
void J_DeleteWeakGlobalRef(CPU *c) { jh_solta(c->r[1]); }
void J_DeleteLocalRef(CPU *c) { jh_solta(c->r[1]); }
void J_EnsureLocalCapacity(CPU *c) { ret32(c, 0); }
void J_PushLocalFrame(CPU *c) { ret32(c, 0); }
void J_PopLocalFrame(CPU *c) { ret32(c, c->r[1]); }
void J_GetObjectRefType(CPU *c) { uint32_t k = (c->r[1] - 0x100000u) / 4; ret32(c, k < MAX_REF && refs[k].usado ? (refs[k].global ? 2 : 1) : 0); }

void J_ExceptionCheck(CPU *c) { JNIEnv *e = jh_env(); ret32(c, (*e)->ExceptionCheck(e)); }
void J_ExceptionOccurred(CPU *c) { JNIEnv *e = jh_env(); ret32(c, jh_local((*e)->ExceptionOccurred(e))); }
void J_ExceptionClear(CPU *c) { JNIEnv *e = jh_env(); (*e)->ExceptionClear(e); }
void J_ExceptionDescribe(CPU *c) { JNIEnv *e = jh_env(); (*e)->ExceptionDescribe(e); }
void J_Throw(CPU *c) { JNIEnv *e = jh_env(); ret32(c, (*e)->Throw(e, jh_obj(c->r[1]))); }
void J_ThrowNew(CPU *c) { JNIEnv *e = jh_env(); ret32(c, (*e)->ThrowNew(e, jh_obj(c->r[1]), G2H(c->r[2]))); }
void J_FatalError(CPU *c) { rt_fatal("JNI FatalError do jogo: %s", (char *)G2H(c->r[1])); }
void J_MonitorEnter(CPU *c) { JNIEnv *e = jh_env(); ret32(c, (*e)->MonitorEnter(e, jh_obj(c->r[1]))); }
void J_MonitorExit(CPU *c) { JNIEnv *e = jh_env(); ret32(c, (*e)->MonitorExit(e, jh_obj(c->r[1]))); }
void J_GetJavaVM(CPU *c) { uint32_t v = jh_vm_jogo(); memcpy(g_mem + c->r[1], &v, 4); ret32(c, 0); }
void J_RegisterNatives(CPU *c) { rt_log("JNI RegisterNatives pedido pelo jogo (%u metodos) - ignorado", c->r[3]); ret32(c, 0); }
void J_UnregisterNatives(CPU *c) { ret32(c, 0); }

/* strings */
void J_NewStringUTF(CPU *c) { JNIEnv *e = jh_env(); ret32(c, jh_local((*e)->NewStringUTF(e, G2H(c->r[1])))); }
void J_GetStringUTFLength(CPU *c) { JNIEnv *e = jh_env(); ret32(c, (*e)->GetStringUTFLength(e, jh_obj(c->r[1]))); }
void J_GetStringLength(CPU *c) { JNIEnv *e = jh_env(); ret32(c, (*e)->GetStringLength(e, jh_obj(c->r[1]))); }
void J_GetStringUTFChars(CPU *c) {
    JNIEnv *e = jh_env();
    const char *s = (*e)->GetStringUTFChars(e, jh_obj(c->r[1]), NULL);
    uint32_t g = guest_strdup(s ? s : "");
    if (s) (*e)->ReleaseStringUTFChars(e, jh_obj(c->r[1]), s);
    if (c->r[2]) g_mem[c->r[2]] = 1;
    ret32(c, g);
}
void J_ReleaseStringUTFChars(CPU *c) { heap_free(c->r[2]); }
void J_GetStringChars(CPU *c) {
    JNIEnv *e = jh_env();
    jstring js = jh_obj(c->r[1]);
    jsize n = (*e)->GetStringLength(e, js);
    uint32_t g = heap_malloc((uint32_t)(n + 1) * 2);
    (*e)->GetStringRegion(e, js, 0, n, (jchar *)G2H(g));
    memset(g_mem + g + 2 * n, 0, 2);
    if (c->r[2]) g_mem[c->r[2]] = 1;
    ret32(c, g);
}
void J_ReleaseStringChars(CPU *c) { heap_free(c->r[2]); }
void J_NewString(CPU *c) { JNIEnv *e = jh_env(); ret32(c, jh_local((*e)->NewString(e, G2H(c->r[1]), (jsize)c->r[2]))); }
void J_GetStringRegion(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    uint32_t s = arg32(&a), ini = arg32(&a), n = arg32(&a), buf = arg32(&a);
    (*e)->GetStringRegion(e, jh_obj(s), (jsize)ini, (jsize)n, G2H(buf));
}
void J_GetStringUTFRegion(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    uint32_t s = arg32(&a), ini = arg32(&a), n = arg32(&a), buf = arg32(&a);
    (*e)->GetStringUTFRegion(e, jh_obj(s), (jsize)ini, (jsize)n, G2H(buf));
}
void J_GetStringCritical(CPU *c) { J_GetStringChars(c); }
void J_ReleaseStringCritical(CPU *c) { heap_free(c->r[2]); }

/* arrays genericos */
void J_GetArrayLength(CPU *c) { JNIEnv *e = jh_env(); ret32(c, (*e)->GetArrayLength(e, jh_obj(c->r[1]))); }
void J_NewObjectArray(CPU *c) {
    JNIEnv *e = jh_env();
    ret32(c, jh_local((*e)->NewObjectArray(e, (jsize)c->r[1], jh_obj(c->r[2]), jh_obj(c->r[3]))));
}
void J_GetObjectArrayElement(CPU *c) { JNIEnv *e = jh_env(); ret32(c, jh_local((*e)->GetObjectArrayElement(e, jh_obj(c->r[1]), (jsize)c->r[2]))); }
void J_SetObjectArrayElement(CPU *c) { JNIEnv *e = jh_env(); (*e)->SetObjectArrayElement(e, jh_obj(c->r[1]), (jsize)c->r[2], jh_obj(c->r[3])); }
/* buffers diretos: a memoria do jogo e do proprio processo, entao o Java le/escreve
 * direto em g_mem + endereco */
void J_NewDirectByteBuffer(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    uint32_t ad = arg32(&a); uint64_t cap = arg64(&a);
    ret32(c, jh_local((*e)->NewDirectByteBuffer(e, g_mem + ad, (jlong)cap)));
}
void J_GetDirectBufferAddress(CPU *c) {
    JNIEnv *e = jh_env();
    uint8_t *p = (*e)->GetDirectBufferAddress(e, jh_obj(c->r[1]));
    if (p && p >= g_mem && p < g_mem + 0x100000000ull) { ret32(c, (uint32_t)(p - g_mem)); return; }
    rt_log("JNI GetDirectBufferAddress: buffer fora da memoria do jogo (%p)", p);
    ret32(c, 0);
}
void J_GetDirectBufferCapacity(CPU *c) {
    JNIEnv *e = jh_env();
    ret64(c, (uint64_t)(*e)->GetDirectBufferCapacity(e, jh_obj(c->r[1])));
}

/* construtores */
static void novo_(CPU *c, int modo) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jclass k = jh_obj(arg32(&a)); const char *sig; jmethodID m = jh_id(arg32(&a), &sig);
    jvalue v[64];
    uint32_t ptr = modo ? arg32(&a) : 0;
    jh_args(sig, modo, &a, ptr, v);
    ret32(c, jh_local((*e)->NewObjectA(e, k, m, v)));
}
void J_NewObject(CPU *c) { novo_(c, 0); }
void J_NewObjectV(CPU *c) { novo_(c, 1); }
void J_NewObjectA(CPU *c) { novo_(c, 2); }
void J_AllocObject(CPU *c) { JNIEnv *e = jh_env(); ret32(c, jh_local((*e)->AllocObject(e, jh_obj(c->r[1])))); }

/* ---- JavaVM do jogo ------------------------------------------------------- */
void V_GetEnv(CPU *c) { uint32_t env = jh_env_jogo(); memcpy(g_mem + c->r[1], &env, 4); jh_env(); ret32(c, 0); }
void V_AttachCurrentThread(CPU *c) { jh_env(); uint32_t env = jh_env_jogo(); memcpy(g_mem + c->r[1], &env, 4); ret32(c, 0); }
void V_AttachCurrentThreadAsDaemon(CPU *c) { V_AttachCurrentThread(c); }
void V_DetachCurrentThread(CPU *c) { (*g_vm)->DetachCurrentThread(g_vm); t_env = NULL; ret32(c, 0); }
void V_DestroyJavaVM(CPU *c) { ret32(c, 0); }

/* ---- ligacao com o Java --------------------------------------------------- */
void jh_inicia(JavaVM *vm, JNIEnv *e, jobject contexto_ou_classe) {
    g_vm = vm;
    t_env = e;
    /* pega o ClassLoader do app a partir de uma classe dele */
    jclass k = (*e)->FindClass(e, "com/nvidia/forge/MainActivity");
    if (k) {
        jclass kc = (*e)->FindClass(e, "java/lang/Class");
        jmethodID gcl = (*e)->GetMethodID(e, kc, "getClassLoader", "()Ljava/lang/ClassLoader;");
        jobject cl = (*e)->CallObjectMethod(e, k, gcl);
        g_carregador = (*e)->NewGlobalRef(e, cl);
        jclass kl = (*e)->FindClass(e, "java/lang/ClassLoader");
        g_loadClass = (*e)->GetMethodID(e, kl, "loadClass", "(Ljava/lang/String;)Ljava/lang/Class;");
    }
    (void)contexto_ou_classe;
}
#endif
