/* GERADO por gerar_jni.py */
#ifndef _WIN32
#include "jni_ponte.h"
#include <string.h>

void rt_garante(void);

void J_DefineClass(CPU *c) { (void)c; rt_fatal("JNI nao implementado: DefineClass"); }

void J_FromReflectedMethod(CPU *c) { (void)c; rt_fatal("JNI nao implementado: FromReflectedMethod"); }

void J_FromReflectedField(CPU *c) { (void)c; rt_fatal("JNI nao implementado: FromReflectedField"); }

void J_ToReflectedMethod(CPU *c) { (void)c; rt_fatal("JNI nao implementado: ToReflectedMethod"); }

void J_ToReflectedField(CPU *c) { (void)c; rt_fatal("JNI nao implementado: ToReflectedField"); }

void J_CallObjectMethod(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jobject alvo = jh_obj(arg32(&a));
    const char *sig; jmethodID m = jh_id(arg32(&a), &sig);
    uint32_t ptr = 0;
    jvalue v[64]; jh_args(sig, 0, &a, ptr, v);
    ret32(c, jh_local((*e)->CallObjectMethodA(e, alvo, m, v)));
}

void J_CallObjectMethodV(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jobject alvo = jh_obj(arg32(&a));
    const char *sig; jmethodID m = jh_id(arg32(&a), &sig);
    uint32_t ptr = arg32(&a);
    jvalue v[64]; jh_args(sig, 1, &a, ptr, v);
    ret32(c, jh_local((*e)->CallObjectMethodA(e, alvo, m, v)));
}

void J_CallObjectMethodA(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jobject alvo = jh_obj(arg32(&a));
    const char *sig; jmethodID m = jh_id(arg32(&a), &sig);
    uint32_t ptr = arg32(&a);
    jvalue v[64]; jh_args(sig, 2, &a, ptr, v);
    ret32(c, jh_local((*e)->CallObjectMethodA(e, alvo, m, v)));
}

void J_CallBooleanMethod(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jobject alvo = jh_obj(arg32(&a));
    const char *sig; jmethodID m = jh_id(arg32(&a), &sig);
    uint32_t ptr = 0;
    jvalue v[64]; jh_args(sig, 0, &a, ptr, v);
    ret32(c, (uint8_t)((*e)->CallBooleanMethodA(e, alvo, m, v)));
}

void J_CallBooleanMethodV(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jobject alvo = jh_obj(arg32(&a));
    const char *sig; jmethodID m = jh_id(arg32(&a), &sig);
    uint32_t ptr = arg32(&a);
    jvalue v[64]; jh_args(sig, 1, &a, ptr, v);
    ret32(c, (uint8_t)((*e)->CallBooleanMethodA(e, alvo, m, v)));
}

void J_CallBooleanMethodA(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jobject alvo = jh_obj(arg32(&a));
    const char *sig; jmethodID m = jh_id(arg32(&a), &sig);
    uint32_t ptr = arg32(&a);
    jvalue v[64]; jh_args(sig, 2, &a, ptr, v);
    ret32(c, (uint8_t)((*e)->CallBooleanMethodA(e, alvo, m, v)));
}

void J_CallByteMethod(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jobject alvo = jh_obj(arg32(&a));
    const char *sig; jmethodID m = jh_id(arg32(&a), &sig);
    uint32_t ptr = 0;
    jvalue v[64]; jh_args(sig, 0, &a, ptr, v);
    ret32(c, (uint32_t)(int32_t)((*e)->CallByteMethodA(e, alvo, m, v)));
}

void J_CallByteMethodV(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jobject alvo = jh_obj(arg32(&a));
    const char *sig; jmethodID m = jh_id(arg32(&a), &sig);
    uint32_t ptr = arg32(&a);
    jvalue v[64]; jh_args(sig, 1, &a, ptr, v);
    ret32(c, (uint32_t)(int32_t)((*e)->CallByteMethodA(e, alvo, m, v)));
}

void J_CallByteMethodA(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jobject alvo = jh_obj(arg32(&a));
    const char *sig; jmethodID m = jh_id(arg32(&a), &sig);
    uint32_t ptr = arg32(&a);
    jvalue v[64]; jh_args(sig, 2, &a, ptr, v);
    ret32(c, (uint32_t)(int32_t)((*e)->CallByteMethodA(e, alvo, m, v)));
}

void J_CallCharMethod(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jobject alvo = jh_obj(arg32(&a));
    const char *sig; jmethodID m = jh_id(arg32(&a), &sig);
    uint32_t ptr = 0;
    jvalue v[64]; jh_args(sig, 0, &a, ptr, v);
    ret32(c, (uint16_t)((*e)->CallCharMethodA(e, alvo, m, v)));
}

void J_CallCharMethodV(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jobject alvo = jh_obj(arg32(&a));
    const char *sig; jmethodID m = jh_id(arg32(&a), &sig);
    uint32_t ptr = arg32(&a);
    jvalue v[64]; jh_args(sig, 1, &a, ptr, v);
    ret32(c, (uint16_t)((*e)->CallCharMethodA(e, alvo, m, v)));
}

void J_CallCharMethodA(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jobject alvo = jh_obj(arg32(&a));
    const char *sig; jmethodID m = jh_id(arg32(&a), &sig);
    uint32_t ptr = arg32(&a);
    jvalue v[64]; jh_args(sig, 2, &a, ptr, v);
    ret32(c, (uint16_t)((*e)->CallCharMethodA(e, alvo, m, v)));
}

void J_CallShortMethod(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jobject alvo = jh_obj(arg32(&a));
    const char *sig; jmethodID m = jh_id(arg32(&a), &sig);
    uint32_t ptr = 0;
    jvalue v[64]; jh_args(sig, 0, &a, ptr, v);
    ret32(c, (uint32_t)(int32_t)((*e)->CallShortMethodA(e, alvo, m, v)));
}

void J_CallShortMethodV(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jobject alvo = jh_obj(arg32(&a));
    const char *sig; jmethodID m = jh_id(arg32(&a), &sig);
    uint32_t ptr = arg32(&a);
    jvalue v[64]; jh_args(sig, 1, &a, ptr, v);
    ret32(c, (uint32_t)(int32_t)((*e)->CallShortMethodA(e, alvo, m, v)));
}

void J_CallShortMethodA(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jobject alvo = jh_obj(arg32(&a));
    const char *sig; jmethodID m = jh_id(arg32(&a), &sig);
    uint32_t ptr = arg32(&a);
    jvalue v[64]; jh_args(sig, 2, &a, ptr, v);
    ret32(c, (uint32_t)(int32_t)((*e)->CallShortMethodA(e, alvo, m, v)));
}

void J_CallIntMethod(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jobject alvo = jh_obj(arg32(&a));
    const char *sig; jmethodID m = jh_id(arg32(&a), &sig);
    uint32_t ptr = 0;
    jvalue v[64]; jh_args(sig, 0, &a, ptr, v);
    ret32(c, (uint32_t)((*e)->CallIntMethodA(e, alvo, m, v)));
}

void J_CallIntMethodV(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jobject alvo = jh_obj(arg32(&a));
    const char *sig; jmethodID m = jh_id(arg32(&a), &sig);
    uint32_t ptr = arg32(&a);
    jvalue v[64]; jh_args(sig, 1, &a, ptr, v);
    ret32(c, (uint32_t)((*e)->CallIntMethodA(e, alvo, m, v)));
}

void J_CallIntMethodA(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jobject alvo = jh_obj(arg32(&a));
    const char *sig; jmethodID m = jh_id(arg32(&a), &sig);
    uint32_t ptr = arg32(&a);
    jvalue v[64]; jh_args(sig, 2, &a, ptr, v);
    ret32(c, (uint32_t)((*e)->CallIntMethodA(e, alvo, m, v)));
}

void J_CallLongMethod(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jobject alvo = jh_obj(arg32(&a));
    const char *sig; jmethodID m = jh_id(arg32(&a), &sig);
    uint32_t ptr = 0;
    jvalue v[64]; jh_args(sig, 0, &a, ptr, v);
    ret64(c, (uint64_t)((*e)->CallLongMethodA(e, alvo, m, v)));
}

void J_CallLongMethodV(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jobject alvo = jh_obj(arg32(&a));
    const char *sig; jmethodID m = jh_id(arg32(&a), &sig);
    uint32_t ptr = arg32(&a);
    jvalue v[64]; jh_args(sig, 1, &a, ptr, v);
    ret64(c, (uint64_t)((*e)->CallLongMethodA(e, alvo, m, v)));
}

void J_CallLongMethodA(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jobject alvo = jh_obj(arg32(&a));
    const char *sig; jmethodID m = jh_id(arg32(&a), &sig);
    uint32_t ptr = arg32(&a);
    jvalue v[64]; jh_args(sig, 2, &a, ptr, v);
    ret64(c, (uint64_t)((*e)->CallLongMethodA(e, alvo, m, v)));
}

void J_CallFloatMethod(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jobject alvo = jh_obj(arg32(&a));
    const char *sig; jmethodID m = jh_id(arg32(&a), &sig);
    uint32_t ptr = 0;
    jvalue v[64]; jh_args(sig, 0, &a, ptr, v);
    retf(c, (*e)->CallFloatMethodA(e, alvo, m, v));
}

void J_CallFloatMethodV(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jobject alvo = jh_obj(arg32(&a));
    const char *sig; jmethodID m = jh_id(arg32(&a), &sig);
    uint32_t ptr = arg32(&a);
    jvalue v[64]; jh_args(sig, 1, &a, ptr, v);
    retf(c, (*e)->CallFloatMethodA(e, alvo, m, v));
}

void J_CallFloatMethodA(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jobject alvo = jh_obj(arg32(&a));
    const char *sig; jmethodID m = jh_id(arg32(&a), &sig);
    uint32_t ptr = arg32(&a);
    jvalue v[64]; jh_args(sig, 2, &a, ptr, v);
    retf(c, (*e)->CallFloatMethodA(e, alvo, m, v));
}

void J_CallDoubleMethod(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jobject alvo = jh_obj(arg32(&a));
    const char *sig; jmethodID m = jh_id(arg32(&a), &sig);
    uint32_t ptr = 0;
    jvalue v[64]; jh_args(sig, 0, &a, ptr, v);
    retd(c, (*e)->CallDoubleMethodA(e, alvo, m, v));
}

void J_CallDoubleMethodV(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jobject alvo = jh_obj(arg32(&a));
    const char *sig; jmethodID m = jh_id(arg32(&a), &sig);
    uint32_t ptr = arg32(&a);
    jvalue v[64]; jh_args(sig, 1, &a, ptr, v);
    retd(c, (*e)->CallDoubleMethodA(e, alvo, m, v));
}

void J_CallDoubleMethodA(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jobject alvo = jh_obj(arg32(&a));
    const char *sig; jmethodID m = jh_id(arg32(&a), &sig);
    uint32_t ptr = arg32(&a);
    jvalue v[64]; jh_args(sig, 2, &a, ptr, v);
    retd(c, (*e)->CallDoubleMethodA(e, alvo, m, v));
}

void J_CallVoidMethod(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jobject alvo = jh_obj(arg32(&a));
    const char *sig; jmethodID m = jh_id(arg32(&a), &sig);
    uint32_t ptr = 0;
    jvalue v[64]; jh_args(sig, 0, &a, ptr, v);
    (*e)->CallVoidMethodA(e, alvo, m, v);
}

void J_CallVoidMethodV(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jobject alvo = jh_obj(arg32(&a));
    const char *sig; jmethodID m = jh_id(arg32(&a), &sig);
    uint32_t ptr = arg32(&a);
    jvalue v[64]; jh_args(sig, 1, &a, ptr, v);
    (*e)->CallVoidMethodA(e, alvo, m, v);
}

void J_CallVoidMethodA(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jobject alvo = jh_obj(arg32(&a));
    const char *sig; jmethodID m = jh_id(arg32(&a), &sig);
    uint32_t ptr = arg32(&a);
    jvalue v[64]; jh_args(sig, 2, &a, ptr, v);
    (*e)->CallVoidMethodA(e, alvo, m, v);
}

void J_CallNonvirtualObjectMethod(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jobject alvo = jh_obj(arg32(&a));
    jclass kl = jh_obj(arg32(&a));
    const char *sig; jmethodID m = jh_id(arg32(&a), &sig);
    uint32_t ptr = 0;
    jvalue v[64]; jh_args(sig, 0, &a, ptr, v);
    ret32(c, jh_local((*e)->CallNonvirtualObjectMethodA(e, alvo, kl, m, v)));
}

void J_CallNonvirtualObjectMethodV(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jobject alvo = jh_obj(arg32(&a));
    jclass kl = jh_obj(arg32(&a));
    const char *sig; jmethodID m = jh_id(arg32(&a), &sig);
    uint32_t ptr = arg32(&a);
    jvalue v[64]; jh_args(sig, 1, &a, ptr, v);
    ret32(c, jh_local((*e)->CallNonvirtualObjectMethodA(e, alvo, kl, m, v)));
}

void J_CallNonvirtualObjectMethodA(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jobject alvo = jh_obj(arg32(&a));
    jclass kl = jh_obj(arg32(&a));
    const char *sig; jmethodID m = jh_id(arg32(&a), &sig);
    uint32_t ptr = arg32(&a);
    jvalue v[64]; jh_args(sig, 2, &a, ptr, v);
    ret32(c, jh_local((*e)->CallNonvirtualObjectMethodA(e, alvo, kl, m, v)));
}

void J_CallNonvirtualBooleanMethod(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jobject alvo = jh_obj(arg32(&a));
    jclass kl = jh_obj(arg32(&a));
    const char *sig; jmethodID m = jh_id(arg32(&a), &sig);
    uint32_t ptr = 0;
    jvalue v[64]; jh_args(sig, 0, &a, ptr, v);
    ret32(c, (uint8_t)((*e)->CallNonvirtualBooleanMethodA(e, alvo, kl, m, v)));
}

void J_CallNonvirtualBooleanMethodV(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jobject alvo = jh_obj(arg32(&a));
    jclass kl = jh_obj(arg32(&a));
    const char *sig; jmethodID m = jh_id(arg32(&a), &sig);
    uint32_t ptr = arg32(&a);
    jvalue v[64]; jh_args(sig, 1, &a, ptr, v);
    ret32(c, (uint8_t)((*e)->CallNonvirtualBooleanMethodA(e, alvo, kl, m, v)));
}

