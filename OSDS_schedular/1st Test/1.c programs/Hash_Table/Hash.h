/*
 * Hash.h
 *
 *  Created on: 17-Jul-2015
 *      Author: tejas
 */

#ifndef HASH_H_
#define HASH_H_

#define 	MAX_LENGTH_OF_FILE		70

typedef struct Linked_Hash											/*Linked list based entries of the element with collision*/
{
    char 				*string;
    int					iLine;										/*conter array for the line number*/
    char				*chFile_Name;
    struct Linked_Hash 	*next;
} List_t,*List_p;



typedef struct Hash_Table_Struct_Files
{
    int 				iSize;       								/* the size of the table */
    List_p 				*table; 									/* the table elements */
} Hash_Table_t, *Hash_Table_p;



typedef Hash_Table_t Hash_Table_C_t, *Hash_Table_C_p;



Hash_Table_p 	Create_Hash_Table(int);								/*Creates the hash table with specified size*/
unsigned int 	Hash(Hash_Table_p, char *);							/*Hashes the string character by character*/
List_p 			Lookup_String(Hash_Table_p, char *);				/*Looking up for the string to compare and get the list pointer*/
int 			Add_File(Hash_Table_p, char *);						/*Add a file to the hash table's particular linked list*/
int 			Add_String(Hash_Table_C_p,char*, char *, int);		/*add a line to the hash table's particular linked list*/
void 			Free_Table(Hash_Table_p);							/*Free the hash table once done with it*/
void 			Print_Hash_Table(Hash_Table_p);						/*Prints the hashed table*/
void 			Print_File_Hash_Table(Hash_Table_C_p, char*);		/*Prints the hashed file data*/

#endif /* HASH_H_ */
