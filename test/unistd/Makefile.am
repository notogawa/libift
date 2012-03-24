check_LTLIBRARIES=\
lib.la

lib_la_CPPFLAGS=\
-I$(top_srcdir)/include \
-I$(top_srcdir)/ext/googletest \
-I$(top_srcdir)/ext/googletest/include

lib_la_SOURCES=\
test.cpp

lib_la_CXXFLAGS=\
$(AM_CXXFLAGS) \
@PTHREAD_CFLAGS@ \
-fno-builtin -O0
