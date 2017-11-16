
#if (defined _WIN32 || defined __WIN32__) && ! defined __CYGWIN__

#include <windows.h>
#include <sys/param.h>

char *realpath(const char *path, char *resolved_path) {
    if (!resolved_path)
        resolved_path = malloc(MAXPATHLEN);
    return _fullpath(resolved_path, path, MAXPATHLEN);
}

#endif