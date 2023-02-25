#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100

typedef struct element {
	char name[20];
	int age;
}element;

int listMerge(element a[], int link[], int start1, int start2) {
	int last1, last2, lastResult = 0;
	for (last1 = start1, last2 = start2;(last1 && last2);) {
		if (a[last1].age >= a[last2].age) {
			link[lastResult] = last1;
			lastResult = last1; 
			last1 = link[last1];
		}
		else {
			link[lastResult] = last2;
			lastResult = last2; 
			last2 = link[last2];
		}
	}
	if (last1 == 0) link[lastResult] = last2;
	else link[lastResult] = last1;
	return link[0];
}

int rmergeSort(element a[], int link[], int left, int right) {
	if (left >= right) {
		return left;
	}
	int mid = (left + right) / 2;
	printf("%8s: %3d\n", "mid", mid);
	return listMerge(a, link, rmergeSort(a, link, left, mid), rmergeSort(a, link, mid + 1, right));
}


void main() {
	int n;
	FILE* fp = fopen("in.txt", "r");
	fscanf(fp, "%d", &n);
	element data[50] = { NULL };
	int link[20] = { 0 };
	for (int i = 1;i <= n;i++) fscanf(fp, "%s %d", data[i].name, &data[i].age);
	printf("[Recursive merge sort]\n");
	rmergeSort(data, link, 1, n);
	printf("\n");
	int index = 0;
	for (int i = 1;i <= n;i++) {
		printf("%8s: %4d\n", data[link[index]].name, data[link[index]].age);
		index = link[index];
	}
	fclose(fp);
}