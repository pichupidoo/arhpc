#include <myTerm.h>
int
mt_clrscr (void)
{
  char s[40] = { 0 };
  int len = snprintf (s, 39, "\33[2J\r");
  write (STDOUT_FILENO, s, len);
  return 0;
}