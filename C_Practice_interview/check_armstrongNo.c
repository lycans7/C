/*
 * check_armstrongNo.c
 *
 *  Created on: 12-Sep-2018
 *      Author: Parth shah
 */

#include <stdio.h>


int multi(int num, int itr) {
	int buff = 1, i = 0;
	for (i; i < itr; i++)
		buff = buff * num;
	return buff;
}
void main() {

	int val, count = 0, temp_rem = 0, buff = 0, cpy_val;
	printf("\n Enter the number to check Armstrong \n\t");
	scanf("%d", &val);
	temp_rem = val;
	cpy_val = val;
	while (temp_rem > 0) {
		count++;
		temp_rem = temp_rem / 10;
	}
	temp_rem = 0;
	while (val > 0) {
		temp_rem = val % 10;
		buff = buff + multi(temp_rem, count);
		val = val / 10;
	}

	if (buff == cpy_val)
		printf("\n Number is Armstrong = %d \n", cpy_val);
	else
		printf("\n Number is Not Armstrong = %d \n", cpy_val);

}

