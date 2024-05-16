#include "sc_variables.h"
#include <stdio.h>
int
sc_accumulatorGet (int *value)
{
  if (value == NULL)
    return -1;
  *value = SC_ACCUMULATOR;
  return 0;
}