#include "sc_variables.h"
#include <mySimpleComputer.h>
int
sc_cacheInit ()
{
  for (int i = 0; i < 5; i++)
    {
      SC_CACHE[i].start_address = -1;
      for (int j = 0; j < 10; j++)
        {
          SC_CACHE[i].str[j] = 0;
        }
      SC_CACHE[i].str_change = 0;
      SC_CACHE[i].str_time = 0;
    }
  return 0;
}