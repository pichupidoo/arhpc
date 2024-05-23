#include <myTerm.h>
int
mt_setdefaultcolor (void)
{
  mt_setfgcolor (0); // "0" - reset
  mt_setbgcolor (0);
  return 0;
}
