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

void dfsconnected(void) {
	int i;
	int subgraph = 1;
	for (i = 0;i < vertexcnt;i++) {
		if (!visited[i]) {
			printf("Component #%d:",subgraph++ );
			dfs(i);
			printf("\n");
		}
	}
}

void bfsconnected(void) {
	int i;
	int subgraph = 1;
	for (int i = 0;i < vertexcnt;i++) visited[i] = 0; //visited 초기화
	for (i = 0;i < vertexcnt;i++) {
		if (!visited[i]) {
			printf("Component #%d:", subgraph++);
			bfs(i);
			printf("\n");
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
	printf("by DFS:\n");
	dfsconnected();
	printf("\nby BFS:\n");
	bfsconnected();

	fclose(fp);
	for (int i = 0;i < vertexcnt;i++) free(matrix[i]);
	free(matrix);
}