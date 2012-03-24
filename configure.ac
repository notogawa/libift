#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.68])
AC_INIT([libift], [0.1], [n.ohkawa@gmail.com], [libift])
AM_INIT_AUTOMAKE([foreign -W -Wall])
AC_CONFIG_SRCDIR([src/libift_preload.cpp])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])

# pkgconfig
AC_ARG_WITH(pkgconfigdir,
            AC_HELP_STRING([--with-pkgconfigdir],
                           [pkgconfig directory [default=LIBDIR/pkgconfig]]),
            [pkgconfigdir=${withval}],
            [pkgconfigdir=${libdir}/pkgconfig])
AC_MSG_NOTICE([pkgconfig directory is ${pkgconfigdir}])
AC_SUBST([pkgconfigdir])

# Checks for programs.
AC_PROG_CXX
AC_PROG_AWK
AC_PROG_CC
AM_PROG_CC_C_O
AC_PROG_CPP
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_PROG_LIBTOOL

# Checks for libraries.
AX_PTHREAD

# Checks for header files.
AC_CHECK_HEADERS([fcntl.h stdlib.h string.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_TYPE_UID_T
AC_TYPE_MODE_T
AC_TYPE_OFF_T
AC_TYPE_PID_T
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T

# Checks for library functions.
AC_FUNC_ERROR_AT_LINE
AC_FUNC_MALLOC
AC_FUNC_REALLOC

# Treat warnings as errors
AM_CFLAGS="-Wall -Wextra -Werror -Wunreachable-code -ansi -pedantic"
AM_CXXFLAGS="-Wall -Wextra -Werror -Wunreachable-code -std=c++0x -pedantic"

# Check for -Wno-error=unused-parameter
AC_CACHE_CHECK([for gcc -Wno-error=unused-parameter support],
               ac_cv_c_gcc_no_error_unused_parameter,
               ac_cv_c_gcc_no_error_unused_parameter="undefined")
if test "x$ac_cv_c_gcc_no_error_unused_parameter" = "xundefined"
then
  AX_GCC_OPTION([-Wno-error=unused-parameter],[],[],
                ac_cv_c_gcc_no_error_unused_parameter="yes",
                ac_cv_c_gcc_no_error_unused_parameter="no")
fi
if test "x$ac_cv_c_gcc_no_error_unused_parameter" = "xyes"
then
  AM_CFLAGS="${AM_CFLAGS} -Wno-error=unused-parameter"
  AM_CXXFLAGS="${AM_CXXFLAGS} -Wno-error=unused-parameter"
else
  AM_CFLAGS="${AM_CFLAGS} -Wno-unused-parameter"
  AM_CXXFLAGS="${AM_CXXFLAGS} -Wno-unused-parameter"
fi

AC_SUBST(AM_CPPFLAGS)
AC_SUBST(AM_CFLAGS)
AC_SUBST(AM_CXXFLAGS)

AC_CONFIG_FILES([Makefile
                 include/Makefile
                 sample/Makefile
                 script/Makefile
                 src/Makefile
                 src/fcntl/Makefile
                 src/signal/Makefile
                 src/stdio/Makefile
                 src/stdlib/Makefile
                 src/string/Makefile
                 src/time/Makefile
                 src/unistd/Makefile
                 test/Makefile
                 test/fcntl/Makefile
                 test/signal/Makefile
                 test/stdarg/Makefile
                 test/stdio/Makefile
                 test/stdlib/Makefile
                 test/string/Makefile
                 test/time/Makefile
                 test/unistd/Makefile
                 libift.pc
                 script/runift])
AC_CONFIG_SUBDIRS([ext/googletest])
AC_OUTPUT
