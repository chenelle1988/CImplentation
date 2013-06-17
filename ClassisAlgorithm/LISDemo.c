//
//  main.c
//  CTemp
//
//  Created by Lanner on 13-2-21.
//  Copyright (c) 2013年 Lanner. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 8

typedef struct _intArray {
    int count;
    int elements[MAX];
} IntArray;

typedef struct _node {
    int length;     
    IntArray preNodes;
} Node;

void calcDP(int *array, Node *DP, int size);        //关键函数
void printLIS(int *array, Node *LLIS, int size);
void printLISFromNode(int *array, Node *LLIS, int lastNode, int *nodes, int nodesCount);        //递归方式打印序列

int main()
{
    int array[MAX] = {8, 3, 7, 5, 1, 2, 9, 0};
    Node LLIS[MAX];
    calcDP(array, LLIS, MAX);
    printLIS(array, LLIS, MAX);
    
	return 0;
}

/** 
 * 根据array，构造LLIS数组，LLIS的每一个结点是一个Node结构
 * LLIS[i].length: 序列array[0...i]的最大递增子序列的长度
 * LLIS[i].preNodes: 如果array[i]被包含在array[0...i]的最大递增子序列，那么preNodes中记录了最大递增子序列中，array[i]的前驱结点。
 * 由于array[0...i]可能有多个最大递增子序列，所以array[i]的前驱结点也可能有多个。
 * 对于LLIS[i+1]，它的length的值可以如此计算
 * LLIS[i+1].length = max{1, LLIS[k].length+1}
 * 其中k满足两个条件：1. 0 <= k <= i     2. array[k] < array[i+1]。
 * 也就是说，在array[0...i]的最大递增子序列的最大值小于array[i+1]的情况下，array[i+1]会被包含在array[0...i+1]的最大递增子序列中，
 * array[0...i+1]的最大递增子序列的长度就是array[0...i]的最大递增子序列的长度加 1。
 * 上述描述中，k值可能为多个，那么这些k值的集合就构成了LLIS[i+1]的preNodes。
 */
void calcDP(int *array, Node *LLIS, int size)
{
    int i, j;
    for (i = 0; i < MAX; i++) {
        LLIS[i].length = 1;
        int count = 0;
        for (j = 0; j < i; j++) {
            if (array[i] >= array[j]) {
                if (LLIS[j].length+1 > LLIS[i].length) {
                    count = 0;
                    LLIS[i].length = LLIS[j].length+1;
                    LLIS[i].preNodes.elements[count] = j;
                    count++;
                } else if (LLIS[j].length+1 == LLIS[i].length) {
                    LLIS[i].preNodes.elements[count] = j;
                    count++;
                }
            }
        }
        LLIS[i].preNodes.count = count;
    }
}

void printLIS(int *array, Node *LLIS, int size)
{
    //当某个结点的preNodes不为空时，说明它被加到了最大递增子序列中
    //找到这些结点中的最后一个，并从后往前递归遍历，打印出所有的子序列
    int lastNode = -1;
    Node tmpNode;
    int i;
    for (i = 0; i < size; i++) {
        tmpNode = LLIS[i];
        if (tmpNode.preNodes.count != 0) {
            lastNode = i;
        }
    }
    
    int nodes[MAX];
    printLISFromNode(array, LLIS, lastNode, nodes, 0);
}

void printLISFromNode(int *array, Node *LLIS, int lastNode, int *nodes, int nodesCount)
{
    nodes[nodesCount] = array[lastNode];
    
    int i;
    if (LLIS[lastNode].preNodes.count == 0) {
        for (i = 0; i <= nodesCount; i++) {
            printf("%d ", nodes[i]);
        }
        printf("\n");
    } else {
        for (i = 0; i < LLIS[lastNode].preNodes.count; i++) {
            printLISFromNode(array, LLIS, LLIS[lastNode].preNodes.elements[i], nodes, nodesCount+1);
        }
    }
}