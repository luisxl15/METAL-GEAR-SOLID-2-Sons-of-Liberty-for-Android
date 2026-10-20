/* GERADO por pontes.py */
#include "runtime.h"
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <ctype.h>
#include <wctype.h>
#include <wchar.h>
#include <fcntl.h>
#include "compat_pc.h"
const char *rt_caminho(const char *p, char *buf, size_t n);   /* caminho.c */
#include <sys/stat.h>
#ifndef _WIN32
#include <unistd.h>
#include <sched.h>
#include <poll.h>
#endif

void I_acos(CPU *c) { RT_PRIMEIRA("acos");
    Args a = args_de(c); (void)a;
    double a0 = argd(&a);
    retd(c, acos(a0));
}

void I_asin(CPU *c) { RT_PRIMEIRA("asin");
    Args a = args_de(c); (void)a;
    double a0 = argd(&a);
    retd(c, asin(a0));
}

void I_atan(CPU *c) { RT_PRIMEIRA("atan");
    Args a = args_de(c); (void)a;
    double a0 = argd(&a);
    retd(c, atan(a0));
}

void I_atan2(CPU *c) { RT_PRIMEIRA("atan2");
    Args a = args_de(c); (void)a;
    double a0 = argd(&a);
    double a1 = argd(&a);
    retd(c, atan2(a0, a1));
}

void I_cbrt(CPU *c) { RT_PRIMEIRA("cbrt");
    Args a = args_de(c); (void)a;
    double a0 = argd(&a);
    retd(c, cbrt(a0));
}

void I_ceil(CPU *c) { RT_PRIMEIRA("ceil");
    Args a = args_de(c); (void)a;
    double a0 = argd(&a);
    retd(c, ceil(a0));
}

void I_cos(CPU *c) { RT_PRIMEIRA("cos");
    Args a = args_de(c); (void)a;
    double a0 = argd(&a);
    retd(c, cos(a0));
}

void I_cosh(CPU *c) { RT_PRIMEIRA("cosh");
    Args a = args_de(c); (void)a;
    double a0 = argd(&a);
    retd(c, cosh(a0));
}

void I_exp(CPU *c) { RT_PRIMEIRA("exp");
    Args a = args_de(c); (void)a;
    double a0 = argd(&a);
    retd(c, exp(a0));
}

void I_floor(CPU *c) { RT_PRIMEIRA("floor");
    Args a = args_de(c); (void)a;
    double a0 = argd(&a);
    retd(c, floor(a0));
}

void I_fmod(CPU *c) { RT_PRIMEIRA("fmod");
    Args a = args_de(c); (void)a;
    double a0 = argd(&a);
    double a1 = argd(&a);
    retd(c, fmod(a0, a1));
}

void I_log(CPU *c) { RT_PRIMEIRA("log");
    Args a = args_de(c); (void)a;
    double a0 = argd(&a);
    retd(c, log(a0));
}

void I_log10(CPU *c) { RT_PRIMEIRA("log10");
    Args a = args_de(c); (void)a;
    double a0 = argd(&a);
    retd(c, log10(a0));
}

void I_pow(CPU *c) { RT_PRIMEIRA("pow");
    Args a = args_de(c); (void)a;
    double a0 = argd(&a);
    double a1 = argd(&a);
    retd(c, pow(a0, a1));
}

void I_sin(CPU *c) { RT_PRIMEIRA("sin");
    Args a = args_de(c); (void)a;
    double a0 = argd(&a);
    retd(c, sin(a0));
}

void I_sinh(CPU *c) { RT_PRIMEIRA("sinh");
    Args a = args_de(c); (void)a;
    double a0 = argd(&a);
    retd(c, sinh(a0));
}

void I_sqrt(CPU *c) { RT_PRIMEIRA("sqrt");
    Args a = args_de(c); (void)a;
    double a0 = argd(&a);
    retd(c, sqrt(a0));
}

void I_tan(CPU *c) { RT_PRIMEIRA("tan");
    Args a = args_de(c); (void)a;
    double a0 = argd(&a);
    retd(c, tan(a0));
}

void I_tanh(CPU *c) { RT_PRIMEIRA("tanh");
    Args a = args_de(c); (void)a;
    double a0 = argd(&a);
    retd(c, tanh(a0));
}

