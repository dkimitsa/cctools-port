#ifndef __CCTOOLS_PORT_SYS_ERRNO_H__
#define __CCTOOLS_PORT_SYS_ERRNO_H__

#if (defined(_WIN32) || defined(__WIN32__)) && !defined(__CYGWIN__)
// nothing, just added to solve dependency
#else
#include_next <sys/errno.h>
#endif

#endif // __CCTOOLS_PORT_SYS_ERRNO_H__
