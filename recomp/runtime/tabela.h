/* Tabelas geradas pelo recompilador (saida/tabela.c). */
#pragma once
#include "cpu.h"

typedef struct { uint32_t ad; FuncJogo fn; } EntradaDespacho;
typedef struct { const char *nome; uint32_t ad; } Importacao;
typedef struct { const char *nome; uint32_t base, tam, init_array, n_init; } ImagemLib;

extern const EntradaDespacho g_despacho[];
extern const uint32_t g_n_despacho;
extern const Importacao g_importacoes[];
extern const uint32_t g_n_importacoes;
extern const Importacao g_dados_importados[];
extern const uint32_t g_n_dados_importados;
extern const ImagemLib g_libs[2];

#define DADOS_BASE   0x00f00000u
#define GNU_BASE     0x01000000u
#define JOGO_BASE    0x02000000u
#define HEAP_INI     0x04000000u
#define HEAP_FIM     0xef000000u
#define PONTES_BASE  0xf0000000u   /* pontes criadas em execucao (GL, JNI, SL) */
#define IMPORT_BASE  0xfff00000u
