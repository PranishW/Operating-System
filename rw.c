#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
pthread_mutex_t wr,mutex;
int readcount=0;
int a = 10;
void *reader(void *args)
{
	long int num = (long int)args;
	pthread_mutex_lock(&mutex);
	readcount++;
	pthread_mutex_unlock(&mutex);
	printf("\nReader %ld is reading %d",num+1,a);
	sleep(1);
	if(readcount==1)
		pthread_mutex_lock(&wr);
	pthread_mutex_lock(&mutex);
	readcount--;
	pthread_mutex_unlock(&mutex);
	printf("\nReader %ld leaving CS",num+1);
	sleep(1);
	if(readcount==0)
		pthread_mutex_unlock(&wr);
	pthread_exit(NULL);
}
void *writer(void *args)
{
	long int num = (long int)args;
	pthread_mutex_lock(&wr);
	printf("\nWriter %ld writes %d",num+1,++a);
	sleep(1);
	pthread_mutex_unlock(&wr);
	printf("\nWriter %ld leaving CS",num+1);
	sleep(1);
	pthread_exit(NULL);
}
int main()
{
	int nw,nr,i,j;
	pthread_t r[10],w[10];
	printf("Enter the number of writers :-");
	scanf("%d",&nw);
	printf("Enter the number of readers :-");
	scanf("%d",&nr);
	pthread_mutex_init(&wr,NULL);
	pthread_mutex_init(&mutex,NULL);
	for(i=0;i<nw;i++)
		pthread_create(&w[i],NULL,writer,(void*)i);
	for(j=0;j<nr;j++)
		pthread_create(&r[j],NULL,reader,(void *)j);
	for(i=0;i<nw;i++)
		pthread_join(w[i],NULL);
	for(j=0;j<nr;j++)
		pthread_join(r[j],NULL);
	return 0;
}
