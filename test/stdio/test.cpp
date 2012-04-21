// Copyright (c) 2012, Noriyuki OHKAWA a.k.a. notogawa.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright
//   notice, this list of conditions and the following disclaimer.
//
// * Redistributions in binary form must reproduce the above
//   copyright notice, this list of conditions and the following
//   disclaimer in the documentation and/or other materials provided
//   with the distribution.
//
// * Neither the name of Noriyuki OHKAWA and notogawa nor the names of other
//   contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#include <config.h>
#include <gtest/gtest.h>
#define _GLIBCXX_USE_C99 1
#include <cstdio>
#include <fcntl.h>
#include <cerrno>
#include "ift/stdio.hpp"

#ifdef HAVE_FOPEN
TEST(stdio,fopen)
{
    fopen_failable_by__(ENOMEM)
    {
        ASSERT_EQ(NULL, std::fopen("/dev/null", "w"));
        ASSERT_EQ(ENOMEM, errno);
    }
}
#endif

#ifdef HAVE_FDOPEN
TEST(stdio,fdopen)
{
    fdopen_failable_by__(ENOMEM)
    {
        int fd = open("/dev/null", O_RDWR, 0);
        ASSERT_EQ(NULL, fdopen(fd, "w"));
        ASSERT_EQ(ENOMEM, errno);
        close(fd);
    }
}
#endif

#ifdef HAVE_FREOPEN
TEST(stdio,freopen)
{
    FILE* fp = std::tmpfile();
    freopen_failable_by__(ENOMEM)
    {
        ASSERT_EQ(NULL, std::freopen("/dev/null", "w", fp));
        ASSERT_EQ(ENOMEM, errno);
    }
    fclose(fp);
}
#endif

#ifdef HAVE_FCLOSE
TEST(stdio,fclose)
{
    FILE* fp = std::tmpfile();
    fclose_failable_by__(EIO)
    {
        ASSERT_EQ(-1, std::fclose(fp));
        ASSERT_EQ(EIO, errno);
    }
    fclose(fp);
}
#endif

#ifdef HAVE_FGETC
TEST(stdio,fgetc)
{
    FILE* fp = std::tmpfile();
    fgetc_failable__
    {
        ASSERT_EQ(EOF, std::fgetc(fp));
    }
    fclose(fp);
}
#endif

#ifdef HAVE_FGETS
TEST(stdio,fgets)
{
    FILE* fp = std::tmpfile();
    fgets_failable__
    {
        char buf[1024];
        ASSERT_EQ(NULL, std::fgets(buf, sizeof(buf)/sizeof(buf[0]), fp));
    }
    fclose(fp);
}
#endif

#ifdef HAVE_GETC
TEST(stdio,getc)
{
    FILE* fp = std::tmpfile();
    getc_failable__
    {
        ASSERT_EQ(EOF, std::getc(fp));
    }
    fclose(fp);
}
#endif

#ifdef HAVE_GETCHAR
TEST(stdio,getchar)
{
    getchar_failable__
    {
        ASSERT_EQ(EOF, std::getchar());
    }
}
#endif

#ifdef HAVE_GETS
TEST(stdio,gets)
{
    gets_failable__
    {
        char buf[1024];
        ASSERT_EQ(NULL, std::gets(buf));
    }
}
#endif

#ifdef HAVE_UNGETC
TEST(stdio,ungetc)
{
    FILE* fp = std::tmpfile();
    ungetc_failable__
    {
        ASSERT_EQ(EOF, std::ungetc(10, fp));
    }
    fclose(fp);
}
#endif

#ifdef HAVE_PRINTF
TEST(stdio,printf)
{
    printf_failable__
    {
        ASSERT_GT(0, std::printf("test\n"));
    }
}
#endif

#ifdef HAVE_FPRINTF
TEST(stdio,fprintf)
{
    FILE* fp = std::tmpfile();
    fprintf_failable__
    {
        ASSERT_GT(0, std::fprintf(fp, "test\n"));
    }
    fclose(fp);
}
#endif

#ifdef HAVE_SPRINTF
TEST(stdio,sprintf)
{
    sprintf_failable__
    {
        char buf[1024];
        ASSERT_GT(0, std::sprintf(buf, "test\n"));
    }
}
#endif

#ifdef HAVE_SNPRINTF
TEST(stdio,snprintf)
{
    snprintf_failable__
    {
        char buf[1024];
        ASSERT_GT(0, std::snprintf(buf, 2, "test\n"));
    }
}
#endif

#ifdef HAVE_FPUTC
TEST(stdio,fputc)
{
    FILE* fp = std::tmpfile();
    fputc_failable__
    {
        ASSERT_EQ(EOF, std::fputc(10, fp));
    }
    fclose(fp);
}
#endif

#ifdef HAVE_FPUTS
TEST(stdio,fputs)
{
    FILE* fp = std::tmpfile();
    fputs_failable__
    {
        ASSERT_EQ(EOF, std::fputs("test", fp));
    }
    fclose(fp);
}
#endif

