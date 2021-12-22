#include "ctype.h"

bool iscntrl(char c)
{
    return c < 32 || c == 127;
}