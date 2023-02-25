#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

void main() {
	int arr[20] = { 0 }, arr1[20] = { 0 };
	int arrcnt = 0, arr1cnt = 0;
	FILE* fp = fopen("in1.txt", "r"), * fp1 = fopen("in2.txt", "r");
	if (!fp || !fp1) {
		exit(1);
	}
	printf("File1: ");
	while (fscanf(fp, "%d", &arr[arrcnt]) != EOF) {
		printf("%d ", arr[arrcnt]);
		arrcnt++;
	}

	printf("\nFile2: ");
	while (fscanf(fp1, "%d", &arr1[arr1cnt]) != EOF) {
		printf("%d ", arr1[arr1cnt]);
		arr1cnt++;
	}
	printf("\n±³ÁýÇÕ: ");
	for (int i = 0;i < arr1cnt;i++) {
		for (int j = 0;j < arrcnt;j++) {
			if (arr[i] == arr1[j]) {
				printf("%d ", arr[i]);
				continue;
			}
			if (arr1[i] < arr[j]) continue;
		}
	}
	fclose(fp);
	fclose(fp1);
}