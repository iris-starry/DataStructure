#include <stdio.h>

int main(void) {
	int m, n, r, t;

	printf("ù ��° ���� ����:");
	scanf_s("%d", &m);

	printf("\n�� ��° ���� ����:");
	scanf_s("%d", &n);

	printf("\n%d, %d��", m, n);

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

	printf(" �ִ������� %d\n", n);

	return 0;

}