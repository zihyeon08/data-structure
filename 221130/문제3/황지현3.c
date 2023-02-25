#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SWAP(x,y,t) ((t)=(x),(x)=(y),(y)=(t))

typedef struct element {
	char name[20];
	int key;
}element;

/*
void quickSort(element a[], int left, int right) {
	int pivot;
	element temp;
	int i, j;
	if (left < right) {
		pivot = a[right].key;
		printf("pivot(name): %5d(%s)\n", pivot, a[right].name);
		i = left - 1;
		for (j = left;j <= right - 1;j++) {
			if (a[j].key < pivot) {
				i++;
				SWAP(a[i], a[j], temp);
			}
		}
		SWAP(a[i + 1], a[j], temp);
		quickSort(a, left, i);
		quickSort(a, i + 2, right);
	}
}*/

void quickSort(element a[], int left, int right) {
	int pivot, i, j;
	element temp;
	if (left < right) {
		i = left-1, j = right;
		pivot = a[right].key;
		printf("pivot(name): %5d(%s)\n", pivot, a[right].name);
		do {
			do i++; while (a[i].key < pivot);
			do j--; while (a[j].key > pivot);
			if (i < j)SWAP(a[i], a[j], temp);
		} while (i < j);
		SWAP(a[right], a[i], temp);
		quickSort(a, left, i - 1);
		quickSort(a, i + 1, right);
	}
}

void main() {
	int n;
	FILE* fp = fopen("in.txt", "r");
	fscanf(fp, "%d", &n);
	element* quick = (element*)malloc(sizeof(element) * (n));
	for (int i = 0;i < n;i++) {
		fscanf(fp, "%s %d", quick[i].name, &quick[i].key);
	}
	printf("[after quick sort]\n");
	quickSort(quick, 0, n - 1);
	printf("\n");
	for (int i = 0;i < n;i++) printf("%5s: %5d\n", quick[i].name, quick[i].key);
	free(quick);
	fclose(fp);
}