void I_acosf(CPU *c) { RT_PRIMEIRA("acosf");
    Args a = args_de(c); (void)a;
    float a0 = argf(&a);
    retf(c, acosf(a0));
}

void I_asinf(CPU *c) { RT_PRIMEIRA("asinf");
    Args a = args_de(c); (void)a;
    float a0 = argf(&a);
    retf(c, asinf(a0));
}

void I_atanf(CPU *c) { RT_PRIMEIRA("atanf");
    Args a = args_de(c); (void)a;
    float a0 = argf(&a);
    retf(c, atanf(a0));
}

void I_atan2f(CPU *c) { RT_PRIMEIRA("atan2f");
    Args a = args_de(c); (void)a;
    float a0 = argf(&a);
    float a1 = argf(&a);
    retf(c, atan2f(a0, a1));
}

void I_cbrtf(CPU *c) { RT_PRIMEIRA("cbrtf");
    Args a = args_de(c); (void)a;
    float a0 = argf(&a);
    retf(c, cbrtf(a0));
}

void I_ceilf(CPU *c) { RT_PRIMEIRA("ceilf");
    Args a = args_de(c); (void)a;
    float a0 = argf(&a);
    retf(c, ceilf(a0));
}

void I_cosf(CPU *c) { RT_PRIMEIRA("cosf");
    Args a = args_de(c); (void)a;
    float a0 = argf(&a);
    retf(c, cosf(a0));
}

void I_floorf(CPU *c) { RT_PRIMEIRA("floorf");
    Args a = args_de(c); (void)a;
    float a0 = argf(&a);
    retf(c, floorf(a0));
}

void I_fmodf(CPU *c) { RT_PRIMEIRA("fmodf");
    Args a = args_de(c); (void)a;
    float a0 = argf(&a);
    float a1 = argf(&a);
    retf(c, fmodf(a0, a1));
}

void I_logf(CPU *c) { RT_PRIMEIRA("logf");
    Args a = args_de(c); (void)a;
    float a0 = argf(&a);
    retf(c, logf(a0));
}

void I_powf(CPU *c) { RT_PRIMEIRA("powf");
    Args a = args_de(c); (void)a;
    float a0 = argf(&a);
    float a1 = argf(&a);
    retf(c, powf(a0, a1));
}

void I_sinf(CPU *c) { RT_PRIMEIRA("sinf");
    Args a = args_de(c); (void)a;
    float a0 = argf(&a);
    retf(c, sinf(a0));
}

void I_tanf(CPU *c) { RT_PRIMEIRA("tanf");
    Args a = args_de(c); (void)a;
    float a0 = argf(&a);
    retf(c, tanf(a0));
}

void I_abs(CPU *c) { RT_PRIMEIRA("abs");
    Args a = args_de(c); (void)a;
    int32_t a0 = (int32_t)arg32(&a);
    ret32(c, (uint32_t)(abs(a0)));
}

void I_isalnum(CPU *c) { RT_PRIMEIRA("isalnum");
    Args a = args_de(c); (void)a;
    int32_t a0 = (int32_t)arg32(&a);
    ret32(c, (uint32_t)(isalnum(a0)));
}

void I_isalpha(CPU *c) { RT_PRIMEIRA("isalpha");
    Args a = args_de(c); (void)a;
    int32_t a0 = (int32_t)arg32(&a);
    ret32(c, (uint32_t)(isalpha(a0)));
}

void I_iscntrl(CPU *c) { RT_PRIMEIRA("iscntrl");
    Args a = args_de(c); (void)a;
    int32_t a0 = (int32_t)arg32(&a);
    ret32(c, (uint32_t)(iscntrl(a0)));
}

void I_islower(CPU *c) { RT_PRIMEIRA("islower");
    Args a = args_de(c); (void)a;
    int32_t a0 = (int32_t)arg32(&a);
    ret32(c, (uint32_t)(islower(a0)));
}

void I_isprint(CPU *c) { RT_PRIMEIRA("isprint");
    Args a = args_de(c); (void)a;
    int32_t a0 = (int32_t)arg32(&a);
    ret32(c, (uint32_t)(isprint(a0)));
}

void I_ispunct(CPU *c) { RT_PRIMEIRA("ispunct");
    Args a = args_de(c); (void)a;
    int32_t a0 = (int32_t)arg32(&a);
    ret32(c, (uint32_t)(ispunct(a0)));
}

