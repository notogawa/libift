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
#ifndef IFT_BASIC_IMPL_HPP
#define IFT_BASIC_IMPL_HPP

#include <set>
#include <dlfcn.h>
#include <cerrno>
#include "cdecls.hpp"
#include "scoped_global_lock.hpp"

#define IFT_BASIC_IMPL(RTYPE, NAME, ATYPES, RETURN, ARGS, CALL, THROW)  \
    typedef RTYPE (*function_t)ATYPES;                                  \
                                                                        \
    namespace {                                                         \
                                                                        \
    __thread bool ____ifs_##NAME##_locked = true;                       \
    __thread int ____ifs_##NAME##_errno = 0;                            \
    function_t ____ifs_##NAME##_orig;                                   \
                                                                        \
    void __attribute__((constructor)) ____ift_save_##NAME()             \
    {                                                                   \
        union {                                                         \
            function_t value;                                           \
            void* as_pvoid;                                             \
        } func;                                                         \
        func.as_pvoid = dlsym(RTLD_NEXT, #NAME);                        \
        ____ifs_##NAME##_orig = func.value;                             \
    }                                                                   \
                                                                        \
    }                                                                   \
                                                                        \
    BEGIN_C_DECLS                                                       \
                                                                        \
    void ____ift_##NAME##_test(bool enable, int error)                  \
    {                                                                   \
        ____ifs_##NAME##_locked = !enable;                              \
        ____ifs_##NAME##_errno = ____ifs_##NAME##_locked ? 0 : error;   \
    }                                                                   \
                                                                        \
    RTYPE NAME ARGS THROW                                               \
    {                                                                   \
        if (____ifs_##NAME##_locked ||                                  \
            ift::scoped_global_lock::locked())                          \
            return ____ifs_##NAME##_orig CALL;                          \
        ift::scoped_global_lock ____ifs_glock;                          \
        void* ____ifs_addr = __builtin_return_address(0);               \
        std::pair< void*, int >                                         \
            occur(____ifs_addr, ____ifs_##NAME##_errno);                \
        static std::set< std::pair< void*, int > > ____ifs_history;     \
        if (____ifs_history.find(occur) != ____ifs_history.end())       \
            return ____ifs_##NAME##_orig CALL;                          \
        ____ifs_history.insert(occur);                                  \
        errno = ____ifs_##NAME##_errno;                                 \
        return RETURN;                                                  \
    }                                                                   \
                                                                        \
    END_C_DECLS

#endif
