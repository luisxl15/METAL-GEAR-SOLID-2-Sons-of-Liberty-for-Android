/* So para o teste no Windows: funcoes POSIX que a CRT da Microsoft nao tem. */
#pragma once
#ifdef _WIN32
#include <string.h>
#include <ctype.h>
#define strcasecmp _stricmp
#define strncasecmp _strnicmp
static inline char *stpcpy(char *d, const char *s) { size_t n = strlen(s); memcpy(d, s, n + 1); return d + n; }
static inline char *strcasestr(const char *h, const char *n) {
    size_t k = strlen(n);
    for (; *h; h++) if (!_strnicmp(h, n, k)) return (char *)h;
    return k ? NULL : (char *)h;
}
#endif
#ifdef _WIN32
#include <io.h>
#include <direct.h>
#include <process.h>
#include <windows.h>
#define getpid _getpid
#define close _close
#define read _read
#define write _write
#define lseek _lseek
#define lseek64 _lseeki64
#define access _access
#define rmdir _rmdir
#define unlink _unlink
#define chdir _chdir
#define dup _dup
#define isatty _isatty
#define fsync _commit
#define ftruncate _chsize
#define open _open
static inline int mkdir_pc(const char *p, int m) { (void)m; return _mkdir(p); }
#define mkdir mkdir_pc
static inline int usleep(unsigned us) { Sleep(us / 1000); return 0; }
static inline int sched_yield(void) { SwitchToThread(); return 0; }
static inline int getpagesize(void) { return 4096; }
#endif
