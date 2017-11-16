#ifndef __CCTOOLS_PORT_UNISTD_H__
#define __CCTOOLS_PORT_UNISTD_H__

#include_next <unistd.h>

#ifndef L_SET
#define L_SET SEEK_SET /* Cygwin */
#endif

#if (defined(_WIN32) || defined(__WIN32__)) && !defined(__CYGWIN__)
static inline uid_t getuid(void) { 
	return 1; 
}

static inline gid_t getgid(void) { 
	return 1; 
}

static inline int chown(const char *__path, uid_t __owner, gid_t __group)
{ 
  return 0; 
}

#endif /* WIN32 */

#endif /* __CCTOOLS_PORT_UNISTD_H__ */
