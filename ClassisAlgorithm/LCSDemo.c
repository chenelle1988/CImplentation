#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 15

void LCS(const char *str1, const size_t length1, const char *str2, const size_t length2);
void printLCS(const char *str1, const char *str2, const int DP[][MAX], const int preInfo[][MAX], const int i, const int j, char lcs[], int lcsSize);

int main()
{
    char str1[] = "BDCABA";
    char str2[] = "ABCBDAB";
    
    LCS(str1, strlen(str1), str2, strlen(str2));
    
	getchar();
    return 0;
}

typedef enum _lcsFrom {
	HEAD = 0,
	INCLUDE_ME = 1,
	SAME_AS_UP = 1 << 2,
	SAME_AS_LEFT = 1 << 3
} LCSFrom;

void LCS(const char *str1, const size_t length1, const char *str2, const size_t length2)
{
    int DP[MAX][MAX] = {0};
	int preInfo[MAX][MAX] = {HEAD};
    int i, j;
    for (i = 0; i < length1; i++) {
        for (j = 0; j < length2; j++) {
			if (str1[i] == str2[j]) {
				if (i == 0 || j == 0) {
					DP[i][j] = 1;
				} else {
					DP[i][j] = DP[i-1][j-1] + 1;
				}
				preInfo[i][j] = INCLUDE_ME;
			} else {
				if (i == 0 && j == 0) {
					DP[i][j] = 0;
				} else if (i > 0 && j == 0) {
					DP[i][j] = DP[i-1][j];
					preInfo[i][j] = SAME_AS_UP;
				} else if (i == 0 && j > 0) {
					DP[i][j] = DP[i][j-1];
					preInfo[i][j] = SAME_AS_LEFT;
				} else {
					int left = DP[i][j-1];
					int up = DP[i-1][j];
					if (left > up) {
						DP[i][j] = left;
						preInfo[i][j] = SAME_AS_LEFT;
					} else if (left == up) {
						DP[i][j] = left;
						preInfo[i][j] = SAME_AS_LEFT | SAME_AS_UP;
					} else {
						DP[i][j] = up;
						preInfo[i][j] = SAME_AS_UP;
					}
				}
			}
        }
    }

	char lcs[MAX];
	printLCS(str1, str2, DP, preInfo, length1-1, length2-1, lcs, 0);
}

void printLCS(const char *str1, const char *str2, const int DP[][MAX], const int preInfo[][MAX], const int i, const int j, char lcs[], int lcsSize)
{
	if (i >= 0  && j >= 0) {
		if (preInfo[i][j] & INCLUDE_ME) {
			lcs[lcsSize] = str1[i];
			printLCS(str1, str2, DP, preInfo, i-1, j-1, lcs, lcsSize+1);
		}

		if (preInfo[i][j] & SAME_AS_LEFT) {
			printLCS(str1, str2, DP, preInfo, i, j-1, lcs, lcsSize);
		}

		if (preInfo[i][j] & SAME_AS_UP) {
			printLCS(str1, str2, DP, preInfo, i-1, j, lcs, lcsSize);
		}
	} else {
		int k;
		for (k = lcsSize-1; k >= 0; k--) {
			printf("%c ", lcs[k]);
		}
		printf("\n");
	}
}