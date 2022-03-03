#ifndef _STAT_H
#define _STAT_H

#include "../stdint.h"
#include "types.h"

struct stat
{
    dev_t st_dev;
    ino_t st_ino;
    mode_t st_mode;
    nlink_t st_nlink;
    uid_t st_uid;
    gid_t st_gid;
    dev_t st_rdev;
    off_t st_size;
    u64 st_blksize;
    u64 st_blocks;

    time_t st_atim;
    time_t st_mtim;
    time_t st_ctim;
};

uint64_t stat(const char* pathname, struct stat* buffer);

#endif // _STAT_H