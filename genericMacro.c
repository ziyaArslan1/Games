#include <stdio.h>
#include <stdlib.h>

#define DA_DEF(TYPE) \
typedef struct TYPE##opt { \
        TYPE *array; \
        size_t capacity; \
        size_t size; \
		char type[10]; \
}TYPE##_opt; \
void init(TYPE##_opt *res, char *type) { \
	res->capacity = 4;\
	res->size = 0;\
	res->array = (TYPE*)malloc(sizeof(TYPE)*res->capacity);\
	strcpy(res->type, type); \
}\
void add(TYPE##_opt * res, TYPE value) {\
	if(res->size < res->capacity) {\
		res->array[res->size++] = value;\
	}else{\
		res->array = (TYPE*)realloc(res->array, sizeof(TYPE)*res->capacity*2);\
		res->capacity *= 2;\
	}\
}

DA_DEF(int); // DA_DEF(int) -> TYPE = int

int main() {
	int_opt *x = (int_opt*)malloc(sizeof(int_opt));
	init(x, "int");

	for(int i=0;i<10;i++)
		add(x, i);

	for(size_t i=0;i<x->size;i++)
		printf("%d\n", x->array[i]);

	free(x->array);
	free(x);

	return 0;
}
