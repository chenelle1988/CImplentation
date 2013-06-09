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

void calcDP(int *array, Node *DP, int size);
int maxElement(int *array, int size);
void printLIS(int *array, Node *LLIS, int size);
void printLISFromNode(int *array, Node *LLIS, int lastNode, int *nodes, int nodesCount);

int main()
{
    int array[MAX] = {8, 3, 7, 5, 1, 2, 9, 0};
    Node LLIS[MAX];
    calcDP(array, LLIS, MAX);
    printLIS(array, LLIS, MAX);
    
	return 0;
}

void calcDP(int *array, Node *LLIS, int size)
{
    int i, j;
    for (i = 0; i < MAX; i++) {
        if (i == 6) {
            printf("");
        }
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