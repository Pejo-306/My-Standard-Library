#include <stdio.h>

int bsearch(int *arr, int size, int value)
{
    if (value > arr[size-1])  // value can't be in this array
        return -1;

    int left = 0, right = size - 1, middle;
    while (left <= right) {
        middle = (left + right) / 2;
        if (arr[middle] == value)
            return middle;
        else if (arr[middle] < value)
            left = middle + 1;
        else 
            right = middle - 1;
    }
    return left;
}

