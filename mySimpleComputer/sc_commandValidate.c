#include "sc_variables.h"
#include <mySimpleComputer.h>

int
sc_commandValidate (int command)
{
  // Stoopid code but I'm too tired to make it a LUT or something more
  // convoluted
  if (!command || command == 1)
    return 0;
  if (command == 10 || command == 11)
    return 0;
  if (command == 20 || command == 21)
    return 0;
  if (command >= 30 && command <= 33)
    return 0;
  if (command >= 40 && command <= 43)
    return 0;
  if (command >= 51 && command <= 76)
    return 0;
  return 1;
}