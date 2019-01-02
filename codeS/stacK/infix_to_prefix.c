/*****************************************************************************************
*                                     Infix to Prefix                                    *
*                                                                                        *
*                                KartiK : kartikdb@cdac.in                               *
*                                                                                        *
******************************************************************************************/


/*
(A+B^C)*D+E^5
step 1 : Reverse the infix expression.
		 	5^E+D*)C^B+A(
Step 2 : Make Every '(' as ')' and every ')' as '(' 
            5^E+D*(C^B+A)
Step 3 : Convert expression to postfix form.
Step 4 : Reverse the expression.
                +*+A^BCD^E5
*/
#include<stdio.h>
#include<string.h>

void infix_to_prefix(void);
void infix_to_postfix(char infix[]);
void push(char elem); 
char pop(void);
int prio(char elem);


char infix[20],postfix[20],prefix[20],stacK[20];
int top = -1;

int main()
{
	printf("Enter the infix expression :: ");
	gets(infix);
	
	infix_to_prefix();
	eval_prefix();
	
	return 0;
}
void infix_to_prefix(void)
{
	char sym;int i;
	strrev(infix);
	printf("Reversed expression is :: ");
	puts(infix);	printf("\n");
	for(i=0;i<infix[i];i++)
	{
		sym = infix[i];
		switch(sym)
		{
			case ')':
				infix[i] = '(';
				break;
			case '(':
				infix[i] = ')';
				break;
		}
	}
	infix_to_postfix(infix);
	strrev(postfix);								// reversing postfix array we will get prefix expression
	printf("Prefix expression is :: ");	
	puts(postfix);
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
 																		//	printf("Postfix Expression is : %s\n",postfix);
}
void eval_prefix(void)
{
	strrev(postfix);
	eval_postfix();
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
