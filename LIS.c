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

typedef struct _node {
    int length;
    int pre;
} Node;

#define MAX 8

void calcDP(int *array, Node *DP, int size);
int maxElement(int *array, int size);
void printLIS(int *array, Node *LLIS, int size);

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
        LLIS[i].pre = -1;
        for (j = 0; j < i; j++) {
            if (array[i] >= array[j] && LLIS[j].length+1 > LLIS[i].length) {
                LLIS[i].length = LLIS[j].length+1;
                LLIS[i].pre = j;
            }
        }
    }
}

void printLIS(int *array, Node *LLIS, int size)
{
    int lastNode = -1;
    Node tmpNode;
    int i;
    for (i = 0; i < size; i++) {
        tmpNode = LLIS[i];
        if (tmpNode.pre != -1) {
            lastNode = i;
        }
    }
    
    while (lastNode != -1) {
        printf("%d ", array[lastNode]);
        tmpNode = LLIS[lastNode];
        lastNode = tmpNode.pre;
    }
}