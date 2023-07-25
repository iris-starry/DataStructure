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

//�̷� Ž��
enum boolean mazeSearch(int maze[M][N]) {
	int in_x, in_y; //�����
	int out_x, out_y; //������
	int current_x, current_y; //���� ��ġ
	int view_x, view_y; //Ž�� ��ġ

	int d = 0; // d�� �̵��� �� �ִ� 0~7 ���� �� �ϳ��� 0���� ���
	//0������ ��, 1������ ����, 2������ ��, 3������ ����, 4������ ��, 5������ �»�, 6������ ��, 7������ ���

	//���⺰ ��,�� ����
	int move[8][2] = { { 0,1 },{ 1,1 },{ 1,0 },{ 1,-1 },{ 0,-1 },{ -1,-1 },{ -1,0 },{ -1,1 } };

	printf("��� ��: "); scanf_s("%d", &in_x);
	printf("��� ��: "); scanf_s("%d", &in_y);
	printf("���� ��: "); scanf_s("%d", &out_x);
	printf("���� ��: "); scanf_s("%d", &out_y);

	current_x = in_x;
	current_y = in_y;

	while (1) {
		while (d < 8) {
			view_x = current_x + move[d][0];
			view_y = current_y + move[d][1];

			//���� �����ϸ�
			if (view_x >= 0 && view_x < M && view_y >= 0 && view_y < N && maze[view_x][view_y] == 1) {
				maze[current_x][current_y] = 9; // �̷� ǥ��

				//���� ��ġ�� ���� ������ push()�ϰ�, push() �ȵǸ� �̷� ����!
				if (!push(current_x, current_y, d + 1)) return false;

				//���� �������� ����
				current_x = view_x;
				current_y = view_y;
				//�������� �����Ͽ��ٸ�
				if (current_x == out_x && current_y == out_y) {
					//������ �̷� ǥ��
					maze[current_x][current_y] = 9;
					//�̷� ã��!
					return true;
				}
				//0���⿡�� Ž�� �ݺ�
				d = 0;

			}
			//���� ���� Ž��
			else d++;

		}

		//���� ��ġ���� �� �̻� ������ ���� �����Ƿ�
		maze[current_x][current_y] = 2; //���� ��ġ Ž�� �Ϸ� ǥ��

		//stack���� pop()�Ͽ� �� ��ġ���� ��Ž��. stack�� ��� ������ �̷� ����!
		if (pop(&current_x, &current_y, &d) == false) return false;

	}

}

int main(void) {
	// 0�� ��, 1�� �� �� �ִ� ���
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

	if (mazeSearch(maze) == false) printf("�ⱸ���� �̷� ����!!\n\n");
	else {
		printf("\n�̷� ã�� �Ϸ�\n");
		for (int i = 0; i < M; i++) {
			for (int j = 0; j < N; j++)
				if (maze[i][j] == 9) printf("* "); // �̷��̸�  * ���
				else printf("%d ", maze[i][j] == 0 ? 0 : 1); //�̷� �ƴϸ� �ʱ� ������ ���
			printf("\n");
		}
	}
	printf("\n");

	return 0;
}