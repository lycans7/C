/*
 * ReverseAWord.c
 *
 *  Created on: 29-Jun-2018
 *      Author: Parth
 */

#include <stdio.h>
#include <string.h>

void reverseChar(char* x, char* y) {
	char temp;
	while (x < y) {
		temp = *x;
		*x++ = *y;
		*y-- = temp;
	}
}

void reverseAWord(char *p) {
	char* lastpos = p, *frontpos = p;
	while (*lastpos) {
		lastpos++;
		if (*lastpos == '\0') {
			reverseChar(frontpos, lastpos - 1);
		} else if (*lastpos == ' ') {
			reverseChar(frontpos, lastpos -1);
			frontpos = lastpos + 1;
		}
	}
}

int main(int arg, char *argv[]) {

	char str[20] = "Hello How are you";
	printf("\n %s \n",str);
	reverseAWord(str);
	printf("\n %s \n",str);
	return 0;
}

