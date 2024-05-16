#include <string.h>
#include <unistd.h>
int
mt_delline (void)
{
  const char *esc = "\E[M";
  if (write (STDOUT_FILENO, esc, strlen (esc)) == -1)
    return -1;
  return 0;
}