#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

int count;

void sig_handler(int signum)
{
    pid_t pid;
    int   status;
    while (1)
	{
		pid = waitpid(-1, &status, WNOHANG);
		if (pid <= 0) return ;
		else
	    {
	        printf("Child %d is exited\n", pid);
	        count ++;
	    }
	}

}


int main(int argc, char * argv[])
{
	count = 0;
	if (argc != 2)
	{
		fprintf(stderr, "Incorrect number of arguments");
		exit(1);
	}

	int numChild = atoi(argv[1]);
	signal(SIGCHLD, sig_handler);
	int sleepTime;
	int pid;

	for (int i = 0 ; i < numChild ; i ++)
	{
		sleepTime = (rand() % 10) + 1;
		pid = fork();
		if (pid != 0) 
		{
			printf("Child %d is created (sleeps for %d seconds)\n", pid, sleepTime);
		}
		else
		{
			break;
		}
	}

	if (pid == 0)
	{
		sleep(sleepTime);
		return 0;
	}
	if (pid != 0)
	{
		while (count < numChild);
	}


	return 0;
}