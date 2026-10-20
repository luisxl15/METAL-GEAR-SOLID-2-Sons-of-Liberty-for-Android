#pragma once
#include "runtime.h"
#ifndef _WIN32
#include <EGL/egl.h>
#include <GLES3/gl32.h>
void *gl_proc(const char *nome);           /* funcao real do driver */
GLsync gl_sync(uint32_t h);                /* handle do jogo -> GLsync */
void *egl_obj(uint32_t h);                 /* handle do jogo -> objeto EGL/ANativeWindow */
uint32_t egl_handle(void *p);              /* objeto -> handle (cria se preciso) */
uint32_t egl_ponte_por_nome(const char *nome);
#endif
