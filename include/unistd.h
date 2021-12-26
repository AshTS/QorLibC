#ifndef _UNISTD_H
#define _UNISTD_H

#include "stdlib.h"

#define STDIN_FILENO 0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2

#include "sys/types.h"

int64_t read(int fd, void* buf, int count);
int64_t write(int fd, void* buf, int count);
int64_t close(int fd);

pid_t tcgetpgrp(int);
int tcsetpgrp(int, pid_t);

#endif // _UNISTD_H