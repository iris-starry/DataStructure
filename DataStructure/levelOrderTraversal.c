#include<stdio.h>
#include<malloc.h>

//���� Ʈ���� ����� ���
struct treeNode {
	struct treeNode* llink;
	char data;
	struct treeNode* rlink;
};

//ť ������ ����� ���
struct queueNode {
	struct treeNode* treePtr;
	struct queueNode* link;
};

struct queueNode* rear = NULL, * front = NULL;

enum boolean { false, true };

struct treeNode* newNode(char value) {
	struct treeNode* p;

	p = (struct treeNode*)malloc(sizeof(struct treeNode));
	p->llink = NULL;
	p->data = value;
	p->rlink = NULL;

	return p;
}

//ť�� ����Ʈ�� ���� ����� �ּҸ� add��
enum boolean add(struct treeNode* p) {
	struct queueNode* addNode;

	addNode = (struct queueNode*)malloc(sizeof(struct queueNode));
	if (addNode == NULL) {
		printf("Queue is Full!!\n");
		return false;
	}

	if (rear == NULL) rear = front = addNode;
	else {
		rear->link = addNode;
		rear = rear->link;
	}

	rear->treePtr = p;
	rear->link = NULL;

	return true;
}

//ť�� �����
struct treeNode* delete(void) {
	struct treeNode* p;
	struct queueNode* delNode = front;

	if (front == NULL) {
		printf("\nQueue is Empty! ������ �Ϸ���!");
		return NULL;
	}
	else {
		p = front->treePtr;
		front = front->link;
		if (front == NULL)rear = NULL;
		free(delNode);
		return p;
	}
}

//����Ʈ�� ��� ��� �Ҹ�
void deleteAll(struct treeNode* p) {
	if (p != NULL) {
		deleteAll(p->llink);
		deleteAll(p->rlink);
		free(p);
	}
}

//���� ���� ����
void levelOrder(struct treeNode* p) {
	printf("%c", p->data);
	add(p);

	while ((p = delete()) != NULL) {
		if (p->llink != NULL) {
			printf("->%c", p->llink->data);
			add(p->llink);
		}
		if (p->rlink != NULL) {
			printf("->%c", p->rlink->data);
			add(p->rlink);
		}
	}
}

int main(void) {
	struct treeNode* root;

	//����Ʈ�� ����
	root = newNode('A');
	root->llink = newNode('B');
	root->rlink = newNode('C');
	root->llink->llink = newNode('D');
	root->llink->rlink = newNode('E');
	root->rlink->llink = newNode('F');
	root->rlink->rlink = newNode('G');
	root->llink->llink->rlink = newNode('H');
	root->rlink->llink->llink = newNode('I');
	root->rlink->llink->llink->llink = newNode('J');

	printf("����Ʈ���� ���Ḯ��Ʈ�� ������!\n");
	printf("���� �Լ����� �����Ǵ� ����Ʈ���� 89�ʿ� �׷����ÿ�.\n");

	printf("\n���� ���� ���� ���: ");
	levelOrder(root);

	deleteAll(root);
	printf("\n\n����Ʈ���� ��� ��带 �Ҹ��Ŵ!\n");

	return 0;
}