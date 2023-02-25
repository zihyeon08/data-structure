#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void main() {
	FILE* fp = fopen("in1.txt", "r");
	FILE* fp1 = fopen("in2.txt", "r");
	if ((fp || fp1) == NULL) {
		exit(1);
	}
	int arrsize = 0,arr1size=0,resize=0;
	int arr[10];
	int arr1[10];
	int result[20];
	while (fscanf(fp, "%d", &arr[arrsize]) != EOF) {
		arrsize++;
	}
	while (fscanf(fp1, "%d", &arr1[arr1size]) != EOF) {
		arr1size++;
	}
	fclose(fp);
	fclose(fp1);
	int i = 0;
	int j = 0;
	while(!(i==arrsize&&j==arr1size)){
		if (i == arrsize) {
			result[resize++] = arr1[j++];
		}
		else if (j == arr1size) {
			result[resize++] = arr[i++];
		}
		else if (arr[i] > arr1[j]) {
			result[resize++] = arr1[j++];
		}
		else if (arr[i] < arr1[j]) {
			result[resize++] = arr[i++];				
		}
		else if (arr[i] == arr1[j]) {
			result[resize++] = arr[i++];
			j++;
		}
	}
	for (int i = 0;i < resize;i++) printf("%d ", result[i]);
}

	



