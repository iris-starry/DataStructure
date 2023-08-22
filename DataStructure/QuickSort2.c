#include <stdio.h>

void QuickSort(int a[], int left, int right) {
	int i = left, j = right, pivot, temp;

	if (left < right) {
		//범위의 왼쪽 값과 가운데 값을 교환
		temp = a[left];
		a[left] = a[(left + right) / 2];
		a[(left + right) / 2] = temp;

		pivot = a[left];

		do {
			while (i < right && a[i] >= pivot) i++;
			while (j > left && a[j] <= pivot) j--;
			if (i >= j) break;
			temp = a[i]; a[i] = a[j]; a[j] = temp;
		} while (1);

		a[left] = a[j];
		a[j] = pivot;

		QuickSort(a, left, j - 1);
		QuickSort(a, j + 1, right);
	}
}

int main(void) {
	int a[] = { 31,25,87,6,11,54,20,62,58,41,17,30,5,29 };
	int i, n;

	n = sizeof(a) / sizeof(int);

	printf("정렬전: ");
	for (i = 0; i < n; i++) printf("%4d", a[i]);
	printf("\n\n");

	QuickSort(a, 0, n - 1);

	printf("\n내림차순 퀵정렬: ");
	for (i = 0; i < n; i++) printf("%4d", a[i]);
	printf("\n\n");

	return 0;
}