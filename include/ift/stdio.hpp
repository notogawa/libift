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
#ifndef IFT_STDIO_HPP
#define IFT_STDIO_HPP

#include "ift/incremental_failable.hpp"

#define fopen_failable_by__(E) incremental_failable__(fopen, E)
#define fdopen_failable_by__(E) incremental_failable__(fdopen, E)
#define freopen_failable_by__(E) incremental_failable__(freopen, E)
#define fclose_failable_by__(E) incremental_failable__(fclose, E)
#define fgetc_failable__ incremental_failable__(fgetc, 0)
#define fgets_failable__ incremental_failable__(fgets ,0)
#define getc_failable__ incremental_failable__(getc, 0)
#define getchar_failable__ incremental_failable__(getchar, 0)
#define gets_failable__ incremental_failable__(gets, 0)
#define ungetc_failable__ incremental_failable__(ungetc, 0)
#define printf_failable__ incremental_failable__(printf, 0)
#define fprintf_failable__ incremental_failable__(fprintf, 0)
#define sprintf_failable__ incremental_failable__(sprintf, 0)
#define snprintf_failable__ incremental_failable__(snprintf, 0)
#define fputc_failable__ incremental_failable__(fputc, 0)
#define fputs_failable__ incremental_failable__(fputs, 0)
#define putchar_failable__ incremental_failable__(putchar, 0)
#define puts_failable__ incremental_failable__(puts, 0)
#define fread_failable__ incremental_failable__(fread, 0)
#define fwrite_failable__ incremental_failable__(fwrite, 0)
#define scanf_failable_by__(E) incremental_failable__(scanf, E)
#define fscanf_failable_by__(E) incremental_failable__(fscanf, E)
#define sscanf_failable_by__(E) incremental_failable__(sscanf, E)
#define fseek_failable_by__(E) incremental_failable__(fseek, E)
#define ftell_failable_by__(E) incremental_failable__(ftell, E)
#define fgetpos_failable_by__(E) incremental_failable__(fgetpos, E)
#define fsetpos_failable_by__(E) incremental_failable__(fsetpos, E)
#define remove_failable_by__(E) incremental_failable__(remove, E)
#define rename_failable_by__(E) incremental_failable__(rename, E)
#define setvbuf_failable_by__(E) incremental_failable__(setvbuf, E)
#define tmpfile_failable_by__(E) incremental_failable__(tmpfile, E)
#define tmpnam_failable__ incremental_failable__(tmpnam, 0)

#endif
