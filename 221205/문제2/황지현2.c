#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100

typedef struct element {
	char name[20];
	int age;
}element;
element merged[50] = { 0 };


void listMerge(element a[], int i, int m, int n) { //left,mid,right
	int j, k, l, t;
	j = m + 1;
	k = i;
	l = i;

	while (l <= m && j <= n) {
		if (a[l].age <= a[j].age) {
			merged[k++] = a[l++];
		}
		else {
			merged[k++] = a[j++];
		}
	}
	if (l > m) {
		for (t = j;t <= n;t++) {
			merged[k++] = a[t];
		}
	}
	else {
		for (t = l;t <= m;t++) {
			merged[k++] = a[t];
		}
	}
	//left~right만큼 정렬된 배열인 merged를 a에 덮음
	for (int q = i;q <= n;q++) {
		a[q] = merged[q];
	}
	return;
}


int rmergeSort(element a[], int left, int right) {
	if (left >= right) {
		return left;
	}
	int mid = (left + right) / 2;
	rmergeSort(a, left, mid);
	rmergeSort(a, mid + 1, right);
	listMerge(a, left, mid, right);
}


void main() {
	int n;
	FILE* fp = fopen("in.txt", "r");
	fscanf(fp, "%d", &n);
	element data[50] = { NULL };
	for (int i = 1;i <= n;i++) fscanf(fp, "%s %d", data[i].name, &data[i].age);
	printf("[Recursive merge sort]\n");
	rmergeSort(data, 1, n);
	for (int i = 1;i <= n;i++) printf("%8s: %6d\n", data[i].name, data[i].age);
	fclose(fp);
}