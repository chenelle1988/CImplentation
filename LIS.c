//
//  main.c
//  CTemp
//
//  Created by Lanner on 13-2-21.
//  Copyright (c) 2013年 Lanner. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#define MAX 8

int DP[MAX][MAX];       //DP[i][j]代表array[0...i]的子序列中最大值不超过sortedArray[j]的最长递增子序列的长度

void quickSort(int *array, int s, int e);
int partition(int *array, int s, int e);
void calcDPMatrix(int *array, int *sortedArray);

int main()
{
    int array[MAX] = {8, 3, 7, 5, 1, 2, 9, 0};
    
    int sortedArray[MAX];
    int i;
    for (i = 0; i < MAX; i++) {
        sortedArray[i] = array[i];
    }
    quickSort(sortedArray, 0, MAX-1);
    
    calcDPMatrix(array, sortedArray);
    printf("Length of LIS is %d", DP[MAX-1][MAX-1]);
    
	return 0;
}

void calcDPMatrix(int *array, int *sortedArray)
{
    /**
     * 利用递归式计算DP每一项的值
     * DP[i][j] = MAX(DP[i-1][j], array[i] > sortedArray[j] ? DP[i][j-1]+1 : DP[i-1][j])
     * 递归式解释：
     * array[0...i]的最大递增子序列可能是
     * 1. array[0...i-1]的最大递增子序列(长度为array[0...i-1]的最大递增子序列的长度；
     * 2. array[0...i-1]的最大递增子序列加上array[i]，长度为array[0...i-1]的最大递增子序列的长度加1
     * 但第二种情况有个条件，就是array[i]要比array[0...i-1]的最大递增子序列的最大值要大。
     */
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