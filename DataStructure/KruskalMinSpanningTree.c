#include <stdio.h>
#include <stdlib.h>

#define MAX 9

enum bool{ false, true };

//����Ŭ ������ üũ��
enum bool cycleChk(int vertexGrp[], int v1, int v2) {
	int i, grp = vertexGrp[v2];

	if (vertexGrp[v1] == vertexGrp[v2]) return true;
	else {
		for (i = 0; i < MAX; i++)
			if (vertexGrp[i] == grp)vertexGrp[i] = vertexGrp[v1];
	}

	return false;
}

//Kruskal �˰��� ���� �Լ�
void Kruskal(int a[MAX][MAX], int edgeNum) {

	//������ ����ġ�� ���Ե� ����ü edge �غ�
	struct edge {
		int weight;
		int vertex1;
		int vertex2;
	};
	struct edge* temp;
	struct edge** edgeSet;

	int i, j, k = 0;
	int vertexSet[MAX] = { 0, }, vertexGrp[MAX];
	int edgeCnt = 0, b[MAX][MAX] = { 0, };

	edgeSet = (struct edge**)malloc(sizeof(struct edge*) * edgeNum);

	//������ ������ŭ ����ü edge�� ����� ������ �ּҸ� ���ʴ�� �迭 edgeSet�� ������
	for (i = 0; i < MAX; i++) {
		for (j = i + 1; j < MAX; j++) {
			if (a[i][j] > 0) {
				edgeSet[k] = (struct edge*)malloc(sizeof(struct edge));
				edgeSet[k]->weight = a[i][j];
				edgeSet[k]->vertex1 = i;
				edgeSet[k]->vertex2 = j;
				k++;
			}
		}
	}

	//������ ����ġ�� ������
	for (i = 1; i < edgeNum; i++) {
		temp = edgeSet[i];
		for (j = i - 1; j >= 0; j--) {
			if (edgeSet[j]->weight > temp[0].weight) edgeSet[j + 1] = edgeSet[j];
			else break;
		}
		edgeSet[j + 1] = temp;
	}

	printf("\n ����ġ ��������\n");
	for (i = 0; i < edgeNum; i++) {
		printf("(%d, %d) %4d\n", edgeSet[i]->vertex1, edgeSet[i]->vertex2, edgeSet[i]->weight);
	}

	for (i = 0; i < MAX; i++) vertexGrp[i] = i;

	i = 0;
	do {
		if (cycleChk(vertexGrp, edgeSet[i]->vertex1, edgeSet[i]->vertex2) == true) {
			printf("����(%d, %d)�� Cycle �����ǹǷ� �ǳʶ�\n", edgeSet[i]->vertex1, edgeSet[i]->vertex2);
		}
		else {
			vertexSet[edgeSet[i]->vertex1] = 1;
			vertexSet[edgeSet[i]->vertex2] = 1;
			vertexGrp[edgeSet[i]->vertex2] = vertexGrp[edgeSet[i]->vertex1];
			b[edgeSet[i]->vertex1][edgeSet[i]->vertex2] = 1;
			b[edgeSet[i]->vertex2][edgeSet[i]->vertex1] = 1;
			edgeCnt++;
		}
		i++;
	} while (edgeCnt < MAX - 1);

	printf("������ %d�� �����Ͽ����Ƿ� ������ ������\n", edgeCnt);

	for (i = 0; i < MAX; i++) {
		for (j = 0; j < MAX; j++) {
			if (b[i][j] == 0) a[i][j] = 0;
		}
	}
}

int main(void) {

	int i, j, edgeCnt = 0;

	//���� ������ �غ�
	char vertex[MAX] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I' };

	//�׷����� ������ķ� ǥ��
	int adjGraph[MAX][MAX] = { {0, 18, 10, 0, 0, 0, 0, 0, 0},
							{18, 0, 0, 3, 0, 7, 0, 0, 0},
							{10, 0, 0, 11, 0, 0, 55, 0, 0},
							{0, 3, 11, 0, 48, 30, 0, 0, 0},
							{0, 0, 0, 48, 0, 0, 21, 25, 0},
							{0, 7, 0, 30, 0, 0, 0, 37, 0},
							{0, 0, 55, 0, 21, 0, 0, 0, 5},
							{0, 0, 0, 0, 25, 37, 0, 0, 17},
							{0, 0, 0, 0, 0, 0, 5, 17, 0} };

	//���� �����͸� �����
	printf("\n\t      ���� ������\n");
	printf("�ε��� : ");
	for (i = 0; i < MAX; i++) printf("%3d", i);
	printf("\n������ : ");
	for (i = 0; i < MAX; i++) printf("%3c", vertex[i]);

	//���� ����� �����
	printf("\n\n\t      ���� ����\n");
	for (i = 0; i < MAX; i++) {
		for (j = 0; j < MAX; j++) {
			if (adjGraph[i][j] > 0 && i < j) edgeCnt++;
			printf("%4d", adjGraph[i][j]);
		}
		printf("\n");
	}

	//Kruskal �Լ��� ȣ����
	Kruskal(adjGraph, edgeCnt);

	//�ּҺ�� ����Ʈ���� �����
	printf("\nKruskal �ּҺ�� ����Ʈ��\n");
	for (i = 0; i < MAX; i++) {
		for (j = 0; j < MAX; j++) {
			printf("%3d", adjGraph[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	return 0;
}