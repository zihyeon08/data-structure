#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct NODE {
	int key;
	struct NODE* next;
}NODE;
NODE* head;

NODE* createNode(int data);
NODE* appendNode(NODE* head, NODE* cur);
void printList(NODE* head);
NODE* inputlist(NODE* head, int key);
NODE* deleteNode(NODE* head, int key);


void main() {
	FILE* fp = fopen("in3.txt", "r");
	FILE* fp1 = fopen("in4.txt", "r");
	FILE* fp2 = fopen("in5.txt", "r");
	int key = 0;
	NODE* head1 = NULL, * cur1;
	NODE* head2 = NULL, * cur2;

	while (fscanf(fp, "%d", &key) != EOF) {
		cur1 = createNode(key);
		head1 = appendNode(head1, cur1);
		cur2 = createNode(key);
		head2 = appendNode(head2, cur2);
	}
	fclose(fp);
	printf("[original]\n");
	printList(head1);
	while (fscanf(fp1, "%d", &key) != EOF) {
		if (key % 2 == 0) {
			printf("Insert %d==> ", key);
			head1=inputlist(head1, key);
			printList(head1);
		}
		else {
			printf("Delete %d==> ",key);
			head1=deleteNode(head1, key);
			printList(head1);
		}
	}
	fclose(fp1);


	printf("\n[original]\n");
	printList(head2);
	while (fscanf(fp2, "%d", &key) != EOF) {
		if (key % 2 == 0) {
			printf("Insert %d==> ", key);
			head2=inputlist(head2, key);
			printList(head2);
		}
		else {
			printf("Delete %d==> ", key);
			head2=deleteNode(head2, key);
			printList(head2);
		}
	}
	fclose(fp2);


}

NODE* createNode(int data) {
	NODE* node;
	node = (NODE*)malloc(sizeof(NODE));
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
	NODE* p = head;
	for (;p != NULL;p = p->next) {
		printf("%d ", p->key);
	}
	printf("\n");
	return;
}

NODE* inputlist(NODE* head, int key) {
	NODE* prev = head, * cur = head;
	NODE* temp = (NODE*)malloc(sizeof(NODE));
	temp->key = key;
	temp->next = NULL;
	if (head->key > key) {//맨앞삽입
		temp->next = head;
		head=temp;
		return head;
	}
	while (cur->next) {
		if (cur->key > key)
			break;
		prev = cur;
		cur = cur->next;
	}
	if (cur->key<temp->key) {//맨끝삽입
		cur->next = temp;
		return head;
	}
	else {//중간에 삽입 위치 나올경우
		temp->next = cur;
		prev->next = temp;
	}
	return head;

}
NODE* deleteNode(NODE* head, int key) {
	NODE* prev = NULL, * cur = head;
	if (head->key == key) {
		head = head->next;
		free(cur);
		return head;
	}
	prev = head;
	cur = head->next;
	while (cur) {
		if (cur->key == key) {
			prev->next = cur->next;
			free(cur);
			break;
		}
		prev = cur;
		cur = cur->next;
	}
	if (cur == NULL) {
		printf("없음. ");
	}
	return head;
}