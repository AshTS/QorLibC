#include "dirent.h"

#include "sys/syscalls.h"
#include "errno.h"
#include "stdlib.h"

int closedir(DIR* directory)
{
    int result = sys_close(directory->fd);

    free(directory);

    if (result < 0)
    {
        errno = -result;
        return -1;
    }

    return 0;
}

DIR* opendir(const char* name)
{
    int fd = sys_open(name, O_RDONLY);
    if (fd < 0)
    {
        errno = -fd;
        return NULL;
    }

    DIR* result = malloc(sizeof(DIR));

    result->buffer = malloc(DIR_READ_BUFFER);
    result->index = 0;
    result->read = 0;

    result->fd = fd;
    return result;
}

struct dirent* readdir(DIR* directory)
{
    if (directory->index < directory->read)
    {
        struct dirent* ent = directory->buffer + directory->index;
        directory->index += ent->d_reclen;
        return ent;
    }

    // TODO: This is a hack which doesn't allow the getdents call to be made multiple times as right now it simply repeats.
    if (directory->read > 0)
    {
        return NULL;
    }

    long bytes_read = sys_getdents(directory->fd, directory->buffer, DIR_READ_BUFFER);

    if (bytes_read < 0)
    {
        errno = -bytes_read;
        return NULL;
    }

    directory->read = bytes_read;
    directory->index = 0;

    struct dirent* ent = &(directory->buffer)[directory->index]; 
    directory->index += ent->d_reclen;

    return ent;
}

int readdir_r(DIR* directory, struct dirent* entry, struct dirent** result)
{
    struct dirent* value = readdir(directory);

    if (value == NULL)
    {
        return -1;
    }

    *entry = *value;
    *result = value;

    return 0;
}

void rewinddir(DIR* directory)
{
    directory->index = 0;
}

void seekdir(DIR* directory, long int pos)
{
    directory->index = pos;
}

long int telldir(DIR* directory)
{
    return directory->index;
}