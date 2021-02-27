#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

#define MAPSIZE 7
#define TANKSIZE 15

struct TANK {
	char name[3];
	size_t row, column;
	int hp;
};

void initTank(struct TANK *t) {
	for(size_t i=0;i<20;i++) {
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
	for(size_t i=0;i<TANKSIZE;i++) {
		printf("\n\n%zu. tank : ", i+1);
		printf("name: %s\n", t[i].name);
		printf("location: %zu-%zu\n", t[i].row, t[i].column);
		printf("hp: %d\n\n", t[i].hp);
	}
}

void init(char tankMap[][MAPSIZE][MAPSIZE], int playerMap[][MAPSIZE], struct TANK *t) {
	size_t index=0;

	for(size_t i=0;i<MAPSIZE;i++) {
		for(size_t j=0;j<MAPSIZE;j++) {
			strcpy(tankMap[i][j], "   ");
			playerMap[i][j] = -1;
		}
	}

	int flag=20;
	while(flag--)
		strcpy(tankMap[rand()%MAPSIZE+0][rand()%MAPSIZE+0], t[index++].name);

	playerMap[rand()%MAPSIZE+0][rand()%MAPSIZE+0] = 1;
}

void printMap(char tankMap[][MAPSIZE][MAPSIZE]) {
	printf("    ");
	for(size_t i=0;i<MAPSIZE;i++)
		printf("  %zu  |", i);
	printf("\n");
	printf("______________________________________________\n");
	for(size_t i=0;i<MAPSIZE;i++) {
		printf("%zu ->", i);
		for(size_t j=0;j<MAPSIZE;j++)
			printf(" +++ |"/*, tankMap[i][j]*/);
		printf("\n");
	}
	printf("______________________________________________\n");
}

int deadTank(char tankMap[][MAPSIZE][MAPSIZE], size_t row, size_t column, struct TANK *t) {
	size_t i;

	for(i=0;i<TANKSIZE;i++) {
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

int tankCtrl(char tankMap[][MAPSIZE][MAPSIZE], struct TANK *t) {
	for(size_t i=0;i<MAPSIZE;i++) {
		for(size_t j=0;j<MAPSIZE;j++) {
			for(size_t index=0;index<TANKSIZE;index++) {
				if(strcmp(tankMap[i][j], t[index].name) == 0)
					return 1;
			}
		}
	}

	return 0;
}

int entryCtrl(char *row, char *column) {
	if(strlen(row) != 1 || strlen(column) != 1)
		return 1;
	if(!(row[0] >= 48 && row[0] <= 54) || !(column[0] >= 48 && column[0] <= 54))
		return 1;
	return 0;
}

void game(char tankMap[][MAPSIZE][MAPSIZE], int playerMap[][MAPSIZE], int *playerHp, struct TANK *t) {
	while(tankCtrl(tankMap, t)) {
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

		if(!(strcmp(tankMap[atoi(row)][atoi(column)], "   ") == 0)) {
			printf("%s is damaged\n", tankMap[atoi(row)][atoi(column)]);
			if(deadTank(tankMap, atoi(row), atoi(column), t))
				printf("%s is dead\n", tankMap[atoi(row)][atoi(column)]);
		} else {
			printf("empty\n");
		}

		for(size_t i=0;i<(TANKSIZE-rand()%TANKSIZE+0);i++) {
			int rnd1 = rand()%MAPSIZE+0;
			int rnd2 = rand()%MAPSIZE+0;

			if(playerMap[rnd1][rnd2] == 1) {
				//printf("\nbuffers\n");
				damagePlayer(&(*playerHp));
			}
		}

		printf("your Hp: %d\n", *playerHp);

		if(*playerHp == 0) {
			printf("\n\e[91mmission failed!!!\n\n");
			return;
		}
	}

	printf("\nYOU WIN\n\n");
	printMap(tankMap);
}

int main() {
	srand((unsigned)time(NULL));

	struct TANK t[TANKSIZE];

	char tankMap[MAPSIZE][MAPSIZE][MAPSIZE];
	int playerMap[MAPSIZE][MAPSIZE];

	int playerHp=100;

	initTank(t);
	init(tankMap, playerMap, t);

	system("clear");
	game(tankMap, playerMap, &playerHp, t);
	return 0;
}
