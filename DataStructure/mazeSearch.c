#include <stdio.h>

#define M 12
#define N 16
#define MAX M*N

enum boolean { false, true };

int top = -1;
int stack[MAX][3] = { 0, };

enum boolean push(int x, int y, int d) {

	if (top >= MAX - 1) {
		printf("stack overflow\n");
		return false;
	}

	top = top + 1;
	stack[top][0] = x;
	stack[top][1] = y;
	stack[top][2] = d;

	return true;
}

enum boolean pop(int* x, int* y, int* d) {

	if (top == -1) {
		printf("stack underflow\n");
		return false;
	}

	*x = stack[top][0];
	*y = stack[top][1];
	*d = stack[top][2];
	top = top - 1;

	return true;
}

//미로 탐색
enum boolean mazeSearch(int maze[M][N]) {
	int in_x, in_y; //출발지
	int out_x, out_y; //도착지
	int current_x, current_y; //현재 위치
	int view_x, view_y; //탐색 위치

	int d = 0; // d는 이동할 수 있는 0~7 방향 중 하나로 0에서 출발
	//0방향은 우, 1방향은 우하, 2방향은 하, 3방향은 좌하, 4방향은 좌, 5방향은 좌상, 6방향은 상, 7방향은 우상

	//방향별 행,열 변위
	int move[8][2] = { { 0,1 },{ 1,1 },{ 1,0 },{ 1,-1 },{ 0,-1 },{ -1,-1 },{ -1,0 },{ -1,1 } };

	printf("출발 행: "); scanf_s("%d", &in_x);
	printf("출발 열: "); scanf_s("%d", &in_y);
	printf("도착 행: "); scanf_s("%d", &out_x);
	printf("도착 열: "); scanf_s("%d", &out_y);

	current_x = in_x;
	current_y = in_y;

	while (1) {
		while (d < 8) {
			view_x = current_x + move[d][0];
			view_y = current_y + move[d][1];

			//전진 가능하면
			if (view_x >= 0 && view_x < M && view_y >= 0 && view_y < N && maze[view_x][view_y] == 1) {
				maze[current_x][current_y] = 9; // 미로 표시

				//현재 위치와 다음 방향을 push()하고, push() 안되면 미로 없음!
				if (!push(current_x, current_y, d + 1)) return false;

				//다음 방향으로 전진
				current_x = view_x;
				current_y = view_y;
				//도착지에 도달하였다면
				if (current_x == out_x && current_y == out_y) {
					//도착지 미로 표시
					maze[current_x][current_y] = 9;
					//미로 찾음!
					return true;
				}
				//0방향에서 탐색 반복
				d = 0;

			}
			//다음 방향 탐색
			else d++;

		}

		//현재 위치에서 더 이상 전진할 곳이 없으므로
		maze[current_x][current_y] = 2; //현재 위치 탐색 완료 표시

		//stack에서 pop()하여 그 위치에서 재탐색. stack이 비어 있으면 미로 없음!
		if (pop(&current_x, &current_y, &d) == false) return false;

	}

}

int main(void) {
	// 0은 벽, 1은 갈 수 있는 통로
	int maze[M][N] = { {1,0,0,0,0,1,0,0,0,0,1,0,0,0,1,0},
			{0,1,1,0,0,0,1,0,0,1,0,0,1,0,0,1},
			{1,0,0,1,1,1,1,1,1,0,0,0,1,0,0,1},
			{1,0,0,0,0,1,0,0,0,0,0,1,1,1,1,0},
			{1,1,0,0,0,0,1,0,1,1,1,0,0,0,1,0},
			{0,0,1,0,0,1,0,1,0,0,1,1,0,0,0,1},
			{0,1,0,0,0,0,0,0,0,0,0,0,0,1,1,0},
			{1,0,0,1,0,1,1,1,1,1,0,1,1,0,0,0},
			{1,0,0,0,1,0,0,0,1,0,1,0,0,0,1,0},
			{0,0,0,1,0,1,0,0,0,0,0,0,1,0,1,1},
			{1,1,0,0,0,1,1,1,1,1,0,0,1,1,0,1},
			{1,0,0,0,0,0,0,0,1,0,1,1,0,1,0,1} };

	if (mazeSearch(maze) == false) printf("출구까지 미로 없음!!\n\n");
	else {
		printf("\n미로 찾기 완료\n");
		for (int i = 0; i < M; i++) {
			for (int j = 0; j < N; j++)
				if (maze[i][j] == 9) printf("* "); // 미로이면  * 출력
				else printf("%d ", maze[i][j] == 0 ? 0 : 1); //미로 아니면 초기 데이터 출력
			printf("\n");
		}
	}
	printf("\n");

	return 0;
}