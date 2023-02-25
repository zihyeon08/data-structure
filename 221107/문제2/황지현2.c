#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100

typedef struct threadedTree {
	short int leftThread;
	struct threadedTree* lchild;
	char data;
	struct threadedTree* rchild;
	short int rightThread;
}threadedTree;

threadedTree* creatnode(threadedTree* root, char data) {
	root->leftThread = 0;
	root->lchild = NULL;
	root->data = data;
	root->rchild = NULL;
	root->rightThread = 0;
	return root;
}

threadedTree* insucc(threadedTree* tree) {
	threadedTree* temp;
	temp = tree->rchild;
	if (!tree->rightThread) {
		while (!temp->leftThread) {
			temp = temp->lchild;
		}
	}
	return temp;
}

void tinorder(threadedTree* tree) {
	threadedTree* temp = tree;
	for (;;) {
		temp = insucc(temp);
		if (temp == tree)break;
		printf("%3c", temp->data);
	}
}

void main() {
	threadedTree *root = (threadedTree*)malloc(sizeof(threadedTree));
	threadedTree* A = (threadedTree*)malloc(sizeof(threadedTree));
	threadedTree* B = (threadedTree*)malloc(sizeof(threadedTree));
	threadedTree* C = (threadedTree*)malloc(sizeof(threadedTree));
	threadedTree* D = (threadedTree*)malloc(sizeof(threadedTree));
	threadedTree* E = (threadedTree*)malloc(sizeof(threadedTree));
	root =creatnode(root,NULL);
	A=creatnode(A, 'A');
	B=creatnode(B, 'B');
	C=creatnode(C, 'C');
	D=creatnode(D,'D');
	E=creatnode(E,'E');
	root->lchild = A;
	root->rchild = root;

	A->lchild=B;
	A->rchild = D;
	B->lchild = C;
	B->rchild = A;
	C->rchild = B;
	C->lchild = root;
	D->lchild = A;
	D->rchild = E;
	E->lchild = D;
	E->rchild = root;

	B->rightThread = 1;
	C->leftThread = 1;
	C->rightThread = 1;
	D->leftThread = 1;
	E->leftThread = 1;
	E->rightThread = 1;
	
	tinorder(root);
}