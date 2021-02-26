#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAPSIZE 5

struct TANK {
	char name[3];
	size_t row, column;
	int hp;
};

void initTank(struct TANK *t) {
	for(size_t i=0;i<10;i++) {
		char name[3]={0};
		for(size_t j=0;j<3;j++)
			name[j] = rand()%(122-97+1)+97;

		strcpy(t[i].name, name);
		t[i].row = i;
		t[i].column = i;
		t[i].hp = 10;
	}
}

void printTank(struct TANK *t) {
	for(size_t i=0;i<10;i++) {
		printf("\n\n%zu. tank : ", i+1);
		printf("name: %s\n", t[i].name);
		printf("location: %zu-%zu\n", t[i].row, t[i].column);
		printf("hp: %d\n\n", t[i].hp);
	}
}

void init(char tankMap[][MAPSIZE][MAPSIZE], int playerMap[][MAPSIZE], struct TANK *t) {
	size_t index=0;

	for(size_t i=0;i<MAPSIZE;i++)
		for(size_t j=0;j<MAPSIZE;j++)
			strcpy(tankMap[i][j], "   ");
	int flag=10;
	while(flag--)
		strcpy(tankMap[rand()%MAPSIZE+0][rand()%MAPSIZE+0], t[index++].name);

	playerMap[rand()%MAPSIZE+0][rand()%MAPSIZE+0] = 1;
}

void printMap(char tankMap[][MAPSIZE][MAPSIZE]) {
	printf("    ");
	for(size_t i=0;i<MAPSIZE;i++)
		printf("  %zu  |", i);
	printf("\n");
	printf("__________________________________\n");

	for(size_t i=0;i<MAPSIZE;i++) {
		printf("%zu ->", i);
		for(size_t j=0;j<MAPSIZE;j++)
			printf(" xxx |"/*, tankMap[i][j]*/);
		printf("\n");
	}
}

int deadTank(char tankMap[][MAPSIZE][MAPSIZE], size_t row, size_t column, struct TANK *t) {
	size_t i;

	for(i=0;i<10;i++) {
		if(strcmp(t[i].name, tankMap[row][column]) == 0) {
			t[i].hp -= 5;
			break;
		}
	}

	if(t[i].hp == 0) {
		strcpy(tankMap[row][column], "   ");
		return 1;
	}

	return 0;
}

void damagePlayer(int *playerHp) {
	*playerHp -= 5;
}

int tankCtrl(char tankMap[][MAPSIZE][MAPSIZE]) {
	for(size_t i=0;i<MAPSIZE;i++)
		for(size_t j=0;j<MAPSIZE;j++)
			if(!(strcmp(tankMap[i][j], "  ") == 0))
				return 1;

	return 0;
}

void game(char tankMap[][MAPSIZE][MAPSIZE], int playerMap[][MAPSIZE], int *playerHp, struct TANK *t) {
	size_t row, column;

	while(tankCtrl(tankMap)) {
		printMap(tankMap);
		printf("\nenter row column(0-9): ");
		scanf("%zu%zu", &row, &column);

		system("clear || cls");

		if(!(strcmp(tankMap[row][column], "   ") == 0)) {
			printf("%s is damaged\n", tankMap[row][column]);
			if(deadTank(tankMap, row, column, t))
				printf("%s is dead\n", tankMap[row][column]);
		} else {
			printf("empty\n");
		}

		for(size_t i=0;i<5;i++) {
			row = rand()%MAPSIZE+0;
			column = rand()%MAPSIZE+0;

			if(playerMap[row][column] == 1)
				damagePlayer(&(*playerHp));
		}

		printf("your Hp: %d\n", *playerHp);
	}

	printMap(tankMap);
}

int main() {
	srand((unsigned)time(NULL));

	struct TANK t[10];

	char tankMap[MAPSIZE][MAPSIZE][MAPSIZE];
	int playerMap[MAPSIZE][MAPSIZE];

	int playerHp=100;

	initTank(t);
	init(tankMap, playerMap, t);

	game(tankMap, playerMap, &playerHp, t);

	system("clear");
	printf("you win\n\n");

	return 0;
}
