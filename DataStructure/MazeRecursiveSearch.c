#include <stdio.h>

#define M 12
#define N 16
#define MAX M*N

int cnt = 0; // �̷� ���� ī��Ʈ

// 0�� ��, 1�� �� �� �ִ� ���
int maze[M][N] = { { 1,0,0,0,0,1,0,0,0,0,1,0,0,0,1,0 },
		{ 0,1,1,0,0,0,1,0,0,1,1,0,1,0,0,1 },
		{ 1,0,0,1,1,1,0,1,1,0,0,0,1,0,1,1 },
		{ 1,0,0,0,0,1,0,0,0,0,0,1,0,1,0,0 },
		{ 1,1,0,0,0,0,1,0,1,1,1,0,0,0,1,0 },
		{ 0,0,1,0,0,1,0,1,0,0,0,1,0,0,0,1 },
		{ 0,1,0,0,0,1,0,0,0,0,0,0,0,1,1,0 },
		{ 1,0,0,1,0,0,1,1,0,1,0,0,1,0,1,0 },
		{ 1,0,0,0,1,0,0,0,1,0,1,0,0,0,0,1 },
		{ 0,1,0,1,0,1,0,0,0,0,1,0,0,0,1,0 },
		{ 1,0,1,0,0,1,1,1,0,1,0,1,0,1,0,0 },
		{ 1,0,0,0,0,0,0,0,1,0,0,0,1,0,1,1 } };

int move[8][2] = { { 0,1 },{ 1,1 },{ 1,0 },{ 1,-1 },{ 0,-1 },{ -1,-1 },{ -1,0 },{ -1,1 } };
int in_x, in_y;
int out_x, out_y;
int x2, y2;

void printMaze(void) {
	int i, j;

	maze[out_x][out_y] = 9;
	printf("\n%d�� ° �̷�\n", ++cnt);
	for (i = 0; i < M; i++) {
		for (j = 0; j < N; j++) {
			if (maze[i][j] == 9) printf("* ");
			else printf("%d ", maze[i][j]);
		}
		printf("\n");
	}
}

void mazeRecursive(int x1, int y1) {
	int d;

	if (x1 == out_x && y1 == out_y) printMaze();
	else {
		maze[x1][y1] = 9;
		for (d = 0; d < 8; d++) {
			x2 = x1 + move[d][0];
			y2 = y1 + move[d][1];
			if (x2 < 0 || x2 >= M || y2 < 0 || y2 >= N || maze[x2][y2] != 1) continue;
			mazeRecursive(x2, y2);
		}
	}
	maze[x1][y1] = 1;
}

int main(void) {

	printf("��� �� 0: "); scanf_s("%d", &in_x);
	printf("��� �� 0: "); scanf_s("%d", &in_y);
	printf("���� �� 11: "); scanf_s("%d", &out_x);
	printf("���� �� 15: "); scanf_s("%d", &out_y);

	mazeRecursive(in_x, in_y);

	if (cnt == 0)printf("���-�������� �̷� ����!\n");

	return 0;
}