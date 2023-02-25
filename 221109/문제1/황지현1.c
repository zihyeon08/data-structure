#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENTS 100
#define HEAP_FULL(n) (n==MAX_ELEMENTS-1)
#define HEAP_EMPTY(n) (!n)

typedef struct {
	char name[10];
	int grade;
}element;

element heap[MAX_ELEMENTS] = { NULL };
int n = 0;

void push(element item) {
	int i;
	if (HEAP_FULL(n)) {
		printf("the heap is full\n");
		exit(1);
	}
	i = ++(n);
	while ((i != 1) && (item.grade < heap[i / 2].grade)) {
		heap[i] = heap[i / 2];
		i /= 2;
	}
	heap[i] = item;
}

element pop() {
	int parent, child;
	element item, temp;
	if (HEAP_EMPTY(n)) {
		printf("the heap is empty\n");
		exit(1);
	}
	item = heap[1];
	temp = heap[(n)--];
	parent = 1;
	child = 2;
	while (child <= n) {
		if ((child < n) && (heap[child].grade > heap[child + 1].grade)) {
			child++;
		}
		if (temp.grade <= heap[child].grade) break;
		heap[parent] = heap[child];
		parent = child;
		child *= 2;
	}
	heap[parent] = temp;
	return item;
}

void printheap() {
	for (int i = 1;i < n + 1;i++) {
		printf("[%s,%d]", heap[i].name, heap[i].grade);
	}
}

void main() {
	FILE* fp = fopen("in1.txt", "r");
	element data, deletedata;
	int num=0;
	while (fscanf(fp, "%s %d", data.name, &data.grade) != EOF) {
		push(data);
	}
	printf("Before deleting:\n");
	printheap();
	printf("\n\nInput number:");
	scanf("%d",&num);
	for (int i = 0;i < num;i++) {
		deletedata = pop();
		printf("item(served): (%s,%d)\n", deletedata.name, deletedata.grade);
	}
	printf("After deleting:\n");
	printheap();
	fclose(fp);
}