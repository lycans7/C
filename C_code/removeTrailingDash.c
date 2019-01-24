/*
 * removeTrailingDash.c
 *
 *  Created on: 24-Jan-2019
 *      Author: Parth shah
 */

#include <stdio.h>

void removeTrailingDash(char *ptr);

int main() {
	char val[] = "H-h-pa-----hello--df-f-f-d------------";
	char va[] = "Parth--";

	removeTrailingDash(va);
	printf(" %s \n", va);

	return 0;
}

void removeTrailingDash(char *ptr) {
	if (ptr == NULL) {
		printf(" Invalid string \n");
		return;
	}
	char* buf = NULL;
	while (*ptr != '\0') {
		if (*ptr == '-') {
			buf = ptr;
			while (*buf == '-') {
				buf = buf + 1;
			}
			if (*buf == '\0') {
				buf = buf - 1;
				if (*buf == '-') {
					*ptr = '\0';
					return;
				}
			}
		}
		ptr += 1;
	}
}

