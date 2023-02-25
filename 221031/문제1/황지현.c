#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	int key;
}element;

typedef struct queue {
	element data;
	queuePointer link;
}queue;

typedef struct queue* queuePointer;

queuePointer front[5]={NULL}, rear[5]={NULL};

void addq(int i, element item);
element deleteq(int i);
void printQueue(int i);
int count = 0;
void main() {
	FILE* fp = fopen("in.txt", "r");//X,Y,Z,W °¢°¢ 0,1,2,3 index.
	char menu[10];
	char deletedata[10];
	element line,delete1,delete2;
	while (fscanf(fp,"%s", menu) != EOF) {
		if (strcmp(menu, "D") == 0) {
			fscanf(fp, "%s", deletedata);
			if (strcmp(deletedata, "X") == 0) {
				printf("(Delete X) ==> ");
				delete1=deleteq(0);
				if (count == 1) continue;
				if (isEmpty(0) == 1) { 
					printf("Person %d served.", delete1);
					printQueue(0);
				}
				else {
					delete2 = deleteq(0);
					printf("Person %d,%d served.", delete1, delete2);
					printQueue(0);
				}
			}
			else if (strcmp(deletedata, "Y") == 0) {
				printf("(Delete Y) ==> ");
				delete1 = deleteq(1);
				if (count == 1) continue;
				if (isEmpty(1) == 1) {
					printf("Person %d served.", delete1);
					printQueue(1);
				}
				else {
					delete2 = deleteq(1);
					printf("Person %d,%d served.", delete1, delete2);
					printQueue(1);
				}
			}
			else if (strcmp(deletedata, "Z") == 0) {
				printf("(Delete Z) ==> ");
				delete1 = deleteq(2);
				if (count == 1) continue;
				if (isEmpty(2) == 1) {
					printf("Person %d served.", delete1);
					printQueue(2);
				}
				else {
					delete2 = deleteq(2);
					printf("Person %d,%d served.", delete1, delete2);
					printQueue(2);
				}
			}
			else if (strcmp(deletedata, "W") == 0) {
				printf("(Delete W) ==> ");
				delete1 = deleteq(3);
				if (count == 1) continue;
				if (isEmpty(3) == 1) {
					printf("Person %d served.", delete1);
					printQueue(0);
				}
				else {
					delete2 = deleteq(3);
					printf("Person %d,%d served.", delete1, delete2);
					printQueue(3);
				}
			}
		}
		else {
			fscanf(fp, "%d",&line.key);
		}
		if (strcmp(menu, "X") == 0) {
			printf("(Insert X %d) ==> X:",line.key);
			addq(0, line);
			printQueue(0);
		}
		else if (strcmp(menu, "Y") == 0) {
			printf("(Insert Y %d) ==> Y:", line.key);
			addq(1, line);
			printQueue(1);
		}
		else if (strcmp(menu, "Z") == 0) {
			printf("(Insert Z %d) ==> Z:", line.key);
			addq(2, line);
			printQueue(2);
		}
		else if (strcmp(menu, "W") == 0) {
			printf("(Insert W %d) ==> W:", line.key);
			addq(3, line);
			printQueue(3);
		}
	}
	fclose(fp);

}



void addq(int i, element item) {
	queuePointer temp;
	temp = (queuePointer*)malloc(sizeof(queue));
	temp->data = item;
	temp->link = NULL;
	if (front[i]) rear[i]->link = temp;
	else front[i] = temp;
	rear[i] = temp;
}


element deleteq(int i) {
	queuePointer temp = front[i];
	element item;
	if (!temp) {
		printf("Waiting Empty\n");
		count += 1;
		return;
	} //queueEmpty
	item = temp->data;
	front[i] = temp->link;
	free(temp);
	return item;
}

void printQueue(int i) {
	queuePointer a = front[i];
	if (a == NULL) {
		printf("Empty\n");
		return;
	}
	for (a;a != NULL;a = a->link) {
		printf("[%d]", a->data);
	}
	printf("\n");
}

int isEmpty(int i) {
	if (front[i] == NULL) return 1;
	return 0;
}