/*
 * swap_word_nibbles.c
 *
 *  Created on: 10-Sep-2018
 *      Author: Parth shah
 */

#include <stdio.h>

void main() {
	unsigned int buf, val;
	printf("\n Enter hex number to swap word \n \t");
	scanf("%X", &val);
	buf = (val >> 8 & 0x00ff) | (val << 8 & 0xff00);
	printf("\n after swap %04X \n", buf);

}
