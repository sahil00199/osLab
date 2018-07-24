#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

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

	int numIter = toInt(argv[1]);
	int parentId = getpid();
	printf("Parent is : %d\n", getpid());
	int pid;
	float time;

	for (int i = 0 ; i < numIter ; i ++)
	{
		if (getpid() == parentId)
		{
			pid = fork();
			if (pid !=0) printf("Child %d is created\n", pid);
			time = (rand()%1000)/100.0;
		}
	}

	for (int i = 0 ; i < numIter ; i ++)
	{
		wait(NULL);
	}

	if (getpid() == parentId)
	{
		printf("Parent exited\n");
	}
	else
	{
		//printf("%f\n", time);
		sleep(time);
		printf("Child %d exited\n", getpid());
	}


	return 0;
}