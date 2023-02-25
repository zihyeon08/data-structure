#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
//4 0 -1 -1 -1 9 8 7 -1 -1 -1 -1 2 3 -1 3 5 7 10 4
//1 -1 2 -1 3 -1 4 -1 0 -1 -1 10 9 8 7 6 -1 -1 -1
typedef struct stack {
	int top;
	int* data;
	int capacity;
}stack;

void initialize(stack* sta);
int IsEmpty(stack* sta);
int IsFull(stack* sta);
void push(stack* sta, int val);
int pop(stack* sta);
void printstack(stack* sta);
void ResultPrintStack(stack* sta);

void main() {
	FILE* fp = fopen("in.txt", "r");
	stack stack;
	int val = 0;
	initialize(&stack);
	while (fscanf(fp, "%d", &val) != EOF) {
		if (val != -1) {
			printf("push item: %d ==> ", val);
			push(&stack,val);
			printstack(&stack);
		}
		else if (val == -1) {
			printf("pop ==>");
			pop(&stack);
			printstack(&stack);
		}
	}
	ResultPrintStack(&stack);
	fclose(fp);
}


void initialize(stack* sta) {
	sta->data = (int*)malloc(sizeof(int) * 1);
	sta->top = -1;
	sta->capacity = 1;
}

int IsEmpty(stack* sta) {
	if (sta->top <= -1) return 1;
	else return 0;
}

int IsFull(stack* sta) {
	if (sta->top >= (sta->capacity) - 1) return 1;
	else return 0;
}
void push(stack* sta, int val) {
	if (!IsFull(sta)) {
		sta->data[++sta->top] = val;
	}
	else {
		sta->capacity *= 2;
		sta->data = (int*)realloc(sta->data, sta->capacity * sizeof(int));
		printf("doubling: %d", sta->capacity);
		push(sta, val);
	}
}
int pop(stack* sta) {
	if (IsEmpty(sta) == 1) {
		printf("stack empty: cannot pop\n");
	}
	else if ((sta->top)-1 == -1) {
		int value = sta->data[sta->top];
		sta->top--;
		printf("stack empty\n");
		return value;
	}
	else
	{
		int value = sta->data[sta->top];
		sta->top--;
		if (sta->capacity / 2 >= sta->top + 1&&sta->capacity/2>=1) {//capacity는 최소 1유지
			sta->capacity /= 2;
			sta->data = (int*)realloc(sta->data, sta->capacity * sizeof(int));
			printf("reducing size(/2): %d", sta->capacity);
		}
		return value;
	}
}
void printstack(stack* sta) {
	if (IsEmpty(sta) == 1){
		return;
	}
	else {
		for (int i = 0;i <= sta->top;i++) {
			printf("[%2d]", sta->data[i]);
		}
		printf("\n");
	}
}

void ResultPrintStack(stack* sta) {
	printf("\n최종 stack 출력\n");
	for (int i = sta->top;i >=0;i--) {
		printf("< %2d>\n", sta->data[i]);
	}
}
