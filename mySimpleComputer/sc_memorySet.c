#include "sc_variables.h"
#include <mySimpleComputer.h>
int
sc_memorySet (int address, int value)
{
  if (address < 0 || address >= SC_MEMARR_SIZE || value < 0 || value > 32767)
    return -1;
  if (SC_IGNORE_CACHE)
    {
      SC_MEMARR[address] = value;
      return 0;
    }
  /*if (sc_cacheSet(address, value))
    return -2;*/
  return 0;
}