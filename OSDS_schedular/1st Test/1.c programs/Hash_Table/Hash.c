/*
 * Hash.c
 *
 *  Created on: 17-Jul-2015
 *      Author: tejas
 */

#include 	<stdio.h>
#include	<unistd.h>
#include 	<dirent.h>
#include 	<string.h>
#include 	<sys/stat.h>
#include 	<stdlib.h>
#include	"Dir.h"
#include	"Hash.h"


extern int iStore;
extern char chFiles[10][MAX_LENGTH_OF_FILE];



/*
 * Function name	:	Create_Hash_Table
 *
 * Description		:	use this function to Create hash table this function handles the memory assignment
 * 						functions.
 *
 * Parameters		:	int iSize -> size of the hash table
 *
 * Returns			:	pointer to the newly created hash table
 */
Hash_Table_p Create_Hash_Table(int iSize)
{
	int iLoop;
	Hash_Table_p New_Table;

    if (iSize<1)
		return NULL; 																	/* invalid size for table */

    if ((New_Table = (Hash_Table_p) malloc(sizeof(Hash_Table_t))) == NULL)				/* Attempt to allocate memory for the table structure */
        return NULL;

    if ((New_Table->table = malloc(sizeof(List_p) * iSize)) == NULL)					/* Attempt to allocate memory for the table itself */
        return NULL;

    for(iLoop=0; iLoop<iSize; iLoop++)													/* Initialize the elements of the table */
    	New_Table->table[iLoop] = NULL;

    New_Table->iSize = iSize;															/* Set the table's size */

    return New_Table;
}


/*
 * Function name	:	Hash
 *
 * Description		:	use this function to Hash the string name e.g.file or string from the file
 *
 * Parameters		:	Hash_Table_p Hash_Table -> pointer to the hash table structure
 * 						char *str -> string to lookup.
 *
 * Returns			:	hashed value
 */
unsigned int Hash(Hash_Table_p Hash_Table, char *str)
{
    unsigned int uiHashval;

    uiHashval = 0;																		/* we start our hash out at 0 */

    for(; *str != '\0'; str++)
    	uiHashval = *str + (uiHashval << 5) - uiHashval;

    return uiHashval % Hash_Table->iSize;
}


/*
 * Function name	:	Lookup_String
 *
 * Description		:	use this function to Lookup the string in the file if same string
 * 						exsist then return will be none otherwise pointer to the containing
 * 						folder
 *
 * Parameters		:	Hash_Table_p Hash_Table -> pointer to the hash table structure
 * 						char *str -> string to lookup.
 *
 * Returns			:	pointer to the node of the linked list in the hash structure if
 * 						comparision is success, else NULL
 */
List_p Lookup_String(Hash_Table_p Hash_Table, char *str)
{
	List_p list;

    unsigned int uiHashval = Hash(Hash_Table, str);

    for(list = Hash_Table->table[uiHashval]; list != NULL; list = list->next)
        if (strcmp(str, list->string) == 0)
        	return list;

    return NULL;
}


/*
 * Function name	:	Add_File
 *
 * Description		:	use this function to add file name to the hash structure table
 *
 * Parameters		:	Hash_Table_p Hash_Table -> pointer to the hash table structure
 * 						char *str -> file name.
 *
 * Returns			:	None
 */
int Add_File(Hash_Table_p Hash_Table, char *str)
{
    List_p New_List;
    List_p Current_List;

    unsigned int uiHashval = Hash(Hash_Table, str);

    if ((New_List = malloc(sizeof(List_t))) == NULL)									/* Attempt to allocate memory for list */
    	return 1;

    Current_List = Lookup_String(Hash_Table, str);

    if (Current_List != NULL)															/*item already exist do not enter*/
    	return 2;

    New_List->string = strdup(str);
    New_List->next = Hash_Table->table[uiHashval];
    Hash_Table->table[uiHashval] = New_List;

    return 0;
}


/*
 * Function name	:	Free_Table
 *
 * Description		:	use this function to free the hash structure table
 *
 * Parameters		:	Hash_Table_p Hash_Table -> pointer to the hash table structure
 *
 * Returns			:	None
 */
void Free_Table(Hash_Table_p Hash_Table)
{
    int iLoop;
    List_p list, temp;

    if (Hash_Table==NULL)
    	return;

    for(iLoop=0; iLoop<Hash_Table->iSize; iLoop++)
    {
        list = Hash_Table->table[iLoop];

        while(list!=NULL)
        {
            temp = list;
            list = list->next;
            free(temp->string);
            free(temp);
        }
    }

    free(Hash_Table->table);
    free(Hash_Table);
}


/*
 * Function name	:	Print_Hash_Table
 *
 * Description		:	use this function to print the directories in the hashed structure.
 *
 * Parameters		:	Hash_Table_p Hash_Table -> pointer to the hash table structure
 *
 * Returns			:	None
 */
void Print_Hash_Table(Hash_Table_p Hash_Table)
{
	int iLocal;
	int iSearch;

	printf("Filenames hashed are,\n");
	for(iLocal = 0; iLocal < iStore;iLocal++)
	{
		iSearch = Hash(Hash_Table,chFiles[iLocal]);
		printf("%s at %d in Hash Table\n",Hash_Table->table[iSearch]->string,iSearch);
	}
}


/*
 * Function name	:	Print_File_Hash_Table
 *
 * Description		:	use this function to print the found strings in the hashed structure.
 *
 * Parameters		:	Hash_Table_C_p Hash_Table -> pointer to the hash table structure
 * 						char * chstr ->  particular string from the file
 *
 * Returns			:	None
 */
void Print_File_Hash_Table(Hash_Table_C_p Hash_Table,char *str)
{
	int iFound = 0;
	unsigned int uiHashval = Hash(Hash_Table,str);

	List_p Local_Search = Hash_Table->table[uiHashval];

	while(Local_Search->next != NULL)
	{
		if(strncmp(str,Local_Search->string,strlen(str)) == 0)
		{
			printf("%s is "
					"found in file %s at"
					" line number %d\n"
					,Local_Search->string
					,Local_Search->chFile_Name
					,Local_Search->iLine+1);
			Local_Search = Local_Search->next;
			iFound = 1;
		}
		else
			Local_Search = Local_Search->next;
	}
	if(iFound == 0)
		printf("String is not in the list please try modifying your search\n");
}


/*
 * Function name	:	Add_String
 *
 * Description		:	use this function to Hash the strings of the file.
 *
 * Parameters		:	Hash_Table_C_p Hash_Table -> pointer to the hash table structure
 * 						char* chFile_Name -> file name with full path from which we have
 * 											 hash the strings.
 * 						char * chstr ->  particular string from the file
 * 						int iLine -> Line number of the string.
 *
 * Returns			:	1 if node of the linked list can not be created
 * 						0 if successful in operation
 */
int Add_String(Hash_Table_C_p Hash_Table,char* chFile_Name, char *chStr, int iLine)
{
    List_p New_List;

    unsigned int uiHashval = Hash(Hash_Table, chStr);

    if ((New_List = malloc(sizeof(List_t))) == NULL)									/* Attempt to allocate memory for list */
    	return 1;

    New_List->string = strdup(chStr);
    New_List->chFile_Name = strdup(chFile_Name);
    New_List->iLine = iLine;
    New_List->next = Hash_Table->table[uiHashval];
    Hash_Table->table[uiHashval] = New_List;

    return 0;
}


//home/tejas/Downloads
///*******************************************************************************
// * Copyright (c) <year>, <company name>
//#include	<stdio.h>			/*	Observe tab in between include and '<'    */
// * History
