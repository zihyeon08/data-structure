#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct NODE {
	int data;
	struct NODE* lchild, * rchild;
}NODE;

typedef NODE* LINK;

LINK makeTree(int n) {
	LINK head = NULL;
	if (n > 1000) return head;

	head = (NODE*)malloc(sizeof(NODE));
	head->lchild = makeTree(n * n);
	head->data = n;
	head->rchild = makeTree(n * 5);
	return head;
}

void inorder(LINK head) {
	if (head) {
		inorder(head->lchild);
		printf("%d ", head->data);
		inorder(head->rchild);
	}
}

void main() {

	int rootdata;
	LINK head;
	printf("Input number: ");
	scanf("%d", &rootdata);
	head = makeTree(rootdata);
	inorder(head);

}

