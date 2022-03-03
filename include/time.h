#ifndef _TIME_H
#define _TIME_H

#include "sys/types.h"
#include "stddef.h"

struct tm
{
    uint32_t tm_sec;
    uint32_t tm_min;
    uint32_t tm_hour;
    uint32_t tm_mday;
    uint32_t tm_mon;
    uint32_t tm_year;
    uint32_t tm_wday;
    uint32_t tm_yday;
    uint32_t tm_isdst;
};

time_t time(time_t* ptr);
struct tm* gmtime(const time_t* timer);
struct tm* gmtime_r(const time_t* timer, struct tm* result);

size_t strftime(char* s, size_t maxsize, const char* format, const struct tm* timptr);
#endif // _TIME_H