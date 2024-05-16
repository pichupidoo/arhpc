#include "sc_variables.h"
#include <stdio.h>
int
sc_regGet (int sc_register, int *value)
{
  if (value == NULL)
    return -1;
  if (sc_register != SC_THROTTLE && sc_register != SC_INVALID_COMMAND
      && sc_register != SC_OUT_OF_MEMORY && sc_register != SC_DIVIDING_BY_ZERO
      && sc_register != SC_OVERFLOW)
    return -1;
  *value = SC_FLAGS & sc_register;
  if (*value > 0)
    *value = 1;
  return 0;
}