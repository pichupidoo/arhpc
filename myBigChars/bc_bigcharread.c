#include <unistd.h>
int
bc_bigcharread (int fd, int *big, int need_count, int *count)
{
  if (!big)
    return -1;
  if (!count)
    return -1;
  ssize_t size = need_count * 2 * sizeof (int);
  *count = read (fd, big, size) / 2 / sizeof (int);
  if (*count != need_count)
    return -1;
  return 0;
}