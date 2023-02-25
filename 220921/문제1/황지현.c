//-1 0 30 10 45 25
//7 4 1 20 6 33 1 39 75 55
//2 6 3 20 4 25 6 33 7 41 75 55
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX_TERMS 100

void minus(int sa, int ea, int sb, int eb, int* sc, int* ec);
void attach(int coef, int expon);

typedef struct {
	int coef; //계수
	int expon;//지수
}polynomial;

polynomial terms[MAX_TERMS] = { 0 };
int avail = 0;

void main() {
	FILE* fp = fopen("a.txt", "r");
	FILE* fp1 = fopen("b.txt", "r");
	if ((fp || fp1) == NULL) exit(1);
	int sa = 0,ea = 0,sb=0,eb=0,sc,ec;

	while (fscanf(fp, "%d %d", &terms[ea].coef, &terms[ea].expon) != EOF) {
		ea++;
	}
	fclose(fp);
	sb = ea;
	eb = ea;

	while (fscanf(fp1, "%d %d", &terms[eb].coef, &terms[eb].expon) != EOF) {
		eb++;
	}
	fclose(fp1);

	//A(x),B(x) 출력
	printf("A(x):");
	for (int i = sa;i < ea;i++) {
		printf("%dx^%d", terms[i].coef, terms[i].expon);
		if (i != ea-1) printf(" + ");
	}
	printf("\nB(x):");
	for (int i = sb;i < eb;i++) {
		printf("%dx^%d", terms[i].coef, terms[i].expon);
		if (i != eb - 1) printf(" + ");
	}

	avail = eb;
	printf("\n\nC(x):");
	int k = 0;
	minus(sa, ea, sb, eb, &sc, &ec);
	for (k = 0;k < ea;k++) {
		if (terms[sa + k].expon != terms[sb + k].expon)
			break;
	}
	if (k ==ea) {
		printf("0");
	}
	else {
		for (int i = sc;i < ec;i++) {
			printf("%dx^%d", terms[i].coef, terms[i].expon);
			if (i != ec - 1) printf(" + ");
		}
	}


	
}

void minus(int sa,int ea,int sb,int eb,int *sc,int *ec) {
	int coefficient;
	*sc = avail;
	while (sa <= ea && sb <= eb) {
		switch (compare(terms[sa].expon, terms[sb].expon)) {
		case -1:
			attach(terms[sa].coef, terms[sa].expon);
			sa += 1;
			break;
		case 0:
			coefficient =(terms[sa].coef-terms[sb].coef);
			if (coefficient) {
				attach(coefficient, terms[sa].expon);
			}
			sa += 1;
			sb += 1;
			break;
		case 1:
			attach(-1*terms[sb].coef, terms[sb].expon);
			sb+=1;
			break;
		}
	}
	for (;sa < ea;sa++) {
		attach(terms[sa].coef, terms[sa].expon);
	}
		
	for (;sb < eb;sb++) {
;		attach(-1*terms[sb].coef, terms[sb].expon);
	}
	*ec = avail - 1;
}

int compare(int a, int b) {
	if (a == b) return 0;
	if (a < b) return -1;
	if (a > b) return 1;
}

void attach(int c, int e) {
	if (avail >= MAX_TERMS) {
		fprintf(stderr, "too many terms in the polynomianl\n");
		exit(1);
	}
	terms[avail].coef = c;
	terms[avail].expon = e;
	avail++;
}