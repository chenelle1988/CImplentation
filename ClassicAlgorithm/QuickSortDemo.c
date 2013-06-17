#include <stdio.h>
#include <stdlib.h>

#define MAX 8

void quickSort(int *array, int s, int e);
int partition(int *array, int s, int e);

int main()
{
    int array[MAX] = {8, 3, 7, 5, 1, 2, 9, 0};
    quickSort(array, 0, MAX-1);
    int i = 0;
    while (i < MAX) {
        printf("%d ", array[i]);
        i++;
    }
    printf("\n");
    
    return 0;
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
