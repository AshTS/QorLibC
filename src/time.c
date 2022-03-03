#include "time.h"

#include "stdbool.h"
#include "string.h"
#include "stdio.h"
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

uint32_t get_leaps(uint32_t year)
{
    return year / 4 - year / 100 + year / 400;
}

bool check_leap_year(uint32_t year)
{
    return (year % 4 == 0) && ((year % 400 == 0) || (year % 100 != 0));
}

uint32_t days_in_month(uint32_t month, uint32_t year)
{
    static uint32_t table[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    uint32_t value = table[month % 12];

    if (check_leap_year(year) && month == 1)
    {
        value++;
    }

    return value;
}

struct tm* gmtime(const time_t* timer)
{
    static struct tm time;

    return gmtime_r(timer, &time);
}

struct tm* gmtime_r(const time_t* timer, struct tm* result)
{
    const time_t t = *timer;

    int32_t days = t / 24 / 3600;
    int32_t year = 1970 + days / 365;
    int32_t month = 0;

    days -= (year - 1970) * 365 + get_leaps(year - 1) - get_leaps(1969);

    while (days < 0)
    {
        year -= 1;
        days += 365 + check_leap_year(year) ? 1 : 0;
    }

    while (month < 11)
    {
        int32_t next_days = days - days_in_month(month, year);

        if (next_days < 0)
        {
            break;
        }

        month += 1;
        days = next_days;
    }

    result->tm_sec = t % 60;
    result->tm_min = (t / 60) % 60;
    result->tm_hour = (t / 3600) % 24;
    result->tm_mday = days + 1;
    result->tm_mon = month;
    result->tm_year = year - 1900;
    result->tm_wday = (2 + days) % 7;

    return result;
}

size_t strftime(char* s, size_t maxsize, const char* format, const struct tm* timptr)
{
    static char internal_buffer[128];

    // Add a zero terminator to the string
    *s = 0;

    // Iterate through the format string
    bool next_is_fmt = false;
    while (*format)
    {
        if (maxsize <= 0)
        {
            return strlen(s);
        }

        char c = *format++;

        if (next_is_fmt)
        {
            char* string = "";
            if (c == 'a')
            {
                switch (timptr->tm_wday)
                {
                    case 0:
                        string = "Sun\0";
                        break;
                    case 1:
                        string = "Mon\0";
                        break;
                    case 2:
                        string = "Tue\0";
                        break;
                    case 3:
                        string = "Wed\0";
                        break;
                    case 4:
                        string = "Thu\0";
                        break;
                    case 5:
                        string = "Fri\0";
                        break;
                    case 6:
                        string = "Sat\0";
                        break;
                    default:
                        string = "WKD\0";
                        break;
                }
            }
            else if (c == 'A')
            {
                switch (timptr->tm_wday)
                {
                    case 0:
                        string = "Sunday\0";
                        break;
                    case 1:
                        string = "Monday\0";
                        break;
                    case 2:
                        string = "Tuesday\0";
                        break;
                    case 3:
                        string = "Wednesday\0";
                        break;
                    case 4:
                        string = "Thursday\0";
                        break;
                    case 5:
                        string = "Friday\0";
                        break;
                    case 6:
                        string = "Saturday\0";
                        break;
                    default:
                        string = "Weekday\0";
                        break;
                }
            }
            else if (c == 'b' || c == 'h')
            {
                switch (timptr->tm_mon)
                {
                    case 0:
                        string = "Jan\0";
                        break;
                    case 1:
                        string = "Feb\0";
                        break;
                    case 2:
                        string = "Mar\0";
                        break;
                    case 3:
                        string = "Apr\0";
                        break;
                    case 4:
                        string = "May\0";
                        break;
                    case 5:
                        string = "Jun\0";
                        break;
                    case 6:
                        string = "Jul\0";
                        break;
                    case 7:
                        string = "Aug\0";
                        break;
                    case 8:
                        string = "Sep\0";
                        break;
                    case 9:
                        string = "Oct\0";
                        break;
                    case 10:
                        string = "Nov\0";
                        break;
                    case 11:
                        string = "Dec\0";
                        break;
                    default:
                        string = "MON\0";
                        break;
                }
            }
            else if (c == 'B')
            {
                switch (timptr->tm_mon)
                {
                    case 0:
                        string = "January\0";
                        break;
                    case 1:
                        string = "February\0";
                        break;
                    case 2:
                        string = "March\0";
                        break;
                    case 3:
                        string = "April\0";
                        break;
                    case 4:
                        string = "May\0";
                        break;
                    case 5:
                        string = "June\0";
                        break;
                    case 6:
                        string = "July\0";
                        break;
                    case 7:
                        string = "August\0";
                        break;
                    case 8:
                        string = "September\0";
                        break;
                    case 9:
                        string = "October\0";
                        break;
                    case 10:
                        string = "November\0";
                        break;
                    case 11:
                        string = "December\0";
                        break;
                    default:
                        string = "Month\0";
                        break;
                }
            }
            else if (c == 'c')
            {
                sprintf(internal_buffer, "%02i:%02i:%02i", timptr->tm_hour, timptr->tm_min, timptr->tm_sec);
                string = internal_buffer;
            }
            else if (c == 'C')
            {
                sprintf(internal_buffer, "%02i", timptr->tm_year % 100);
                string = internal_buffer;
            }
            else if (c == 'd')
            {
                sprintf(internal_buffer, "%02i", timptr->tm_mday);
                string = internal_buffer;
            }
            else if (c == 'D')
            {
                sprintf(internal_buffer, "%02i/%02i/%02i", timptr->tm_mon + 1, timptr->tm_mday, timptr->tm_year);
                string = internal_buffer;
            }
            else if (c == 'e')
            {
                sprintf(internal_buffer, "% 2i", timptr->tm_mday);
                string = internal_buffer;
            }
            else if (c == 'H')
            {
                sprintf(internal_buffer, "%02i", timptr->tm_hour);
                string = internal_buffer;
            }
            else if (c == 'I')
            {
                int h = timptr->tm_hour % 12;
                if (h == 0)
                {
                    h += 12;
                }
                sprintf(internal_buffer, "%02i", h);
                string = internal_buffer;
            }
            else if (c == 'm')
            {
                sprintf(internal_buffer, "%02i", timptr->tm_mon + 1);
                string = internal_buffer;
            }
            else if (c == 'M')
            {
                sprintf(internal_buffer, "%02i", timptr->tm_min);
                string = internal_buffer;
            }
            else if (c == 'c' || c == 'T')
            {
                sprintf(internal_buffer, "%02i:%02i:%02i", timptr->tm_hour, timptr->tm_min, timptr->tm_sec);
                string = internal_buffer;
            }
            else if (c == 'S')
            {
                sprintf(internal_buffer, "%02i", timptr->tm_sec);
                string = internal_buffer;
            }
            else if (c == 'Y')
            {

                sprintf(internal_buffer, "%02i", timptr->tm_year + 1900 + 100 * (timptr->tm_year <= 69));
                string = internal_buffer;
            }

            if (maxsize < strlen(string))
            {
                int i = 0;
                while (--maxsize > 0)
                {
                    char buf[2] = {string[i++], 0};

                    strcat(s, buf);
                }

                return strlen(s);
            }
            else
            {
                strcat(s, string);
            }

            next_is_fmt = false;
        }
        else
        {
            if (c == '%')
            {
                next_is_fmt = true;
            }
            else
            {
                char buf[2] = {c, 0};

                strcat(s, buf);
                maxsize--;
            }
        }
    }

    return strlen(s);
}