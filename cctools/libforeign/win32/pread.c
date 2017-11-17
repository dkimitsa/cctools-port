#if (defined(_WIN32) || defined(__WIN32__)) && !defined(__CYGWIN__)

// dkimitsa: thanks to https://github.com/git/git

#include <stdio.h>
#include <unistd.h>

static ssize_t read_in_full(int fd, void *buf, size_t count)
{
	char *p = buf;
	ssize_t total = 0;

	while (count > 0) {
		ssize_t loaded = read(fd, p, count);
		if (loaded < 0)
			return -1;
		if (loaded == 0)
			return total;
		count -= loaded;
		p += loaded;
		total += loaded;
	}

	return total;
}

ssize_t pread(int fd, void *buf, size_t count, off_t offset)
{
    off_t current_offset;
    ssize_t rc;

    current_offset = lseek(fd, 0, SEEK_CUR);

    if (lseek(fd, offset, SEEK_SET) < 0)
        return -1;

    rc = read_in_full(fd, buf, count);

    if (current_offset != lseek(fd, current_offset, SEEK_SET))
        return -1;
    return rc;
}

#endif // win32