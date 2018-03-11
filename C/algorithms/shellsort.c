#include <stdio.h>

void shellsort(int *arr, int size)
{
    int tmp;

    for (int gap = size / 2; gap >= 1; gap /= 2) {
        for (int i = gap, j; i < size; ++i) {
            tmp = arr[i];
            for (j = i; j >= gap && tmp < arr[j-gap]; j -= gap)
                arr[j] = arr[j-gap];
            arr[j] = tmp;
        }
    }
}

