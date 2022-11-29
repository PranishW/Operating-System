// Fork system call, orphan and zombie process
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
void bubble_sort(int arr[],int n)
{
	int i,j,temp;
	for(i=0;i<n;i++)
	{
		for(j=0;j<=n-i;j++)
		{
			if(arr[j]>arr[j+1])
			{
				temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;
			}
		}
	}
	printf("After sorting - ");
	for(i=0;i<n;i++)
		printf("%d ",arr[i]);
	printf("\n");
}
int main()
{
	int n;
	printf("Enter the no of elements :- ");
	scanf("%d",&n);
	int arr[n];
	printf("Enter %d elements - ",n);
	for(int i=0;i<n;i++)
		scanf("%d",&arr[i]);
	printf("Before Sorting :- ");
	for(int i=0;i<n;i++)
		printf("%d ",arr[i]);
	printf("\n");
	pid_t p;
	while(1)
	{
		int choice;
		printf("\n1. Fork System Call\n2. Zombie Process\n3. Orphan Process\n4. Exit\n");
		printf("Enter choice - ");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:
				p = fork();
				if(p==0)
				{
					printf("\nI am Child Process id %d - ",getpid());
					printf("\nParent Process id - %d",getppid());
					printf("\nPrinting the sorted array from Child Process - \n");
					bubble_sort(arr,n);
				}
				else
				{
					wait(NULL);
					printf("I am Parent Process id %d - ",getpid());
					printf("\nPrinting the sorted array from Parent Process -\n");
					bubble_sort(arr,n);
					printf("Child Process terminated using wait system call id - %d",p);
				}
				break;
			case 2:
				p = fork();
				if(p==0)
				{
					printf("\nZombie Process");
					printf("\nI am Child Process id %d ",getpid());
					printf("\nParent Process id %d ",getppid());
				}
				else
				{
					sleep(5);
					printf("\n I am Parent Process id %d ",getpid());
					printf("My child process id - %d",p);
				}
				break;
			case 3:
				p = fork();
				if(p==0)
				{
					sleep(5);
					printf("\nI am Child Process id - %d",getpid());
					printf("\nParent Process id - %d",getppid());
				}
				else
				{
					printf("\nI am Parent Process id %d - ",getpid());
					printf("\nMy chilf process id - %d",p);
				}
				break;
			case 4:
				printf("Exiting.......");
				exit(0);
		}
	}
	return 0;
}
