#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100

typedef struct { //�ش� ��ġ���� ������ �˻��ϴ� ����ü ����
	short int vert;//����
	short int horiz;//����
}offsets;

offsets move[4] = { {-1,0},{0,1},{1,0},{0,-1} };//�ϵ����� ǥ��

typedef struct { //�Ա����� �ⱸ���� ���� ���� ���ÿ� �����ϱ� ���� ����ü.
	short int row;//��
	short int col;//��
	short int dir;//���� ���ٰ� �ٽ� ���ƿ� ��� dir�� ������ ������ ������ Ž���ϰ� ��.
}element;

element stack[MAX_STACK_SIZE] = { 0 }; //�ⱸ�� �������� ���� ǥ���� ����.
int** maze = 0; //maze�� �����Ҵ���.
int strow, stcol, endrow, endcol;//�Ա���ǥ ��,�� / �ⱸ��ǥ ��,��
int mark[100][100] = { 0 };//�� �� ������ mark�� 1�� ������.
int resultrow, resultcol;//findexit���� maze�� ������ֱ� ���� maze row,col���� �����س��� �Լ� �ȿ��� �����.
void setmaze(FILE* fp); //maze�� mark ������ �־��ִ� �Լ�.
void findexit();//maze ������ ���� ã���ְ� �̸� �������� �����.
void push(int* top, element position);//���ÿ� �ⱸ�� �������� ���� �־��ִ� push�Լ�.
element pop(int* top);//������ ���� ��� �ٽ� �ǵ��ư��� ���� pop����.

void main() {
	FILE* fp = fopen("maze1.txt", "r");
	FILE* fp1 = fopen("maze2.txt", "r");
	FILE* fp2 = fopen("maze3.txt", "r");
	FILE* fp3 = fopen("maze4.txt", "r");
	setmaze(fp);
	findexit();
	fclose(fp);

	setmaze(fp1);
	findexit();
	fclose(fp1);

	setmaze(fp2);
	findexit();
	fclose(fp2);

	setmaze(fp3);
	findexit();
	fclose(fp3);

	//�Լ� ���� �� maze�� free��.
	for (int i = 0;i < resultrow + 2;i++) {
		free(maze[i]);
	}
	free(maze);
}

void setmaze(FILE* fp) {

	int data = 0; //maze�� �� ���
	int i, j; //����
	int row, col; //��,��
	fscanf(fp, "%d %d", &row, &col);//maze�� ��� ���� ������ �ޱ�.

	resultcol = col; resultrow = row;//findexit���� ����ϱ� ���� �� �־���.

	for (int i = 0;i < row;i++) {//mark�Լ� �ʱ�ȭ
		for (int j = 0;j < col;j++) mark[i][j] = 0;
	}

	maze = (int**)calloc((row + 2), sizeof(int*)); //maze�� 1�� �׵θ��� ����� ��.
	for (int i = 0;i < row + 2;i++) {
		maze[i] = (int*)calloc((col + 2), sizeof(int));
		for (int j = 0;j < col + 2;j++) maze[i][j] = 1;//�� 1�� ����
	}

	printf("MAZE\n");
	for (int i = 1;i < row + 1;i++) {
		for (int j = 1;j < col + 1;j++) {
			fscanf(fp, "%d", &data);//row+2, col+2ũ��� ��� 1�� ����� maze ������ �迭�� fscanf�� ���� txt���Ͽ��� data�� �о� �迭�� ������.
			maze[i][j] = data;
			printf("%3d", maze[i][j]);
		}
		printf("\n");
	}
	fscanf(fp, "%d %d %d %d", &strow, &stcol, &endrow, &endcol);//�Ա���ǥ�� �ⱸ��ǥ �ޱ� 

	maze[strow + 1][stcol + 1] = 10; //���߿� ��½� S�� ���.
	maze[endrow + 1][endcol + 1] = 11; //���߿� ��½� F�� ���.

}

