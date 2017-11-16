#include_next <fcntl.h>

#ifndef O_FSYNC
#ifdef O_SYNC
#define O_FSYNC O_SYNC /* Cygwin */
#else
#define O_FSYNC 0 /* win32 case, zero will not affect open call in writeout */
#endif
#endif /* O_FSYNC */

