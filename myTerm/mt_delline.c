#include <myTerm.h>
int
mt_delline (void)
{
  char s[40] = { 0 };
  int len = snprintf (s, 39, "\33[2K\r");
  write (STDOUT_FILENO, s, len);
  return 0;
}