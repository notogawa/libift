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
#ifndef IFT_SOCKET_HPP
#define IFT_SOCKET_HPP

#include "ift/incremental_failable.hpp"

#define socket_failable_by__(E) incremental_failable__(socket, E)
#define socketpair_failable_by__(E) incremental_failable__(socketpair, E)
#define bind_failable_by__(E) incremental_failable__(bind, E)
#define getsockname_failable_by__(E) incremental_failable__(getsockname, E)
#define connect_failable_by__(E) incremental_failable__(connect, E)
#define getpeername_failable_by__(E) incremental_failable__(getpeername, E)
#define send_failable_by__(E) incremental_failable__(send, E)
#define recv_failable_by__(E) incremental_failable__(recv, E)
#define sendto_failable_by__(E) incremental_failable__(sendto, E)
#define recvfrom_failable_by__(E) incremental_failable__(recvfrom, E)
#define sendmsg_failable_by__(E) incremental_failable__(sendmsg, E)
#define recvmsg_failable_by__(E) incremental_failable__(recvmsg, E)
#define getsockopt_failable_by__(E) incremental_failable__(getsockopt, E)
#define setsockopt_failable_by__(E) incremental_failable__(setsockopt, E)
#define listen_failable_by__(E) incremental_failable__(listen, E)
#define accept_failable_by__(E) incremental_failable__(accept, E)
#define accept4_failable_by__(E) incremental_failable__(accept4, E)
#define shutdown_failable_by__(E) incremental_failable__(shutdown, E)
#define sockatmark_failable_by__(E) incremental_failable__(sockatmark, E)
#define isfdtype_failable__ incremental_failable__(isfdtype, EBADF)

#endif
