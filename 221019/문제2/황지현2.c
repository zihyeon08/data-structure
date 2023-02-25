#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
//10 5 -8 3 -2 2 3 0
//-4 2 1 1
//10 5 -8 3 5 2 3 0
//-5 2 1 1


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
	FILE* fp = fopen("poly1.txt", "r");
	FILE* fp1 = fopen("poly2.txt", "r");
	int coef = 0, expon = 0;
	polyNode* a, * b, * result;

	a = creatLinkedLIst();
	b = creatLinkedLIst();
	result = creatLinkedLIst();


	printf("[poly 1]\n ");
	while (fscanf(fp, "%d %d", &coef, &expon) != EOF) {
		insertpoly(a, coef, expon);

	}
	printList(a);

	printf("[poly 2]\n");
	while (fscanf(fp1, "%d %d", &coef, &expon) != EOF) {
		insertpoly(b, coef, expon);
	}
	printList(b);

	fclose(fp);
	fclose(fp1);

	padd(a, b, result);
	printf("[poly1*poly2]\n");
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
	int resultcoef;
	int resultexpon;
	int sum;
	for (;pa != NULL;pa = pa->link) {
		for (;pb != NULL;pb = pb->link) {
			resultcoef = (pa->coef) * (pb->coef);
			resultexpon = (pa->expon) + (pb->expon);
			if (resultcoef) {
				attach(resultcoef, resultexpon, result);
			}
		}
		pb = b->head;
	}
}


void attach(int coefficient, int exponent, polyNode* result) {
	NODE* q, * temp,*p;
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
		p = NULL;
		while (q->link != NULL) {
			p = q;
			q = q->link; 
			if (q->expon == newNode->expon) {
				newNode->coef= q->coef + newNode->coef;
				
				if (newNode->coef!=0) {
					p->link= newNode;
					return;
				}
				else {
					p->link = q->link;
					free(q);
					return;
				}

			}
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
	for (;p != NULL;p = p->link) {
		printf("(%d,%d) ", p->coef, p->expon);
	}
	printf("\n");
}

