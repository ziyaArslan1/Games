#include <stdio.h>
#include <stdlib.h>

typedef struct _DA {
	void *array;
	size_t capacity;
	size_t size;
	size_t typeSize;
}DA;

int DA_init(DA *arr, size_t typeSize) {
	arr->capacity = 4;
	arr->size = 0;
	arr->typeSize = typeSize;

	arr->array = malloc(typeSize*4);
	if(arr == NULL) {
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

int DA_add(DA *arr, void *address) {
	if(arr->size >= arr->capacity) {
		arr->capacity *= 2;
		arr->array = realloc(arr->array, arr->capacity*arr->typeSize);
		memcpy(arr->array+arr->size*arr->typeSize, address, arr->typeSize);
		arr->size++;

		return EXIT_SUCCESS;
	}

	memcpy(arr->array+arr->size*arr->typeSize, address, arr->typeSize);
	arr->size++;
	return EXIT_SUCCESS;
}

void *DA_get(DA *arr) {
	return arr->array+arr->size;
}

void DA_clear(DA *arr) {
	free(arr->array);
}

void DA_print(DA *arr, size_t type) {
	int index = 1;
	for(size_t i=0;i<arr->typeSize*arr->size;i += arr->typeSize) {
		printf("%d. data: %d\n",index++, *(int*)(arr->array + i));
	}
}

struct test {
	int x,y;
	char name[10];
};

int main() {
	DA *arr;
	struct test t;

	int ch=97;
	for(int i=0;i<5;i++) {
		t.x = rand()%99+1;
		t.y = rand()%99+1;
		strcpy(t.name, (char*)&ch);
		ch++;
	}

	if(DA_init(arr, sizeof(int)) == EXIT_FAILURE) {
		perror("\nDA_init() error!!\n");
		return -1;
	}

	for(int i=1;i<=10;i++) {
		DA_add(arr, &i);
	}

	DA_print(arr, sizeof(int));
	DA_clear(arr);
	return 0;
}
