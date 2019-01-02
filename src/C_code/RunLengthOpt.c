/*
 * RunLengthOpt.c
 *
 *  Created on: 11-Jul-2018
 *      Author: Parth Shah
 */

#include <stdio.h>

int PS_charToInt(char* str, int count) {
	int buff, i = 0, temp, dum;
	temp = count;
	while (temp > 0) {
		temp = temp / 10;
		i++;
	}
	dum = i;
	while (count > 0) {
		buff = count % 10;
		str[i--] = buff + '0';
		count = count / 10;
	}
	printf(" str = %s\n", str);
	return dum;
}

void Runlength(char *str) {
	char *ptr = str;
	int count = 1;
	while (*str != '\0') {
		if (*++str == *ptr) {
			count++;
		} else {
			if (count > 1) {
				ptr += PS_charToInt(ptr, count);
			}
			count = 1;
			*++ptr = *str;
		}
	}

}

int main() {
	char string[120];
	printf("\n Enter the string\n");
	gets(string);
	Runlength(string);
	printf(" Final string = %s ", string);
	return 0;
}