void I_isspace(CPU *c) { RT_PRIMEIRA("isspace");
    Args a = args_de(c); (void)a;
    int32_t a0 = (int32_t)arg32(&a);
    ret32(c, (uint32_t)(isspace(a0)));
}

void I_isupper(CPU *c) { RT_PRIMEIRA("isupper");
    Args a = args_de(c); (void)a;
    int32_t a0 = (int32_t)arg32(&a);
    ret32(c, (uint32_t)(isupper(a0)));
}

void I_isxdigit(CPU *c) { RT_PRIMEIRA("isxdigit");
    Args a = args_de(c); (void)a;
    int32_t a0 = (int32_t)arg32(&a);
    ret32(c, (uint32_t)(isxdigit(a0)));
}

void I_tolower(CPU *c) { RT_PRIMEIRA("tolower");
    Args a = args_de(c); (void)a;
    int32_t a0 = (int32_t)arg32(&a);
    ret32(c, (uint32_t)(tolower(a0)));
}

void I_toupper(CPU *c) { RT_PRIMEIRA("toupper");
    Args a = args_de(c); (void)a;
    int32_t a0 = (int32_t)arg32(&a);
    ret32(c, (uint32_t)(toupper(a0)));
}

void I_iswalpha(CPU *c) { RT_PRIMEIRA("iswalpha");
    Args a = args_de(c); (void)a;
    uint32_t a0 = arg32(&a);
    ret32(c, (uint32_t)(iswalpha(a0)));
}

void I_iswcntrl(CPU *c) { RT_PRIMEIRA("iswcntrl");
    Args a = args_de(c); (void)a;
    uint32_t a0 = arg32(&a);
    ret32(c, (uint32_t)(iswcntrl(a0)));
}

void I_iswdigit(CPU *c) { RT_PRIMEIRA("iswdigit");
    Args a = args_de(c); (void)a;
    uint32_t a0 = arg32(&a);
    ret32(c, (uint32_t)(iswdigit(a0)));
}

void I_iswlower(CPU *c) { RT_PRIMEIRA("iswlower");
    Args a = args_de(c); (void)a;
    uint32_t a0 = arg32(&a);
    ret32(c, (uint32_t)(iswlower(a0)));
}

void I_iswprint(CPU *c) { RT_PRIMEIRA("iswprint");
    Args a = args_de(c); (void)a;
    uint32_t a0 = arg32(&a);
    ret32(c, (uint32_t)(iswprint(a0)));
}

void I_iswpunct(CPU *c) { RT_PRIMEIRA("iswpunct");
    Args a = args_de(c); (void)a;
    uint32_t a0 = arg32(&a);
    ret32(c, (uint32_t)(iswpunct(a0)));
}

void I_iswspace(CPU *c) { RT_PRIMEIRA("iswspace");
    Args a = args_de(c); (void)a;
    uint32_t a0 = arg32(&a);
    ret32(c, (uint32_t)(iswspace(a0)));
}

void I_iswupper(CPU *c) { RT_PRIMEIRA("iswupper");
    Args a = args_de(c); (void)a;
    uint32_t a0 = arg32(&a);
    ret32(c, (uint32_t)(iswupper(a0)));
}

void I_iswxdigit(CPU *c) { RT_PRIMEIRA("iswxdigit");
    Args a = args_de(c); (void)a;
    uint32_t a0 = arg32(&a);
    ret32(c, (uint32_t)(iswxdigit(a0)));
}

void I_towlower(CPU *c) { RT_PRIMEIRA("towlower");
    Args a = args_de(c); (void)a;
    uint32_t a0 = arg32(&a);
    ret32(c, (uint32_t)(towlower(a0)));
}

void I_towupper(CPU *c) { RT_PRIMEIRA("towupper");
    Args a = args_de(c); (void)a;
    uint32_t a0 = arg32(&a);
    ret32(c, (uint32_t)(towupper(a0)));
}

void I_btowc(CPU *c) { RT_PRIMEIRA("btowc");
    Args a = args_de(c); (void)a;
    int32_t a0 = (int32_t)arg32(&a);
    ret32(c, (uint32_t)(btowc(a0)));
}

