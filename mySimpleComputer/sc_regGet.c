#include "sc_variables.h"
#include <mySimpleComputer.h>
#include <stdio.h>
int
sc_regGet (int reg, int *value)
{
  // if (reg >> 5)
  //  return -1;
  // rintf("%x %x %x\n", SC_REG_FLAGS, reg, *value);
  *value = (SC_REG_FLAGS & reg);
  return 0;
}