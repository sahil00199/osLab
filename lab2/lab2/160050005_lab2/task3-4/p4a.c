#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char* argv[])
{
	if (argc != 2) 
	{
		fprintf(stderr, "Incorrect number of arguments, %d expected but %d give\n", 1, argc - 1);
		return 0;
	}


	//FILE* outputFile = fopen (argv[1], "w");
	int outputFd = open(argv[1], O_RDWR | O_CREAT , S_IRWXU); 
	if (outputFd == -1)
	{
		fprintf(stderr, "The file did not open!");
	}
	int pid = fork();
	if (pid == 0)
	{
		printf("Child %d: writing to file %d\n", getpid(), outputFd);
		write(outputFd, "hello world! i am the child\n", 28);
		//fprintf(outputFile, "hello world! i am the child\n");
	}
	else
	{
		printf("Parent: File opened. fd = %d\n", outputFd);
		printf("Parent %d: writing to file %d\n", getpid(), outputFd);
		write(outputFd, "hello world! i am the parent\n", 30);
		//fprintf(outputFile, "hello world! i am the parent\n");
		wait(NULL);
		printf("Parent : The child has terminated\n");
	}


	return 0;
}