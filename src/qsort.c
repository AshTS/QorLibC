#include "stdlib.h"
#include "stddef.h"

void swap(void* base, size_t size, size_t I, size_t J)
{
    uint8_t* buf0 = base + size * I;
    uint8_t* buf1 = base + size * J;

    for (size_t i = 0; i < size; i++)
    {
        uint8_t temp = buf1[i];
        buf1[i] = buf0[i];
        buf0[i] = temp;
    }
}

int64_t partition(void* base, size_t count, size_t size, int (*compar)(const void*, const void*), int64_t lo, int64_t hi)
{
    int64_t pivot_value = hi;
    int64_t low = lo - 1;

    for (int j = lo; j < hi; j++)
    {
        if (compar(base + size * j, base + size * hi) <= 0)
        {
            low += 1;
            swap(base, size, low, j);
        }
    }

    low += 1;
    swap(base, size, low, hi);

    return low;
}   

void quicksort(void* base, size_t count, size_t size, int (*compar)(const void*, const void*), int64_t lo, int64_t hi)
{
    if (lo >= 0 && hi >= 0)
    {
        if (lo < hi)
        {
            int64_t pivot = partition(base, count, size, compar, lo, hi);
            quicksort(base, count, size, compar, lo, pivot - 1);
            quicksort(base, count, size, compar, pivot + 1, hi);
        }
    }
}

void qsort(void* base, size_t nmemb, size_t size, int (*compar)(const void*, const void*))
{
    if (nmemb < 2) return;
    if (size == 0) return;

    quicksort(base, nmemb, size, compar, 0, nmemb - 1);
}