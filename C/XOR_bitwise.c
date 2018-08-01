/*
 * XOR_bitwise.c
 *
 *  Created on: 01-Aug-2018
 *      Author: Parth shah
 */

// Function to return the only odd occurring element
int findOdd(int arr[], int n) {
   int res = 0, i;
   for (i = 0; i < n; i++){
	   printf("\n res %d %d %d \n",res,i,arr[i]);
     res ^= arr[i];
     printf("\n res %d %d \n",res,i);
   }
   return res;
}

int main(void) {
   int arr[] = {12, 12, 8,8,2,14, 90, 14, 14, 14,24,24,90};
   int n = sizeof(arr)/sizef(arr[0]);
   printf ("The odd occurring element is %d ", findOdd(arr, n));
   return 0;
}



