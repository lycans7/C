/*****************************************************************************************
*                                     String Reverse                                     *
*                                                                                        *
*                                KartiK : kartikdb@cdac.in                               *
*                                                                                        *
******************************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void push(char);
char pop(void);

char str[20],stacK[20];
int top;

void main()
{
	int ch,i;

	printf("Enter the string you want to reverse :: ");
	gets(str);
//	puts(str);

	for(i=0;i<strlen(str);i++)
		push(str[i]);

	for(i=0;i<strlen(str);i++)
		str[i] = pop();

	printf("reverse string is :: ");
	puts(str);
}

void push(char letter)
{
	stacK[top++] = letter;
}
char pop(void)
{
	return(stacK[--top]);
}