void I_wctob(CPU *c) { RT_PRIMEIRA("wctob");
    Args a = args_de(c); (void)a;
    uint32_t a0 = arg32(&a);
    ret32(c, (uint32_t)(wctob(a0)));
}

void I_wctype(CPU *c) { RT_PRIMEIRA("wctype");
    Args a = args_de(c); (void)a;
    void * a0 = G2H(arg32(&a));
    ret32(c, (uint32_t)(wctype(a0)));
}

void I_iswctype(CPU *c) { RT_PRIMEIRA("iswctype");
    Args a = args_de(c); (void)a;
    uint32_t a0 = arg32(&a);
    uint32_t a1 = arg32(&a);
    ret32(c, (uint32_t)(iswctype((wint_t)a0, (wctype_t)a1)));
}

void I_strlen(CPU *c) { RT_PRIMEIRA("strlen");
    Args a = args_de(c); (void)a;
    void * a0 = G2H(arg32(&a));
    ret32(c, (uint32_t)(strlen(a0)));
}

void I_strcmp(CPU *c) { RT_PRIMEIRA("strcmp");
    Args a = args_de(c); (void)a;
    void * a0 = G2H(arg32(&a));
    void * a1 = G2H(arg32(&a));
    ret32(c, (uint32_t)(strcmp(a0, a1)));
}

void I_strncmp(CPU *c) { RT_PRIMEIRA("strncmp");
    Args a = args_de(c); (void)a;
    void * a0 = G2H(arg32(&a));
    void * a1 = G2H(arg32(&a));
    size_t a2 = (size_t)arg32(&a);
    ret32(c, (uint32_t)(strncmp(a0, a1, a2)));
}

void I_strcasecmp(CPU *c) { RT_PRIMEIRA("strcasecmp");
    Args a = args_de(c); (void)a;
    void * a0 = G2H(arg32(&a));
    void * a1 = G2H(arg32(&a));
    ret32(c, (uint32_t)(strcasecmp(a0, a1)));
}

void I_strncasecmp(CPU *c) { RT_PRIMEIRA("strncasecmp");
    Args a = args_de(c); (void)a;
    void * a0 = G2H(arg32(&a));
    void * a1 = G2H(arg32(&a));
    size_t a2 = (size_t)arg32(&a);
    ret32(c, (uint32_t)(strncasecmp(a0, a1, a2)));
}

void I_strcpy(CPU *c) { RT_PRIMEIRA("strcpy");
    Args a = args_de(c); (void)a;
    void * a0 = G2H(arg32(&a));
    void * a1 = G2H(arg32(&a));
    ret32(c, H2G(strcpy(a0, a1)));
}

void I_strncpy(CPU *c) { RT_PRIMEIRA("strncpy");
    Args a = args_de(c); (void)a;
    void * a0 = G2H(arg32(&a));
    void * a1 = G2H(arg32(&a));
    size_t a2 = (size_t)arg32(&a);
    ret32(c, H2G(strncpy(a0, a1, a2)));
}

void I_strcat(CPU *c) { RT_PRIMEIRA("strcat");
    Args a = args_de(c); (void)a;
    void * a0 = G2H(arg32(&a));
    void * a1 = G2H(arg32(&a));
    ret32(c, H2G(strcat(a0, a1)));
}

void I_strncat(CPU *c) { RT_PRIMEIRA("strncat");
    Args a = args_de(c); (void)a;
    void * a0 = G2H(arg32(&a));
    void * a1 = G2H(arg32(&a));
    size_t a2 = (size_t)arg32(&a);
    ret32(c, H2G(strncat(a0, a1, a2)));
}

void I_stpcpy(CPU *c) { RT_PRIMEIRA("stpcpy");
    Args a = args_de(c); (void)a;
    void * a0 = G2H(arg32(&a));
    void * a1 = G2H(arg32(&a));
    ret32(c, H2G(stpcpy(a0, a1)));
}

void I_strchr(CPU *c) { RT_PRIMEIRA("strchr");
    Args a = args_de(c); (void)a;
    void * a0 = G2H(arg32(&a));
    int32_t a1 = (int32_t)arg32(&a);
    ret32(c, H2G(strchr(a0, a1)));
}

