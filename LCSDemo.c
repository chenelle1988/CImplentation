#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 15

void LCS(const char *str1, const size_t length1, const char *str2, const size_t length2);

int main()
{
    char str1[] = "Myblogs";
    char str2[] = "Belongs To";
    
    LCS(str1, strlen(str1), str2, strlen(str2));
    
    return 0;
}

void LCS(const char *str1, const size_t length1, const char *str2, const size_t length2)
{
    int DP[MAX][MAX] = {0};
    int i, j;
    for (i = 0; i < length1; i++) {
        for (j = 0; j < length2; j++) {
            if (i == 0 || j == 0) {
                if (str1[i] == str2[j]) {
                    DP[i][j] = 1;
                } else {
                    DP[i][j] = 0;
                }
            } else {
                if (str1[i] == str2[j]) {
                    DP[i][j] = DP[i-1][j-1] + 1;
                } else {
                    DP[i][j] = (DP[i-1][j] > DP[i][j-1] ? DP[i-1][j] : DP[i][j-1]);
                }
            }
        }
    }
}
