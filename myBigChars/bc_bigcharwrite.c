#include <unistd.h>
int
bc_bigcharwrite (int fd, int *big, int count)
{
  if (!big)
    return -1;
  ssize_t size = count * sizeof (int) * 2;
  if (write (fd, big, size) != size)
    return -1;
  return 0;
}