#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
sem_t empty,full;
pthread_mutex_t mutex;
int buffer[5];
int count=0;
void *producer(void *args)
{
	long int num = (long int)args;
	sem_wait(&empty);
	pthread_mutex_lock(&mutex);
	buffer[count] = rand()%10;
	printf("Producer %ld produced %d\n",num+1,buffer[count]);
	count++;
	sleep(1);
	pthread_mutex_unlock(&mutex);
	sem_post(&full);
	pthread_exit(NULL);
}
void *consumer(void *args)
{
	long int num = (long int)args;
	sem_wait(&full);
	pthread_mutex_lock(&mutex);
	count--;
	printf("Consumer %ld consumed %d\n",num+1,buffer[count]);
	sleep(1);
	pthread_mutex_unlock(&mutex);
	sem_post(&empty);
	pthread_exit(NULL);
}
int main()
{
	int nc,np,i,j,k,l;
	pthread_t p[10],c[10];
	printf("Enter the number of consumers :-");
	scanf("%d",&nc);
	printf("Enter the number of producers :-");
	scanf("%d",&np);
	sem_init(&empty,0,5);
	sem_init(&full,0,0);
	pthread_mutex_init(&mutex,NULL);
	for(i=0;i<np;i++)
		pthread_create(&p[i],NULL,producer , (void *)i);
	for(j=0;j<nc;j++)
		pthread_create(&c[j],NULL,consumer , (void *)j);
	for(k=0;k<np;k++)
		pthread_join(p[k],NULL);
	for(l=0;l<nc;l++)
		pthread_join(c[l],NULL);
	return 0;
}
