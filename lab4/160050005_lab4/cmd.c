#include "types.h"
#include "user.h"
#include "fcntl.h"

void
panic(char *s)
{
  printf(2, "%s\n", s);
  exit();
}

int
fork1(void)
{
  int pid;

  pid = fork();
  if(pid == -1)
    panic("fork");
  return pid;
}


int main(int argc, char *argv[])
{
	if (argc <= 1)
	{
		printf(1, "There were too few arguments\n");
	}
	if (fork1() == 0)
	{
		exec(argv[1], argv + 1);
	}
	else
	{
		wait();
	}

	exit();
}