/*
 * RunLength.c
 *
 *  Created on: 10-Jul-2018
 *      Author: Parth Shah
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* PS_RunLenSingleChar(char* str) {

	if (str == NULL) {
		return NULL;
	}

	int i = 0, count = 1, flag = 0;
	i = strlen(str);

	char* ptr = (char *) malloc(i + 1), *buff;
	buff = ptr;
	while (*str != '\0') {
		if (*str != *(str + 1) && flag == 0) {
			*ptr++ = *str++;
		} else if (*str == *(str + 1)) {
			count++;
			*ptr = *str++;
			flag = 1;
		} else if (*str != *(str + 1) && flag == 1) {
			*++ptr = count + '0';
			count = 1;
			flag = 0;
			ptr++;
			str++;
		}
	}
	if (count > 2 && *str == '\0') {
		*++ptr = count;
		count = 0;
		flag = 0;
	}
	return buff;
}

int main() {
	char string[50], *out;

	printf("\n Enter the string \n");
	gets(string);

	out = PS_RunLenSingleChar(string);
	printf("\n  string = %s \n", string);
	printf("\n  final = %s \n", out);
	if (out != NULL) {
		free(out);
	}
	return 0;
}

