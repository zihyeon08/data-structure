#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int Sequential(int arr[], int size, int num);
int ibs(int arr[], int left, int right, int num);
int compare(int arr, int searchnum);

void main() {

	FILE* fp = fopen("in.txt", "r");
	int arr[100] = { 0 };
	int size = 0,num=0;
	if (fp == NULL) {
		exit(1);
	}
	while (fscanf(fp, "%d", &arr[size]) != EOF) {
		size++;
	}
	fclose(fp);
	printf("찾으려는 숫자:");
	scanf("%d", &num);

	printf("iterative binary search의 결과>>");
	int left = 0, right = size - 1;;
	if (ibs(arr, left, right, num) != -1) printf("success\n");
	else printf("fail\n");

	printf("sequential search의 결과>>");
	if (Sequential(arr, size, num) != -1)printf("success");
	else printf("fail");

}

int Sequential(int arr[],int size,int num) {
	for (int i = 0;i < size;i++) {
		if (arr[i] == num) {
			return i;
		}
	}
	return -1;
}

int ibs(int arr[], int left, int right, int num) {
	while (left <= right) {
		int mid = (left + right) / 2;
		switch (compare(arr[mid], num)) {
		case -1: left = mid + 1;
			break;
		case 0: return mid;
		case 1: right = mid - 1;
		}
	}
	return -1;
}

int compare(int arr, int searchnum) {
	if (arr == searchnum) return 0;
	else if (arr > searchnum) return 1;
	else if (arr < searchnum) return -1;
}