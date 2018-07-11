/*
 * Header.h
 *
 *  Created on: 05-Jul-2018
 *      Author: Parth shah
 */

#ifndef INCLUDE_HEADER_H_
#define INCLUDE_HEADER_H_

#ifdef __cplusplus
extern "C"{
#endif

namespace stringCode {

/**********************************************
 *************String string function***********
 **********************************************/

char* PS_strstr(char* str, char* fnd);

/**********************************************
 *************atoi function********************
 **********************************************/

int PS_atoi(char* str);

/**********************************************
 *************String compare*******************
 **********************************************/

int PS_strcmp(char* firstString, char* secondString);

/**********************************************
 *************String length********************
 **********************************************/

int PS_strlen(char* str);

/**********************************************
 *************String concatenation function****
 **********************************************/

char* PS_strcat(char* str1, char* str2);

/**********************************************
 *************String to integer ****
 **********************************************/

int PS_charToInt(char* str, int count)
}

namespace str=stringCode; //re-name of namespace stringCode to parth

#ifdef __cplusplus
}
#endif
#endif /* INCLUDE_HEADER_H_ */
