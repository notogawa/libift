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
#include <gtest/gtest.h>
#include <unistd.h>
#include <fcntl.h>
#include <cerrno>
#include "ift/unistd.hpp"

TEST(unistd,access)
{
    access_failable_by__(EACCES)
    {
        ASSERT_EQ(-1, access("/dev/zero", X_OK));
        ASSERT_EQ(EACCES, errno);
    }
}

TEST(unistd,euidaccess)
{
    euidaccess_failable_by__(EACCES)
    {
        ASSERT_EQ(-1, euidaccess("/dev/zero", X_OK));
        ASSERT_EQ(EACCES, errno);
    }
}

TEST(unistd,eaccess)
{
    eaccess_failable_by__(EACCES)
    {
        ASSERT_EQ(-1, eaccess("/dev/zero", X_OK));
        ASSERT_EQ(EACCES, errno);
    }
}

TEST(unistd,faccessat)
{
    int dirfd = open("/tmp", O_RDWR);
    faccessat_failable_by__(ENOTDIR)
    {
        ASSERT_EQ(-1, faccessat(dirfd, "/dev/zero", X_OK, AT_SYMLINK_NOFOLLOW));
        ASSERT_EQ(ENOTDIR, errno);
    }
    close(dirfd);
}

TEST(unistd,lseek)
{
    int fd = open("/tmp/test", O_RDWR);
    lseek_failable_by__(EBADF)
    {
        ASSERT_EQ(-1, lseek(fd, 0, SEEK_SET));
        ASSERT_EQ(EBADF, errno);
    }
    close(fd);
}

TEST(unistd,close)
{
    int fd = open("/tmp/test", O_RDWR);
    close_failable_by__(EIO)
    {
        ASSERT_EQ(-1, close(fd));
        ASSERT_EQ(EIO, errno);
    }
    close(fd);
}

TEST(unistd,read)
{
    int fd = open("/tmp/test", O_RDWR);
    read_failable_by__(EIO)
    {
        char buf[1024];
        ASSERT_EQ(-1, read(fd, buf, sizeof(buf)/sizeof(buf[0])));
        ASSERT_EQ(EIO, errno);
    }
    close(fd);
}

TEST(unistd,write)
{
    int fd = open("/tmp/test", O_RDWR);
    write_failable_by__(EIO)
    {
        char buf[1024];
        ASSERT_EQ(-1, write(fd, buf, sizeof(buf)/sizeof(buf[0])));
        ASSERT_EQ(EIO, errno);
    }
    close(fd);
}

TEST(unistd,pread)
{
    int fd = open("/tmp/test", O_RDWR);
    pread_failable_by__(EIO)
    {
        char buf[1024];
        ASSERT_EQ(-1, pread(fd, buf, sizeof(buf)/sizeof(buf[0]), 0));
        ASSERT_EQ(EIO, errno);
    }
    close(fd);
}

TEST(unistd,pwrite)
{
    int fd = open("/tmp/test", O_RDWR);
    pwrite_failable_by__(EIO)
    {
        char buf[1024];
        ASSERT_EQ(-1, pwrite(fd, buf, sizeof(buf)/sizeof(buf[0]), 0));
        ASSERT_EQ(EIO, errno);
    }
    close(fd);
}

TEST(unistd,pipe)
{
    pipe_failable_by__(EMFILE)
    {
        int pipefd[2];
        ASSERT_EQ(-1, pipe(pipefd));
        ASSERT_EQ(EMFILE, errno);
    }
}

TEST(unistd,pipe2)
{
    pipe2_failable_by__(EMFILE)
    {
        int pipefd[2];
        ASSERT_EQ(-1, pipe2(pipefd, O_CLOEXEC));
        ASSERT_EQ(EMFILE, errno);
    }
}

TEST(unistd,usleep)
{
    usleep_failable_by__(EINTR)
    {
        ASSERT_EQ(-1, usleep(1000));
        ASSERT_EQ(EINTR, errno);
    }
}

TEST(unistd,pause)
{
    pause_failable__
    {
        ASSERT_EQ(-1, pause());
        ASSERT_EQ(EINTR, errno);
    }
}

TEST(unistd,chown)
{
    chown_failable_by__(ENOENT)
    {
        ASSERT_EQ(-1, chown("/tmp/test", 0, 0));
        ASSERT_EQ(ENOENT, errno);
    }
}

TEST(unistd,fchown)
{
    int fd = open("/tmp/test", O_RDWR);
    fchown_failable_by__(ENOENT)
    {
        ASSERT_EQ(-1, fchown(fd, 0, 0));
        ASSERT_EQ(ENOENT, errno);
    }
    close(fd);
}

