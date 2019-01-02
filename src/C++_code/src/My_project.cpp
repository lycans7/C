/*
 * My_project.cpp
 *
 *  Created on: 05-Jul-2018
 *      Author: Parth shah
 */

#include <stdio.h>
#include <stdlib.h>
#include "../Include/Header.h"

using namespace str;

int main(){
	char string[50], find[50], *p;

	printf("\n Enter the string \n\t");
	gets(string);
	printf("\n Enter a word to find \n\t");
	gets(find);

	p = PS_strstr(string, find);

	printf("\n return from strstr = %s \n\t string = %s \n\t find = %s \n index = %d \n", p,
			string, find,p - string);


	return 0;
}

