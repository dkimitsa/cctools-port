#ifndef __CCTOOLS_PORT_SYS_STAT_H__
#define __CCTOOLS_PORT_SYS_STAT_H__

#include_next <sys/stat.h>

#if (defined(_WIN32) || defined(__WIN32__)) && !defined(__CYGWIN__)

#define S_ISUID  0004000
#define S_ISVTX  0001000

#define S_IFLNK	 0120000
#define S_ISLNK(m)	(((m) & S_IFMT) == S_IFLNK)

#define S_IFSOCK 0140000
#define S_ISSOCK(m)	(((m) & S_IFMT) == S_IFSOCK)

#define S_ISGID  0002000

#define DEFFILEMODE (S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)

inline static int fchmod(int fd, mode_t mode) {
  return 0;
}

#endif // WIN32

#endif // __CCTOOLS_PORT_SYS_PARAM_H__
