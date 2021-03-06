#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/**
 * 微软面试100题
 * 48. 一个数组是由一个递减数列左移若干位形成的，比如{4，3，2，1，6，5} 是由 {6，5，4，3，2，1} 左移两位形成的，在这种数组中查找某一个数。
 */

#define MAX_N 100
#define NOT_FOUND -1

int binarySearchInShiftedArray(int key, int shiftedArray[], int size);

int main()
{
    int shiftedArray[] = {4, 3, 2, 1, 6, 5};
    int index = binarySearchInShiftedArray(3, shiftedArray, 6);
    printf("index = %d\n", index);
    return 0;
}

int binarySearchInShiftedArray(int key, int shiftedArray[], int size)
{
    int i;
    int shiftingSize = 0;
    
    int low, high, mid;
    
    for (i = size-1; i > 0; i++) {
        if (shiftedArray[i] > shiftedArray[i-1]) {
            break;
        }
    }
    
    if (i > 0) {
        shiftingSize = size - i;
    }
    
    low = 0;
    high = size-1;
    mid = low + (high-low)/2;
    while (low < high && shiftedArray[(mid-shiftingSize+size)%size] != key) {
        if (shiftedArray[(mid-shiftingSize+size)%size] > key) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
        mid = low + (high-low)/2;
    }
    
    if (low < high) {
        return (mid-shiftingSize+size) % size;
    } else {
        return NOT_FOUND;
    }
}