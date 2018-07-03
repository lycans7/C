/*
 * Matrix_multiplication.c
 *
 *  Created on: 29-Jun-2018
 *      Author: Parth
 */

#include <stdio.h>

int main() {
	int mat1[2][2] = { 1, 2, 3, 4 };
	int mat2[2][2] = { 5, 6, 7, 8 };
	int mat3[2][2] = { 0 };
	int i, j, k;
	for (i = 0; i < 2; i++) {
		for (j = 0; j < 2; j++) {
			for (k = 0; k < 2; k++) {

				mat3[i][j] += mat1[i][k] * mat2[k][j];

			}
		}
	}
	printf("\n");
	for (i = 0; i < 2; i++) {
		for (j = 0; j < 2; j++) {
			printf("mat3 [%d][%d] = [%d]\n",i,j,mat3[i][j]);
		}
	}
	return 0;
}

