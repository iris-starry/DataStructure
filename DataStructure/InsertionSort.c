#include<stdio.h>

void InsertionSort(int a[], int n) {
	int i, j, key;

	for (i = 1; i < n; i++) {
		key = a[i];
		for (j = i - 1; j >= 0; j--) {
			if (key >= a[j]) break;
			a[j + 1] = a[j];
		}
		a[j + 1] = key;
	}
}

int main(void) {
	int a[] = { 7, 12, 6, 11, 3, 8, 5, 2 };
	int i, n = sizeof(a) / sizeof(int);

	printf("정렬 전: ");
	for (i = 0; i < n; i++) printf("%d  ", a[i]);

	InsertionSort(a, n);

	printf("\n삽입 정렬 후 : ");
	for (i = 0; i < n; i++) printf("%d  ", a[i]);

	return 0;
}