void J_CallNonvirtualBooleanMethodA(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jobject alvo = jh_obj(arg32(&a));
    jclass kl = jh_obj(arg32(&a));
    const char *sig; jmethodID m = jh_id(arg32(&a), &sig);
    uint32_t ptr = arg32(&a);
    jvalue v[64]; jh_args(sig, 2, &a, ptr, v);
    ret32(c, (uint8_t)((*e)->CallNonvirtualBooleanMethodA(e, alvo, kl, m, v)));
}

void J_CallNonvirtualByteMethod(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jobject alvo = jh_obj(arg32(&a));
    jclass kl = jh_obj(arg32(&a));
    const char *sig; jmethodID m = jh_id(arg32(&a), &sig);
    uint32_t ptr = 0;
    jvalue v[64]; jh_args(sig, 0, &a, ptr, v);
    ret32(c, (uint32_t)(int32_t)((*e)->CallNonvirtualByteMethodA(e, alvo, kl, m, v)));
}

void J_CallNonvirtualByteMethodV(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jobject alvo = jh_obj(arg32(&a));
    jclass kl = jh_obj(arg32(&a));
    const char *sig; jmethodID m = jh_id(arg32(&a), &sig);
    uint32_t ptr = arg32(&a);
    jvalue v[64]; jh_args(sig, 1, &a, ptr, v);
    ret32(c, (uint32_t)(int32_t)((*e)->CallNonvirtualByteMethodA(e, alvo, kl, m, v)));
}

void J_CallNonvirtualByteMethodA(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jobject alvo = jh_obj(arg32(&a));
    jclass kl = jh_obj(arg32(&a));
    const char *sig; jmethodID m = jh_id(arg32(&a), &sig);
    uint32_t ptr = arg32(&a);
    jvalue v[64]; jh_args(sig, 2, &a, ptr, v);
    ret32(c, (uint32_t)(int32_t)((*e)->CallNonvirtualByteMethodA(e, alvo, kl, m, v)));
}

void J_CallNonvirtualCharMethod(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jobject alvo = jh_obj(arg32(&a));
    jclass kl = jh_obj(arg32(&a));
    const char *sig; jmethodID m = jh_id(arg32(&a), &sig);
    uint32_t ptr = 0;
    jvalue v[64]; jh_args(sig, 0, &a, ptr, v);
    ret32(c, (uint16_t)((*e)->CallNonvirtualCharMethodA(e, alvo, kl, m, v)));
}

void J_CallNonvirtualCharMethodV(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jobject alvo = jh_obj(arg32(&a));
    jclass kl = jh_obj(arg32(&a));
    const char *sig; jmethodID m = jh_id(arg32(&a), &sig);
    uint32_t ptr = arg32(&a);
    jvalue v[64]; jh_args(sig, 1, &a, ptr, v);
    ret32(c, (uint16_t)((*e)->CallNonvirtualCharMethodA(e, alvo, kl, m, v)));
}

void J_CallNonvirtualCharMethodA(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jobject alvo = jh_obj(arg32(&a));
    jclass kl = jh_obj(arg32(&a));
    const char *sig; jmethodID m = jh_id(arg32(&a), &sig);
    uint32_t ptr = arg32(&a);
    jvalue v[64]; jh_args(sig, 2, &a, ptr, v);
    ret32(c, (uint16_t)((*e)->CallNonvirtualCharMethodA(e, alvo, kl, m, v)));
}

void J_CallNonvirtualShortMethod(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jobject alvo = jh_obj(arg32(&a));
    jclass kl = jh_obj(arg32(&a));
    const char *sig; jmethodID m = jh_id(arg32(&a), &sig);
    uint32_t ptr = 0;
    jvalue v[64]; jh_args(sig, 0, &a, ptr, v);
    ret32(c, (uint32_t)(int32_t)((*e)->CallNonvirtualShortMethodA(e, alvo, kl, m, v)));
}

void J_CallNonvirtualShortMethodV(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jobject alvo = jh_obj(arg32(&a));
    jclass kl = jh_obj(arg32(&a));
    const char *sig; jmethodID m = jh_id(arg32(&a), &sig);
    uint32_t ptr = arg32(&a);
    jvalue v[64]; jh_args(sig, 1, &a, ptr, v);
    ret32(c, (uint32_t)(int32_t)((*e)->CallNonvirtualShortMethodA(e, alvo, kl, m, v)));
}

void J_CallNonvirtualShortMethodA(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jobject alvo = jh_obj(arg32(&a));
    jclass kl = jh_obj(arg32(&a));
    const char *sig; jmethodID m = jh_id(arg32(&a), &sig);
    uint32_t ptr = arg32(&a);
    jvalue v[64]; jh_args(sig, 2, &a, ptr, v);
    ret32(c, (uint32_t)(int32_t)((*e)->CallNonvirtualShortMethodA(e, alvo, kl, m, v)));
}

void J_CallNonvirtualIntMethod(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jobject alvo = jh_obj(arg32(&a));
    jclass kl = jh_obj(arg32(&a));
    const char *sig; jmethodID m = jh_id(arg32(&a), &sig);
    uint32_t ptr = 0;
    jvalue v[64]; jh_args(sig, 0, &a, ptr, v);
    ret32(c, (uint32_t)((*e)->CallNonvirtualIntMethodA(e, alvo, kl, m, v)));
}

void J_CallNonvirtualIntMethodV(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jobject alvo = jh_obj(arg32(&a));
    jclass kl = jh_obj(arg32(&a));
    const char *sig; jmethodID m = jh_id(arg32(&a), &sig);
    uint32_t ptr = arg32(&a);
    jvalue v[64]; jh_args(sig, 1, &a, ptr, v);
    ret32(c, (uint32_t)((*e)->CallNonvirtualIntMethodA(e, alvo, kl, m, v)));
}

void J_CallNonvirtualIntMethodA(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jobject alvo = jh_obj(arg32(&a));
    jclass kl = jh_obj(arg32(&a));
    const char *sig; jmethodID m = jh_id(arg32(&a), &sig);
    uint32_t ptr = arg32(&a);
    jvalue v[64]; jh_args(sig, 2, &a, ptr, v);
    ret32(c, (uint32_t)((*e)->CallNonvirtualIntMethodA(e, alvo, kl, m, v)));
}

void J_CallNonvirtualLongMethod(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jobject alvo = jh_obj(arg32(&a));
    jclass kl = jh_obj(arg32(&a));
    const char *sig; jmethodID m = jh_id(arg32(&a), &sig);
    uint32_t ptr = 0;
    jvalue v[64]; jh_args(sig, 0, &a, ptr, v);
    ret64(c, (uint64_t)((*e)->CallNonvirtualLongMethodA(e, alvo, kl, m, v)));
}

void J_CallNonvirtualLongMethodV(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jobject alvo = jh_obj(arg32(&a));
    jclass kl = jh_obj(arg32(&a));
    const char *sig; jmethodID m = jh_id(arg32(&a), &sig);
    uint32_t ptr = arg32(&a);
    jvalue v[64]; jh_args(sig, 1, &a, ptr, v);
    ret64(c, (uint64_t)((*e)->CallNonvirtualLongMethodA(e, alvo, kl, m, v)));
}

void J_CallNonvirtualLongMethodA(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jobject alvo = jh_obj(arg32(&a));
    jclass kl = jh_obj(arg32(&a));
    const char *sig; jmethodID m = jh_id(arg32(&a), &sig);
    uint32_t ptr = arg32(&a);
    jvalue v[64]; jh_args(sig, 2, &a, ptr, v);
    ret64(c, (uint64_t)((*e)->CallNonvirtualLongMethodA(e, alvo, kl, m, v)));
}

void J_CallNonvirtualFloatMethod(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jobject alvo = jh_obj(arg32(&a));
    jclass kl = jh_obj(arg32(&a));
    const char *sig; jmethodID m = jh_id(arg32(&a), &sig);
    uint32_t ptr = 0;
    jvalue v[64]; jh_args(sig, 0, &a, ptr, v);
    retf(c, (*e)->CallNonvirtualFloatMethodA(e, alvo, kl, m, v));
}

void J_CallNonvirtualFloatMethodV(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jobject alvo = jh_obj(arg32(&a));
    jclass kl = jh_obj(arg32(&a));
    const char *sig; jmethodID m = jh_id(arg32(&a), &sig);
    uint32_t ptr = arg32(&a);
    jvalue v[64]; jh_args(sig, 1, &a, ptr, v);
    retf(c, (*e)->CallNonvirtualFloatMethodA(e, alvo, kl, m, v));
}

void J_CallNonvirtualFloatMethodA(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jobject alvo = jh_obj(arg32(&a));
    jclass kl = jh_obj(arg32(&a));
    const char *sig; jmethodID m = jh_id(arg32(&a), &sig);
    uint32_t ptr = arg32(&a);
    jvalue v[64]; jh_args(sig, 2, &a, ptr, v);
    retf(c, (*e)->CallNonvirtualFloatMethodA(e, alvo, kl, m, v));
}

void J_CallNonvirtualDoubleMethod(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jobject alvo = jh_obj(arg32(&a));
    jclass kl = jh_obj(arg32(&a));
    const char *sig; jmethodID m = jh_id(arg32(&a), &sig);
    uint32_t ptr = 0;
    jvalue v[64]; jh_args(sig, 0, &a, ptr, v);
    retd(c, (*e)->CallNonvirtualDoubleMethodA(e, alvo, kl, m, v));
}

void J_CallNonvirtualDoubleMethodV(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jobject alvo = jh_obj(arg32(&a));
    jclass kl = jh_obj(arg32(&a));
    const char *sig; jmethodID m = jh_id(arg32(&a), &sig);
    uint32_t ptr = arg32(&a);
    jvalue v[64]; jh_args(sig, 1, &a, ptr, v);
    retd(c, (*e)->CallNonvirtualDoubleMethodA(e, alvo, kl, m, v));
}

void J_CallNonvirtualDoubleMethodA(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jobject alvo = jh_obj(arg32(&a));
    jclass kl = jh_obj(arg32(&a));
    const char *sig; jmethodID m = jh_id(arg32(&a), &sig);
    uint32_t ptr = arg32(&a);
    jvalue v[64]; jh_args(sig, 2, &a, ptr, v);
    retd(c, (*e)->CallNonvirtualDoubleMethodA(e, alvo, kl, m, v));
}

void J_CallNonvirtualVoidMethod(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jobject alvo = jh_obj(arg32(&a));
    jclass kl = jh_obj(arg32(&a));
    const char *sig; jmethodID m = jh_id(arg32(&a), &sig);
    uint32_t ptr = 0;
    jvalue v[64]; jh_args(sig, 0, &a, ptr, v);
    (*e)->CallNonvirtualVoidMethodA(e, alvo, kl, m, v);
}

void J_CallNonvirtualVoidMethodV(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jobject alvo = jh_obj(arg32(&a));
    jclass kl = jh_obj(arg32(&a));
    const char *sig; jmethodID m = jh_id(arg32(&a), &sig);
    uint32_t ptr = arg32(&a);
    jvalue v[64]; jh_args(sig, 1, &a, ptr, v);
    (*e)->CallNonvirtualVoidMethodA(e, alvo, kl, m, v);
}

void J_CallNonvirtualVoidMethodA(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jobject alvo = jh_obj(arg32(&a));
    jclass kl = jh_obj(arg32(&a));
    const char *sig; jmethodID m = jh_id(arg32(&a), &sig);
    uint32_t ptr = arg32(&a);
    jvalue v[64]; jh_args(sig, 2, &a, ptr, v);
    (*e)->CallNonvirtualVoidMethodA(e, alvo, kl, m, v);
}

void J_GetObjectField(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jobject alvo = jh_obj(arg32(&a));
    jfieldID f = jh_id(arg32(&a), NULL);
    ret32(c, jh_local((*e)->GetObjectField(e, alvo, f)));
}

void J_GetBooleanField(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jobject alvo = jh_obj(arg32(&a));
    jfieldID f = jh_id(arg32(&a), NULL);
    ret32(c, (uint8_t)((*e)->GetBooleanField(e, alvo, f)));
}

void J_GetByteField(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jobject alvo = jh_obj(arg32(&a));
    jfieldID f = jh_id(arg32(&a), NULL);
    ret32(c, (uint32_t)(int32_t)((*e)->GetByteField(e, alvo, f)));
}

void J_GetCharField(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jobject alvo = jh_obj(arg32(&a));
    jfieldID f = jh_id(arg32(&a), NULL);
    ret32(c, (uint16_t)((*e)->GetCharField(e, alvo, f)));
}

void J_GetShortField(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jobject alvo = jh_obj(arg32(&a));
    jfieldID f = jh_id(arg32(&a), NULL);
    ret32(c, (uint32_t)(int32_t)((*e)->GetShortField(e, alvo, f)));
}

void J_GetIntField(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jobject alvo = jh_obj(arg32(&a));
    jfieldID f = jh_id(arg32(&a), NULL);
    ret32(c, (uint32_t)((*e)->GetIntField(e, alvo, f)));
}

void J_GetLongField(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jobject alvo = jh_obj(arg32(&a));
    jfieldID f = jh_id(arg32(&a), NULL);
    ret64(c, (uint64_t)((*e)->GetLongField(e, alvo, f)));
}

void J_GetFloatField(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jobject alvo = jh_obj(arg32(&a));
    jfieldID f = jh_id(arg32(&a), NULL);
    retf(c, (*e)->GetFloatField(e, alvo, f));
}

void J_GetDoubleField(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jobject alvo = jh_obj(arg32(&a));
    jfieldID f = jh_id(arg32(&a), NULL);
    retd(c, (*e)->GetDoubleField(e, alvo, f));
}

void J_SetObjectField(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jobject alvo = jh_obj(arg32(&a));
    jfieldID f = jh_id(arg32(&a), NULL);
    (*e)->SetObjectField(e, alvo, f, jh_obj(arg32(&a)));
}

void J_SetBooleanField(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jobject alvo = jh_obj(arg32(&a));
    jfieldID f = jh_id(arg32(&a), NULL);
    (*e)->SetBooleanField(e, alvo, f, (jboolean)arg32(&a));
}