TEST(unistd,lchown)
{
    lchown_failable_by__(ENOENT)
    {
        ASSERT_EQ(-1, lchown("/tmp/test", 0, 0));
        ASSERT_EQ(ENOENT, errno);
    }
}

TEST(unistd,fchownat)
{
    int dirfd = open("/tmp", O_RDWR);
    fchownat_failable_by__(ENOENT)
    {
        ASSERT_EQ(-1, fchownat(dirfd, "/tmp/test", 0, 0, AT_SYMLINK_NOFOLLOW));
        ASSERT_EQ(ENOENT, errno);
    }
    close(dirfd);
}

TEST(unistd,chdir)
{
    chdir_failable_by__(EIO)
    {
        ASSERT_EQ(-1, chdir("/tmp"));
        ASSERT_EQ(EIO, errno);
    }
}

TEST(unistd,fchdir)
{
    int dirfd = open("/tmp", O_RDWR);
    fchdir_failable_by__(EACCES)
    {
        ASSERT_EQ(-1, fchdir(dirfd));
        ASSERT_EQ(EACCES, errno);
    }
    close(dirfd);
}

TEST(unistd,getcwd)
{
    getcwd_failable_by__(EACCES)
    {
        char buf[1024];
        ASSERT_EQ(NULL, getcwd(buf, sizeof(buf)/sizeof(buf[0])));
        ASSERT_EQ(EACCES, errno);
    }
}

TEST(unistd,get_current_dir_name)
{
    get_current_dir_name_failable_by__(ENOMEM)
    {
        ASSERT_EQ(NULL, get_current_dir_name());
        ASSERT_EQ(ENOMEM, errno);
    }
}

TEST(unistd,dup)
{
    int fd = open("/tmp/test", O_RDWR);
    dup_failable_by__(EMFILE)
    {
        ASSERT_EQ(-1, dup(fd));
        ASSERT_EQ(EMFILE, errno);
    }
    close(fd);
}

TEST(unistd,dup2)
{
    int fd = open("/tmp/test", O_RDWR);
    dup2_failable_by__(EMFILE)
    {
        int newfd = 0;
        ASSERT_EQ(-1, dup2(fd, newfd));
        ASSERT_EQ(EMFILE, errno);
    }
    close(fd);
}

TEST(unistd,dup3)
{
    int fd = open("/tmp/test", O_RDWR);
    dup3_failable_by__(EMFILE)
    {
        int newfd = 0;
        ASSERT_EQ(-1, dup3(fd, newfd, O_CLOEXEC));
        ASSERT_EQ(EMFILE, errno);
    }
    close(fd);
}

TEST(unistd,execve)
{
    execve_failable_by__(E2BIG)
    {
        char* const argv[] = {NULL};
        char* const envp[] = {NULL};
        ASSERT_EQ(-1, execve("/bin/ls", argv, envp));
        ASSERT_EQ(E2BIG, errno);
    }
}

TEST(unistd,fexecve)
{
    int fd = open("/bin/ls", O_RDONLY);
    fexecve_failable_by__(E2BIG)
    {
        char* const argv[] = {NULL};
        char* const envp[] = {NULL};
        ASSERT_EQ(-1, fexecve(fd, argv, envp));
        ASSERT_EQ(E2BIG, errno);
    }
    close(fd);
}

TEST(unistd,execv)
{
    execv_failable_by__(E2BIG)
    {
        char* const argv[] = {NULL};
        ASSERT_EQ(-1, execv("/bin/ls", argv));
        ASSERT_EQ(E2BIG, errno);
    }
}

TEST(unistd,execvp)
{
    execvp_failable_by__(E2BIG)
    {
        char* const argv[] = {NULL};
        ASSERT_EQ(-1, execvp("ls", argv));
        ASSERT_EQ(E2BIG, errno);
    }
}

TEST(unistd,execvpe)
{
    execvpe_failable_by__(E2BIG)
    {
        char* const argv[] = {NULL};
        char* const envp[] = {NULL};
        ASSERT_EQ(-1, execvpe("ls", argv, envp));
        ASSERT_EQ(E2BIG, errno);
    }
}

TEST(unistd,nice)
{
    nice_failable__
    {
        ASSERT_EQ(-1, nice(0));
        ASSERT_EQ(EPERM, errno);
    }
}

TEST(unistd,pathconf)
{
    pathconf_failable_by__(EPERM)
    {
        ASSERT_EQ(-1, pathconf("/tmp/test", _PC_LINK_MAX));
        ASSERT_EQ(EPERM, errno);
    }
}

