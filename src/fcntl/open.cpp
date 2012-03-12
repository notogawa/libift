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
#include <fcntl.h>
#include <cstdarg>
#include <set>
#include <dlfcn.h>
#include <cerrno>
#include "cdecls.hpp"
#include "scoped_global_lock.hpp"

typedef int (*function_t)(const char*, int, ...);

namespace {

__thread bool ____ifs_open_locked = true;
__thread int ____ifs_open_errno = 0;
function_t ____ifs_open_orig;

void __attribute__((constructor)) ____ift_save_open()
{
    union {
        function_t value;
        void* as_pvoid;
    } func;
    func.as_pvoid = dlsym(RTLD_NEXT, "open");
    ____ifs_open_orig = func.value;
}

}

BEGIN_C_DECLS

void ____ift_open_test(bool enable, int error)
{
    ____ifs_open_locked = !enable;
    ____ifs_open_errno = ____ifs_open_locked ? 0 : error;
}

int open (const char *pathname, int flags, ...)
{
    if (____ifs_open_locked ||
        ift::scoped_global_lock::locked())
    {
        va_list argptr;
        va_start(argptr, flags);
        mode_t mode = (mode_t)va_arg(argptr, mode_t);
        int result = ____ifs_open_orig(pathname, flags, mode);
        va_end(argptr);
        return result;
    }
    ift::scoped_global_lock ____ifs_glock;
    void* ____ifs_addr = __builtin_return_address(0);
    std::pair< void*, int >
        occur(____ifs_addr, ____ifs_open_errno);
    static std::set< std::pair< void*, int > > ____ifs_history;
    if (____ifs_history.find(occur) != ____ifs_history.end())
    {
        va_list argptr;
        va_start(argptr, flags);
        mode_t mode = (mode_t)va_arg(argptr, mode_t);
        int result = ____ifs_open_orig(pathname, flags, mode);
        va_end(argptr);
        return result;
    }
    ____ifs_history.insert(occur);
    errno = ____ifs_open_errno;
    return -1;
}

END_C_DECLS
