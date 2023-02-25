#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct {
	int key;
}element;

element* Queue;

int rear = 0;
int front = 0;
int queuesize = 0;
int che = 0;

void AddQ(element item);
element DeleteQ();
int IsFull();
int IsEmpty();
void printQ();

void main() {
	FILE* fp = fopen("in1.txt", "r");
	FILE* fp1 = fopen("in2.txt", "r");
	FILE* fp2 = fopen("in3.txt", "r");

	char menu=0;
	element data;

	fscanf(fp, "%d", &queuesize);
	printf("Queue size: %d\n", queuesize);
	Queue = (element*)malloc(sizeof(element) * queuesize);
	while (fscanf(fp,"%c",&menu)!=EOF){
		if (menu=='a') {
			fscanf(fp, "%d", &data.key);
			AddQ(data);
			if (che == 1) {
				break;
			}
			printf("Circular queue:");
			printQ();
		}
		else if (menu=='d') {
			if (IsEmpty() == 1) {
				printf("queue empty: cannot delete\n");
				break;
			}
			DeleteQ();
			if (che == 1) {
				che = 0;
				continue;
			}
			printf("Circular queue:");
			printQ();
		}
	}
	fclose(fp);
	printf("\n");



	fscanf(fp1, "%d", &queuesize);
	printf("Queue size: %d\n", queuesize);
	Queue =realloc(Queue,sizeof(element) * queuesize);
	rear = 0; front = 0; che = 0;
	while (fscanf(fp1, "%c", &menu) != EOF) {
		if (menu == 'a') {
			fscanf(fp1, "%d", &data.key);
			AddQ(data);
			if (che == 1) {
				break;
			}
			printf("Circular queue:");
			printQ();
		}
		else if (menu == 'd') {
			if (IsEmpty() == 1) {
				printf("queue empty: cannot delete\n");
				break;
			}
			DeleteQ();
			if (che == 1) {
				che = 0;
				continue;
			}
			printf("Circular queue:");
			printQ();
		}
	}
	fclose(fp1);
	printf("\n");



	fscanf(fp2, "%d", &queuesize);
	printf("Queue size: %d\n", queuesize);
	Queue = realloc(Queue, sizeof(element) * queuesize);
	rear = 0; front = 0; che = 0;
	while (fscanf(fp2, "%c", &menu) != EOF) {
		if (menu == 'a') {
			fscanf(fp2, "%d", &data.key);
			AddQ(data);
			if (che == 1) break;
			printf("Circular queue:");
			printQ();
		}
		else if (menu == 'd') {
			if (IsEmpty() == 1) {
				printf("queue empty: cannot delete\n");
				break;
			}
			DeleteQ();
			if (che == 1) {
				che = 0;
				continue;
			}
			printf("Circular queue:");
			printQ();
		}
	}
	fclose(fp2);
	free(Queue);

}

void AddQ(element item){
	rear = (rear + 1) % queuesize;
	if (front==rear) {
		printf("queue full: cannot add\n");
		che = 1;
		return;
	}
	else Queue[rear] = item;
}

element DeleteQ(){
		front = (front + 1) % queuesize;
		if (IsEmpty() == 1) {
			printf("Circular queue is empty\n");
			che = 1;
			return;
		}
		return Queue[front];
}

int IsFull(){
	if ((rear + 1) % queuesize == front)return 1;
	else return 0;
}

int IsEmpty(){
	if (front ==rear) return 1;
	else return 0;
}

void printQ() {
	if (front >= rear) {
		
		for (int i = front+1;i <queuesize ;i++) {
			printf("%d ", Queue[i].key);
		}
		for (int i = 0;i <= rear;i++) {
			printf("%d ", Queue[i].key);
		}
		printf("\n");
	}
	else {
		for (int i = front+1;i <= rear;i++) {
			printf("%d ", Queue[i].key);
		}
		printf("\n");
	}
}