void J_SetByteField(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jobject alvo = jh_obj(arg32(&a));
    jfieldID f = jh_id(arg32(&a), NULL);
    (*e)->SetByteField(e, alvo, f, (jbyte)arg32(&a));
}

void J_SetCharField(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jobject alvo = jh_obj(arg32(&a));
    jfieldID f = jh_id(arg32(&a), NULL);
    (*e)->SetCharField(e, alvo, f, (jchar)arg32(&a));
}

void J_SetShortField(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jobject alvo = jh_obj(arg32(&a));
    jfieldID f = jh_id(arg32(&a), NULL);
    (*e)->SetShortField(e, alvo, f, (jshort)arg32(&a));
}

void J_SetIntField(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jobject alvo = jh_obj(arg32(&a));
    jfieldID f = jh_id(arg32(&a), NULL);
    (*e)->SetIntField(e, alvo, f, (jint)arg32(&a));
}

void J_SetLongField(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jobject alvo = jh_obj(arg32(&a));
    jfieldID f = jh_id(arg32(&a), NULL);
    (*e)->SetLongField(e, alvo, f, (jlong)arg64(&a));
}

void J_SetFloatField(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jobject alvo = jh_obj(arg32(&a));
    jfieldID f = jh_id(arg32(&a), NULL);
    (*e)->SetFloatField(e, alvo, f, argf(&a));
}

void J_SetDoubleField(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jobject alvo = jh_obj(arg32(&a));
    jfieldID f = jh_id(arg32(&a), NULL);
    (*e)->SetDoubleField(e, alvo, f, argd(&a));
}

void J_CallStaticObjectMethod(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jclass alvo = jh_obj(arg32(&a));
    const char *sig; jmethodID m = jh_id(arg32(&a), &sig);
    uint32_t ptr = 0;
    jvalue v[64]; jh_args(sig, 0, &a, ptr, v);
    ret32(c, jh_local((*e)->CallStaticObjectMethodA(e, alvo, m, v)));
}

void J_CallStaticObjectMethodV(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jclass alvo = jh_obj(arg32(&a));
    const char *sig; jmethodID m = jh_id(arg32(&a), &sig);
    uint32_t ptr = arg32(&a);
    jvalue v[64]; jh_args(sig, 1, &a, ptr, v);
    ret32(c, jh_local((*e)->CallStaticObjectMethodA(e, alvo, m, v)));
}

void J_CallStaticObjectMethodA(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jclass alvo = jh_obj(arg32(&a));
    const char *sig; jmethodID m = jh_id(arg32(&a), &sig);
    uint32_t ptr = arg32(&a);
    jvalue v[64]; jh_args(sig, 2, &a, ptr, v);
    ret32(c, jh_local((*e)->CallStaticObjectMethodA(e, alvo, m, v)));
}

void J_CallStaticBooleanMethod(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jclass alvo = jh_obj(arg32(&a));
    const char *sig; jmethodID m = jh_id(arg32(&a), &sig);
    uint32_t ptr = 0;
    jvalue v[64]; jh_args(sig, 0, &a, ptr, v);
    ret32(c, (uint8_t)((*e)->CallStaticBooleanMethodA(e, alvo, m, v)));
}

void J_CallStaticBooleanMethodV(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jclass alvo = jh_obj(arg32(&a));
    const char *sig; jmethodID m = jh_id(arg32(&a), &sig);
    uint32_t ptr = arg32(&a);
    jvalue v[64]; jh_args(sig, 1, &a, ptr, v);
    ret32(c, (uint8_t)((*e)->CallStaticBooleanMethodA(e, alvo, m, v)));
}

void J_CallStaticBooleanMethodA(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jclass alvo = jh_obj(arg32(&a));
    const char *sig; jmethodID m = jh_id(arg32(&a), &sig);
    uint32_t ptr = arg32(&a);
    jvalue v[64]; jh_args(sig, 2, &a, ptr, v);
    ret32(c, (uint8_t)((*e)->CallStaticBooleanMethodA(e, alvo, m, v)));
}

void J_CallStaticByteMethod(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jclass alvo = jh_obj(arg32(&a));
    const char *sig; jmethodID m = jh_id(arg32(&a), &sig);
    uint32_t ptr = 0;
    jvalue v[64]; jh_args(sig, 0, &a, ptr, v);
    ret32(c, (uint32_t)(int32_t)((*e)->CallStaticByteMethodA(e, alvo, m, v)));
}

void J_CallStaticByteMethodV(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jclass alvo = jh_obj(arg32(&a));
    const char *sig; jmethodID m = jh_id(arg32(&a), &sig);
    uint32_t ptr = arg32(&a);
    jvalue v[64]; jh_args(sig, 1, &a, ptr, v);
    ret32(c, (uint32_t)(int32_t)((*e)->CallStaticByteMethodA(e, alvo, m, v)));
}

void J_CallStaticByteMethodA(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jclass alvo = jh_obj(arg32(&a));
    const char *sig; jmethodID m = jh_id(arg32(&a), &sig);
    uint32_t ptr = arg32(&a);
    jvalue v[64]; jh_args(sig, 2, &a, ptr, v);
    ret32(c, (uint32_t)(int32_t)((*e)->CallStaticByteMethodA(e, alvo, m, v)));
}

void J_CallStaticCharMethod(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jclass alvo = jh_obj(arg32(&a));
    const char *sig; jmethodID m = jh_id(arg32(&a), &sig);
    uint32_t ptr = 0;
    jvalue v[64]; jh_args(sig, 0, &a, ptr, v);
    ret32(c, (uint16_t)((*e)->CallStaticCharMethodA(e, alvo, m, v)));
}

void J_CallStaticCharMethodV(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jclass alvo = jh_obj(arg32(&a));
    const char *sig; jmethodID m = jh_id(arg32(&a), &sig);
    uint32_t ptr = arg32(&a);
    jvalue v[64]; jh_args(sig, 1, &a, ptr, v);
    ret32(c, (uint16_t)((*e)->CallStaticCharMethodA(e, alvo, m, v)));
}

void J_CallStaticCharMethodA(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jclass alvo = jh_obj(arg32(&a));
    const char *sig; jmethodID m = jh_id(arg32(&a), &sig);
    uint32_t ptr = arg32(&a);
    jvalue v[64]; jh_args(sig, 2, &a, ptr, v);
    ret32(c, (uint16_t)((*e)->CallStaticCharMethodA(e, alvo, m, v)));
}

void J_CallStaticShortMethod(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jclass alvo = jh_obj(arg32(&a));
    const char *sig; jmethodID m = jh_id(arg32(&a), &sig);
    uint32_t ptr = 0;
    jvalue v[64]; jh_args(sig, 0, &a, ptr, v);
    ret32(c, (uint32_t)(int32_t)((*e)->CallStaticShortMethodA(e, alvo, m, v)));
}

void J_CallStaticShortMethodV(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jclass alvo = jh_obj(arg32(&a));
    const char *sig; jmethodID m = jh_id(arg32(&a), &sig);
    uint32_t ptr = arg32(&a);
    jvalue v[64]; jh_args(sig, 1, &a, ptr, v);
    ret32(c, (uint32_t)(int32_t)((*e)->CallStaticShortMethodA(e, alvo, m, v)));
}

void J_CallStaticShortMethodA(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jclass alvo = jh_obj(arg32(&a));
    const char *sig; jmethodID m = jh_id(arg32(&a), &sig);
    uint32_t ptr = arg32(&a);
    jvalue v[64]; jh_args(sig, 2, &a, ptr, v);
    ret32(c, (uint32_t)(int32_t)((*e)->CallStaticShortMethodA(e, alvo, m, v)));
}

void J_CallStaticIntMethod(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jclass alvo = jh_obj(arg32(&a));
    const char *sig; jmethodID m = jh_id(arg32(&a), &sig);
    uint32_t ptr = 0;
    jvalue v[64]; jh_args(sig, 0, &a, ptr, v);
    ret32(c, (uint32_t)((*e)->CallStaticIntMethodA(e, alvo, m, v)));
}

void J_CallStaticIntMethodV(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jclass alvo = jh_obj(arg32(&a));
    const char *sig; jmethodID m = jh_id(arg32(&a), &sig);
    uint32_t ptr = arg32(&a);
    jvalue v[64]; jh_args(sig, 1, &a, ptr, v);
    ret32(c, (uint32_t)((*e)->CallStaticIntMethodA(e, alvo, m, v)));
}

void J_CallStaticIntMethodA(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jclass alvo = jh_obj(arg32(&a));
    const char *sig; jmethodID m = jh_id(arg32(&a), &sig);
    uint32_t ptr = arg32(&a);
    jvalue v[64]; jh_args(sig, 2, &a, ptr, v);
    ret32(c, (uint32_t)((*e)->CallStaticIntMethodA(e, alvo, m, v)));
}

void J_CallStaticLongMethod(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jclass alvo = jh_obj(arg32(&a));
    const char *sig; jmethodID m = jh_id(arg32(&a), &sig);
    uint32_t ptr = 0;
    jvalue v[64]; jh_args(sig, 0, &a, ptr, v);
    ret64(c, (uint64_t)((*e)->CallStaticLongMethodA(e, alvo, m, v)));
}

void J_CallStaticLongMethodV(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jclass alvo = jh_obj(arg32(&a));
    const char *sig; jmethodID m = jh_id(arg32(&a), &sig);
    uint32_t ptr = arg32(&a);
    jvalue v[64]; jh_args(sig, 1, &a, ptr, v);
    ret64(c, (uint64_t)((*e)->CallStaticLongMethodA(e, alvo, m, v)));
}

void J_CallStaticLongMethodA(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jclass alvo = jh_obj(arg32(&a));
    const char *sig; jmethodID m = jh_id(arg32(&a), &sig);
    uint32_t ptr = arg32(&a);
    jvalue v[64]; jh_args(sig, 2, &a, ptr, v);
    ret64(c, (uint64_t)((*e)->CallStaticLongMethodA(e, alvo, m, v)));
}

void J_CallStaticFloatMethod(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jclass alvo = jh_obj(arg32(&a));
    const char *sig; jmethodID m = jh_id(arg32(&a), &sig);
    uint32_t ptr = 0;
    jvalue v[64]; jh_args(sig, 0, &a, ptr, v);
    retf(c, (*e)->CallStaticFloatMethodA(e, alvo, m, v));
}

void J_CallStaticFloatMethodV(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jclass alvo = jh_obj(arg32(&a));
    const char *sig; jmethodID m = jh_id(arg32(&a), &sig);
    uint32_t ptr = arg32(&a);
    jvalue v[64]; jh_args(sig, 1, &a, ptr, v);
    retf(c, (*e)->CallStaticFloatMethodA(e, alvo, m, v));
}

void J_CallStaticFloatMethodA(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jclass alvo = jh_obj(arg32(&a));
    const char *sig; jmethodID m = jh_id(arg32(&a), &sig);
    uint32_t ptr = arg32(&a);
    jvalue v[64]; jh_args(sig, 2, &a, ptr, v);
    retf(c, (*e)->CallStaticFloatMethodA(e, alvo, m, v));
}

void J_CallStaticDoubleMethod(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jclass alvo = jh_obj(arg32(&a));
    const char *sig; jmethodID m = jh_id(arg32(&a), &sig);
    uint32_t ptr = 0;
    jvalue v[64]; jh_args(sig, 0, &a, ptr, v);
    retd(c, (*e)->CallStaticDoubleMethodA(e, alvo, m, v));
}

void J_CallStaticDoubleMethodV(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jclass alvo = jh_obj(arg32(&a));
    const char *sig; jmethodID m = jh_id(arg32(&a), &sig);
    uint32_t ptr = arg32(&a);
    jvalue v[64]; jh_args(sig, 1, &a, ptr, v);
    retd(c, (*e)->CallStaticDoubleMethodA(e, alvo, m, v));
}

void J_CallStaticDoubleMethodA(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jclass alvo = jh_obj(arg32(&a));
    const char *sig; jmethodID m = jh_id(arg32(&a), &sig);
    uint32_t ptr = arg32(&a);
    jvalue v[64]; jh_args(sig, 2, &a, ptr, v);
    retd(c, (*e)->CallStaticDoubleMethodA(e, alvo, m, v));
}

void J_CallStaticVoidMethod(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jclass alvo = jh_obj(arg32(&a));
    const char *sig; jmethodID m = jh_id(arg32(&a), &sig);
    uint32_t ptr = 0;
    jvalue v[64]; jh_args(sig, 0, &a, ptr, v);
    (*e)->CallStaticVoidMethodA(e, alvo, m, v);
}

void J_CallStaticVoidMethodV(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jclass alvo = jh_obj(arg32(&a));
    const char *sig; jmethodID m = jh_id(arg32(&a), &sig);
    uint32_t ptr = arg32(&a);
    jvalue v[64]; jh_args(sig, 1, &a, ptr, v);
    (*e)->CallStaticVoidMethodA(e, alvo, m, v);
}

void J_CallStaticVoidMethodA(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jclass alvo = jh_obj(arg32(&a));
    const char *sig; jmethodID m = jh_id(arg32(&a), &sig);
    uint32_t ptr = arg32(&a);
    jvalue v[64]; jh_args(sig, 2, &a, ptr, v);
    (*e)->CallStaticVoidMethodA(e, alvo, m, v);
}

void J_GetStaticObjectField(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jclass alvo = jh_obj(arg32(&a));
    jfieldID f = jh_id(arg32(&a), NULL);
    ret32(c, jh_local((*e)->GetStaticObjectField(e, alvo, f)));
}

void J_GetStaticBooleanField(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jclass alvo = jh_obj(arg32(&a));
    jfieldID f = jh_id(arg32(&a), NULL);
    ret32(c, (uint8_t)((*e)->GetStaticBooleanField(e, alvo, f)));
}

void J_GetStaticByteField(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jclass alvo = jh_obj(arg32(&a));
    jfieldID f = jh_id(arg32(&a), NULL);
    ret32(c, (uint32_t)(int32_t)((*e)->GetStaticByteField(e, alvo, f)));
}

