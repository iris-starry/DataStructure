#include<stdio.h>
#include<stdlib.h>

#define NEW (struct node *)malloc(sizeof(struct node))

//이진 트리 구성에 사용할 노드 정의
struct node {
	struct node* llink;
	int data;
	struct node* rlink;
};

//모든 노드 제거
void deleteAll(struct node* delNode) {
	if (delNode != NULL) {
		deleteAll(delNode->llink);
		deleteAll(delNode->rlink);
		printf("% 5d", delNode->data);
		free(delNode);
	}
}

//좌우 균형된 이진 트리를 생성하고 첫 번째 생성된 노드의 주소를 반환함
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

	printf("루트에서 출발하여 왼쪽 자식쪽만으로의 데이터 : ");
	p = root;
	while (p != NULL) {
		printf("% 5d", p->data);
		p = p->llink;
	}
	printf("\n");

	//이진 트리 소멸
	printf("노드가 사라지는 순서 : ");
	deleteAll(root);
	printf("\n");

	return 0;
}