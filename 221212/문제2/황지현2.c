#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 20

typedef struct ht {
	char key[20];
	int count;
	struct ht* link;
}ht;

ht* top[MAX_SIZE] = { NULL };

int hashFunction(char key[], int size) {
	int sum = 0;
	int i = 0;
	int len = strlen(key);
	for (int i = 0;i < len;i++) {
		sum += key[i];
	}
	sum = sum % (size);
	return sum;
}

void add(char data[],int size) {
	int hashpoint = hashFunction(data, size);
	ht* temp;
	temp = (ht*)malloc(sizeof(ht));
	temp->link = NULL;
	strcpy(temp->key, data);
	temp->count = hashpoint;
	temp->link = top[hashpoint];
	top[hashpoint] = temp;
}

void search(ht *arry[], int size, char check[]) {
	for (int i = 0;i < size;i++) {
		ht* p = arry[i];
		while (p) {
			if (strcmp(p->key,check ) == 0) {
				if (p->count == i){
					printf("Success\n");
					return;
				}
			}
			p = p->link;
		}
	}
	printf("Fail\n");
	return;
}

void printtop(ht* head,int i) {
	ht* p=head;
	while (p) {
		printf("[%4s]", p->key);
		p = p->link;
	}
	
}

void main() {
	int size, hashpoint;
	char data[10];
	char check[10];
	FILE* fp = fopen("in.txt", "r");
	printf("Input bucket size:");
	scanf("%d", &size);
	
	while (fscanf(fp, "%s", data) != EOF) {
		add(data,size);
	}
	for (int i = 0;i < size;i++) {
		printf("[%d]", i);
		printtop(top[i],size);
		printf("\n");
	}
	while (1) {
		printf("Input string(Q for quit):");
		scanf("%s", &check);
		if (strcmp(check, "Q") == 0) {
			printf("Exit");
			break;
		}
		else {
			search(top, size, check);
		}

	}
	fclose(fp);
}

