#include "unistd.h"
#include "sys/syscalls.h"
#include "errno.h"

int64_t read(int fd, void* buf, int count)
{
    int val = sys_read(fd, buf, count);

    if (val < 0)
    {
        errno = -val;
        return -1;
    }

    return (int64_t)val;
}

int64_t write(int fd, void* buf, int count)
{
    int val = sys_write(fd, buf, count);

    if (val < 0)
    {
        errno = -val;
        return -1;
    }

    return (int64_t)val;
}


int64_t close(int fd)
{
    int64_t val = sys_close(fd);

    if (val < 0)
    {
        errno = -val;
        return -1;
    }

    return val;
}

int64_t unlink(const char* path)
{
    int64_t val = sys_unlink(path);

    if (val < 0)
    {
        errno = -val;
        return -1;
    }

    return val;
}

int64_t rmdir(const char* path)
{
    int64_t val = sys_rmdir(path);

    if (val < 0)
    {
        errno = -val;
        return -1;
    }

    return val;
}