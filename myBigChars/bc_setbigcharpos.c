#include <mySimpleComputer.h>
int
bc_setbigcharpos (int *big, int x, int y, int value)
{
  int bit_number = x < 5 ? y + (x - 1) * 8 : y + (x - 5) * 8;
  if (x < 5)
    {
      if (value)
        SET_BIT (big[0], bit_number);
      else
        SET_BIT_ZERO (big[0], bit_number);
    }
  else
    {
      if (value)
        SET_BIT (big[1], bit_number);
      else
        SET_BIT_ZERO (big[1], bit_number);
    }
  return 0;
}