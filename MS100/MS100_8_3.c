#include <stdio.h>
#include <stdlib.h>

/**
 * 微软面试100题
 * 8.3 逆置链表
 */

#define MAX 10

typedef struct _node {
    int value;
    struct _node *next;
} Node;

typedef Node* Linklist;

Linklist linkListFromArray(const int *array, const int size);
void reversedLinklist(Linklist *linkList);

int main()
{
    Node *tmpNodePtr;
    int array[MAX] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    Linklist header = linkListFromArray(array, MAX);
    reversedLinklist(&header);
    for (tmpNodePtr = header; tmpNodePtr; tmpNodePtr = tmpNodePtr->next) {
        printf("%d ", tmpNodePtr->value);
    }
    printf("\n");
    return 0;
}

Linklist linkListFromArray(const int *array, const int size)
{
    Linklist header = NULL;
    Node *tailNodePtr = header, *tmpNode;
    int i;
    for (i = 0; i < size; i++) {
        tmpNode = (Node *)malloc(sizeof(Node));
        tmpNode->value = array[i];
        tmpNode->next = NULL;
        if (!header) {
            header = tmpNode;
        } else {
            tailNodePtr->next = tmpNode;
        }
        tailNodePtr = tmpNode;
    }
    
    return header;
}

void reversedLinklist(Linklist *linkList)
{
    Node *tmpNodePtr, *tailNodePtr = *linkList;
    if (tailNodePtr) {
        while (tailNodePtr->next) {
            tmpNodePtr = tailNodePtr->next;
            tailNodePtr->next = tmpNodePtr->next;
            tmpNodePtr->next = (*linkList);
            (*linkList) = tmpNodePtr;
        }
    }
}