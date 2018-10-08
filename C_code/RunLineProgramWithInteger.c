/*
 * RunLineProgramWithInteger.c
 *
 *  Created on: 09-Jul-2018
 *      Author: Parth Shah.
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * find next char and increase count and save in new array.
 * if not reset the count and save only char.
 * Que :- aaabbbccc
 * out :- a3b3c3
 *
 * */

/*int PS_atoi(char* buff) {

 if (buff == NULL) {
 return 0;
 }

 int val = 0;

 while (buff != '\0' && *buff >= '0' && *buff <= '9') {
 val = val * 10 + *buff++ - '0';
 }
 return val;
 }*/

char* PS_runLength(char* str, char size) {
	if (str == NULL) {
		return NULL;
	}
	char *arr = str;
	arr++;
	int flagchar = 0, flagint = 0, countInt = 1;
	char *ptr = (char *) malloc(size + 1);
	while (*str != '\0') {
		printf("\nLine %d \t *str = %c\n", __LINE__, *str);
		if (str != '\0' && *str >= '0' && *str <= '9') {
			printf("\nLine %d \t *str = %c *arr = %c\n", __LINE__, *str, *arr);
			if (*str == *arr) {
				flagint = 1;
				countInt++;
				*ptr = *str;
				printf("\nLine %d \t *str = %c\n", __LINE__, *str);
			} else if (str != '\0' && *str != *arr && flagint == 1) {
				if (countInt != 1) {
					ptr++;
					*ptr = countInt;
					countInt = 1;
				} else {
					*ptr++ = *str;
					countInt = 1;
				}
				printf("\nLine %d \t *str = %c\n", __LINE__, *str);
				flagint = 0;
			} else if (*arr == '\0' && *str == *arr && flagint == 1) {
				if (countInt != 1) {
					ptr++;
					*ptr = countInt;
					countInt = 1;
					printf("\nLine %d \t *str = %c\n", __LINE__, *str);
				} else {
					*ptr++ = *str;
					countInt = 1;
				}
				printf("\nLine %d \t *str = %c\n", __LINE__, *str);
				flagint = 0;
			} else {
				*ptr++ = *str;
			}
		} else if (str != '\0') {
			printf("\nLine %d \n", __LINE__, *str);
		}
		str++;
		arr++;
	}

	return ptr;
}

int main() {
	char string[50] = { 0 }, *out;
	int size = 0;
	printf("\n Enter the string \n");
	gets(string);
	while (*(string + ++size))
		; //string length

	printf("\n Size = %d \n", size);
	out = PS_runLength(string, size);
	printf("\n Enter string = %s \n", string);
	printf("\n Final string output = %s\n", out);
	free(out);
}

