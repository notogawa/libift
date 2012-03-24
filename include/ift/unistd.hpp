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
#ifndef IFT_UNISTD_HPP
#define IFT_UNISTD_HPP

#include "ift/incremental_failable.hpp"

#define access_failable_by__(E) incremental_failable__(access, E)
#define euidaccess_failable_by__(E) incremental_failable__(euidaccess, E)
#define eaccess_failable_by__(E) incremental_failable__(eaccess, E)
#define faccessat_failable_by__(E) incremental_failable__(faccessat, E)
#define lseek_failable_by__(E) incremental_failable__(lseek, E)
#define close_failable_by__(E) incremental_failable__(close, E)
#define read_failable_by__(E) incremental_failable__(read, E)
#define write_failable_by__(E) incremental_failable__(write, E)
#define pread_failable_by__(E) incremental_failable__(pread, E)
#define pwrite_failable_by__(E) incremental_failable__(pwrite, E)
#define pipe_failable_by__(E) incremental_failable__(pipe, E)
#define pipe2_failable_by__(E) incremental_failable__(pipe2, E)
#define usleep_failable_by__(E) incremental_failable__(usleep, E)
#define pause_failable__ incremental_failable__(pause, EINTR)
#define chown_failable_by__(E) incremental_failable__(chown, E)
#define fchown_failable_by__(E) incremental_failable__(fchown, E)
#define lchown_failable_by__(E) incremental_failable__(lchown, E)
#define fchownat_failable_by__(E) incremental_failable__(fchownat, E)
#define chdir_failable_by__(E) incremental_failable__(chdir, E)
#define fchdir_failable_by__(E) incremental_failable__(fchdir, E)
#define getcwd_failable_by__(E) incremental_failable__(getcwd, E)
#define get_current_dir_name_failable_by__(E)       \
    incremental_failable__(get_current_dir_name, E)
#define dup_failable_by__(E) incremental_failable__(dup, E)
#define dup2_failable_by__(E) incremental_failable__(dup2, E)
#define dup3_failable_by__(E) incremental_failable__(dup3, E)
#define execve_failable_by__(E) incremental_failable__(execve, E)
#define fexecve_failable_by__(E) incremental_failable__(fexecve, E)
#define execv_failable_by__(E) incremental_failable__(execv, E)
#define execvp_failable_by__(E) incremental_failable__(execvp, E)
#define execvpe_failable_by__(E) incremental_failable__(execvpe, E)
#define nice_failable__ incremental_failable__(nice, EPERM)
#define pathconf_failable_by__(E) incremental_failable__(pathconf, E)
#define fpathconf_failable_by__(E) incremental_failable__(fpathconf, E)
#define sysconf_failable__ incremental_failable__(sysconf, EINVAL)
#define getpgid_failable_by__(E) incremental_failable__(getpgid, E)
#define setpgid_failable_by__(E) incremental_failable__(setpgid, E)
#define setpgrp_failable_by__(E) incremental_failable__(setpgrp, E)
#define setsid_failable__ incremental_failable__(setsid, EPERM)
#define getsid_failable_by__(E) incremental_failable__(getsid, E)
#define getgroups_failable_by__(E) incremental_failable__(getgroups, E)
#define setuid_failable_by__(E) incremental_failable__(setuid, E)
#define setreuid_failable__ incremental_failable__(setreuid, EPERM)
#define seteuid_failable__ incremental_failable__(seteuid, EPERM)
#define setgid_failable__ incremental_failable__(setgid, EPERM)
#define setregid_failable__ incremental_failable__(setregid, EPERM)
#define setegid_failable__ incremental_failable__(setegid, EPERM)
#define getresuid_failable__ incremental_failable__(getresuid, EFAULT)
#define getresgid_failable__ incremental_failable__(getresgid, EFAULT)
#define setresuid_failable_by__(E) incremental_failable__(setresuid, E)
#define setresgid_failable_by__(E) incremental_failable__(setresgid, E)
#define fork_failable_by__(E) incremental_failable__(fork, E)
#define ttyname_failable_by__(E) incremental_failable__(ttyname, E)
#define ttyname_r_failable_by__(E) incremental_failable__(ttyname_r, E)
#define isatty_failable_by__(E) incremental_failable__(isatty, E)
#define link_failable_by__(E) incremental_failable__(link, E)
#define linkat_failable_by__(E) incremental_failable__(linkat, E)
#define symlink_failable_by__(E) incremental_failable__(symlink, E)
#define readlink_failable_by__(E) incremental_failable__(readlink, E)
#define symlinkat_failable_by__(E) incremental_failable__(symlinkat, E)
#define readlinkat_failable_by__(E) incremental_failable__(readlinkat, E)
#define unlink_failable_by__(E) incremental_failable__(unlink, E)
#define unlinkat_failable_by__(E) incremental_failable__(unlinkat, E)
#define rmdir_failable_by__(E) incremental_failable__(rmdir, E)
#define tcgetpgrp_failable_by__(E) incremental_failable__(tcgetpgrp, E)
#define tcsetpgrp_failable_by__(E) incremental_failable__(tcsetpgrp, E)
#define getlogin_failable_by__(E) incremental_failable__(getlogin, E)
#define getlogin_r_failable_by__(E) incremental_failable__(getlogin_r, E)
#define gethostname_failable_by__(E) incremental_failable__(gethostname, E)
#define sethostname_failable_by__(E) incremental_failable__(sethostname, E)
#define sethostid_failable_by__(E) incremental_failable__(sethostid, E)
#define getdomainname_failable_by__(E) incremental_failable__(getdomainname, E)
#define setdomainname_failable_by__(E) incremental_failable__(setdomainname, E)
#define vhangup_failable__ incremental_failable__(vhangup, EPERM)
#define acct_failable_by__(E) incremental_failable__(acct, E)
#define daemon_failable_by__(E) incremental_failable__(daemon, E)
#define chroot_failable_by__(E) incremental_failable__(chroot, E)
#define getpass_failable__ incremental_failable__(getpass, ENXIO)
#define fsync_failable_by__(E) incremental_failable__(fsync, E)
#define syncfs_failable__ incremental_failable__(syncfs, EBADF)
#define truncate_failable_by__(E) incremental_failable__(truncate, E)
#define ftruncate_failable_by__(E) incremental_failable__(ftruncate, E)
#define brk_failable__ incremental_failable__(brk, ENOMEM)
#define sbrk_failable__ incremental_failable__(sbrk, ENOMEM)
#define lockf_failable_by__(E) incremental_failable__(lockf, E)
#define fdatasync_failable_by__(E) incremental_failable__(fdatasync, E)
#define crypt_failable__ incremental_failable__(crypt, ENOSYS)

#endif
