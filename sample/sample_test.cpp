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
#include <iostream>
#include <cstdlib>
#include <cerrno>
#include <cstring>
#include <gtest/gtest.h>
#include "ift/stdio.hpp"
#include "ift/stdlib.hpp"

#include "sample.h"

TEST(SampleTest,malloc)
{
    ASSERT_EQ(0, sample_malloc_function());
    malloc_failable__
    {
        ASSERT_EQ(1, sample_malloc_function());
        ASSERT_EQ(2, sample_malloc_function());
        ASSERT_EQ(0, sample_malloc_function());
    }
    ASSERT_EQ(0, sample_malloc_function());
    malloc_failable__
    {
        ASSERT_EQ(0, sample_malloc_function());
        ASSERT_EQ(0, sample_malloc_function());
        ASSERT_EQ(0, sample_malloc_function());
    }
    ASSERT_EQ(0, sample_malloc_function());
}

TEST(SampleTest,fopen)
{
    ASSERT_EQ(0, sample_fopen_function());
    malloc_failable__ fopen_failable_by__(ENOMEM)
    {
        ASSERT_EQ(1, sample_fopen_function());
        ASSERT_EQ(2, sample_fopen_function());
        ASSERT_EQ(0, sample_fopen_function());
    }
    ASSERT_EQ(0, sample_fopen_function());
    fopen_failable_by__(ENOMEM)
    {
        ASSERT_EQ(0, sample_fopen_function());
        ASSERT_EQ(0, sample_fopen_function());
        ASSERT_EQ(0, sample_fopen_function());
    }
    ASSERT_EQ(0, sample_fopen_function());
}

TEST(SampleTest,printf)
{
    ASSERT_LE(0, sample_printf_function());
    printf_failable__ puts_failable__
    {
        ASSERT_EQ(-1, sample_printf_function());
    }
    ASSERT_LE(0, sample_printf_function());
    printf_failable__ puts_failable__
    {
        ASSERT_LE(0, sample_printf_function());
    }
    ASSERT_LE(0, sample_printf_function());
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
