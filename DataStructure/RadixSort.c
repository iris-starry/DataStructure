#include <stdio.h>
#include <stdlib.h>

void RadixSort(int* a, int n) {
	int i, max = a[0], digit_base = 1;
	int digit_cnt[10] = { 0 };
	int* bucket = (int*)malloc(sizeof(int) * n);

	for (i = 0; i < n; i++)
		if (a[i] > max) max = a[i];

	while (digit_base <= max) {
		for (i = 0; i < n; i++) digit_cnt[a[i] / digit_base % 10]++;
		for (i = 1; i < 10; i++)	digit_cnt[i] += digit_cnt[i - 1];
		for (i = n - 1; i >= 0; i--) bucket[--digit_cnt[a[i] / digit_base % 10]] = a[i];
		for (i = 0; i < n; i++) a[i] = bucket[i];
		for (i = 0; i < 10; i++)	digit_cnt[i] = 0;
		printf("\n%6d 자리 정렬 :", digit_base);
		for (i = 0; i < n; i++) printf("   %d", a[i]);
		digit_base *= 10;
	}
	free(bucket);
}

int main(void) {
	int a[] = { 10, 258, 125, 3684, 50, 15, 654, 85476, 300, 525, 67, 9207, 2631, 728, 35026, 6027, 430 };
	int i, n = sizeof(a) / sizeof(int);

	RadixSort(a, n);

	printf("\n정렬 후 :");
	for (i = 0; i < n; i++) printf("   %d", a[i]);
	printf("\n");

	return 0;
}