#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int  digit(int data, int d, int i, int r) { //data, 최대 자릿수, 좌측에서 i번쨰 자릿수 구하기, 각각의 자릿수는 0~9(십진수)
	int result;
	if (i == 0) {
		data /= r;data /= r;data /= r;
		data %= r;
		result = data;
		return result;
	}
	else if (i == 3) {
		result = data % r;
		return result;
	}
	else if (i == 1) {
		data /= r;
		data /= r;
		data %= r;
		result = data;
		return result;
	}
	else if (i == 2) {
		data /= r;
		data %= r;
		result = data;
		return result;
	}
}


int radixSort(int a[], int link[], int d, int r, int n) {
	int front[10] = { 0 }, rear[10] = { 0 };
	int i, bin, current, first, last;
	first = 1;
	for (i = 1;i < n;i++) link[i] = i + 1;
	link[n] = 0;
	for (i =0 ;i <=d-1;i++) {
		for (bin = 0;bin < r;bin++) front[bin] = 0;
		for (current = first;current;current = link[current]) {
			bin = digit(a[current], d, i, r);
			if (front[bin] == 0) front[bin] = current;
			else link[rear[bin]] = current;
			rear[bin] = current;
		}
		for (bin = 0;!front[bin];bin++);
		first = front[bin]; last = rear[bin];
		for (bin++;bin < r;bin++) {
			if (front[bin]) {
				link[last] = front[bin]; last = rear[bin];
			}
		}
		link[last] = 0;
	}

	return first;
}

void main() {
	int size = 0;
	int range = 0;
	int* list;
	int link[15] = { 0 };
	printf("Input size: ");
	scanf("%d", &size);
	list = (int*)malloc(sizeof(int) * (size+1));

	printf("Input range(10~9999): ");
	scanf("%d", &range);

	srand(time(NULL));
	for (int i = 1;i <= size;i++) list[i] = rand() % range;
	printf("before radix sort...\n");
	for (int i = 1;i <= size;i++) printf("%d ", list[i]);
	printf("\nafter radix sort...\n");

	int index = 0;
	index=radixSort(list, link, 4, 10, size);
	for (int i = 0;i < size;i++) {
		printf("%d ", list[index]);
		index = link[index];
	}
	free(list);
}