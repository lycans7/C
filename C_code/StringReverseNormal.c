/*
 * StringReverseNormal.c
 *
 *  Created on: 29-Jun-2018
 *      Author: Parth
 */

#include <stdio.h>
#include <string.h>

void swap(char *x, char*y) {
	char temp;
	temp = *x;
	*x = *y;
	*y = temp;
}
int main() {
	char p[30], temp[30];
	int len;
	printf("\n Enter the string \n");
	gets(p);
	len = strlen(p) / 2;

	for (int i = 0, j = strlen(p) - 1; i < len && j > len - 1; i++, j--) {
		swap(&p[i], &p[j]);
	}

	printf("\n Enter the string = %s \n", p);

}

