#include <myBigChars.h>
int
bc_bigcharwrite (int fd, int *big, int count)
{
  ssize_t size = count * sizeof (int) * 2;
  if (write (fd, big, size) == size)
    return 0;
  else
    return -1;
}