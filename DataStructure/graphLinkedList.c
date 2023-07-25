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

	printf("\n 정점의 개수 입력 : ");
	scanf_s("%d", &n);

	for (i = 0; i < n; i++) { // 정점의 개수만큼 반복. 시작 정점과 인접 정점을 반복해서 입력
		getchar(); // 입력 버퍼의 Enter를 비움
		printf("\n\n 시작 정점 데이터 : ");
		scanf_s("%c", &dd, 1);
		G[i] = (struct node*)malloc(sizeof(struct node));
		t = G[i]; t->data = dd; t->next = NULL;
		getchar(); // 입력 버퍼의 Enter를 비움
		printf("\n 인접 정점 데이터 : ");
		scanf_s("%c", &dd, 1);
		while (dd != '0') { // 데이터가 0이 아니면 계속 인접 리스트를 구성한다.
			t->next = (struct node*)malloc(sizeof(struct node));
			t = t->next; t->data = dd; t->next = NULL;
			getchar(); // 입력 버퍼의 Enter를 비움
			printf("\n 다음 인접 데이터(없으면 0 입력) : ");
			scanf_s("%c", &dd, 1);
		}
	}

	// 인접 리스트 출력
	for (i = 0; i < n; i++) {
		printf("\n 정점 %d : ", i);
		t = G[i];
		while (t != NULL) {
			if (t->next != NULL) printf("%c -> ", t->data);
			else printf("%c", t->data);
			t = t->next;
		}
	}

	return 0;
}