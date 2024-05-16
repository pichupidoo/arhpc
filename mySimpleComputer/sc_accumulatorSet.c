#include "sc_variables.h"
int
sc_accumulatorSet (int value)
{
  if (value < 0 || value > 32767)
    return -1;
  SC_ACCUMULATOR = value;
  return 0;
}