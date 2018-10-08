/*
 * spiral_print.c
 *
 *  Created on: 20-Sep-2018
 *      Author: Parth shah
 */

#include <stdio.h>
int row, col;
void print_spiral(int arr[row][col], int row_end, int col_end);

int main() {
	int i = 0, j = 0;

	printf("\n Enter the dimension Matrix NxM \n");
	scanf("%d%d", &row, &col);

	int arr[row][col];

	if (row == 0 || col == 0) {
		printf("\n Invalid input Re-entered Dimension \n");
		return 1;
	}

	printf("\n Enter the value in Matrix \n");

	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {
			scanf("%d", &arr[i][j]);
		}
	}

	printf("\n You Enter the value of Matrix \n");

	for (i = 0; i < row; i++) {
		printf(" \n ");
		for (j = 0; j < col; j++) {
			printf(" %d ", arr[i][j]);
		}
	}

	print_spiral(arr, row, col);

	printf(" \n ");
	return 0;
}

void print_spiral(int arr[row][col], int row_end, int col_end) {
	int itr, row_start = 0, col_start = 0;
	printf("\n Print spiral Matrix \n");
	while (row_start < row_end && col_start < col_end) {

		for (itr = col_start; itr < col_end; itr++) {
			printf(" %d ", arr[row_start][itr]);
		}
		row_start++;

		for (itr = row_start; itr < row_end; itr++) {
			printf(" %d ", arr[itr][col_end - 1]);
		}
		col_end--;

		if (row_start < row_end) {
			for (itr = col_end - 1; itr >= col_start; itr--) {
				printf(" %d ", arr[row_end - 1][itr]);
			}
			row_end--;
		}

		if (col_start < col_end) {
			for (itr = row_end - 1; itr >= row_start; itr--) {
				printf(" %d ", arr[itr][col_start]);
			}
			col_start++;
		}
	}
}

