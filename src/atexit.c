#include "stdlib.h"

#include "sys/syscalls.h"

void (*exit_fn_ptr)(void) = 0;

int atexit(void (*function)(void))
{
    exit_fn_ptr = function;
    return 0;
}

void exit(int returncode)
{
    if (exit_fn_ptr != 0)
    {
        exit_fn_ptr();
    }
    sys_exit(returncode);
}