#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int row;
	int col;
	int value;
}term;

void FastTranspose(term a[], term b[]);

void main() {
	FILE* fp = fopen("a1.txt", "r");
	term beforedata[20];//nonzero data
	term afterdata[20];//nonzero data
	int i = 0, numrow = 0, numcol=0,num=0,cnt=1;
	//nonzero data�� �ؽ�Ʈ���� �޾ƿ�.
	fscanf(fp, "%d %d", &beforedata[0].row, &beforedata[0].col);

	for (int i = 0;i < beforedata[0].row;i++) {
		for (int j = 0;j < beforedata[0].col;j++) {
			fscanf(fp, "%d", &num);
			if (num > 0) {
				beforedata[cnt].row = i;
				beforedata[cnt].col = j;
				beforedata[cnt].value = num;
				cnt++;
			}
		}
	}
	fclose(fp);
	beforedata[0].value = cnt - 1;
	printf("[Matrix A]\n");
	for (int i = 0;i < cnt;i++) {
		printf("( %d %d %d )\n", beforedata[i].row, beforedata[i].col, beforedata[i].value);
	}
	//��ġ�ϱ�.
	FastTranspose(beforedata, afterdata);

	printf("[Transpose A]\n");
	for (int i = 0;i < cnt;i++) {
		printf("( %d %d %d )\n",afterdata[i].row, afterdata[i].col, afterdata[i].value);
	}

}

void FastTranspose(term a[], term b[]) {

	int rowTerms[10] = { 0 };//col�� ������ ����
	int startingPos[10] = { 0 };//rowTerms�� �������� afterdata�� ���� ���� ����
	int i, j, numcols = a[0].col, numTerms = a[0].value;

	//b[0]�� a[0]�� ��ġ�ؼ� ����.
	b[0].row = a[0].col; b[0].col = a[0].row; 
	b[0].value = numTerms;

	if (numTerms > 0) {
		for (i = 0;i < numcols;i++) rowTerms[i] = 0; //rowTerms �ʱ�ȭ.

		for (i = 1;i <= numTerms;i++) rowTerms[a[i].col]++; //�� value�� ������Դ��� ������� ����.

		startingPos[0] = 1;
		for (i = 1;i < numcols;i++)
			startingPos[i] = startingPos[i - 1] + rowTerms[i - 1];

		for (i = 1;i <= numTerms; i++) {
			j = startingPos[a[i].col]++;
			b[j].row = a[i].col;
			b[j].col = a[i].row;
			b[j].value = a[i].value;
		}
	}
}