#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>

#define X 20
#define Y 20

typedef struct {
	int x,y;
}snake_t;

int len=4;
int score=0;
int row=5, col=10;

char map[X][Y];

int kbhit()
{
    struct termios term;
    tcgetattr(0, &term);

    struct termios term2 = term;
    term2.c_lflag &= ~ICANON;
    tcsetattr(0, TCSANOW, &term2);

    int byteswaiting;
    ioctl(0, FIONREAD, &byteswaiting);

    tcsetattr(0, TCSANOW, &term);

    return byteswaiting > 0;
}

int continues(snake_t *snake) {
	int k1=0, k2=0;

	if(snake[0].x == 0 || snake[0].x == 19 || snake[0].y == 0 || snake[0].y == 39) {
		k1 = 1;
	}

	for(int i=1;i<len;i++) {
		if(snake[0].x == snake[i].x && snake[0].y == snake[i].y) {
			k2 = 1;
			break;
		}
	}

	return (k1 == 1 || k2 == 1);
}

void yemleme() {
	row = rand()%((X-2)-2+1)+2;
	col = rand()%((Y-2)-2+1)+2;
}

void yem(char arr[][Y], snake_t *snake) {
	if(snake[len-1].x == row && snake[len-1].y == col) {
		snake[len].x = row;
		snake[len].y = col;
		len++;
		score += 10;
		yemleme();
		printf("\a");
	}
}

void defend(char arr[][Y]) {
	for(int i=0;i<X;i++) {
		if(i == 0 || i == 19) {
			for(int j=0;j<Y;j++)
				arr[i][j] = '=';
		} else {
			arr[i][0] = '|';
			for(int j=1;j<Y-1;j++)
				arr[i][j] = ' ';
			arr[i][Y-1] = '|';
		}
	}

	map[row][col] = 'x';
}

void print(char arr[][Y]) {
	system("cls | clear");

	printf("score: %d\n", score);

	for(int i=0;i<X;i++) {
		for(int j=0;j<Y;j++) {
			printf("%c ", arr[i][j]);
		}
		printf("\n");
	}
}

void start(snake_t *snake) {
	snake[0].x = 1;
	snake[0].y = 4;

	snake[1].x = 1;
	snake[1].y = 3;

	snake[2].x = 1;
	snake[2].y = 2;

	snake[3].x = 1;
	snake[3].y = 1;
}

void snakeInfo(char arr[][Y], snake_t *snake) {
	yem(map, snake);

	for(int i=0;i<len;i++)
		arr[snake[i].x][snake[i].y] = '*';
}

void fright(snake_t *snake, const int lenght) {
	for(int i=lenght-1;i>0;i--) {
		snake[i].x = snake[i-1].x;
		snake[i].y = snake[i-1].y;
	}

	snake[0].y++;
}

void fleft(snake_t *snake, const int lenght) {
	for(int i=lenght-1;i>0;i--) {
		snake[i].x = snake[i-1].x;
		snake[i].y = snake[i-1].y;
	}

	snake[0].y--;
}

void fup(snake_t *snake, const int lenght) {
	for(int i=lenght-1;i>0;i--) {
		snake[i].x = snake[i-1].x;
		snake[i].y = snake[i-1].y;
	}

	snake[0].x--;
}

void fdown(snake_t *snake, const int lenght) {
	for(int i=lenght-1;i>0;i--) {
		snake[i].x = snake[i-1].x;
		snake[i].y = snake[i-1].y;
	}

	snake[0].x++;
}

void ctrlRight(long int *i, int *ctrl, snake_t *snake, long int miliSecond) {
	while(*i < 100000) {
		if(*i % 2000 == 0) {
			if(continues(snake)) {
				print(map);
				*ctrl = 1;
				break;
			}
			fright(snake, len);
			defend(map);
			snakeInfo(map, snake);
			print(map);
			usleep(miliSecond);
		}
		(*i)++;
		if(kbhit()) break;
	}
}

void ctrlLeft(long int *i, int *ctrl, snake_t *snake, long int miliSecond) {
    while(*i < 100000) {
        if(*i % 2000 == 0) {
            if(continues(snake)) {
                print(map);
                *ctrl = 1;
                break;
            }
            fleft(snake, len);
            defend(map);
            snakeInfo(map, snake);
            print(map);
			usleep(miliSecond);
        }
        (*i)++;
        if(kbhit()) break;
    }
}

void ctrlUp(long int *i, int *ctrl, snake_t *snake, long int miliSecond) {
    while(*i < 100000) {
        if(*i % 2000 == 0) {
            if(continues(snake)) {
                print(map);
                *ctrl = 1;
                break;
            }
            fup(snake, len);
            defend(map);
            snakeInfo(map, snake);
            print(map);
			usleep(miliSecond);
        }
        (*i)++;
        if(kbhit()) break;
    }
}

