#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void QuickSort(int*, int, int);

int main(void) {
	int n = 3000; //n은 데이터 개수
	int i, value;

	int* a = (int*)malloc(sizeof(int) * n);

	//임의의 데이터 생성
	for (i = 0; i < n; i++) {
		value = rand() << rand() % 16;
		value = value | rand();
		a[i] = value;
	}

	//퀵 정렬 호출
	QuickSort(a, 0, n - 1);

	printf("\n퀵 정렬 결과: %d ＊ ＊ ＊ ＊ ＊ %d\n", a[0], a[n - 1]);

	//퀵 정렬 다시 호출
	QuickSort(a, 0, n - 1);

	printf("\n퀵 정렬이 완료됨!");
	printf("\n정렬된 데이터 퀵 정렬: %d ＊ ＊ ＊ ＊ ＊ %d\n", a[0], a[n - 1]);

	return 0;
}

void QuickSort(int* a, int left, int right) {
	int i, j, pivot, temp;

	if (left < right) {
		pivot = a[left];
		i = left;
		j = right;
		while (i < j) {
			while (i < right && a[i] <= pivot) i++;
			while (j > left && a[j] >= pivot) j--;
			if (i < j) {
				temp = a[i];
				a[i] = a[j];
				a[j] = temp;
			}
		}

		a[left] = a[j];
		a[j] = pivot;

		QuickSort(a, left, j - 1);
		QuickSort(a, j + 1, right);
	}
}