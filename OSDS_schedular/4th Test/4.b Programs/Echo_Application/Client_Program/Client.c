/*
 * Client.c
 *
 *  Created on: 04-Aug-2015
 *      Author: tejas
 */


#include	<stdio.h>
#include	<unistd.h>
#include	<string.h>
#include	<stdlib.h>
#include	<arpa/inet.h>
#include	<sys/socket.h>
#include	<time.h>

#define 	SERVER 		"127.0.0.1"												/*	Server is IP address*/
#define 	BUFLEN 		512  													/*	Max length of buffer*/
#define 	PORT 		8888   													/*	The port on which to send data*/


typedef struct sockaddr_in Socket_t;


int main(void)
{
	Socket_t	Client_Socket;													/*	Client socket object of structure sockaddr_in*/
	int 		iSock_Fd;														/*	File descriptor for socket*/
	int			iSock_Len = sizeof(Client_Socket);								/*	Length of socket*/
	char 		chBuffer[BUFLEN];												/*	Buffer handling messages*/
	time_t		Start_Time,End_Time,Gap_Time;									/*	Time_t objects for calculating time taken by the server*/
	double		dTotal;															/*	Difference of time is accumulated here*/

	iSock_Fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);						/*	Creating a socket*/

    if (iSock_Fd == -1)
    {
    	fprintf(stderr,"Error creating socket in client\n");					/*	Error message*/
    }

    memset((char *) &Client_Socket, 0, sizeof(Client_Socket));					/*	Cleaning the garbage values in socket object*/
    Client_Socket.sin_family = AF_INET;											/*	Clients information related to connecting host*/
    Client_Socket.sin_port = htons(PORT);


    if(inet_aton(SERVER , &Client_Socket.sin_addr) == 0)						/*	Converts the IP address of host in binary and stores in object for communication*/
    {
    	fprintf(stderr, "inet_aton() failed\n");								/*	Error message*/
    	exit(EXIT_FAILURE);
    }

    while(1)
    {
    	printf("Enter message : ");
    	fgets(chBuffer,sizeof(chBuffer),stdin);									/*	Get the data from the stdin*/

    	Start_Time = clock();													/*	Start the clock before sending the data*/

    	if(sendto(iSock_Fd,chBuffer,											/*	Send data to the server*/
        		strlen(chBuffer),0,
        		(struct sockaddr *)&Client_Socket,
        		iSock_Len)==-1)
    	{
    		fprintf(stderr,"Error in sending data to server\n");				/*	Error message*/
        }

        End_Time = clock();														/*	Record the time taken by the function*/

        dTotal = (double)(End_Time - Start_Time)/CLOCKS_PER_SEC;				/*	Convert in Seconds*/

        Gap_Time = clock();														/*	Start the timer*/

        memset(chBuffer,'\0', BUFLEN);											/*	Clean the buffer for receiving data from server*/

        Start_Time = clock();													/*	Start the timer for another function*/

        dTotal += (double)(Start_Time - Gap_Time)/CLOCKS_PER_SEC;				/*	Accumulate the time taken by client for reaching to recvfrom()*/

        if (recvfrom(iSock_Fd,chBuffer,											/*	Receive data from server*/
        		BUFLEN,0,
        		(struct sockaddr *) &Client_Socket,
        		(socklen_t *) &iSock_Len) == -1)
        {
            fprintf(stderr,"Error in sending receiving data\n");				/*	Error message*/
        }

        End_Time = clock();														/*	Record the time taken by recvfrom()*/
        dTotal += (double)(End_Time - Start_Time)/CLOCKS_PER_SEC;				/*	Accumulate total time i.e. processing time*/

        printf("Server response: %s"											/*	Prints the server's echoed message*/
        		"Processing time: %0.0fseconds\n",chBuffer,dTotal);

        if(strncmp(chBuffer,"quit",4) == 0)										/*	If echoed message if quit then break the loop*/
        	break;
    }

    if(close(iSock_Fd) == -1)													/*	Close the created socket*/
    	perror("Error in closing the socket.\n");								/*	Error message*/

    printf("Terminating The Client...\n");
    return 0;
}
