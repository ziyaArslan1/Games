/*

 - Date >> 18 Aralık 2020
 - Copyright o da ne oyle sjjfj
 - author >> Ziya ARSLAN
 - Linked list implementasyonu

*/


#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
	int data;
	struct Node *next;
}LL;

LL *make(int num) {
	LL *newNode = (LL*)malloc(sizeof(LL));
	newNode->data = num;
	newNode->next = NULL;

	return newNode;
}

int nodesLen(LL *ll) {
	LL *iter = ll;
	int len=1;
	while(iter->next != NULL) {
		iter = iter->next;
		len++;
	}

	return len;
}

void clearNodes(LL **ll) {
	free((*ll));
}

void printNodes(LL *ll) {
	LL *temp = ll;

	if(ll == NULL) {
		printf("\nNodes is NULL.\n");
		return;
	}

	int i=1;
	while(temp->next != NULL) {
		printf("%d. node : %d\n", i,temp->data);
		temp = temp->next;
		i++;
	}
	printf("%d. node : %d\n", i, temp->data);
}

LL *addToEnd(LL *ll, int num) {
	if(ll == NULL) {
		LL *newNode = make(num);
		return newNode;
	}

	LL *temp = ll;

	while(temp->next != NULL) { temp = temp->next; }

	temp->next = make(num);
	return ll;
}

void insertionAdd(LL **buffer, LL *ll, int num, int index) {
	LL *iter = ll;
	LL *temp = make(num);

	if(index == 1) {
		*buffer = temp;
		(*buffer)->next = iter;
	} else {
		for(int i=0;i<index-2;i++) {
			iter = iter->next;
		}

		temp->next = iter->next;
		iter->next = temp;
	}
}

int searchNodes(LL *ll, int src) {
	if(ll == NULL) { return 0; }

	int flag = 0;

	LL *temp = ll;

	while(temp->next != NULL) {
		if(temp->data == src) { flag = 1; }
		temp = temp->next;
	}

	if(ll->data == src) { flag = 1; }

	return flag;
}

void deleteNodes(LL **ll, int index) {
	LL *iter = (*ll);

	if(index == 1) {
		iter = iter->next;
		free((*ll));
		(*ll) = iter;
		return;
	}

	iter = (*ll);
	for(int i=0;i<index-2;i++) { iter = iter->next; }

	iter->next = iter->next->next;
}

void choiceMenu() {
	printf("\nEleman ekleme       : [1]");
	printf("\nAraya eleman ekleme : [2]");
	printf("\nEleman silme        : [3]");
	printf("\nEleman arama        : [4]");
	printf("\nListeyi yazdirma    : [5]");
	printf("\n\nEXIT                : [0]\n\n");
}

int main() {
	LL *root = NULL;
	int choice, num, index;

	while(1) {
		//system("cls || clear");
		choiceMenu();
		printf("\nChoice: ");
		scanf("%d", &choice);

		switch(choice) {
			case 1:
				printf("\nEnter num: ");
				scanf("%d", &num);
				root = addToEnd(root, num);
				printf("\nSuccess.\n");
				break;
			case 2:
				printf("\nEnter num: ");
				scanf("%d", &num);
				printf("\nEnter index: ");
				scanf("%d", &index);
				if(index > nodesLen(root) || index < 0) {
					printf("\nindex not found!\n");
				} else {
					insertionAdd(&root, root, num, index);
					printf("\nSuccess.\n");
				}
				break;
			case 3:
				printf("\nEnter index: ");
				scanf("%d", &index);
				if(index > nodesLen(root) || index < 0) {
					printf("\nindex not found!\n");
				} else {
					deleteNodes(&root, index);
					printf("\nSuccess.\n");
				}
				break;
			case 4:
				printf("\nSearch num: ");
				scanf("%d", &num);
				if(searchNodes(root, num)) {
					printf("\nFound num[+]\n");
				} else {
					printf("\nNum not found[-]\n");
				}
				break;
			case 5:
				system("cls || clear");
				printNodes(root);
				break;
			case 0:
				clearNodes(&root);
				root = NULL;
				exit(0);
			default:
				printf("\nChoice not found!\n");
				break;
		}
	}

	return 0;
}
