/*
 * FTP_Functions.h
 *
 *  Created on: 10-Aug-2015
 *      Author: tejas
 */

#ifndef FTP_FUNCTIONS_H_
#define FTP_FUNCTIONS_H_


#include 	<stdio.h>
#include 	<unistd.h>
#include 	<string.h>
#include 	<stdlib.h>
#include 	<dirent.h>
#include	<sys/stat.h>
#include	<netinet/in.h>
#include	<sys/socket.h>
#include 	<sys/msg.h>
#include	<time.h>
#include	<sys/time.h>
#include	<sys/types.h>
#include	<errno.h>
#include	"Dir.h"


typedef struct sockaddr_in 	Socket_t;											/*	Structure is renamed for shorter name in program*/
typedef struct timeval		Time_Out_t;											/*	Structure is renamed for shorter name in program*/

struct 	Message_Queue															/*	Message queue structure*/
{
	char		chNum_Connection[100];
	long int	liMsg_Type;
}Parent_Child_t;																/*	Object of message queue structure*/


void 	Create_List_Of_Files(void);												/*	Creates a file list*/
void 	Get_User_Name(void);													/*	Get the user name*/
void 	Connect_Socket_Server(void);											/*	Connect to the socket*/


#endif /* FTP_FUNCTIONS_H_ */
