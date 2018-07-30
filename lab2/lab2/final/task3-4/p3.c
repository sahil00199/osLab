#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main()
{
	int pid = fork();
	if (pid == 0)
	{
		execl("./mycat", "", (char * ) NULL);
		printf("came here\n");
	}
	else
	{
		wait(NULL);
		printf("Parent : The child has terminated\n");
	}

	return 0;
}