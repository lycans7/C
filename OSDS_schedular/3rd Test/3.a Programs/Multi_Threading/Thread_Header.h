/*
 * Thread_Header.h
 *
 *  Created on: 24-Jul-2015
 *      Author: tejas
 */

#ifndef THREAD_HEADER_H_
#define THREAD_HEADER_H_



typedef struct Thread_Arguments
{
	int iA[3][3];
	int iB[3][3];
}Matrix_t, *Matrix_p;


void 		Print_Matrix(Matrix_t , int);			/*	Prints the user input in matrix form*/
Matrix_t 	Get_Matrix(Matrix_t, int);				/*	Ask the user for Matrix*/
Matrix_t 	Get_Two_Matrix(void);						/*	Ask the user to enter Matrix*/
void 		Print_Result_Matrix(void);					/*	Prints the final result of multiplication*/

void 		Create_Thread(int);							/*	Creates multiple threads*/
void 		Join_Thread(void);							/*	Joins multiple threads*/

void 		*Matrix_Multiplication_C11(void *);			/*	Thread function for thread C11*/
void 		*Matrix_Multiplication_C12(void *);			/*	Thread function for thread C12*/
void 		*Matrix_Multiplication_C13(void *);			/*	Thread function for thread C13*/
void 		*Matrix_Multiplication_C21(void *);			/*	Thread function for thread C21*/
void 		*Matrix_Multiplication_C22(void *);			/*	Thread function for thread C22*/
void 		*Matrix_Multiplication_C23(void *);			/*	Thread function for thread C23*/
void 		*Matrix_Multiplication_C31(void *);			/*	Thread function for thread C31*/
void 		*Matrix_Multiplication_C32(void *);			/*	Thread function for thread C32*/
void 		*Matrix_Multiplication_C33(void *);			/*	Thread function for thread C33*/



#endif /* THREAD_HEADER_H_ */
