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
#include <cstdarg>
#include "ift/stdarg.hpp"

namespace {

void test_vprintf(int a, ...)
{
    va_list argptr;
    va_start(argptr, a);
    ASSERT_GT(0, std::vprintf("test\n", argptr));
    va_end(argptr);
}

void test_vfprintf(int a, ...)
{
    FILE* fp = std::tmpfile();
    va_list argptr;
    va_start(argptr, a);
    ASSERT_GT(0, std::vfprintf(fp, "test\n", argptr));
    va_end(argptr);
    fclose(fp);
}

void test_vsprintf(int a, ...)
{
    char buf[1024];
    va_list argptr;
    va_start(argptr, a);
    ASSERT_GT(0, std::vsprintf(buf, "test\n", argptr));
    va_end(argptr);
}

void test_vsnprintf(int a, ...)
{
    char buf[1024];
    va_list argptr;
    va_start(argptr, a);
    ASSERT_GT(0, std::vsnprintf(buf, 2, "test\n", argptr));
    va_end(argptr);
}

void test_vscanf(int a, ...)
{
    va_list argptr;
    va_start(argptr, a);
    ASSERT_EQ(EOF, std::vscanf("%d", argptr));
    ASSERT_EQ(ERANGE, errno);
    va_end(argptr);
}

void test_vfscanf(int a, ...)
{
    FILE* fp = std::tmpfile();
    va_list argptr;
    va_start(argptr, a);
    ASSERT_EQ(EOF, std::vfscanf(fp, "%d", argptr));
    ASSERT_EQ(EBADF, errno);
    va_end(argptr);
    fclose(fp);
}

void test_vsscanf(int a, ...)
{
    va_list argptr;
    va_start(argptr, a);
    ASSERT_EQ(EOF, std::vsscanf("12", "%d", argptr));
    ASSERT_EQ(ENOMEM, errno);
    va_end(argptr);
}

} // anonymous namespace

TEST(stdarg,vprintf)
{
    vprintf_failable__
    {
        test_vprintf(0);
    }
}

TEST(stdarg,vfprintf)
{
    vfprintf_failable__
    {
        test_vfprintf(0);
    }
}

TEST(stdarg,vsprintf)
{
    vsprintf_failable__
    {
        test_vsprintf(0);
    }
}

TEST(stdarg,vsnprintf)
{
    vsnprintf_failable__
    {
        test_vsnprintf(0);
    }
}

TEST(stdarg,vscanf)
{
    vscanf_failable_by__(ERANGE)
    {
        test_vscanf(0);
    }
}

TEST(stdarg,vfscanf)
{
    vfscanf_failable_by__(EBADF)
    {
        test_vfscanf(0);
    }
}

TEST(stdarg,vsscanf)
{
    vsscanf_failable_by__(ENOMEM)
    {
        test_vsscanf(0);
    }
}
