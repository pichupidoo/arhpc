#include "sc_variables.h"
int
sc_setIgnoreCache (int value)
{
  if (value != 0 && value != 1)
    return -1;
  SC_IGNORE_CACHE = value;
  return 0;
}