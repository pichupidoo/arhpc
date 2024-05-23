#include <myTerm.h>
int
mt_gotoXY (int row, int col)
{
  char s[40] = { 0 };
  int len = snprintf (s, 39, "\33[%d;%dH", row, col);
  write (STDOUT_FILENO, s, len);
  return 0;
}