void J_GetStaticCharField(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jclass alvo = jh_obj(arg32(&a));
    jfieldID f = jh_id(arg32(&a), NULL);
    ret32(c, (uint16_t)((*e)->GetStaticCharField(e, alvo, f)));
}

void J_GetStaticShortField(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jclass alvo = jh_obj(arg32(&a));
    jfieldID f = jh_id(arg32(&a), NULL);
    ret32(c, (uint32_t)(int32_t)((*e)->GetStaticShortField(e, alvo, f)));
}

void J_GetStaticIntField(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jclass alvo = jh_obj(arg32(&a));
    jfieldID f = jh_id(arg32(&a), NULL);
    ret32(c, (uint32_t)((*e)->GetStaticIntField(e, alvo, f)));
}

void J_GetStaticLongField(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jclass alvo = jh_obj(arg32(&a));
    jfieldID f = jh_id(arg32(&a), NULL);
    ret64(c, (uint64_t)((*e)->GetStaticLongField(e, alvo, f)));
}

void J_GetStaticFloatField(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jclass alvo = jh_obj(arg32(&a));
    jfieldID f = jh_id(arg32(&a), NULL);
    retf(c, (*e)->GetStaticFloatField(e, alvo, f));
}

void J_GetStaticDoubleField(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jclass alvo = jh_obj(arg32(&a));
    jfieldID f = jh_id(arg32(&a), NULL);
    retd(c, (*e)->GetStaticDoubleField(e, alvo, f));
}

void J_SetStaticObjectField(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jclass alvo = jh_obj(arg32(&a));
    jfieldID f = jh_id(arg32(&a), NULL);
    (*e)->SetStaticObjectField(e, alvo, f, jh_obj(arg32(&a)));
}

void J_SetStaticBooleanField(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jclass alvo = jh_obj(arg32(&a));
    jfieldID f = jh_id(arg32(&a), NULL);
    (*e)->SetStaticBooleanField(e, alvo, f, (jboolean)arg32(&a));
}

void J_SetStaticByteField(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jclass alvo = jh_obj(arg32(&a));
    jfieldID f = jh_id(arg32(&a), NULL);
    (*e)->SetStaticByteField(e, alvo, f, (jbyte)arg32(&a));
}

void J_SetStaticCharField(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jclass alvo = jh_obj(arg32(&a));
    jfieldID f = jh_id(arg32(&a), NULL);
    (*e)->SetStaticCharField(e, alvo, f, (jchar)arg32(&a));
}

void J_SetStaticShortField(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jclass alvo = jh_obj(arg32(&a));
    jfieldID f = jh_id(arg32(&a), NULL);
    (*e)->SetStaticShortField(e, alvo, f, (jshort)arg32(&a));
}

void J_SetStaticIntField(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jclass alvo = jh_obj(arg32(&a));
    jfieldID f = jh_id(arg32(&a), NULL);
    (*e)->SetStaticIntField(e, alvo, f, (jint)arg32(&a));
}

void J_SetStaticLongField(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jclass alvo = jh_obj(arg32(&a));
    jfieldID f = jh_id(arg32(&a), NULL);
    (*e)->SetStaticLongField(e, alvo, f, (jlong)arg64(&a));
}

void J_SetStaticFloatField(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jclass alvo = jh_obj(arg32(&a));
    jfieldID f = jh_id(arg32(&a), NULL);
    (*e)->SetStaticFloatField(e, alvo, f, argf(&a));
}

void J_SetStaticDoubleField(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    jclass alvo = jh_obj(arg32(&a));
    jfieldID f = jh_id(arg32(&a), NULL);
    (*e)->SetStaticDoubleField(e, alvo, f, argd(&a));
}

void J_NewBooleanArray(CPU *c) {
    JNIEnv *e = jh_env(); ret32(c, jh_local((*e)->NewBooleanArray(e, (jsize)c->r[1])));
}

void J_NewByteArray(CPU *c) {
    JNIEnv *e = jh_env(); ret32(c, jh_local((*e)->NewByteArray(e, (jsize)c->r[1])));
}

void J_NewCharArray(CPU *c) {
    JNIEnv *e = jh_env(); ret32(c, jh_local((*e)->NewCharArray(e, (jsize)c->r[1])));
}

void J_NewShortArray(CPU *c) {
    JNIEnv *e = jh_env(); ret32(c, jh_local((*e)->NewShortArray(e, (jsize)c->r[1])));
}

void J_NewIntArray(CPU *c) {
    JNIEnv *e = jh_env(); ret32(c, jh_local((*e)->NewIntArray(e, (jsize)c->r[1])));
}

void J_NewLongArray(CPU *c) {
    JNIEnv *e = jh_env(); ret32(c, jh_local((*e)->NewLongArray(e, (jsize)c->r[1])));
}

void J_NewFloatArray(CPU *c) {
    JNIEnv *e = jh_env(); ret32(c, jh_local((*e)->NewFloatArray(e, (jsize)c->r[1])));
}

void J_NewDoubleArray(CPU *c) {
    JNIEnv *e = jh_env(); ret32(c, jh_local((*e)->NewDoubleArray(e, (jsize)c->r[1])));
}

void J_GetBooleanArrayElements(CPU *c) {
    JNIEnv *e = jh_env(); jarray arr = jh_obj(c->r[1]);
    jsize n = (*e)->GetArrayLength(e, arr);
    uint32_t g = heap_malloc((uint32_t)n * sizeof(jboolean) + 8);
    (*e)->GetBooleanArrayRegion(e, arr, 0, n, (jboolean *)G2H(g));
    if (c->r[2]) g_mem[c->r[2]] = 1;
    ret32(c, g);
}

void J_GetByteArrayElements(CPU *c) {
    JNIEnv *e = jh_env(); jarray arr = jh_obj(c->r[1]);
    jsize n = (*e)->GetArrayLength(e, arr);
    uint32_t g = heap_malloc((uint32_t)n * sizeof(jbyte) + 8);
    (*e)->GetByteArrayRegion(e, arr, 0, n, (jbyte *)G2H(g));
    if (c->r[2]) g_mem[c->r[2]] = 1;
    ret32(c, g);
}

void J_GetCharArrayElements(CPU *c) {
    JNIEnv *e = jh_env(); jarray arr = jh_obj(c->r[1]);
    jsize n = (*e)->GetArrayLength(e, arr);
    uint32_t g = heap_malloc((uint32_t)n * sizeof(jchar) + 8);
    (*e)->GetCharArrayRegion(e, arr, 0, n, (jchar *)G2H(g));
    if (c->r[2]) g_mem[c->r[2]] = 1;
    ret32(c, g);
}

void J_GetShortArrayElements(CPU *c) {
    JNIEnv *e = jh_env(); jarray arr = jh_obj(c->r[1]);
    jsize n = (*e)->GetArrayLength(e, arr);
    uint32_t g = heap_malloc((uint32_t)n * sizeof(jshort) + 8);
    (*e)->GetShortArrayRegion(e, arr, 0, n, (jshort *)G2H(g));
    if (c->r[2]) g_mem[c->r[2]] = 1;
    ret32(c, g);
}

void J_GetIntArrayElements(CPU *c) {
    JNIEnv *e = jh_env(); jarray arr = jh_obj(c->r[1]);
    jsize n = (*e)->GetArrayLength(e, arr);
    uint32_t g = heap_malloc((uint32_t)n * sizeof(jint) + 8);
    (*e)->GetIntArrayRegion(e, arr, 0, n, (jint *)G2H(g));
    if (c->r[2]) g_mem[c->r[2]] = 1;
    ret32(c, g);
}

void J_GetLongArrayElements(CPU *c) {
    JNIEnv *e = jh_env(); jarray arr = jh_obj(c->r[1]);
    jsize n = (*e)->GetArrayLength(e, arr);
    uint32_t g = heap_malloc((uint32_t)n * sizeof(jlong) + 8);
    (*e)->GetLongArrayRegion(e, arr, 0, n, (jlong *)G2H(g));
    if (c->r[2]) g_mem[c->r[2]] = 1;
    ret32(c, g);
}

void J_GetFloatArrayElements(CPU *c) {
    JNIEnv *e = jh_env(); jarray arr = jh_obj(c->r[1]);
    jsize n = (*e)->GetArrayLength(e, arr);
    uint32_t g = heap_malloc((uint32_t)n * sizeof(jfloat) + 8);
    (*e)->GetFloatArrayRegion(e, arr, 0, n, (jfloat *)G2H(g));
    if (c->r[2]) g_mem[c->r[2]] = 1;
    ret32(c, g);
}

void J_GetDoubleArrayElements(CPU *c) {
    JNIEnv *e = jh_env(); jarray arr = jh_obj(c->r[1]);
    jsize n = (*e)->GetArrayLength(e, arr);
    uint32_t g = heap_malloc((uint32_t)n * sizeof(jdouble) + 8);
    (*e)->GetDoubleArrayRegion(e, arr, 0, n, (jdouble *)G2H(g));
    if (c->r[2]) g_mem[c->r[2]] = 1;
    ret32(c, g);
}

void J_ReleaseBooleanArrayElements(CPU *c) {
    JNIEnv *e = jh_env(); jarray arr = jh_obj(c->r[1]);
    if (c->r[3] != JNI_ABORT) { jsize n = (*e)->GetArrayLength(e, arr); (*e)->SetBooleanArrayRegion(e, arr, 0, n, (jboolean *)G2H(c->r[2])); }
    if (c->r[3] != JNI_COMMIT) heap_free(c->r[2]);
}

void J_ReleaseByteArrayElements(CPU *c) {
    JNIEnv *e = jh_env(); jarray arr = jh_obj(c->r[1]);
    if (c->r[3] != JNI_ABORT) { jsize n = (*e)->GetArrayLength(e, arr); (*e)->SetByteArrayRegion(e, arr, 0, n, (jbyte *)G2H(c->r[2])); }
    if (c->r[3] != JNI_COMMIT) heap_free(c->r[2]);
}

void J_ReleaseCharArrayElements(CPU *c) {
    JNIEnv *e = jh_env(); jarray arr = jh_obj(c->r[1]);
    if (c->r[3] != JNI_ABORT) { jsize n = (*e)->GetArrayLength(e, arr); (*e)->SetCharArrayRegion(e, arr, 0, n, (jchar *)G2H(c->r[2])); }
    if (c->r[3] != JNI_COMMIT) heap_free(c->r[2]);
}

void J_ReleaseShortArrayElements(CPU *c) {
    JNIEnv *e = jh_env(); jarray arr = jh_obj(c->r[1]);
    if (c->r[3] != JNI_ABORT) { jsize n = (*e)->GetArrayLength(e, arr); (*e)->SetShortArrayRegion(e, arr, 0, n, (jshort *)G2H(c->r[2])); }
    if (c->r[3] != JNI_COMMIT) heap_free(c->r[2]);
}

void J_ReleaseIntArrayElements(CPU *c) {
    JNIEnv *e = jh_env(); jarray arr = jh_obj(c->r[1]);
    if (c->r[3] != JNI_ABORT) { jsize n = (*e)->GetArrayLength(e, arr); (*e)->SetIntArrayRegion(e, arr, 0, n, (jint *)G2H(c->r[2])); }
    if (c->r[3] != JNI_COMMIT) heap_free(c->r[2]);
}

void J_ReleaseLongArrayElements(CPU *c) {
    JNIEnv *e = jh_env(); jarray arr = jh_obj(c->r[1]);
    if (c->r[3] != JNI_ABORT) { jsize n = (*e)->GetArrayLength(e, arr); (*e)->SetLongArrayRegion(e, arr, 0, n, (jlong *)G2H(c->r[2])); }
    if (c->r[3] != JNI_COMMIT) heap_free(c->r[2]);
}

void J_ReleaseFloatArrayElements(CPU *c) {
    JNIEnv *e = jh_env(); jarray arr = jh_obj(c->r[1]);
    if (c->r[3] != JNI_ABORT) { jsize n = (*e)->GetArrayLength(e, arr); (*e)->SetFloatArrayRegion(e, arr, 0, n, (jfloat *)G2H(c->r[2])); }
    if (c->r[3] != JNI_COMMIT) heap_free(c->r[2]);
}

void J_ReleaseDoubleArrayElements(CPU *c) {
    JNIEnv *e = jh_env(); jarray arr = jh_obj(c->r[1]);
    if (c->r[3] != JNI_ABORT) { jsize n = (*e)->GetArrayLength(e, arr); (*e)->SetDoubleArrayRegion(e, arr, 0, n, (jdouble *)G2H(c->r[2])); }
    if (c->r[3] != JNI_COMMIT) heap_free(c->r[2]);
}

void J_GetBooleanArrayRegion(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    uint32_t arr = arg32(&a), ini = arg32(&a), n = arg32(&a), buf = arg32(&a);
    (*e)->GetBooleanArrayRegion(e, jh_obj(arr), (jsize)ini, (jsize)n, (jboolean *)G2H(buf));
}

void J_GetByteArrayRegion(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    uint32_t arr = arg32(&a), ini = arg32(&a), n = arg32(&a), buf = arg32(&a);
    (*e)->GetByteArrayRegion(e, jh_obj(arr), (jsize)ini, (jsize)n, (jbyte *)G2H(buf));
}

void J_GetCharArrayRegion(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    uint32_t arr = arg32(&a), ini = arg32(&a), n = arg32(&a), buf = arg32(&a);
    (*e)->GetCharArrayRegion(e, jh_obj(arr), (jsize)ini, (jsize)n, (jchar *)G2H(buf));
}

void J_GetShortArrayRegion(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    uint32_t arr = arg32(&a), ini = arg32(&a), n = arg32(&a), buf = arg32(&a);
    (*e)->GetShortArrayRegion(e, jh_obj(arr), (jsize)ini, (jsize)n, (jshort *)G2H(buf));
}

void J_GetIntArrayRegion(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    uint32_t arr = arg32(&a), ini = arg32(&a), n = arg32(&a), buf = arg32(&a);
    (*e)->GetIntArrayRegion(e, jh_obj(arr), (jsize)ini, (jsize)n, (jint *)G2H(buf));
}

void J_GetLongArrayRegion(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    uint32_t arr = arg32(&a), ini = arg32(&a), n = arg32(&a), buf = arg32(&a);
    (*e)->GetLongArrayRegion(e, jh_obj(arr), (jsize)ini, (jsize)n, (jlong *)G2H(buf));
}

