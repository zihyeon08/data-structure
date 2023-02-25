#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct element {
	char name[20];
	int age;
}element;

void insert(element e, element a[], int i) {
	a[0] = e;
	while (e.age > a[i].age) {
		a[i + 1] = a[i];
		i--;
	}
	a[i + 1] = e;
}

void insertionSort(element a[], int n) {
	int j;
	for (j = 2;j <= n;j++) {
		element temp = a[j];
		insert(temp, a, j - 1);
	}
}

void printinsertsort(element a[], int n) {
	for (int i = 1;i <= n;i++) {
		printf("%6s: %4d\n", a[i].name, a[i].age);
	}
}

void main() {
	int n;
	char namedata[20];
	int scoredata;
	FILE* fp = fopen("in.txt", "r");
	fscanf(fp, "%d", &n);
	element*insert = (element*)malloc(sizeof(element)*(n+1));
	for (int i = 1;i < n + 1;i++) {
		fscanf(fp, "%s %d", namedata, &scoredata);
		strcpy(insert[i].name, namedata);
		insert[i].age = scoredata;
	}
	insertionSort(insert, n);
	printf("[Insert sort]\n");
	printinsertsort(insert, n);
	free(insert);
	fclose(fp);
}