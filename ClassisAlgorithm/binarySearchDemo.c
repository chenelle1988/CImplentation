#include <stdio.h>
#include <stdlib.h>

#define MAX 8
#define DOES_NOT_EXISTS -1

void quickSort(int *array, int s, int e);
int partition(int *array, int s, int e);
int binarySearch(const int *array, const int size, const int key);

int main()
{
    int array[MAX] = {8, 3, 7, 5, 1, 2, 9, 0};
    quickSort(array, 0, MAX-1);
    
    int keys[3] = {9, 8, 10};
    int index;
    int i;

    for (i = 0; i < 3; i++) {
        index = binarySearch(array, MAX, keys[i]);
        if (index != DOES_NOT_EXISTS) {
            printf("%d 在数组中的位置是: %d\n", keys[i], index);
        } else {
            printf("数组中没有 %d\n", keys[i]);
        }
    }

    return 0;
}

int binarySearch(const int *array, const int size, const int key)
{
    int index = DOES_NOT_EXISTS;
    int low = 0, high = size-1, mid = low + (high-low)/2;
    while (index == DOES_NOT_EXISTS && low <= high) {
        if (array[mid] == key) {
            index = mid;
        } else if (array[mid] < key) {
            low = mid + 1;
            mid = low + (high-low)/2;
        } else if (array[mid] > key) {
            high = mid - 1;
            mid = low + (high-low)/2;
        }
    }

    return index;
}


void quickSort(int *array, int s, int e)
{
    if (s < e) {
        int mid = partition(array, s, e);
        quickSort(array, s, mid-1);
        quickSort(array, mid+1, e);
    }
}

int partition(int *array, int s, int e)
{
    int i = s, j = e;
    int key = array[i];
    while (i < j) {
        while (i < j && array[j] >= key) {
            j--;
        }
        if (i < j) {
            array[i] = array[j];
            i++;
        }
        while (i < j && array[i] <= key) {
            i++;
        }
        if (i < j) {
            array[j] = array[i];
            j--;
        }
    }
    
    array[i] = key;
    
    return i;
}
