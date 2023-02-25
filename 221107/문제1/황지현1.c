#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100

typedef struct node{
	char data;
	struct node *lchild, * rchild;
}NODE;

//Levelorder
int front = 0, rear = 0;
NODE* queue[MAX_SIZE];//스택으로 구현

void addq(NODE* ptr) {
	queue[rear++] = ptr;
}

NODE* deleteq() {
	return queue[front++];
}

void levelOrder(NODE* ptr) {
	if (!ptr)return;
	addq(ptr);
	for (;;) {
		ptr = deleteq();
		if (ptr) {
			printf("%c ", ptr->data);
			if (ptr->lchild) addq(ptr->lchild);
			if (ptr->rchild) addq(ptr->rchild);
		}
		else break;
	}
	return;
}

//inorder
void inorder(NODE* ptr) {
	if (ptr) {
		inorder(ptr->lchild);
		printf("%c ", ptr->data);
		inorder(ptr->rchild);
	}
}

//preorder
void preorder(NODE* ptr) {
	if (ptr) {
		printf("%c ", ptr->data);
		preorder(ptr->lchild);
		preorder(ptr->rchild);
	}
}

//postorder
void postorder(NODE* ptr) {
	if (ptr) {
		postorder(ptr->lchild);
		postorder(ptr->rchild);
		printf("%c ", ptr->data);
	}

}
//maketree
int front1 = 0, rear1 = 0;
NODE* queue1[MAX_SIZE];
void addqueue(NODE* ptr) {
	queue1[rear1++] = ptr;
}

NODE* deletequeue() {
	return queue1[front1++];
}

NODE* maketree(char inputchar,char start) {
	NODE* root = (NODE*)malloc(sizeof(NODE));
	root->data = start;
	root->lchild = NULL;
	root->rchild = NULL;
	addqueue(root);
	NODE* cur;
	for (char i=start + 1;i <= inputchar;i++) {
		if (i > inputchar)break;
		cur = deletequeue();
		if (cur->lchild == NULL ) {
			if (i > inputchar)break;
			cur->lchild = (NODE*)malloc(sizeof(NODE));
			cur->lchild->data = i++;
			cur->lchild->lchild = NULL;
			cur->lchild->rchild = NULL;
			addqueue(cur->lchild);
		}
		if (cur->rchild == NULL) {
			if (i > inputchar)break;
			cur->rchild = (NODE*)malloc(sizeof(NODE));
			cur->rchild->data = i;
			cur->rchild->lchild = NULL;
			cur->rchild->rchild = NULL;
			addqueue(cur->rchild);
		}
	}
	return root;
}

void main() {
    char inputchar;
	printf("Input character: ");
    scanf("%c", &inputchar);
    char start = 'a';
	NODE* root;
	root=maketree(inputchar,start);
	printf("level order: ");
	levelOrder(root);

	printf("\ninorder: ");
	inorder(root);

	printf("\npreorder: ");
	preorder(root);

	printf("\npostorder: ");
	postorder(root);


}