/*
 * main.c
 *
 *  Created on: 16-Jul-2015
 *      Author: tejas
 */

#include 	<stdio.h>
#include 	<unistd.h>
#include 	<time.h>
#include 	<stdlib.h>
#include	"Task_Scheduler_Header.h"

int iTask_Check;

int main()
{
	while(1)
	{
		iTask_Check = Task_Schedular();

		if(iTask_Check == 4)
			break;
		else if(iTask_Check == 2)
			Do_As_Per_Task_Priority();
	}
	return 0;
}
