AM_CPPFLAGS=\
-I$(top_srcdir)/include \
-I$(top_srcdir)/ext/googletest/include \
-I$(top_srcdir)/ext/googletest

check_PROGRAMS=\
sample_test

noinst_HEADERS=\
sample.h

sample_test_SOURCES=\
$(top_srcdir)/ext/googletest/src/gtest-all.cc \
sample_test.cpp \
sample.c

sample_test_CFLAGS=\
$(AM_CFLAGS) \
@PTHREAD_CFLAGS@ \
-fno-builtin -O0 \
@NO_ERROR_LONG_LONG_CFLAGS@ \
@NO_ERROR_VARIADIC_MACROS_CFLAGS@

sample_test_CXXFLAGS=\
$(AM_CXXFLAGS) \
@PTHREAD_CFLAGS@ \
-fno-builtin -O0 \
@NO_ERROR_LONG_LONG_CXXFLAGS@ \
@NO_ERROR_VARIADIC_MACROS_CXXFLAGS@

sample_test_LDFLAGS=\
-no-install \
-L$(top_builddir)/src/ -lift \
@PTHREAD_LIBS@

TESTS_ENVIRONMENT=\
env LD_PRELOAD=$(top_builddir)/src/.libs/libift_preload.so:$$LD_PRELOAD

TESTS=$(check_PROGRAMS)
