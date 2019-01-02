/*****************************************************************************************
*                                   Validity of Expression                               *
*                                                                                        *
*                                KartiK : kartikdb@cdac.in                               *
*                                                                                        *
******************************************************************************************/



#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void push(char);
char pop(void);
void display(void);

char str[20],stacK[20];
int top;

int main()
{
	int i,f=0;char letter;

		printf("Enter the expression :: ");
		gets(str);
	
		for(i=0;i<strlen(str);i++)
		{	
			if(str[i] == '[' || str[i] == '(' || str[i] == '{')
				push(str[i]);
		
			if(str[i] == ']' || str[i] == ')' || str[i] == '}')
				letter = pop();
				if(letter == '[' && str[i] == ']')
					f = 1;
				if(letter == '{' && str[i] == '}')
					f = 1;
				if(letter == '(' && str[i] == ')')
					f = 1;		
		}	
	
		
	if(f && top == 0)
		printf("Valid Expression\n");
	else
		printf("Invalid expression\n")	;
	

	return 0;
}
void push(char item)
{
	stacK[top++] = item;
}
char pop()
{
	return stacK[--top];
}
void display(void)
{
	int i;
	for(i=top;i>-0;i--)
		printf("%c",stacK[--top]);
	printf("\n");
}
