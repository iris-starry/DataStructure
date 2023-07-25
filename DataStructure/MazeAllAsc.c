#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define M 12
#define N 16

int move[8][2] = { { 0, 1 },{ 1, 1 },{ 1, 0 },{ 1, -1 },{ 0, -1 },{ -1, -1 },{ -1, 0 },{ -1, 1 } };
int in_x, in_y, out_x, out_y, x2, y2;


//셀 좌표
struct coord {
	int r;
	int c;
};

//미로 정점 노드
struct node {
	struct coord square;
	struct node* link;
};

//미로 Head 노드
struct head {
	int mazeLength;
	struct node* mazeList;
	struct head* nextMaze;
};

struct head* mazeHeader1 = NULL, * mazeHeader2 = NULL;
struct node* top = NULL;

int nodeCnt = 0, pathCnt = 0;

typedef enum { false, true } bool;

bool push(int row, int col) {
	struct node* newNode = (struct node*)malloc(sizeof(struct node));

	if (newNode == NULL) {
		printf("Stack Overflow!\n");
		return false;
	}
	newNode->square.r = row;
	newNode->square.c = col;
	newNode->link = top;
	top = newNode;
	nodeCnt++;
	return true;
}

bool pop(void) {
	struct node* delNode = top;

	if (top == NULL) 	return false;
	top = top->link;
	free(delNode);
	nodeCnt--;
	return true;
}

void InsertHead(void) {
	struct head* previous = mazeHeader1;

	mazeHeader2 = previous->nextMaze;
	while (mazeHeader2 != NULL && nodeCnt > mazeHeader2->mazeLength) {
		previous = mazeHeader2;
		mazeHeader2 = mazeHeader2->nextMaze;
	}
	previous->nextMaze = (struct head*)malloc(sizeof(struct head));
	previous = previous->nextMaze;
	previous->mazeLength = nodeCnt;
	previous->nextMaze = mazeHeader2;
	mazeHeader2 = previous;
}

void newPathAdd(void) {
	struct node* p = top, * insNode;

	insNode = (struct node*)malloc(sizeof(struct node));
	mazeHeader2->mazeList = insNode;

	do {
		insNode->square.r = p->square.r;
		insNode->square.c = p->square.c;
		insNode->link = NULL;
		p = p->link;
		if (p == NULL) break;
		insNode->link = (struct node*)malloc(sizeof(struct node));
		insNode = insNode->link;
	} while (1);
	pathCnt++;
}

void mazePathMark(int mazePath[M][N], struct node* p, int cnt) {
	while (p != NULL) {
		mazePath[p->square.r][p->square.c] = cnt--;
		p = p->link;
	}
}

void printMazePath(int mazePath[M][N], int maze[M][N]) {
	int i, j;

	for (i = 0; i < M; i++) {
		for (j = 0; j < N; j++) {
			if (mazePath[i][j] == 0)
				printf("%3d", maze[i][j]);
			else {
				printf("%3d", mazePath[i][j]);
				mazePath[i][j] = 0;
			}
		}
		printf("\n");
	}
	printf("\n");
}

void mazePathDel(struct node* del) {

	if (del != NULL) mazePathDel(del->link);
	free(del);
}

void mazeRecursive(int maze[M][N], int x1, int y1) {
	int dir;

	if (x1 == out_x && y1 == out_y) {
		push(x1, y1);
		InsertHead();
		newPathAdd();
		pop();
	}
	else {
		maze[x1][y1] = 9;
		push(x1, y1);
		for (dir = 0; dir < 8; dir++) {
			x2 = x1 + move[dir][0];
			y2 = y1 + move[dir][1];
			if (x2 < 0 || x2 >= M || y2 < 0 || y2 >= N || maze[x2][y2] != 1) continue;
			mazeRecursive(maze, x2, y2);
		}
		maze[x1][y1] = 1;
		pop();
	}
}

int main(void) {
	// 0은 벽, 1은 갈 수 있는 통로
	int maze[M][N] = { {  1,0,0,0,0,1,0,0,0,0,1,0,0,0,1,0 },
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

	int mazePath[M][N] = { 0, };

	int i;
	struct head* p;

	//준비된 미로 출력
	printf("\n준비된 미로\n\n");
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			if (maze[i][j] >= 1) {
				maze[i][j] = 1;
				printf("%2d", maze[i][j]);
			}
			else printf("%2d", 0);
		}
		printf("\n");
	}
	printf("\n");

	printf("출발 행(0~11): "); scanf_s("%d", &in_x);
	printf("출발 열(0~15): "); scanf_s("%d", &in_y);
	printf("도착 행(0~11): "); scanf_s("%d", &out_x);
	printf("도착 열(0~15): "); scanf_s("%d", &out_y);

	mazeHeader1 = (struct head*)malloc(sizeof(struct head));
	mazeHeader1->mazeLength = 0;
	mazeHeader1->mazeList = NULL;
	mazeHeader1->nextMaze = NULL;

	mazeRecursive(maze, in_x, in_y);

	printf("\n  모든 미로(오름차순)\n");

	p = mazeHeader1->nextMaze;
	i = 1;

	while (p != NULL) {
		mazePathMark(mazePath, p->mazeList, p->mazeLength);
		printf("\n %d번째 미로, 길이는 %d\n\n", i++, p->mazeLength);
		printMazePath(mazePath, maze);
		p = p->nextMaze;
	}

	//모든 노드 제거
	mazePathDel(top);

	p = mazeHeader1;
	while (p != NULL) {
		mazePathDel(p->mazeList);
		p = p->nextMaze;
	}

	p = mazeHeader1;
	while (p != NULL) {
		mazeHeader1 = mazeHeader1->nextMaze;
		free(p);
		p = mazeHeader1;
	}

	return 0;
}