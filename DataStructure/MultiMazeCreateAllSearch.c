//8����(��,����,��,����,��,�»�,��,���) �� �� �������� �̵� ����
//0�� ��, 1�� �̵� ������ ���

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

//�̷� ũ��
#define R 20
#define C 30
//�̷� ī��Ʈ
int cnt = 0;

//�ʱ�� ��� 0���� ����
int maze[R][C] = { 0 };
//�Ա�
int start_r, start_c;
//�ⱸ
int end_r, end_c;
//Ž�� ��ġ
int x2, y2;

enum bool{ false, true };

struct direction {
	int r;
	int c;
};
//��, ����, ��, ����, ��, �»�, ��, ��� ���� ����
struct direction move[8] = { { 0,1 },{ 1,1 },{ 1,0 },{ 1,-1 },{ 0,-1 },{ -1,-1 },{ -1,0 },{ -1,1 } };

//���� ���������� �̷� ���� ���� �Ǵ�
enum bool nextCheck(int maze_r, int maze_c, int next_r, int next_c) {
	int i;

	for (i = 0; i < 8; i++) {
		if (next_r + move[i].r < 0 || next_c + move[i].c < 0 || next_r + move[i].r >= R || next_c + move[i].c >= C) continue;
		if (next_r + move[i].r == maze_r && next_c + move[i].c == maze_c)continue;
		if (maze[next_r + move[i].r][next_c + move[i].c] >= 1) return false;
	}
	return true;
}

//������ �̷� ����
void createMaze(int maze_r, int maze_c) {
	int dir, next_r, next_c;

	while (maze[maze_r][maze_c] < 255) { //8���� ��� ���� �� ������ �ݺ�
		do {
			dir = rand() % 8; //8���� �� ������ ����
		} while ((maze[maze_r][maze_c] & (1 << dir)) == 1);//���� �� ������ �ƴ� ������

		//�̵� ������ ǥ����. dir�� 3�̸� �����ʿ��� �� ��°�� 1�� �ǰ� ��. 000...000000100
		//8���� ��� ���캸�Ҵٸ� 000...011111111 => 255
		maze[maze_r][maze_c] |= (1 << dir);

		//���� ��ġ(��,��) ���ϰ�
		next_r = maze_r + move[dir].r;
		next_c = maze_c + move[dir].c;

		if (next_r >= 0 && next_c >= 0 && next_r < R && next_c < C) //�̷� ���� ���̰�
			//���� ��ġ�� 0�̰� ������ ��� 0�̸�
			if (maze[next_r][next_c] == 0 && nextCheck(maze_r, maze_c, next_r, next_c)) {
				//���� ��ġ�� ��(1)���� ǥ��
				maze[next_r][next_c] = 1;
				//���� ��ġ�� �̵��Ͽ� ��� ���� ����� ����
				createMaze(next_r, next_c);
			}
	}
}

//�ⱸ���� �ռ� ������ �̷�������
void endToMaze(int maze_r, int maze_c) {
	int dir, next_r, next_c, chk = 0;

	do {

		dir = rand() % 8; //8���� �� ������ ����

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

//������ �̷� ���
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

//ã�� �̷� ���
void allPath(void) {
	int i, j;

	maze[end_r][end_c] = 9;
	printf("\n%d�� ° �̷�\n", ++cnt);
	for (i = 0; i < R; i++) {
		for (j = 0; j < C; j++) {
			if (maze[i][j] == 9) printf("* ");
			else printf("%d ", maze[i][j]);
		}
		printf("\n");
	}
}

//��� �̷� Ž��
//���� ��ġ(x0, y0), ���� ��ġ(x1, y1), Ž�� ��ġ(x2, y2)
void mazeRecursive(int x0, int y0, int x1, int y1) {
	int d;

	//�ⱸ�� �����Ͽ��ٸ� �̷� ���
	if (x1 == end_r && y1 == end_c) allPath();
	else { //�׷��� �ʴٸ� �̷� Ž��
		for (d = 0; d < 8; d++) { //���� ��ġ���� 8���� ��� ���캽
			//Ž�� ��ġ�� ��(x2), ��(y2)�� ����
			x2 = x1 + move[d].r;
			y2 = y1 + move[d].c;
			//�̷� ������ ����ų� 1(��)�� �ƴϸ� ���� ���� Ž��
			if (x2 < 0 || x2 >= R || y2 < 0 || y2 >= C || maze[x2][y2] != 1) continue;
			//���� ��ġ(x0, y0)�� ���� ��ġ(x2, y2)�� �����̸� ���� ���� Ž��. �̷� ���� ����
			if (abs(x0 - x2) <= 1 && abs(y0 - y2) <= 1) continue;
			//�̷� ǥ��
			maze[x1][y1] = 9;
			//���� ��ġ(x2, y2)�� �����Ͽ� ��� �̷� Ž���ϰ� ��
			mazeRecursive(x1, y1, x2, y2);
		}
	}
	//�̷ΰ� �ƴϹǷ� �̷� ǥ��(9�� ǥ��)�� ����ġ��Ŵ
	maze[x1][y1] = 1;
}

int main(void) {
	int i, rnd_r, rnd_c;

	srand((unsigned int)time(NULL));

	printf("�̷� �� ũ��� 20, �� ũ��� 30\n\n");
	printf("������� �� ��ȣ(0~%d): ", R - 1);
	scanf_s("%d", &start_r);
	printf("������� �� ��ȣ(0~%d): ", C - 1);
	scanf_s("%d", &start_c);

	printf("\n�������� �� ��ȣ(0~%d): ", R - 1);
	scanf_s("%d", &end_r);
	printf("�������� �� ��ȣ(0~%d): ", C - 1);
	scanf_s("%d", &end_c);

	maze[end_r][end_c] = 256;

	printf("\n");
	//��������� �̷� ����
	createMaze(start_r, start_c);

	//���������� �̷� ����
	endToMaze(end_r, end_c);

	//�ټ��� �̷ΰ� �ǰ� ��
	for (i = 0; i < R * C / 100; i++) {
		do {
			rnd_r = rand() % R;
			rnd_c = rand() % C;
		} while (maze[rnd_r][rnd_c] >= 1);
		maze[rnd_r][rnd_c] = 1;
	}

	//�̷� ���
	printf("\n�Ա����� �ⱸ���� ������ �ټ��� �̷�\n\n");
	createdMaze();

	//��� �̷� ���
	printf("\n\n��� �̷� ���\n\n");
	mazeRecursive(-1, -1, start_r, start_c);
	printf("\n\n");

	return 0;
}