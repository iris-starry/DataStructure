#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int a[] = { 10, 20, 30, 40, 50 };
	int* p1 = a;
	int b[3][5] = { {3, 6, 9}, {5, 10, 15, 20, 25}, {100, 200} };
	int(*p2)[5] = b;
	int* p3[3] = { b[0], b[1], b[2] };
	char str1[11] = "Meister";
	char* str2 = "Good job!!";

	printf("%d, %d, %d, %d\n", a[1], *(a + 1), b[1][2], *(*(b + 1) + 2));
	printf("%d, %d, %d, %d\n", *(p1 + 1), p1[1], *(*(p2 + 1) + 2), p2[1][2]);
	printf("%d, %d\n", *(*(p3 + 1) + 2), p3[1][2]);

	printf("%s, %s\n", str1, str2);
	printf("%c, %c, %c, %c\n", str1[3], *(str1 + 3), *(str2 + 3), str2[3]);

	// a++; 불가능한 문장
	p1++; //가능한 문장
	printf("%d, %d, %d, %d\n", a[1], *(a + 1), *(p1 + 1), p1[1]);

	// str1++; 불가능한 문장
	str2++; //가능한 문장
	printf("%s, %s\n", str1, str2);

	return 0;
}