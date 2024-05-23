#include "sc_variables.h"
#include <mySimpleComputer.h>

/**
 * @brief Set a value in memory by address.
 *
 * @param address - address in memory
 * @param value - value to be set
 *
 * @retval 0 - success
 * @retval -1 - out of memory bounds/invalid value
 */
int
sc_memorySet (int address, int value)
{
  // Outside of address space
  if (address < 0 && address >= SC_MEMARR_SIZE)
    return -1;
  // Value is too big
  if (value >> 15)
    return -1;
  SC_MEMARR[address] = value;
  return 0;
}