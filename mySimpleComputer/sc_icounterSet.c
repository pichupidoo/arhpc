#include "sc_variables.h"
int
sc_icounterSet (int value)
{
  if (value < 0 || value > 127)
    return -1;
  SC_ICOUNTER = value;
  return 0;
}