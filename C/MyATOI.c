/*
 * MyATOI.c
 *
 *  Created on: 04-Jul-2018
 *      Author: Parth Shah
 */

#include <stdio.h>

int PS_atoi(char* str) {
	if (*str == '\0') {
		return NULL;
	}

	int buff = 0;

	while (*str != '\0' && *str >= '0' && *str <= '9') {
		buff = buff * 10 + *str++ - '0';
	}

	return buff;
}

int main() {
	char string[50] = "1223Str";
	int val = PS_atoi(string);
	printf("\n Final string = [%d] \n", val);
	return 0;
}

