#include <stdio.h>
#include <stdlib.h>

#define DA_DEF(TYPE) \
typedef struct TYPE##opt { \
        TYPE *arr; \
        size_t capacity; \
        size_t size; \
}TYPE##_opt; \
void init(TYPE##_opt *res) { \
	res->capacity = 4;\
	res->size = 0;\
	res->arr = (TYPE*)malloc(sizeof(TYPE)*res->capacity);\
}\
TYPE##_add(TYPE##_opt * res, TYPE value) {\
		if(res->size < res->capacity) \
			res->arr[res->size++] = value;\
		else\
			printf("array is full\n");\
}

DA_DEF(int); // DA_DEF(int) -> TYPE = int

int main() {
	int_opt *x = (int_opt*)malloc(sizeof(int_opt));
	init(x);

	for(int i=0;i<5;i++)
		int_add(x, i);

	for(size_t i=0;i<x->size;i++)
		printf("%d\n", x->arr[i]);

	free(x->arr);
	free(x);

	return 0;
}
