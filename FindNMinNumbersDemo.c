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
 * ���ÿ���˼�룬ÿ��ȷ��array[0]���ڵ�λ��
 * ������ص�ֵmid��n����ô��������mid�����ֵ������array[0]�ٴ�ȷ��������array[0...mid-1]��λ��
 * ������ص�ֵmid����n��˵��array[0]���ǵ�n������֣���ʱ����array[0...n-1]��ӡ��������
 * ������ص�ֵmid��nС����ô˵��array[0...mid]�Ѿ��źã���ȷ��array[mid+1]��array[mid+1...size-1]�е�λ��
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