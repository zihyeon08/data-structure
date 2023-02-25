#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SWAP(x,y,t) ((t)=(x),(x)=(y),(y)=(t))

typedef struct element {
	char name[20];
	int age;
}element;

void quickSort(element a[],int left,int right) {
	int pivot, i, j;
	element temp;
	if (left < right) {
		i = left, j = right + 1;
		pivot = a[left].age;
		do{
			do i++; while (a[i].age > pivot);
			do j--; while (a[j].age < pivot);
			if (i < j)SWAP(a[i], a[j], temp);
		} while (i < j);
		SWAP(a[left], a[j],temp);
		quickSort(a, left, j - 1);
		quickSort(a, j + 1, right);
	}
}

void printquicksort(element a[], int n) {
	for (int i = 0;i < n;i++) printf("%6s: %4d\n", a[i].name, a[i].age);
}
void main() {
	int n;
	char namedata[20];
	int scoredata;
	FILE* fp = fopen("in.txt", "r");
	fscanf(fp, "%d", &n);
	element* quick = (element*)malloc(sizeof(element) * n);
	for (int i = 0;i < n;i++) {
		fscanf(fp, "%s %d", namedata, &scoredata);
		strcpy(quick[i].name, namedata);
		quick[i].age = scoredata;
	}

	quickSort(quick, 0, n - 1);
	printf("[Quick sort]\n");
	printquicksort(quick, n);
	free(quick);
	fclose(fp);
}