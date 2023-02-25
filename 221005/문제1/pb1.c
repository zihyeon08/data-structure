#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int top = -1;
int top1 = -1;
char result[20];
int compare(char cal);
void push(char stack[], char pu);
void evalpush(char stack[], char pu);
char pop(char stack[]);
int isEmpty(char stack[]);
char peek(char stack[]);
void calculation(char eval[]);
void push1(char pu);
char pop1();

void main()
{
	FILE* fp;
	char cal[100] = { 0 };//0으로 해야 오류 x(함수가 void 형).
	char stack[20] = { 0 };
	char evaluation[100] = { 0 };
	if ((fp = fopen("infix.txt", "r")) == NULL)
	{
		printf("cannot find the file");
		return 0;
	}
	for (int i = 0;i < 4;i++) {
		top = 0;//stack초기화
		top1 = 0;
		fscanf(fp, "%s", cal);// 파일 1줄 받음.
		printf("Infix: %s\n", cal);//infix 출력.
		printf("Postfix: ");

		for (int j = 0;j < strlen(cal);j++) {
			if (cal[j] >= '0' && cal[j] <= '9') {//숫자일 경우
				printf("%c", cal[j]);
				evalpush(evaluation, cal[j]);
			}
			else { //연산자일 경우
				//(와)일때의 경우를 나눠야 함.
				if (cal[j] == '(') {
					push(stack, cal[j]);
					continue;
				}
				else if (cal[j] == ')') {
					while (peek(stack) != '(') {
						char che;
						che = pop(stack);
						evalpush(evaluation, che);
						printf("%c", che);
					}
					pop(stack);//(도 빼주기.
					continue;
				}
				while (isEmpty(stack) == 0 && compare(cal[j]) <= compare(peek(stack)))//if는 1개만 보고 끝내서 while문을 써야함.
				{
					char che;
					che = pop(stack);
					evalpush(evaluation, che);
					printf("%c", che);

				}
				push(stack, cal[j]);
			}
		}
		char chestack;
		while (isEmpty(stack) == 0) {
			if ((chestack = pop(stack)) != '(')
				evalpush(evaluation, chestack);
			printf("%c", chestack);
		}
		printf("\nResult : ");
		calculation(evaluation);

	}
	fclose(fp);
}

int compare(char cal)
{
	switch (cal)
	{
	case '*': case '/': case '%':
		return 3;
	case '+': case '-':
		return 2;
	case '(': case ')':
		return 1;
	}
}

void push(char stack[], char pu)
{
	stack[++top] = pu;
}

void evalpush(char stack[], char pu)
{
	stack[++top1] = pu;
}


char pop(char stack[])
{
	if (isEmpty(stack) == 1) return -1;
	else {
		top--;
		return stack[top + 1];
	}
}

int isEmpty(char stack[])
{
	if (top == -1) return 1;//empty
	else return 0;
}

char peek(char stack[])
{
	if (isEmpty(stack) == 0) return stack[top];
	else return 0;
}

void push1(char pu) {
	result[++top] = pu;
}
char pop1() {
	return result[top--];
}

void calculation(char eval[]) {

	char op1, op2;
	top = -1;
	for (int i = 0;i < top1;i++) {
		if (eval[i] - '0' >= 1 && eval[i] - '0' <= 9) {
			char che = eval[i] - '0';
			push1(che);

		}
		else {
			op2 = pop1();
			op1 = pop1();
			switch (eval[i]) {
			case '+':
				push1(op1 + op2);
				break;
			case '-':
				push1(op1 - op2);
				break;
			case '*':
				push1(op1 * op2);
				break;
			case '/':
				push1(op1 / op2);
				break;
			case '%':
				push1(op1 % op2);
				break;
			}
		}
	}
	printf("%d\n\n", pop1());
	return;
}