void J_GetFloatArrayRegion(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    uint32_t arr = arg32(&a), ini = arg32(&a), n = arg32(&a), buf = arg32(&a);
    (*e)->GetFloatArrayRegion(e, jh_obj(arr), (jsize)ini, (jsize)n, (jfloat *)G2H(buf));
}

void J_GetDoubleArrayRegion(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    uint32_t arr = arg32(&a), ini = arg32(&a), n = arg32(&a), buf = arg32(&a);
    (*e)->GetDoubleArrayRegion(e, jh_obj(arr), (jsize)ini, (jsize)n, (jdouble *)G2H(buf));
}

void J_SetBooleanArrayRegion(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    uint32_t arr = arg32(&a), ini = arg32(&a), n = arg32(&a), buf = arg32(&a);
    (*e)->SetBooleanArrayRegion(e, jh_obj(arr), (jsize)ini, (jsize)n, (jboolean *)G2H(buf));
}

void J_SetByteArrayRegion(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    uint32_t arr = arg32(&a), ini = arg32(&a), n = arg32(&a), buf = arg32(&a);
    (*e)->SetByteArrayRegion(e, jh_obj(arr), (jsize)ini, (jsize)n, (jbyte *)G2H(buf));
}

void J_SetCharArrayRegion(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    uint32_t arr = arg32(&a), ini = arg32(&a), n = arg32(&a), buf = arg32(&a);
    (*e)->SetCharArrayRegion(e, jh_obj(arr), (jsize)ini, (jsize)n, (jchar *)G2H(buf));
}

void J_SetShortArrayRegion(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    uint32_t arr = arg32(&a), ini = arg32(&a), n = arg32(&a), buf = arg32(&a);
    (*e)->SetShortArrayRegion(e, jh_obj(arr), (jsize)ini, (jsize)n, (jshort *)G2H(buf));
}

void J_SetIntArrayRegion(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    uint32_t arr = arg32(&a), ini = arg32(&a), n = arg32(&a), buf = arg32(&a);
    (*e)->SetIntArrayRegion(e, jh_obj(arr), (jsize)ini, (jsize)n, (jint *)G2H(buf));
}

void J_SetLongArrayRegion(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    uint32_t arr = arg32(&a), ini = arg32(&a), n = arg32(&a), buf = arg32(&a);
    (*e)->SetLongArrayRegion(e, jh_obj(arr), (jsize)ini, (jsize)n, (jlong *)G2H(buf));
}

void J_SetFloatArrayRegion(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    uint32_t arr = arg32(&a), ini = arg32(&a), n = arg32(&a), buf = arg32(&a);
    (*e)->SetFloatArrayRegion(e, jh_obj(arr), (jsize)ini, (jsize)n, (jfloat *)G2H(buf));
}

void J_SetDoubleArrayRegion(CPU *c) {
    JNIEnv *e = jh_env(); Args a = args_de(c); arg32(&a);
    uint32_t arr = arg32(&a), ini = arg32(&a), n = arg32(&a), buf = arg32(&a);
    (*e)->SetDoubleArrayRegion(e, jh_obj(arr), (jsize)ini, (jsize)n, (jdouble *)G2H(buf));
}

void J_GetPrimitiveArrayCritical(CPU *c) { (void)c; rt_fatal("JNI nao implementado: GetPrimitiveArrayCritical"); }

void J_ReleasePrimitiveArrayCritical(CPU *c) { (void)c; rt_fatal("JNI nao implementado: ReleasePrimitiveArrayCritical"); }

void J_GetVersion(CPU *c);
void J_FindClass(CPU *c);
void J_GetSuperclass(CPU *c);
void J_IsAssignableFrom(CPU *c);
void J_Throw(CPU *c);
void J_ThrowNew(CPU *c);
void J_ExceptionOccurred(CPU *c);
void J_ExceptionDescribe(CPU *c);
void J_ExceptionClear(CPU *c);
void J_FatalError(CPU *c);
void J_PushLocalFrame(CPU *c);
void J_PopLocalFrame(CPU *c);
void J_NewGlobalRef(CPU *c);
void J_DeleteGlobalRef(CPU *c);
void J_DeleteLocalRef(CPU *c);
void J_IsSameObject(CPU *c);
void J_NewLocalRef(CPU *c);
void J_EnsureLocalCapacity(CPU *c);
void J_AllocObject(CPU *c);
void J_NewObject(CPU *c);
void J_NewObjectV(CPU *c);
void J_NewObjectA(CPU *c);
void J_GetObjectClass(CPU *c);
void J_IsInstanceOf(CPU *c);
void J_GetMethodID(CPU *c);
void J_GetFieldID(CPU *c);
void J_GetStaticMethodID(CPU *c);
void J_GetStaticFieldID(CPU *c);
void J_NewString(CPU *c);
void J_GetStringLength(CPU *c);
void J_GetStringChars(CPU *c);
void J_ReleaseStringChars(CPU *c);
void J_NewStringUTF(CPU *c);
void J_GetStringUTFLength(CPU *c);
void J_GetStringUTFChars(CPU *c);
void J_ReleaseStringUTFChars(CPU *c);
void J_GetArrayLength(CPU *c);
void J_NewObjectArray(CPU *c);
void J_GetObjectArrayElement(CPU *c);
void J_SetObjectArrayElement(CPU *c);
void J_RegisterNatives(CPU *c);
void J_UnregisterNatives(CPU *c);
void J_MonitorEnter(CPU *c);
void J_MonitorExit(CPU *c);
void J_GetJavaVM(CPU *c);
void J_GetStringRegion(CPU *c);
void J_GetStringUTFRegion(CPU *c);
void J_GetStringCritical(CPU *c);
void J_ReleaseStringCritical(CPU *c);
void J_NewWeakGlobalRef(CPU *c);
void J_DeleteWeakGlobalRef(CPU *c);
void J_ExceptionCheck(CPU *c);
void J_NewDirectByteBuffer(CPU *c);
void J_GetDirectBufferAddress(CPU *c);
void J_GetDirectBufferCapacity(CPU *c);
void J_GetObjectRefType(CPU *c);

