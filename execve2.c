#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc,char* argv[],char* envp[])
{
	int i,n = argc-1;
	int arr[n];
	for(i=0;i<n;i++)
	{
		arr[i] = atoi(argv[i+1]);
	}
	printf("\nPrinting array nos in descending order from child process -");
	for(i=n-1;i>=0;i--)
		printf("%d ",arr[i]);
	return 0;
}
