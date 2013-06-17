#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 20

void findNMin(int *array, int size, int n);
int partition(int *array, int s, int e);

int main()
{
	int array[MAX] = {13, 16, 8, 19, 12, 11, 2, 8, 18, 5, 3, 13, 13, 13, 0, 19, 18, 11, 0, 7};
	findNMin(array, MAX, 6);

	getchar();
    return 0;
}

/** 
 * 利用快排思想，每次确定array[0]所在的位置
 * 如果返回的值mid比n大，那么就舍弃掉mid后面的值，根据array[0]再次确认子数组array[0...mid-1]的位置
 * 如果返回的值mid等于n，说明array[0]就是第n大的数字，此时，把array[0...n-1]打印出来即可
 * 如果返回的值mid比n小，那么说明array[0...mid]已经排好，再确定array[mid+1]在array[mid+1...size-1]中的位置
*/
void findNMin(int *array, int size, int n)
{
	int i;
	int s = 0, e = size - 1, mid = partition(array, s, e);
	while (mid != n) {
		if (mid > n) {
			e = mid - 1;
		} else if (mid < n) {
			s = mid + 1;
		}
		mid = partition(array, s, e);
	}

	for (i = 0; i < n; i++) {
		printf("%d ", array[i]);
	}
	printf("\n");
}

int partition(int *array, int s, int e)
{
	int i = s, j = e;
	int key = array[s];
	while (i < j) {
		while (i < j && array[j] >= key) {
			j--;
		}
		if (i < j) {
			array[i] = array[j];
			i++;
		}
		while (i < j && array[i] <= key) {
			i++;
		}
		if (i < j) {
			array[j] = array[i];
			j--;
		}
	}
	array[i] = key;
	return i;
}