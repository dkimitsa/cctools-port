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

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

#ifndef FTS_MAX_DEPTH
#define FTS_MAX_DEPTH 64
#endif

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

static char *
getcwd_a()
{
    char buf[256];
    char *ret;
    ret = getcwd(buf, 256);
    if(ret == NULL)
        return NULL;
    return strdup(buf);
}

static char *
mkfilename(const char *path, char *filename)
{
    int n = strlen(path);
    char *buf = malloc(n + 1 + strlen(filename) + 1);
    if(buf == NULL)
        return NULL;
    memcpy(buf, path, n);
    if(buf[n - 1] != '/')
        buf[n++] = '/';
    strcpy(buf + n, filename);
    return buf;
}

static int
split(const char *path, int *slash_return, int *dlen, int *blen)
{
    int len; int slash;
    len = strlen(path);
    while(len > 0 && path[len - 1] == '/')
        len--;
    if(len == 0)
        return -1;
    slash = len - 1;
    while(slash >= 0 && path[slash] != '/')
        slash--;

    if(slash_return) *slash_return = slash;
    if(dlen) *dlen = slash + 1;
    if(blen) *blen = len - slash - 1;
    return 1;
}

static char *
basename_a(const char *path)
{
    int blen, slash;
    char *b;
    int rc;

    rc = split(path, &slash, NULL, &blen);
    if(rc < 0 || blen == 0)
        return NULL;

    b = malloc(blen + 1);
    if(b == NULL)
        return NULL;
    memcpy(b, path + slash + 1, blen);
    b[blen] = '\0';
    return b;
}

static char *
dirname_a(const char *path)
{
    int dlen;
    int rc;
    char *d;

    rc = split(path, NULL, &dlen, NULL);
    if(rc < 0)
        return NULL;

    d = malloc(dlen + 1);
    if(d == NULL)
        return NULL;
    memcpy(d, path, dlen);
    d[dlen] = '\0';
    return d;
}



/*
 * Make the directory identified by the argument the current directory.
 */
static int
change_to_dir(DIR *dir)
{
    size_t len = strlen(dir->dd_name);
    if (dir->dd_name[len -1 ] != '*') {
        return chdir(dir->dd_name);
    } else {
        char *path = malloc(len);
        strncpy(path, dir->dd_name, len - 1);
        path[len - 1] = '\0';

        int res = chdir(path);
        int save = errno;
        free(path);
        errno = save;
        return res;
    }

}

static FTS*
fts_open(char * const *path_argv, int options,
         int (*compar)(const FTSENT **, const FTSENT **))
{
    FTS *fts;
    DIR *dir;
    char *cwd;
    int rc;

    if(options != FTS_LOGICAL || compar != NULL || path_argv[1] != NULL) {
        errno = ENOSYS;
        return NULL;
    }

    dir = opendir(path_argv[0]);
    if(dir == NULL)
        return NULL;

    fts = calloc(sizeof(FTS), 1);
    if(fts == NULL) {
        int save = errno;
        closedir(dir);
        errno = save;
        return NULL;
    }

    cwd = getcwd_a();
    if(cwd == NULL) {
        int save = errno;
        free(fts);
        closedir(dir);
        errno = save;
        return NULL;
    }

    rc = change_to_dir(dir);
    if(rc < 0) {
        int save = errno;
        free(cwd);
        free(fts);
        closedir(dir);
        errno = save;
        return NULL;
    }

    fts->depth = 0;
    fts->dir[0] = dir;
    fts->cwd0 = cwd;
    fts->cwd = strdup(path_argv[0]);
    return fts;
}

static int
fts_close(FTS *fts)
{
    int save = 0;
    int rc;

    if(fts->ftsent.fts_path) {
        free(fts->ftsent.fts_path);
        fts->ftsent.fts_path = NULL;
    }

    if(fts->dname) {
        free(fts->dname);
        fts->dname = NULL;
    }

    rc = chdir(fts->cwd0);
    if(rc < 0)
        save = errno;

    while(fts->depth >= 0) {
        closedir(fts->dir[fts->depth]);
        fts->depth--;
    }

    free(fts->cwd0);
    if(fts->cwd) free(fts->cwd);
    free(fts);

    if(rc < 0) {
        errno = save;
        return -1;
    }
    return 0;
}

