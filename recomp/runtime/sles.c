/* OpenSL ES do jogo sobre o do Android.
 * Uma interface do jogo (SLxxxItf) e o endereco de uma celula de 8 bytes na
 * memoria do jogo: [0] = endereco da vtable (pontes), [4] = handle do objeto
 * real.  Os IIDs do jogo (SL_IID_*) apontam para copias dos 16 bytes reais. */
#include "runtime.h"
#include <string.h>
#ifdef _WIN32
void sles_inicia_iids(uint32_t a, uint32_t b, uint32_t c, uint32_t d) { (void)a; (void)b; (void)c; (void)d; }
#else
#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>

/* ---- handles de interfaces reais ----------------------------------------- */
#define MAX_ITF 512
static const void *itfs[MAX_ITF];
static uint32_t celulas[MAX_ITF];
static Trava trava_sl;

static uint32_t celula_de(const void *real, uint32_t vtab) {
    trava(&trava_sl);
    for (uint32_t k = 1; k < MAX_ITF; k++) if (itfs[k] == real && celulas[k]) { destrava(&trava_sl); return celulas[k]; }
    for (uint32_t k = 1; k < MAX_ITF; k++) if (!itfs[k]) {
        itfs[k] = real;
        uint32_t cel = heap_calloc(1, 8);
        memcpy(g_mem + cel, &vtab, 4);
        memcpy(g_mem + cel + 4, &k, 4);
        celulas[k] = cel;
        destrava(&trava_sl);
        return cel;
    }
    destrava(&trava_sl);
    rt_fatal("OpenSL: interfaces esgotadas");
}
static const void *real_de(uint32_t cel) {
    if (!cel) return NULL;
    uint32_t k; memcpy(&k, g_mem + cel + 4, 4);
    return k < MAX_ITF ? itfs[k] : NULL;
}
static void esquece(uint32_t cel) {
    uint32_t k; memcpy(&k, g_mem + cel + 4, 4);
    if (k < MAX_ITF) { itfs[k] = NULL; celulas[k] = 0; }
    heap_free(cel);
}

/* ---- IIDs ---------------------------------------------------------------- */
static uint32_t iid_engine, iid_bq, iid_play, iid_vol, iid_abq;
static uint32_t iid_copia(SLInterfaceID real) {
    uint32_t g = heap_malloc(16);
    memcpy(g_mem + g, real, 16);
    return g;
}
void sles_inicia_iids(uint32_t engine, uint32_t bq, uint32_t play, uint32_t vol) {
    trava_inicia(&trava_sl);
    iid_engine = iid_copia(SL_IID_ENGINE); iid_bq = iid_copia(SL_IID_BUFFERQUEUE);
    iid_play = iid_copia(SL_IID_PLAY); iid_vol = iid_copia(SL_IID_VOLUME);
    iid_abq = iid_copia(SL_IID_ANDROIDSIMPLEBUFFERQUEUE);
    if (engine) memcpy(g_mem + engine, &iid_engine, 4);
    if (bq) memcpy(g_mem + bq, &iid_bq, 4);
    if (play) memcpy(g_mem + play, &iid_play, 4);
    if (vol) memcpy(g_mem + vol, &iid_vol, 4);
}
static SLInterfaceID iid_real(uint32_t g) {
    static const SLInterfaceID *tab[] = { &SL_IID_ENGINE, &SL_IID_BUFFERQUEUE, &SL_IID_PLAY, &SL_IID_VOLUME,
                                          &SL_IID_ANDROIDSIMPLEBUFFERQUEUE, &SL_IID_OBJECT, &SL_IID_ENVIRONMENTALREVERB,
                                          &SL_IID_EFFECTSEND, &SL_IID_SEEK, &SL_IID_MUTESOLO, &SL_IID_PLAYBACKRATE };
    for (size_t k = 0; k < sizeof tab / sizeof tab[0]; k++) if (!memcmp(g_mem + g, *tab[k], 16)) return *tab[k];
    rt_log("OpenSL: IID desconhecido");
    return NULL;
}

