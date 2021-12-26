#include "stdio.h"

#include "errno.h"
#include "stdarg.h"
#include "stdbool.h"
#include "string.h"

#include "sys/syscalls.h"

#define PRINTF_BUFFER_LEN 64

#define PRINTF_IMPL(helper) va_list args;       \
    va_start(args, format);\
    /* Longer format specifiers*/     \
    char long_fmt_spec[16];     \
    unsigned int fmt_index = 0;     \
        \
    /* Initialize the buffer */       \
    char buffer[PRINTF_BUFFER_LEN];     \
    unsigned int index = 0;     \
        \
    for (int i = 0; i < PRINTF_BUFFER_LEN; i++)     \
    {       \
        buffer[i] = 0;      \
    }       \
        \
    /* Flag for if the next character is to be a format specifier */      \
    bool next_format_specifier = false;     \
        \
    /* Last character (for two byte format specifiers) */     \
    char last_char = 0;     \
\
    /* Number of characters to pad the ouput to */ \
    int padding_count = 0; \
        \
    /* Loop over every character in the input stream */       \
    char c = 1;     \
    while (c)       \
    {       \
        /* Get the next character */      \
        c = *(format++);      \
        \
        if (!next_format_specifier)     \
        {           \
            if (c == '%')       \
            {       \
                next_format_specifier = true;       \
                last_char = c;      \
        \
                fmt_index = 0;      \
                \
                padding_count = 0; \
        \
                continue;       \
            }       \
        \
            last_char = c;      \
        }       \
        else        \
        {       \
            if (c == 'i' || c == 'd')       \
            {       \
                int i = va_arg(args, int);      \
        \
                if (i < 0)      \
                {       \
                    i = -i;     \
                    helper(buffer, &index, '-');     \
                }       \
        \
                int counter = 1;        \
                int j = 1; \
                while (counter <= i / 10)       \
                {       \
                    counter *= 10;      \
                    j += 1; \
                }       \
        \
                for (; j < padding_count; j++) { helper(buffer, &index, ' '); } \
        \
                if (fmt_index > 1)      \
                {       \
                    int this_counter = 1;       \
                    while (long_fmt_spec[1]-- > '1')        \
                    {       \
                        this_counter *= 10;     \
                    }       \
        \
                    if (this_counter > counter)     \
                    {       \
                        counter = this_counter;         \
                    }       \
                }       \
        \
                while (counter >= 1)        \
                {       \
                    helper(buffer, &index, '0' + (i / counter) % 10);        \
                    counter /= 10;      \
                }       \
        \
                next_format_specifier = false;      \
            }       \
            else if (c == 'l')      \
            {       \
                next_format_specifier = true;       \
            }       \
            else if (c == 'd' && last_char == 'l')      \
            {       \
                long i = va_arg(args, long);        \
        \
                if (i < 0)      \
                {       \
                    i = -i;     \
                    helper(buffer, &index, '-');     \
                }       \
        \
                long counter = 1;       \
                int j = 1; \
                while (counter <= i / 10)       \
                {       \
                    counter *= 10;      \
                    j += 1; \
                }       \
        \
                for (; j < padding_count; j++) { helper(buffer, &index, ' '); } \
        \
                while (counter >= 1)        \
                {       \
                    helper(buffer, &index, '0' + (i / counter) % 10);        \
                    counter /= 10;      \
                }       \
        \
                next_format_specifier = false;      \
            }       \
            else if (c == 'p')      \
            {       \
                unsigned long i = va_arg(args, unsigned long);      \
        \
                helper(buffer, &index, '0');     \
                helper(buffer, &index, 'x');     \
        \
                unsigned long counter = 1;      \
                int j = 1; \
                while (counter <= i / 16)       \
                {       \
                    counter *= 16;      \
                    j += 1; \
                }       \
        \
                for (; j < padding_count; j++) { helper(buffer, &index, ' '); } \
        \
                while (counter >= 1)        \
                {       \
                    char digit = (i / counter) % 16;        \
        \
                    if (digit < 10)     \
                    {       \
                        helper(buffer, &index, '0' + digit);     \
                    }       \
                    else        \
                    {       \
                        helper(buffer, &index, 'A' + (digit - 10));      \
                    }       \
                            \
                    counter /= 16;      \
                }       \
                next_format_specifier = false;      \
            }       \
            else if (c == 'x')      \
            {       \
                unsigned int i = va_arg(args, unsigned int);        \
        \
                unsigned int counter = 1;       \
                int j = 1; \
                while (counter <= i / 16)       \
                {       \
                    counter *= 16;      \
                    j += 1; \
                }       \
        \
                char padding_char = long_fmt_spec[0] == '0' ? '0' : ' '; \
                for (; j < padding_count; j++) { helper(buffer, &index, padding_char); } \
        \
                while (counter >= 1)        \
                {       \
                    char digit = (i / counter) % 16;        \
        \
                    if (digit < 10)     \
                    {       \
                        helper(buffer, &index, '0' + digit);     \
                    }       \
                    else        \
                    {       \
                        helper(buffer, &index, 'A' + (digit - 10));      \
                    }       \
                            \
                    counter /= 16;      \
                }       \
                next_format_specifier = false;      \
            }       \
            else if (c == 's')      \
            {       \
                const char* s = va_arg(args, const char*);      \
        \
                for (int i = 0; s[i] != 0; i++) { padding_count --; } \
                for (int i = 0; i < padding_count; i++) { helper(buffer, &index, ' '); } \
        \
                while (*s)      \
                {       \
                    helper(buffer, &index, *(s++));      \
                }       \
                next_format_specifier = false;      \
            }       \
            else if (c == 'c')      \
            {       \
                int c = va_arg(args, int);      \
        \
                for (int i = 1; i < padding_count; i++) { helper(buffer, &index, ' '); } \
                helper(buffer, &index, (char)c);     \
                next_format_specifier = false;      \
            }       \
            else if (c >= '0' && c <= '9') \
            { \
                padding_count *= 10; \
                padding_count += (c - '0'); \
            } \
            long_fmt_spec[fmt_index++] = c;     \
            last_char = c;      \
            continue;       \
        }       \
        \
        /* Add to the buffer and possibly refresh the buffer  */      \
        helper(buffer, &index, c);       \
    }  

