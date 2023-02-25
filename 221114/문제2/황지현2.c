#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int data;
	struct node* leftchild, * rightchild;
}NODE;

void insert(NODE** node, int k);
NODE* modifiedsearch(NODE* node, int k);
void inorder(NODE* node);
NODE* deletenode(NODE* node, int deletedata);
NODE* minvalue(NODE* node);

void main() {
	FILE* fp = fopen("in2.txt", "r");
	int data,deletedata;
	NODE* tree=NULL;
	printf("Binary search tree(Inorder):\n");
	while (fscanf(fp, "%d", &data) != EOF) {
		insert(&tree, data);
	}
	inorder(tree);
	printf("\n");
	while (1) {
		printf("delete number:");
		scanf("%d", &deletedata);
		if (deletedata == -1) {
			printf("Quit");
			break;
		}
		tree = deletenode(tree, deletedata);
		inorder(tree);
		printf("\n");
	}
	fclose(fp);

}

NODE* modifiedsearch(NODE* node, int k) {
	NODE* temp = node;
	while (node) {
		temp = node;
		if (k < node->data) node = node->leftchild;
		else if (k > node->data) node = node->rightchild;
		else return NULL; //k==node->data ÀÏ¶§
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

void inorder(NODE* node) {
	if (node) {
		inorder(node->leftchild);
		printf("%3d ", node->data);
		inorder(node->rightchild);
	}
}

NODE* minvalue(NODE* node) {
    NODE* current = node;
    while (current->leftchild != NULL) {
        current = current->leftchild;
    }
    return current;
}

NODE* deletenode(NODE* root, int deletedata) {
    if (root == NULL) return root;
    if (deletedata < root->data) root->leftchild = deletenode(root->leftchild, deletedata);
    else if (deletedata > root->data) root->rightchild = deletenode(root->rightchild, deletedata);
    else {
        if (root->rightchild == NULL) {
            NODE* temp = root->leftchild;
            free(root);
            return temp;
        }
        if (root->leftchild == NULL) {
            NODE* temp = root->rightchild;
            free(root);
            return temp;
        }
        NODE* temp = minvalue(root->rightchild);
        root->data = temp->data;
        root->rightchild = deletenode(root->rightchild, temp->data);
    }
    return root;
}
