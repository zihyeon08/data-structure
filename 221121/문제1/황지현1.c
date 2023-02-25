#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int** matrix = 0;
int visited[50];
int vertexcnt = 0;
int queue[50];
int front, rear;

void addq(int v) {
	queue[++rear] = v;
}

int deleteq() {
	return queue[++front];
}

void bfs(int v) {
	int w;
	front = rear = -1;
	for (int i = 0;i < vertexcnt;i++) visited[i] = 0; //visited 초기화
	visited[v] = 1;
	printf("%3d ", v);
	addq(v);
	while (rear - front != 0) {
		v = deleteq();
		for (w = 0;w < vertexcnt;w++) {
			if (matrix[v][w] && !visited[w]) {
				visited[w] = 1;
				printf("%3d ", w);
				addq(w);
			}
		}
	}
}

void dfs(int v) {
	int i;
	visited[v] = 1;
	printf("%3d ", v);
	for (i = 0;i < vertexcnt;i++) {
		if (matrix[v][i] && !visited[i]) {
			dfs(i);
		}
	}
}


void main() {
	int data;
	int dfsche, bfsche;
	FILE* fp = fopen("in.txt", "r");
	fscanf(fp, "%d", &vertexcnt);
	matrix = (int**)malloc(sizeof(int*) * vertexcnt);
	for (int i = 0;i < vertexcnt;i++) {
		matrix[i] = (int*)malloc(sizeof(int) * vertexcnt);
		for (int j = 0;j < vertexcnt;j++) {
			fscanf(fp, "%d", &data);
			matrix[i][j] = data;
		}
	}
	printf("[DFS]\n");
	while (1) {
		printf("Starting number: ");
		scanf("%d", &dfsche);
		if (dfsche<0 || dfsche>vertexcnt) break;
		else {
			for (int i = 0;i < vertexcnt;i++) visited[i] = 0; //visited 초기화
			dfs(dfsche);
		}
		printf("\n");
	}
	printf("\n[BFS]\n");
	while (1) {
		printf("Starting number: ");
		scanf("%d", &bfsche);
		if (bfsche<0 || bfsche>vertexcnt) break;
		else bfs(bfsche);
		printf("\n");
	}
	fclose(fp);
	for (int i = 0;i < vertexcnt;i++) free(matrix[i]);
	free(matrix);
}