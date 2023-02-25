#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 50

//인접 리스트 구현
typedef struct graphnode {
	int edge;
	struct graphnode* link;
}graphnode;


void insertedgelist(graphnode** g, int v, int e) {
	graphnode* node;
	graphnode* temp;
	node = (graphnode*)malloc(sizeof(node));
	node->edge = e;
	node->link = NULL;
	temp = g[v];
	g[v] = node;
	node->link = temp;
	
	return;
}

void printlist(graphnode** g,int n) {
	graphnode** q=g;
	for (int i = 0;i < n;i++) {
		printf("[%d] ", i);
		while (q[i] != NULL) {
			printf("%d ", q[i]->edge);
			q[i] =q[i]->link;
		}
		printf("\n");
	}
	printf("\n");
}

void main() {
	int **agdmat = 0;
	graphnode** linked = NULL;
	graphnode** inverse = NULL;
	FILE* fp = fopen("in.txt", "r");
	int n, v, e;
	int indegree[MAX_SIZE] = { 0 };
	int outdegree[MAX_SIZE] = { 0 };

	//n을 받아 matrix,linkedlist 초기화
	fscanf(fp, "%d", &n);
	agdmat = (int**)malloc(sizeof(int*) * n);
	linked = (graphnode**)malloc(sizeof(*linked)*n);
	inverse = (graphnode**)malloc(sizeof(*inverse)*n);
	for (int i = 0;i < n;i++) {
		agdmat[i] = (int*)malloc(sizeof(int) * n);
		linked[i] = NULL;
		inverse[i] = NULL;
		for (int j = 0;j < n;j++) agdmat[i][j] = 0;
	}
	
	
	//값을 받아 넣어줌
	while (fscanf(fp, "%d %d", &v, &e) != EOF) {
		agdmat[v][e] = 1;
		insertedgelist(linked, v, e);
		insertedgelist(inverse, e, v);
		indegree[e]++;
		outdegree[v]++;
	}
	fclose(fp);
	


	//출력
	printf("(1) adjacency matrix\n");
	for (int i = 0;i < n;i++) {
		for (int j = 0;j < n;j++) printf("%d ", agdmat[i][j]);
		printf("\n");
	}
	printf("\n(2) Linked adjacency list\n");
	printlist(linked,n);
	printf("(3) Inverse adjacency list\n");
	printlist(inverse,n);
	printf("(4) In degree\n");
	for (int i = 0;i < n;i++) printf("[%d] %d\n", i, indegree[i]);
	printf("\n(5) Outdegree\n");
	for (int i = 0;i < n;i++) printf("[%d] %d\n", i, outdegree[i]);
    

	//free과정
	for (int i = 0;i < n;i++) free(agdmat[i]);
	free(agdmat);
	for (int i = 0;i < n;i++) {
		graphnode *p = linked[i];
		graphnode *temp;
		while (p != NULL) {
			temp = p;
			p = p->link;
			free(temp);
		}
		free(linked[i]);
	}
	free(linked);
	for (int i = 0;i < n;i++) {
		graphnode* p = inverse[i];
		graphnode* temp;
		while (p != NULL) {
			temp = p;
			p = p->link;
			free(temp);
		}
		free(inverse[i]);
	}
	free(inverse);
}