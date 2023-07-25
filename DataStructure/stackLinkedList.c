#include <stdio.h>
#include <stdlib.h>
#define SIZE 10

struct node {
	int data;
	struct node* link;
};

struct node* top = NULL;
int cnt = 0;

int push(int data) {
	struct node* addNode;

	if (cnt >= SIZE) {
		printf("Stack Overflow!\n");
		return -1;
	}

	addNode = (struct node*)malloc(sizeof(struct node));
	addNode->data = data;
	addNode->link = top;
	top = addNode;
	cnt++;

	return 0;
}

int pop(void) {
	int data;
	struct node* delNode = top;

	if (top == NULL) {
		printf("Stack Underflow!\n");
		return -1;
	}

	data = top->data;
	top = top->link;
	free(delNode);
	cnt--;

	return data;
}

int main(void) {
	struct node* freeNode;

	push(10); push(20); push(30);
	printf("POP: %d\n", pop());
	push(40); push(50);

	printf("스택 유효 데이터(top에서 base까지): ");
	while (top != NULL) {
		printf("%d, ", top->data);
		freeNode = top;
		top = top->link;
		free(freeNode);
	}

	return 0;
}