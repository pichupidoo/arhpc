#include "sc_variables.h"
#include <mySimpleComputer.h>

int
sc_icounterSet (int value)
{
  if (value >> 15)
    return -1;
  SC_REG_IC = value;
  return 0;
}