void I_strrchr(CPU *c) { RT_PRIMEIRA("strrchr");
    Args a = args_de(c); (void)a;
    void * a0 = G2H(arg32(&a));
    int32_t a1 = (int32_t)arg32(&a);
    ret32(c, H2G(strrchr(a0, a1)));
}

void I_strstr(CPU *c) { RT_PRIMEIRA("strstr");
    Args a = args_de(c); (void)a;
    void * a0 = G2H(arg32(&a));
    void * a1 = G2H(arg32(&a));
    ret32(c, H2G(strstr(a0, a1)));
}

void I_strcasestr(CPU *c) { RT_PRIMEIRA("strcasestr");
    Args a = args_de(c); (void)a;
    void * a0 = G2H(arg32(&a));
    void * a1 = G2H(arg32(&a));
    ret32(c, H2G(strcasestr(a0, a1)));
}

void I_strpbrk(CPU *c) { RT_PRIMEIRA("strpbrk");
    Args a = args_de(c); (void)a;
    void * a0 = G2H(arg32(&a));
    void * a1 = G2H(arg32(&a));
    ret32(c, H2G(strpbrk(a0, a1)));
}

void I_strcspn(CPU *c) { RT_PRIMEIRA("strcspn");
    Args a = args_de(c); (void)a;
    void * a0 = G2H(arg32(&a));
    void * a1 = G2H(arg32(&a));
    ret32(c, (uint32_t)(strcspn(a0, a1)));
}

void I_strcoll(CPU *c) { RT_PRIMEIRA("strcoll");
    Args a = args_de(c); (void)a;
    void * a0 = G2H(arg32(&a));
    void * a1 = G2H(arg32(&a));
    ret32(c, (uint32_t)(strcoll(a0, a1)));
}

void I_strxfrm(CPU *c) { RT_PRIMEIRA("strxfrm");
    Args a = args_de(c); (void)a;
    void * a0 = G2H(arg32(&a));
    void * a1 = G2H(arg32(&a));
    size_t a2 = (size_t)arg32(&a);
    ret32(c, (uint32_t)(strxfrm(a0, a1, a2)));
}

void I_strtok(CPU *c) { RT_PRIMEIRA("strtok");
    Args a = args_de(c); (void)a;
    void * a0 = G2H(arg32(&a));
    void * a1 = G2H(arg32(&a));
    ret32(c, H2G(strtok(a0, a1)));
}

void I_memcpy(CPU *c) { RT_PRIMEIRA("memcpy");
    Args a = args_de(c); (void)a;
    void * a0 = G2H(arg32(&a));
    void * a1 = G2H(arg32(&a));
    size_t a2 = (size_t)arg32(&a);
    ret32(c, H2G(memcpy(a0, a1, a2)));
}

void I_memmove(CPU *c) { RT_PRIMEIRA("memmove");
    Args a = args_de(c); (void)a;
    void * a0 = G2H(arg32(&a));
    void * a1 = G2H(arg32(&a));
    size_t a2 = (size_t)arg32(&a);
    ret32(c, H2G(memmove(a0, a1, a2)));
}

void I_memset(CPU *c) { RT_PRIMEIRA("memset");
    Args a = args_de(c); (void)a;
    void * a0 = G2H(arg32(&a));
    int32_t a1 = (int32_t)arg32(&a);
    size_t a2 = (size_t)arg32(&a);
    ret32(c, H2G(memset(a0, a1, a2)));
}

void I_memchr(CPU *c) { RT_PRIMEIRA("memchr");
    Args a = args_de(c); (void)a;
    void * a0 = G2H(arg32(&a));
    int32_t a1 = (int32_t)arg32(&a);
    size_t a2 = (size_t)arg32(&a);
    ret32(c, H2G(memchr(a0, a1, a2)));
}

void I_memcmp(CPU *c) { RT_PRIMEIRA("memcmp");
    Args a = args_de(c); (void)a;
    void * a0 = G2H(arg32(&a));
    void * a1 = G2H(arg32(&a));
    size_t a2 = (size_t)arg32(&a);
    ret32(c, (uint32_t)(memcmp(a0, a1, a2)));
}

void I_atoi(CPU *c) { RT_PRIMEIRA("atoi");
    Args a = args_de(c); (void)a;
    void * a0 = G2H(arg32(&a));
    ret32(c, (uint32_t)(atoi(a0)));
}

