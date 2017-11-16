#ifndef __CCTOOLS_PORT_PWD_H__
#define __CCTOOLS_PORT_PWD_H__

#if !((defined(_WIN32) || defined(__WIN32__)) && !defined(__CYGWIN__))
#include_next <pwd.h>
#else 
#include <stdio.h> /* stderr */

struct passwd {
	char	*pw_dir;		/* home directory */
};

static inline struct passwd *getpwnam(const char * name) {
    fprintf(stderr, "getpwnam() not implemented\n");
    return NULL;
}
#endif /* WIN32 */
#endif /* __CCTOOLS_PORT_DLFCN_H__ */
