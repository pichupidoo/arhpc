#include <myBigChars.h>
int
bc_bigcharread (int fd, int *big, int need_count, int *count)
{
  *count = read (fd, big, need_count * sizeof (int) * 2);
  if (*count != (int)(need_count * sizeof (int) * 2))
    return -1;
  else
    return 0;
}