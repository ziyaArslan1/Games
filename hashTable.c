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

void init(HASH *d) {
	d->size = 0;
	d->cap = 4;

	d->array = (int*)malloc(sizeof(int)*d->cap);
}

int put(HASH *hash, const char *value) {
	for(int i=0;i<strlen(value);i++) {
		int num = value[i];
		while(num) {
			if(hash->size >= hash->cap) {
				hash->cap *= 2;
				hash->array = (int*)realloc(hash->array, sizeof(int)*hash->cap);
			}
			hash->array[hash->size++] = (num%10)+key;
			num /= 10;
		}
		hash->array[hash->size++] = -1;
	}

	return 1;
}

int unput(HASH *hash) {
	int index=0;
	int *nums = (int*)malloc(sizeof(int)*100);

	for(int i=0;i<hash->size;) {
		int count=0, basamak, j;
		for(j=i;hash->array[i++] != -1;j++)
			count++;

		if(count == 6)
			basamak = 100000;
		else if(count == 5)
			basamak = 10000;
		else if(count == 4)
			basamak = 1000;
		else if(count == 3)
			basamak = 100;
		else if(count == 2)
			basamak = 10;
		else if(count == 1)
			basamak = count;

		int num = 0;
		for(int m=j-1;hash->array[m] != -1;m--) {
			num += (hash->array[m]-key)*basamak;
			basamak /= 10;
		}

		nums[index++] = num;
	}

	char *str = (char*)malloc(sizeof(char)*index+1);

	for(int i=0;i<index;i++)
		str[i] = nums[i];

	printf("%s\n", str);

	free(str);
	free(nums);
	return 1;
}

void printHash(HASH *hash) {
	for(int i=0;i<hash->size;i++)
		printf("%d", hash->array[i]);
	printf("\n");
}

int main() {
	HASH *hash = (HASH*)malloc(sizeof(HASH));
	init(hash);

	char str[34];

	printf("str: ");
	scanf("%s", str);

	printf("Normal : %s\n", str);

	//encrypt
	put(hash, str);
	printf("Sifrelenmis : ");
	printHash(hash);

	//decrypt
	unput(hash);

	free(hash->array);
	free(hash);

	return 0;
}
