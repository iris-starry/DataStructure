#include <stdio.h>
#define SIZE 5

void main(void) {
	int graph[SIZE][SIZE] = { 0, };
	int i, j, vertex, edge, e1, e2;

	printf("\n 정점 개수 : ");
	scanf_s("%d", &vertex); // 5 입력
	printf("\n 간선 개수 : ");
	scanf_s("%d", &edge); // 8 입력
	for (i = 0; i < edge; i++) {
		printf("\n 간선 시작 번호 : ");
		scanf_s("%d", &e1);
		printf("\n 간선 끝 번호 : ");
		scanf_s("%d", &e2);
		graph[e1][e2] = 1;
	}
	printf("\n\n인접 행렬\n");
	for (i = 0; i < vertex; i++) {
		for (j = 0; j < vertex; j++)
			printf("%5d", graph[i][j]);
		printf("\n");
	}
}