/*
 * generic_string_reverse.c
 *
 *  Created on: 20-Nov-2018
 *      Author: Parth shah
 */

#include <stdio.h>
#include <string.h>

void rev(char *fir, char* last) {
	char* temp;
	*temp = *fir;
	*fir = *last;
	*last = *temp;
}

int main() {
	int size, len, i, j;
	printf("Enter the size of array \n");
	scanf("%d", &size);
	printf("\n Enter the string \n");
	char arr[size];
//	scanf("%s", &arr);
	gets(arr);
	len = strlen(arr) / 2;
	for (i = 0, j = strlen(arr) - 1; i < len && j > len - 1; i++, j--) {
		rev(&arr[i], &arr[j]);
	}
	printf("\n string  = %s \n", arr);
	return 0;
}

