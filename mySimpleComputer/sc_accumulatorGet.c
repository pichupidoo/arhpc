#include "sc_variables.h"
#include <mySimpleComputer.h>

int
sc_accumulatorGet (int *value)
{
  if (!value)
    return -1;
  *value = SC_REG_ACC;
  return 0;
}