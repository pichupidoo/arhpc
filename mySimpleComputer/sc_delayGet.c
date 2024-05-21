#include "sc_variables.h"
#include <mySimpleComputer.h>

int
sc_delayGet (int *delay)
{
  *delay = SC_REG_DELAY;
  return 0;
}