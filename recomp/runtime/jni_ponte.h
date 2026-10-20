#pragma once
#include "runtime.h"
#ifndef _WIN32
#include <jni.h>
extern JavaVM *g_vm;
JNIEnv *jh_env(void);
void jh_define_env(JNIEnv *e);
void jh_inicia(JavaVM *vm, JNIEnv *e, jobject contexto_ou_classe);
int jh_args(const char *sig, int modo, Args *a, uint32_t ptr, jvalue *v);
#endif
void *jh_obj(uint32_t h);
uint32_t jh_local(void *o);
uint32_t jh_global(void *o);
void jh_solta(uint32_t h);
int jh_marca_locais(void);
void jh_solta_locais(int marca);
uint32_t jh_id_novo(void *id, const char *sig, int campo);
void *jh_id(uint32_t h, const char **sig);
uint32_t jh_env_jogo(void);
uint32_t jh_vm_jogo(void);
