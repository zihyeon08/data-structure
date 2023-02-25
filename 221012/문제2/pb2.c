#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>

struct node {
	int num;
	struct node* next;
};

typedef struct node NODE;//노드자체
typedef NODE* LINK;//노드를 가리키는 포인터 변수

void printList(LINK head);
LINK appendNode(LINK head, LINK cur);
LINK createNode(int data);
void freenode(LINK head);

void main() {
	LINK head = NULL, cur;
	FILE* fp = fopen("in4.txt", "r");
	int data;
	while (fscanf(fp,"%d",&data)!=EOF) {
		cur = createNode(data);
		head=appendNode(head, cur);
	}
	printList(head);
	freenode(head);
}

void printList(LINK head) {
	LINK nextnode = head;
	while (nextnode) {
		printf("%4d", nextnode->num);
		nextnode = nextnode->next;
	}

}

LINK appendNode(LINK head, LINK cur) {//수정필요
	LINK p, q;
	p = head;
	q = cur;
	/*while (p != NULL) {
		if ((p->num) > cur->num) //왼쪽이 더 크면 멈추고 바꿔서넣어줌
		{
			break;
		}
		q = p;
		p = p->next;
	}*/
	if (p == head) {//맨처음일때
		cur->next = head;
		head = cur;
	}
	else { //아닐때
		cur->next = p;
		q->next = cur;
	}
	return head;

}
LINK createNode(int data) {
	LINK cur = (NODE*)malloc(sizeof(NODE));
	cur->num = data;
	cur->next = NULL;
	return cur;
}


void freenode(LINK head) {
	LINK nextnode = head;
	while (nextnode) {
		free(nextnode);
		nextnode = nextnode->next;
	}
}