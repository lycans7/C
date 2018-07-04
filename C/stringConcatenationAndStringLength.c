/*
 * stringConcatenationAndStringLength.c
 *
 *  Created on: 04-Jul-2018
 *      Author: eximiusdesign
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
	int length = PS_stringLength(str1) + PS_stringLength(str2), i = 0;

	char* dynamicArray = (char*) malloc(sizeof(length + 1));

	for (i = 0; i < length; i++) {
		if (*str1 != '\0') {
			*(dynamicArray + i) = *str1++;
		} else {
			*(dynamicArray + i) = *str2++;
		}
	}
	return dynamicArray;

}

int main() {

	char string1[50] = { 0 };
	char string2[50] = { 0 };
	char* ptr;

	printf("\n Enter the First string \n\t");
	gets(string1);

	printf("\n Enter the Second string \n\t");
	gets(string2);

	printf("\n length string1 = [%d] string2 = [%d] \n\t",
			PS_stringLength(string1), PS_stringLength(string2));

	ptr = PS_strcat(string1, string2);

	printf("\n Final string  = [%s] \n\t", ptr);
	free(ptr);

}

