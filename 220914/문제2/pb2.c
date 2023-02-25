#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int findmin(int* arr, int size);

void main() {
	int arr[100] = { 0 };
	FILE* fp = fopen("in.txt", "r");
	int size=0;
	if (fp == NULL) {
		exit(1);
	}
	fscanf(fp, "%d", &size);

	printf("Numbers: ");
	for (int i = 0;i < size;i++) {
		fscanf(fp, "%d", &arr[i]);
		printf("%d ", arr[i]);
	}
	fclose(fp);

	printf("\nMin:");
	printf(" %d",findmin(arr, size-1));

}

int findmin(int* arr, int size) {
	int min;
	if (size == 0)
		return arr[size];
	min = findmin(arr,size - 1);

	if (min > arr[size])
		return arr[size];
	else
		return min;
}
