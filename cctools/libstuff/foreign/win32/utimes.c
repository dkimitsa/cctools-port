#if (defined(_WIN32) || defined(__WIN32__)) && !defined(__CYGWIN__)

#include <windows.h>

#define KDE_SECONDS_SINCE_1601	11644473600LL
#define KDE_USEC_IN_SEC	1000000LL

/*after Microsoft KB167296   */
static void UnixTimevalToFileTime(struct timeval t, LPFILETIME pft)
{
	LONGLONG ll;

	ll = Int32x32To64(t.tv_sec, KDE_USEC_IN_SEC*10) + t.tv_usec*10 + KDE_SECONDS_SINCE_1601*KDE_USEC_IN_SEC*10;
	pft->dwLowDateTime = (DWORD)ll;
	pft->dwHighDateTime = ll >> 32;
}

/*errno==EACCES on read-only devices */
int utimes(const char *filename, const struct timeval times[2])
{
	FILETIME LastAccessTime;
	FILETIME LastModificationTime;
	HANDLE hFile;

#ifdef _WIN32_WCE
	const wchar_t *wfilename = wce_mbtowc(filename);
#endif

	if(times) {
		UnixTimevalToFileTime(times[0], &LastAccessTime);
		UnixTimevalToFileTime(times[1], &LastModificationTime);
	}
	else {
		GetSystemTimeAsFileTime(&LastAccessTime);
		GetSystemTimeAsFileTime(&LastModificationTime);
	}

#ifndef _WIN32_WCE
	hFile=CreateFileA(filename, FILE_WRITE_ATTRIBUTES, FILE_SHARE_DELETE | FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL, OPEN_EXISTING, 0, NULL);
#else
	hFile=CreateFileW(wfilename, FILE_WRITE_ATTRIBUTES, FILE_SHARE_DELETE | FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL, OPEN_EXISTING, 0, NULL);
	free(wfilename);
#endif
	if(hFile==INVALID_HANDLE_VALUE) {
		switch(GetLastError()) {
			case ERROR_FILE_NOT_FOUND:
				errno=ENOENT;
				break;
			case ERROR_PATH_NOT_FOUND:
			case ERROR_INVALID_DRIVE:
				errno=ENOTDIR;
				break;
/*			case ERROR_WRITE_PROTECT:	reateFile sets ERROR_ACCESS_DENIED on read-only devices
				errno=EROFS;
				break;*/
			case ERROR_ACCESS_DENIED:
				errno=EACCES;
				break;
			default:
				errno=ENOENT;	/*what other errors can occur? */
		}
		return -1;
	}

	if(!SetFileTime(hFile, NULL, &LastAccessTime, &LastModificationTime)) {
		/*can this happen? */
		errno=ENOENT;
		return -1;
	}
	CloseHandle(hFile);
	return 0;
}


#endif // WIN32
