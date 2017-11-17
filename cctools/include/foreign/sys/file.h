
#ifndef __CCTOOLS_PORT_SYS_FILE_H__
#define __CCTOOLS_PORT_SYS_FILE_H__

#include_next <sys/file.h>
#if (defined _WIN32 || defined __WIN32__) && ! defined __CYGWIN__

#ifndef ESTALE
#define	ESTALE		116	/* Stale file handle */
#endif

/* Operations for the 'flock' call (same as Linux kernel constants).  */
# define LOCK_SH 1       /* Shared lock.  */
# define LOCK_EX 2       /* Exclusive lock.  */
# define LOCK_UN 8       /* Unlock.  */

/* Can be OR'd in to one of the above.  */
# define LOCK_NB 4 /* Don't block when locking.  */

#ifdef __cplusplus
extern "C" {
#endif

int flock (int fd, int operation);

#ifdef __cplusplus
}
#endif

#endif /* !Windows */


#endif // __CCTOOLS_PORT_SYS_TYPES_H__
