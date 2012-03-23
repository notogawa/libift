SUBDIRS=\
fcntl \
signal \
stdarg \
stdio \
stdlib \
string \
time

# not a standard libtool library name
check_LTLIBRARIES=\
lib.a

lib_a_SOURCES=

lib_a_LIBADD=\
fcntl/lib.la \
signal/lib.la \
stdarg/lib.la \
stdio/lib.la \
stdlib/lib.la \
string/lib.la \
time/lib.la

check_PROGRAMS=\
test

test_CPPFLAGS=\
$(AM_CPPFLAGS) \
-I$(top_srcdir)/ext/googletest \
-I$(top_srcdir)/ext/googletest/include

test_SOURCES=\
$(top_srcdir)/ext/googletest/src/gtest-all.cc \
test.cpp

test_CXXFLAGS=\
$(AM_CXXFLAGS) \
@PTHREAD_CFLAGS@ \
-fno-builtin -O0

test_LDFLAGS=\
-Wl,--whole-archive,lib.a,--no-whole-archive \
-L$(top_builddir)/src -lift \
@PTHREAD_LIBS@

TESTS_ENVIRONMENT=\
env LD_PRELOAD=$(top_builddir)/src/.libs/libift_preload.so:$$LD_PRELOAD

TESTS=\
$(check_PROGRAMS)

AUTOMAKE_OPTIONS=\
color-tests
