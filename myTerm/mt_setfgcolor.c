#include "colors.h"
#include <string.h>
#include <unistd.h>
int
mt_setfgcolor (enum colors color)
{
  ssize_t bytes_written;
  char *esc = NULL;
  switch (color)
    {
    case BLACK:
      esc = "\E[38;5;0m";
      bytes_written = write (STDOUT_FILENO, esc, strlen (esc));
      break;
    case RED:
      esc = "\E[38;5;1m";
      bytes_written = write (STDOUT_FILENO, esc, strlen (esc));
      break;
    case GREEN:
      esc = "\E[38;5;2m";
      bytes_written = write (STDOUT_FILENO, esc, strlen (esc));
      break;
    case YELLOW:
      esc = "\E[38;5;3m";
      bytes_written = write (STDOUT_FILENO, esc, strlen (esc));
      break;
    case BLUE:
      esc = "\E[38;5;4m";
      bytes_written = write (STDOUT_FILENO, esc, strlen (esc));
      break;
    case PURPLE:
      esc = "\E[38;5;5m";
      bytes_written = write (STDOUT_FILENO, esc, strlen (esc));
      break;
    case CYAN:
      esc = "\E[38;5;6m";
      bytes_written = write (STDOUT_FILENO, esc, strlen (esc));
      break;
    case WHITE:
      esc = "\E[38;5;7m";
      bytes_written = write (STDOUT_FILENO, esc, strlen (esc));
      break;
    case DEFAULT:
      esc = "\E[0m";
      bytes_written = write (STDOUT_FILENO, esc, strlen (esc));
      break;
    }
  if (bytes_written == -1)
    {
      return -1;
    }
  return 0;
}