#include<stdio.h>
#define SIZE 6

int stack[SIZE] = { 0, };
int top = -1;

int push(int data) {
	if (top == SIZE - 1) {
		printf("stack overflow!\n");
		return -1;
	}
	stack[++top] = data;

	return 0;
}

int pop(void) {
	if (top == -1) {
		printf("stack underflow!\n");
		return -1;
	}

	return stack[top--];
}

int main(void) {
	//정상적으로 push()됨
	push(10); push(20); push(30); push(40); push(50); push(60);

	//overflow 발생으로 push()되지 않고, ’stack overflow!’를 출력
	push(70);

	//정상적으로 pop()됨
	printf("1st pop: %d\n", pop()); printf("2nd pop: %d\n", pop());
	printf("3rd pop: %d\n", pop());

	//정상적으로 push()됨
	push(80);

	// 정상적으로 pop()됨
	printf("4th pop: %d\n", pop()); printf("5th pop: %d\n", pop());
	printf("6th pop: %d\n", pop()); printf("7th pop: %d\n", pop());

	//top은 -1이므로 underflow 발생. ‘stack underflow!’를 출력하고 리턴받은 -1도 출력함
	printf("8th pop: %d\n", pop());

	return 0;
}