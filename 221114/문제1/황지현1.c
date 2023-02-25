#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int data;
	struct node* leftchild, * rightchild;
}NODE;

void insert(NODE** node, int k);
NODE* modifiedsearch(NODE* node, int k);
void postorder(NODE* node);
int itersearch(NODE* tree, int k);

void main() {
	FILE* fp = fopen("in1.txt", "r");
	int data;
	int searchdata,result;
	NODE* tree=NULL;
	while (fscanf(fp, "%d", &data) != EOF) {
		insert(&tree, data);
	}
	printf("Postorder traversal:\n");
	postorder(tree);
	printf("\n");
	while(1){
		printf("Input number: ");
		scanf("%d", &searchdata);
		if (searchdata < 0) {
			printf("Quit");
			break;
		}
		else {
			result=itersearch(tree, searchdata);
			if (result) printf("%d: O\n", searchdata);
			else printf("%d: X\n", searchdata);
		}
	}
	fclose(fp);

}


int itersearch(NODE* tree, int k) {
	while (tree) {
		if (k == tree->data) return tree->data;
		if (k < tree->data) tree = tree->leftchild;
		else
			tree = tree->rightchild;
	}
	return NULL;
}

NODE* modifiedsearch(NODE* node, int k) {
	NODE* temp = node;
	while (node) {
		temp = node;
		if (k < node->data) node = node->leftchild;
		else if (k > node->data) node = node->rightchild;
		else return NULL; //k==node->data 일때 (같은 값은 들어갈수없으므로 NULL리턴)
	}
	return temp;
}

void insert(NODE** node, int k) {
	NODE* ptr, * temp = modifiedsearch(*node, k);
	if (temp || !(*node)) {
		ptr = (NODE*)malloc(sizeof(*ptr));
		ptr->data = k;
		ptr->leftchild = ptr->rightchild = NULL;
		if (*node) {
			if (k < temp->data)temp->leftchild = ptr;
			else temp->rightchild = ptr;
		}
		else *node = ptr;
	}
}

void postorder(NODE* node) {
	if (node) {
		postorder(node->leftchild);
		postorder(node->rightchild);
		printf("%3d ", node->data);
	}
}