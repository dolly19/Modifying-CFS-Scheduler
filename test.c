/* Name: Dolly Sidar
   Roll_Number: 2019304 */
   
   
#include <stdio.h>
#include <stdlib.h>
#include <linux/kernel.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <sys/wait.h>
#include <time.h>
#include <omp.h>


int fib(int n)
{	
	if(n == 0) 
		return 0;
	else if(n == 1)
		return 1;
	else 
		return fib(n - 1) + fib(n - 2);
}

int main()
{
	int pid;
	long s_runtime;
	double start_time;
	double time;
	int i;
	printf("Enter soft runtime value : ");
	int args = scanf("%ld",&s_runtime);
	if(args <1 ){
		printf("Error : wrong input \n"); 
		return 1 ;}
	
	if(s_runtime < 0 ){
		printf("Error : soft runtime can't be negative\n"); 
		return 1;}
		

	printf("Time taken with soft realtime guarantees:\n");
	start_time = omp_get_wtime();
	for(i = 0; i < 4; i++)
	{
		if(fork() == 0)
		{
			
			long status = syscall(548, pid, s_runtime);
			int result = fib(43);
			time = omp_get_wtime() - start_time;
			printf("Process %d: %f sec\n", i + 1, time);
			exit(0);
			
		}
	}
	while(i > 0)
	{
		wait(NULL);
		i--;
	}
	
	printf("Time taken without soft realtime guarantees:\n");
	start_time = omp_get_wtime();
	for(i = 0; i < 4; i++)
	{
		if(fork() == 0)
		{
			int result = fib(43);
			time = omp_get_wtime() - start_time;
			printf("Processes %d: %f sec\n", i + 1, time);
			exit(0);
		}
	}
	while(i > 0)
	{
		wait(NULL);
		i--;
	}
	

	return 0;

}
