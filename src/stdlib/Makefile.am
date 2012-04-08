AM_CPPFLAGS=\
-I$(top_srcdir)/src

noinst_LTLIBRARIES=\
lib.la

lib_la_SOURCES=\
malloc.cpp \
calloc.cpp \
realloc.cpp \
getenv.cpp \
system.cpp \
posix_memalign.cpp

lib_la_CXXFLAGS=\
$(AM_CXXFLAGS) \
-fno-exceptions
