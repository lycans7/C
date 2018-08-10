/*
 * arrayOfPointersCharacters.c
 *
 *  Created on: 10-Aug-2018
 *      Author: Parth shah
 */

#include <stdio.h>

int main() {
	char arr[][15] = { "Hello", "Eximius", "Team" };
	int i, j;
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 7; j++)
			printf("\n %s %s %c \n", (char *) (arr + i), (char *) arr + i,
					arr[i][j]);
	}
	printf(
			"\n ------------------------------------------------------------- \n");
	char *arr1[] = { "Hey", "How", "are", "you" };
	for (i = 0; i < 4; i++)
		printf("\n %c \n", *(*arr1 + i));
	printf(
				"\n ------------------------------------------------------------- \n");
	for (i = 0; i < 4; i++)
		printf("\n %s \n", *arr1 + i);
	printf(
				"\n ------------------------------------------------------------- \n");
	for (i = 0; i < 4; i++)
		printf("\n %s \n", *(arr1 + i));
	printf(
				"\n ------------------------------------------------------------- \n");
	for (i = 0; i < 4; i++)
			printf("\n arr1[%d] = [%s] \n",i, arr1[i]);
	printf(
				"\n ------------------------------------------------------------- \n");
	char* p = "Hello";
	printf("\n %p %s %c\n",p,p,*p);
	p = "Parth";
	printf("\n %p %s %c\n",p,p,*p);
	return 0;
}

