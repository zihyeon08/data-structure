#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct edge {
	int x, y;
	int cost;
};

struct edge data[50];
struct edge result[50];
int resultindex;

int parent[50];
int vertex;

void setinit(int n) {
	for (int i = 0;i < n;i++) {
		parent[i] = -1;
	}
}

int find(int i) {
	if (parent[i] == -1) return i;
	for (;parent[i] != -1;i = parent[i]);
	return i;
}

int setunion(int i, int j) {
	int root = find(i);
	int root1 = find(j);
	if (root != root1) parent[root] = root1;
}

void kruskal() {
	int edge = 0;
	int u, v;
	struct edge e;
	setinit(vertex);
	int i = 0;
	while (edge < vertex - 1) {
		e = data[i];
		u = find(e.x); //x의 집합번호
		v = find(e.y); //y의 집합번호

		if (u != v) { //서로 같은 집합이 아닌 경우
			result[resultindex].x = e.x;
			result[resultindex].y = e.y;
			result[resultindex].cost = e.cost;
			resultindex += 1;
			edge++;
			setunion(u, v); //add
		}
		else {
			i++; //discard
		}
	}
	if (resultindex < vertex - 1) {
		printf("No spanning tree\n");
	}
}

void sortingresult() {
	struct edge temp;
	
	for (int i = 0;i < resultindex;i++) {
		for (int j = i+1;j < resultindex;j++) {
			if (result[i].cost > result[j].cost) {
				temp = result[i];
				result[i] = result[j];
				result[j] = temp;
			}
		}
	}
}

void printresult() {
	printf("(edge):weight\n");
	for (int i = 0;i < resultindex;i++) {
		printf("(%d, %d): %d\n", result[i].x, result[i].y, result[i].cost);
	}
}

void main() {
	FILE* fp = fopen("in.txt", "r");
	int x, y, cost;

	fscanf(fp, "%d", &vertex);
	int index = 0;
	for(int i=0;i<vertex;i++){
		for (int j = 0;j < vertex;j++) {
			fscanf(fp, "%d", &cost);
			if (cost) {
				data[index].x = i;
				data[index].y = j;
				data[index].cost = cost;
				index += 1;
			}
		}
	}
	kruskal();
	sortingresult();
	printresult();
	fclose(fp);

}