#include <mySimpleComputer.h>
int
bc_getbigcharpos (int *big, int x, int y, int *value)
{
  int bit_number = x < 5 ? y + (x - 1) * 8 : y + (x - 5) * 8;
  if (x < 5)
    *value = GET_BIT_VALUE (big[0], bit_number);
  else
    *value = GET_BIT_VALUE (big[1], bit_number);
  return 0;
}