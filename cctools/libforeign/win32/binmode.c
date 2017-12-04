//
// dkimitsa: workaround for broken binmode.o in mingw.
//
#include <fcntl.h>
int _fmode = _O_BINARY;

