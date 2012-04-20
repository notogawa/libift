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
#include <sys/epoll.h>
#include <fcntl.h>
#include <cerrno>
#include "ift/sys/epoll.hpp"

#ifdef HAVE_EPOLL_CREATE
TEST(epoll,epoll_create)
{
    epoll_create_failable_by__(EMFILE)
    {
        ASSERT_EQ(-1, epoll_create(16));
        ASSERT_EQ(EMFILE, errno);
    }
}
#endif

#ifdef HAVE_EPOLL_CREATE1
TEST(epoll,epoll_create1)
{
    epoll_create1_failable_by__(EMFILE)
    {
        ASSERT_EQ(-1, epoll_create1(EPOLL_CLOEXEC));
        ASSERT_EQ(EMFILE, errno);
    }
}
#endif

#ifdef HAVE_EPOLL_CTL
TEST(epoll,epoll_ctl)
{
    int epfd = epoll_create(16);
    int fd = open("/dev/zero", O_WRONLY);
    epoll_ctl_failable_by__(EEXIST)
    {
        struct epoll_event event;
        event.events = EPOLLIN | EPOLLET;
        event.data.fd = fd;
        ASSERT_EQ(-1, epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &event));
        ASSERT_EQ(EEXIST, errno);
    }
    close(fd);
    close(epfd);
}
#endif

#ifdef HAVE_EPOLL_WAIT
TEST(epoll,epoll_wait)
{
    int epfd = epoll_create(16);
    epoll_wait_failable_by__(EINTR)
    {
        struct epoll_event events[16];
        ASSERT_EQ(-1, epoll_wait(epfd, events, 16, 100));
        ASSERT_EQ(EINTR, errno);
    }
    close(epfd);
}
#endif

#ifdef HAVE_EPOLL_PWAIT
TEST(epoll,epoll_pwait)
{
    int epfd = epoll_create(16);
    epoll_pwait_failable_by__(EINTR)
    {
        struct epoll_event events[16];
        sigset_t sigmask;
        ASSERT_EQ(-1, epoll_pwait(epfd, events, 16, 100, &sigmask));
        ASSERT_EQ(EINTR, errno);
    }
    close(epfd);
}
#endif
