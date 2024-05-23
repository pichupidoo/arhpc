#include <myBigChars.h>
int
bc_setbigcharpos (int *big, int x, int y, int value)
{
  if (!big)
    return -1;
  // Evil pointer hack
  char *bigchar = (char *)big;
  if (value)
    bigchar[y] = bigchar[y] | 1 << (7 - x);
  else
    bigchar[y] = bigchar[y] & 0 << (7 - x);
  return 0;
}