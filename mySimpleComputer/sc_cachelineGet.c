#include "sc_variables.h"
#include <stdio.h>
int
sc_cachelineGet (int line_number, int *cacheline)
{
  if (cacheline == NULL)
    return -1;
  if (line_number < 0 || line_number > 4)
    return -1;
  int line_size = cache[line_number].address == 120 ? 8 : 10;
  if (cache[line_number].address != -1)
    for (int i = 0; i < line_size; i++)
      cacheline[i] = cache[line_number].line[i];
  return cache[line_number].address;
}