void I_atof(CPU *c) { RT_PRIMEIRA("atof");
    Args a = args_de(c); (void)a;
    void * a0 = G2H(arg32(&a));
    retd(c, atof(a0));
}

void I_wcslen(CPU *c) { RT_PRIMEIRA("wcslen");
    Args a = args_de(c); (void)a;
    void * a0 = G2H(arg32(&a));
    ret32(c, (uint32_t)(wcslen(a0)));
}

void I_wcscoll(CPU *c) { RT_PRIMEIRA("wcscoll");
    Args a = args_de(c); (void)a;
    void * a0 = G2H(arg32(&a));
    void * a1 = G2H(arg32(&a));
    ret32(c, (uint32_t)(wcscoll(a0, a1)));
}

void I_wcsxfrm(CPU *c) { RT_PRIMEIRA("wcsxfrm");
    Args a = args_de(c); (void)a;
    void * a0 = G2H(arg32(&a));
    void * a1 = G2H(arg32(&a));
    size_t a2 = (size_t)arg32(&a);
    ret32(c, (uint32_t)(wcsxfrm(a0, a1, a2)));
}

void I_wmemchr(CPU *c) { RT_PRIMEIRA("wmemchr");
    Args a = args_de(c); (void)a;
    void * a0 = G2H(arg32(&a));
    uint32_t a1 = arg32(&a);
    size_t a2 = (size_t)arg32(&a);
    ret32(c, H2G(wmemchr(a0, (wchar_t)a1, a2)));
}

void I_wmemcmp(CPU *c) { RT_PRIMEIRA("wmemcmp");
    Args a = args_de(c); (void)a;
    void * a0 = G2H(arg32(&a));
    void * a1 = G2H(arg32(&a));
    size_t a2 = (size_t)arg32(&a);
    ret32(c, (uint32_t)(wmemcmp(a0, a1, a2)));
}

void I_wmemcpy(CPU *c) { RT_PRIMEIRA("wmemcpy");
    Args a = args_de(c); (void)a;
    void * a0 = G2H(arg32(&a));
    void * a1 = G2H(arg32(&a));
    size_t a2 = (size_t)arg32(&a);
    ret32(c, H2G(wmemcpy(a0, a1, a2)));
}

void I_wmemmove(CPU *c) { RT_PRIMEIRA("wmemmove");
    Args a = args_de(c); (void)a;
    void * a0 = G2H(arg32(&a));
    void * a1 = G2H(arg32(&a));
    size_t a2 = (size_t)arg32(&a);
    ret32(c, H2G(wmemmove(a0, a1, a2)));
}

void I_wmemset(CPU *c) { RT_PRIMEIRA("wmemset");
    Args a = args_de(c); (void)a;
    void * a0 = G2H(arg32(&a));
    uint32_t a1 = arg32(&a);
    size_t a2 = (size_t)arg32(&a);
    ret32(c, H2G(wmemset(a0, (wchar_t)a1, a2)));
}

void I_rand(CPU *c) { RT_PRIMEIRA("rand");
    Args a = args_de(c); (void)a;
    ret32(c, (uint32_t)(rand()));
}

void I_srand(CPU *c) { RT_PRIMEIRA("srand");
    Args a = args_de(c); (void)a;
    uint32_t a0 = arg32(&a);
    srand(a0);
}

void I_close(CPU *c) { RT_PRIMEIRA("close");
    Args a = args_de(c); (void)a;
    int32_t a0 = (int32_t)arg32(&a);
    ret32(c, (uint32_t)(close(a0)));
}

void I_dup(CPU *c) { RT_PRIMEIRA("dup");
    Args a = args_de(c); (void)a;
    int32_t a0 = (int32_t)arg32(&a);
    ret32(c, (uint32_t)(dup(a0)));
}

void I_access(CPU *c) { RT_PRIMEIRA("access");
    Args a = args_de(c); (void)a;
    char _b0[1024]; const char * a0 = rt_caminho(G2H(arg32(&a)), _b0, sizeof _b0);
    int32_t a1 = (int32_t)arg32(&a);
    ret32(c, (uint32_t)(access(a0, a1)));
}

