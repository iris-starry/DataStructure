#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>

#pragma comment(lib, "winmm.lib") //timeGetTime()함수 사용을 위해

//qsort()에서 사용할 비교 함수(정수 오름차순)
int compareInt(const void* a, const void* b) {

	return *(int*)a - *(int*)b;

}

void SelectionSort(int a[], int n) {
	int i, j, min, index;

	for (i = 0; i < n - 1; i++) {
		min = a[i];
		index = i;
		for (j = i + 1; j < n; j++) {
			if (a[j] < min) {
				min = a[j];
				index = j;
			}
		}
		a[index] = a[i];
		a[i] = min;
	}
}

void InsertionSort(int a[], int n) {
	int i, j, temp;
	for (i = 1; i < n; i++) {
		temp = a[i];
		for (j = i - 1; j >= 0; j--) {
			if (temp >= a[j]) break;
			a[j + 1] = a[j];
		}
		a[j + 1] = temp;
	}
}

void BubbleSort(int a[], int n) {
	int i = 0, j, temp, flag = 1;
	while (flag == 1) {
		flag = 0;
		i++;
		for (j = 0; j < n - i; j++) {
			if (a[j] > a[j + 1]) {
				temp = a[j]; a[j] = a[j + 1]; a[j + 1] = temp;
				flag = 1;
			}
		}
	}
}

void ShellSort(int a[], int n) {
	int i, j, t, temp;
	for (t = n / 2; t > 0; t /= 2) {
		for (i = t; i < n; i++) {
			temp = a[i];
			for (j = i; j >= t; j -= t) {
				if (temp >= a[j - t]) break;
				a[j] = a[j - t];
			}
			a[j] = temp;
		}
	}
}

void QuickSort(int a[], int left, int right) {
	int i, j, pivot, temp;

	if (left < right) {
		pivot = a[(left + right) / 2];
		a[(left + right) / 2] = a[left];
		a[left] = pivot;
		i = left;
		j = right;
		while (i < j) {
			while (i < right && a[i] <= pivot) i++;
			while (j > left && a[j] >= pivot) j--;
			if (i < j) {
				temp = a[i];
				a[i] = a[j];
				a[j] = temp;
			}
		}

		a[left] = a[j];
		a[j] = pivot;

		QuickSort(a, left, i - 1);
		QuickSort(a, i + 1, right);
	}
}

void HeapSort(int a[], int n) {
	int i, parent, child, value;

	for (i = n / 2; i >= 1; i--) {
		value = a[i];
		parent = i;
		while ((child = parent * 2) <= n) {
			if (child + 1 <= n && a[child] < a[child + 1]) child++;
			if (value >= a[child]) break;
			a[parent] = a[child];
			parent = child;
		}
		a[parent] = value;
	}

	while (n > 1) {
		value = a[n];
		a[n--] = a[1];
		parent = 1;
		while ((child = parent * 2) <= n) {
			if (child + 1 <= n && a[child] < a[child + 1]) child++;
			if (value >= a[child]) break;
			a[parent] = a[child];
			parent = child;
		}
		a[parent] = value;
	}
}

void Merge(int a[], int left, int mid, int right) {
	int i = left, j = mid + 1, k = 0;
	int* bk = (int*)malloc(sizeof(int) * (right - left + 1));

	while (i <= mid && j <= right)
		if (a[i] <= a[j]) bk[k++] = a[i++];
		else bk[k++] = a[j++];

	if (i <= mid) while (i <= mid) bk[k++] = a[i++];
	else while (j <= right) bk[k++] = a[j++];
	k = 0;
	for (i = left; i <= right; i++) a[i] = bk[k++];
	free(bk);
}

void Division(int a[], int left, int right) {
	int mid;

	if (left < right) {
		mid = (left + right) / 2;
		Division(a, left, mid);
		Division(a, mid + 1, right);
		Merge(a, left, mid, right);
	}
}

void RadixSort(int* a, int n) {
	int i, max = a[0], digit_base = 1;
	int digit_cnt[10] = { 0 };
	int* bucket = (int*)malloc(sizeof(int) * n);

	for (i = 0; i < n; i++)
		if (a[i] > max) max = a[i];

	while (digit_base <= max) {
		for (i = 0; i < n; i++)
			digit_cnt[a[i] / digit_base % 10]++;
		for (i = 1; i < 10; i++)
			digit_cnt[i] += digit_cnt[i - 1];
		for (i = n - 1; i >= 0; i--)
			bucket[--digit_cnt[a[i] / digit_base % 10]] = a[i];
		for (i = 0; i < n; i++) a[i] = bucket[i];
		for (i = 0; i < 10; i++) digit_cnt[i] = 0;
		digit_base *= 10;
	}
	free(bucket);
}

