#include <stdio.h>
#include <math.h>
#include <time.h>

int main(void) {
	int i, j, k = 0, d;
	int a = 50000, b = 51000; //a ~ b 구간 설정
	clock_t t1, t2;

	// O(n∙m) 방법(n은 구간 크기, m은 소수 판단을 위한 반복 횟수)
	t1 = clock();
	for (i = a; i <= b; i++) {
		d = i / 2;
		for (j = 2; j <= d; j++) {
			if (i % j == 0) {
				k = 1;
				break;
			}
		}
		if (k == 0) printf("%d, ", i);
		k = 0;
	}
	t2 = clock();
	printf("\nO(n∙m) 방법: %.3lf초 소요\n\n", (double)(t2 - t1) / 1000);

	// O(n∙sqrt(m)) 방법(n은 구간 크기, sqrt(m)은 소수 판단을 위한 반복 횟수)
	t1 = clock();
	k = 0;
	for (i = a; i <= b; i++) {
		if (i % 2 == 0) continue;
		d = (int)sqrt((double)i);
		for (j = 2; j <= d; j++) {
			if (i % j == 0) {
				k = 1;
				break;
			}
		}
		if (k == 0) printf("%d, ", i);
		k = 0;
	}
	t2 = clock();

	printf("\nO(n∙√m) 방법: %.3lf초 소요\n\n", (double)(t2 - t1) / 1000);

	return 0;
}