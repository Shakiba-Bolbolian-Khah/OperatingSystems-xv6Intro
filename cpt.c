#include "fcntl.h"
#include "types.h"
#include "stat.h"
#include "user.h"

char buf[512];

void
cptCopy(int fdIn, int fdOut)
{
  int n;

  while((n = read(fdIn, buf, sizeof(buf))) > 0) {
    if (write(fdOut, buf, n) != n) {
      printf(1, "cpt: write error\n");
      exit();
    }
  }
  if(n < 0){
    printf(1, "cpt: read error\n");
    exit();
  }
}

void
cptWrite(int fd)
{
  int n;

  if((n = read(0, buf, sizeof(buf))) > 0)
  {
    if (write(fd, buf, n) != n)
    {
      printf(1, "cpt: write error\n");
      exit();
    }
  }
  if(n < 0)
  {
    printf(1, "cpt: read error\n");
    exit();
  }
}

int
main(int argc, char *argv[])
{
  int fd, fdIn, fdOut;

  if(argc == 2)
  {
    if((fd = open(argv[1], 0)) < 0)
    {
      fd = open(argv[1],O_CREATE);
      close(fd);
    }
    fd = open(argv[1],O_WRONLY);
    cptWrite(fd);
    close(fd);
    exit();
  }
  else if(argc == 3)
  {
    if((fdIn = open(argv[1],0)) < 0)
    {
      printf(1, "cpt: read error\n");
      exit();
    }
    else
    {
      if((fdOut = open(argv[2],0)) < 0)
      {
        fdOut = open(argv[2],O_CREATE);
        close(fdOut);
      }
      fdOut = open(argv[2],O_WRONLY);
      cptCopy(fdIn, fdOut);
      close(fdIn);
      close(fdOut);
      exit();
    }
  }
  else
  {
    printf(1, "cpt: command failed\n");
    exit();
  }
}
