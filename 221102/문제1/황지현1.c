#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define False 0
#define True 1

typedef struct node* nodePointer;
typedef struct node {
	int data;
	nodePointer link;
}node;

void equivalence(FILE* fp, int* out, int size);

void main() {
	FILE* fp = fopen("e1.txt", "r");
	FILE* fp1 = fopen("e2.txt", "r");
	FILE* fp2 = fopen("e3.txt", "r");
	int size;
	fscanf(fp, "%d", &size);
	size += 1; //0~size까지면 index 개수는 size+1
	int* out = (int*)malloc(size * sizeof(int));
	equivalence(fp, out, size);
	printf("\n");

	fscanf(fp1, "%d", &size);
	out = realloc(out, sizeof(int) * size);
	equivalence(fp1, out, size);
	printf("\n");

	fscanf(fp2, "%d", &size);
	out = realloc(out, sizeof(int) * size);
	equivalence(fp2, out, size);

	printf("\n");
	fclose(fp);
	fclose(fp1);
	fclose(fp2);


}

void equivalence(FILE* f, int* out, int size) {

	nodePointer seq[15] = { NULL };
	nodePointer x, y, top;
	int i, j, n = size;
	for (i = 0;i < n;i++) {
		out[i] = True;
	}
	while (fscanf(f, "%d %d", &i, &j) != EOF) {
		x = (nodePointer)malloc(sizeof(node));
		x->data = j;
		x->link = seq[i];
		seq[i] = x;
		x = (nodePointer)malloc(sizeof(node));
		x->data = i;
		x->link = seq[j];
		seq[j] = x;
	}
	for (int i = 0;i < n;i++) {
		nodePointer print = seq[i];
		printf("[%d]", i);
		while (print) {
			printf("<%d>", print->data);
			print = print->link;
		}
		printf("\n");
	}
	printf("\n");
	for (i = 0;i < n;i++) {
		if (out[i]) {
			printf("New class: %5d", i);
			out[i] = False;
			x = seq[i];
			top = NULL;
			for (;;) {
				while (x) {
					j = x->data;
					if (out[j]) {
						printf("%5d", j);
						out[j] = False;
						y = x->link;
						x->link = top;
						top = x;
						x = y;
					}
					else {
						x = x->link;
					}
				}
				if (!top) break;
				x = seq[top->data];
				top = top->link;
			}
			printf("\n");
		}
	}
	return;
}