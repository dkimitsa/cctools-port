#ifndef __CCTOOLS_PORT_SYS_PARAM_H__
#define __CCTOOLS_PORT_SYS_PARAM_H__

#include_next <sys/param.h>

#if (defined(_WIN32) || defined(__WIN32__)) && !defined(__CYGWIN__)

#ifndef MIN
#define MIN(a,b) (((a)<(b))?(a):(b))
#endif

#ifndef MAX
#define MAX(a,b) (((a)>(b))?(a):(b))
#endif

#endif // WIN32

#endif // __CCTOOLS_PORT_SYS_PARAM_H__
