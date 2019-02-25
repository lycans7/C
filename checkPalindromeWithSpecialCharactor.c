/*
 * checkPalindromeWithSpecialCharactor.c
 *
 *  Created on: 22-Feb-2019
 *      Author: Parth shah
 */

#include <stdio.h>
#include <string.h>

int CheckPalindrome(char arr[], int size);

int main() {
	char arr[] = "madam o m;a;;dam";
	int val = 0, size = strlen(arr);

	val = CheckPalindrome(arr, size);

	if (val == 0) {
		printf(" string is not palindrome \n");
	} else {
		printf(" String is palindrome \n");
	}
	return 0;
}

int CheckPalindrome(char arr[], int size) {

	int start = 0, last = size - 1;
	while (start < last) {
		switch (arr[start]) {
		case 'a' ... 'z':
		case 'A' ... 'Z':
		case '0' ... '9':
		case ' ':
			break;

		default:
			start++;
			continue;
		}

		switch (arr[last]) {
		case 'a' ... 'z':
		case 'A' ... 'Z':
		case '0' ... '9':
		case ' ':
			break;

		default:
			last--;
			continue;
		}

		if (arr[start] != arr[last]) {
			return 0;
		}
		start++;
		last--;
	}
	return 1;
}

