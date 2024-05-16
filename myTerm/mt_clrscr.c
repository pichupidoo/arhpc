#include <string.h>
#include <unistd.h>
int
mt_clrscr (void)
{
  const char *str = "\E[H\E[2J\E[0;0H";
  ssize_t bytes_written = write (STDOUT_FILENO, str, strlen (str));
  if (bytes_written == -1)
    return -1;
  return 0;
}