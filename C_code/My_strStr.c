/*
 * My_strStr.c
 *
 *  Created on: 05-Jul-2018
 *      Author: Parth shah
 */

#include <stdio.h>
#include <stdlib.h>


char* PS_strstr(char* str, char* fnd) {
	char* val = NULL, *buff = fnd, flag = 0;
//	int i = 0, count = 0;  //if you want to check the position un comment it all

	if (*str == '\0' && *fnd == '\0') {
		return NULL;
	}

	while (*str != '\0' && *fnd != '\0') {

		if (*str == *fnd) {
			if (flag == 0) {
				val = str;
				flag = 1;
			}
		} else if (*str != *fnd && flag == 1) {
			val = NULL;
			flag = 0;
			fnd = buff;
//			i += count;
//			count = 0;
		}
		if (flag == 1) {
			fnd++;
//			count++;
		}
//		if (flag != 1) {
//			i++;
//		}
		str++;

	}

//	printf("\n index = %d \n\t", i);
	return val;
}

int main() {
	char string[50], find[50], *p;

	printf("\n Enter the string \n\t");
	gets(string);
	printf("\n Enter a word to find \n\t");
	gets(find);

	p = PS_strstr(string, find);

	printf("\n return from strstr = %s \n\t string = %s \n\t find = %s \n index = %d \n", p,
			string, find,p - string);

	return 0;
}

