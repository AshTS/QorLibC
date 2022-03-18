#ifndef _STDIO_H
#define _STDIO_H

#include "stdbool.h"
#include "stdint.h"
#include "stddef.h"

typedef struct FILE
{
    uint32_t fd;
    bool is_binary;
} FILE;

static FILE STDIN_FILE = {.fd = 0, .is_binary = false};
static FILE STDOUT_FILE = {.fd = 1, .is_binary = false};
static FILE STDERR_FILE = {.fd = 2, .is_binary = false};

#define EOF 404

#define stdin (&STDIN_FILE)
#define stdout (&STDOUT_FILE)
#define stderr (&STDERR_FILE)

int fprintf(FILE* stream, const char *format, ...);
int raw_fprintf(int fd, const char *format, ...);


int sprintf(char* s, const char *format, ...);

#define printf(...) fprintf (stdout, __VA_ARGS__)
#define eprintf(...) fprintf (stderr, __VA_ARGS__)

#define SEEK_SET 1
#define SEEK_CUR 2
#define SEEK_END 4

int fclose(FILE*);
FILE* fopen(const char*, const char*);
size_t fread(void*, size_t, size_t, FILE*);
size_t fwrite(const void*, size_t, size_t, FILE *);
int fseek(FILE* stream, long offset, int origin);

int getchar(void);
int fgetc(FILE* stream);
char* gets(char* buffer);
char* fgets(char* buffer, int n, FILE* stream);

void perror(const char *s);

int puts(const char* str);

#endif // _STDIO_H