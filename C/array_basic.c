#include<stdio.h>

int main(){

char q[3] = {'a','e','h'};


printf("\n%c\n",q[0]);
printf("\n%c\n",(*q)++);
printf("\n%p\n",q + 1);


return 0;
}
