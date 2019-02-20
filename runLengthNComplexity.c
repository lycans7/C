 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void str_count(int count[],char arr[]);

int main(){
	char arr[] = "abbcaadccbd";
	int i = 0,el_count[255] = {0};
	for(i = 0; i < strlen(arr) ; i++){
		el_count[arr[i]]++;  // el_count[65]++ ( 'a' ascii value) means 65 location value increment by 1
	}
	
	memset(arr,0,strlen(arr));
	
	str_count(el_count , arr);
	
	printf("%s \n",arr);
	return 0;
}

void str_count(int count[],char arr[]) {

	static int i;

	if(count[i]!=0 ){
		char* loc = (char*) malloc(sizeof(char) * 2);
		sprintf(loc,"%c%d",i++,count[i]);
		strcat(arr,loc);
		free(loc);
	
	}else{
		i++;
	}

	if(i < 255)
		str_count(count,arr);
}
