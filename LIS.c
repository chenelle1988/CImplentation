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
void printLISFromNode(Node *LLIS, int lastNode);

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
        LLIS[i].length = 1;
        int count = 0;
        for (j = 0; j < i; j++) {
            if (array[i] >= array[j] && LLIS[j].length+1 > LLIS[i].length) {
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
    
    printLISFromNode(LLIS, lastNode);
}

void printLISFromNode(Node *LLIS, int lastNode)
{
    
}