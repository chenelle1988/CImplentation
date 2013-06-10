//
//  main.c
//  CTemp
//
//  Created by lanner on 13-3-2.
//  Copyright (c) 2013�� lanner. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
    int value;
    struct _node *left, *right;
} Node;

typedef Node* Tree;

Tree constructATree();
void visitTreeWithPreOrder(Tree root);
void visitTreeWithInOrder(Tree root);
void visitTreeWithPostOrder(Tree root);

int main()
{
    Tree tree = constructATree();
    visitTreeWithPreOrder(tree);
    visitTreeWithInOrder(tree);
    visitTreeWithPostOrder(tree);

    getchar();
    return 0;
}

#define MAX 10

Tree constructATree()
{
    int values[MAX] = {5, 3, 2, 6, 7, 8, 2, 9, 10, -1};
    Node *nodeQueue[MAX] = {NULL};
    int i, j, size;

    for (i = 0, size = 0; i < MAX; i++) {
        Node *tmpNode = (Node *)malloc(sizeof(Node));
        tmpNode->value = values[i];
        tmpNode->left = NULL;
        tmpNode->right = NULL;
        if (i > 0) {
            for (j = 0; nodeQueue[j]->left && nodeQueue[j]->right; j++){}
            if (!nodeQueue[j]->left) {
                nodeQueue[j]->left = tmpNode;
            } else {
                nodeQueue[j]->right = tmpNode;
            }
        }
        nodeQueue[i] = tmpNode;
    }

    return nodeQueue[0];
}

void visitTreeWithPreOrder(Tree root)
{
	printf("PreOrder: ");

    Node *nodeStack[MAX*2];
    int size = 0;
    Node *visitNode = root;

    while (visitNode || size) {
        if (visitNode) {
            printf("%d ", visitNode->value);
            nodeStack[size++] = visitNode;
            visitNode = visitNode->left;
        } else {
            visitNode = nodeStack[--size]->right;
        }
    }

	printf("\n");
}

void visitTreeWithInOrder(Tree root)
{
	printf("InOrder: ");

	Node *nodeStack[MAX*2];
    int size = 0;
    Node *visitNode = root;

    while (visitNode || size) {
        if (visitNode) {
            nodeStack[size++] = visitNode;
            visitNode = visitNode->left;
        } else {
			Node *tmpNode = nodeStack[--size];
			printf("%d ", tmpNode->value);
			visitNode = tmpNode->right;
        }
    }

	printf("\n");
}

void visitTreeWithPostOrder(Tree root)
{
	printf("PostOrder: ");

	Node *nodeStack[MAX*2];
	int tagStack[MAX*2] = {0};
    int size = 0;
    Node *visitNode = root;

    while (visitNode || size) {
        if (visitNode) {
            nodeStack[size] = visitNode;
			tagStack[size] = 0;
			size++;
            visitNode = visitNode->left;
        } else {
			while (size && tagStack[size-1]) {
				Node *parentNode = nodeStack[size-1];
				printf("%d ", parentNode->value);
				size--;
			}
			if (size) {
				Node *parentNode = nodeStack[size-1];
				tagStack[size-1] = 1;
				visitNode = parentNode->right;
			}
        }
    }

	printf("\n");
}
