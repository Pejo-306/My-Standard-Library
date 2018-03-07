#include <stdio.h>

#define UINT_BITS 32

unsigned int leftrot(unsigned int num, int positions)
{
    return num << positions | num >> (UINT_BITS - positions);
}

