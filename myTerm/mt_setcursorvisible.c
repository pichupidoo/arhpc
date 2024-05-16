#include <string.h>
#include <unistd.h>
int
mt_setcursorvisible (int value)
{
  ssize_t bytes_written;
  char *esc;
  switch (value)
    {
    case 0:
      esc = "\E[?25l";
      bytes_written = write (STDOUT_FILENO, esc, strlen (esc));
      break;
    case 1:
      esc = "\E[?12;25h";
      bytes_written = write (STDOUT_FILENO, esc, strlen (esc));
      break;
    }
  if (bytes_written == -1)
    {
      return -1;
    }
  return 0;
}