/* libjava_util.so do SHIELD reescrita em ARM64 (o original e ARM32):
 * PreferencesManager.setenv / getprop, usados pelo Java antes de carregar o jogo. */
#include <jni.h>
#include <stdlib.h>
#include <sys/system_properties.h>

JNIEXPORT void JNICALL Java_com_nvidia_forge_PreferencesManager_setenv(JNIEnv *e, jclass k, jstring nome, jstring valor, jboolean sobrescreve) {
    (void)k;
    const char *n = (*e)->GetStringUTFChars(e, nome, NULL);
    const char *v = (*e)->GetStringUTFChars(e, valor, NULL);
    setenv(n, v, sobrescreve);
    (*e)->ReleaseStringUTFChars(e, nome, n);
    (*e)->ReleaseStringUTFChars(e, valor, v);
}

JNIEXPORT jstring JNICALL Java_com_nvidia_forge_PreferencesManager_getprop(JNIEnv *e, jclass k, jstring nome) {
    (void)k;
    const char *n = (*e)->GetStringUTFChars(e, nome, NULL);
    char v[PROP_VALUE_MAX] = {0};
    __system_property_get(n, v);
    (*e)->ReleaseStringUTFChars(e, nome, n);
    return (*e)->NewStringUTF(e, v);
}
