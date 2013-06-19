#include <stdio.h>
#include <stdlib.h>

/**
 * 微软面试100题
 * 21. 输入两个整数 n 和 m,从数列 1,2,3.......n 中随意取几个数, 使其和等于 m ,要求将其中所有的可能组合列出来。
 */

#define MAX 10
#define MAX_SUM 56

typedef struct _intArray {
    int count;
    int elements[MAX];
} IntArray;

typedef struct _reachableNode {
    int isReachable;
    IntArray preNodes;
} ReachableNode;

void calcSubArraySummedM(int n, int m);
void outputSubArray(ReachableNode *reachableSum, int index, int * const nodes, int count);
int isInSet(int n, int *set, int size);

int main()
{
    calcSubArraySummedM(10, 23);
    return 0;
}

void calcSubArraySummedM(int n, int m)
{
    ReachableNode reachableSum[MAX_SUM];
    int i, j;
    int *nodes = (int *)malloc(sizeof(int) * n);
    
    for (i = 0; i <= m; i++) {
        reachableSum[i].isReachable = 0;
        reachableSum[i].preNodes.count = 0;
    }
    
    
    reachableSum[0].isReachable = 1;
    reachableSum[0].preNodes.count = 0;
    
    for (i = 0; i <= m; i++) {
        if (reachableSum[i].isReachable) {
            for (j = 1; j < n; j++) {
                if (j + i <= m) {
                    reachableSum[j+i].isReachable = 1;
                    reachableSum[j+i].preNodes.elements[reachableSum[j+i].preNodes.count] = j;
                    reachableSum[j+i].preNodes.count++;
                }
            }
        }
    }
    
    for (i = 0; i < reachableSum[m].preNodes.count; i++) {
        nodes[0] = reachableSum[m].preNodes.elements[i];
        outputSubArray(reachableSum, m - reachableSum[m].preNodes.elements[i], nodes, 1);
    }
}

void outputSubArray(ReachableNode *reachableSum, int index, int * const nodes, int count)
{
    int i;
    
    if (reachableSum[index].preNodes.count == 0) {
        for (i = 0; i < count; i++) {
            printf("%d ", nodes[i]);
        }
        printf("\n");
    } else {
        for (i = 0; i < reachableSum[index].preNodes.count; i++) {
            if (!isInSet(reachableSum[index].preNodes.elements[i], nodes, count)) {
                nodes[count] = reachableSum[index].preNodes.elements[i];
                outputSubArray(reachableSum, index - reachableSum[index].preNodes.elements[i], nodes, count+1);
            }
        }
    }
}

int isInSet(int n, int *set, int size)
{
    int i;
    for (i = 0; i < size; i++) {
        if (set[i] == n) {
            break;
        }
    }
    
    if (i == size) {
        return 0;
    } else {
        return 1;
    }
}