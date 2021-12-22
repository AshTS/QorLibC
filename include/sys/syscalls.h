#ifndef _SYSCALLS_H
#define _SYSCALLS_H

#define PROT_NONE 0
#define PROT_READ 1
#define PROT_WRITE 2
#define PROT_EXEC 4

#define MAP_SHARED 0
#define MAP_PRIVATE 0

#define MAP_ANONYMOUS 1
#define MAP_ANON MAP_ANONYMOUS

#define O_RDONLY 1
#define O_WRONLY 2
#define O_RDWR   3
#define O_APPEND 4
#define O_TRUNC  8
#define O_CREAT  16
#define O_EXCL   32

#define SEEK_SET 1
#define SEEK_CUR 2
#define SEEK_END 4

#include "ioctl.h"

struct time_repr
{
    long tv_sec;
    long tv_nsec;
};

extern unsigned int sys_exit(int val);
extern unsigned int sys_write(int fd, void* buffer, int size);
extern unsigned int sys_open(const char* name, int open_mode);
extern unsigned int sys_close(int fd);
extern unsigned int sys_read(int fd, void *buffer, int size);
extern unsigned int sys_fork();
extern unsigned int sys_execve(const char *path, const char **argv, const char **envp);
extern unsigned int sys_wait(int *wstatus);
extern unsigned int sys_getcwd(void *buffer, int size);
extern void *sys_mmap(void *start, int length, int prot, int flags, int fd, int off);
extern unsigned int sys_munmap(void *buffer, int size);
extern unsigned int sys_getdents(int fd, void *dirents, unsigned int count);
extern unsigned int sys_chdir(const char *path);
extern unsigned int sys_mkdir(const char *path, unsigned short mode);
extern unsigned int sys_lseek(int fd, unsigned int offset, int whence);
extern unsigned int sys_pipe(int fds[2]);
extern unsigned int sys_dup2(int old_fd, int new_fd);
extern unsigned int sys_dup(int old);
extern unsigned int sys_ioctl(unsigned int fd, unsigned int cmd, unsigned long arg);
extern unsigned int sys_nanosleep(struct time_repr* req, struct time_repr* rem);
extern int sys_pause();
extern int sys_kill(short pid, int signal);
extern int sys_sigaction(int signal, void* new_action, void* old_action);
extern void sys_sigreturn();
extern int sys_sync();
extern int sys_getpid();

#endif // _SYSCALLS_H