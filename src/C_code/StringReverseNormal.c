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
	char p[30];
	int len;
	printf("\n Enter the string \n");
	gets(p);
	len = strlen(p) / 2;

	for (int i = 0, j = strlen(p) - 1; i < len && j > len - 1; i++, j--) {
		swap(&p[i], &p[j]);
	}

	printf("\n Enter the string = %s \n", p);
return 0;
}
	/* Recursion Working */

/*void reverse(char *p, int first, int last);
int main() {
	char p[30] = "Parthg";
	int len = strlen(p) - 1;
	printf(" len  =%d\n", len);
	reverse(p, 0, len);
	printf("%s\n", p);
	return 0;
}

void reverse(char* p, int first, int last) {
	printf(" first = %d  last = %d \n", first, last);
	if (first >= last) {
		return;
	}
	char temp;
	temp = p[first];
	p[first] = p[last];
	p[last] = temp;
	printf(" p[first] = %c  p[last] = %c \n", p[first], p[last]);

	reverse(p, first + 1, last - 1);

}

*/
