#include <stdio.h>
#include <malloc.h>
#define SIZE 5

struct node {
	char data;
	struct node* next;
};
struct node* G[SIZE];

int main() {
	int i, n;
	char dd;
	struct node* t;

	printf("\n ������ ���� �Է� : ");
	scanf_s("%d", &n);

	for (i = 0; i < n; i++) { // ������ ������ŭ �ݺ�. ���� ������ ���� ������ �ݺ��ؼ� �Է�
		getchar(); // �Է� ������ Enter�� ���
		printf("\n\n ���� ���� ������ : ");
		scanf_s("%c", &dd, 1);
		G[i] = (struct node*)malloc(sizeof(struct node));
		t = G[i]; t->data = dd; t->next = NULL;
		getchar(); // �Է� ������ Enter�� ���
		printf("\n ���� ���� ������ : ");
		scanf_s("%c", &dd, 1);
		while (dd != '0') { // �����Ͱ� 0�� �ƴϸ� ��� ���� ����Ʈ�� �����Ѵ�.
			t->next = (struct node*)malloc(sizeof(struct node));
			t = t->next; t->data = dd; t->next = NULL;
			getchar(); // �Է� ������ Enter�� ���
			printf("\n ���� ���� ������(������ 0 �Է�) : ");
			scanf_s("%c", &dd, 1);
		}
	}

	// ���� ����Ʈ ���
	for (i = 0; i < n; i++) {
		printf("\n ���� %d : ", i);
		t = G[i];
		while (t != NULL) {
			if (t->next != NULL) printf("%c -> ", t->data);
			else printf("%c", t->data);
			t = t->next;
		}
	}

	return 0;
}