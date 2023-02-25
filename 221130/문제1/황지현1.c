#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 500

typedef struct element {
	char name[20];
	int age;
}element;

void printlist(element a[], int n);
void merge(element iniList[], element mergedList[], int i, int m, int n);
void mergePass(element initList[], element mergedList[], int n, int s);
void mergeSort(element a[], int n);

void main() {
	int n;
	FILE* fp = fopen("in.txt", "r");
	fscanf(fp, "%d", &n);
	element data[20];
	for (int i = 1;i <= n;i++) fscanf(fp, "%s %d", data[i].name, &data[i].age);
	printf("[Iterative merge sort]\n");
	mergeSort(data, n);
	fclose(fp);
}

void printlist(element a[], int n) {
	for (int i = 1;i <=n;i++) printf("%6s: %5d\n", a[i].name, a[i].age);
}

void merge(element initList[], element mergedList[], int i, int m, int n) {
	int j, k, t;
	j = m + 1;
	k = i;
	while (i <= m && j <= n) {
		if (initList[i].age >= initList[j].age) mergedList[k++] = initList[i++];
		else mergedList[k++] = initList[j++];
	}
	if (i > m) {
		for (t = j;t <= n;t++) mergedList[t] = initList[t];
	}
	else {
		for (t = i;t <= m;t++) mergedList[k + t - i] = initList[t];
	}
}

void mergePass(element initList[], element mergedList[], int n, int s) {
	int i, j;
	for (i = 1;i <= n - 2 * s + 1;i += 2 * s) {
		merge(initList, mergedList, i, i + s - 1, i + 2 * s - 1);
	}
	if (i + s - 1 < n)
		merge(initList, mergedList, i, i + s - 1, n);
	else {
		for (j = i;j <= n;j++) {
			mergedList[j] = initList[j];
		}
	}
}

void mergeSort(element a[], int n) {
	int s = 1;
	element extra[MAX_SIZE];
	while (s < n) {
		mergePass(a, extra, n, s);
		printlist(a, s);
		printf("----------------\n");
		s *= 2;
		mergePass(extra, a, n, s);
		printlist(a, s);
		printf("----------------\n");
		s *= 2;
	}
	printlist(a, n);
}