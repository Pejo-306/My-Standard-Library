#include <stdio.h>

#define UINT_BITS 32

unsigned int leftrot(unsigned int x, int n)
{
    return x << n | x >> (UINT_BITS - n);
}

