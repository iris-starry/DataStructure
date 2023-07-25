#include<stdio.h>
#include<malloc.h>

//이진 트리에 사용할 노드
struct treeNode {
	struct treeNode* llink;
	char data;
	struct treeNode* rlink;
};

//큐 구현에 사용할 노드
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

//큐에 이진트리 현재 노드의 주소를 add함
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

//큐를 사용함
struct treeNode* delete(void) {
	struct treeNode* p;
	struct queueNode* delNode = front;

	if (front == NULL) {
		printf("\nQueue is Empty! 운행을 완료함!");
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

//이진트리 모든 노드 소멸
void deleteAll(struct treeNode* p) {
	if (p != NULL) {
		deleteAll(p->llink);
		deleteAll(p->rlink);
		free(p);
	}
}

//레벨 오더 운행
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

	//이진트리 구성
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

	printf("이진트리를 연결리스트로 구현함!\n");
	printf("메인 함수에서 생성되는 이진트리를 89쪽에 그려보시오.\n");

	printf("\n레벨 오더 운행 결과: ");
	levelOrder(root);

	deleteAll(root);
	printf("\n\n이진트리의 모든 노드를 소멸시킴!\n");

	return 0;
}