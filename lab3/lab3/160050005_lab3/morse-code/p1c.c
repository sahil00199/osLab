#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

//The sleep values have been hardcoded to ensure that we have cases where child and grandchild terminate
//at different times. To change this, one must change the value of the variables childSleep 
//and grandChildSleep

void sig_handler(int signum)
{
	pid_t pid;
	int status;
	while (1)
	{
		pid = waitpid(-1, &status, WNOHANG);
		if (pid <= 0)
		{
			return ;
		}
		else
		{
			printf("Parent %d: Child %d is exited\n", getpid(), pid);
		}
	}
}

int main()
{
	signal(SIGCHLD, sig_handler);
	int childSleep = 4;
	int grandChildSleep = 9;
	int pid = fork();
	int ppid;
	if (pid != 0)
	{	
		printf("Child %d is created by parent %d (sleeps for %d seconds)\n", pid, getpid(), childSleep);
	}
	else
	{
		ppid = fork();
		if (ppid != 0)
		{
			printf("Child %d is created by parent %d (sleeps for %d seconds)\n", ppid, getpid(), grandChildSleep);
			sleep(childSleep);
			return 0;
		}
		else
		{
			sleep(grandChildSleep);
			return 0;
		}
	}

	if (pid != 0) 
	{
		sleep(100);
	}



	return 0;
}