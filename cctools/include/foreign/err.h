#ifndef __CCTOOLS_PORT_ERR_H__
#define __CCTOOLS_PORT_ERR_H__

#if !((defined(_WIN32) || defined(__WIN32__)) && !defined(__CYGWIN__))
#include_next <err.h>
#else
#define err(retval, ...) do { \
    fprintf(stderr, __VA_ARGS__); \
    fprintf(stderr, "Undefined error: %d\n", errno); \
    exit(retval); \
} while(0)

#define errx(retval, ...) do { \
    fprintf(stderr, __VA_ARGS__); \
    fprintf(stderr, "Undefined error: %d\n", errno); \
    exit(retval); \
} while(0)

#define warn(...) { \
    fprintf(stderr, __VA_ARGS__); \
} while(0)

#define warnx(...) { \
    fprintf(stderr, __VA_ARGS__); \
} while(0)

#endif // WIN32

#endif // __CCTOOLS_PORT_ERR_H__