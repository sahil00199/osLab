#include "types.h"
#include "stat.h"
#include "user.h"

char buf[1];

void
cat(int fd, int numLines)
{
  int n;
  int currentLines = 0;

  while((n = read(fd, buf, sizeof(buf))) > 0 && currentLines < numLines) {
    if (write(1, buf, n) != n) {
      printf(1, "cat: write error\n");
      exit();
    }
    if (buf[0] == '\n')
    {
      currentLines += 1;
    }
  }
  if(n < 0){
    printf(1, "cat: read error\n");
    exit();
  }
}

int
main(int argc, char *argv[])
{
  int fd, i;

  if(argc <= 2){
    printf(1, "There were too few arguments for head!\n");
    exit();
  }
  int isOkay = 1;
  for (int i = 0 ; argv[1][i] != '\0' ; i ++)
  {
    if (argv[1][i] < '0' || argv[1][i] > '9')
    {
      isOkay = 0;
      printf(1, "invalid number of lines\n");
      break;
    }
  }
  int numLines = atoi(argv[1]);
  //printf(1, "%d\n", numLines)

  if (argv[1][0] == '-')
  {
    printf(1, "Cannot print a negative number of lines\n");
  }
  else if (isOkay != 0)
  {
    for(i = 2; i < argc; i++){
      printf(1, "--- %s ---\n", argv[i]);
      if((fd = open(argv[i], 0)) < 0){
        printf(1, "cat: cannot open %s\n", argv[i]);
        exit();
      }
      cat(fd, numLines);
      close(fd);
    }
  }
  exit();
}
