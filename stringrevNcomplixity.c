#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){

	char arr[50] = "hello world abcd tejas";
	int i, flag = 1;
	char* str = malloc (sizeof(char) * strlen(arr));
	i = strlen(arr);
	char* temp;
	while( i >= 0){
		if(arr[i - 1] == ' '){
			temp = &arr[i - 1];
			if (flag) {
				strcpy(str,temp + 1);
				flag = 0;
			} else
				strcat(str,temp + 1);

			strcat(str," ");
			arr[ i - 1] = '\0';
		}
		if( i == 0){
			temp = &arr[i];
			strcat(str,temp);
			strcpy(arr,str);
			free(str);
		}
		i--;
	}

	printf("%s\n",arr);
	return 0;
}