/* ---- vtables do jogo ------------------------------------------------------ */
static uint32_t vt_obj, vt_eng, vt_play, vt_vol, vt_bq;
static uint32_t vtab(Ponte *fs, int n, const char *nome) {
    uint32_t v = heap_calloc((uint32_t)n, 4);
    for (int k = 0; k < n; k++) { uint32_t p = fs[k] ? ponte_nova(fs[k], nome) : 0; memcpy(g_mem + v + 4 * k, &p, 4); }
    return v;
}
static void sl_nao(CPU *c) { rt_log("OpenSL: funcao nao suportada (lr=%08x)", c->r[14]); ret32(c, SL_RESULT_FEATURE_UNSUPPORTED); }

/* SLObjectItf */
#define OBJ(cel) ((SLObjectItf)real_de(cel))
static void o_Realize(CPU *c) { SLObjectItf o = OBJ(c->r[0]); ret32(c, (*o)->Realize(o, (SLboolean)c->r[1])); }
static void o_Resume(CPU *c) { SLObjectItf o = OBJ(c->r[0]); ret32(c, (*o)->Resume(o, (SLboolean)c->r[1])); }
static void o_GetState(CPU *c) { SLObjectItf o = OBJ(c->r[0]); SLuint32 s = 0; SLresult r = (*o)->GetState(o, &s); memcpy(g_mem + c->r[1], &s, 4); ret32(c, r); }
static void o_GetInterface(CPU *c) {
    SLObjectItf o = OBJ(c->r[0]);
    SLInterfaceID id = iid_real(c->r[1]);
    void *itf = NULL;
    SLresult r = id ? (*o)->GetInterface(o, id, &itf) : SL_RESULT_FEATURE_UNSUPPORTED;
    uint32_t cel = 0;
    if (r == SL_RESULT_SUCCESS) {
        uint32_t vt = id == SL_IID_ENGINE ? vt_eng : id == SL_IID_PLAY ? vt_play : id == SL_IID_VOLUME ? vt_vol :
                      (id == SL_IID_BUFFERQUEUE || id == SL_IID_ANDROIDSIMPLEBUFFERQUEUE) ? vt_bq : 0;
        if (!vt) { rt_log("OpenSL: interface sem proxy"); r = SL_RESULT_FEATURE_UNSUPPORTED; }
        else cel = celula_de(itf, vt);
    }
    memcpy(g_mem + c->r[2], &cel, 4);
    ret32(c, r);
}
static void o_Destroy(CPU *c) { SLObjectItf o = OBJ(c->r[0]); (*o)->Destroy(o); esquece(c->r[0]); }
static void o_AbortAsync(CPU *c) { SLObjectItf o = OBJ(c->r[0]); (*o)->AbortAsyncOperation(o); }

/* SLEngineItf: le as estruturas de fonte/destino do jogo */
typedef struct { SLDataSource src; SLDataSink snk; SLDataLocator_AndroidSimpleBufferQueue lbq; SLDataFormat_PCM pcm;
                 SLDataLocator_OutputMix lmix; } Dados;
