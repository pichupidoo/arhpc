#include "sc_variables.h"
#include <mySimpleComputer.h>

int
sc_accumulatorSet (int value)
{
  if (value >> 15)
    return -1;
  SC_REG_ACC = value;
  return 0;
}