#include "console.h"
#include <fcntl.h>
#include <myBigChars.h>
#include <stdio.h>
#include <unistd.h>
int
get_font (char *filename)
{
  int fd;
  fd = open (filename, O_RDONLY);
  if (fd == -1)
    {
      printf ("Can't open font :(\n");
      return -1;
    }
  int count;
  bc_bigcharread (fd, big, 18, &count);
  if (count != 18)
    {
      printf ("Something wrong with bc_bigcharread\n");
      close (fd);
      return -1;
    }
  close (fd);
  return 0;
}