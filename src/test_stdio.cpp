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
#include <gtest/gtest.h>
#include <fcntl.h>
#include "ift/stdio.hpp"

TEST(stdio,fopen)
{
    fopen_failable_by__(ENOMEM)
    {
        ASSERT_EQ(NULL, fopen("/dev/null", "w"));
        ASSERT_EQ(ENOMEM, errno);
    }
}

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

TEST(stdio,freopen)
{
    FILE* fp = tmpfile();
    freopen_failable_by__(ENOMEM)
    {
        ASSERT_EQ(NULL, freopen("/dev/null", "w", fp));
        ASSERT_EQ(ENOMEM, errno);
    }
    fclose(fp);
}

TEST(stdio,fclose)
{
    FILE* fp = tmpfile();
    fclose_failable_by__(EIO)
    {
        ASSERT_EQ(-1, fclose(fp));
        ASSERT_EQ(EIO, errno);
    }
    fclose(fp);
}

TEST(stdio,fgetc)
{
    FILE* fp = tmpfile();
    fgetc_failable__
    {
        ASSERT_EQ(EOF, fgetc(fp));
    }
    fclose(fp);
}

TEST(stdio,fgets)
{
    FILE* fp = tmpfile();
    fgets_failable__
    {
        char buf[1024];
        ASSERT_EQ(NULL, fgets(buf, sizeof(buf)/sizeof(buf[0]), fp));
    }
    fclose(fp);
}

TEST(stdio,getc)
{
    FILE* fp = tmpfile();
    getc_failable__
    {
        ASSERT_EQ(EOF, getc(fp));
    }
    fclose(fp);
}

TEST(stdio,getchar)
{
    getchar_failable__
    {
        ASSERT_EQ(EOF, getchar());
    }
}

TEST(stdio,gets)
{
    gets_failable__
    {
        char buf[1024];
        ASSERT_EQ(NULL, gets(buf));
    }
}

TEST(stdio,ungetc)
{
    FILE* fp = tmpfile();
    ungetc_failable__
    {
        ASSERT_EQ(EOF, ungetc(10, fp));
    }
    fclose(fp);
}

TEST(stdio,printf)
{
    printf_failable__
    {
        ASSERT_GT(0, printf("test\n"));
    }
}

TEST(stdio,fprintf)
{
    FILE* fp = tmpfile();
    fprintf_failable__
    {
        ASSERT_GT(0, fprintf(fp, "test\n"));
    }
    fclose(fp);
}

TEST(stdio,sprintf)
{
    sprintf_failable__
    {
        char buf[1024];
        ASSERT_GT(0, sprintf(buf, "test\n"));
    }
}

TEST(stdio,snprintf)
{
    snprintf_failable__
    {
        char buf[1024];
        ASSERT_GT(0, snprintf(buf, 2, "test\n"));
    }
}

TEST(stdio,fputc)
{
    FILE* fp = tmpfile();
    fputc_failable__
    {
        ASSERT_EQ(EOF, fputc(10, fp));
    }
    fclose(fp);
}

TEST(stdio,fputs)
{
    FILE* fp = tmpfile();
    fputs_failable__
    {
        ASSERT_EQ(EOF, fputs("test", fp));
    }
    fclose(fp);
}

TEST(stdio,putchar)
{
    putchar_failable__
    {
        ASSERT_EQ(EOF, putchar(10));
    }
}

TEST(stdio,puts)
{
    puts_failable__
    {
        ASSERT_EQ(EOF, puts("test"));
    }
}

TEST(stdio,fread)
{
    FILE* fp = tmpfile();
    fread_failable__
    {
        ASSERT_EQ(0U, fread(NULL, 10, 10, fp));
    }
    fclose(fp);
}

TEST(stdio,fwrite)
{
    FILE* fp = tmpfile();
    fwrite_failable__
    {
        ASSERT_EQ(0U, fwrite(NULL, 10, 10, fp));
    }
    fclose(fp);
}

TEST(stdio,scanf)
{
    scanf_failable_by__(ERANGE)
    {
        int n = 0;
        ASSERT_EQ(EOF, scanf("%d", &n));
        ASSERT_EQ(ERANGE, errno);
    }
}

TEST(stdio,fscanf)
{
    FILE* fp = tmpfile();
    fscanf_failable_by__(EBADF)
    {
        int n = 0;
        ASSERT_EQ(EOF, fscanf(fp, "%d", &n));
        ASSERT_EQ(EBADF, errno);
    }
    fclose(fp);
}

TEST(stdio,sscanf)
{
    sscanf_failable_by__(ENOMEM)
    {
        int n = 0;
        ASSERT_EQ(EOF, sscanf("12", "%d", &n));
        ASSERT_EQ(ENOMEM, errno);
    }
}

TEST(stdio,fseek)
{
    FILE* fp = tmpfile();
    fseek_failable_by__(EBADF)
    {
        ASSERT_EQ(-1, fseek(fp, 0, SEEK_SET));
        ASSERT_EQ(EBADF, errno);
    }
    fclose(fp);
}

TEST(stdio,ftell)
{
    FILE* fp = tmpfile();
    ftell_failable_by__(EBADF)
    {
        ASSERT_EQ(-1, ftell(fp));
        ASSERT_EQ(EBADF, errno);
    }
    fclose(fp);
}

TEST(stdio,fgetpos)
{
    FILE* fp = tmpfile();
    fgetpos_failable_by__(EBADF)
    {
        fpos_t pos;
        ASSERT_EQ(-1, fgetpos(fp, &pos));
        ASSERT_EQ(EBADF, errno);
    }
    fclose(fp);
}

TEST(stdio,fsetpos)
{
    FILE* fp = tmpfile();
    fsetpos_failable_by__(EBADF)
    {
        fpos_t pos;
        ASSERT_EQ(0, fgetpos(fp, &pos));
        ASSERT_EQ(-1, fsetpos(fp, &pos));
        ASSERT_EQ(EBADF, errno);
    }
    fclose(fp);
}

TEST(stdio,remove)
{
    remove_failable_by__(EACCES)
    {
        ASSERT_EQ(-1, remove("/tmp/foo"));
        ASSERT_EQ(EACCES, errno);
    }
}

TEST(stdio,rename)
{
    rename_failable_by__(EACCES)
    {
        ASSERT_EQ(-1, rename("/tmp/foo", "/tmp/bar"));
        ASSERT_EQ(EACCES, errno);
    }
}

TEST(stdio,setvbuf)
{
    FILE* fp = tmpfile();
    setvbuf_failable_by__(ENOMEM)
    {
        char buf[1024];
        ASSERT_EQ(-1, setvbuf(fp, buf, _IOLBF, sizeof(buf)/sizeof(buf[0])));
        ASSERT_EQ(ENOMEM, errno);
    }
    fclose(fp);
}

TEST(stdio,tmpfile)
{
    tmpfile_failable_by__(EEXIST)
    {
        ASSERT_EQ(NULL, tmpfile());
        ASSERT_EQ(EEXIST, errno);
    }
}

TEST(stdio,tmpnam)
{
    tmpnam_failable__
    {
        char buf[1024];
        ASSERT_EQ(NULL, tmpnam(buf));
    }
}
