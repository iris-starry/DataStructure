#include <stdio.h>
#define SIZE 5

void main(void) {
	int graph[SIZE][SIZE] = { 0, };
	int i, j, vertex, edge, e1, e2;

	printf("\n ���� ���� : ");
	scanf_s("%d", &vertex); // 5 �Է�
	printf("\n ���� ���� : ");
	scanf_s("%d", &edge); // 8 �Է�
	for (i = 0; i < edge; i++) {
		printf("\n ���� ���� ��ȣ : ");
		scanf_s("%d", &e1);
		printf("\n ���� �� ��ȣ : ");
		scanf_s("%d", &e2);
		graph[e1][e2] = 1;
	}
	printf("\n\n���� ���\n");
	for (i = 0; i < vertex; i++) {
		for (j = 0; j < vertex; j++)
			printf("%5d", graph[i][j]);
		printf("\n");
	}
}