void findexit() {
	int i, row, col, next_row, next_col, dir;//������ǥ:row,col  ������ǥ�� next_row,next_col
	int found = 0;//���� �ִ��� ������ ǥ��
	element position;//���ÿ� �־��� ��ǥ
	mark[strow][stcol] = 1;//mark�� �Ա���ǥ�� 1�� ����.
	int top = 0;//������ ���� ��
	stack[0].row = strow + 1, stack[0].col = stcol + 1, stack[0].dir = 0;//stack[0]�� �Ա���ǥ�� �־���.

	while (top > -1 && !found) {
		position = pop(&top);//ó���� element positon�� stack[0]���� ��������. �� �ķδ� ���̻� �� ���� ���� �� �ǵ��ư�����.
		row = position.row; col = position.col; dir = position.dir;//������ǥ�� ����.

		while (dir < 4 && !found) { //4���� ã��
			next_row = row + move[dir].vert; //���� ��ǥ�������� �ð�������� ���ư���, ���� ��ǥ��.
			next_col = col + move[dir].horiz;

			if (maze[next_row][next_col] == 11) {//�ⱸ��ǥ�� ������ ���.
				position.row = row; position.col = col; position.dir = ++dir;//������ǥ�� position�� �ֱ�.
				push(&top, position);//���ÿ� push
				found = 1;//�� ã�� ǥ��(while�� ��������)
			}
			else if (maze[next_row][next_col] == 0 && mark[next_row][next_col] == 0) {//�������� ���̰� maze�� �����ִ±��϶�.

				mark[next_row][next_col] = 1;//������ �� ǥ��
				position.row = row; position.col = col; position.dir = ++dir;//������ǥ�� position���� ����. �ٽ� ������ �� ���� ������� �˻��ϰ� �ϱ����� ++dir.
				push(&top, position);//���ÿ� push
				row = next_row; //�̸������س��� ������ǥ�� ����.
				col = next_col;
				dir = 0;//���� �ʱ�ȭ
			}
			else ++dir;//�˻��� ������ 1�� ��� ���⸸ +1.

		}
	}
	if (found) {//���� ���� ���
		for (i = 1;i < top + 1;i++) maze[stack[i].row][stack[i].col] = 12;//���ÿ� �����س��� ���� maze�迭���� 12�� �ٲ�. ���߿� ��½� X�� ���.
		printf("The path is:\n");
		for (i = 1;i < resultrow + 1;i++) { //�׵θ� ���� ����ؾ��ϹǷ� 1~resultrow+1���� ���
			for (int j = 1;j < resultcol + 1;j++) { //�׵θ� ���� ����ؾ��ϹǷ� 1~resultcol+1���� ���
				if (maze[i][j] == 10) printf("  S");
				else if (maze[i][j] == 11) printf("  F");
				else if (maze[i][j] == 12) printf("  X");
				else printf("%3d", maze[i][j]);
			}
			printf("\n");
		}
		printf("\n");
	}
	else {//���� ���� ���
		printf("No path!\n");
		for (int i = 1;i < resultrow + 1;i++) {//�׵θ� ���� ����ؾ��ϹǷ� 1~resultrow+1���� ���
			for (int j = 1;j < resultcol + 1;j++) {//�׵θ� ���� ����ؾ��ϹǷ� 1~resultcol+1���� ���
				if (maze[i][j] == 10) printf("  S");
				else if (maze[i][j] == 11) printf("  F");
				else printf("%3d", maze[i][j]);
			}
			printf("\n");
		}
		printf("\n");
	}

}

void push(int* top, element position) {//position�� push
	(*top)++;
	stack[*top].row = position.row;
	stack[*top].col = position.col;
	stack[*top].dir = position.dir;
}

element pop(int* top) {//pop����.
	element result;
	if (*top < 0) printf("stack is empty\n");
	else {
		result = stack[*top];
		(*top)--;
	}
	return result;
}