TEST(unistd,fpathconf)
{
    int fd = open("/tmp/test", O_RDWR);
    fpathconf_failable_by__(EPERM)
    {
        ASSERT_EQ(-1, fpathconf(fd, _PC_LINK_MAX));
        ASSERT_EQ(EPERM, errno);
    }
    close(fd);
}

TEST(unistd,sysconf)
{
    sysconf_failable__
    {
        ASSERT_EQ(-1, sysconf(_SC_PAGESIZE));
        ASSERT_EQ(EINVAL, errno);
    }
}

TEST(unistd,getpgid)
{
    getpgid_failable_by__(ESRCH)
    {
        ASSERT_EQ(-1, getpgid(0));
        ASSERT_EQ(ESRCH, errno);
    }
}

TEST(unistd,setpgid)
{
    setpgid_failable_by__(EACCES)
    {
        ASSERT_EQ(-1, setpgid(0, 0));
        ASSERT_EQ(EACCES, errno);
    }
}

TEST(unistd,setpgrp)
{
    setpgrp_failable_by__(EACCES)
    {
        ASSERT_EQ(-1, setpgrp());
        ASSERT_EQ(EACCES, errno);
    }
}

TEST(unistd,setsid)
{
    setsid_failable__
    {
        ASSERT_EQ(-1, setsid());
        ASSERT_EQ(EPERM, errno);
    }
}

TEST(unistd,getsid)
{
    getsid_failable_by__(ESRCH)
    {
        ASSERT_EQ(-1, getsid(0));
        ASSERT_EQ(ESRCH, errno);
    }
}

TEST(unistd,getgroups)
{
    getgroups_failable_by__(EFAULT)
    {
        gid_t list[16] = {0};
        ASSERT_EQ(-1, getgroups(sizeof(list)/sizeof(list[0]), list));
        ASSERT_EQ(EFAULT, errno);
    }
}

TEST(unistd,setuid)
{
    setuid_failable_by__(EAGAIN)
    {
        ASSERT_EQ(-1, setuid(0));
        ASSERT_EQ(EAGAIN, errno);
    }
}

TEST(unistd,setreuid)
{
    setreuid_failable__
    {
        ASSERT_EQ(-1, setreuid(0,0));
        ASSERT_EQ(EPERM, errno);
    }
}

TEST(unistd,seteuid)
{
    seteuid_failable__
    {
        ASSERT_EQ(-1, seteuid(0));
        ASSERT_EQ(EPERM, errno);
    }
}

TEST(unistd,setgid)
{
    setgid_failable__
    {
        ASSERT_EQ(-1, setgid(0));
        ASSERT_EQ(EPERM, errno);
    }
}

TEST(unistd,setregid)
{
    setregid_failable__
    {
        ASSERT_EQ(-1, setregid(0,0));
        ASSERT_EQ(EPERM, errno);
    }
}

TEST(unistd,setegid)
{
    setegid_failable__
    {
        ASSERT_EQ(-1, setegid(0));
        ASSERT_EQ(EPERM, errno);
    }
}

TEST(unistd,getresuid)
{
    getresuid_failable__
    {
        uid_t ruid = 0, euid = 0, suid = 0;
        ASSERT_EQ(-1, getresuid(&ruid, &euid, &suid));
        ASSERT_EQ(EFAULT, errno);
    }
}

TEST(unistd,getresgid)
{
    getresgid_failable__
    {
        gid_t rgid = 0 , egid = 0, sgid = 0;
        ASSERT_EQ(-1, getresgid(&rgid, &egid, &sgid));
        ASSERT_EQ(EFAULT, errno);
    }
}

TEST(unistd,setresuid)
{
    setresuid_failable_by__(EPERM)
    {
        uid_t ruid = 0, euid = 0, suid = 0;
        ASSERT_EQ(-1, setresuid(ruid, euid, suid));
        ASSERT_EQ(EPERM, errno);
    }
}

TEST(unistd,setresgid)
{
    setresgid_failable_by__(EPERM)
    {
        gid_t rgid = 0 , egid = 0, sgid = 0;
        ASSERT_EQ(-1, setresgid(rgid, egid, sgid));
        ASSERT_EQ(EPERM, errno);
    }
}

TEST(unistd,fork)
{
    fork_failable_by__(ENOMEM)
    {
        ASSERT_EQ(-1, fork());
        ASSERT_EQ(ENOMEM, errno);
    }
}

