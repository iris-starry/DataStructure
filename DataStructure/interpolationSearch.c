#include<stdio.h>

int interpolationSearch(int a[], int n, int key) {
    int left = 0, right = n - 1, mid;

    while (left <= right) {
        if (a[left] < a[right]) { // 나눗셈의 분모, 0 방지
            mid = left + (right - left) * (key - a[left]) / (a[right] - a[left]);
            if (mid > right) mid = right;
            if (mid < left) mid = left;
        }
        else mid = left;
        
        if (key == a[mid]) return mid;
        else if (key > a[mid]) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

int main(void) {
    int i, key, index, n;
    int a[] = { 3,7,10,12,14,18,21,33,35,48 };

    n = sizeof(a) / sizeof(int);
    printf("찾을 대상 : ");
    for (i = 0; i < n; i++) {
        printf("%5d", a[i]);
    }
    printf("\n 찾을 값 : ");
    scanf_s("%d", &key);
    index = interpolationSearch(a, n, key);
    if (index >= 0) printf("\n%d을(를) %d에서 찾음! \n", key, index);
    else printf("\n찾고자 하는 값이 없음!\n");
    return 0;
}