#include <stdio.h>
#include <stdlib.h>

/**
 * 微软面试100题
 * 4. 在二叉树中找出和为某一值的所有路径
 * 输入一个整数和一颗二叉树，从树的根节点开始往下访问一直到叶结点所经过的所有节点形成一条路经，打印出和与输入整数相等的所有路径。
 * 例如输入整数22和如下二叉树
 *     10
 *   /    \
 *   5    12
 * /  \
 * 4  7
 * 则打印出两条路径: 10,12 和 10,5,7
 *
 * 解题思路:
 * 先序遍历，把根节点的值加入到部分和中
 * 1. 部分和与输入的整数相等，打印路径，停止遍历
 * 2. 部分和大于输入的整数，停止遍历
 * 3. 部分和小于输入的整数，继续先序遍历
 */

#define MAX 5

typedef struct _node {
    int value;
    struct _node *left, *right;
} Node;

typedef Node* Tree;

Tree constructATree();
void printPathSummedNInTree(const int sum, int * const path, int partialSum, int count, const Tree root);

int main()
{
    Tree tree = constructATree();
    int path[MAX];
    printPathSummedNInTree(22, path, 0, 0, tree);
    
    return 0;
}


Tree constructATree()
{
    int values[MAX] = {10, 5, 12, 4, 7};
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

void printPathSummedNInTree(const int sum, int * const path, int partialSum, int count, const Tree root)
{
    int i;
    
    if (root) {
        path[count] = root->value;
        partialSum += root->value;
        if (partialSum == sum) {
            for (i = 0; i <= count; i++) {
                printf("%d ", path[i]);
            }
            printf("\n");
        } else if (partialSum < sum) {
            if (root->left) {
                printPathSummedNInTree(sum, path, partialSum, count+1, root->left);
            }
            if (root->right) {
                printPathSummedNInTree(sum, path, partialSum, count+1, root->right);
            }
        }
    }
}