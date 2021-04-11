/* string encrypt sample */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define key 7

typedef struct {
	int *array;
	size_t cap;
	size_t size;
}HASH;

void init(HASH **hash) {
	(*hash)->size = 0;
	(*hash)->cap = 4;

	(*hash)->array = (int*)malloc(sizeof(int)*(*hash)->cap);
}

int encrypt(HASH **hash, const char *value) {
	for(int i=0;i<strlen(value);i++) {
		int num = value[i];
		while(num) {
			if((*hash)->size >= (*hash)->cap) {
				(*hash)->cap *= 2;
				(*hash)->array = (int*)realloc((*hash)->array, sizeof(int)*(*hash)->cap);
			}
			(*hash)->array[(*hash)->size++] = (num%10)+key;
			num /= 10;
		}
		(*hash)->array[(*hash)->size++] = -1;
	}

	return 1;
}

void decrypt(HASH **hash) {
	int index=0, cap=4;
	int *nums = (int*)malloc(sizeof(int)*cap);

	int steps[] = {0,1,10,100,1000,10000,100000,1000000};

	for(int i=0;i<(*hash)->size;) {
		int count=0, step, j;
		for(j=i;(*hash)->array[i++] != -1;j++)
			count++;

		step = steps[count];

		int num = 0;
		for(int m=j-1;(*hash)->array[m] != -1;m--) {
			num += ((*hash)->array[m]-key)*step;
			step /= 10;
		}

		if(index >= cap) {
			cap *= 2;
			nums = (int*)realloc(nums, sizeof(int)*cap);
		}

		nums[index++] = num;
	}

	char *str = (char*)malloc(sizeof(char)*index+1);

	for(int i=0;i<index;i++)
		str[i] = nums[i];

	printf("%s\n", str);

	free(str);
	free(nums);
}

void printHash(HASH **hash) {
	for(int i=0;i<(*hash)->size;i++)
		printf("%d", (*hash)->array[i]);
	printf("\n");
}

int main() {
	HASH *hash = (HASH*)malloc(sizeof(HASH));
	init(&hash);

	char str[1024];

	printf("enter of string(1024): ");
	fgets(str, sizeof(str), stdin);
	str[strlen(str)-1] = '\0';

	printf("Normal : %s\n", str);

	//encrypt
	encrypt(&hash, str);
	printf("Sifrelenmis : ");
	printHash(&hash);

	//decrypt
	decrypt(&hash);

	free(hash->array);
	free(hash);

	return 0;
}