void I_mkdir(CPU *c) { RT_PRIMEIRA("mkdir");
    Args a = args_de(c); (void)a;
    char _b0[1024]; const char * a0 = rt_caminho(G2H(arg32(&a)), _b0, sizeof _b0);
    uint32_t a1 = arg32(&a);
    ret32(c, (uint32_t)(mkdir(a0, a1)));
}

void I_rmdir(CPU *c) { RT_PRIMEIRA("rmdir");
    Args a = args_de(c); (void)a;
    char _b0[1024]; const char * a0 = rt_caminho(G2H(arg32(&a)), _b0, sizeof _b0);
    ret32(c, (uint32_t)(rmdir(a0)));
}

void I_unlink(CPU *c) { RT_PRIMEIRA("unlink");
    Args a = args_de(c); (void)a;
    char _b0[1024]; const char * a0 = rt_caminho(G2H(arg32(&a)), _b0, sizeof _b0);
    ret32(c, (uint32_t)(unlink(a0)));
}

void I_remove(CPU *c) { RT_PRIMEIRA("remove");
    Args a = args_de(c); (void)a;
    char _b0[1024]; const char * a0 = rt_caminho(G2H(arg32(&a)), _b0, sizeof _b0);
    ret32(c, (uint32_t)(remove(a0)));
}

void I_rename(CPU *c) { RT_PRIMEIRA("rename");
    Args a = args_de(c); (void)a;
    char _b0[1024], _b1[1024];
    const char * a0 = rt_caminho(G2H(arg32(&a)), _b0, sizeof _b0);
    const char * a1 = rt_caminho(G2H(arg32(&a)), _b1, sizeof _b1);
    ret32(c, (uint32_t)(rename(a0, a1)));
}

void I_chdir(CPU *c) { RT_PRIMEIRA("chdir");
    Args a = args_de(c); (void)a;
    char _b0[1024]; const char * a0 = rt_caminho(G2H(arg32(&a)), _b0, sizeof _b0);
    ret32(c, (uint32_t)(chdir(a0)));
}

void I_fsync(CPU *c) { RT_PRIMEIRA("fsync");
    Args a = args_de(c); (void)a;
    int32_t a0 = (int32_t)arg32(&a);
    ret32(c, (uint32_t)(fsync(a0)));
}

void I_ftruncate(CPU *c) { RT_PRIMEIRA("ftruncate");
    Args a = args_de(c); (void)a;
    int32_t a0 = (int32_t)arg32(&a);
    int32_t a1 = (int32_t)arg32(&a);
    ret32(c, (uint32_t)(ftruncate(a0, a1)));
}

void I_getpid(CPU *c) { RT_PRIMEIRA("getpid");
    Args a = args_de(c); (void)a;
    ret32(c, (uint32_t)(getpid()));
}

#ifdef _WIN32
void I_kill(CPU *c) { RT_PRIMEIRA("kill"); (void)c; rt_fatal("kill no PC"); }
#else
void I_kill(CPU *c) { RT_PRIMEIRA("kill");
    Args a = args_de(c); (void)a;
    int32_t a0 = (int32_t)arg32(&a);
    int32_t a1 = (int32_t)arg32(&a);
    ret32(c, (uint32_t)(kill(a0, a1)));
}

#endif
void I_lseek(CPU *c) { RT_PRIMEIRA("lseek");
    Args a = args_de(c); (void)a;
    int32_t a0 = (int32_t)arg32(&a);
    int32_t a1 = (int32_t)arg32(&a);
    int32_t a2 = (int32_t)arg32(&a);
    ret32(c, (uint32_t)(lseek(a0, a1, a2)));
}

void I_lseek64(CPU *c) { RT_PRIMEIRA("lseek64");
    Args a = args_de(c); (void)a;
    int32_t a0 = (int32_t)arg32(&a);
    int64_t a1 = (int64_t)arg64(&a);
    int32_t a2 = (int32_t)arg32(&a);
    ret64(c, (uint64_t)(lseek64(a0, a1, a2)));
}

void I_raise(CPU *c) { RT_PRIMEIRA("raise");
    Args a = args_de(c); (void)a;
    int32_t a0 = (int32_t)arg32(&a);
    ret32(c, (uint32_t)(raise(a0)));
}

void I_sched_yield(CPU *c) { RT_PRIMEIRA("sched_yield");
    Args a = args_de(c); (void)a;
    ret32(c, (uint32_t)(sched_yield()));
}

