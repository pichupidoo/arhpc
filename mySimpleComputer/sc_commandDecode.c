#include "sc_variables.h"
#include <mySimpleComputer.h>

int
sc_commandDecode (int value, int *sign, int *command, int *operand)
{
  if (!sign || !command || !operand)
    return -1;
  if (value >> 16)
    return -1;
  *sign = value >> 14;
  *command = (value >> 7) & 127; // 0b01111111
  *operand = value & 127;
  return 0;
}