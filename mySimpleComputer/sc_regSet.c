#include "sc_variables.h"
int
sc_regSet (int sc_register, int value)
{
  if (sc_register != SC_THROTTLE && sc_register != SC_INVALID_COMMAND
      && sc_register != SC_OUT_OF_MEMORY && sc_register != SC_DIVIDING_BY_ZERO
      && sc_register != SC_OVERFLOW)
    return -1;
  switch (value)
    {
    case 1:
      SC_FLAGS |= sc_register;
      return 0;
    case 0:
      SC_FLAGS &= ~sc_register;
      return 0;
    }
  return -1;
}