#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
void bubble_sort(int arr[],int n)
{
	int i,j,temp;
	for(i=0;i<n-1;i++)
	{
		for(j=0;j<n-i-1;j++)
		{
			if(arr[j]>arr[j+1])
			{
				temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;
			}
		}
	}
}
int main(int argc,char* argv[],char* envp[])
{
	int i,j,n,temp;
	printf("Enter the size of array :-");
	scanf("%d",&n);
	int arr[n];
	printf("Enter array nos :-");
	for(i=0;i<n;i++)
		scanf("%d",&arr[i]);
	printf("Array nos - ");
	for(i=0;i<n;i++)
		printf("%d ",arr[i]);
	bubble_sort(arr,n);
	printf("\nBefore fork() - ");
	for(i=0;i<n;i++)
		printf("%d ",arr[i]);
	pid_t p = fork();
	if(p==0)
	{
		sleep(2);
		printf("\nChild Process running id - %d",getpid());
		printf("\nParent Process is %d ",getppid());
		char *argv[n+1];
		argv[0] = "./sort";
		for(i=1;i<=n;i++)
		{
			argv[i] = malloc(10);
			snprintf(argv[i],10,"%d",arr[i-1]);
		}
		argv[i] = NULL;
		char *envp[] = {NULL};
		execve(argv[0],argv,envp);
	}
	else
	{
		printf("\nParent Process id - %d",getpid());
		printf("\nChild Process of this Parent Process is %d",p);
		printf("\nSorting array in ascending order in parent process - ");
		for(i=0;i<n;i++)
			printf("%d ",arr[i]);
		printf("\n");
	}
	return 0;
}
