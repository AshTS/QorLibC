#include "termios.h"

#include "errno.h"

#include "sys/syscalls.h"
#include "sys/ioctl.h"

// Get the state of the terminal settings for the file descriptor and put it in the given pointer
int tcgetattr(int fd, struct termios* ptr)
{
    int result = sys_ioctl(fd, TCGETS, ptr);

    if (result < 0)
    {
        errno = -result;
        return -1;
    }

    return result;
}

// Set the state of the terminal settings for the file descriptor from the given pointer with the given timing actions
int tcsetattr(int fd, int actions, const struct termios* ptr)
{
    int timing = TCSETS;

    if (actions & TCSADRAIN)
    {
        timing = TCSETSW;
    }
    else if (actions * TCSAFLUSH)
    {
        timing = TCSETSF;
    }

    int result = sys_ioctl(fd, timing, ptr);

    if (result < 0)
    {
        errno = -result;
        return -1;
    }

    return result;
}