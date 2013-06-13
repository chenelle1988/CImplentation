#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NOT_FOUND_FLAG -1
#define START_FLAG -1

int indexOfString(char *mainString, size_t mainSize, char *substring, size_t subSize);
void constructNextArray(char *substring, int *next, size_t size);

int main()
{
    char mainString[] = "ababcabcacbab";
    char substring[] = "abcac";
    printf("%s starts from %d in %s", substring, indexOfString(mainString, strlen(mainString), substring, strlen(substring)), mainString);
    
    return 0;
}

void constructNextArray(char *substring, int *next, size_t size)
{
    int i, lastK;
    for (i = 0; i < size; i++) {
        if (i == 0) {
            next[i] = START_FLAG;
        } else {
            lastK = next[i-1];
            while (lastK != START_FLAG && substring[i-1] != substring[lastK]) {
                lastK = next[lastK];
            }
            
            if (lastK == START_FLAG) {
                next[i] = 0;
            } else if (substring[i-1] == substring[lastK]) {
                next[i] = lastK+1;
            }
        }
    }
}

int indexOfString(char *mainString, size_t mainSize, char *substring, size_t subSize)
{
    size_t i = 0, j = 0;
    int index = NOT_FOUND_FLAG;
    int *next = (int *)malloc(subSize * sizeof(int));
    constructNextArray(substring, next, subSize);
    
    while (i < mainSize && j < subSize) {
        if (mainString[i] == substring[j]) {
            if (index == NOT_FOUND_FLAG) {
                index = (int)i;
            }
            i++;
            j++;
        } else {
            j = next[j];
            if (j == START_FLAG) {
                index = NOT_FOUND_FLAG;
                j = 0;
                i++;
            } else {
                index = (int)(i-j);
            }
        }
    }
    
    return index;
}
