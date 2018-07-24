#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

/*
	The input before entering anything (for the child process was):
		 3133 pts/76   S+     0:00 ./a.out
	and the output after entering (i.e. after the child process terminated) was:
		 3133 pts/76   Z+     0:00 [a.out] <defunct>

*/

int main()
{
	int pid = fork();
	if (pid == 0)
	{
		printf("Child : The child's process ID is : %d\n", getpid());
		printf("Child : The parent process ID is : %d\n", getppid());
		char  str[100];
		scanf("%s", str);
		//printf("child dead\n");
	}
	else
	{
		printf("Parent : The child's process ID is : %d\n", pid);
		printf("Parent : The process ID is : %d\n", getpid());
		sleep(60);
		wait(NULL);
		printf("Parent : The parent has terminated\n");
	}

	return 0;
}