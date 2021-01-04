#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int myStrlen(char *str) {
	int num=0;
	for(int i=0;str[i] != '\0';i++) num++;
	return num;
}

void myStrcpy(char *str1, char *str2) {
	int len = myStrlen(str2);
	int i;

	for(i=0;i<len;i++) {
		str1[i] = str2[i];
	}
	str1[i] = '\0';
}

void print(char str[][30]) {
	for(int i=0;i<10;i++) {
		printf("\n%d word : %s\n", i+1, str[i]);
	}
}

int main() {
	char arr[10][30]={0};
	char str[200]={0};

	printf("\nCumle gir(sadece 200 karakter): ");
	fgets(str, sizeof(str), stdin);

	int y=0;

	printf("\nKelimeler ayriliyor....\n");
	sleep(1);

	for(int i=0;i<myStrlen(str);) {
		int j, x=0;
		for(j=i;str[j] != ' ';j++);

		char *temp = (char*)malloc(sizeof(char)*j);

		for(j=i;str[i++] != ' ';j++) {
			temp[x++] = str[j];
		}

		myStrcpy(arr[y++], temp);
		free(temp);
	}

	print(arr);
	fflush(stdin);
	fflush(stdout);
	return 0;
}
