#include <myTerm.h>
int
mt_setfgcolor (enum colors color)
{
  char buf[40];
  int len = snprintf (buf, 40, "\33[%dm", color);
  write (STDOUT_FILENO, buf, len);
  return 0;
}
