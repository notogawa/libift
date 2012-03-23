# not a standard libtool library name
check_LTLIBRARIES=\
lib.a

lib_a_CPPFLAGS=\
-I$(top_srcdir)/include \
-I$(top_srcdir)/ext/googletest \
-I$(top_srcdir)/ext/googletest/include

lib_a_SOURCES=\
test.cpp

lib_a_CXXFLAGS=\
$(AM_CXXFLAGS) \
@PTHREAD_CFLAGS@ \
-fno-builtin -O0