int main(void) {
	int* a, * b, * c, * d, * e1, * e2, * f, * g, * h;
	int i, n = 50000;
	long value;

	unsigned __int64 t1, t2, CPU_Clock_Per_Sec;
	unsigned long t3;

	//Sleep(1000), sleep(1000)함수는 1초보다 조금 더 지연되므로
	//Sleep()는 윈도우즈에서 지원, sleep()는 유닉스, 리눅스에서 지원

	//아래 방법으로 1초 지연
	timeBeginPeriod(1); //timer 시간 간격을 1ms로 설정

	t1 = __rdtsc(); //현재 CPU 클럭을 구함

	//1초 지연
	t3 = timeGetTime();
	for (;;) if (timeGetTime() - t3 >= 1000) break;

	t2 = __rdtsc(); //1초 지난 후 CPU 클럭을 구함

	timeEndPeriod(1); //timer 시간 간격을 기본으로 재설정

	//1초 전과 후의 CPU 클럭 차이를 계산하면 초당 CPU 클럭이 됨
	CPU_Clock_Per_Sec = t2 - t1;

	a = (int*)malloc(sizeof(int) * n);
	b = (int*)malloc(sizeof(int) * n);
	c = (int*)malloc(sizeof(int) * n);
	d = (int*)malloc(sizeof(int) * n);
	e1 = (int*)malloc(sizeof(int) * n);
	e2 = (int*)malloc(sizeof(int) * n);
	f = (int*)malloc(sizeof(int) * n);
	g = (int*)malloc(sizeof(int) * n);
	h = (int*)malloc(sizeof(int) * n);

	for (i = 0; i < n; i++) {
		value = rand() << rand() % 16;
		value = value | rand();
		a[i] = value;
		b[i] = a[i];
		c[i] = a[i];
		d[i] = a[i];
		e1[i] = a[i];
		e2[i] = a[i];
		f[i] = a[i];
		g[i] = a[i];
		h[i] = a[i];
	}

	t1 = __rdtsc();
	SelectionSort(a, n);
	t2 = __rdtsc();
	printf("\n%d개 데이터 선택정렬 시간 : %.16lf초 소요\n", n, (double)(t2 - t1) / CPU_Clock_Per_Sec);
	t1 = __rdtsc();
	SelectionSort(a, n);
	t2 = __rdtsc();
	printf("\n%d개 정렬된 데이터 선택정렬 시간 : %.16lf초 소요\n", n, (double)(t2 - t1) / CPU_Clock_Per_Sec);

	t1 = __rdtsc();
	InsertionSort(b, n);
	t2 = __rdtsc();
	printf("\n%d개 데이터 삽입정렬 시간 : %.16lf초 소요\n", n, (double)(t2 - t1) / CPU_Clock_Per_Sec);
	t1 = __rdtsc();
	InsertionSort(b, n);
	t2 = __rdtsc();
	printf("\n%d개 정렬된 데이터 삽입정렬 시간 : %.16lf초 소요\n", n, (double)(t2 - t1) / CPU_Clock_Per_Sec);

	t1 = __rdtsc();
	BubbleSort(c, n);
	t2 = __rdtsc();
	printf("\n%d개 데이터 버블정렬 시간 : %.16lf초 소요\n", n, (double)(t2 - t1) / CPU_Clock_Per_Sec);
	t1 = __rdtsc();
	BubbleSort(c, n);
	t2 = __rdtsc();
	printf("\n%d개 정렬된 데이터 버블정렬 시간 : %.16lf초 소요\n", n, (double)(t2 - t1) / CPU_Clock_Per_Sec);

	t1 = __rdtsc();
	ShellSort(d, n);
	t2 = __rdtsc();
	printf("\n%d개 데이터 쉘정렬 시간 : %.16lf초 소요\n", n, (double)(t2 - t1) / CPU_Clock_Per_Sec);
	t1 = __rdtsc();
	ShellSort(d, n);
	t2 = __rdtsc();
	printf("\n%d개 정렬된 데이터 쉘정렬 시간 : %.16lf초 소요\n", n, (double)(t2 - t1) / CPU_Clock_Per_Sec);

	t1 = __rdtsc();
	QuickSort(e1, 0, n - 1);
	t2 = __rdtsc();
	printf("\n%d개 데이터 퀵정렬 시간 : %.16lf초 소요\n", n, (double)(t2 - t1) / CPU_Clock_Per_Sec);
	t1 = __rdtsc();
	QuickSort(e1, 0, n - 1);
	t2 = __rdtsc();
	printf("\n%d개 정렬된 데이터 퀵정렬 시간 : %.16lf초 소요\n", n, (double)(t2 - t1) / CPU_Clock_Per_Sec);

	t1 = __rdtsc();
	qsort(e2, n, sizeof(int), compareInt);
	t2 = __rdtsc();
	printf("\n\n%d개 qsort() 수행 시간 : %.16lf초 소요\n", n, (double)(t2 - t1) / CPU_Clock_Per_Sec);

	t1 = __rdtsc();
	HeapSort(f, n - 1);
	t2 = __rdtsc();
	printf("\n\n%d개 데이터 힙정렬 시간 : %.16lf초 소요\n", n, (double)(t2 - t1) / CPU_Clock_Per_Sec);
	t1 = __rdtsc();
	HeapSort(f, n - 1);
	t2 = __rdtsc();
	printf("\n%d개 정렬된 데이터 힙정렬 시간 : %.16lf초 소요\n", n, (double)(t2 - t1) / CPU_Clock_Per_Sec);

	t1 = __rdtsc();
	Division(g, 0, n - 1);
	t2 = __rdtsc();
	printf("\n%d개 데이터 병합정렬 시간 : %.16lf초 소요\n", n, (double)(t2 - t1) / CPU_Clock_Per_Sec);
	t1 = __rdtsc();
	Division(g, 0, n - 1);
	t2 = __rdtsc();
	printf("\n%d개 정렬된 데이터 병합정렬 시간 : %.16lf초 소요\n", n, (double)(t2 - t1) / CPU_Clock_Per_Sec);

	t1 = __rdtsc();
	RadixSort(h, n);
	t2 = __rdtsc();
	printf("\n%d개 데이터 기수정렬 시간 : %.16lf초 소요\n", n, (double)(t2 - t1) / CPU_Clock_Per_Sec);
	t1 = __rdtsc();
	RadixSort(h, n);
	t2 = __rdtsc();
	printf("\n%d개 정렬된 데이터 기수정렬 시간 : %.16lf초 소요\n", n, (double)(t2 - t1) / CPU_Clock_Per_Sec);

	free(a);
	free(b);
	free(c);
	free(d);
	free(e1);
	free(e2);
	free(f);
	free(g);
	free(h);

	return 0;
}