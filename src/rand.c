#include "stdlib.h"
#include "sys/syscalls.h"

#include "assert.h"

static unsigned short rand0 = 0xF72B;
static unsigned short rand1 = 0x9F80;

int rand()
{
    rand0 ^= rand0 << 7;
    rand0 ^= rand0 >> 8;
    rand0 ^= rand0 << 9;

    rand1 ^= rand1 << 6;
    rand1 ^= rand1 >> 7;
    rand1 ^= rand1 << 13;

    return ((int)rand0 << 16) | ((int)rand1);
}