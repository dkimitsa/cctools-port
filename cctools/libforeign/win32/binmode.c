//
// dkimitsa: workaround for broken binmode.o in mingw.
//
#if (defined _WIN32 || defined __WIN32__) && ! defined __CYGWIN__

#include <fcntl.h>
int _fmode = _O_BINARY;

#endif
