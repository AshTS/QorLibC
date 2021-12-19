#include "fcntl.h"
#include "sys/syscalls.h"
#include "errno.h"

int64_t open(const char* name, int mode)
{
    int64_t result = sys_open(name, mode);

    if (result < 0)
    {
        errno = -result;
        return -1;
    }

    return result;
}