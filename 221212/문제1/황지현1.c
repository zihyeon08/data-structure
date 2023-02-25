#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ht {
	char key[10];
	int count;
}ht;


int hashFunction(char key[],int size) {
	int sum=0;
	int i = 0;
	int len = strlen(key);
	for (int i = 0;i < len;i++) {
		sum += key[i];
	}
	sum = sum % (size);
	return sum;
}

void add(ht* arry, char data[], int size) {
	int hashpoint = hashFunction(data, size);
	//printf("%s %d\n", data, hashpoint);
	if (strcmp(arry[hashpoint].key,"")==0) {
		strcpy(arry[hashpoint].key, data);
		arry[hashpoint].count = hashpoint;
	}
	else {
		int i=hashpoint;
		while (strcmp(arry[i].key, "") != 0) {
			i++;
			if (i > 16) {
				i %= 17;
			}
		}
		strcpy(arry[i].key, data);
		arry[i].count = i;
	}
}

void search(ht arry[],int size,char check[]) {
	for (int i = 0;i < size;i++) {
		if (strcmp(arry[i].key, check)== 0) {
			if (arry[i].count == i) {
				printf("Success\n");
			}
			return;
		}
	}
	printf("Fail\n");
	return;
}

void main() {
	int size,hashpoint;
	char data[10];
	char check[10];
	FILE* fp = fopen("in.txt", "r");
	printf("Input bucket size:");
	scanf("%d", &size);
	ht* arry = (ht*)calloc(size,sizeof(ht));
	for (int i = 0;i < size;i++) {
		strcpy(arry[i].key, "");
	}
	while(fscanf(fp, "%s", data)!=EOF) {
		add(arry,data,size);
	}
	for (int i = 0;i < size;i++) printf("[%d]: %4s\n", arry[i].count, arry[i].key);
	while (1) {
		printf("Input string(Q for quit):");
		scanf("%s", &check);
		if (strcmp(check,"Q") == 0) {
			printf("Exit");
			break;
		}
		else {
			search(arry,size,check);
		}

	}
	free(arry);
	fclose(fp);
}

