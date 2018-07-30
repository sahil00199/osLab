#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>

int main(int argc, char* argv[])
{

	if (argc != 2) 
	{
		fprintf(stderr, "Incorrect number of arguments, %d expected but %d give\n", 1, argc - 1);
		return 0;
	}

	close(0);
	//FILE* outputFile = fopen (argv[1], "r");
	int fd = open(argv[1], O_RDWR | O_CREAT , S_IRWXU);
	if (fd == -1)
	{
		fprintf(stderr, "Unable to open file.\n");
		return 0;
	}
	int pid = fork();
	if (pid == 0)
	{
		execl("./mycat", "", (char * ) NULL);
	}
	else
	{
		printf("Parent: File opened: fd = %d\n", fd);
		//printf("Parent %d : writing to file %d\n", getpid(), fileno(outputFile));
		wait(NULL);
		printf("\nParent : The child has terminated.\n");
	}


	return 0;
}