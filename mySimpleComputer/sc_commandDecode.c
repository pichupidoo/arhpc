#include <stdio.h>
int
sc_commandDecode (int value, int *sign, int *command, int *operand)
{
  if (sign == NULL)
    return -1;
  if (command == NULL)
    return -1;
  if (operand == NULL)
    return -1;
  if (value < 0 || value > 32767)
    return -1;
  int mask = 0x7f;
  *sign = value >> 14;
  *command = (value >> 7) & mask;
  *operand = value & mask;
  return 0;
}