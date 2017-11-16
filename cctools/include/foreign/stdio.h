/*
 * Cygwin defines __STRICT_ANSI__ with -std=c++0x which
 * disables needed functions and -std=gnu++0x doesn't work
 * work due to weird errors in libstdc++.
 */

#ifndef __CCTOOLS_PORT_STDIO_H__
#define __CCTOOLS_PORT_STDIO_H__

#ifdef __CYGWIN__
#pragma push_macro("__STRICT_ANSI__")
#undef __STRICT_ANSI__
#endif /* __CYGWIN__ */

#include_next <stdio.h>

#ifdef __CYGWIN__
#pragma pop_macro("__STRICT_ANSI__")
#endif /* __CYGWIN__ */


#if (defined(_WIN32) || defined(__WIN32__)) && !defined(__CYGWIN__)
#define flockfile(fh)
#define funlockfile(fh)
#define getc_unlocked(fh) getc(fh)
#define setbuf(stream, buf)
#define setbuffer(stream, buf, size)
#define setlinebuf(stream)
#define setvbuf(stream, buf, mode, size) 0
#endif

#endif /* __CCTOOLS_PORT_STDIO_H__ */