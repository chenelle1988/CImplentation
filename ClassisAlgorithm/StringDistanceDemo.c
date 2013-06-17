#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 20

int stringDistance(const char *str1, size_t length1, const char *str2, size_t length2);

int main()
{
	char str1[] = "abcdefg";
	char str2[] = "abcdef";
	printf("The distance of \"%s\" and \"%s\" is %d\n", str1, str2, stringDistance(str1, strlen(str1), str2, strlen(str2)));

	return 0;
}

int stringDistance(const char *str1, size_t length1, const char *str2, size_t length2)
{
	int distance[MAX][MAX] = {0};
	int i, j;

    for (i = 0; i < length1; i++) {
    	for (j = 0; j < length2; j++) {
    		if (str1[i] == str2[j]) {
                if (i == 0 && j == 0) {
                    distance[i][j] = 0;
                } else if (i > 0 && j == 0) {
                    distance[i][j] = i;
                } else if (i == 0 && j > 0) {
                    distance[i][j] = j;
                } else {
                	distance[i][j] = distance[i-1][j-1];
                }
    		} else {
                if (i == 0 && j == 0) {
                    distance[i][j] = 1;
                } else if (i > 0 && j == 0) {
                    distance[i][j] = distance[i-1][j] + 1;
                } else if (i == 0 && j > 0) {
                    distance[i][j] = distance[i][j-1] + 1;
                } else {
                	int minDistance = distance[i-1][j];
                	if (minDistance > distance[i][j-1]) {
                		minDistance = distance[i][j-1];
                	}
                	if (minDistance > distance[i-1][j-1]) {
                		minDistance = distance[i-1][j-1];
                	}
                	distance[i][j] = minDistance + 1;
                }
    		}
    	}
    }

	return distance[length1-1][length2-1];
}