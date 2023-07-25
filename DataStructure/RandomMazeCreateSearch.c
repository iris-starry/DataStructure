#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//미로 크기
#define R 20
#define C 30
//스택 크기
#define MAX R*C

//미로(8방향) 배열 준비. 1은 미로, 0은 벽. 초기는 모두 0으로 벽임
int maze[R][C] = { 0 };

//스택구조에 사용할 배열 준비
int stack[MAX][3] = { 0, };
int top = -1;

enum bool{ false, true };

struct direction {
	int r;
	int c;
};

//0방향은 우, 1방향은 우하, 2방향은 하, 3방향은 좌하, 4방향은 좌, 5방향은 좌상, 6방향은 상, 7방향은 우상
//move 배열은 각 방향에 대한 변위임
struct direction move[8] = { {0,1},{1,1}, {1,0},{1,-1},{0,-1},{-1,-1},{-1,0},{-1,1} };

//다음 방향쪽으로 미로 생성 여부를 판단
enum bool nextCheck(int maze_r, int maze_c, int next_r, int next_c) {
	int i;

	for (i = 0; i < 8; i++) {
		if (next_r + move[i].r < 0 || next_c + move[i].c < 0 || next_r + move[i].r >= R || next_c + move[i].c >= C) continue;
		if (next_r + move[i].r == maze_r && next_c + move[i].c == maze_c)continue;
		if (maze[next_r + move[i].r][next_c + move[i].c] >= 1) return false;
	}
	return true;
}

//재귀적 방법으로 임의의 미로 생성
void mazeCreate(int maze_r, int maze_c) {
	int dir, next_r, next_c;

	while (maze[maze_r][maze_c] < 255) { //8방향 모두 살펴 볼 때까지 반복
		do {
			dir = rand() % 8; //8방향 중 임의의 방향
		} while ((maze[maze_r][maze_c] & (1 << dir)) == 1);

		//이동 방향을 표시함. dir이 3이면 오른쪽에서 세 번째가 1이 되게 함.
		maze[maze_r][maze_c] |= (1 << dir);
		next_r = maze_r + move[dir].r;
		next_c = maze_c + move[dir].c;

		if (next_r >= 0 && next_c >= 0 && next_r < R && next_c < C)
			if (maze[next_r][next_c] == 0 && nextCheck(maze_r, maze_c, next_r, next_c)) {
				maze[next_r][next_c] = 1;
				mazeCreate(next_r, next_c);
			}
	}
}

//생성된 미로 출력 함수
void mazePrint(void) {
	int i, j;

	for (i = 0; i < R; i++) {
		for (j = 0; j < C; j++) {
			if (maze[i][j] >= 1) {
				maze[i][j] = 1;
				printf("%2d", 1);
			}
			else printf("%2d", 0);
		}
		printf("\n");
	}

}

//스택에 푸시
enum bool push(int r, int c, int d) {
	if (top >= MAX - 1) {
		printf("stack overflow\n");
		return false;
	}
	top = top + 1;
	stack[top][0] = r;
	stack[top][1] = c;
	stack[top][2] = d;
	return true;
}

//스택에서 팝
enum bool pop(int* r, int* c, int* d) {
	if (top == -1) {
		printf("stack underflow\n");
		return false;
	}
	*r = stack[top][0];
	*c = stack[top][1];
	*d = stack[top][2];
	top = top - 1;
	return true;
}

//미로 탐색
enum bool mazeSearch(void) {
	int current_r, current_c, out_r, out_c;
	int view_r, view_c;
	int d = 0; // d는 이동할 수 있는 0~8 방향 중 하나로 0에서 출발
	//0방향은 우, 1방향은 우하, 2방향은 하, 3방향은 좌하, 4방향은 좌, 5방향은 좌상, 6방향은 상, 7방향은 우상
	int move[8][2] = { { 0,1 },{ 1,1 },{ 1,0 },{ 1,-1 },{ 0,-1 },{ -1,-1 },{ -1,0 },{ -1,1 } };

	printf("출발 행(0~%d): ", R - 1); scanf_s("%d", &current_r);
	printf("출발 열(0~%d): ", C - 1); scanf_s("%d", &current_c);
	printf("도착 행(0~%d): ", R - 1); scanf_s("%d", &out_r);
	printf("도착 열(0~%d): ", C - 1); scanf_s("%d", &out_c);

	while (1) {
		while (d < 8) {
			view_r = current_r + move[d][0];
			view_c = current_c + move[d][1];
			if (view_r >= 0 && view_r < R && view_c >= 0 && view_c < C && maze[view_r][view_c] == 1) {
				maze[current_r][current_c] = 9; // 미로 표시
				if (push(current_r, current_c, d + 1) == false) return false;
				current_r = view_r;
				current_c = view_c;
				if (current_r == out_r && current_c == out_c) {
					maze[current_r][current_c] = 9;
					return true;
				}
				d = 0;
			}
			else d++;
		}
		maze[current_r][current_c] = 2; // 돌아온 경로 표시
		if (pop(&current_r, &current_c, &d) == false) return false;
	}
}

int main(void) {
	int start_r, start_c, i, j;

	srand((unsigned int)time(NULL));
	start_r = (int)rand() % R;
	start_c = (int)rand() % C;

	//임의의 출발점에서 미로 생성
	mazeCreate(start_r, start_c);

	//미로 출력
	printf("\t\t임의로 만들어진 미로\n");
	mazePrint();
	printf("\n\n");

	//미로 찾아 출력하기
	if (mazeSearch() == false) printf("출구까지 미로 없음!!\n\n");
	else {
		printf("\n\t\t입구에서 출구까지미로\n");
		for (i = 0; i < R; i++) {
			for (j = 0; j < C; j++)
				if (maze[i][j] == 9) printf("* "); // 미로이면  * 출력
				else printf("%d ", maze[i][j] == 0 ? 0 : 1); //미로 아니면 초기 데이터 출력
			printf("\n");
		}
	}
	printf("\n");

	return 0;
}