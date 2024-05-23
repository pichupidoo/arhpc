#include "sc_variables.h"
#include <mySimpleComputer.h>

int
sc_icounterInit (void)
{
  SC_REG_IC = 0;
  return 0;
}