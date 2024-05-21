#include "sc_variables.h"
#include <mySimpleComputer.h>

int
sc_delayInit (void)
{
  SC_REG_DELAY = 0;
  return 0;
}