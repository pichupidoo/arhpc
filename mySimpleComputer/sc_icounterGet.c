#include "sc_variables.h"
#include <mySimpleComputer.h>

int
sc_icounterGet (int *value)
{
  if (!value)
    return -1;
  *value = SC_REG_IC;
  return 0;
}