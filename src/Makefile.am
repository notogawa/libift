SUBDIRS=\
fcntl \
signal \
stdio \
stdlib \
string \
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
-ldl \
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
-ldl \
-version-info 0:0:0 \
-shared

libift_preload_la_LIBADD=\
fcntl/lib.la \
signal/lib.la \
stdio/lib.la \
stdlib/lib.la \
string/lib.la \
time/lib.la \
unistd/lib.la

libift_preload_la_CPPFLAGS=\
$(AM_CPPFLAGS) \
-I$(top_srcdir)/src

check_PROGRAMS=\
test

test_CPPFLAGS=\
$(AM_CPPFLAGS) \
-I$(top_srcdir)/ext/googletest/include \
-I$(top_srcdir)/ext/googletest

test_SOURCES=\
$(top_srcdir)/ext/googletest/src/gtest-all.cc \
test_libift.cpp \
test_stdio.cpp

test_CXXFLAGS=\
$(AM_CXXFLAGS) \
-fno-builtin -O0 \
@PTHREAD_CFLAGS@

test_LDFLAGS=\
-lift \
@PTHREAD_LIBS@

TESTS_ENVIRONMENT=\
env LD_PRELOAD=$(top_builddir)/src/.libs/libift_preload.so:$$LD_PRELOAD

TESTS=\
$(check_PROGRAMS)

AUTOMAKE_OPTIONS=\
color-tests
