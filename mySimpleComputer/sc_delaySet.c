#include "sc_variables.h"
#include <mySimpleComputer.h>

int
sc_delaySet (int delay)
{
  SC_REG_DELAY = delay;
  return 0;
}