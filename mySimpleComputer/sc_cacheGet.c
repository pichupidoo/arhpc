#include "sc_variables.h"
#include <stdio.h>
int
sc_cacheGet (int address, int *value)
{
  if (address < 0 || address >= SC_MEMARR_SIZE || value == NULL)
    return -1;
  int cacheline_address;
  for (int i = 0; i < SC_CACHE_SIZE; i++)
    if (cache[i].address != -1)
      cache[i].downtime++;
  for (int i = 0; i < SC_CACHE_SIZE; i++)
    {
      if (cache[i].address != -1)
        {
          cacheline_address = address - cache[i].address;
          if (cacheline_address >= 0 && cacheline_address < 10)
            {
              cache[i].downtime = 0;
              *value = cache[i].line[cacheline_address];
              return 0;
            }
        }
    }
  return -1;
}