uint32_t jni_tabela_jogo(void) {
    static uint32_t tab;
    if (tab) return tab;
    tab = heap_calloc(233, 4);
    uint32_t *t = (uint32_t *)G2H(tab);
    t[4] = ponte_nova(J_GetVersion, "JNI:GetVersion");
    t[5] = ponte_nova(J_DefineClass, "JNI:DefineClass");
    t[6] = ponte_nova(J_FindClass, "JNI:FindClass");
    t[7] = ponte_nova(J_FromReflectedMethod, "JNI:FromReflectedMethod");
    t[8] = ponte_nova(J_FromReflectedField, "JNI:FromReflectedField");
    t[9] = ponte_nova(J_ToReflectedMethod, "JNI:ToReflectedMethod");
    t[10] = ponte_nova(J_GetSuperclass, "JNI:GetSuperclass");
    t[11] = ponte_nova(J_IsAssignableFrom, "JNI:IsAssignableFrom");
    t[12] = ponte_nova(J_ToReflectedField, "JNI:ToReflectedField");
    t[13] = ponte_nova(J_Throw, "JNI:Throw");
    t[14] = ponte_nova(J_ThrowNew, "JNI:ThrowNew");
    t[15] = ponte_nova(J_ExceptionOccurred, "JNI:ExceptionOccurred");
    t[16] = ponte_nova(J_ExceptionDescribe, "JNI:ExceptionDescribe");
    t[17] = ponte_nova(J_ExceptionClear, "JNI:ExceptionClear");
    t[18] = ponte_nova(J_FatalError, "JNI:FatalError");
    t[19] = ponte_nova(J_PushLocalFrame, "JNI:PushLocalFrame");
    t[20] = ponte_nova(J_PopLocalFrame, "JNI:PopLocalFrame");
    t[21] = ponte_nova(J_NewGlobalRef, "JNI:NewGlobalRef");
    t[22] = ponte_nova(J_DeleteGlobalRef, "JNI:DeleteGlobalRef");
    t[23] = ponte_nova(J_DeleteLocalRef, "JNI:DeleteLocalRef");
    t[24] = ponte_nova(J_IsSameObject, "JNI:IsSameObject");
    t[25] = ponte_nova(J_NewLocalRef, "JNI:NewLocalRef");
    t[26] = ponte_nova(J_EnsureLocalCapacity, "JNI:EnsureLocalCapacity");
    t[27] = ponte_nova(J_AllocObject, "JNI:AllocObject");
    t[28] = ponte_nova(J_NewObject, "JNI:NewObject");
    t[29] = ponte_nova(J_NewObjectV, "JNI:NewObjectV");
    t[30] = ponte_nova(J_NewObjectA, "JNI:NewObjectA");
    t[31] = ponte_nova(J_GetObjectClass, "JNI:GetObjectClass");
    t[32] = ponte_nova(J_IsInstanceOf, "JNI:IsInstanceOf");
    t[33] = ponte_nova(J_GetMethodID, "JNI:GetMethodID");
    t[34] = ponte_nova(J_CallObjectMethod, "JNI:CallObjectMethod");
    t[35] = ponte_nova(J_CallObjectMethodV, "JNI:CallObjectMethodV");
    t[36] = ponte_nova(J_CallObjectMethodA, "JNI:CallObjectMethodA");
    t[37] = ponte_nova(J_CallBooleanMethod, "JNI:CallBooleanMethod");
    t[38] = ponte_nova(J_CallBooleanMethodV, "JNI:CallBooleanMethodV");
    t[39] = ponte_nova(J_CallBooleanMethodA, "JNI:CallBooleanMethodA");
    t[40] = ponte_nova(J_CallByteMethod, "JNI:CallByteMethod");
    t[41] = ponte_nova(J_CallByteMethodV, "JNI:CallByteMethodV");
    t[42] = ponte_nova(J_CallByteMethodA, "JNI:CallByteMethodA");
    t[43] = ponte_nova(J_CallCharMethod, "JNI:CallCharMethod");
    t[44] = ponte_nova(J_CallCharMethodV, "JNI:CallCharMethodV");
    t[45] = ponte_nova(J_CallCharMethodA, "JNI:CallCharMethodA");
    t[46] = ponte_nova(J_CallShortMethod, "JNI:CallShortMethod");
    t[47] = ponte_nova(J_CallShortMethodV, "JNI:CallShortMethodV");
    t[48] = ponte_nova(J_CallShortMethodA, "JNI:CallShortMethodA");
    t[49] = ponte_nova(J_CallIntMethod, "JNI:CallIntMethod");
    t[50] = ponte_nova(J_CallIntMethodV, "JNI:CallIntMethodV");
    t[51] = ponte_nova(J_CallIntMethodA, "JNI:CallIntMethodA");
    t[52] = ponte_nova(J_CallLongMethod, "JNI:CallLongMethod");
    t[53] = ponte_nova(J_CallLongMethodV, "JNI:CallLongMethodV");
    t[54] = ponte_nova(J_CallLongMethodA, "JNI:CallLongMethodA");
    t[55] = ponte_nova(J_CallFloatMethod, "JNI:CallFloatMethod");
    t[56] = ponte_nova(J_CallFloatMethodV, "JNI:CallFloatMethodV");
    t[57] = ponte_nova(J_CallFloatMethodA, "JNI:CallFloatMethodA");
    t[58] = ponte_nova(J_CallDoubleMethod, "JNI:CallDoubleMethod");
    t[59] = ponte_nova(J_CallDoubleMethodV, "JNI:CallDoubleMethodV");
    t[60] = ponte_nova(J_CallDoubleMethodA, "JNI:CallDoubleMethodA");
    t[61] = ponte_nova(J_CallVoidMethod, "JNI:CallVoidMethod");
    t[62] = ponte_nova(J_CallVoidMethodV, "JNI:CallVoidMethodV");
    t[63] = ponte_nova(J_CallVoidMethodA, "JNI:CallVoidMethodA");
    t[64] = ponte_nova(J_CallNonvirtualObjectMethod, "JNI:CallNonvirtualObjectMethod");
    t[65] = ponte_nova(J_CallNonvirtualObjectMethodV, "JNI:CallNonvirtualObjectMethodV");
    t[66] = ponte_nova(J_CallNonvirtualObjectMethodA, "JNI:CallNonvirtualObjectMethodA");
    t[67] = ponte_nova(J_CallNonvirtualBooleanMethod, "JNI:CallNonvirtualBooleanMethod");
    t[68] = ponte_nova(J_CallNonvirtualBooleanMethodV, "JNI:CallNonvirtualBooleanMethodV");
    t[69] = ponte_nova(J_CallNonvirtualBooleanMethodA, "JNI:CallNonvirtualBooleanMethodA");
    t[70] = ponte_nova(J_CallNonvirtualByteMethod, "JNI:CallNonvirtualByteMethod");
    t[71] = ponte_nova(J_CallNonvirtualByteMethodV, "JNI:CallNonvirtualByteMethodV");
    t[72] = ponte_nova(J_CallNonvirtualByteMethodA, "JNI:CallNonvirtualByteMethodA");
    t[73] = ponte_nova(J_CallNonvirtualCharMethod, "JNI:CallNonvirtualCharMethod");
    t[74] = ponte_nova(J_CallNonvirtualCharMethodV, "JNI:CallNonvirtualCharMethodV");
    t[75] = ponte_nova(J_CallNonvirtualCharMethodA, "JNI:CallNonvirtualCharMethodA");
    t[76] = ponte_nova(J_CallNonvirtualShortMethod, "JNI:CallNonvirtualShortMethod");
    t[77] = ponte_nova(J_CallNonvirtualShortMethodV, "JNI:CallNonvirtualShortMethodV");
    t[78] = ponte_nova(J_CallNonvirtualShortMethodA, "JNI:CallNonvirtualShortMethodA");
    t[79] = ponte_nova(J_CallNonvirtualIntMethod, "JNI:CallNonvirtualIntMethod");
    t[80] = ponte_nova(J_CallNonvirtualIntMethodV, "JNI:CallNonvirtualIntMethodV");
    t[81] = ponte_nova(J_CallNonvirtualIntMethodA, "JNI:CallNonvirtualIntMethodA");
    t[82] = ponte_nova(J_CallNonvirtualLongMethod, "JNI:CallNonvirtualLongMethod");
    t[83] = ponte_nova(J_CallNonvirtualLongMethodV, "JNI:CallNonvirtualLongMethodV");
    t[84] = ponte_nova(J_CallNonvirtualLongMethodA, "JNI:CallNonvirtualLongMethodA");
    t[85] = ponte_nova(J_CallNonvirtualFloatMethod, "JNI:CallNonvirtualFloatMethod");
    t[86] = ponte_nova(J_CallNonvirtualFloatMethodV, "JNI:CallNonvirtualFloatMethodV");
    t[87] = ponte_nova(J_CallNonvirtualFloatMethodA, "JNI:CallNonvirtualFloatMethodA");
    t[88] = ponte_nova(J_CallNonvirtualDoubleMethod, "JNI:CallNonvirtualDoubleMethod");
    t[89] = ponte_nova(J_CallNonvirtualDoubleMethodV, "JNI:CallNonvirtualDoubleMethodV");
    t[90] = ponte_nova(J_CallNonvirtualDoubleMethodA, "JNI:CallNonvirtualDoubleMethodA");
    t[91] = ponte_nova(J_CallNonvirtualVoidMethod, "JNI:CallNonvirtualVoidMethod");
    t[92] = ponte_nova(J_CallNonvirtualVoidMethodV, "JNI:CallNonvirtualVoidMethodV");
    t[93] = ponte_nova(J_CallNonvirtualVoidMethodA, "JNI:CallNonvirtualVoidMethodA");
    t[94] = ponte_nova(J_GetFieldID, "JNI:GetFieldID");
    t[95] = ponte_nova(J_GetObjectField, "JNI:GetObjectField");
    t[96] = ponte_nova(J_GetBooleanField, "JNI:GetBooleanField");
    t[97] = ponte_nova(J_GetByteField, "JNI:GetByteField");
    t[98] = ponte_nova(J_GetCharField, "JNI:GetCharField");
    t[99] = ponte_nova(J_GetShortField, "JNI:GetShortField");
    t[100] = ponte_nova(J_GetIntField, "JNI:GetIntField");
    t[101] = ponte_nova(J_GetLongField, "JNI:GetLongField");
    t[102] = ponte_nova(J_GetFloatField, "JNI:GetFloatField");
    t[103] = ponte_nova(J_GetDoubleField, "JNI:GetDoubleField");
    t[104] = ponte_nova(J_SetObjectField, "JNI:SetObjectField");
    t[105] = ponte_nova(J_SetBooleanField, "JNI:SetBooleanField");
    t[106] = ponte_nova(J_SetByteField, "JNI:SetByteField");
    t[107] = ponte_nova(J_SetCharField, "JNI:SetCharField");
    t[108] = ponte_nova(J_SetShortField, "JNI:SetShortField");
    t[109] = ponte_nova(J_SetIntField, "JNI:SetIntField");
    t[110] = ponte_nova(J_SetLongField, "JNI:SetLongField");
    t[111] = ponte_nova(J_SetFloatField, "JNI:SetFloatField");
    t[112] = ponte_nova(J_SetDoubleField, "JNI:SetDoubleField");
    t[113] = ponte_nova(J_GetStaticMethodID, "JNI:GetStaticMethodID");
    t[114] = ponte_nova(J_CallStaticObjectMethod, "JNI:CallStaticObjectMethod");
    t[115] = ponte_nova(J_CallStaticObjectMethodV, "JNI:CallStaticObjectMethodV");
    t[116] = ponte_nova(J_CallStaticObjectMethodA, "JNI:CallStaticObjectMethodA");
    t[117] = ponte_nova(J_CallStaticBooleanMethod, "JNI:CallStaticBooleanMethod");
    t[118] = ponte_nova(J_CallStaticBooleanMethodV, "JNI:CallStaticBooleanMethodV");
    t[119] = ponte_nova(J_CallStaticBooleanMethodA, "JNI:CallStaticBooleanMethodA");
    t[120] = ponte_nova(J_CallStaticByteMethod, "JNI:CallStaticByteMethod");
    t[121] = ponte_nova(J_CallStaticByteMethodV, "JNI:CallStaticByteMethodV");
    t[122] = ponte_nova(J_CallStaticByteMethodA, "JNI:CallStaticByteMethodA");
    t[123] = ponte_nova(J_CallStaticCharMethod, "JNI:CallStaticCharMethod");
    t[124] = ponte_nova(J_CallStaticCharMethodV, "JNI:CallStaticCharMethodV");
    t[125] = ponte_nova(J_CallStaticCharMethodA, "JNI:CallStaticCharMethodA");
    t[126] = ponte_nova(J_CallStaticShortMethod, "JNI:CallStaticShortMethod");
    t[127] = ponte_nova(J_CallStaticShortMethodV, "JNI:CallStaticShortMethodV");
    t[128] = ponte_nova(J_CallStaticShortMethodA, "JNI:CallStaticShortMethodA");
    t[129] = ponte_nova(J_CallStaticIntMethod, "JNI:CallStaticIntMethod");
    t[130] = ponte_nova(J_CallStaticIntMethodV, "JNI:CallStaticIntMethodV");
    t[131] = ponte_nova(J_CallStaticIntMethodA, "JNI:CallStaticIntMethodA");
    t[132] = ponte_nova(J_CallStaticLongMethod, "JNI:CallStaticLongMethod");
    t[133] = ponte_nova(J_CallStaticLongMethodV, "JNI:CallStaticLongMethodV");
    t[134] = ponte_nova(J_CallStaticLongMethodA, "JNI:CallStaticLongMethodA");
    t[135] = ponte_nova(J_CallStaticFloatMethod, "JNI:CallStaticFloatMethod");
    t[136] = ponte_nova(J_CallStaticFloatMethodV, "JNI:CallStaticFloatMethodV");
    t[137] = ponte_nova(J_CallStaticFloatMethodA, "JNI:CallStaticFloatMethodA");
    t[138] = ponte_nova(J_CallStaticDoubleMethod, "JNI:CallStaticDoubleMethod");
    t[139] = ponte_nova(J_CallStaticDoubleMethodV, "JNI:CallStaticDoubleMethodV");
    t[140] = ponte_nova(J_CallStaticDoubleMethodA, "JNI:CallStaticDoubleMethodA");
    t[141] = ponte_nova(J_CallStaticVoidMethod, "JNI:CallStaticVoidMethod");
    t[142] = ponte_nova(J_CallStaticVoidMethodV, "JNI:CallStaticVoidMethodV");
    t[143] = ponte_nova(J_CallStaticVoidMethodA, "JNI:CallStaticVoidMethodA");
    t[144] = ponte_nova(J_GetStaticFieldID, "JNI:GetStaticFieldID");
    t[145] = ponte_nova(J_GetStaticObjectField, "JNI:GetStaticObjectField");
    t[146] = ponte_nova(J_GetStaticBooleanField, "JNI:GetStaticBooleanField");
    t[147] = ponte_nova(J_GetStaticByteField, "JNI:GetStaticByteField");
    t[148] = ponte_nova(J_GetStaticCharField, "JNI:GetStaticCharField");
    t[149] = ponte_nova(J_GetStaticShortField, "JNI:GetStaticShortField");
    t[150] = ponte_nova(J_GetStaticIntField, "JNI:GetStaticIntField");
    t[151] = ponte_nova(J_GetStaticLongField, "JNI:GetStaticLongField");
    t[152] = ponte_nova(J_GetStaticFloatField, "JNI:GetStaticFloatField");
    t[153] = ponte_nova(J_GetStaticDoubleField, "JNI:GetStaticDoubleField");
    t[154] = ponte_nova(J_SetStaticObjectField, "JNI:SetStaticObjectField");
    t[155] = ponte_nova(J_SetStaticBooleanField, "JNI:SetStaticBooleanField");
    t[156] = ponte_nova(J_SetStaticByteField, "JNI:SetStaticByteField");
    t[157] = ponte_nova(J_SetStaticCharField, "JNI:SetStaticCharField");
    t[158] = ponte_nova(J_SetStaticShortField, "JNI:SetStaticShortField");
    t[159] = ponte_nova(J_SetStaticIntField, "JNI:SetStaticIntField");
    t[160] = ponte_nova(J_SetStaticLongField, "JNI:SetStaticLongField");
    t[161] = ponte_nova(J_SetStaticFloatField, "JNI:SetStaticFloatField");
    t[162] = ponte_nova(J_SetStaticDoubleField, "JNI:SetStaticDoubleField");
    t[163] = ponte_nova(J_NewString, "JNI:NewString");
    t[164] = ponte_nova(J_GetStringLength, "JNI:GetStringLength");
    t[165] = ponte_nova(J_GetStringChars, "JNI:GetStringChars");
    t[166] = ponte_nova(J_ReleaseStringChars, "JNI:ReleaseStringChars");
    t[167] = ponte_nova(J_NewStringUTF, "JNI:NewStringUTF");
    t[168] = ponte_nova(J_GetStringUTFLength, "JNI:GetStringUTFLength");
    t[169] = ponte_nova(J_GetStringUTFChars, "JNI:GetStringUTFChars");
    t[170] = ponte_nova(J_ReleaseStringUTFChars, "JNI:ReleaseStringUTFChars");
    t[171] = ponte_nova(J_GetArrayLength, "JNI:GetArrayLength");
    t[172] = ponte_nova(J_NewObjectArray, "JNI:NewObjectArray");
    t[173] = ponte_nova(J_GetObjectArrayElement, "JNI:GetObjectArrayElement");
    t[174] = ponte_nova(J_SetObjectArrayElement, "JNI:SetObjectArrayElement");
    t[175] = ponte_nova(J_NewBooleanArray, "JNI:NewBooleanArray");
    t[176] = ponte_nova(J_NewByteArray, "JNI:NewByteArray");
    t[177] = ponte_nova(J_NewCharArray, "JNI:NewCharArray");
    t[178] = ponte_nova(J_NewShortArray, "JNI:NewShortArray");
    t[179] = ponte_nova(J_NewIntArray, "JNI:NewIntArray");
    t[180] = ponte_nova(J_NewLongArray, "JNI:NewLongArray");
    t[181] = ponte_nova(J_NewFloatArray, "JNI:NewFloatArray");
    t[182] = ponte_nova(J_NewDoubleArray, "JNI:NewDoubleArray");
    t[183] = ponte_nova(J_GetBooleanArrayElements, "JNI:GetBooleanArrayElements");
    t[184] = ponte_nova(J_GetByteArrayElements, "JNI:GetByteArrayElements");
    t[185] = ponte_nova(J_GetCharArrayElements, "JNI:GetCharArrayElements");
    t[186] = ponte_nova(J_GetShortArrayElements, "JNI:GetShortArrayElements");
    t[187] = ponte_nova(J_GetIntArrayElements, "JNI:GetIntArrayElements");
    t[188] = ponte_nova(J_GetLongArrayElements, "JNI:GetLongArrayElements");
    t[189] = ponte_nova(J_GetFloatArrayElements, "JNI:GetFloatArrayElements");
    t[190] = ponte_nova(J_GetDoubleArrayElements, "JNI:GetDoubleArrayElements");
    t[191] = ponte_nova(J_ReleaseBooleanArrayElements, "JNI:ReleaseBooleanArrayElements");
    t[192] = ponte_nova(J_ReleaseByteArrayElements, "JNI:ReleaseByteArrayElements");
    t[193] = ponte_nova(J_ReleaseCharArrayElements, "JNI:ReleaseCharArrayElements");
    t[194] = ponte_nova(J_ReleaseShortArrayElements, "JNI:ReleaseShortArrayElements");
    t[195] = ponte_nova(J_ReleaseIntArrayElements, "JNI:ReleaseIntArrayElements");
    t[196] = ponte_nova(J_ReleaseLongArrayElements, "JNI:ReleaseLongArrayElements");
    t[197] = ponte_nova(J_ReleaseFloatArrayElements, "JNI:ReleaseFloatArrayElements");
    t[198] = ponte_nova(J_ReleaseDoubleArrayElements, "JNI:ReleaseDoubleArrayElements");
    t[199] = ponte_nova(J_GetBooleanArrayRegion, "JNI:GetBooleanArrayRegion");
    t[200] = ponte_nova(J_GetByteArrayRegion, "JNI:GetByteArrayRegion");
    t[201] = ponte_nova(J_GetCharArrayRegion, "JNI:GetCharArrayRegion");
    t[202] = ponte_nova(J_GetShortArrayRegion, "JNI:GetShortArrayRegion");
    t[203] = ponte_nova(J_GetIntArrayRegion, "JNI:GetIntArrayRegion");
    t[204] = ponte_nova(J_GetLongArrayRegion, "JNI:GetLongArrayRegion");
    t[205] = ponte_nova(J_GetFloatArrayRegion, "JNI:GetFloatArrayRegion");
    t[206] = ponte_nova(J_GetDoubleArrayRegion, "JNI:GetDoubleArrayRegion");
    t[207] = ponte_nova(J_SetBooleanArrayRegion, "JNI:SetBooleanArrayRegion");
    t[208] = ponte_nova(J_SetByteArrayRegion, "JNI:SetByteArrayRegion");
    t[209] = ponte_nova(J_SetCharArrayRegion, "JNI:SetCharArrayRegion");
    t[210] = ponte_nova(J_SetShortArrayRegion, "JNI:SetShortArrayRegion");
    t[211] = ponte_nova(J_SetIntArrayRegion, "JNI:SetIntArrayRegion");
    t[212] = ponte_nova(J_SetLongArrayRegion, "JNI:SetLongArrayRegion");
    t[213] = ponte_nova(J_SetFloatArrayRegion, "JNI:SetFloatArrayRegion");
    t[214] = ponte_nova(J_SetDoubleArrayRegion, "JNI:SetDoubleArrayRegion");
    t[215] = ponte_nova(J_RegisterNatives, "JNI:RegisterNatives");
    t[216] = ponte_nova(J_UnregisterNatives, "JNI:UnregisterNatives");
    t[217] = ponte_nova(J_MonitorEnter, "JNI:MonitorEnter");
    t[218] = ponte_nova(J_MonitorExit, "JNI:MonitorExit");
    t[219] = ponte_nova(J_GetJavaVM, "JNI:GetJavaVM");
    t[220] = ponte_nova(J_GetStringRegion, "JNI:GetStringRegion");
    t[221] = ponte_nova(J_GetStringUTFRegion, "JNI:GetStringUTFRegion");
    t[222] = ponte_nova(J_GetPrimitiveArrayCritical, "JNI:GetPrimitiveArrayCritical");
    t[223] = ponte_nova(J_ReleasePrimitiveArrayCritical, "JNI:ReleasePrimitiveArrayCritical");
    t[224] = ponte_nova(J_GetStringCritical, "JNI:GetStringCritical");
    t[225] = ponte_nova(J_ReleaseStringCritical, "JNI:ReleaseStringCritical");
    t[226] = ponte_nova(J_NewWeakGlobalRef, "JNI:NewWeakGlobalRef");
    t[227] = ponte_nova(J_DeleteWeakGlobalRef, "JNI:DeleteWeakGlobalRef");
    t[228] = ponte_nova(J_ExceptionCheck, "JNI:ExceptionCheck");
    t[229] = ponte_nova(J_NewDirectByteBuffer, "JNI:NewDirectByteBuffer");
    t[230] = ponte_nova(J_GetDirectBufferAddress, "JNI:GetDirectBufferAddress");
    t[231] = ponte_nova(J_GetDirectBufferCapacity, "JNI:GetDirectBufferCapacity");
    t[232] = ponte_nova(J_GetObjectRefType, "JNI:GetObjectRefType");
    return tab;
}

