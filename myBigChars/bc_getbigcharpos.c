#include <myBigChars.h>
int
bc_getbigcharpos (int *big, int x, int y, int *value)
{
  if (!big || !value)
    return -1;
  // Evil pointer hack
  char *bigchar = (char *)big;
  *value = bigchar[y] << (7 - x) & 1;
  return 0;
}