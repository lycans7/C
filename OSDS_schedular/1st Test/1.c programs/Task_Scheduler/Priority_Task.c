#include	<stdio.h>
#include	<unistd.h>
#include 	<time.h>
#include 	<stdlib.h>
#include	"Task_Scheduler_Header.h"

#define SIZE 5        			   						/*Size of Queue */

int iFlushed = 0, iRemaining=-1;      					/*Global declarations */
double dDiff_t;											/*for taking difference between two tasks*/
PriorityQ PQ[SIZE];

/*
 * Function name	:	Task_Schedular
 *
 * Description		:	use this function to insert display or delete a task from the queue.
 *
 * Parameters		:	None
 *
 * Returns			:	int that describe the nature of the further operation
 */
int Task_Schedular(void)
{
	int iOption;
	PriorityQ pMain_Queue;

	printf("1.Insert\n"
		  "2.Delete\n"
		  "3.Display\n"
		  "4.Exit\n");
	printf("Enter your choise: ");
	scanf("%d",&iOption);
	switch(iOption)
	{
	  case 1:
		  printf("\nAdd the element:");
		  scanf("%d",&pMain_Queue.iElement);

		  printf("And its Priority \n\"0\" means highest & \"5\" means lowest:");
		  scanf("%d",&pMain_Queue.iPriority);

		  if(pMain_Queue.iPriority < 0)
			  pMain_Queue.iPriority = 0;
		  else if(pMain_Queue.iPriority > 5)
			  pMain_Queue.iPriority = 5;

		  PQ_Insert(pMain_Queue.iElement,pMain_Queue.iPriority);
		  break;

	  case 2:
		  pMain_Queue=PQ_Delete();
		  if(pMain_Queue.iReturn_Status == 1)
		  {
			  if(pMain_Queue.iMulti != 0)
			  {
				  int iLocal = pMain_Queue.iMulti - 1;
				  while(iLocal > 0)
				  {
					  PQ[iLocal] = PQ[iLocal-1];
					  iLocal--;
				  }
			  }
			  PQ[iFlushed] = PQ[iFlushed-1];
		  }
		  if( pMain_Queue.iElement != -1)
			  printf("\n\nDeleted Element is %d \n",pMain_Queue.iElement);
		  break;

	  case 3:
		  printf("\nStatus of Queue\n");
		  Display();
		  break;

	  case 4:
		  printf("\nTerminating\n");
		  break;

	  default:
		  printf("\nInvalid Option !!! Try Again !! \n");
		  break;
	}
	return iOption;
}


/*
 * Function name	:	PQ_Insert
 *
 * Description		:	use this function to insert task to the queue.
 *
 * Parameters		:	int iElem -> element of the task
 * 						int iPre ->	priority of the task
 *
 * Returns			:	int that describe the nature of the further operation
 */
void PQ_Insert(int iElem, int iPre)
{
	int i;       /* Function for Insert operation */
	time_t Start_Time_t;
	 if( Q_Full())
		 printf("\n\n Overflow!!!!\n\n");
	 else
	 {
		  i=iRemaining;
		  ++iRemaining;
		  while(PQ[i].iPriority >= iPre && i >= 0) /* Find location for new elem */
		  {
			   PQ[i+1]=PQ[i];
			   i--;
		  }
		  PQ[i+1].iElement=iElem;
		  PQ[i+1].iPriority=iPre;
		  PQ[i+1].Mytime_t=time(&Start_Time_t);
	 }
}


/*
 * Function name	:	PQ_Delete
 *
 * Description		:	use this function to delete task from the queue.
 *
 * Parameters		:	None
 *
 * Returns			:	Object of the priority queue structure
 */
PriorityQ PQ_Delete(void)
{
	PriorityQ pTemp_Queue;
	if(Q_Empty())
	{
		printf("\n\nUnderflow!!!!\n\n");
		pTemp_Queue.iElement=-1;
		pTemp_Queue.iPriority=-1;
		return(pTemp_Queue);
	}
	else
	{
		pTemp_Queue = Check_For_Same_Priority(PQ[iFlushed],PQ[iFlushed+1]);
		iFlushed++;
		return(pTemp_Queue);
	}
}


/*
 * Function name	:	Q_Full
 *
 * Description		:	use this function to check if the queue is full or not
 *
 * Parameters		:	None
 *
 * Returns			:	1 if queue is full else 0
 */
int Q_Full(void)
{
	 if(iRemaining==SIZE-1)
		 return 1;
	 return 0;
}


