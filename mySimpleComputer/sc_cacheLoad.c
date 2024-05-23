#include "sc_variables.h"
#include <mySimpleComputer.h>

int
sc_cacheLoad (int address)
{
  int tcounter = 0;
  sc_delayGet (&tcounter);
  sc_delaySet (tcounter + 9);

  int stop = 0;

  // для последней строки
  ((address + 10) < SC_MEMARR_SIZE) ? (stop = 10) : (stop = 8);

  int flag = -1;
  for (int i = 0; i < 5; i++)
    {
      if (SC_CACHE[i].start_address == -1)
        {
          flag = i;
          break;
        }
    }

  if (flag >= 0)
    {
      int value = 0;
      SC_CACHE[flag].start_address = address;
      for (int i = 0; i < stop; i++)
        {
          sc_memoryGet (address + i, &value);
          SC_CACHE[flag].str[i] = value;
        }
    }
  else
    {
      int max_time = 0;
      int max_index = -1;
      for (int i = 0; i < 5; i++)
        {
          if (SC_CACHE[i].str_time > max_time)
            {
              max_time = SC_CACHE[i].str_time;
              max_index = i;
            }
        }
      if (SC_CACHE[max_index].str_change)
        {
          sc_cacheSave (address);
        }

      int value = 0;
      SC_CACHE[max_index].start_address = address;
      for (int i = 0; i < stop; i++)
        {
          sc_memoryGet (address + i, &value);
          SC_CACHE[max_index].str[i] = value;
        }
      SC_CACHE[max_index].str_change = 0;
      SC_CACHE[max_index].str_time = 0;
    }

  return 0;
}