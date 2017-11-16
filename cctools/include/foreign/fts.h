/*
Copyright (c) 2003-2006 by Juliusz Chroboczek

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

/* dkimitsa: thanks to https://github.com/jech/polipo */

#ifndef __CCTOOLS_PORT_FTS_H__
#define __CCTOOLS_PORT_FTS_H__

#if (defined(_WIN32) || defined(__WIN32__)) && !defined(__CYGWIN__)

#include <dirent.h>

#define FTS_LOGICAL 1
// below is just required to allow cctools to compile, there is no hard links expected on linux
#define FTS_PHYSICAL FTS_LOGICAL

#define FTS_F 1
#define FTS_D 2
#define FTS_DP 3
#define FTS_DC 4
#define FTS_NS 5
#define FTS_NSOK 6
#define FTS_DNR 7
#define FTS_SLNONE 8
#define FTS_DEFAULT 9
#define FTS_ERR 10


#ifndef FTS_MAX_DEPTH
#define FTS_MAX_DEPTH 64
#endif

struct _FTSENT {
    unsigned short fts_info;
    char *fts_path;
    size_t fts_pathlen;
    char *fts_name;
    char *fts_accpath;
    struct stat *fts_statp;
    int fts_errno;
};

typedef struct _FTSENT FTSENT;

struct _FTS {
    int depth;
    DIR *dir[FTS_MAX_DEPTH];
    char *cwd0, *cwd;
    struct _FTSENT ftsent;
    struct stat stat;
    char *dname;
};

typedef struct _FTS FTS;

FTS* fts_open(char * const *path_argv, int options,
              int (*compar)(const FTSENT **, const FTSENT **));
int fts_close(FTS *fts);
FTSENT * fts_read(FTS *fts);

#else
#include_next <fts.h>
#endif /* windows */

#endif /*__CCTOOLS_PORT_FTS_H__ */
