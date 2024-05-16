#include "sc_variables.h"
int
sc_cacheInit (void)
{
  for (int i = 0; i < SC_CACHE_SIZE; i++)
    {
      cache[i].address = -1;
      cache[i].downtime = 0;
      for (int j = 0; j < 10; j++)
        {
          cache[i].line[j] = 0;
        }
    }
  return 0;
}