#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/**
 * 微软面试100题
 * 14. 给定一个升序数组和一个数字m，输出数组中两个数，使它们的和为m
 *
 * 解题思路: 设置两个下标，分别从数组的两端开始遍历，如果两个下标所指向的元素之和大于m，则把大的下标减一；反之，把小的下标加一。直到两个下标所指元素之和相等，返回这两个元素
 */

typedef struct _intPair {
    int a, b;
} IntPair;

IntPair* pairSummedNFromArray(int n, const int *array, const int size);

int main()
{
    int array[] = {1, 2, 4, 7, 11, 15};
    IntPair *pairPtr = pairSummedNFromArray(15, array, 6);
    if (pairPtr) {
        printf("%d %d\n", pairPtr->a, pairPtr->b);
    } else {
        printf("404\n");
    }
	return 0;
}

IntPair* pairSummedNFromArray(int n, const int *array, const int size)
{
    IntPair *pair = NULL;
    int i = 0, j = size-1, sum = array[i]+array[j];
    
    while (i < j && sum != n) {
        if (sum > n) {
            j--;
        } else if (sum < n) {
            i++;
        }
        sum = array[i]+array[j];
    }
    
    if (sum == n) {
        pair = (IntPair *)malloc(sizeof(IntPair));
        pair->a = array[i];
        pair->b = array[j];
    }
    
    return pair;
}
