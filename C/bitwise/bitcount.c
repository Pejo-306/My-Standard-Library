#include <stdio.h>

int bitcount(unsigned int num)
{
    // count the 1's in a number's binary representation
    int bits = 0;
    for (bits = 0; num != 0; num &= num - 1)
        bits++;

    return bits;
}

