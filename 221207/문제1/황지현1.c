#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct element {
	char face;
	int suit;
}element;

int digit1(char face) {
	if (face == 'C') {
		return 0;
	}
	else if (face == 'D') {
		return 1;
	}
	else if (face == 'H') {
		return 2;
	}
	else if (face == 'S') {
		return 3;
	}
}

int  digit(int data) {
	if (data == 1) {
		return 12;
	}
	else {
		int result = data - 2;
		return result;
	}
}


int radixSort(element a[], int link[], int d, int r, int n) {
	int front[13] = { 0 }, rear[13] = { 0 };
	int i, bin, current, first, last;
	first = 1;
	for (i = 1;i < n;i++) link[i] = i + 1;
	link[n] = 0;
	for (bin = 0;bin < r;bin++) front[bin] = 0;
	for (current = first;current;current = link[current]) {
		bin = digit(a[current].suit);
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

	for (bin = 0;bin < r;bin++) front[bin] = 0;
	for (current = first;current;current = link[current]) {
		bin = digit1(a[current].face);
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

	return first;

}

void main() {
	FILE* fp = fopen("in.txt", "r");
	int size;
	int link[13] = { 0 };
	element data[11] = { 0 };
	fscanf(fp, "%d", &size);
	for (int i = 1;i <= size;i++) {
		fscanf(fp, "\n%c\n%d",&data[i].face, &data[i].suit);
	}

	//Ãâ·Â
	int index = 0;
	index=radixSort(data, link, 2, 13, size);
	for (int i = 0;i < size;i++) {
		if (data[index].face == 'C') printf("( club,");
		else if (data[index].face == 'D') printf("(  dia,");
		else if (data[index].face == 'H') printf("(heart,");
		else if (data[index].face == 'S') printf("(spade,");
		
		if (data[index].suit == 11) printf("%5c)\n", 'J');
		else if (data[index].suit == 12) printf("%5c)\n", 'Q');
		else if (data[index].suit == 13) printf("%5c)\n", 'K');
		else printf("%5d)\n", data[index].suit);
		index = link[index];
	}

	fclose(fp);
}