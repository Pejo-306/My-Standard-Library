using namespace std;

int bsearch(int *arr, int left, int right, int value)
{
    if (left <= right) {
        int middle = (left + right) / 2;

        if (arr[middle] == value)
            return middle;
        else if (arr[middle] > value)
            return bsearch(arr, left, middle - 1, value);
        else
            return bsearch(arr, middle + 1, right, value);
    }

    return -1; // element not found
}

