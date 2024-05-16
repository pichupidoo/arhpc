#include <myTerm.h>
int
bc_printA (char *str)
{
  if (!str)
    return -1;
  mt_print ("\e(0%s\e(B", str);
  return 0;
}