#ifdef HAVE_PUTCHAR
TEST(stdio,putchar)
{
    putchar_failable__
    {
        ASSERT_EQ(EOF, std::putchar(10));
    }
}
#endif

#ifdef HAVE_PUTS
TEST(stdio,puts)
{
    puts_failable__
    {
        ASSERT_EQ(EOF, std::puts("test"));
    }
}
#endif

#ifdef HAVE_FREAD
TEST(stdio,fread)
{
    FILE* fp = std::tmpfile();
    fread_failable__
    {
        char buf[1024];
        ASSERT_EQ(0U, std::fread(buf, 10, 10, fp));
    }
    fclose(fp);
}
#endif

#ifdef HAVE_FWRITE
TEST(stdio,fwrite)
{
    FILE* fp = std::tmpfile();
    fwrite_failable__
    {
        char buf[1024];
        ASSERT_EQ(0U, std::fwrite(buf, 10, 10, fp));
    }
    fclose(fp);
}
#endif

#ifdef HAVE_SCANF
TEST(stdio,scanf)
{
    scanf_failable_by__(ERANGE)
    {
        int n = 0;
        ASSERT_EQ(EOF, std::scanf("%d", &n));
        ASSERT_EQ(ERANGE, errno);
    }
}
#endif

#ifdef HAVE_FSCANF
TEST(stdio,fscanf)
{
    FILE* fp = std::tmpfile();
    fscanf_failable_by__(EBADF)
    {
        int n = 0;
        ASSERT_EQ(EOF, std::fscanf(fp, "%d", &n));
        ASSERT_EQ(EBADF, errno);
    }
    fclose(fp);
}
#endif

#ifdef HAVE_SSCANF
TEST(stdio,sscanf)
{
    sscanf_failable_by__(ENOMEM)
    {
        int n = 0;
        ASSERT_EQ(EOF, sscanf("12", "%d", &n));
        ASSERT_EQ(ENOMEM, errno);
    }
}
#endif

#ifdef HAVE_FSEEK
TEST(stdio,fseek)
{
    FILE* fp = std::tmpfile();
    fseek_failable_by__(EBADF)
    {
        ASSERT_EQ(-1, std::fseek(fp, 0, SEEK_SET));
        ASSERT_EQ(EBADF, errno);
    }
    fclose(fp);
}
#endif

#ifdef HAVE_FTELL
TEST(stdio,ftell)
{
    FILE* fp = std::tmpfile();
    ftell_failable_by__(EBADF)
    {
        ASSERT_EQ(-1, std::ftell(fp));
        ASSERT_EQ(EBADF, errno);
    }
    fclose(fp);
}
#endif

#ifdef HAVE_FGETPOS
TEST(stdio,fgetpos)
{
    FILE* fp = std::tmpfile();
    fgetpos_failable_by__(EBADF)
    {
        fpos_t pos;
        ASSERT_EQ(-1, std::fgetpos(fp, &pos));
        ASSERT_EQ(EBADF, errno);
    }
    fclose(fp);
}
#endif

#ifdef HAVE_FSETPOS
TEST(stdio,fsetpos)
{
    FILE* fp = std::tmpfile();
    fsetpos_failable_by__(EBADF)
    {
        fpos_t pos;
        ASSERT_EQ(0, std::fgetpos(fp, &pos));
        ASSERT_EQ(-1, std::fsetpos(fp, &pos));
        ASSERT_EQ(EBADF, errno);
    }
    fclose(fp);
}
#endif

#ifdef HAVE_REMOVE
TEST(stdio,remove)
{
    remove_failable_by__(EACCES)
    {
        ASSERT_EQ(-1, std::remove("/tmp/foo"));
        ASSERT_EQ(EACCES, errno);
    }
}
#endif

#ifdef HAVE_RENAME
TEST(stdio,rename)
{
    rename_failable_by__(EACCES)
    {
        ASSERT_EQ(-1, std::rename("/tmp/foo", "/tmp/bar"));
        ASSERT_EQ(EACCES, errno);
    }
}
#endif

#ifdef HAVE_SETVBUF
TEST(stdio,setvbuf)
{
    FILE* fp = std::tmpfile();
    setvbuf_failable_by__(ENOMEM)
    {
        char buf[1024];
        ASSERT_EQ(-1, std::setvbuf(fp, buf, _IOLBF, sizeof(buf)/sizeof(buf[0])));
        ASSERT_EQ(ENOMEM, errno);
    }
    fclose(fp);
}
#endif

#ifdef HAVE_TMPFILE
TEST(stdio,tmpfile)
{
    tmpfile_failable_by__(EEXIST)
    {
        ASSERT_EQ(NULL, std::tmpfile());
        ASSERT_EQ(EEXIST, errno);
    }
}
#endif

#ifdef HAVE_TMPNAM
TEST(stdio,tmpnam)
{
    tmpnam_failable__
    {
        char buf[1024];
        ASSERT_EQ(NULL, std::tmpnam(buf));
    }
}
#endif
