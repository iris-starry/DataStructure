#include <stdio.h>
#include <limits.h>

#define MAX 9

//Prim �ּҺ�� ����Ʈ�� ������
void Prim(int a[MAX][MAX], int startVertex) {
	int i, j, k, min, r, c, vertexCnt = 0, chk = 0;
	int vertexSet[MAX], b[MAX][MAX] = { 0 };

	vertexSet[0] = startVertex;

	do {
		min = INT_MAX;
		for (i = 0; i <= vertexCnt; i++) {
			for (j = 0; j < MAX; j++) {
				k = vertexSet[i];
				if (a[k][j] != 0 && a[k][j] < min && b[k][j] == 0) {
					min = a[k][j];
					r = k;
					c = j;
				}
			}
		}

		for (i = vertexCnt; i >= 0; i--)
			if (vertexSet[i] == c) {
				chk = 1;
				break;
			}

		if (chk == 1) {
			a[r][c] = 0;
			a[c][r] = 0;
			printf("���� (%d, %d)�� Cycle�� �����ϹǷ� �ǳʶ�\n", r, c);
		}
		else {
			vertexCnt++;
			vertexSet[vertexCnt] = c;
			b[r][c] = 1;
			b[c][r] = 1;
		}

		chk = 0;

	} while (vertexCnt < MAX - 1);

	for (i = 0; i < MAX; i++) {
		for (j = 0; j < MAX; j++) {
			if (b[i][j] == 0) a[i][j] = 0;
		}
	}
}

int main(void) {
	int i, j;
	char startVertex;
	char vertex[MAX] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I' };
	int adjGraph[MAX][MAX] = { {0, 18, 10, 0, 0, 0, 0, 0, 0},
							{18, 0, 0, 3, 0, 7, 0, 0, 0},
							{10, 0, 0, 11, 0, 0, 55, 0, 0},
							{0, 3, 11, 0, 48, 30, 0, 0, 0},
							{0, 0, 0, 48, 0, 0, 21, 25, 0},
							{0, 7, 0, 30, 0, 0, 0, 37, 0},
							{0, 0, 55, 0, 21, 0, 0, 0, 5},
							{0, 0, 0, 0, 25, 37, 0, 0, 17},
							{0, 0, 0, 0, 0, 0, 5, 17, 0} };

	printf("\n\t      ���� ������\n");
	printf("�ε��� : ");
	for (i = 0; i < MAX; i++) printf("%3d", i);
	printf("\n������ : ");
	for (i = 0; i < MAX; i++) printf("%3c", vertex[i]);

	printf("\n\n\t      ���� ����\n");
	for (i = 0; i < MAX; i++) {
		for (j = 0; j < MAX; j++) {
			printf("%4d", adjGraph[i][j]);
		}
		printf("\n");
	}

	printf("\n��� ����(A ~ I) : ");
	scanf_s("%c", &startVertex, 1);

	for (i = 0; i < MAX; i++)if (vertex[i] == startVertex)break;
	startVertex = i;

	Prim(adjGraph, startVertex);
	printf("\n\tPrim �ּҺ�� ����Ʈ��\n");
	for (i = 0; i < MAX; i++) {
		for (j = 0; j < MAX; j++) {
			printf("%4d", adjGraph[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	return 0;
}