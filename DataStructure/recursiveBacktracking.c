/*
������ ��������� ������ �� �ִ� �� ����(�¿���� ��)�� ���Ƿ� �����Ͽ� ���� �㹰�� ����(�̷� ǥ��)�ϴٰ�
�� �̻� ������ �� ������ �������� ���ư��鼭 ������ �� �ִ� �ٸ� �������� ��� �̷θ� ����� ������ ���
������ �� ���� ������ �迭 ������ ����ų� ���� �̷θ� ������ ���
���� �̷������� ���� �㹰�� ����Ŭ�� �����Ǿ� �ɵ��� ��ΰ� ��������� ������ �����Ǿ�� ��
*/

/*
�̷� �࿭�� ���� �����ϴ� �������
�̷� ���� ���� c, ���� r���� ������� �� ���
�̷� �࿭�� �� ũ��� (r*2 + 1), �� ũ��� (c*2 + 1)�� �غ�
*/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

//���� ������ �̷� ũ��. row�� ��, col�� �� ũ��� 3 �̻��� ��
int row, col;

//2���� �迭�� ¦�� ��� ���� ��, Ȧ�� ��� ���� �̷� ��
//�̷θ� ����� �ͷ� ȣ�� ������� ����� ����
void mazeCreating(char** mazeMark, int i, int j) {
	int view_i, view_j, dir;
	int move[4][2] = { {-2,0},{2,0},{0,-2},{0,2} };//�����¿�

	//�����¿� ��� ���� �� ������ �ݺ�
	//������� 16���� ǥ�õ�(�����ʿ��� 5��° bit�� 1��)
	while ((mazeMark[i][j] & 15) < 15) { //������� ǥ������ �ʴ´ٸ� while (mazeMark[i][j] < 15) {

		do {

			dir = rand() % 4; //4���� �� ������ ����

		} while ((mazeMark[i][j] & (1 << dir)) >= 1); //dir�� ���캻 �����̸� dir �ٽ� ����

		//�̵� ������ ǥ����. dir�� 3�̸� �����ʿ��� �� ��°�� 1�� �ǰ� ��. 00000100
		//4���� ��� ���캸�Ҵٸ� 00001111 => 15
		mazeMark[i][j] |= (1 << dir);

		//�̵��� ���� ��ǥ�� ����
		view_i = i + move[dir][0];
		view_j = j + move[dir][1];

		//�̵��� ���� ��ǥ�� �̷� �࿭ �������� �ְ�
		if (view_i >= 1 && view_i <= row - 2 && view_j >= 1 && view_j <= col - 2) {

			//Ž���� ���� �ʾҴٸ�
			if (mazeMark[view_i][view_j] == 0) {

				//�̷� ���� ǥ��. ���� �㹰��
				switch (dir) {

				case 0:mazeMark[i - 1][j] |= (1 << 0); break;

				case 1:mazeMark[i + 1][j] |= (1 << 1); break;

				case 2:mazeMark[i][j - 1] |= (1 << 2); break;

				case 3:mazeMark[i][j + 1] |= (1 << 3);

				}

				//�̵��� �濡�� ���� ������ ��Ǯ����
				mazeCreating(mazeMark, view_i, view_j);

			}

		}

	}

}

int main(void) {
	int i, j;
	char** mazeMark;

	printf("���� ������ �̷��� �� ũ��<3�̻��� Ȧ��>: ");

	do {

		scanf_s("%d", &row);

		if (row < 3 || row % 2 == 0) printf("\n�ٽ� �Է��ϼ���: ");

		else break;

	} while (1);

	printf("\n���� ������ �̷��� �� ũ��<3�̻��� Ȧ��>: ");

	do {

		scanf_s("%d", &col);

		if (col < 3 || col % 2 == 0) printf("\n�ٽ� �Է��ϼ���: ");

		else break;

	} while (1);

	//2���� �迭ó�� ����� mazeMark �غ�
	mazeMark = (char**)malloc(sizeof(char*) * row);

	for (i = 0; i < row; i++) mazeMark[i] = (char*)malloc(sizeof(char) * col);

	//��� ����� ��Ž������ ä��
	for (i = 0; i < row; i++) {

		for (j = 0; j < col; j++) {

			mazeMark[i][j] = 0;

		}

	}

	srand((unsigned int)time(NULL));

	//������� ���Ƿ� ����
	i = rand() % (row - 1);
	j = rand() % (col - 1);

	//�࿭�� ¦���̸� Ȧ���� ����
	if (i % 2 == 0)i++;
	if (j % 2 == 0)j++;

	//����� ǥ��
	mazeMark[i][j] |= (1 << 4);

	//����� �ͷ� ��� ȣ��
	mazeCreating(mazeMark, i, j);

	//�̷θ� ����� 
	printf("\n\n����� �ͷ�(Recursive Backtracking) ���");
	printf("\n\n��:�����, ��:�̷λ��� ����, ��:��\n\n");

	for (i = 0; i < row; i++) {

		for (j = 0; j < col; j++) {

			if (mazeMark[i][j] & 16) printf("��");

			else if (i % 2 == 1 && j % 2 == 1) printf("��");

			else if (mazeMark[i][j] & 1) printf("��");

			else if (mazeMark[i][j] & 2) printf("��");

			else if (mazeMark[i][j] & 4) printf("��");

			else if (mazeMark[i][j] & 8) printf("��");

			else printf("��");

		}

		printf("\n");

	}

	printf("\n\n�̷� ���� ���� ����");
	printf("\n\n��:�����, ��:��\n\n");

	for (i = 0; i < row; i++) {

		for (j = 0; j < col; j++) {

			if (mazeMark[i][j] & 16) printf("��");

			else if ((i % 2 == 1 && j % 2 == 1) || mazeMark[i][j] > 0) printf("��");

			else printf("��");

		}

		printf("\n");

	}

	return 0;

}