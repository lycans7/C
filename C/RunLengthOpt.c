/*
 * RunLengthOpt.c
 *
 *  Created on: 11-Jul-2018
 *      Author: eximiusdesign
 */

#include <stdio.h>

void Runlength(char *str) {
	char *ptr = str;
	int count = 1;
	while (*str != '\0') {
		if (*++str == *ptr) {
			count++;
		} else {
			if (count > 1)
				*++ptr = count + '0';
			count = 1;
			*++ptr = *str;
		}
	}

}

int main() {
	char string[50];
	printf("\n Enter the string\n");
	gets(string);
	Runlength(string);
	printf(" Final string = %s ", string);
	return 0;
}

