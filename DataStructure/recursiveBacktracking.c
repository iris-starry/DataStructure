/*
임의의 출발점에서 전진할 수 있는 한 방향(좌우상하 중)을 임의로 선택하여 벽을 허물고 전진(미로 표시)하다가
더 이상 전진할 수 없으면 이전으로 돌아가면서 전진할 수 있는 다른 방향으로 계속 미로를 만들어 나가는 방법
전진할 수 없는 조건은 배열 범위를 벗어나거나 기존 미로를 만나는 경우
기존 미로쪽으로 벽을 허물면 사이클이 형성되어 맴도는 경로가 만들어지기 때문에 배제되어야 함
*/

/*
미로 행열에 벽을 포함하는 방법으로
미로 방을 가로 c, 세로 r개로 만들고자 할 경우
미로 행열은 행 크기는 (r*2 + 1), 열 크기는 (c*2 + 1)로 준비
*/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

//벽을 포함한 미로 크기. row는 행, col은 열 크기로 3 이상의 값
int row, col;

//2차원 배열의 짝수 행과 열은 벽, 홀수 행과 열은 미로 방
//미로를 재귀적 귀로 호출 방법으로 만들어 나감
void mazeCreating(char** mazeMark, int i, int j) {
	int view_i, view_j, dir;
	int move[4][2] = { {-2,0},{2,0},{0,-2},{0,2} };//상하좌우

	//상하좌우 모두 살펴 볼 때까지 반복
	//출발점은 16으로 표시됨(오른쪽에서 5번째 bit가 1임)
	while ((mazeMark[i][j] & 15) < 15) { //출발점을 표시하지 않는다면 while (mazeMark[i][j] < 15) {

		do {

			dir = rand() % 4; //4방향 중 임의의 방향

		} while ((mazeMark[i][j] & (1 << dir)) >= 1); //dir이 살펴본 방향이면 dir 다시 구함

		//이동 방향을 표시함. dir이 3이면 오른쪽에서 세 번째가 1이 되게 함. 00000100
		//4방향 모두 살펴보았다면 00001111 => 15
		mazeMark[i][j] |= (1 << dir);

		//이동할 방의 좌표를 구함
		view_i = i + move[dir][0];
		view_j = j + move[dir][1];

		//이동할 방의 좌표가 미로 행열 범위내에 있고
		if (view_i >= 1 && view_i <= row - 2 && view_j >= 1 && view_j <= col - 2) {

			//탐색을 하지 않았다면
			if (mazeMark[view_i][view_j] == 0) {

				//미로 방향 표시. 벽을 허물고
				switch (dir) {

				case 0:mazeMark[i - 1][j] |= (1 << 0); break;

				case 1:mazeMark[i + 1][j] |= (1 << 1); break;

				case 2:mazeMark[i][j - 1] |= (1 << 2); break;

				case 3:mazeMark[i][j + 1] |= (1 << 3);

				}

				//이동한 방에서 같은 과정을 되풀이함
				mazeCreating(mazeMark, view_i, view_j);

			}

		}

	}

}

int main(void) {
	int i, j;
	char** mazeMark;

	printf("벽을 포함한 미로의 행 크기<3이상의 홀수>: ");

	do {

		scanf_s("%d", &row);

		if (row < 3 || row % 2 == 0) printf("\n다시 입력하세요: ");

		else break;

	} while (1);

	printf("\n벽을 포함한 미로의 열 크기<3이상의 홀수>: ");

	do {

		scanf_s("%d", &col);

		if (col < 3 || col % 2 == 0) printf("\n다시 입력하세요: ");

		else break;

	} while (1);

	//2차원 배열처럼 사용할 mazeMark 준비
	mazeMark = (char**)malloc(sizeof(char*) * row);

	for (i = 0; i < row; i++) mazeMark[i] = (char*)malloc(sizeof(char) * col);

	//모든 방들을 미탐색으로 채움
	for (i = 0; i < row; i++) {

		for (j = 0; j < col; j++) {

			mazeMark[i][j] = 0;

		}

	}

	srand((unsigned int)time(NULL));

	//출발점을 임의로 정함
	i = rand() % (row - 1);
	j = rand() % (col - 1);

	//행열이 짝수이면 홀수로 변경
	if (i % 2 == 0)i++;
	if (j % 2 == 0)j++;

	//출발점 표시
	mazeMark[i][j] |= (1 << 4);

	//재귀적 귀로 방법 호출
	mazeCreating(mazeMark, i, j);

	//미로를 출력함 
	printf("\n\n재귀적 귀로(Recursive Backtracking) 방법");
	printf("\n\n●:출발점, →:미로생성 방향, ▦:벽\n\n");

	for (i = 0; i < row; i++) {

		for (j = 0; j < col; j++) {

			if (mazeMark[i][j] & 16) printf("●");

			else if (i % 2 == 1 && j % 2 == 1) printf("　");

			else if (mazeMark[i][j] & 1) printf("↑");

			else if (mazeMark[i][j] & 2) printf("↓");

			else if (mazeMark[i][j] & 4) printf("←");

			else if (mazeMark[i][j] & 8) printf("→");

			else printf("▦");

		}

		printf("\n");

	}

	printf("\n\n미로 생성 방향 생략");
	printf("\n\n●:출발점, ▦:벽\n\n");

	for (i = 0; i < row; i++) {

		for (j = 0; j < col; j++) {

			if (mazeMark[i][j] & 16) printf("●");

			else if ((i % 2 == 1 && j % 2 == 1) || mazeMark[i][j] > 0) printf("　");

			else printf("▦");

		}

		printf("\n");

	}

	return 0;

}