#ifndef __CCTOOLS_PORT_STRING_H__
#define __CCTOOLS_PORT_STRING_H__
#include_next <string.h>

#if (defined(_WIN32) || defined(__WIN32__)) && !defined(__CYGWIN__)

inline static char *rindex(const char *s, int c) {
	return strrchr(s, c);
}

inline static char *index(const char *s, int c) {
	return strchr(s, c);
}

#define bcopy(src, dest, n) memcpy(dest, src, n)
#define strerror_r(errnum, buf, buflen) EINVAL

#endif /* WIN32 */
#endif /* __CCTOOLS_PORT_PWD_H__ */
