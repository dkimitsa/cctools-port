#ifndef __CCTOOLS_PORT_SYS_TYPES_H__
#define __CCTOOLS_PORT_SYS_TYPES_H__

#include_next <sys/types.h>

#if (defined(_WIN32) || defined(__WIN32__)) && !defined(__CYGWIN__)

#include <stdint.h>

typedef uint8_t u_char;
typedef uint32_t u_int;
typedef uint16_t u_short;
typedef uint16_t u_int16_t;
typedef uint32_t u_int32_t;
typedef uint32_t uid_t;
typedef uint32_t gid_t;

#endif // windows

#endif // __CCTOOLS_PORT_SYS_TYPES_H__
