#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<time.h>

#define DISK 8 //DISK�� ������ ����

int call = 0, no, * chk;
char aa, cc;
int cnt = 0, moveCnt = 0;

void HanoiTower(int n, char a, char b, char c) {
	if (n == 1) {
		if (chk[++call] == 1) {
			printf("%d�� ° �̵��� ���� ��ȣ: ", moveCnt + 1);
			scanf_s("%d", &no);
			getchar();
			printf("��� ���(A or B or C): ");
			scanf_s("%c", &aa, 1);
			aa = toupper(aa);
			printf("���� ���(A or B or C): ");
			getchar();
			scanf_s("%c", &cc, 1);
			cc = toupper(cc);
			if (no == n && aa == a && cc == c) {
				printf("%d�� ° �̵�: ���� %d, %c -> %c\n", ++moveCnt, n, a, c);
				cnt++;
			}
			else printf("%d�� °�� �����Դϴ�.\n", ++moveCnt);
		}
		else printf("%d�� ° �̵�: ���� %d, %c -> %c\n", ++moveCnt, n, a, c);
	}
	else {
		HanoiTower(n - 1, a, c, b);
		if (chk[++call] == 1) {
			printf("%d�� ° �̵��� ���� ��ȣ: ", moveCnt + 1);
			scanf_s("%d", &no);
			getchar();
			printf("��� ���(A or B or C): ");
			scanf_s("%c", &aa, 1);
			aa = toupper(aa);
			printf("���� ���(A or B or C): ");
			getchar();
			scanf_s("%c", &cc, 1);
			cc = toupper(cc);
			if (no == n && aa == a && cc == c) {
				printf("%d�� ° �̵�: ���� %d, %c -> %c\n", ++moveCnt, n, a, c);
				cnt++;
			}
			else printf("%d�� °�� �����Դϴ�.\n", ++moveCnt);
		}
		else printf("%d�� ° �̵�: ���� %d, %c -> %c\n", ++moveCnt, n, a, c);
		HanoiTower(n - 1, b, a, c);
	}
}

int power(int base, int exp) {
	int i, pow = 1;

	if (exp == 0) return 1;
	else for (i = 1; i <= exp; i++) pow *= base;
	return pow;
}

int main(void) {
	int n = DISK;
	int i, r;

	chk = (int*)calloc(power(2, n), sizeof(int));
	srand((unsigned int)time(0));

	printf("\n�־��� �ܰ迡�� �̵��� ������ ��ȣ, �����, �������� ���ʷ� �Է��Ͻÿ�.\n");
	printf("(A ����� ���� %d���� C ������� �ű��.)\n\n", n);

	for (i = 1; i <= 5; i++) {
		do {
			r = 4 + rand() % (power(2, n) - 4);
		} while (chk[r] == 1);
		chk[r] = 1;
	}

	HanoiTower(n, 'A', 'B', 'C');

	printf("\n%dȸ ��Ȯ��.\n\n", cnt);

	getchar(); getchar();

	return 0;
}