#include <stdio.h>

void QuickSort(int a[], int left, int right) {
	int i = left, j = right, pivot = a[left], temp;

	if (left < right) {
		while (i < j) {
			while (i < right && a[i] <= pivot) i++;
			while (j > left && a[j] >= pivot) j--;
			if (i < j) {
				temp = a[i]; a[i] = a[j]; a[j] = temp;
			}
		}
		a[left] = a[j];
		a[j] = pivot;

		QuickSort(a, left, j - 1);
		QuickSort(a, j + 1, right);
	}
}

int main(void) {
	int a[] = { 15, 7, 2, 20, 33, 17, 26, 5, 21, 30, 27, 29, 11, 10, 3 };
	int i, n = sizeof(a) / sizeof(int);

	printf("정렬 전 : ");
	for (i = 0; i < n; i++) printf("%5d", a[i]);

	QuickSort(a, 0, n - 1);

	printf("\n퀵 정렬 후 : ");
	for (i = 0; i < n; i++) printf("%5d", a[i]);
	printf("\n");

	return 0;
}