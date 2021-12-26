#ifndef _SYS_IOCTL_H
#define _SYS_IOCTL_H

#define RTC_RD_TIME      0x7009
#define RTC_RD_TIMESTAMP 0x70FF

#define FB_FLUSH         0x46FF

#define TCGETS           0x5401
#define TCSETS           0x5402
#define TCSETSW          0x5403
#define TCSETSF          0x5404
#define TIOCGPGRP        0x540F
#define TIOCSPGRP        0x5410

#endif // _SYS_IOCTL_H