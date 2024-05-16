#include <string.h>
#include <unistd.h>
int
mt_setdefaultcolor (void)
{
  const char *esc = "\E[0m";
  if (write (STDOUT_FILENO, esc, strlen (esc)) == -1)
    return -1;
  return 0;
}