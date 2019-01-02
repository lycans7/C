/****************************************************
*													*
*	                list dynamic                    *
*             KartiK : kartikdb@cdac.in             *
*                                                   *
*****************************************************/

#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>

void create();
void insert();
void delete();
void search();
void sort();
void display_all();

int i,*arr=NULL,n,*ptr,count=0;

void main()
{
	char ch;
	printf("Enter Number of Elements :: ");
	scanf("%d",&n);
	do
	{
	printf("1. Create the List\n");
	printf("2. Insert\n");
	printf("3. Delete List\n");
	printf("4. Search\n");
	printf("5. Sort\n");
	printf("6. Display All the Elements\n");
	printf("7. Exit\n");

	printf("Enter the Choice you want to operate :: ");
	scanf("\n%c",&ch);

	switch(ch)
	{
		case '1':
			create();
			break;
		case '2':
			insert();
			break;
		case '3':
			delete();
			break;
		case '4':
			search();
			break;
		case '5':
			sort();
			break;
		case '6':
			display_all();
			break;
		case '7':
			exit(0);
		default:
			printf("Invalid Choice\n");
	}
	}while(1);
}

void create()
{
	int data;
	
        
	printf("Enter the data to the List :: ");
	scanf("%d",&data);

	if(arr==NULL)
	{
		printf("%d",count);
		ptr=(int*)malloc(n*sizeof(int));
		arr=ptr;
		*(arr+count)=data;
		count++;
	}
	else
	{	
		*(arr+count)=data;
		count++;
	}
	if(count==n)
		return;
	else
		create();
}
void insert()
{
	int pos,info,j=++count;

	arr=(int*)realloc(ptr,(count+1)*sizeof(int));

	printf("Enter the Position Where You want to Add the Element :: ");
	scanf("%d",&pos);
	printf("Enter the Element to insert :: ");
	scanf("%d",&info);

        while(j!=(pos-1))
	{
		*(arr+j)=*(arr+j-1);
		printf("%d\t",*(arr+j));
		j--;
	}
	*(arr+pos-1)=info;
	display_all();
}
void delete()
{
	int info;
	printf("Enter the Element to Delete :: ");
	scanf("%d",&info);

	for(i=0;i<count;i++)
	{
		if(*(arr+i)==info)
		{
			while(i!=count)
			{
				*(arr+i)=*(arr+i+1);
				i++;
			}
			count--;
			arr=(int*)realloc(arr,count*sizeof(int));
			return;
		}

	}
//	arr=(int*)realloc(arr,(count-1)*sizeof(int));
	display_all();
}
void search()
{
	int info,f;
	
	printf("Enter the element you want to display :: ");
	scanf("%d",&info);

	for(i=0;i<=count;i++)
	{
		if(*(arr+i)==info)
		{
			f=1;
			break;
		}
		else
			f=0;
	}

	if(f)
		printf("Element is Found and is %d\n",*(arr+i));
	else
		printf("Element is Not Found\n");
}

void sort()
{
	int p,q,temp;
	printf("Sorted list is :: ");

	for(p=0;p<count;p++)
	{
		for(q=p+1;q<count;q++)
		{
			if(*(arr+p) > *(arr+q))
			{
				temp = *(arr+p);
				*(arr+p)=*(arr+q);
				*(arr+q)=temp;
			}
		}

	}
	for(p=0;p<n;p++)
		printf("%d\t",*(arr+p));
	printf("\n");
}

void display_all()
{
	printf("All entered Elements are\n");
	for(i=0;i<count;i++)
		printf("Element %d is ::  %d \n",i,*(arr+i));
	
}
