#include "sc_variables.h"
#include <mySimpleComputer.h>
#include <stdio.h>
int
sc_memoryGet (int address, int *value)
{
  if (address < 0 || address >= SC_MEMARR_SIZE || value == NULL)
    return -1;
  if (SC_IGNORE_CACHE)
    {
      *value = SC_MEMARR[address];
      return 0;
    }
  /*if (sc_cacheGet(address, value))
  {
    sc_cacheSet(address, *value);
    return -2;
  }*/
  return 0;
}