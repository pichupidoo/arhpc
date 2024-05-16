#include "mySimpleComputer.h"
#include <stdio.h>
int
sc_commandEncode (int sign, int command, int operand, int *value)
{
  if (sign != 0 && sign != 1)
    return -1;
  if (sc_commandValidate (command))
    return -1;
  if (operand < 0 || operand > 127)
    return -1;
  if (value == NULL)
    return -1;
  sign <<= 14;
  command <<= 7;
  *value = operand;
  *value |= command;
  *value |= sign;
  return 0;
}