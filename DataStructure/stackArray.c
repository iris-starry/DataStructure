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
	//���������� push()��
	push(10); push(20); push(30); push(40); push(50); push(60);

	//overflow �߻����� push()���� �ʰ�, ��stack overflow!���� ���
	push(70);

	//���������� pop()��
	printf("1st pop: %d\n", pop()); printf("2nd pop: %d\n", pop());
	printf("3rd pop: %d\n", pop());

	//���������� push()��
	push(80);

	// ���������� pop()��
	printf("4th pop: %d\n", pop()); printf("5th pop: %d\n", pop());
	printf("6th pop: %d\n", pop()); printf("7th pop: %d\n", pop());

	//top�� -1�̹Ƿ� underflow �߻�. ��stack underflow!���� ����ϰ� ���Ϲ��� -1�� �����
	printf("8th pop: %d\n", pop());

	return 0;
}