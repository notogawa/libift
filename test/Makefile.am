SUBDIRS=\
fcntl \
signal \
stdarg \
stdio \
stdlib \
string \
sys \
time \
unistd

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
sys/lib.la \
time/lib.la \
unistd/lib.la

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
-fno-builtin -O0 \
-Wno-long-long -Wno-variadic-macros

test_LDFLAGS=\
-no-install \
-Wl,--whole-archive,lib.a,--no-whole-archive \
-L$(top_builddir)/src -lift \
-lcrypt \
@PTHREAD_LIBS@

test_LDADD=\
lib.a

TESTS_ENVIRONMENT=\
env LD_PRELOAD=$(top_builddir)/src/.libs/libift_preload.so:$$LD_PRELOAD

TESTS=\
$(check_PROGRAMS)

AUTOMAKE_OPTIONS=\
color-tests
