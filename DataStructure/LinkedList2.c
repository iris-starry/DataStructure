#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student {
	char hakbun[5];
	char name[11];
	int age;
	char tel[14];
	struct student* link;
};

void input(struct student* p) {
	printf("\n학번(4자리): ");
	gets_s(p->hakbun, 5);

	printf("성명(5자이내): ");
	gets_s(p->name, 11);

	printf("나이: ");
	scanf_s("%d", &p->age);
	getchar();

	printf("전화번호: ");
	gets_s(p->tel, 14);
}

void createLinkedList(struct student* p) {
	char yn = 'y';

	while (yn == 'y' || yn == 'Y') {
		p->link = (struct student*)malloc(sizeof(struct student));
		p = p->link;
		input(p);
		p->link = NULL;
		printf("\n계속 입력이면 y 누르고, 그만 입력이면 n 누름: ");
		scanf_s("%c", &yn, 1);
		getchar();
	}
}

void printLinkedList(struct student* p) {
	printf("\n\t- 학생 정보 출력 -\n\n");
	printf("학번\t성명\t나이\t전화번호\n");
	while (p != NULL) {
		printf("%s\t%s\t%d\t%s\n", p->hakbun, p->name, p->age, p->tel);
		p = p->link;
	}
	printf("\n");
}

void deleteNode(struct student* p, int n) {
	int pos = 1;
	struct student* del;

	while (pos < n && p->link != NULL) {
		p = p->link;
		pos++;
	}

	del = p->link;
	p->link = del->link;

	free(del);

}

void insertNode(struct student* p, int n) {
	int pos = 1;
	struct student* ins;

	while (pos < n && p->link != NULL) {
		p = p->link;
		pos++;
	}

	ins = (struct student*)malloc(sizeof(struct student));
	input(ins);
	ins->link = p->link;
	p->link = ins;
}

void allDestruction(struct student* p) {
	struct student* del = p;

	while (p != NULL) {
		p = p->link;
		free(del);
		del = p;
	}
}

int main(void) {
	int n;
	struct student* head;

	head = (struct student*)malloc(sizeof(struct student));
	strcpy_s(head->hakbun, 1, "");
	strcpy_s(head->name, 1, "");
	head->age = 0;
	strcpy_s(head->tel, 1, "");
	head->link = NULL;

	printf("\n\t#생성 작업#\n");
	createLinkedList(head);
	printLinkedList(head->link);

	printf("\n\t#삽입 작업#\n");
	printf("\n몇 번째에 삽입할까요. 숫자로 입력: ");
	scanf_s("%d", &n);
	getchar();
	insertNode(head, n);
	printLinkedList(head->link);

	printf("\n\t#삭제 작업#\n\n");
	printf("몇 번째를 삭제할까요. 숫자로 입력: ");
	scanf_s("%d", &n);
	getchar();
	deleteNode(head, n);
	printLinkedList(head->link);

	allDestruction(head);

	return 0;
}