void V_DestroyJavaVM(CPU *c);
void V_AttachCurrentThread(CPU *c);
void V_DetachCurrentThread(CPU *c);
void V_GetEnv(CPU *c);
void V_AttachCurrentThreadAsDaemon(CPU *c);
uint32_t jni_tabela_vm_jogo(void) {
    static uint32_t tab;
    if (tab) return tab;
    tab = heap_calloc(8, 4);
    uint32_t *t = (uint32_t *)G2H(tab);
    t[3] = ponte_nova(V_DestroyJavaVM, "JavaVM:DestroyJavaVM");
    t[4] = ponte_nova(V_AttachCurrentThread, "JavaVM:AttachCurrentThread");
    t[5] = ponte_nova(V_DetachCurrentThread, "JavaVM:DetachCurrentThread");
    t[6] = ponte_nova(V_GetEnv, "JavaVM:GetEnv");
    t[7] = ponte_nova(V_AttachCurrentThreadAsDaemon, "JavaVM:AttachCurrentThreadAsDaemon");
    return tab;
}

JNIEXPORT void JNICALL Java_com_nvidia_forge_DeviceInfo_addDevice(JNIEnv *e, jobject self, jint p0, jint p1, jboolean p2, jboolean p3, jboolean p4, jboolean p5, jint p6, jint p7, jint p8, jint p9, jboolean p10) {
    rt_garante();
#ifdef MGS2_DEPURA
    rt_log("DeviceInfo.addDevice(id %x, slot %d, ... avisa %d)", p0, p1, p10);
#endif
    jh_define_env(e);
    int marca = jh_marca_locais();
    uint32_t a[24]; int n = 0;
    a[n++] = jh_env_jogo();
    a[n++] = jh_local(self);
    a[n++] = (uint32_t)(int32_t)p0;
    a[n++] = (uint32_t)(int32_t)p1;
    a[n++] = (uint32_t)(int32_t)p2;
    a[n++] = (uint32_t)(int32_t)p3;
    a[n++] = (uint32_t)(int32_t)p4;
    a[n++] = (uint32_t)(int32_t)p5;
    a[n++] = (uint32_t)(int32_t)p6;
    a[n++] = (uint32_t)(int32_t)p7;
    a[n++] = (uint32_t)(int32_t)p8;
    a[n++] = (uint32_t)(int32_t)p9;
    a[n++] = (uint32_t)(int32_t)p10;
    CPU *c = cpu_atual();
    uint32_t r = jogo_chama_v(c, 0x02b32120u, n, a); (void)r;
    jh_solta_locais(marca);
}

JNIEXPORT void JNICALL Java_com_nvidia_forge_DeviceInfo_removeDevice(JNIEnv *e, jobject self, jint p0) {
    rt_garante();
    jh_define_env(e);
    int marca = jh_marca_locais();
    uint32_t a[24]; int n = 0;
    a[n++] = jh_env_jogo();
    a[n++] = jh_local(self);
    a[n++] = (uint32_t)(int32_t)p0;
    CPU *c = cpu_atual();
    uint32_t r = jogo_chama_v(c, 0x02b32030u, n, a); (void)r;
    jh_solta_locais(marca);
}

JNIEXPORT void JNICALL Java_com_nvidia_forge_DeviceInfo_setBatteryLevel(JNIEnv *e, jobject self, jint p0, jint p1) {
    rt_garante();
    jh_define_env(e);
    int marca = jh_marca_locais();
    uint32_t a[24]; int n = 0;
    a[n++] = jh_env_jogo();
    a[n++] = jh_local(self);
    a[n++] = (uint32_t)(int32_t)p0;
    a[n++] = (uint32_t)(int32_t)p1;
    CPU *c = cpu_atual();
    uint32_t r = jogo_chama_v(c, 0x02b3234cu, n, a); (void)r;
    jh_solta_locais(marca);
}

JNIEXPORT void JNICALL Java_com_nvidia_forge_DeviceInfo_updateDeviceFlags(JNIEnv *e, jobject self, jint p0, jboolean p1, jboolean p2, jboolean p3) {
    rt_garante();
    jh_define_env(e);
    int marca = jh_marca_locais();
    uint32_t a[24]; int n = 0;
    a[n++] = jh_env_jogo();
    a[n++] = jh_local(self);
    a[n++] = (uint32_t)(int32_t)p0;
    a[n++] = (uint32_t)(int32_t)p1;
    a[n++] = (uint32_t)(int32_t)p2;
    a[n++] = (uint32_t)(int32_t)p3;
    CPU *c = cpu_atual();
    uint32_t r = jogo_chama_v(c, 0x02b322c4u, n, a); (void)r;
    jh_solta_locais(marca);
}

JNIEXPORT void JNICALL Java_com_nvidia_forge_DeviceState_setState(JNIEnv *e, jobject self, jint p0, jint p1, jfloat p2, jfloat p3, jfloat p4, jfloat p5, jfloat p6, jfloat p7) {
    rt_garante();
#ifdef MGS2_DEPURA
    { static int n; if (n++ < 30) rt_log("DeviceState.setState(slot %d, botoes %04x, lt %.2f rt %.2f, esq %.2f %.2f, dir %.2f %.2f)", p0, p1, p2, p3, p4, p5, p6, p7); }
#endif
    jh_define_env(e);
    int marca = jh_marca_locais();
    uint32_t a[24]; int n = 0;
    a[n++] = jh_env_jogo();
    a[n++] = jh_local(self);
    a[n++] = (uint32_t)(int32_t)p0;
    a[n++] = (uint32_t)(int32_t)p1;
    { uint32_t w; memcpy(&w, &p2, 4); a[n++] = w; }
    { uint32_t w; memcpy(&w, &p3, 4); a[n++] = w; }
    { uint32_t w; memcpy(&w, &p4, 4); a[n++] = w; }
    { uint32_t w; memcpy(&w, &p5, 4); a[n++] = w; }
    { uint32_t w; memcpy(&w, &p6, 4); a[n++] = w; }
    { uint32_t w; memcpy(&w, &p7, 4); a[n++] = w; }
    CPU *c = cpu_atual();
    uint32_t r = jogo_chama_v(c, 0x02b32524u, n, a); (void)r;
    jh_solta_locais(marca);
}

JNIEXPORT void JNICALL Java_com_nvidia_forge_InputSystem_addKeyboardEvent(JNIEnv *e, jclass self, jint p0, jboolean p1, jboolean p2) {
    rt_garante();
    jh_define_env(e);
    int marca = jh_marca_locais();
    uint32_t a[24]; int n = 0;
    a[n++] = jh_env_jogo();
    a[n++] = jh_local(self);
    a[n++] = (uint32_t)(int32_t)p0;
    a[n++] = (uint32_t)(int32_t)p1;
    a[n++] = (uint32_t)(int32_t)p2;
    CPU *c = cpu_atual();
    uint32_t r = jogo_chama_v(c, 0x02b32eb8u, n, a); (void)r;
    jh_solta_locais(marca);
}

JNIEXPORT void JNICALL Java_com_nvidia_forge_InputSystem_addMouseButtonEvent(JNIEnv *e, jclass self, jint p0, jboolean p1, jint p2, jint p3, jint p4, jint p5) {
    rt_garante();
    jh_define_env(e);
    int marca = jh_marca_locais();
    uint32_t a[24]; int n = 0;
    a[n++] = jh_env_jogo();
    a[n++] = jh_local(self);
    a[n++] = (uint32_t)(int32_t)p0;
    a[n++] = (uint32_t)(int32_t)p1;
    a[n++] = (uint32_t)(int32_t)p2;
    a[n++] = (uint32_t)(int32_t)p3;
    a[n++] = (uint32_t)(int32_t)p4;
    a[n++] = (uint32_t)(int32_t)p5;
    CPU *c = cpu_atual();
    uint32_t r = jogo_chama_v(c, 0x02b338f0u, n, a); (void)r;
    jh_solta_locais(marca);
}

JNIEXPORT void JNICALL Java_com_nvidia_forge_InputSystem_addMouseMoveEvent(JNIEnv *e, jclass self, jint p0, jint p1, jint p2, jint p3, jint p4, jint p5) {
    rt_garante();
    jh_define_env(e);
    int marca = jh_marca_locais();
    uint32_t a[24]; int n = 0;
    a[n++] = jh_env_jogo();
    a[n++] = jh_local(self);
    a[n++] = (uint32_t)(int32_t)p0;
    a[n++] = (uint32_t)(int32_t)p1;
    a[n++] = (uint32_t)(int32_t)p2;
    a[n++] = (uint32_t)(int32_t)p3;
    a[n++] = (uint32_t)(int32_t)p4;
    a[n++] = (uint32_t)(int32_t)p5;
    CPU *c = cpu_atual();
    uint32_t r = jogo_chama_v(c, 0x02b33728u, n, a); (void)r;
    jh_solta_locais(marca);
}

JNIEXPORT void JNICALL Java_com_nvidia_forge_InputSystem_addMouseWheelEvent(JNIEnv *e, jclass self, jint p0, jint p1, jint p2, jint p3, jint p4, jint p5) {
    rt_garante();
    jh_define_env(e);
    int marca = jh_marca_locais();
    uint32_t a[24]; int n = 0;
    a[n++] = jh_env_jogo();
    a[n++] = jh_local(self);
    a[n++] = (uint32_t)(int32_t)p0;
    a[n++] = (uint32_t)(int32_t)p1;
    a[n++] = (uint32_t)(int32_t)p2;
    a[n++] = (uint32_t)(int32_t)p3;
    a[n++] = (uint32_t)(int32_t)p4;
    a[n++] = (uint32_t)(int32_t)p5;
    CPU *c = cpu_atual();
    uint32_t r = jogo_chama_v(c, 0x02b33ac8u, n, a); (void)r;
    jh_solta_locais(marca);
}

JNIEXPORT void JNICALL Java_com_nvidia_forge_InputSystem_clearDevices(JNIEnv *e, jclass self) {
    rt_garante();
    jh_define_env(e);
    int marca = jh_marca_locais();
    uint32_t a[24]; int n = 0;
    a[n++] = jh_env_jogo();
    a[n++] = jh_local(self);
    CPU *c = cpu_atual();
    uint32_t r = jogo_chama_v(c, 0x02b3238cu, n, a); (void)r;
    jh_solta_locais(marca);
}

JNIEXPORT void JNICALL Java_com_nvidia_forge_InputSystem_initInputSystem(JNIEnv *e, jclass self) {
    rt_garante();
    jh_define_env(e);
    int marca = jh_marca_locais();
    uint32_t a[24]; int n = 0;
    a[n++] = jh_env_jogo();
    a[n++] = jh_local(self);
    CPU *c = cpu_atual();
    uint32_t r = jogo_chama_v(c, 0x02b33e50u, n, a); (void)r;
    jh_solta_locais(marca);
}

JNIEXPORT void JNICALL Java_com_nvidia_forge_InputSystem_onCreate(JNIEnv *e, jclass self) {
    rt_garante();
    jh_define_env(e);
    int marca = jh_marca_locais();
    uint32_t a[24]; int n = 0;
    a[n++] = jh_env_jogo();
    a[n++] = jh_local(self);
    CPU *c = cpu_atual();
    uint32_t r = jogo_chama_v(c, 0x02b327ccu, n, a); (void)r;
    jh_solta_locais(marca);
}

JNIEXPORT void JNICALL Java_com_nvidia_forge_InputSystem_onDestroy(JNIEnv *e, jclass self) {
    rt_garante();
    jh_define_env(e);
    int marca = jh_marca_locais();
    uint32_t a[24]; int n = 0;
    a[n++] = jh_env_jogo();
    a[n++] = jh_local(self);
    CPU *c = cpu_atual();
    uint32_t r = jogo_chama_v(c, 0x02b32d14u, n, a); (void)r;
    jh_solta_locais(marca);
}

JNIEXPORT void JNICALL Java_com_nvidia_forge_InputSystem_onGamepadsLost(JNIEnv *e, jclass self) {
    rt_garante();
    jh_define_env(e);
    int marca = jh_marca_locais();
    uint32_t a[24]; int n = 0;
    a[n++] = jh_env_jogo();
    a[n++] = jh_local(self);
    CPU *c = cpu_atual();
    uint32_t r = jogo_chama_v(c, 0x02b32d38u, n, a); (void)r;
    jh_solta_locais(marca);
}

JNIEXPORT void JNICALL Java_com_nvidia_forge_InputSystem_onPause(JNIEnv *e, jclass self) {
    rt_garante();
    jh_define_env(e);
    int marca = jh_marca_locais();
    uint32_t a[24]; int n = 0;
    a[n++] = jh_env_jogo();
    a[n++] = jh_local(self);
    CPU *c = cpu_atual();
    uint32_t r = jogo_chama_v(c, 0x02b327f0u, n, a); (void)r;
    jh_solta_locais(marca);
}

