/*
 * stringConcatenationAndStringLength.c
 *
 *  Created on: 04-Jul-2018
 *      Author: Parth Shah
 */

#include <stdio.h>
#include <stdlib.h>

int PS_stringLength(char* str) {
	int count = 0;
	while (*str++ != '\0') {
		count++;
	}
	return count;
}

char* PS_strcat(char* str1, char* str2) {
	int length = PS_stringLength(str1) + PS_stringLength(str2);
	char* buff = NULL;

	if (PS_stringLength(str1) < length) {
		buff = (char *) realloc(str1, length + 1);
	}
	while (*buff != '\0') {
		buff++;
	}

	while (*str2 != '\0') {
		*buff++ = *str2++;
	}
	return str1;

}

int main() {
	char* string1 = (char*) malloc(5);

	char* string2 = (char*) malloc(5);

	printf("\n Enter the First string \n\t");
	gets(string1);

	printf("\n Enter the Second string \n\t");
	gets(string2);

	printf("\n length string1 = [%d] string2 = [%d] \n\t",
			PS_stringLength(string1), PS_stringLength(string2));

	string1 = PS_strcat(string1, string2);

	printf("\n Final string  = [%s] \n\t", string1);
	free(string1);
	free(string2);
}

