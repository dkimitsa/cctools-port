noinst_LTLIBRARIES = libforeign.la

libforeign_la_CFLAGS = -I$(top_srcdir)/include -I$(top_srcdir)/include/foreign -D__DARWIN_UNIX03 $(WARNINGS) $(LTO_DEF) -DPROGRAM_PREFIX="\"$(PROGRAM_PREFIX)\"" $(ENDIAN_FLAG)

libforeign_la_SOURCES =  \
	win32/flock.c \
	win32/fts.c \
	win32/mman.c \
	win32/pread.c \
	win32/realpath.c \
	win32/utimes.c \
	win32/binmode.c