JNIEXPORT void JNICALL Java_com_nvidia_forge_InputSystem_onRestart(JNIEnv *e, jclass self) {
    rt_garante();
    jh_define_env(e);
    int marca = jh_marca_locais();
    uint32_t a[24]; int n = 0;
    a[n++] = jh_env_jogo();
    a[n++] = jh_local(self);
    CPU *c = cpu_atual();
    uint32_t r = jogo_chama_v(c, 0x02b32cf0u, n, a); (void)r;
    jh_solta_locais(marca);
}

JNIEXPORT void JNICALL Java_com_nvidia_forge_InputSystem_onResume(JNIEnv *e, jclass self) {
    rt_garante();
    jh_define_env(e);
    int marca = jh_marca_locais();
    uint32_t a[24]; int n = 0;
    a[n++] = jh_env_jogo();
    a[n++] = jh_local(self);
    CPU *c = cpu_atual();
    uint32_t r = jogo_chama_v(c, 0x02b3299cu, n, a); (void)r;
    jh_solta_locais(marca);
}

JNIEXPORT void JNICALL Java_com_nvidia_forge_InputSystem_onStart(JNIEnv *e, jclass self) {
    rt_garante();
    jh_define_env(e);
    int marca = jh_marca_locais();
    uint32_t a[24]; int n = 0;
    a[n++] = jh_env_jogo();
    a[n++] = jh_local(self);
    CPU *c = cpu_atual();
    uint32_t r = jogo_chama_v(c, 0x02b32cccu, n, a); (void)r;
    jh_solta_locais(marca);
}

JNIEXPORT void JNICALL Java_com_nvidia_forge_InputSystem_onStop(JNIEnv *e, jclass self) {
    rt_garante();
    jh_define_env(e);
    int marca = jh_marca_locais();
    uint32_t a[24]; int n = 0;
    a[n++] = jh_env_jogo();
    a[n++] = jh_local(self);
    CPU *c = cpu_atual();
    uint32_t r = jogo_chama_v(c, 0x02b32b34u, n, a); (void)r;
    jh_solta_locais(marca);
}

JNIEXPORT void JNICALL Java_com_nvidia_forge_InputSystem_setScreenSize(JNIEnv *e, jclass self, jint p0, jint p1) {
    rt_garante();
    jh_define_env(e);
    int marca = jh_marca_locais();
    uint32_t a[24]; int n = 0;
    a[n++] = jh_env_jogo();
    a[n++] = jh_local(self);
    a[n++] = (uint32_t)(int32_t)p0;
    a[n++] = (uint32_t)(int32_t)p1;
    CPU *c = cpu_atual();
    uint32_t r = jogo_chama_v(c, 0x02b33e64u, n, a); (void)r;
    jh_solta_locais(marca);
}

JNIEXPORT jboolean JNICALL Java_com_nvidia_forge_MainActivity_checkStartupProgress(JNIEnv *e, jclass self) {
    rt_garante();
    jh_define_env(e);
    int marca = jh_marca_locais();
    uint32_t a[24]; int n = 0;
    a[n++] = jh_env_jogo();
    a[n++] = jh_local(self);
    CPU *c = cpu_atual();
    uint32_t r = jogo_chama_v(c, 0x02b38438u, n, a); (void)r;
    jh_solta_locais(marca); return (jboolean)r;
}

JNIEXPORT void JNICALL Java_com_nvidia_forge_MainActivity_forceExit(JNIEnv *e, jclass self) {
    rt_garante();
    jh_define_env(e);
    int marca = jh_marca_locais();
    uint32_t a[24]; int n = 0;
    a[n++] = jh_env_jogo();
    a[n++] = jh_local(self);
    CPU *c = cpu_atual();
    uint32_t r = jogo_chama_v(c, 0x02b31ee8u, n, a); (void)r;
    jh_solta_locais(marca);
}

JNIEXPORT void JNICALL Java_com_nvidia_forge_MainActivity_googlePlayHasBeenInitialized(JNIEnv *e, jclass self) {
    rt_garante();
    jh_define_env(e);
    int marca = jh_marca_locais();
    uint32_t a[24]; int n = 0;
    a[n++] = jh_env_jogo();
    a[n++] = jh_local(self);
    CPU *c = cpu_atual();
    uint32_t r = jogo_chama_v(c, 0x02b37f38u, n, a); (void)r;
    jh_solta_locais(marca);
}

JNIEXPORT void JNICALL Java_com_nvidia_forge_MainActivity_nativeGfxSetSplashTeardown(JNIEnv *e, jclass self) {
    rt_garante();
    jh_define_env(e);
    int marca = jh_marca_locais();
    uint32_t a[24]; int n = 0;
    a[n++] = jh_env_jogo();
    a[n++] = jh_local(self);
    CPU *c = cpu_atual();
    uint32_t r = jogo_chama_v(c, 0x02b36558u, n, a); (void)r;
    jh_solta_locais(marca);
}

JNIEXPORT void JNICALL Java_com_nvidia_forge_MainActivity_nativeGfxSetSurface(JNIEnv *e, jclass self, jobject p0) {
    rt_garante();
    jh_define_env(e);
    int marca = jh_marca_locais();
    uint32_t a[24]; int n = 0;
    a[n++] = jh_env_jogo();
    a[n++] = jh_local(self);
    a[n++] = jh_local(p0);
    CPU *c = cpu_atual();
    uint32_t r = jogo_chama_v(c, 0x02b31ff0u, n, a); (void)r;
    jh_solta_locais(marca);
}

JNIEXPORT void JNICALL Java_com_nvidia_forge_MainActivity_nativeMainCreate(JNIEnv *e, jclass self, jobject p0) {
    rt_garante();
    jh_define_env(e);
    int marca = jh_marca_locais();
    uint32_t a[24]; int n = 0;
    a[n++] = jh_env_jogo();
    a[n++] = jh_local(self);
    a[n++] = jh_local(p0);
    CPU *c = cpu_atual();
    uint32_t r = jogo_chama_v(c, 0x02b31f6cu, n, a); (void)r;
    jh_solta_locais(marca);
}

JNIEXPORT void JNICALL Java_com_nvidia_forge_MainActivity_nativeOnSndPause(JNIEnv *e, jclass self) {
    rt_garante();
    jh_define_env(e);
    int marca = jh_marca_locais();
    uint32_t a[24]; int n = 0;
    a[n++] = jh_env_jogo();
    a[n++] = jh_local(self);
    CPU *c = cpu_atual();
    uint32_t r = jogo_chama_v(c, 0x02b2f834u, n, a); (void)r;
    jh_solta_locais(marca);
}

JNIEXPORT void JNICALL Java_com_nvidia_forge_MainActivity_nativeOnSndResume(JNIEnv *e, jclass self) {
    rt_garante();
    jh_define_env(e);
    int marca = jh_marca_locais();
    uint32_t a[24]; int n = 0;
    a[n++] = jh_env_jogo();
    a[n++] = jh_local(self);
    CPU *c = cpu_atual();
    uint32_t r = jogo_chama_v(c, 0x02b2f830u, n, a); (void)r;
    jh_solta_locais(marca);
}

JNIEXPORT void JNICALL Java_com_nvidia_forge_MainActivity_nativeOnSndStart(JNIEnv *e, jclass self) {
    rt_garante();
    jh_define_env(e);
    int marca = jh_marca_locais();
    uint32_t a[24]; int n = 0;
    a[n++] = jh_env_jogo();
    a[n++] = jh_local(self);
    CPU *c = cpu_atual();
    uint32_t r = jogo_chama_v(c, 0x02b2f65cu, n, a); (void)r;
    jh_solta_locais(marca);
}

JNIEXPORT void JNICALL Java_com_nvidia_forge_MainActivity_nativeOnSndStop(JNIEnv *e, jclass self) {
    rt_garante();
    jh_define_env(e);
    int marca = jh_marca_locais();
    uint32_t a[24]; int n = 0;
    a[n++] = jh_env_jogo();
    a[n++] = jh_local(self);
    CPU *c = cpu_atual();
    uint32_t r = jogo_chama_v(c, 0x02b2f838u, n, a); (void)r;
    jh_solta_locais(marca);
}

JNIEXPORT void JNICALL Java_com_nvidia_forge_MainActivity_nvidiaInitGPGS(JNIEnv *e, jclass self, jobject p0, jobject p1, jobject p2) {
    rt_garante();
    jh_define_env(e);
    int marca = jh_marca_locais();
    uint32_t a[24]; int n = 0;
    a[n++] = jh_env_jogo();
    a[n++] = jh_local(self);
    a[n++] = jh_local(p0);
    a[n++] = jh_local(p1);
    a[n++] = jh_local(p2);
    CPU *c = cpu_atual();
    uint32_t r = jogo_chama_v(c, 0x02b356bcu, n, a); (void)r;
    jh_solta_locais(marca);
}

JNIEXPORT void JNICALL Java_com_nvidia_forge_MainActivity_setEngineVersion(JNIEnv *e, jclass self, jobject p0, jobject p1, jobject p2, jobject p3, jobject p4) {
    rt_garante();
    jh_define_env(e);
    int marca = jh_marca_locais();
    uint32_t a[24]; int n = 0;
    a[n++] = jh_env_jogo();
    a[n++] = jh_local(self);
    a[n++] = jh_local(p0);
    a[n++] = jh_local(p1);
    a[n++] = jh_local(p2);
    a[n++] = jh_local(p3);
    a[n++] = jh_local(p4);
    CPU *c = cpu_atual();
    uint32_t r = jogo_chama_v(c, 0x02b39730u, n, a); (void)r;
    jh_solta_locais(marca);
}

JNIEXPORT void JNICALL Java_com_nvidia_forge_MainActivity_setMainActivity(JNIEnv *e, jclass self, jobject p0) {
    rt_garante();
    jh_define_env(e);
    int marca = jh_marca_locais();
    uint32_t a[24]; int n = 0;
    a[n++] = jh_env_jogo();
    a[n++] = jh_local(self);
    a[n++] = jh_local(p0);
    CPU *c = cpu_atual();
    uint32_t r = jogo_chama_v(c, 0x02b31d94u, n, a); (void)r;
    jh_solta_locais(marca);
}

JNIEXPORT void JNICALL Java_com_nvidia_forge_MainActivity_setSystemVersion(JNIEnv *e, jclass self, jobject p0, jobject p1, jobject p2, jint p3) {
    rt_garante();
    jh_define_env(e);
    int marca = jh_marca_locais();
    uint32_t a[24]; int n = 0;
    a[n++] = jh_env_jogo();
    a[n++] = jh_local(self);
    a[n++] = jh_local(p0);
    a[n++] = jh_local(p1);
    a[n++] = jh_local(p2);
    a[n++] = (uint32_t)(int32_t)p3;
    CPU *c = cpu_atual();
    uint32_t r = jogo_chama_v(c, 0x02b393bcu, n, a); (void)r;
    jh_solta_locais(marca);
}

JNIEXPORT void JNICALL Java_com_nvidia_forge_MainActivity_stopSlesDevice(JNIEnv *e, jclass self) {
    rt_garante();
    jh_define_env(e);
    int marca = jh_marca_locais();
    uint32_t a[24]; int n = 0;
    a[n++] = jh_env_jogo();
    a[n++] = jh_local(self);
    CPU *c = cpu_atual();
    uint32_t r = jogo_chama_v(c, 0x02b2fa28u, n, a); (void)r;
    jh_solta_locais(marca);
}

JNIEXPORT void JNICALL Java_com_nvidia_forge_MainActivity_updateSlesDeviceData(JNIEnv *e, jclass self, jint p0, jint p1, jint p2, jint p3, jint p4) {
    rt_garante();
    jh_define_env(e);
    int marca = jh_marca_locais();
    uint32_t a[24]; int n = 0;
    a[n++] = jh_env_jogo();
    a[n++] = jh_local(self);
    a[n++] = (uint32_t)(int32_t)p0;
    a[n++] = (uint32_t)(int32_t)p1;
    a[n++] = (uint32_t)(int32_t)p2;
    a[n++] = (uint32_t)(int32_t)p3;
    a[n++] = (uint32_t)(int32_t)p4;
    CPU *c = cpu_atual();
    uint32_t r = jogo_chama_v(c, 0x02b2f9a0u, n, a); (void)r;
    jh_solta_locais(marca);
}

JNIEXPORT void JNICALL Java_com_nvidia_forge_PreferencesManager_setFirstRun(JNIEnv *e, jclass self, jboolean p0) {
    rt_garante();
    jh_define_env(e);
    int marca = jh_marca_locais();
    uint32_t a[24]; int n = 0;
    a[n++] = jh_env_jogo();
    a[n++] = jh_local(self);
    a[n++] = (uint32_t)(int32_t)p0;
    CPU *c = cpu_atual();
    uint32_t r = jogo_chama_v(c, 0x02b30cacu, n, a); (void)r;
    jh_solta_locais(marca);
}

JNIEXPORT void JNICALL Java_com_nvidia_forge_PreferencesManager_setPath(JNIEnv *e, jclass self, jobject p0, jint p1, jobject p2) {
    rt_garante();
    jh_define_env(e);
    int marca = jh_marca_locais();
    uint32_t a[24]; int n = 0;
    a[n++] = jh_env_jogo();
    a[n++] = jh_local(self);
    a[n++] = jh_local(p0);
    a[n++] = (uint32_t)(int32_t)p1;
    a[n++] = jh_local(p2);
    CPU *c = cpu_atual();
    uint32_t r = jogo_chama_v(c, 0x02b30a40u, n, a); (void)r;
    jh_solta_locais(marca);
}

JNIEXPORT void JNICALL Java_com_nvidia_forge_PreferencesManager_setupInternalPaths(JNIEnv *e, jclass self) {
    rt_garante();
    jh_define_env(e);
    int marca = jh_marca_locais();
    uint32_t a[24]; int n = 0;
    a[n++] = jh_env_jogo();
    a[n++] = jh_local(self);
    CPU *c = cpu_atual();
    uint32_t r = jogo_chama_v(c, 0x02b30cc0u, n, a); (void)r;
    jh_solta_locais(marca);
}

#endif