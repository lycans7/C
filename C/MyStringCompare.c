/*
 * MyStringCompare.c
 *
 *  Created on: 03-Jul-2018
 *      Author: eximiusdesign
 */

#include <stdio.h>

int Strcmp(char* firstString, char* secondString) {
	int ret;
	while (*firstString != '\0' && *secondString != '\0') {
		if (*firstString == *secondString) {
			ret = 0;
		} else {
			return *firstString - *secondString;
		}

		firstString++;
		secondString++;
	}
	return ret;
}

int main() {
	char first[50] = { 0 }, second[50] = { 0 };
	int val = 0;

	printf("\n Enter string first \n\t");
	gets(first);
	printf("\n Enter string second \n\t");
	gets(second);

	val = Strcmp(first, second);

	if (val == 0) {
		printf("\n Both string are same  =  %d\n", val);
	} else {
		printf("\n Both string are not same = %d \n", val);
	}
	return 0;
}

