#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define SWAP(x,y,t) ((t)=(x),(x)=(y),(y)=(t))
typedef struct element {
	char name[20];
	int score;
}element;
int che = 0;

void adjust(element a[], int root, int n) {
	int child, rootkey;
	element temp;
	temp = a[root];
	rootkey = a[root].score;
	child = 2 * root;
	while (child <= n) {
		if ((child < n) && (a[child].score > a[child + 1].score)) child++;
		if (rootkey < a[child].score) {
			break;
		}
		else {
			a[child / 2] = a[child];
			child *= 2;
		}
	}
	printf("adjust %d: rootkey: %d\n", ++che, rootkey);
	a[child / 2] = temp;
}

void heapSort(element a[], int n) {
	int i, j, che = 0;
	element temp;
	for (i = n / 2;i > 0;i--) adjust(a, i, n);
	for (i = n - 1;i > 0;i--) {
		SWAP(a[1], a[i + 1], temp);
		adjust(a, 1, i);
	}
	printf("\n");
	for (i = 1;i <= n;i++)printf("%8s: %6d\n", a[i].name, a[i].score);
}

void main() {
	FILE* fp = fopen("in.txt", "r");
	int n;
	fscanf(fp, "%d", &n);
	element* data = (element*)malloc(sizeof(element) * (n + 1));
	for (int i = 1;i <= n;i++) {
		fscanf(fp, "%s %d", data[i].name, &data[i].score);
	}
	printf("[Heap Sort]\n");
	heapSort(data, n);
	free(data);
	fclose(fp);
}