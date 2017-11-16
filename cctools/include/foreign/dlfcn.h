#ifndef __CCTOOLS_PORT_DLFCN_H__
#define __CCTOOLS_PORT_DLFCN_H__
#if defined(__CYGWIN__)
#include_next <dlfcn.h>
#include <stdio.h> /* stderr */
typedef struct dl_info {
    const char  *dli_fname;
    void        *dli_fbase;
    const char  *dli_sname;
    void        *dli_saddr;
} Dl_info;

static inline int dladdr(void *addr, Dl_info *info)
{
    fprintf(stderr, "dladdr() not implemented\n");
    return 0;
}

#elif (defined(_WIN32) || defined(__WIN32__))

#define RTLD_LAZY     0x0001
#define RTLD_NOW      0x0002
#define RTLD_GLOBAL   0x0100
#define RTLD_LOCAL    0x0000
#define RTLD_NOSHARE  0x1000
#define RTLD_EXE      0x2000
#define RTLD_SCRIPT   0x4000
#define RTLD_DEFAULT ((void *) 0)

#include <stdio.h> /* stderr */
typedef struct dl_info {
    const char  *dli_fname;
    void        *dli_fbase;
    const char  *dli_sname;
    void        *dli_saddr;
} Dl_info;

static inline int dladdr(void *addr, Dl_info *info)
{
    fprintf(stderr, "dladdr() not implemented\n");
    return 0;
}

static inline void *dlopen(const char *filename, int flag) {
    fprintf(stderr, "dlopen() not implemented\n");
    return 0;
}

static inline char *dlerror(void) {
    fprintf(stderr, "dlerror() not implemented\n");
    return 0;
}

static inline void *dlsym(void *handle, const char *symbol) {
    fprintf(stderr, "dlsym() not implemented\n");
    return 0;
}

static inline int dlclose(void *handle) {
    fprintf(stderr, "dlclose() not implemented\n");
    return -1;
}

#else

#include_next <dlfcn.h>

#endif

#endif /* __CCTOOLS_PORT_DLFCN_H__ */
