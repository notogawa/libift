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
#include <cstdlib>
#include "basic_impl.hpp"
//IFT_BASIC_IMPL(void*, calloc, (size_t, size_t),
//               NULL, (size_t nmemb, size_t size), (nmemb, size), throw ())

// see http://blog.bigpixel.ro/2010/09/interposing-calloc-on-linux/

typedef void* (*function_t)(size_t, size_t);

namespace {

__thread bool ____ifs_locked = true;
__thread int ____ifs_errno = 0;

// our temporary calloc used until we get the address of libc provided
// one in our interposed calloc
void* temporary_calloc(size_t nmemb, size_t size)
{
    return NULL;
}

// before trying to get the libc provided
// calloc, set the calloc function to the temporary
// one returning NULL.
function_t ____ifs_calloc_orig = temporary_calloc;

void __attribute__((constructor)) ____ift_save_calloc()
{
    union {
        function_t value;
        void* as_pvoid;
    } func;
    func.as_pvoid = dlsym(RTLD_NEXT, "calloc");
    ____ifs_calloc_orig = func.value;
}

}

BEGIN_C_DECLS

void ____ift_calloc_test(bool enable, int error)
{
    ____ifs_locked = !enable;
    ____ifs_errno = ____ifs_locked ? 0 : error;
}

void* calloc (size_t nmemb, size_t size)
{
    if (____ifs_locked || ift::scoped_global_lock::locked())
        return ____ifs_calloc_orig (nmemb, size);
    ift::scoped_global_lock ____ifs_glock;
    void* ____ifs_addr = __builtin_return_address(0);
    std::pair< void*, int > occur(____ifs_addr, ____ifs_errno);
    static std::set< std::pair< void*, int > > ____ifs_history;
    if (____ifs_history.find(occur) != ____ifs_history.end())
        return ____ifs_calloc_orig (nmemb, size);
    ____ifs_history.insert(occur);
    errno = ____ifs_errno;
    return NULL;
}

END_C_DECLS