static FTSENT *
fts_read(FTS *fts)
{
    struct dirent *dirent;
    int rc;
    char *name;
    char buf[1024];

    if(fts->ftsent.fts_path) {
        free(fts->ftsent.fts_path);
        fts->ftsent.fts_path = NULL;
    }

    if(fts->dname) {
        free(fts->dname);
        fts->dname = NULL;
    }

    again:
    dirent = readdir(fts->dir[fts->depth]);
    if(dirent == NULL) {
        char *newcwd = NULL;
        closedir(fts->dir[fts->depth]);
        fts->dir[fts->depth] = NULL;
        fts->depth--;
        if(fts->depth >= 0) {
            fts->dname = basename_a(fts->cwd);
            if(fts->dname == NULL)
                goto error;
            newcwd = dirname_a(fts->cwd);
            if(newcwd == NULL)
                goto error;
        }
        if(fts->cwd) free(fts->cwd);
        fts->cwd = NULL;
        if(fts->depth < 0)
            return NULL;
        rc = change_to_dir(fts->dir[fts->depth]);
        if(rc < 0) {
            free(newcwd);
            goto error;
        }
        fts->cwd = newcwd;
        name = fts->dname;
        fts->ftsent.fts_info = FTS_DP;
        goto done;
    }

    name = dirent->d_name;

    again2:
    rc = stat(name, &fts->stat);
    if(rc < 0) {
        fts->ftsent.fts_info = FTS_NS;
        goto error2;
    }

    if(S_ISDIR(fts->stat.st_mode)) {
        char *newcwd;
        DIR *dir;

        if(strcmp(name, ".") == 0 || strcmp(name, "..") == 0)
            goto again;

        if(fts->depth >= FTS_MAX_DEPTH) {
            // it is better than error
            goto again;
//            errno = ENFILE;
//            goto error;
        }
        dir = opendir(dirent->d_name);
        if(dir == NULL) {
            if(errno == EACCES) {
                fts->ftsent.fts_info = FTS_DNR;
                goto error2;
            } else
                goto error;
        }
        newcwd = mkfilename(fts->cwd, dirent->d_name);
        rc = change_to_dir(dir);
        if(rc < 0) {
            free(newcwd);
            goto error;
        }
        free(fts->cwd);
        fts->cwd = newcwd;
        fts->ftsent.fts_info = FTS_D;
        fts->depth++;
        fts->dir[fts->depth] = dir;
        goto done;
    } else if(S_ISREG(fts->stat.st_mode)) {
        fts->ftsent.fts_info = FTS_F;
        goto done;
#ifdef _____S_ISLNK
        } else if(S_ISLNK(fts->stat.st_mode)) {
        int rc;
        rc = readlink(name, buf, 1024);
        if(rc < 0)
            goto error;
        if(rc >= 1023) {
            errno = ENAMETOOLONG;
            goto error;
        }
        buf[rc] = '\0';
        name = buf;
        if(access(buf, F_OK) >= 0)
            goto again2;
        fts->ftsent.fts_info = FTS_SLNONE;
        goto done;
#endif
    } else {
        fts->ftsent.fts_info = FTS_DEFAULT;
        goto done;
    }

    done:
    if(fts->cwd == NULL)
        fts->cwd = getcwd_a();
    if(fts->cwd == NULL) goto error;
    fts->ftsent.fts_path = mkfilename(fts->cwd, name);
    if(fts->ftsent.fts_path == NULL) goto error;
    fts->ftsent.fts_pathlen = strlen(fts->ftsent.fts_path);
    fts->ftsent.fts_accpath = name;
    fts->ftsent.fts_name = name;
    fts->ftsent.fts_statp = &fts->stat;
    return &fts->ftsent;

    error:
    fts->ftsent.fts_info = FTS_ERR;
    error2:
    fts->ftsent.fts_errno = errno;
    return NULL;
}

#else
#include_next <fts.h>
#endif /* windows */

#endif /*__CCTOOLS_PORT_FTS_H__ */
