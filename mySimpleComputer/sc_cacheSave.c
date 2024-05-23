#include "sc_variables.h"
#include <mySimpleComputer.h>

int
sc_cacheSave (int address)
{
  int stop = 0;
  ((address + 10) < SC_MEMARR_SIZE) ? (stop = 10) : (stop = 8);

  int index = -1;
  for (int i = 0; i < 5; i++)
    {
      if (SC_CACHE[i].start_address == address)
        {
          index = i;
          break;
        }
    }

  for (int i = 0; i < stop; i++)
    {
      int value = SC_CACHE[index].str[i];
      sc_memorySet (address + i, value);
    }

  return 0;
}