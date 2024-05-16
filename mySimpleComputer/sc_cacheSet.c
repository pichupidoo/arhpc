#include "sc_variables.h"
#include <myTerm.h>
#include <stdio.h>
int
sc_cacheSet (int address, int value)
{
  if (address < 0 || address >= SC_MEMARR_SIZE)
    return -1;
  int i;
  int max_downtime = 0;
  int displacement = 0;
  int line_size = 10;
  int hit = 0;
  for (i = 0; i < SC_CACHE_SIZE; i++)
    {
      if (cache[i].address == -1)
        {
          break;
        }
      if (cache[i].downtime > max_downtime)
        {
          max_downtime = cache[i].downtime;
        }
      if (cache[i].address == (address - (address % 10)))
        {
          hit = 1;
          break;
        }
    }
  if (hit)
    {
      cache[i].line[address % 10] = value;
      return 0;
    }
  else
    SC_TCOUNTER = 10;
  if (i == SC_CACHE_SIZE)
    {
      displacement = 1;
      for (i = 0; i < SC_CACHE_SIZE; i++)
        if (cache[i].downtime == max_downtime)
          break;
    }
  line_size = cache[i].address == 120 ? 8 : 10;
  if (displacement)
    for (int j = 0; j < line_size; j++)
      {
        SC_MEMARR[cache[i].address + j] = cache[i].line[j];
      }
  cache[i].address = address - (address % 10);
  line_size = cache[i].address == 120 ? 8 : 10;
  for (int j = 0; j < line_size; j++)
    {
      cache[i].line[j] = SC_MEMARR[cache[i].address + j];
    }
  return -2;
}