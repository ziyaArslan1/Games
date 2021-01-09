#include <stdio.h>

#define ROW 9
#define COL 9

void printTable(char code[][COL], int *arr) {
	printf("\n   ");

	for(int i=0;i<9;i++) printf("\e[90m%d|", arr[i]);

	printf("\n");

	for(int i=0;i<ROW;i++) {
		printf("\e[90m%d |", i+1);

		for(int j=0;j<COL;j++) {
			if(code[i][j] == '*') {
				printf("\e[91m%c\e[90m|", code[i][j]);
			} else {
				printf("\e[90m%c\e[90m|", code[i][j]);
			}
		}

		printf("\n");
	}

	printf("\n");
}

int sep(int *arr, long int num) {
	int ln, i=8;

	if(num < 100000000 || num > 999999999) {
		printf("\nlutfen 9 basamakli sayir gir!\n");
		return 0;
	}

	while(num > 0) {
		ln = num%10;
		num /= 10;
		arr[i--] = ln;
	}
	return 1;
}

void starMap(char code[][COL], int *arr) {
	for(int i=0;i<ROW;i++) {
		for(int j=0;j<COL;j++) {
			if(arr[j] == i+1) {
				code[i][j] = '*';
			}
		}
	}
}

int main() {
	int arr[9]={0};

	char code[ROW][COL] = {
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
 		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}
	/*	{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '} */
	};

	long int num;

	printf("\nSayi gir: ");
	scanf("%ld", &num);

	if(sep(arr, num)) {
		starMap(code, arr);
		printTable(code, arr);
	} else {
		return -1;
	}

	return 0;
}
