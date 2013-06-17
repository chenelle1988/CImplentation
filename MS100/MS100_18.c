#include <stdio.h>
#include <stdlib.h>

int remainingElement(const int *array, const int size, const int m);

int main()
{
    int array[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int remaining = remainingElement(array, 8, 3);
    printf("The remaining one is %d\n", remaining);

    return 0;
}

int remainingElement(const int *array, const int size, const int m)
{
    int n = 1, lastRemainingIndex = 0;
    while (n <= size) {
        lastRemainingIndex = (lastRemainingIndex + m) % n;
        n++;
    }
    return array[lastRemainingIndex];
}
