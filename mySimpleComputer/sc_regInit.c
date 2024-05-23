#include "sc_variables.h"
#include <mySimpleComputer.h>

/**
 * Initialize flags register with zero value
 * @returns 0 - success
 */
int
sc_regInit (void)
{
  SC_REG_FLAGS = 0;
  sc_regSet (SC_FLAG_IGNORECLK, 1);
  return 0;
}