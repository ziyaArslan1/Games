/* date: 08.03.2021
   author: ziya arslan
   copyright: NONE
   update: continues
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

#define MAPSIZE 7
#define TANKSIZE 15

typedef struct _ENEMYTANK {
	char name[3];
	size_t row, col;
	int hp, gun;
}enemyTank;

typedef struct _PLAYERTANK {
	char name[3];
	size_t row, col;
	int hp, gun;
}playerTank;

void initPCTank(enemyTank (*enemyTanks)[]) {
	for(size_t i=0;i<20;i++) {
		char name[3]={0};
		for(size_t j=0;j<3;j++)
			name[j] = rand()%(122-97+1)+97;

		strcpy((*enemyTanks)[i].name, name);
		(*enemyTanks)[i].hp = 10;
		(*enemyTanks)[i].gun = 10;
	}
}

void initPlayerTank(playerTank (*playerTanks)[]) {
	for(size_t i=0;i<TANKSIZE;i++) {
		char name[3] = {0};
		for(size_t j=0;j<3;j++)
			name[j] = rand()%(122-97+1)+97;
		strcpy((*playerTanks)[i].name, name);
		(*playerTanks)[i].hp = 10;
		(*playerTanks)[i].gun = 10;
	}
}

void initMain(char (*tankMap)[][MAPSIZE][MAPSIZE], char (*playerMap)[][MAPSIZE][MAPSIZE], enemyTank (*enemyTanks)[], playerTank (*playerTanks)[]) {
	size_t index=0;

	for(size_t i=0;i<MAPSIZE;i++) {
		for(size_t j=0;j<MAPSIZE;j++) {
			strcpy((*tankMap)[i][j], "   ");
			strcpy((*playerMap)[i][j], "   ");
		}
	}

	int flag=20;
	while(flag--) {
		strcpy((*tankMap)[rand()%MAPSIZE+0][rand()%MAPSIZE+0], (*enemyTanks)[index].name);
		strcpy((*playerMap)[rand()%MAPSIZE+0][rand()%MAPSIZE+0], (*playerTanks)[index].name);
		index++;
	}
}

void printMap(char (*tankMap)[][MAPSIZE][MAPSIZE]) {
	printf("    ");
	for(size_t i=0;i<MAPSIZE;i++)
		printf("  %zu  |", i);
	printf("\n");
	printf("______________________________________________\n");
	for(size_t i=0;i<MAPSIZE;i++) {
		printf("%zu ->", i);
		for(size_t j=0;j<MAPSIZE;j++)
			printf(" %s |", (*tankMap)[i][j]);
		printf("\n");
	}
	printf("______________________________________________\n");
}

int deadTank(char (*tankMap)[][MAPSIZE][MAPSIZE], size_t row, size_t column, enemyTank (*enemyTanks)[]) {
	size_t i;

	for(i=0;i<TANKSIZE;i++) {
		if(strcmp((*enemyTanks)[i].name, (*tankMap)[row][column]) == 0) {
			(*enemyTanks)[i].hp -= 5;
			break;
		}
	}

	if((*enemyTanks)[i].hp == 0) {
		strcpy((*tankMap)[row][column], "   ");
		return 1;
	}

	return 0;
}

int tankCtrl(char (*tankMap)[][MAPSIZE][MAPSIZE], enemyTank (*enemyTanks)[]) {
	for(size_t i=0;i<MAPSIZE;i++) {
		for(size_t j=0;j<MAPSIZE;j++) {
			for(size_t index=0;index<TANKSIZE;index++) {
				if(strcmp((*tankMap)[i][j], (*enemyTanks)[index].name) == 0)
					return 1;
			}
		}
	}

	return 0;
}

int ctrlYourTank(char (*playerMap)[][MAPSIZE][MAPSIZE], playerTank (*playerTanks)[]) {
	for(size_t i=0;i<MAPSIZE;i++)
		for(size_t j=0;j<MAPSIZE;j++)
			for(size_t index=0;index<TANKSIZE;index++)
				if(strcmp((*playerMap)[i][j], (*playerTanks)[index].name) == 0)
					return 1;
	return 0;
}

int entryCtrl(char *row, char *column) {
	if(strlen(row) != 1 || strlen(column) != 1)
		return 1;
	if(!(row[0] >= 48 && row[0] <= 54) || !(column[0] >= 48 && column[0] <= 54))
		return 1;
	return 0;
}

void game(char (*tankMap)[][MAPSIZE][MAPSIZE], char (*playerMap)[][MAPSIZE][MAPSIZE], enemyTank (*enemyTanks)[], playerTank (*playerTanks)[]) {
	while(tankCtrl(tankMap, enemyTanks)) {
		char row[2], column[2];
		printMap(tankMap);

		printf("\n\nenter row column(0-4): ");
		scanf("%s%s", row, column);

		while(entryCtrl(row, column)) {
			printf("\nHata. lutfen tekrar gir.\n");
			printf("\nenter row column(0-4): ");
			scanf("%s%s", row, column);
		}

		system("clear");

		if(!(strcmp((*tankMap)[atoi(row)][atoi(column)], "   ") == 0)) {
			printf("%s is damaged\n", (*tankMap)[atoi(row)][atoi(column)]);
			if(deadTank(tankMap, atoi(row), atoi(column), enemyTanks))
				printf("%s is dead\n", (*tankMap)[atoi(row)][atoi(column)]);
		} else {
			printf("empty\n");
		}

		if(ctrlYourTank(playerMap, playerTanks)) {
			printf("\n\e[91mmission failed!!!\n\n");
			return;
		}
	}

	printf("\nYOU WIN\n\n");
	printMap(tankMap);
}

int main() {
	srand((unsigned)time(NULL));

	enemyTank enemyTanks[TANKSIZE];
	playerTank playerTanks[TANKSIZE];

	char tankMap[MAPSIZE][MAPSIZE][MAPSIZE];
	char playerMap[MAPSIZE][MAPSIZE][MAPSIZE];

	initPCTank(&enemyTanks);
	initPlayerTank(&playerTanks);

	initMain(&tankMap, &playerMap, &enemyTanks, &playerTanks);

	system("clear");

	printf("\n-------ENEMYTANKS--------\n");
	printMap(&tankMap);
	printf("\n-------PLAYERTANKS-------\n");
	printMap(&playerMap);

	//game(&tankMap, &playerMap, &enemyTanks, &playerTanks);
	return 0;
}
