#include <stdio.h>
#include <math.h>

int main(void) {
	int n, i, j, k = 1, cnt = 0;
	char answer;
	int b[8] = { 0 };

	printf("�˾Ƹ��� ������ ���� �Է�: 0 ~ ");
	scanf_s("%d", &n);

	printf("\n0���� %d������ ���ڸ� �����ϼ���!\n", n);
	getchar();

	for (i = 0; i <= log2(n); i++) {
		printf("\n\t%d��° ī��\n\n", i + 1);
		for (j = 0; j <= n; j++) {
			if ((j & k) == k) {
				printf("%d\t", j);
				cnt++;
				if (cnt % 4 == 0)printf("\n");
			}
		}
		printf("\n\n������ ���ڰ� ������ y, ������ n�Է�: ");
		scanf_s("%c", &answer, 1); getchar();

		if (answer == 'y') b[i] = 1;
		else b[i] = 0;

		cnt = 0;
		k *= 2;
	}

	k = 1;	answer = 0;
	for (i = 0; i < log2(n); i++) {
		if (b[i] == 1) answer += k;
		k *= 2;
	}

	if (answer <= n) printf("\n������ ���ڴ� %d�Դϴ�.\n\n", answer);
	else printf("\n��信 ������ �ֽ��ϴ�.\n\n");

	return 0;
}