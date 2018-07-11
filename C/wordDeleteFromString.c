/*
 * wordDeleteFromString.c
 *
 *  Created on: 03-Jul-2018
 *      Author: Parth Shah
 */

#include <stdio.h>

void Delete(char* start, char* last, int count) {
	int i;
	char temp;
	for (i = 0; i < count; i++) {
		*start++ = *last++;
	}

}

void DeleteAChar(char *str, char del) {
	char *start = str, *last = str;
	int count = 0;
	while (*last != '\0') {
		if (*last == del) {
			start = last;
			while (*last++ != '\0') {
				count++;
			}
			last = start + 1;
			Delete(start, last, count);
			break;
		}

		last++;
	}

}

int main() {
	char string[50] = "Hello how are you";
	char del;
	printf("\n  string = %s \n\t", string);
	printf("\n  Enter the char you want to delete\n\t");
	scanf("%c", &del);

	DeleteAChar(string, del);

	printf("\n Final string after delete char = %s \n", string);

	return 0;
}

