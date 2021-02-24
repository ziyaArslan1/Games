#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

void myScanf(char *fmt, ...) {
	va_list arg;
	va_start(arg, fmt);

	int *integerArg;
	char *charArg;
	char *strArg;

	for(size_t i=0;i<strlen(fmt);i++) {
		switch(fmt[i]) {
			case 'd':
				integerArg = va_arg(arg, int*);
				*integerArg = 34;
				break;
			case 'c':
				charArg = va_arg(arg, char*);
				*charArg = 'z';
				break;
			case 's':
				strArg = va_arg(arg, char*);
				strcpy(strArg, "hiii");
				break;
			default:
				continue;
		}
	}
}

int main() {
	int a;
	char b;
	char c[10];

	myScanf("dcs", &a, &b, c);

	printf("%d  %c   %s\n", a,b,c);

	return 0;
}