TEST(unistd,ttyname)
{
    int fd = open("/dev/tty", O_RDWR);
    ttyname_failable_by__(EBADF)
    {
        ASSERT_EQ(NULL, ttyname(fd));
        ASSERT_EQ(EBADF, errno);
    }
    close(fd);
}

TEST(unistd,ttyname_r)
{
    int fd = open("/dev/tty", O_RDWR);
    ttyname_r_failable_by__(EBADF)
    {
        char buf[1024];
        ASSERT_EQ(EBADF, ttyname_r(fd, buf, sizeof(buf)/sizeof(buf[0])));
    }
    close(fd);
}

TEST(unistd,isatty)
{
    int fd = open("/dev/tty", O_RDWR);
    isatty_failable_by__(EBADF)
    {
        ASSERT_EQ(0, isatty(fd));
        ASSERT_EQ(EBADF, errno);
    }
    close(fd);
}

TEST(unistd,link)
{
    link_failable_by__(EIO)
    {
        ASSERT_EQ(-1, link("/tmp", "/tmp"));
        ASSERT_EQ(EIO, errno);
    }
}

TEST(unistd,linkat)
{
    int dirfd = open("/tmp", O_RDWR);
    linkat_failable_by__(EIO)
    {
        ASSERT_EQ(-1, linkat(dirfd, "test", dirfd, "test",
                             AT_SYMLINK_FOLLOW));
        ASSERT_EQ(EIO, errno);
    }
    close(dirfd);
}

TEST(unistd,symlink)
{
    symlink_failable_by__(EIO)
    {
        ASSERT_EQ(-1, symlink("/tmp", "/tmp"));
        ASSERT_EQ(EIO, errno);
    }
}

TEST(unistd,readlink)
{
    readlink_failable_by__(EIO)
    {
        char buf[1024];
        ASSERT_EQ(-1, readlink("/tmp", buf, sizeof(buf)/sizeof(buf[0])));
        ASSERT_EQ(EIO, errno);
    }
}

TEST(unistd,symlinkat)
{
    int dirfd = open("/tmp", O_RDWR);
    symlinkat_failable_by__(EIO)
    {
        ASSERT_EQ(-1, symlinkat("test", dirfd, "test"));
        ASSERT_EQ(EIO, errno);
    }
    close(dirfd);
}

TEST(unistd,readlinkat)
{
    int dirfd = open("/tmp", O_RDWR);
    readlinkat_failable_by__(EIO)
    {
        char buf[1024];
        ASSERT_EQ(-1, readlinkat(dirfd, "test", buf,
                                 sizeof(buf)/sizeof(buf[0])));
        ASSERT_EQ(EIO, errno);
    }
    close(dirfd);
}

TEST(unistd,unlink)
{
    unlink_failable_by__(EIO)
    {
        ASSERT_EQ(-1, unlink("/tmp/test"));
        ASSERT_EQ(EIO, errno);
    }
}

TEST(unistd,unlinkat)
{
    int dirfd = open("/tmp", O_RDWR);
    unlinkat_failable_by__(EIO)
    {
        ASSERT_EQ(-1, unlinkat(dirfd, "test", AT_REMOVEDIR));
        ASSERT_EQ(EIO, errno);
    }
    close(dirfd);
}

TEST(unistd,rmdir)
{
    rmdir_failable_by__(EBUSY)
    {
        ASSERT_EQ(-1, rmdir("/tmp/test"));
        ASSERT_EQ(EBUSY, errno);
    }
}

TEST(unistd,tcgetpgrp)
{
    int fd = open("/dev/tty", O_RDWR);
    tcgetpgrp_failable_by__(ENOTTY)
    {
        ASSERT_EQ(-1, tcgetpgrp(fd));
        ASSERT_EQ(ENOTTY, errno);
    }
    close(fd);
}

TEST(unistd,tcsetpgrp)
{
    int fd = open("/dev/tty", O_RDWR);
    tcsetpgrp_failable_by__(ENOTTY)
    {
        ASSERT_EQ(-1, tcsetpgrp(fd, 0));
        ASSERT_EQ(ENOTTY, errno);
    }
    close(fd);
}

TEST(unistd,getlogin)
{
    getlogin_failable_by__(EMFILE)
    {
        ASSERT_EQ(NULL, getlogin());
        ASSERT_EQ(EMFILE, errno);
    }
}

TEST(unistd,getlogin_r)
{
    getlogin_r_failable_by__(EMFILE)
    {
        char buf[1024];
        ASSERT_EQ(EMFILE, getlogin_r(buf, sizeof(buf)/sizeof(buf[0])));
    }
}

