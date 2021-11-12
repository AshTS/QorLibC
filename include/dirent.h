#ifndef _DIRENT_H
#define _DIRENT_H

#include "stdint.h"
#include "stddef.h"

#include "sys/types.h"

#define DIR_READ_BUFFER 1024

typedef struct DIR
{
    uint32_t fd;
    void* buffer;
    size_t index;
    size_t read;
} DIR;

struct dirent
{
   ino_t  d_ino;
   unsigned long  d_off;
   unsigned short d_reclen;
   char           d_name[];
};

int closedir(DIR*);
DIR* opendir(const char*);
struct dirent* readdir(DIR*);
int readdir_r(DIR*, struct dirent*,struct  dirent**);
void rewinddir(DIR*);
void seekdir(DIR*, long int);
long int telldir(DIR*);

#endif _DIRENT_H