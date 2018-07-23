#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char* argv[])
{
	close(0);
	FILE* outputFile = fopen (argv[1], "r");
	int pid = fork();
	if (pid == 0)
	{
		execl("./mycat", "", (char * ) NULL);
	}
	else
	{
		printf("Parent : File opened: fd = %d\n", fileno(outputFile));
		//printf("Parent %d : writing to file %d\n", getpid(), fileno(outputFile));
		wait(NULL);
		printf("\nParent : The child has terminated\n");
	}


	return 0;
}