/*
 * Function name	:	Q_Empty
 *
 * Description		:	use this function to check if the queue is empty or not
 *
 * Parameters		:	None
 *
 * Returns			:	1 if queue is full else 0
 */
int Q_Empty(void)
{
	 if(iFlushed > iRemaining)
	 {
		 iFlushed = 0;
		 iRemaining = -1;
		 return 1;
	 }
	 return 0;
}


/*
 * Function name	:	Display
 *
 * Description		:	use this function to display the tasks pending in the queue.
 *
 * Parameters		:	None
 *
 * Returns			:	None
 */
void Display(void)
{
	 int i;
	 if(Q_Empty())
		 printf(" \n Empty Queue\n");
	 else
	 {
		  printf("--------------------Start--------------------\n");
		  for(i=iFlushed;i<=iRemaining;i++)
		  {
			  printf("%d.Element\t:\t%d\n",i+1,PQ[i].iElement);
			  printf("%d.Priority\t:\t%d\n",i+1,PQ[i].iPriority);
		  }
		  printf("--------------------Ends---------------------\n\n");
	 }
}


/*
 * Function name	:	Check_For_Same_Priority
 *
 * Description		:	use this function to check for the same priority task exist or not
 * 						if exist than return the oldest task with the same priority
 *
 * Parameters		:	PriorityQ pTemp_Queue -> object of the Priority queue structure
 * 						PriorityQ pTemp_After -> object of the Priority queue structure
 *
 * Returns			:	Object of the priority queue structure
 */
PriorityQ Check_For_Same_Priority(PriorityQ pTemp_Queue,PriorityQ pTemp_After)
{
	int iLoop,iCount = 0;
	static int iDel_Count = 0;

	for(iLoop = iRemaining+1; iLoop > -1  ; iLoop--)
	{
		if(PQ[iLoop].iPriority == PQ[iLoop-1].iPriority)
			iCount++;
	}

	if((iCount-iDel_Count) > 2)
	{
		if(PQ[SIZE-iCount-1].iPriority == PQ[SIZE-iCount].iPriority)
		if(pTemp_Queue.iPriority == pTemp_After.iPriority)
		{
			dDiff_t = difftime(PQ[SIZE-iCount-1].Mytime_t,PQ[SIZE-iCount].Mytime_t);
			if(dDiff_t < 0)
			{
				PQ[SIZE-iCount-1].iReturn_Status = 0;
				iDel_Count++;
				return PQ[SIZE-iCount-1];
			}
			else
			{
				PQ[SIZE-iCount].iReturn_Status = 1;
				PQ[SIZE-iCount].iMulti = iCount;
				iDel_Count++;
				return PQ[SIZE-iCount];
			}
		}
	}
	else if(pTemp_Queue.iPriority == pTemp_After.iPriority)
	{
		dDiff_t = difftime(pTemp_Queue.Mytime_t,pTemp_After.Mytime_t);
		if(dDiff_t < 0)
		{
			pTemp_Queue.iReturn_Status = 0;
			iDel_Count++;
			return pTemp_Queue;
		}
		else
		{
			pTemp_After.iReturn_Status = 1;
			iDel_Count++;
			return pTemp_After;
		}
	}
	if(iDel_Count > 5)
	{
		iDel_Count = 0;
	}
	else
	{
		pTemp_Queue.iReturn_Status = 0;
		iDel_Count++;
		return pTemp_Queue;
	}
}


/*
 * Function name	:	Do_As_Per_Task_Priority
 *
 * Description		:	use this function to follow the task priority in performing the task
 *
 * Parameters		:	None
 *
 * Returns			:	None
 */
void Do_As_Per_Task_Priority(void)
{
	if(PQ[iFlushed-1].iPriority == 0)
	{
		printf("Highest Priority task\n");
	}
	else if(PQ[iFlushed-1].iPriority == 1)
	{
		printf("Priority of the task is %d\n",PQ[iFlushed-1].iPriority);
	}
	else if(PQ[iFlushed-1].iPriority == 2)
	{
		printf("Priority of the task is %d\n",PQ[iFlushed-1].iPriority);
	}
	else if(PQ[iFlushed-1].iPriority == 3)
	{
		printf("Priority of the task is %d\n",PQ[iFlushed-1].iPriority);
	}
	else if(PQ[iFlushed-1].iPriority == 4)
	{
		printf("Priority of the task is %d\n",PQ[iFlushed-1].iPriority);
	}
	else if(PQ[iFlushed-1].iPriority == 5)
	{
		printf("Lowest Priority task\n");
	}
}
