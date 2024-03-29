B#                                               -*- Autoconf -*-
#0;95;c Process this file with autoconf to produce a configure script.

AC_PREREQ([2.68])
AC_INIT([libift], [0.1], [n.ohkawa@gmail.com],
        [libift], [https://github.com/notogawa/libift])
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
AC_CHECK_LIB([dl], [dlsym],
             [DL_LIBS=-ldl
              AC_SUBST(DL_LIBS)],
             [AC_MSG_ERROR("missing -ldl")])

# Checks for header files.
AC_CHECK_HEADERS([arpa/inet.h fcntl.h netinet/in.h stdlib.h string.h \
                  sys/socket.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_TYPE_UID_T
AC_TYPE_MODE_T
AC_TYPE_OFF_T
AC_TYPE_PID_T
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T

AX_TLS([],AC_MSG_ERROR([$CC does not support Thread Local Storage]))

# Checks for library functions.
AC_FUNC_ERROR_AT_LINE
# fcntl.h
AC_CHECK_FUNCS([open creat])
# signal.h
AC_CHECK_FUNCS([signal])
# stdarg.h
AC_CHECK_FUNCS([vprintf vfprintf vsprintf vsnprintf vscanf vfscanf vsscanf])
# stdio.h
AC_CHECK_FUNCS([fopen fdopen freopen fclose fgetc fgets getc getchar gets \
                ungetc printf fprintf sprintf snprintf fputc fputs putchar \
                puts fread fwrite scanf fscanf sscanf fseek ftell fgetpos \
                fsetpos remove rename setvbuf tmpfile tmpnam])
# stdlib.h
AX_FUNC_POSIX_MEMALIGN
AC_CHECK_FUNCS([malloc calloc realloc getenv system])
# string.h
AC_CHECK_FUNCS([strerror])
# sys/epoll.h
AC_CHECK_FUNCS([epoll_create epoll_create1 epoll_ctl epoll_wait epoll_pwait])
# sys/select.h
AC_CHECK_FUNCS([select pselect])
# sys/socket.h
AC_CHECK_FUNCS([socket socketpair bind getsockname connect getpeername send \
                recv sendto recvfrom sendmsg recvmsg getsockopt setsockopt \
                listen accept accept4 shutdown sockatmark isfdtype])
# time.h
AC_CHECK_FUNCS([clock strftime time])
# unistd.h
AC_CHECK_FUNCS([access euidaccess eaccess faccessat lseek close read write \
                pread pwrite pipe pipe2 usleep pause chown fchown lchown \
                fchownat chdir fchdir getcwd get_current_dir_name dup dup2 \
                dup3 execve fexecve execv execvp execvpe nice pathconf \
                fpathconf sysconf getpgid setpgid setpgrp setsid getsid \
                getgroups setuid setreuid seteuid setgid setregid setegid \
                getresuid getresgid setresuid setresgid fork ttyname ttyname_r \
                isatty link linkat symlink readlink symlinkat readlinkat \
                unlink unlinkat rmdir tcgetpgrp tcsetpgrp getlogin getlogin_r \
                gethostname sethostname sethostid getdomainname setdomainname \
                vhangup acct daemon chroot getpass fsync syncfs truncate \
                ftruncate brk sbrk lockf fdatasync])
AC_CHECK_FUNCS([crypt],
               [AC_DEFINE_UNQUOTED(HAVE_CRYPT, 1)],
               [AC_CHECK_LIB([crypt], [crypt],
                             [AC_DEFINE_UNQUOTED(HAVE_CRYPT, 1)
                              CRYPT_LIBS=-lcrypt
                              AC_SUBST(CRYPT_LIBS)],
                             [CRYPT_LIBS=
                              AC_SUBST(CRYPT_LIBS)])])

# Treat warnings as errors
AM_CFLAGS="-Wall -Wextra -Werror -ansi -pedantic -fno-inline"
AM_CXXFLAGS="-Wall -Wextra -Werror -ansi -pedantic -fno-inline"

# Check for -Wno-error=unused-parameter
AX_GCC_OPTION([-Wno-error=unused-parameter],
              [${AM_CFLAGS}],[
int main(int argc, char** argv)
{
    return 0;
}
],
              [AM_CFLAGS="${AM_CFLAGS} -Wno-error=unused-parameter"],
              [AM_CFLAGS="${AM_CFLAGS} -Wno-unused-parameter"])
AX_GCC_OPTION([-Wno-error=unused-parameter],
              [-x c++ ${AM_CXXFLAGS}],[
int main(int argc, char** argv)
{
    return 0;
}
],
              [AM_CXXFLAGS="${AM_CXXFLAGS} -Wno-error=unused-parameter"],
              [AM_CXXFLAGS="${AM_CXXFLAGS} -Wno-unused-parameter"])

AX_GCC_OPTION([-Wno-error=long-long],
              [${AM_CFLAGS}],[
int main()
{
    long long _;
    _ = 0;
    return 0;
}
],
              [NO_ERROR_LONG_LONG_CFLAGS="-Wno-error=long-long"],
              [NO_ERROR_LONG_LONG_CFLAGS="-Wno-long-long"])
AC_SUBST(NO_ERROR_LONG_LONG_CFLAGS)
AX_GCC_OPTION([-Wno-error=long-long],
              [-x c++ ${AM_CXXFLAGS}],[
int main()
{
    long long _;
    _ = 0;
    return 0;
}
],
              [NO_ERROR_LONG_LONG_CXXFLAGS="-Wno-error=long-long"],
              [NO_ERROR_LONG_LONG_CXXFLAGS="-Wno-long-long"])
AC_SUBST(NO_ERROR_LONG_LONG_CXXFLAGS)

AX_GCC_OPTION([-Wno-error=variadic-macros],
              [${AM_CFLAGS}],[
#define X(...) __VA_ARGS__
int main()
{
    return 0;
}
],
              [NO_ERROR_VARIADIC_MACROS_CFLAGS="-Wno-error=variadic-macros"],
              [NO_ERROR_VARIADIC_MACROS_CFLAGS="-Wno-variadic-macros"])
AC_SUBST(NO_ERROR_VARIADIC_MACROS_CFLAGS)
AX_GCC_OPTION([-Wno-error=variadic-macros],
              [-x c++ ${AM_CXXFLAGS}],[
#define X(...) __VA_ARGS__
int main()
{
    return 0;
}
],
              [NO_ERROR_VARIADIC_MACROS_CXXFLAGS="-Wno-error=variadic-macros"],
              [NO_ERROR_VARIADIC_MACROS_CXXFLAGS="-Wno-variadic-macros"])
AC_SUBST(NO_ERROR_VARIADIC_MACROS_CXXFLAGS)

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
                 src/sys/Makefile
                 src/sys/epoll/Makefile
                 src/sys/select/Makefile
                 src/sys/socket/Makefile
                 src/time/Makefile
                 src/unistd/Makefile
                 test/Makefile
                 test/fcntl/Makefile
                 test/signal/Makefile
                 test/stdarg/Makefile
                 test/stdio/Makefile
                 test/stdlib/Makefile
                 test/string/Makefile
                 test/sys/Makefile
                 test/sys/epoll/Makefile
                 test/sys/select/Makefile
                 test/sys/socket/Makefile
                 test/time/Makefile
                 test/unistd/Makefile
                 libift.pc
                 script/runift])
AC_CONFIG_SUBDIRS([ext/googletest])
AC_OUTPUT
