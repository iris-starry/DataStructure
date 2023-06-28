#include <stdio.h>

int main(void) {
	int m, n, r, t;

	printf("첫 번째 양의 정수:");
	scanf_s("%d", &m);

	printf("\n두 번째 양의 정수:");
	scanf_s("%d", &n);

	printf("\n%d, %d의", m, n);

	if (m < n) {
		t = m;
		m = n;
		n = t;
	}

	r = m % n;

	while (r != 0) {
		m = n;
		n = r;
		r = m % n;
	}

	printf(" 최대공약수는 %d\n", n);

	return 0;

}