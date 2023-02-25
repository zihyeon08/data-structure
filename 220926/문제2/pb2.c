#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int row;
	int col;
	int value;
}term;

void minus(term a[], term b[], term result[]);

void main() {
	FILE* fp = fopen("a2.txt", "r");
	FILE* fp1 = fopen("b2.txt", "r");
	term adata[30];//nonzero data
	term bdata[30];//nonzero data
	term result[30];
	int i = 0, num = 0, cnt = 1;

	//a2 nonzero data를 텍스트에서 받아옴.
	fscanf(fp, "%d %d", &adata[0].row, &adata[0].col);

	for (int i = 0;i < adata[0].row;i++) {
		for (int j = 0;j < adata[0].col;j++) {
			fscanf(fp, "%d", &num);
			if (num != 0) {
				adata[cnt].row = i;
				adata[cnt].col = j;
				adata[cnt].value = num;
				cnt++;
			}
		}
	}
	fclose(fp);
	adata[0].value = cnt-1;
	printf("[Matrix A]\n");
	for (int i = 0;i < adata[0].value+1;i++) {
		printf("( %d %d %d )\n", adata[i].row, adata[i].col, adata[i].value);
	}

	//b2 nonzerodata를 텍스트에서 받아옴.
	fscanf(fp1, "%d %d", &bdata[0].row, &bdata[0].col);

	i = 0, num = 0, cnt = 1;
	for (int i = 0;i < bdata[0].row;i++) {
		for (int j = 0;j < bdata[0].col;j++) {
			fscanf(fp1, "%d", &num);
			if (num != 0) {
				bdata[cnt].row = i;
				bdata[cnt].col = j;
				bdata[cnt].value = num;
				cnt++;
			}
		}
	}
	fclose(fp1);
	bdata[0].value = cnt-1;
	printf("[Matrix B]\n");
	for (int i = 0;i < bdata[0].value+1;i++) {
		printf("( %d %d %d )\n", bdata[i].row, bdata[i].col, bdata[i].value);
	}
	printf("\n");
	
	minus(adata, bdata, result);
	for (int i = 0;i < result[0].value+1;i++) {
		printf("( %d %d %d )\n", result[i].row, result[i].col, result[i].value);
	}
	


}
void minus(term a[], term b[], term result[]) {
	int num = 1;


	int anum = 1, bnum = 1;

	while (anum <= a[0].value && bnum <= b[0].value) {
		if (a[anum].row == b[bnum].row) {
			if (a[anum].col > b[bnum].col) {
				result[num].row = b[bnum].row;
				result[num].col = b[bnum].col;
				result[num].value = -b[bnum].value;
				num++;
				bnum++;
			}
			else if (a[anum].col == b[bnum].col) {
				result[num].row = b[bnum].row;
				result[num].col = b[bnum].col;
				result[num++].value = a[anum].value - b[bnum].value;
				anum++, bnum++;
			}
			else {
				result[num].row = a[anum].row;
				result[num].col = a[anum].col;
				result[num++].value = a[anum].value;
				anum++;
			}
		}
		else if (a[anum].row < b[bnum].row) {
			result[num].row = a[anum].row;
			result[num].col = a[anum].col;
			result[num++].value = a[anum].value;
			anum++;
		}
		else if (a[anum].row > b[bnum].row) {
			result[num].row = b[bnum].row;
			result[num].col = b[bnum].col;
			result[num++].value = -b[bnum].value;

			bnum++;
		}

	}
	for (; bnum <= b[0].value; bnum++) {
		result[num].row = b[bnum].row;
		result[num].col = b[bnum].col;
		result[num].value = -b[bnum].value;
		num++;
	}
	for (; anum <= a[0].value; anum++) {
		result[num].row = a[anum].row;
		result[num].col = a[anum].col;
		result[num].value = a[anum].value;
		num++;
	}
	
	result[0].row = a[0].row;
	result[0].col = a[0].col;
	result[0].value = num - 1;
}
