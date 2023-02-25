#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct student {
	char stunum[10];
	char name[30];
	char phonenumber[100];
	int age;
};

void main() {
	int n = 0, input = 0;
	FILE* fp = fopen("score.txt", "r"), * fp1 = fopen("result.txt", "w");
	if (!fp || !fp1) {
		exit(1);
	}
	fscanf(fp, "%d", &n);
	struct student* s = (struct student*)malloc(sizeof(struct student) * n);

	for (int i = 0;i < n;i++) {
		fscanf(fp, "%s %s %s %d", s[i].stunum, s[i].name, s[i].phonenumber, &s[i].age);
	}

	printf("Input age: ");
	scanf("%d", &input);
	for (int i = 0;i < n;i++) {
		if (s[i].age >= input) {
			fprintf(fp1, "%s, %s, %s, %d\n", s[i].stunum, s[i].name, s[i].phonenumber, s[i].age);
		}
	}
	fclose(fp);
	fclose(fp1);
	free(s);
}