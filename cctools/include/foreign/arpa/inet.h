#if (defined(_WIN32) || defined(__WIN32__)) && !defined(__CYGWIN__)
#include <winsock.h> // for hton etc
#else
#include_next <arpa/inet.h>
#endif
