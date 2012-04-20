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
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <cerrno>
#include "ift/sys/socket.hpp"

#ifdef HAVE_SOCKET
TEST(socket,socket)
{
    socket_failable_by__(EAFNOSUPPORT)
    {
        ASSERT_EQ(-1, socket(AF_INET, SOCK_STREAM, 0));
        ASSERT_EQ(EAFNOSUPPORT, errno);
    }
}
#endif

#ifdef HAVE_SOCKETPAIR
TEST(socket,socketpair)
{
    socketpair_failable_by__(EAFNOSUPPORT)
    {
        int fds[2] = {0,0};
        ASSERT_EQ(-1, socketpair(AF_INET, SOCK_STREAM, 0, fds));
        ASSERT_EQ(EAFNOSUPPORT, errno);
    }
}
#endif

#ifdef HAVE_BIND
TEST(socket,bind)
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    bind_failable_by__(EACCES)
    {
        struct sockaddr_in addr;
        addr.sin_port = htons(12345);
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = htonl(INADDR_ANY);
        ASSERT_EQ(-1, bind(sockfd, (struct sockaddr*)&addr, sizeof(addr)));
        ASSERT_EQ(EACCES, errno);
    }
    close(sockfd);
}
#endif

#ifdef HAVE_GETSOCKNAME
TEST(socket,getsockname)
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    getsockname_failable_by__(ENOBUFS)
    {
        struct sockaddr_in addr;
        socklen_t addrlen = 0;
        ASSERT_EQ(-1, getsockname(sockfd, (struct sockaddr*)&addr, &addrlen));
        ASSERT_EQ(ENOBUFS, errno);
    }
    close(sockfd);
}
#endif

#ifdef HAVE_CONNECT
TEST(socket,connect)
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    connect_failable_by__(EALREADY)
    {
        struct sockaddr_in addr;
        addr.sin_port = htons(12345);
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = inet_addr("127.0.0.1");
        ASSERT_EQ(-1, connect(sockfd, (struct sockaddr*)&addr, sizeof(addr)));
        ASSERT_EQ(EALREADY, errno);
    }
    close(sockfd);
}
#endif

#ifdef HAVE_GETPEERNAME
TEST(socket,getpeername)
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    getpeername_failable_by__(ENOTSOCK)
    {
        struct sockaddr_in addr;
        socklen_t addrlen = 0;
        ASSERT_EQ(-1, getpeername(sockfd, (struct sockaddr*)&addr, &addrlen));
        ASSERT_EQ(ENOTSOCK, errno);
    }
    close(sockfd);
}
#endif

#ifdef HAVE_SEND
TEST(socket,send)
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    send_failable_by__(ECONNRESET)
    {
        ASSERT_EQ(-1, send(sockfd, NULL, 0, 0));
        ASSERT_EQ(ECONNRESET, errno);
    }
    close(sockfd);
}
#endif

#ifdef HAVE_RECV
TEST(socket,recv)
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    recv_failable_by__(ECONNREFUSED)
    {
        ASSERT_EQ(-1, recv(sockfd, NULL, 0, 0));
        ASSERT_EQ(ECONNREFUSED, errno);
    }
    close(sockfd);
}
#endif

#ifdef HAVE_SENDTO
TEST(socket,sendto)
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    sendto_failable_by__(ECONNRESET)
    {
        struct sockaddr_in addr;
        addr.sin_port = htons(12345);
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = inet_addr("127.0.0.1");
        ASSERT_EQ(-1, sendto(sockfd, NULL, 0, 0,
                             (const struct sockaddr*)&addr, sizeof(addr)));
        ASSERT_EQ(ECONNRESET, errno);
    }
    close(sockfd);
}
#endif

