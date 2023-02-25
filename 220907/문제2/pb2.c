#include <stdio.h>
#include <time.h>
#define SWAP(x,y,t) (t=x,x=y,y=t)
#define MAX_SIZE 1001

void sort(int[], int);

void main() {
	int i, n, step = 10;
	int a[MAX_SIZE];
	double duration;

	printf("     n  repetitions    time\n");
	for (n = 0;n <= 1000;n += step) {
		long repetitions = 0;
		clock_t start = clock();
		do {
			repetitions++;
			for (i = 0;i < n;i++) a[i] = n - i;
			sort(a, n);
		} while (clock() - start < 1000);

		duration = ((double)(clock() - start));
		duration /= repetitions;
		printf("%6d  %9d  %f\n", n, repetitions, duration);
		if (n == 100)step = 100;
	}
}

void sort(int list[], int n) {
	int i, j, min, temp;
	for (i = 0;i < n - 1;i++) {
		min = i;
		for (j = i + 1;j < n;j++) {
			if (list[j] < list[min])
				min = j;
		}
		SWAP(list[i], list[min], temp);
	}
}