static void le_fonte(uint32_t g, SLDataSource *s, Dados *d) {
    uint32_t loc, fmt; memcpy(&loc, g_mem + g, 4); memcpy(&fmt, g_mem + g + 4, 4);
    uint32_t tipo; memcpy(&tipo, g_mem + loc, 4);
    memcpy(&d->lbq, g_mem + loc, sizeof d->lbq);
    if (tipo == SL_DATALOCATOR_BUFFERQUEUE) d->lbq.locatorType = SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE;
    memcpy(&d->pcm, g_mem + fmt, sizeof d->pcm);
    s->pLocator = &d->lbq; s->pFormat = &d->pcm;
}
static void le_destino(uint32_t g, SLDataSink *s, Dados *d) {
    uint32_t loc; memcpy(&loc, g_mem + g, 4);
    uint32_t tipo, mix; memcpy(&tipo, g_mem + loc, 4); memcpy(&mix, g_mem + loc + 4, 4);
    d->lmix.locatorType = tipo; d->lmix.outputMix = OBJ(mix);
    s->pLocator = &d->lmix; s->pFormat = NULL;
}
static int le_iids(uint32_t n, uint32_t ids, uint32_t req, SLInterfaceID *out, SLboolean *oreq) {
    int k = 0;
    for (uint32_t i = 0; i < n && k < 8; i++) {
        uint32_t g; memcpy(&g, g_mem + ids + 4 * i, 4);
        SLInterfaceID id = iid_real(g);
        if (!id) continue;
        if (id == SL_IID_BUFFERQUEUE) id = SL_IID_ANDROIDSIMPLEBUFFERQUEUE;
        out[k] = id;
        uint32_t r = 1; if (req) memcpy(&r, g_mem + req + 4 * i, 4);
        oreq[k] = (SLboolean)r;
        k++;
    }
    return k;
}
#define ENG(cel) ((SLEngineItf)real_de(cel))
static void e_CreateOutputMix(CPU *c) {
    Args a = args_de(c); SLEngineItf e = ENG(arg32(&a)); uint32_t pmix = arg32(&a), n = arg32(&a), ids = arg32(&a), req = arg32(&a);
    SLInterfaceID iv[8]; SLboolean rv[8]; int k = le_iids(n, ids, req, iv, rv);
    SLObjectItf mix = NULL;
    SLresult r = (*e)->CreateOutputMix(e, &mix, (SLuint32)k, iv, rv);
    uint32_t cel = r == SL_RESULT_SUCCESS ? celula_de(mix, vt_obj) : 0;
    memcpy(g_mem + pmix, &cel, 4);
    ret32(c, r);
}
static void e_CreateAudioPlayer(CPU *c) {
    Args a = args_de(c);
    SLEngineItf e = ENG(arg32(&a)); uint32_t pp = arg32(&a), src = arg32(&a), snk = arg32(&a);
    uint32_t n = arg32(&a), ids = arg32(&a), req = arg32(&a);
    Dados d; SLDataSource s; SLDataSink k_;
    le_fonte(src, &s, &d); le_destino(snk, &k_, &d);
    SLInterfaceID iv[8]; SLboolean rv[8]; int k = le_iids(n, ids, req, iv, rv);
    SLObjectItf p = NULL;
    SLresult r = (*e)->CreateAudioPlayer(e, &p, &s, &k_, (SLuint32)k, iv, rv);
    if (r != SL_RESULT_SUCCESS) rt_log("OpenSL CreateAudioPlayer falhou: %u (%u Hz, %u canais, %u bits)", r, d.pcm.samplesPerSec / 1000, d.pcm.numChannels, d.pcm.bitsPerSample);
    uint32_t cel = r == SL_RESULT_SUCCESS ? celula_de(p, vt_obj) : 0;
    memcpy(g_mem + pp, &cel, 4);
    ret32(c, r);
}

/* SLPlayItf */
#define PLAY(cel) ((SLPlayItf)real_de(cel))
static void p_SetPlayState(CPU *c) { SLPlayItf p = PLAY(c->r[0]); ret32(c, (*p)->SetPlayState(p, c->r[1])); }
static void p_GetPlayState(CPU *c) { SLPlayItf p = PLAY(c->r[0]); SLuint32 s = 0; SLresult r = (*p)->GetPlayState(p, &s); memcpy(g_mem + c->r[1], &s, 4); ret32(c, r); }
static void p_GetPosition(CPU *c) { SLPlayItf p = PLAY(c->r[0]); SLmillisecond s = 0; SLresult r = (*p)->GetPosition(p, &s); memcpy(g_mem + c->r[1], &s, 4); ret32(c, r); }

/* SLVolumeItf */
#define VOL(cel) ((SLVolumeItf)real_de(cel))
static void v_SetVolumeLevel(CPU *c) { SLVolumeItf v = VOL(c->r[0]); ret32(c, (*v)->SetVolumeLevel(v, (SLmillibel)(int16_t)c->r[1])); }
static void v_GetVolumeLevel(CPU *c) { SLVolumeItf v = VOL(c->r[0]); SLmillibel m = 0; SLresult r = (*v)->GetVolumeLevel(v, &m); memcpy(g_mem + c->r[1], &m, 2); ret32(c, r); }
static void v_GetMaxVolumeLevel(CPU *c) { SLVolumeItf v = VOL(c->r[0]); SLmillibel m = 0; SLresult r = (*v)->GetMaxVolumeLevel(v, &m); memcpy(g_mem + c->r[1], &m, 2); ret32(c, r); }
static void v_SetMute(CPU *c) { SLVolumeItf v = VOL(c->r[0]); ret32(c, (*v)->SetMute(v, (SLboolean)c->r[1])); }

