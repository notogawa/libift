/*
  Copyright (c) 2012, Noriyuki OHKAWA a.k.a. notogawa.
  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:

  * Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.

  * Redistributions in binary form must reproduce the above
    copyright notice, this list of conditions and the following
    disclaimer in the documentation and/or other materials provided
    with the distribution.

  * Neither the name of Noriyuki OHKAWA and notogawa nor the names of other
    contributors may be used to endorse or promote products derived
    from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sample.h"

int sample_malloc_function()
{
    void* p = NULL;
    void* q = NULL;
    p = malloc(10);
    if (NULL == p) return 1;
    q = malloc(10);
    if (NULL == q)
    {
        free(p);
        return 2;
    }
    free(p);
    free(q);
    return 0;
}

int sample_fopen_function()
{
    FILE* p = NULL;
    FILE* q = NULL;
    p = fopen("/dev/null", "w");
    if (NULL == p) {
        perror("fopen()");
        return 1;
    }
    q = fopen("/dev/null", "w");
    if (NULL == q)
    {
        perror("fopen()");
        fclose(p);
        return 2;
    }
    fclose(p);
    fclose(q);
    return 0;
}

int sample_printf_function()
{
    return printf("%s:%d:%s: sample\n",__FILE__,__LINE__,__FUNCTION__);
}
