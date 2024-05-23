#include "sc_variables.h"
#include <mySimpleComputer.h>
int
sc_cacheSet (int address, int value)
{
  int tcounter = 0;
  sc_delayGet (&tcounter);
  sc_delaySet (tcounter + 1);

  if (address < 0 || address > 127)
    {
      sc_regSet (SC_FLAG_MEMOOB, 1);
      return -1;
    }
  int l1_address = (address / 10) * 10;

  int flag = 0;
  while (1)
    {
      for (int i = 0; i < 5; i++)
        {
          if (SC_CACHE[i].start_address == l1_address)
            {
              SC_CACHE[i].str[address % 10] = value;
              SC_CACHE[i].str_change = 1;
              SC_CACHE[i].str_time = 0;
              flag = 1;
            }
          else
            {
              SC_CACHE[i].str_time++;
            }
        }
      if (flag)
        {
          return 0;
        }
      if (sc_cacheLoad (l1_address))
        {
          return -1;
        }
    }
}