void ctrlDown(long int *i, int *ctrl, snake_t *snake, long int miliSecond) {
    while(*i < 100000) {
        if(*i % 2000 == 0) {
            if(continues(snake)) {
                print(map);
                *ctrl = 1;
                break;
            }
            fdown(snake, len);
            defend(map);
            snakeInfo(map, snake);
            print(map);
			usleep(miliSecond);
        }
        (*i)++;
        if(kbhit()) break;
    }
}

void welcome() {
	printf("Yilan Oyunu\n\n");
	printf("Oyuna baslamak icin yon(a,w,s,d) tusuna basip enter yapin.\n");
	printf("sonrasinda artik a,w,s,d tuslarina basarak(enter yapmadan) hareket edebilirsiniz..\n");
	printf("\nKolay gelsin :)\n");
}

int main() {
	srand((unsigned)time(NULL));

	FILE *file = fopen("snake.txt", "w+");

	char name[30];
	printf("isminiz: ");
	fgets(name, sizeof(name), stdin);
	name[strlen(name)-1] = '\0';

	char yon;
	snake_t snake[100];
	long int i, miliSecond=90000;
	int ctrl=0;

	defend(map);
	start(snake);
	snakeInfo(map, snake);
	print(map);

	welcome();

	while(1) {
		yon = getchar();
		i=0;

		if(yon == 'd')
			ctrlRight(&i, &ctrl, snake, miliSecond);
		else if(yon == 'a')
			ctrlLeft(&i, &ctrl, snake, miliSecond);
		else if(yon == 'w')
			ctrlUp(&i, &ctrl, snake, miliSecond);
		else if(yon == 's')
			ctrlDown(&i, &ctrl, snake, miliSecond);
		else continue;

		if(ctrl == 1) break;
	}

	printf("Skorunuz: %d\n", score);

	fprintf(file, "isim: %s  >> Skor: %d\n", name, score);
	fclose(file);

	return 0;
}
/*
Bence sebebi ekranı sürekli silip tekrar yazmandan kaynaklanıyor. Öyle yapmak yerine sadece değişiklik olan koordinatları değiştir aynı olan koordinatları tekrar çizdirme. Bu yüzden CLS yerine daha işlevli sadece koordinat silebilen bir fonksiyon aramalısın. Sağlam garafik kütüphanelerinde böyle fonksiyonlar mutlaka mevcuttur . Eğer böyle bir fonksiyon kullanırsan programın daha iyi olacaktır. OpenGL falan araştırmanı tavsiye ederim , grafikle ilgili sağlam kütüphaneleri mevcut.


PPau_end9 Temmuz 2010 Cuma 13:07:02 (1 mesaj)
İşlem

0
Çok özür dilerim farklı bi başlık altında yazıyorum ama..Arkadaşlar C++'den bi ödevim var yardım edebilecek olan biri varsa lütfen çok acil...:(..


SSettingsBoy9 Temmuz 2010 Cuma 13:55:42 (98 mesaj)
İşlem

0
eheheh oynadım güzelmiş.

s tuşu ile başlayın oyuna


Moribito12 Temmuz 2010 Pazartesi 12:57:58 (3776 mesaj)
İşlem

0
Oyunu oynamadim ama;

main functionda


while(i<100000) var, ve saniyorsam her hareketten sonra, program karar veriyor, programi 100000 lik bir loopa sokmak her seferinde CPUyu cok zorlar. Daha degisik bir karar verme motoru gelistirmen gerekebilir, ama dedigim gibi incelemedim programi, %40-50 CPU kullanimi bu loop yuzunden oldugunu dusnuyorum.


Kkayhantolga15 Şubat 2011 Salı 16:23:57 (42 mesaj)
İşlem

0
Bence de ekranı silip yazması yoruyor işlemciyi çünkü printf fonksiyonu ağır bir fonksiyonhttp://letscoding.com/2011/02/12/snake-v2-0/ bu adreste bir örnek var bak istersen


VVLC1117 Şubat 2011 Perşembe 13:19:06 (10 mesaj)
İşlem

0
Hos olmus eline saglik
bencede ekranin surekli yenilenmesinden dolayi islemci kullanimi artiyor.
cunku sonsuz donuyor program duvara carpana kadar donecek.
bunu aciklamak icin bir ornek vercek olursak printf le herhangi bir sey yazin ve bunu sonsuz donguye sokun ve programi calistirin
benim 4 cekirdekli phenomII 965 im %30 yuk altina girdi 
bu aslinda C nin cok zayif bir dil olmasindan kaynaklaniyor
C# veya diger visual dilleri og
Allah çarpar adamı 


evgind20 Şubat 2011 Pazar 00:45:59 (548 mesaj)
İşlem

0
quote:

Orijinalden alıntı: R_M_A


bu aslinda C nin cok zayif bir dil olmasindan kaynaklaniyor
C# veya diger visual dilleri ogrenip onlarla yazarsaniz daha etkin olur 


Hadi canim kapat sen o kapiyi, soguk girmesin içeriye.


VVLC1121 Şubat 2011 Pazartesi 16:13:52 (10 mesaj)
İşlem

0
artistik yapacagina adama yardimci olacak bisi yaz lale


Qqamyoncu21 Şubat 201
*/
