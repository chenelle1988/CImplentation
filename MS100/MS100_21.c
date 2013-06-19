#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/**
 * 微软面试100题
 * 21. 输入两个整数 n 和 m,从数列 1,2,3.......n 中随意取几个数, 使其和等于 m ,要求将其中所有的可能组合列出来。
 */

#define MAX_N 11
#define MAX_SUM 56

void calcStateGraph(int n, int m);
void outputPathsToDestState(const int stateGraph[][MAX_SUM], const int graphSize, const int stateIndex, int path[], int nodeCount);

int main()
{
    calcStateGraph(10, 23);
    return 0;
}

void calcStateGraph(int n, int m)
{
    int graph[MAX_SUM][MAX_SUM] = {0};
    int isReachable[MAX_SUM] = {0};
    int i, j, destNodeIndex;
    int path[MAX_N+1];
    
    for (i = 0; i < MAX_SUM; i++) {
        for (j = 0; j < MAX_SUM; j++) {
            graph[i][j] = INT_MAX;
        }
    }
    
    isReachable[0] = 1;
    for (i = 1; i <= n; i++) {
        for (j = 0; j <= m-i; j++) {
            if (isReachable[j]) {
                destNodeIndex = j + i;
                isReachable[destNodeIndex] = 1;
                graph[j][destNodeIndex] = i;
            }
        }
    }
    
    if (isReachable[m]) {
        outputPathsToDestState(graph, m+1, m, path, 0);
    }
}

void outputPathsToDestState(const int stateGraph[][MAX_SUM], const int graphSize, const int destStateIndex, int path[], int nodeCount)
{
    int i;
    int lastEdgeLength = INT_MAX;
    if (destStateIndex == 0) {
        for (i = nodeCount-1; i >= 0; i--) {
            printf("%d ", path[i]);
        }
        printf("\n");
    } else {
        if (nodeCount) {
            lastEdgeLength = path[nodeCount-1];
        }
        for (i = 0; i < graphSize; i++) {
            if (stateGraph[i][destStateIndex] < lastEdgeLength) {
                path[nodeCount] = stateGraph[i][destStateIndex];
                outputPathsToDestState(stateGraph, graphSize, i, path, nodeCount+1);
            }
        }
    }
}