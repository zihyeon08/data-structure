#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

//2 6 9 10 14 17 22 35 41 57
//12 13 14 15 16 17 57

//1 2 3 4 5 6
//7 8 9 10

typedef struct NODE {
	int key;
	struct NODE* next;
}NODE;
NODE* head;

NODE* createNode(int data);
NODE* appendNode(NODE* head, NODE* cur);
void printList(NODE* head);

void main() {
	FILE* fp = fopen("in1.txt", "r");
	FILE* fp1 = fopen("in2.txt", "r");
	int key = 0;
	NODE* head1 = NULL, * cur1;
	NODE* head2 = NULL, * cur2;
	NODE* head3 = NULL, * cur3;
	while (fscanf(fp, "%d", &key) != EOF) {
		cur1 = createNode(key);
		head1 = appendNode(head1, cur1);
	}
	printf("[in1.txt]\n");
	printList(head1);
	fclose(fp);
	while (fscanf(fp1, "%d", &key) != EOF) {
		cur2 = createNode(key);
		head2 = appendNode(head2, cur2);
	}
	printf("[in2.txt]\n");
	printList(head2);
	fclose(fp1);
	NODE* che = head1,*che1 = head2;
	for (;che!= NULL;che = che->next) {
		for (;che1 != NULL;che1 = che1->next) {
			if (che->key == che1->key) {
				cur3 = createNode(che->key);
				head3 = appendNode(head3, cur3);
			}
		}
		che1 = head2;
	}
	printf("[in1 AND in2]\n");
	printList(head3);

}




NODE* createNode(int data) {
	NODE* node;
	node = (NODE*)malloc(sizeof(node));
	node->key = data;
	node->next = NULL;
	return node;
}

NODE* appendNode(NODE* head, NODE* cur) {
	NODE* nextnode = head;
	if (!head) {
		head = cur;
		return head;
	}
	while (nextnode->next) {
		nextnode = nextnode->next;
	}
	nextnode->next = cur;
	return head;
}

void printList(NODE* head) {
	NODE* p=head;
	if (p == NULL) {
		printf("공통된 원소가 없음");
		return;
	}
	for (;p != NULL;p = p->next) {
		printf("%d ", p->key);
	}
	printf("\n");
	return;
}