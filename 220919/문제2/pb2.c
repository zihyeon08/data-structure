#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
void main() {
	int i = 0, j = 0, k = 0;
	printf("A[I][J][K]...\n");
	printf("Input I:");
	scanf("%d", &i);
	printf("Input J:");
	scanf("%d", &j);
	printf("Input K:");
	scanf("%d", &k);

	//3차원 배열 동적할당
	int*** arr=(int***)malloc(sizeof(int**)*i);
	for (int m = 0;m < i;m++) {
		arr[m] = (int**)malloc(sizeof(int*) * j);
		for (int n = 0;n < j;n++) {
			arr[m][n] = (int*)malloc(sizeof(int) * k);
			for (int l = 0;l < k;l++) {
				arr[m][n][l] = m + n + l;
			}
		}
	}

	for (int m = 0;m < i;m++) {
		for (int n = 0;n < j;n++) {
			for (int l = 0;l < k;l++) {
				printf("A[%d][%d][%d]=%d ", m, n, l, arr[m][n][l]);
			}
			printf("\n");
		}
		printf("\n");
	}
	for (int m = 0;m < i;m++) {
		for (int n = 0;n < j;n++) {
			for (int l = 0;l < k;l++) {
				free(arr[m][n][l]);
			}
			free(arr[m][n]);
		}
		free(arr[m]);
	}
	free(arr);
}