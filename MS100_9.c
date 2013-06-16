#include <stdio.h>
#include <stdlib.h>

/**
 * 微软面试100题
 * 9. 判断一个序列是不是一颗二叉查找树的后序遍历
 */

#define MAX 10

int isPostOrder(int *array, int s, int e);

int main()
{
    int array1[] = {5, 7, 6, 9, 11, 10, 8};
    int array2[] = {7, 4, 6, 5};
    printf("Array1 is post order: %d\n", isPostOrder(array1, 0, 6));
    printf("Array2 is post order: %d\n", isPostOrder(array2, 0, 3));
    
    return 0;
}

int isPostOrder(int *array, int s, int e)
{
    int is = 1, leftTreeIsPostOrder = 1, rightTreeIsPostOrder = 1;
    int rightStart = -1;
    int i;
    if (s < e) {
        //根据最后一个结点(根节点)，分割左右子树的范围
        for (i = s; i < e; i++) {
            if (array[i] > array[e]) {
                rightStart = i;
                break;
            }
        }
        
        //如果右子树中有比根节点小的结点，这个序列不是后序遍历的序列
        for (; i < e; i++) {
            if (array[i] < array[e]) {
                is = 0;
                break;
            }
        }
        
        //如果右子树的所有结点都比根节点大，那么继续判断左右子树的序列是不是后序遍历的序列
        if (is) {
            if (rightStart) {
                leftTreeIsPostOrder = isPostOrder(array, s, rightStart-1);
                rightTreeIsPostOrder = isPostOrder(array, rightStart, e-1);
            } else {
                leftTreeIsPostOrder = isPostOrder(array, s, e-1);
            }
            
            //左右子树中有一个序列不是后序遍历的序列，那么整个序列也就不是后序遍历序列
            is = leftTreeIsPostOrder & rightTreeIsPostOrder;
        }
    }
    
    return is;
}