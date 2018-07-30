#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void f();

void sig_handler(int signum)
{
	if (signum == 2)
	{
		printf("Interrupt SIGINT received\nDo you really want to quit (y|n)?\n");
		char c;
		scanf("%s", &c);
		if (c == 'y')
		{
			exit(0);
		}
		else if (c == 'n')
		{
			printf("\n");
			return;
		}
	}

	else if (signum == 15)
	{
		printf("Interrupt SIGTERM received\nDo you really want to quit (y|n)?\n");
		char c;
		scanf("%s", &c);
		if (c == 'y')
		{
			exit(0);
		}
		else if (c == 'n')
		{
			printf("\n");
			return;
		}
	}
}

void f()
{
	while (1)
	{
		signal(SIGTERM, sig_handler);
		signal(SIGINT, sig_handler);
		//sleep(1);
	}
}

int main()
{
	f();


	return 0;
}
