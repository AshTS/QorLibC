#include "sys/stat.h"

#include "errno.h"
#include "sys/syscalls.h"

uint64_t stat(const char* pathname, struct stat* buffer)
{
    int result = sys_stat(pathname, buffer);

    if (result < 0)
    {
        errno = -result;
        return -1;
    }

    return result;
}