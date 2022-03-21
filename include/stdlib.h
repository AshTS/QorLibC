#ifndef _STDLIB_H
#define _STDLIB_H

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

#define NULL 0

#define RAND_MAX 2147483647

#define MB_CUR_MAX

#include "stddef.h"

extern const char** environ;

void* malloc(unsigned int size);
void free(void* ptr);
int rand();
void srand(unsigned int seed);

void qsort(void* base, size_t nmemb, size_t size, int (*compar)(const void*, const void*));

char* getenv(const char* name);

void exit(int returncode);

extern void (*exit_fn_ptr)(void);

int atexit(void (*function)(void));

void _store_envp(int argc, char** argv, const char** envp);

#endif