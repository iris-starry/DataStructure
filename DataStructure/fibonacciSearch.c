#include <stdio.h>

int fibonacciSearch(int a[], int n, int key) {
	int index = 0, pos, k = 0;
	static int fibo[] = { 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55 };

	while (fibo[k] < n) k++;

	while (k > 0)
	{
		pos = index + fibo[--k];
		if (pos < n)
		{
			if (key == a[pos]) return pos;
			else
			{
				if (key > a[pos]) {
					index = pos;
					k--;
				}

			}
		}
	}

	return -1;
}

int main(void) {

	int a[] = { 5,12,17,20,25,33,38,41,59,65,68,70,75,87,92,95,99,100,102,110,115,117,120,125,128 };
	int i, n, key;

	n = sizeof(a) / sizeof(int);

	printf("�˻� ���: ");
	for (i = 0; i < n; i++) printf("%4d", a[i]);
	printf("\n");

	printf("ã���� �ϴ� �� �Է�:");
	scanf_s("%d", &key);

	i = fibonacciSearch(a, n, key);

	if (i >= 0)
		printf("\nfound %d at index %d.\n", key, i);
	else
		printf("\n%d is not found.\n", key);

	return 0;
}