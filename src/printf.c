#include "stdio.h"

#include "assert.h"
#include "errno.h"
#include "stdarg.h"
#include "stdbool.h"
#include "string.h"

#include "sys/syscalls.h"

#define PRINTF_BUFFER_LEN 256

enum parser_states { WAIT_FOR_PERCENT,
 READ_FLAGS_FIRST, 
 READ_FLAGS, 
 READ_WIDTH_FIRST, 
 READ_WIDTH, 
 READ_PRECISION_FIRST,
 READ_PRECISION,
 READ_LENGTH,
 READ_LENGTH2,
 READ_SPECIFIER
};

#define PRINTF_IMPL(helper) unsigned int index = 0;\
    va_list args;\
    va_start(args, format);\
    \
    char buffer[PRINTF_BUFFER_LEN];\
    \
    enum parser_states state = WAIT_FOR_PERCENT;\
    bool is_left_justified = false;\
    bool must_sign = false;\
    bool space_for_sign = false;\
    bool show_prefix = false; /* i.e. 0x, 0o, 0X*/\
    bool pad_with_zero = false;\
    \
    unsigned int width = 0;\
    unsigned int precision = 0;\
    \
    char length0;\
    char length1;\
    \
    char specifier;\
    \
    char c;\
    while ((c = *(format ++)))\
    {\
        switch (state)\
        {\
            case WAIT_FOR_PERCENT:\
                if (c == '%')\
                {\
                    state = READ_FLAGS_FIRST;\
                    \
                    is_left_justified = false;\
                    must_sign = false;\
                    space_for_sign = false;\
                    show_prefix = false;\
                    pad_with_zero = false;\
                    \
                    width = 0;\
                    precision = 0;\
                    \
                    length0 = 0;\
                    length1 = ' ';\
                    \
                    specifier = 0;\
                }\
                else\
                {\
                    helper(buffer, &index, c);\
                }\
                break;\
            case READ_FLAGS_FIRST:\
                if (c == '%')\
                {\
                    state = WAIT_FOR_PERCENT;\
                    helper(buffer, &index, '%');\
                    break;\
                }\
                state = READ_FLAGS;\
            case READ_FLAGS:\
                if (c == '-')\
                {\
                    is_left_justified = true;\
                    break;\
                }\
                else if (c == '+')\
                {\
                    must_sign = true;\
                    break;\
                }\
                else if (c == ' ')\
                {\
                    space_for_sign = true;\
                    break;\
                }\
                else if (c == '#')\
                {\
                    show_prefix = true;\
                    break;\
                }\
                else if (c == '0')\
                {\
                    pad_with_zero = true;\
                    break;\
                }\
                state = READ_WIDTH;\
            case READ_WIDTH_FIRST:\
                if (c == '*')\
                {\
                    width = va_arg(args, int);\
                    break;\
                }\
            case READ_WIDTH:\
                if (c >= '0' && c <= '9')\
                {\
                    width *= 10;\
                    width += (unsigned int)(c - '0');\
                    break;\
                }\
                else if (c == '.')\
                {\
                    state = READ_PRECISION_FIRST;\
                    break;\
                }\
                read_length:\
            case READ_LENGTH:\
                if (c == 'h' || c == 'l')\
                {\
                    length0 = c;\
                    state = READ_LENGTH2;\
                    break;\
                }\
                else if (c == 'j' || c == 'z' || c == 't' || c == 'L')\
                {\
                    length0 = c;\
                    state = READ_SPECIFIER;\
                    break;\
                }\
            case READ_LENGTH2:\
                if (c == 'h' || c == 'l')\
                {\
                    length1 = c;\
                    state = READ_SPECIFIER;\
                    break;\
                }\
            case READ_SPECIFIER:\
                specifier = c;\
                \
                if (specifier == 's')\
                {\
                    char* s = va_arg(args, char*);\
                    int len = strlen(s);\
                    \
                    if (!is_left_justified && (len < width))\
                    {\
                        for (int i = 0; i < (width - len); i++)\
                        {\
                            if (pad_with_zero)\
                            {\
                                helper(buffer, &index, '0');\
                            }\
                            else\
                            {\
                                helper(buffer, &index, ' ');\
                            }\
                        }\
                    }\
                    \
                    while (*s)\
                    {\
                        helper(buffer, &index, *(s++));\
                    }\
                    \
                    if (is_left_justified && (len < width))\
                    {\
                        for (int i = 0; i < (width - len); i++)\
                        {\
                            if (pad_with_zero)\
                            {\
                                helper(buffer, &index, '0');\
                            }\
                            else\
                            {\
                                helper(buffer, &index, ' ');\
                            }\
                        }\
                    }\
                }\
                else\
                {\
                    unsigned long value = false;\
                    bool sign_negative = false;\
                    \
                    bool is_unsigned = (specifier == 'u' || specifier == 'x' || specifier == 'X' || specifier == 'o');\
                \
                    if (length0 == 'h')\
                    {\
                        short int v = va_arg(args, int);\
                        \
                        if (!is_unsigned)\
                        {\
                            if (v < 0)\
                            {\
                                v *= -1;\
                                sign_negative = true;\
                            }\
                        }\
                        \
                        value = v & 0xFFFF;\
                    }\
                    else if (length0 == 'l')\
                    {\
                        long v = va_arg(args, long);\
                        \
                        if (!is_unsigned)\
                        {\
                            if (v < 0)\
                            {\
                                v *= -1;\
                                sign_negative = true;\
                            }\
                        }\
                        \
                        value = v & 0xFFFFFFFFFFFFFFFF;\
                    }\
                    else if (length0 == 0)\
                    {\
                        int v = va_arg(args, int);\
                        \
                        if (!is_unsigned)\
                        {\
                            if (v < 0)\
                            {\
                                v *= -1;\
                                sign_negative = true;\
                            }\
                        }\
                        \
                        value = v & 0xFFFFFFFF;\
                    }\
                    else\
                    {\
                        assert(0 && "Format Length Given Not Supported");\
                    }\
                    \
                    char sign_character = 0;\
                    \
                    if (!is_unsigned)\
                        {\
                            if (sign_negative)\
                            {\
                                sign_character = '-'; \
                            }\
                            else\
                            {\
                                if (must_sign)\
                                {\
                                    sign_character = '+';\
                                }\
                                else if (space_for_sign)\
                                {\
                                    sign_character = ' ';\
                                }\
                            }\
                        }\
    \
                    if (specifier == 'd' || specifier == 'i' || specifier == 'u')\
                    {\
                        unsigned long power = 1;\
                        int number_length = 1;\
                        \
                        while (value / power >= 10)\
                        {\
                            power *= 10;\
                            number_length += 1;\
                        }\
                        \
                        if (sign_character != 0)\
                        {\
                            number_length += 1;\
                            \
                            if (pad_with_zero)\
                            {\
                                helper(buffer, &index, sign_character);\
                            }\
                        }\
                        \
                        if (!is_left_justified && (number_length < width))\
                        {\
                            for (int i = 0; i < (width - number_length); i++)\
                            {\
                                if (pad_with_zero)\
                                {\
                                    helper(buffer, &index, '0');\
                                }\
                                else\
                                {\
                                    helper(buffer, &index, ' ');\
                                }\
                            }\
                        }\
                        \
                        if (sign_character != 0 && !pad_with_zero)\
                        {\
                            helper(buffer, &index, sign_character);\
                        }\
                        \
                        while (power > 0)\
                        {\
                            unsigned int this_digit = (value / power);\
                            value -= this_digit * power;\
                            \
                            helper(buffer, &index, this_digit + '0');\
                            power /= 10;\
                        }\
                        \
                        if (is_left_justified && (number_length < width))\
                        {\
                            for (int i = 0; i < (width - number_length); i++)\
                            {\
                                if (pad_with_zero)\
                                {\
                                    helper(buffer, &index, '0');\
                                }\
                                else\
                                {\
                                    helper(buffer, &index, ' ');\
                                }\
                            }\
                        }\
                    }\
                    else if (specifier == 'o')\
                    {\
                        unsigned long power = 1;\
                        int number_length = 1;\
                        \
                        while (value / power >= 8)\
                        {\
                            power *= 8;\
                            number_length += 1;\
                        }\
                        \
                        if (show_prefix)\
                        {\
                            number_length += 2;\
                        }\
                        \
                        if (!is_left_justified && (number_length < width))\
                        {\
                            for (int i = 0; i < (width - number_length); i++)\
                            {\
                                if (pad_with_zero)\
                                {\
                                    helper(buffer, &index, '0');\
                                }\
                                else\
                                {\
                                    helper(buffer, &index, ' ');\
                                }\
                            }\
                        }\
                        \
                        if (show_prefix)\
                        {\
                            helper(buffer, &index, '0');\
                            helper(buffer, &index, specifier);\
                        }\
                        \
                        if (is_left_justified && (number_length < width))\
                        {\
                            for (int i = 0; i < (width - number_length); i++)\
                            {\
                                if (pad_with_zero)\
                                {\
                                    helper(buffer, &index, '0');\
                                }\
                                else\
                                {\
                                    helper(buffer, &index, ' ');\
                                }\
                            }\
                        }\
                        \
                        while (power > 0)\
                        {\
                            unsigned int this_digit = (value / power);\
                            value -= this_digit * power;\
                            \
                            helper(buffer, &index, this_digit + '0');\
                            power /= 8;\
                        }\
                    }\
                    else if (specifier == 'x' || specifier == 'X')\
                    {\
                        char* mapping = specifier == 'x' ? "0123456789abcdef" : "0123456789ABCDEF";\
                        \
                        unsigned long power = 1;\
                        int number_length = 1;\
                        \
                        while (value / power >= 16)\
                        {\
                            power *= 16;\
                            number_length += 1;\
                        }\
                        \
                        if (show_prefix)\
                        {\
                            number_length += 2;\
                        }\
                        \
                        if (!is_left_justified && (number_length < width))\
                        {\
                            for (int i = 0; i < (width - number_length); i++)\
                            {\
                                if (pad_with_zero)\
                                {\
                                    helper(buffer, &index, '0');\
                                }\
                                else\
                                {\
                                    helper(buffer, &index, ' ');\
                                }\
                            }\
                        }\
                        \
                        if (show_prefix)\
                        {\
                            helper(buffer, &index, '0');\
                            helper(buffer, &index, specifier);\
                        }\
                        \
                        while (power > 0)\
                        {\
                            unsigned int this_digit = (value / power);\
                            value -= this_digit * power;\
                            \
                            helper(buffer, &index, mapping[this_digit]);\
                            power /= 16;\
                        }\
                        \
                        if (is_left_justified && (number_length < width))\
                        {\
                            for (int i = 0; i < (width - number_length); i++)\
                            {\
                                if (pad_with_zero)\
                                {\
                                    helper(buffer, &index, '0');\
                                }\
                                else\
                                {\
                                    helper(buffer, &index, ' ');\
                                }\
                            }\
                        }\
                    }\
                    else if (specifier == 'c')\
                    {\
                        if (!is_left_justified && (1 < width))\
                        {\
                            for (int i = 0; i < (width - 1); i++)\
                            {\
                                if (pad_with_zero)\
                                {\
                                    helper(buffer, &index, '0');\
                                }\
                                else\
                                {\
                                    helper(buffer, &index, ' ');\
                                }\
                            }\
                        }\
                        \
                        helper(buffer, &index, value);\
                        \
                        if (is_left_justified && (1 < width))\
                        {\
                            for (int i = 0; i < (width - 1); i++)\
                            {\
                                if (pad_with_zero)\
                                {\
                                    helper(buffer, &index, '0');\
                                }\
                                else\
                                {\
                                    helper(buffer, &index, ' ');\
                                }\
                            }\
                        }\
                    }\
                    else\
                    {\
                        assert(0 && "Unknown Specifier");\
                    }\
                }\
                \
                state = WAIT_FOR_PERCENT;\
                break;\
                \
            case READ_PRECISION_FIRST:\
                if (c == '*')\
                {\
                    precision = va_arg(args, int);\
                    break;\
                }\
            case READ_PRECISION:\
                if (c >= '0' && c <= '9')\
                {\
                    precision *= 10;\
                    precision += (unsigned int)(c - '0');\
                    break;\
                }\
                goto read_length;\
            default:\
                break;\
        }\
    }\
    helper(buffer, &index, c);

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
    // sys_write(fd, (void*)&c, 1);
    
    buffer[*index] = c;
    (*index)++;
    if (*index == 0 || c == 0)
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
    **dest = c;
    (*dest)++;
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
    if (s != NULL)
    {
        if (*s != 0)
        {
            printf("%s: ", s);

        }
    }

    printf("%s\n", strerror(errno));
}