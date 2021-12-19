#ifndef _STDLIB_H
#define _STDLIB_H

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

#define NULL 0

#define RAND_MAX 2147483647

#define MB_CUR_MAX

#include "stddef.h"

void* malloc(unsigned int size);
void free(void* ptr);
int rand();

void qsort(void* base, size_t nmemb, size_t size, int (*compar)(const void*, const void*));

void exit(int returncode);

#endif