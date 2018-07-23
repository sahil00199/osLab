#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main()
{
	int pid = fork();
	if (pid == 0)
	{
		printf("Child : My process ID is : %d\n", getpid());
		printf("Child : The parent process ID is : %d\n", getppid());
		sleep(2);
		printf("\nChild : My process ID is : %d\n", getpid());
		printf("Child : The parent process ID is : %d\n", getppid());
	}
	else
	{
		printf("Parent : My process ID is : %d\n", getpid());
		printf("Parent : The child process ID is : %d\n", pid);
		sleep(1);
		printf("Parent : The parent has terminated\n");
	}

	return 0;
}