#include "time.h"

#include "sys/syscalls.h"

time_t time(time_t* ptr)
{
    int fd = sys_open("/dev/rtc0", O_RDONLY);

    if (fd < 0)
    {
        return 0;
    }

    time_t result;

    if (sys_ioctl(fd, RTC_RD_TIMESTAMP, (long)&result) < 0)
    {
        return 1;
    }

    result /= 1000000000;

    if (ptr != 0)
    {
        *ptr = result;
    }

    return result;
}