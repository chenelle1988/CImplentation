#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/**
 * 微软100题
 * 15. 把一颗二叉树变成它的镜像
 *
 * 解题思路：递归，先把左子树变为镜像，再把右子树变为镜像，最后把左右子树位置交换
 */

typedef struct _node {
    int value;
    struct _node *left, *right;
} Node;

typedef Node* Tree;

Tree constructATree();
void visitTreeWithInOrder(Tree root);
void reverseTree(Tree *tree);

int main()
{
    Tree tree = constructATree();
    visitTreeWithInOrder(tree);
    reverseTree(&tree);
    visitTreeWithInOrder(tree);
    
    return 0;
}

void reverseTree(Tree *tree)
{
    Tree tmpTree;
    if (*tree) {
        reverseTree(&(*tree)->left);
        reverseTree(&(*tree)->right);
        tmpTree = (*tree)->left;
        (*tree)->left = (*tree)->right;
        (*tree)->right = tmpTree;
    }
}

#define MAX 7

Tree constructATree()
{
    int values[MAX] = {8, 6, 10, 5, 7, 9, 11};
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