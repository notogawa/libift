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
#include "config.h"
#include <gtest/gtest.h>
#include <cstdlib>
#include <cerrno>
#include "ift/stdlib.hpp"

#ifdef HAVE_MALLOC
TEST(stdlib,malloc)
{
    malloc_failable__
    {
        ASSERT_EQ(NULL, std::malloc(10));
        ASSERT_EQ(ENOMEM, errno);
    }
}
#endif

#ifdef HAVE_CALLOC
TEST(stdlib,calloc)
{
    calloc_failable__
    {
        ASSERT_EQ(NULL, std::calloc(10, 10));
        ASSERT_EQ(ENOMEM, errno);
    }
}
#endif

#ifdef HAVE_REALLOC
TEST(stdlib,realloc)
{
    void* p = malloc(10);
    realloc_failable__
    {
        ASSERT_EQ(NULL, std::realloc(p, 20));
        ASSERT_EQ(ENOMEM, errno);
    }
    free(p);
}
#endif

#ifdef HAVE_GETENV
TEST(stdlib,getenv)
{
    getenv_failable__
    {
        ASSERT_EQ(NULL, std::getenv("LD_PRELOAD"));
    }
}
#endif

#ifdef HAVE_SYSTEM
TEST(stdlib,system)
{
    system_failable__
    {
        ASSERT_EQ(-1, std::system("echo OK"));
    }
}
#endif

#ifdef HAVE_POSIX_MEMALIGN
TEST(stdlib,posix_memalign)
{
    posix_memalign_failable_by__(ENOMEM)
    {
        void* p = NULL;
        ASSERT_EQ(ENOMEM, posix_memalign(&p, sizeof(void*)*2, 10));
    }
}
#endif
