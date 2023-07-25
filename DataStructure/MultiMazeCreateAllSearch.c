//8방향(우,우하,하,좌하,좌,좌상,상,우상) 중 한 방향으로 이동 가능
//0은 벽, 1은 이동 가능한 경로

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

//미로 크기
#define R 20
#define C 30
//미로 카운트
int cnt = 0;

//초기는 모두 0으로 벽임
int maze[R][C] = { 0 };
//입구
int start_r, start_c;
//출구
int end_r, end_c;
//탐색 위치
int x2, y2;

enum bool{ false, true };

struct direction {
	int r;
	int c;
};
//우, 우하, 하, 좌하, 좌, 좌상, 상, 우상에 대한 변위
struct direction move[8] = { { 0,1 },{ 1,1 },{ 1,0 },{ 1,-1 },{ 0,-1 },{ -1,-1 },{ -1,0 },{ -1,1 } };

//다음 방향쪽으로 미로 생성 여부 판단
enum bool nextCheck(int maze_r, int maze_c, int next_r, int next_c) {
	int i;

	for (i = 0; i < 8; i++) {
		if (next_r + move[i].r < 0 || next_c + move[i].c < 0 || next_r + move[i].r >= R || next_c + move[i].c >= C) continue;
		if (next_r + move[i].r == maze_r && next_c + move[i].c == maze_c)continue;
		if (maze[next_r + move[i].r][next_c + move[i].c] >= 1) return false;
	}
	return true;
}

//임의의 미로 생성
void createMaze(int maze_r, int maze_c) {
	int dir, next_r, next_c;

	while (maze[maze_r][maze_c] < 255) { //8방향 모두 살펴 볼 때까지 반복
		do {
			dir = rand() % 8; //8방향 중 임의의 방향
		} while ((maze[maze_r][maze_c] & (1 << dir)) == 1);//살펴 본 방향이 아닐 때까지

		//이동 방향을 표시함. dir이 3이면 오른쪽에서 세 번째가 1이 되게 함. 000...000000100
		//8방향 모두 살펴보았다면 000...011111111 => 255
		maze[maze_r][maze_c] |= (1 << dir);

		//다음 위치(행,열) 구하고
		next_r = maze_r + move[dir].r;
		next_c = maze_c + move[dir].c;

		if (next_r >= 0 && next_c >= 0 && next_r < R && next_c < C) //미로 범위 내이고
			//다음 위치가 0이고 인접도 모두 0이면
			if (maze[next_r][next_c] == 0 && nextCheck(maze_r, maze_c, next_r, next_c)) {
				//다음 위치가 길(1)임을 표시
				maze[next_r][next_c] = 1;
				//다음 위치로 이동하여 계속 길을 만들어 나감
				createMaze(next_r, next_c);
			}
	}
}

//출구에서 앞서 생성된 미로쪽으로
void endToMaze(int maze_r, int maze_c) {
	int dir, next_r, next_c, chk = 0;

	do {

		dir = rand() % 8; //8방향 중 임의의 방향

		next_r = maze_r + move[dir].r;
		next_c = maze_c + move[dir].c;

		if (next_r >= 0 && next_c >= 0 && next_r < R && next_c < C) {
			if (nextCheck(maze_r, maze_c, next_r, next_c)) {
				maze[next_r][next_c] = 1;
				maze_r = next_r;
				maze_c = next_c;
			}
			else break;
		}

	} while (1);

	maze[next_r][next_c] = 1;
}

//생성된 미로 출력
void createdMaze(void) {
	int i, j;

	for (i = 0; i < R; i++) {
		for (j = 0; j < C; j++) {
			if (maze[i][j] >= 1) {
				maze[i][j] = 1;
				printf("%2d", maze[i][j]);
			}
			else printf("%2d", 0);
		}
		printf("\n");
	}

}

//찾은 미로 출력
void allPath(void) {
	int i, j;

	maze[end_r][end_c] = 9;
	printf("\n%d번 째 미로\n", ++cnt);
	for (i = 0; i < R; i++) {
		for (j = 0; j < C; j++) {
			if (maze[i][j] == 9) printf("* ");
			else printf("%d ", maze[i][j]);
		}
		printf("\n");
	}
}

//모든 미로 탐색
//이전 위치(x0, y0), 현재 위치(x1, y1), 탐색 위치(x2, y2)
void mazeRecursive(int x0, int y0, int x1, int y1) {
	int d;

	//출구에 도착하였다면 미로 출력
	if (x1 == end_r && y1 == end_c) allPath();
	else { //그렇지 않다면 미로 탐색
		for (d = 0; d < 8; d++) { //현재 위치에서 8방향 모두 살펴봄
			//탐색 위치의 행(x2), 열(y2)을 구함
			x2 = x1 + move[d].r;
			y2 = y1 + move[d].c;
			//미로 범위를 벗어나거나 1(길)이 아니면 다음 방향 탐색
			if (x2 < 0 || x2 >= R || y2 < 0 || y2 >= C || maze[x2][y2] != 1) continue;
			//이전 위치(x0, y0)와 다음 위치(x2, y2)가 인접이면 다음 방향 탐색. 미로 수를 줄임
			if (abs(x0 - x2) <= 1 && abs(y0 - y2) <= 1) continue;
			//미로 표시
			maze[x1][y1] = 9;
			//다음 위치(x2, y2)로 전진하여 계속 미로 탐색하게 함
			mazeRecursive(x1, y1, x2, y2);
		}
	}
	//미로가 아니므로 미로 표시(9로 표시)를 원위치시킴
	maze[x1][y1] = 1;
}

int main(void) {
	int i, rnd_r, rnd_c;

	srand((unsigned int)time(NULL));

	printf("미로 행 크기는 20, 열 크기는 30\n\n");
	printf("출발점의 행 번호(0~%d): ", R - 1);
	scanf_s("%d", &start_r);
	printf("출발점의 열 번호(0~%d): ", C - 1);
	scanf_s("%d", &start_c);

	printf("\n도착점의 행 번호(0~%d): ", R - 1);
	scanf_s("%d", &end_r);
	printf("도착점의 열 번호(0~%d): ", C - 1);
	scanf_s("%d", &end_c);

	maze[end_r][end_c] = 256;

	printf("\n");
	//출발점에서 미로 생성
	createMaze(start_r, start_c);

	//도착점에서 미로 생성
	endToMaze(end_r, end_c);

	//다수의 미로가 되게 함
	for (i = 0; i < R * C / 100; i++) {
		do {
			rnd_r = rand() % R;
			rnd_c = rand() % C;
		} while (maze[rnd_r][rnd_c] >= 1);
		maze[rnd_r][rnd_c] = 1;
	}

	//미로 출력
	printf("\n입구에서 출구까지 생성된 다수의 미로\n\n");
	createdMaze();

	//모든 미로 출력
	printf("\n\n모든 미로 출력\n\n");
	mazeRecursive(-1, -1, start_r, start_c);
	printf("\n\n");

	return 0;
}