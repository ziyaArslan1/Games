/*
* date  : 03.03.2021
* author: ziya arslan
* generic dynamic array
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct _ZZ {
        void *arr;
        size_t cap;
        size_t size;
        size_t type;
}ZZ;

int init(ZZ *root, size_t type) {
        root->cap = 4;
        root->size = 0;
        root->type = type;

        root->arr = malloc(type*root->cap);

        if(root->arr == NULL)
                return EXIT_FAILURE;

        return EXIT_SUCCESS;
}

int addFunction(ZZ *root, void *address) {
        if(root->size >= root->cap) {
                root->cap *= 2;
                root->arr = realloc(root->arr, root->cap*root->type);

                memcpy(root->arr + root->size * root->type, address, root->type);
                root->size++;
                return EXIT_SUCCESS;
        }

        memcpy(root->arr + root->size * root->type, address, root->type);
        root->size++;
        return EXIT_SUCCESS;
}

int delFunction(ZZ *root, size_t index) {
        if(root->size == 0) {
                printf("array is empty!\n");
                return EXIT_FAILURE;
        }
        return 1;
}

void clearZZ(ZZ *root) {
        free(root->arr);
        free(root);
}

void printZZ(ZZ *root, size_t type) {
        size_t index=1;

        for(size_t i=0;i<root->type*root->size;i += root->type)
                printf("%zu. data: %d\n", index++, *(int*)(root->arr+i));

}

int main() {
        // test
        ZZ *start = (ZZ*)malloc(sizeof(ZZ));

        if(init(start, sizeof(int)) == EXIT_FAILURE) {
                printf("\ninit() error!\n");
                return -1;
        }

        for(int i=1;i<=20;i++) {
                int num = rand()%(122-97+1)+97;
                addFunction(start, &num);
        }

        printZZ(start, sizeof(int));

        printf("\ncap : %zu\n", start->cap);
        printf("size: %zu\n", start->size);
        printf("type: %zu\n", start->type);

        clearZZ(start);
        return 0;
}