TEST(unistd,gethostname)
{
    gethostname_failable_by__(EPERM)
    {
        char buf[1024];
        ASSERT_EQ(-1, gethostname(buf, sizeof(buf)/sizeof(buf[0])));
        ASSERT_EQ(EPERM, errno);
    }
}

TEST(unistd,sethostname)
{
    sethostname_failable_by__(EPERM)
    {
        char buf[1024];
        ASSERT_EQ(-1, sethostname(buf, sizeof(buf)/sizeof(buf[0])));
        ASSERT_EQ(EPERM, errno);
    }
}

TEST(unistd,sethostid)
{
    sethostid_failable_by__(EPERM)
    {
        ASSERT_EQ(-1, sethostid(0));
        ASSERT_EQ(EPERM, errno);
    }
}

TEST(unistd,getdomainname)
{
    getdomainname_failable_by__(EPERM)
    {
        char buf[1024];
        ASSERT_EQ(-1, getdomainname(buf, sizeof(buf)/sizeof(buf[0])));
        ASSERT_EQ(EPERM, errno);
    }
}

TEST(unistd,setdomainname)
{
    setdomainname_failable_by__(EPERM)
    {
        char buf[1024];
        ASSERT_EQ(-1, setdomainname(buf, sizeof(buf)/sizeof(buf[0])));
        ASSERT_EQ(EPERM, errno);
    }
}

TEST(unistd,vhangup)
{
    vhangup_failable__
    {
        ASSERT_EQ(-1, vhangup());
        ASSERT_EQ(EPERM, errno);
    }
}

TEST(unistd,acct)
{
    acct_failable_by__(EIO)
    {
        ASSERT_EQ(-1, acct("test"));
        ASSERT_EQ(EIO, errno);
    }
}

TEST(unistd,daemon)
{
    daemon_failable_by__(ENOMEM)
    {
        ASSERT_EQ(-1, daemon(0,0));
        ASSERT_EQ(ENOMEM, errno);
    }
}

TEST(unistd,chroot)
{
    chroot_failable_by__(ENOMEM)
    {
        ASSERT_EQ(-1, chroot("/tmp"));
        ASSERT_EQ(ENOMEM, errno);
    }
}

TEST(unistd,getpass)
{
    getpass_failable__
    {
        ASSERT_EQ(NULL, getpass("> "));
        ASSERT_EQ(ENXIO, errno);
    }
}

TEST(unistd,fsync)
{
    int fd = open("/tmp/test", O_RDWR);
    fsync_failable_by__(EIO)
    {
        ASSERT_EQ(-1, fsync(fd));
        ASSERT_EQ(EIO, errno);
    }
    close(fd);
}

TEST(unistd,syncfs)
{
    int fd = open("/tmp/test", O_RDWR);
    syncfs_failable__
    {
        ASSERT_EQ(-1, syncfs(fd));
        ASSERT_EQ(EBADF, errno);
    }
    close(fd);
}

TEST(unistd,truncate)
{
    truncate_failable_by__(ENOENT)
    {
        ASSERT_EQ(-1, truncate("/tmp/test", 10));
        ASSERT_EQ(ENOENT, errno);
    }
}

TEST(unistd,ftruncate)
{
    int fd = open("/tmp/test", O_RDWR);
    ftruncate_failable_by__(ENOENT)
    {
        ASSERT_EQ(-1, ftruncate(fd, 10));
        ASSERT_EQ(ENOENT, errno);
    }
    close(fd);
}

TEST(unistd,brk)
{
    brk_failable__
    {
        ASSERT_EQ(-1, brk(NULL));
        ASSERT_EQ(ENOMEM, errno);
    }
}

TEST(unistd,sbrk)
{
    sbrk_failable__
    {
        intptr_t increment = 0;
        ASSERT_EQ(((void*)(-1)), sbrk(increment));
        ASSERT_EQ(ENOMEM, errno);
    }
}

TEST(unistd,lockf)
{
    int fd = open("/tmp/test", O_RDWR);
    lockf_failable_by__(EDEADLK)
    {
        ASSERT_EQ(-1, lockf(fd, F_TEST, 0));
        ASSERT_EQ(EDEADLK, errno);
    }
    close(fd);
}

TEST(unistd,fdatasync)
{
    int fd = open("/tmp/test", O_RDWR);
    fdatasync_failable_by__(EIO)
    {
        ASSERT_EQ(-1, fdatasync(fd));
        ASSERT_EQ(EIO, errno);
    }
    close(fd);
}

TEST(unistd,crypt)
{
    crypt_failable__
    {
        ASSERT_EQ(NULL, crypt("test", "AA"));
        ASSERT_EQ(ENOSYS, errno);
    }
}

