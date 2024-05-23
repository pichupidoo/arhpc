#include "sc_variables.h"
#include <mySimpleComputer.h>

/**
 * @brief Get a value in memory by address.
 *
 * @param address - address in memory
 * @param value - pointer to a result variable
 *
 * @retval 0 - success
 * @retval -1 - out of memory bounds/invalid value pointer
 */
int
sc_memoryGet (int address, int *value)
{
  // Outside of address space
  if (address < 0 && address >= SC_MEMARR_SIZE)
    return -1;
  // Value is too big
  if (!value)
    return -1;
  *value = SC_MEMARR[address];
  return 0;
}