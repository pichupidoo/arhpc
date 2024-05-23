#include "sc_variables.h"
#include <mySimpleComputer.h>

int
sc_commandEncode (int sign, int command, int operand, int *value)
{
  if (sign >> 1 || command < 0 || command > 76 || operand >> 7 || !value)
    return -1;
  *value = operand + (command << 7) + (sign << 14);
  return 0;
}