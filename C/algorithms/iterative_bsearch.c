int bsearch(int *arr, int size, int value)
{
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
    return -1; // value not found
}

