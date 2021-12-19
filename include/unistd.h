#ifndef _UNISTD_H
#define _UNISTD_H

#include "stdlib.h"

#define STDIN_FILENO 0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2

int64_t read(int fd, void* buf, int count);
int64_t write(int fd, void* buf, int count);
int64_t close(int fd);

#endif // _UNISTD_H