#ifdef HAVE_RECVFROM
TEST(socket,recvfrom)
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    recvfrom_failable_by__(ECONNREFUSED)
    {
        struct sockaddr_in addr;
        addr.sin_port = htons(12345);
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = inet_addr("127.0.0.1");
        socklen_t addrlen = 0;
        ASSERT_EQ(-1, recvfrom(sockfd, NULL, 0, 0,
                               (struct sockaddr*)&addr, &addrlen));
        ASSERT_EQ(ECONNREFUSED, errno);
    }
    close(sockfd);
}
#endif

#ifdef HAVE_SENDMSG
TEST(socket,sendmsg)
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    sendmsg_failable_by__(ECONNRESET)
    {
        struct msghdr msg;
        ASSERT_EQ(-1, sendmsg(sockfd, &msg, 0));
        ASSERT_EQ(ECONNRESET, errno);
    }
    close(sockfd);
}
#endif

#ifdef HAVE_RECVMSG
TEST(socket,recvmsg)
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    recvmsg_failable_by__(ECONNREFUSED)
    {
        struct msghdr msg;
        ASSERT_EQ(-1, recvmsg(sockfd, &msg, 0));
        ASSERT_EQ(ECONNREFUSED, errno);
    }
    close(sockfd);
}
#endif

#ifdef HAVE_GETSOCKOPT
TEST(socket,getsockopt)
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    getsockopt_failable_by__(ENOPROTOOPT)
    {
        int optval = 0;
        socklen_t optlen = 0;
        ASSERT_EQ(-1, getsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR,
                                 &optval, &optlen));
        ASSERT_EQ(ENOPROTOOPT, errno);
    }
    close(sockfd);
}
#endif

#ifdef HAVE_SETSOCKOPT
TEST(socket,setsockopt)
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt_failable_by__(ENOPROTOOPT)
    {
        int optval = 0;
        ASSERT_EQ(-1, setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR,
                                 &optval, sizeof(optval)));
        ASSERT_EQ(ENOPROTOOPT, errno);
    }
    close(sockfd);
}
#endif

#ifdef HAVE_LISTEN
TEST(socket,listen)
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    listen_failable_by__(EADDRINUSE)
    {
        ASSERT_EQ(-1, listen(sockfd, 1));
        ASSERT_EQ(EADDRINUSE, errno);
    }
    close(sockfd);
}
#endif

#ifdef HAVE_ACCEPT
TEST(socket,accept)
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    accept_failable_by__(ECONNABORTED)
    {
        struct sockaddr_in addr;
        socklen_t addrlen = 0;
        ASSERT_EQ(-1, accept(sockfd, (struct sockaddr*)&addr, &addrlen));
        ASSERT_EQ(ECONNABORTED, errno);
    }
    close(sockfd);
}
#endif

#ifdef HAVE_ACCEPT4
TEST(socket,accept4)
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    accept4_failable_by__(ECONNABORTED)
    {
        struct sockaddr_in addr;
        socklen_t addrlen = 0;
        ASSERT_EQ(-1, accept4(sockfd, (struct sockaddr*)&addr, &addrlen,
                              SOCK_CLOEXEC));
        ASSERT_EQ(ECONNABORTED, errno);
    }
    close(sockfd);
}
#endif

#ifdef HAVE_SHUTDOWN
TEST(socket,shutdown)
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    shutdown_failable_by__(ENOTSOCK)
    {
        ASSERT_EQ(-1, shutdown(sockfd, SHUT_RDWR));
        ASSERT_EQ(ENOTSOCK, errno);
    }
    close(sockfd);
}
#endif

#ifdef HAVE_SOCKATMARK
TEST(socket,sockatmark)
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    sockatmark_failable_by__(EBADF)
    {
        ASSERT_EQ(-1, sockatmark(sockfd));
        ASSERT_EQ(EBADF, errno);
    }
    close(sockfd);
}
#endif

#ifdef HAVE_ISFDTYPE
TEST(socket,isfdtype)
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    isfdtype_failable__
    {
        ASSERT_EQ(-1, isfdtype(sockfd, S_IFREG));
        ASSERT_EQ(EBADF, errno);
    }
    close(sockfd);
}
#endif
