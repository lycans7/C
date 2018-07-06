/*
 * PS_lib.c
 *
 *  Created on: 05-Jul-2018
 *      Author: Parth Shah
 */

#include <stdio.h>
#include <stdlib.h>
/**********************************************
 *************String string function***********
 **********************************************/

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

/**********************************************
 *************atoi function********************
 **********************************************/

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

/**********************************************
 *************String compare*******************
 **********************************************/

int PS_strcmp(char* firstString, char* secondString) {
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

/**********************************************
 *************String length********************
 **********************************************/

int PS_strlen(char* str) {
	int count = 0;
	while (*str++ != '\0') {
		count++;
	}
	return count;
}


/**********************************************
 *************String concatenation function****
 **********************************************/

char* PS_strcat(char* str1, char* str2) {
	int length = PS_strlen(str1) + PS_strlen(str2);
	char* buff = NULL;

	if (PS_strlen(str1) < length) {
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

