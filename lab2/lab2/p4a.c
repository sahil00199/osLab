#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char* argv[])
{
	if (argc != 2) 
	{
		fprintf(stderr, "Incorrect number of arguments, %d expected but %d give\n", 1, argc - 1);
	}


	FILE* outputFile = fopen (argv[1], "w");
	int pid = fork();
	if (pid == 0)
	{
		printf("Child %d : writing to file %d\n", getpid(), fileno(outputFile));
		write(fileno(outputFile), "hellp world! i am the child\n", 28);
		//fprintf(outputFile, "hello world! i am the child\n");
	}
	else
	{
		printf("Parent : File opened. fd = %d\n", fileno(outputFile));
		printf("Parent %d : writing to file %d\n", getpid(), fileno(outputFile));
		wtrite(fileno(outputFile), "hello world! i am the parent\n", 28);
		//fprintf(outputFile, "hello world! i am the parent\n");
		wait(NULL);
		printf("Parent : The child has terminated\n");
	}


	return 0;
}