#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>

typedef struct NODE {
	int coef;
	int expon;
	struct NODE* link;
}NODE;

typedef struct polyNode {
	NODE* head;
}polyNode;

polyNode* creatLinkedLIst(void);
void insertpoly(polyNode* poly, int coef, int expon);
void padd(polyNode* a, polyNode* b, polyNode* result);
int compare(int a, int b);
void attach(int coefficient, int exponent, polyNode* result);
void printList(polyNode* result);
void erase(polyNode* ptr);

void main() {
	FILE* fp = fopen("padd1.txt", "r");
	FILE* fp1 = fopen("padd2.txt", "r");
	int coef = 0, expon = 0;
	polyNode* a, * b, * result;

	a = creatLinkedLIst();
	b = creatLinkedLIst();
	result = creatLinkedLIst();


	printf("%10s", "poly A : ");
	while (fscanf(fp, "%d %d", &coef, &expon) != EOF) {
		insertpoly(a, coef, expon);

	}
	printList(a);

	printf("%10s", "poly B : ");
	while (fscanf(fp1, "%d %d", &coef, &expon) != EOF) {
		insertpoly(b, coef, expon);
	}
	printList(b);

	fclose(fp);
	fclose(fp1);

	padd(a, b, result);
	printf("%10s", "poly(A+B):");
	printList(result);

	erase(a);
	erase(b);
	erase(result);

	printf("\nafter erasing...\n");
	printList(a);
	printList(b);
	printList(result);

}

polyNode* creatLinkedLIst(void) {

	polyNode* poly = (polyNode*)malloc(sizeof(poly));
	poly->head = NULL;
	return poly;
}

void insertpoly(polyNode* poly, int coef, int expon) {
	NODE* q;
	NODE* newNode = (NODE*)malloc(sizeof(NODE));
	q = poly;
	newNode->coef = coef;
	newNode->expon = expon;
	newNode->link = NULL;

	if (poly->head == NULL)
	{
		poly->head = newNode;
		return;
	}
	else {
		q = poly->head;
		while (q->link != NULL) {
			q = q->link;
		}
		q->link = newNode;
	}
}

void padd(polyNode* a, polyNode* b, polyNode* result) {
	NODE* pa = a->head;
	NODE* pb = b->head;
	int sum;

	while (pa && pb) {

		switch (compare(pa->expon, pb->expon))
		{
		case -1:
			attach(pa->coef, pa->expon, result);
			pa = pa->link;
			break;
		case 0:
			sum = (pa->coef) + (pb->coef);
			if (sum) attach(sum, pa->expon, result);
			pa = pa->link;
			pb = pb->link;
			break;
		case 1:
			attach(pb->coef, pb->expon, result);
			pb = pb->link;
			break;
		}
	}
	for (;pa != NULL;pa = pa->link) attach(pa->coef, pa->expon, result);
	for (;pb != NULL;pb = pb->link) attach(pb->coef, pb->expon, result);
}

int compare(int a, int b) {
	if (a < b) return 1;
	else if (a == b) return 0;
	else return -1;
}

void attach(int coefficient, int exponent, polyNode* result) {
	NODE* q;
	NODE* newNode = (NODE*)malloc(sizeof(NODE));
	newNode->coef = coefficient;
	newNode->expon = exponent;
	newNode->link = NULL;

	if (result->head == NULL)
	{
		result->head = newNode;
		return;
	}
	else {
		q = result->head;
		while (q->link != NULL) {
			q = q->link;
		}
		q->link = newNode;
	}
}

void printList(polyNode* poly) {
	NODE* p = poly->head;
	if (p == NULL) {
		printf("empty list!\n");
		return;
	}
	for (;p != NULL;p = p->link) printf("<%d,%d> ", p->coef, p->expon);
	printf("\n");
}


void erase(polyNode* ptr) {
	NODE* temp;
	temp = ptr->head;
	while (ptr->head != NULL) {
		temp = ptr->head;
		ptr->head = ptr->head->link;
		free(temp);
	}
}


