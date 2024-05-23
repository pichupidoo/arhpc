#include "sc_variables.h"
#include <mySimpleComputer.h>

/**
 * @brief Set a flag in flags register.
 *
 * @param register - flag to be set (macros start with SC_FLAG_)
 * @param value - value to be set
 *
 * @retval 0 - success
 * @retval -1 - invalid flag, flags remain unchanged
 */
int
sc_regSet (int address, int value)
{
  // Invalid flag
  if (address >> 5)
    return -1;

  if (value >> 15)
    return -1;

  if (value)
    {
      SC_REG_FLAGS = SC_REG_FLAGS | address;
      return 0;
    }
  else
    {
      SC_REG_FLAGS = SC_REG_FLAGS & (~address);
      return 0;
    }
}