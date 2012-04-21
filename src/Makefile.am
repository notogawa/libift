SUBDIRS=\
fcntl \
signal \
stdio \
stdlib \
string \
sys \
time \
unistd

AM_CPPFLAGS=\
-I$(top_srcdir)/include

lib_LTLIBRARIES=\
libift.la \
libift_preload.la

libift_la_SOURCES=\
incremental_failable.cpp

libift_la_LDFLAGS=\
@DL_LIBS@ \
-version-info 0:0:0

noinst_HEADERS=\
cdecls.hpp \
basic_impl.hpp \
vargs_impl.hpp \
scoped_global_lock.hpp

libift_preload_la_SOURCES=\
scoped_global_lock.cpp \
libift_preload.cpp

libift_preload_la_LDFLAGS=\
@DL_LIBS@ \
-version-info 0:0:0 \
-shared

libift_preload_la_LIBADD=\
fcntl/lib.la \
signal/lib.la \
stdio/lib.la \
stdlib/lib.la \
string/lib.la \
sys/lib.la \
time/lib.la \
unistd/lib.la

libift_preload_la_CPPFLAGS=\
$(AM_CPPFLAGS) \
-I$(top_srcdir)/src
