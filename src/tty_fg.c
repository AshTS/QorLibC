#include "unistd.h"

#include "sys/syscalls.h"
#include "errno.h"

pid_t tcgetpgrp(int fd)
{
    pid_t result;

    int return_code = sys_ioctl(fd, TIOCGPGRP, &result);

    if (return_code < 0)
    {
        errno = -return_code;
        return -1;
    }

    return result;
}

int tcsetpgrp(int fd, pid_t pgid)
{
    int return_code = sys_ioctl(fd, TIOCSPGRP, &pgid);

    if (return_code < 0)
    {
        errno = -return_code;
        return -1;
    }

    return 0;
}