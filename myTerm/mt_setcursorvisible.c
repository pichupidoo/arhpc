#include <myTerm.h>
int
mt_setcursorvisible (int value)
{
  char s[40] = { 0 };
  int len;
  if (value)
    len = snprintf (s, 40, "\33[?25h\r");
  else
    len = snprintf (s, 40, "\33[?25l\r");
  write (STDOUT_FILENO, s, len);
  return 0;
}