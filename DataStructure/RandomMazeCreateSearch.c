#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//�̷� ũ��
#define R 20
#define C 30
//���� ũ��
#define MAX R*C

//�̷�(8����) �迭 �غ�. 1�� �̷�, 0�� ��. �ʱ�� ��� 0���� ����
int maze[R][C] = { 0 };

//���ñ����� ����� �迭 �غ�
int stack[MAX][3] = { 0, };
int top = -1;

enum bool{ false, true };

struct direction {
	int r;
	int c;
};

//0������ ��, 1������ ����, 2������ ��, 3������ ����, 4������ ��, 5������ �»�, 6������ ��, 7������ ���
//move �迭�� �� ���⿡ ���� ������
struct direction move[8] = { {0,1},{1,1}, {1,0},{1,-1},{0,-1},{-1,-1},{-1,0},{-1,1} };

//���� ���������� �̷� ���� ���θ� �Ǵ�
enum bool nextCheck(int maze_r, int maze_c, int next_r, int next_c) {
	int i;

	for (i = 0; i < 8; i++) {
		if (next_r + move[i].r < 0 || next_c + move[i].c < 0 || next_r + move[i].r >= R || next_c + move[i].c >= C) continue;
		if (next_r + move[i].r == maze_r && next_c + move[i].c == maze_c)continue;
		if (maze[next_r + move[i].r][next_c + move[i].c] >= 1) return false;
	}
	return true;
}

//����� ������� ������ �̷� ����
void mazeCreate(int maze_r, int maze_c) {
	int dir, next_r, next_c;

	while (maze[maze_r][maze_c] < 255) { //8���� ��� ���� �� ������ �ݺ�
		do {
			dir = rand() % 8; //8���� �� ������ ����
		} while ((maze[maze_r][maze_c] & (1 << dir)) == 1);

		//�̵� ������ ǥ����. dir�� 3�̸� �����ʿ��� �� ��°�� 1�� �ǰ� ��.
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

//������ �̷� ��� �Լ�
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

//���ÿ� Ǫ��
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

//���ÿ��� ��
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

//�̷� Ž��
enum bool mazeSearch(void) {
	int current_r, current_c, out_r, out_c;
	int view_r, view_c;
	int d = 0; // d�� �̵��� �� �ִ� 0~8 ���� �� �ϳ��� 0���� ���
	//0������ ��, 1������ ����, 2������ ��, 3������ ����, 4������ ��, 5������ �»�, 6������ ��, 7������ ���
	int move[8][2] = { { 0,1 },{ 1,1 },{ 1,0 },{ 1,-1 },{ 0,-1 },{ -1,-1 },{ -1,0 },{ -1,1 } };

	printf("��� ��(0~%d): ", R - 1); scanf_s("%d", &current_r);
	printf("��� ��(0~%d): ", C - 1); scanf_s("%d", &current_c);
	printf("���� ��(0~%d): ", R - 1); scanf_s("%d", &out_r);
	printf("���� ��(0~%d): ", C - 1); scanf_s("%d", &out_c);

	while (1) {
		while (d < 8) {
			view_r = current_r + move[d][0];
			view_c = current_c + move[d][1];
			if (view_r >= 0 && view_r < R && view_c >= 0 && view_c < C && maze[view_r][view_c] == 1) {
				maze[current_r][current_c] = 9; // �̷� ǥ��
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
		maze[current_r][current_c] = 2; // ���ƿ� ��� ǥ��
		if (pop(&current_r, &current_c, &d) == false) return false;
	}
}

int main(void) {
	int start_r, start_c, i, j;

	srand((unsigned int)time(NULL));
	start_r = (int)rand() % R;
	start_c = (int)rand() % C;

	//������ ��������� �̷� ����
	mazeCreate(start_r, start_c);

	//�̷� ���
	printf("\t\t���Ƿ� ������� �̷�\n");
	mazePrint();
	printf("\n\n");

	//�̷� ã�� ����ϱ�
	if (mazeSearch() == false) printf("�ⱸ���� �̷� ����!!\n\n");
	else {
		printf("\n\t\t�Ա����� �ⱸ�����̷�\n");
		for (i = 0; i < R; i++) {
			for (j = 0; j < C; j++)
				if (maze[i][j] == 9) printf("* "); // �̷��̸�  * ���
				else printf("%d ", maze[i][j] == 0 ? 0 : 1); //�̷� �ƴϸ� �ʱ� ������ ���
			printf("\n");
		}
	}
	printf("\n");

	return 0;
}