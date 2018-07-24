#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int toInt(char * input)
{
	int answer = 0;
	int index = 0;
	//printf("%s\n", input);
	while (input[index] != '\0')
	{
		answer = 10*answer + input[index] - '0';
		index ++;
		//printf("%d\n", answer);
	}
	return answer;
}

int main(int argc, char* argv[])
{
	if (argc != 2) 
	{
		fprintf(stderr, "Incorrect number of arguments, %d expected but %d give\n", 1, argc - 1);
	}

	printf("Parent is : %d\n", getpid());
	int parentID = getpid();
	int numIter = toInt(argv[1]);
	printf("Number of children: %d\n", numIter);
	//printf("%d\n", numIter);
	//printf("%s\n", argv[1]);
	//int pid = fork();
	int pid = 0;
	for (int i = 0 ; i < numIter ; i ++)
	{
		pid = fork();
		if (pid != 0)
		{
			printf("Child %d is created\n", pid);
			wait(NULL);
			break;
		}
		/*if (pid == 0)
		{
			pid = fork();
			if (pid != 0) 
			{
				printf("Child %d is created\n", pid);
				wait(NULL);
			}
		}*/
	}
	if (getpid() == parentID)
	{
		printf("Parent exited\n");
	}
	else
	{
		printf("Child %d exited\n", getpid());
	}


	return 0;
}