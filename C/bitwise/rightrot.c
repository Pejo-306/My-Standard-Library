#include <stdio.h>

#define UINT_BITS 32

unsigned int rightrot(unsigned int x, int n)
{
    return x >> n | x << (UINT_BITS - n);
}

