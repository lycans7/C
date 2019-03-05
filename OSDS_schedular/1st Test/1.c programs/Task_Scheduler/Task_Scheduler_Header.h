/*
 * Task_Scheduler_Header.h
 *
 *  Created on: 16-Jul-2015
 *      Author: tejas
 */

#ifndef TASK_SCHEDULER_HEADER_H_
#define TASK_SCHEDULER_HEADER_H_

typedef struct PRQ
{
 int iElement;
 int iPriority;
 int iReturn_Status;
 int iMulti;
 time_t Mytime_t;
}PriorityQ;

int 		Task_Schedular(void);
void 		PQ_Insert(int, int);
PriorityQ 	PQ_Delete(void);
PriorityQ 	Check_For_Same_Priority(PriorityQ,PriorityQ);
int 		Q_Full(void);
int 		Q_Empty(void);
void 		Display(void);
void 		Do_As_Per_Task_Priority(void);




#endif /* TASK_SCHEDULER_HEADER_H_ */
