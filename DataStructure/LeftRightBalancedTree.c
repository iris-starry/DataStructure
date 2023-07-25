#include<stdio.h>
#include<stdlib.h>

#define NEW (struct node *)malloc(sizeof(struct node))

//���� Ʈ�� ������ ����� ��� ����
struct node {
	struct node* llink;
	int data;
	struct node* rlink;
};

//��� ��� ����
void deleteAll(struct node* delNode) {
	if (delNode != NULL) {
		deleteAll(delNode->llink);
		deleteAll(delNode->rlink);
		printf("% 5d", delNode->data);
		free(delNode);
	}
}

//�¿� ������ ���� Ʈ���� �����ϰ� ù ��° ������ ����� �ּҸ� ��ȯ��
struct node* binaryTree(int a[], int left, int right) {
	int mid;
	struct node* p = NULL;

	if (left <= right) {
		mid = (left + right) / 2;
		p = NEW;
		p->data = a[mid];
		p->llink = binaryTree(a, left, mid - 1);
		p->rlink = binaryTree(a, mid + 1, right);
	}
	return p;
}

int main(void) {
	int a[] = { 3, 5, 7, 10, 15, 17, 20, 25, 28, 31, 33, 35 };
	int n = sizeof(a) / sizeof(int);
	struct node* root, * p;

	root = binaryTree(a, 0, n - 1);

	printf("��Ʈ���� ����Ͽ� ���� �ڽ��ʸ������� ������ : ");
	p = root;
	while (p != NULL) {
		printf("% 5d", p->data);
		p = p->llink;
	}
	printf("\n");

	//���� Ʈ�� �Ҹ�
	printf("��尡 ������� ���� : ");
	deleteAll(root);
	printf("\n");

	return 0;
}