void I_usleep(CPU *c) { RT_PRIMEIRA("usleep");
    Args a = args_de(c); (void)a;
    uint32_t a0 = arg32(&a);
    ret32(c, (uint32_t)(usleep(a0)));
}

void I_getpagesize(CPU *c) { RT_PRIMEIRA("getpagesize");
    Args a = args_de(c); (void)a;
    ret32(c, (uint32_t)(getpagesize()));
}

#ifdef _WIN32
void I_gethostname(CPU *c) { RT_PRIMEIRA("gethostname"); (void)c; rt_fatal("gethostname no PC"); }
#else
void I_gethostname(CPU *c) { RT_PRIMEIRA("gethostname");
    Args a = args_de(c); (void)a;
    void * a0 = G2H(arg32(&a));
    size_t a1 = (size_t)arg32(&a);
    ret32(c, (uint32_t)(gethostname(a0, a1)));
}

#endif
void I_open(CPU *c) { RT_PRIMEIRA("open");
    Args a = args_de(c); (void)a;
    char _b0[1024]; const char * a0 = rt_caminho(G2H(arg32(&a)), _b0, sizeof _b0);
    int32_t a1 = (int32_t)arg32(&a);
    uint32_t a2 = arg32(&a);
    int fd = open(a0, a1, (int)a2);
#ifdef MGS2_DEPURA
    { static int n; if (__atomic_fetch_add(&n, 1, __ATOMIC_RELAXED) < 80) rt_log("open(%s, %x) -> %d", (char *)a0, a1, fd); }
#endif
    ret32(c, (uint32_t)fd);
}

void I_read(CPU *c) { RT_PRIMEIRA("read");
    Args a = args_de(c); (void)a;
    int32_t a0 = (int32_t)arg32(&a);
    void * a1 = G2H(arg32(&a));
    size_t a2 = (size_t)arg32(&a);
    ret32(c, (uint32_t)(read(a0, a1, a2)));
}

void I_write(CPU *c) { RT_PRIMEIRA("write");
    Args a = args_de(c); (void)a;
    int32_t a0 = (int32_t)arg32(&a);
    void * a1 = G2H(arg32(&a));
    size_t a2 = (size_t)arg32(&a);
    ret32(c, (uint32_t)(write(a0, a1, a2)));
}

#ifdef _WIN32
void I_pread(CPU *c) { RT_PRIMEIRA("pread"); (void)c; rt_fatal("pread no PC"); }
#else
void I_pread(CPU *c) { RT_PRIMEIRA("pread");
    Args a = args_de(c); (void)a;
    int32_t a0 = (int32_t)arg32(&a);
    void * a1 = G2H(arg32(&a));
    size_t a2 = (size_t)arg32(&a);
    int32_t a3 = (int32_t)arg32(&a);
    ret32(c, (uint32_t)(pread(a0, a1, a2, a3)));
}

#endif
#ifdef _WIN32
void I_pwrite(CPU *c) { RT_PRIMEIRA("pwrite"); (void)c; rt_fatal("pwrite no PC"); }
#else
void I_pwrite(CPU *c) { RT_PRIMEIRA("pwrite");
    Args a = args_de(c); (void)a;
    int32_t a0 = (int32_t)arg32(&a);
    void * a1 = G2H(arg32(&a));
    size_t a2 = (size_t)arg32(&a);
    int32_t a3 = (int32_t)arg32(&a);
    ret32(c, (uint32_t)(pwrite(a0, a1, a2, a3)));
}

#endif
#ifdef _WIN32
void I_poll(CPU *c) { RT_PRIMEIRA("poll"); (void)c; rt_fatal("poll no PC"); }
#else
void I_poll(CPU *c) { RT_PRIMEIRA("poll");
    Args a = args_de(c); (void)a;
    void * a0 = G2H(arg32(&a));
    uint32_t a1 = arg32(&a);
    int32_t a2 = (int32_t)arg32(&a);
    ret32(c, (uint32_t)(poll((struct pollfd *)a0, (nfds_t)a1, a2)));
}

#endif
void I_isatty(CPU *c) { RT_PRIMEIRA("isatty");
    Args a = args_de(c); (void)a;
    int32_t a0 = (int32_t)arg32(&a);
    ret32(c, (uint32_t)(isatty(a0)));
}
