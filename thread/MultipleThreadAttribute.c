#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int count1,count2,count3;

pthread_mutex_t mut1,mut2;

void* fun(){
 
	while(1){
		printf("I am no 2. count = %d \n", count1);
		sleep(1);
		count1++;
	}
}

void* fun1(){
	while(1){
		printf("I am no 1. count2  = %d \n", count2);
		sleep(1);
		count2++;
	}
}

void* fun2(){
	while(1){
		printf("I am no 3. count3 = %d \n", count3);
		sleep(1);
		count3++;
	}
}

int main(){
	int ret;
	pthread_t t1,t2,t3;
	pthread_attr_t attr1,attr2,attr3;

	struct sched_param param1,param2,param3;

	ret = pthread_attr_init(&attr1); // for 1 thread scheduling 

	ret = pthread_attr_getschedparam(&attr1,&param1);
	param1.sched_priority = 3 ;
	printf("param1.sched_priority = %d \n",param1.sched_priority);

	ret = pthread_attr_setschedparam(&attr1,&param1);

	ret = pthread_create(&t1,&attr1,&fun1,0);  //thread create 1
	if(ret != 0){
		printf(" ERROR TO CREATE: %d \n",ret);
		return 1;
	}

	ret = pthread_attr_init(&attr2);   // for second thread scheduling

	ret = pthread_attr_getschedparam(&attr2,&param2);
	param2.sched_priority = 2;
	printf("param2.sched_priority = %d \n",param2.sched_priority);


	ret = pthread_attr_setschedparam(&attr2,&param2);

	ret = pthread_create(&t2,&attr2,&fun,0);   //thread create 2
	if(ret != 0){
		printf(" ERROR TO CREATE: %d \n",ret);
		return 1;
	}

	ret = pthread_attr_init(&attr3);   //for third thread scheduling

	ret = pthread_attr_getschedparam(&attr3,&param3);
Z
	printf("param3.sched_priority = %d \n",param3.sched_priority);

	ret = pthread_attr_setschedparam(&attr3,&param3);

	ret = pthread_create(&t3,&attr3,&fun2,0); // thread create 3

	if(ret != 0){
		printf(" ERROR TO CREATE: %d \n",ret);
		return 1;
	}

	pthread_join(t1,NULL);	
	pthread_join(t2,NULL);
	pthread_join(t3,NULL);

	return 0;
}