/* SLBufferQueueItf (atendido pela fila simples do Android, mesma vtable) */
#define BQ(cel) ((SLAndroidSimpleBufferQueueItf)real_de(cel))
typedef struct { uint32_t fn, cel, ctx; } Retorno;
static Retorno retornos[64];
static void bq_ponte(SLAndroidSimpleBufferQueueItf bq, void *ctx) {
    (void)bq;
    Retorno *r = ctx;
    jogo_chama(r->fn, 2, r->cel, r->ctx);
}
static void b_Enqueue(CPU *c) { SLAndroidSimpleBufferQueueItf b = BQ(c->r[0]); ret32(c, (*b)->Enqueue(b, G2H(c->r[1]), c->r[2])); }
static void b_Clear(CPU *c) { SLAndroidSimpleBufferQueueItf b = BQ(c->r[0]); ret32(c, (*b)->Clear(b)); }
static void b_GetState(CPU *c) {
    SLAndroidSimpleBufferQueueItf b = BQ(c->r[0]);
    SLAndroidSimpleBufferQueueState s; SLresult r = (*b)->GetState(b, &s);
    memcpy(g_mem + c->r[1], &s, 8);
    ret32(c, r);
}
static void b_RegisterCallback(CPU *c) {
    SLAndroidSimpleBufferQueueItf b = BQ(c->r[0]);
    Retorno *r = NULL;
    for (int k = 0; k < 64; k++) if (!retornos[k].cel || retornos[k].cel == c->r[0]) { r = &retornos[k]; break; }
    if (!r) { ret32(c, SL_RESULT_MEMORY_FAILURE); return; }
    r->fn = c->r[1]; r->cel = c->r[0]; r->ctx = c->r[2];
    ret32(c, (*b)->RegisterCallback(b, c->r[1] ? bq_ponte : NULL, r));
}

/* ---- slCreateEngine ------------------------------------------------------- */
static void monta_vtabs(void) {
    if (vt_obj) return;
    Ponte o[10] = { o_Realize, o_Resume, o_GetState, o_GetInterface, sl_nao, o_AbortAsync, o_Destroy, sl_nao, sl_nao, sl_nao };
    vt_obj = vtab(o, 10, "SLObject");
    Ponte e[15] = { sl_nao, sl_nao, e_CreateAudioPlayer, sl_nao, sl_nao, sl_nao, sl_nao, e_CreateOutputMix, sl_nao, sl_nao, sl_nao, sl_nao, sl_nao, sl_nao, sl_nao };
    vt_eng = vtab(e, 15, "SLEngine");
    Ponte p[12] = { p_SetPlayState, p_GetPlayState, sl_nao, p_GetPosition, sl_nao, sl_nao, sl_nao, sl_nao, sl_nao, sl_nao, sl_nao, sl_nao };
    vt_play = vtab(p, 12, "SLPlay");
    Ponte v[9] = { v_SetVolumeLevel, v_GetVolumeLevel, v_GetMaxVolumeLevel, v_SetMute, sl_nao, sl_nao, sl_nao, sl_nao, sl_nao };
    vt_vol = vtab(v, 9, "SLVolume");
    Ponte b[4] = { b_Enqueue, b_Clear, b_GetState, b_RegisterCallback };
    vt_bq = vtab(b, 4, "SLBufferQueue");
}
void I_slCreateEngine(CPU *c) { RT_PRIMEIRA("slCreateEngine");
    monta_vtabs();
    Args a = args_de(c);
    uint32_t pe = arg32(&a); arg32(&a); arg32(&a); uint32_t n = arg32(&a), ids = arg32(&a), req = arg32(&a);
    SLInterfaceID iv[8]; SLboolean rv[8]; int k = le_iids(n, ids, req, iv, rv);
    SLObjectItf eng = NULL;
    SLEngineOption op[] = { { SL_ENGINEOPTION_THREADSAFE, SL_BOOLEAN_TRUE } };
    SLresult r = slCreateEngine(&eng, 1, op, (SLuint32)k, iv, rv);
    uint32_t cel = r == SL_RESULT_SUCCESS ? celula_de(eng, vt_obj) : 0;
    memcpy(g_mem + pe, &cel, 4);
    rt_log("OpenSL: motor criado (%u)", r);
    ret32(c, r);
}
#endif
