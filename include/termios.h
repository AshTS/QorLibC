#ifndef _TERMIOS_H
#define _TERMIOS_H

#include "stdint.h"

typedef uint8_t cc_t;
typedef uint32_t speed_t;
typedef uint32_t tcflag_t;

struct termios
{
    tcflag_t c_iflag;
    tcflag_t c_oflag;
    tcflag_t c_cflag;
    tcflag_t c_lflag;
    cc_t c_line;
    cc_t c_cc[32];
    speed_t c_ispeed;
    speed_t c_ospeed;
};

// Special Characters
#define VINTR 0
#define VQUIT 1
#define VERASE 2
#define VKILL 3
#define VEOF 4
#define VTIME 5
#define VMIN 6
#define VSWTC 7
#define VSTART 8
#define VSTOP 9
#define VSUSP 10
#define VEOL 11
#define VREPRINT 12
#define VDISCARD 13
#define VWERASE 14
#define VLNEXT 15
#define VEOL2 16

// Input Flags
#define ICRNL 0x00000100
#define IXON 0x00000400

// Output Flags
#define OPOST 0x00000001

// Local Flags
#define ISIG 0x00000001
#define ICANON 0x00000002
#define ECHO 0x00000008
#define IEXTEN 0x00008000

// Attribute Timings
#define TCSANOW 0
#define TCSADRAIN 2
#define TCSAFLUSH 4

// Get the state of the terminal settings for the file descriptor and put it in the given pointer
int tcgetattr(int fd, struct termios* ptr);

// Set the state of the terminal settings for the file descriptor from the given pointer with the given timing actions
int tcsetattr(int fd, int actions, const struct termios* ptr);

#endif // _TERMIOS_H