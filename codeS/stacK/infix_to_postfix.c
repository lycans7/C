/*****************************************************************************************
*                                    Infix to Postfix                                    *
*                                                                                        *
*                               KartiK : kartikdb@cdac.in                                *
*                                                                                        *
******************************************************************************************/

#include<stdio.h>
#include<string.h>
#include<math.h>

void push(char elem);
char pop(void);
int prio(char elem);
void infix_to_postfix(char []);
void eval_postfix(void);

char stacK[20],postfix[50];
int top = -1;

main() 
{
	char infix[50];
	int k = 0,i;
 	printf("Enter the Infix Expression :: ");	scanf("%s",infix);

	infix_to_postfix(infix);
 	eval_postfix();
}
void infix_to_postfix(char infix[])
{
	int i,k=0;
	char ch,sym;
	
	push('#');
	for(i=0;infix[i];i++)
	{
		ch = infix[i];
  		if (ch == '(')
   			push(ch);
  		else if (isalnum(ch))
   			postfix[k++] = ch;
  		else if (ch == ')')
		{
   			while (stacK[top] != '(')
    			postfix[k++] = pop();
   			sym = pop(); 																	// Remove (
  		}
		else
		{																					// Operator 
   			while (prio(stacK[top]) >= prio(ch))
   			    postfix[k++] = pop();
   			push(ch);
  		}
 	}
	while (stacK[top] != '#') 																// Pop from stack till empty
  		postfix[k++] = pop();
 	postfix[k] = '\0'; 																		
 	printf("Postfix Expression is : %s\n",postfix);
}
void push(char elem) 
{ 
	stacK[++top] = elem;
}
 
char pop(void) 
{
	return (stacK[top--]);
}
 
int prio(char elem) 
{
	switch (elem)
	{
 		case '#':
  			return 0;
 		case '(':
  			return 1;
 		case '+':
 		case '-':
  			return 2;
 		case '*':
 		case '/':
 		case '%':
  			return 3;
  		case '^':
  			return 4;
  	}
}
void eval_postfix(void)
{
	int i,temp,a,b,result;
	for(i=0;i<strlen(postfix);i++)
	{
		if(postfix[i] <= '9' && postfix[i] >= '0')
			push(postfix[i] - '0');
		else
		{
			a = pop();
			b = pop();
			switch(postfix[i])
			{
				case '+':
					temp = b + a;
					break;
				case '-':
					temp = b - a;
					break;
				case '*':
					temp = b * a;
					break;
				case '/'	:
					temp = b / a;
					break;
				case '%':
					temp = b % a;
					break;
				case '^':
					temp = pow(b,a);
					break;
			}
			push(temp);
		}
	}
	printf("Value of the expression is :: %d",pop());
}