// Put implementation for printf
void local_put(const char* data, int fd)
{
    int count = 0;
    while (*(data + count))
    {
        count++;
    }

    sys_write(fd, (void*)data, count);
}

// Helper function for printf
void printf_helper(char* buffer, unsigned int* index, char c, int fd)
{
    buffer[((*index)++) % (PRINTF_BUFFER_LEN - 1)] = c;
    if (*index % (PRINTF_BUFFER_LEN - 1) == 0 || c == 0)
    {
        local_put(buffer, fd);

        *index = 0;
    }
}

#define FPRINTF_HELPER(buffer, index, c) printf_helper(buffer, index, c, stream->fd); length++

int fprintf(FILE* stream, const char *format, ...)
{
    int length = 0;
    PRINTF_IMPL(FPRINTF_HELPER)

    return length;
}

#define RAW_FPRINTF_HELPER(buffer, index, c) printf_helper(buffer, index, c, fd); length++

int raw_fprintf(int fd, const char *format, ...)
{
    int length = 0;
    PRINTF_IMPL(RAW_FPRINTF_HELPER)

    return length;
}

// Sput implementation for sprintf
void local_sput(const char* data, char** dest)
{
    int count = 0;
    while (*(data + count))
    {
        *((*(dest))++) = *(data + count);
        count++;
    }
}

// Helper function for sprintf
void sprintf_helper(char* buffer, unsigned int* index, char c, char** dest)
{
    buffer[((*index)++) % (PRINTF_BUFFER_LEN - 1)] = c;
    if (*index % (PRINTF_BUFFER_LEN - 1) == 0 || c == 0)
    {
        local_sput(buffer, dest);

        *index = 0;
    }
}

#define SPRINTF_HELPER(buffer, index, c) sprintf_helper(buffer, index, c, &dest); length++

int sprintf(char* dest, const char *format, ...)
{
    int length = 0;
    PRINTF_IMPL(SPRINTF_HELPER)

    *dest = 0;

    return length;
}

void perror(const char *s)
{
    printf("%s%s\n", s, strerror(errno));
}