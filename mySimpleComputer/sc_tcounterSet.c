#include "sc_variables.h"
int
sc_tcounterSet (unsigned char value)
{
  SC_TCOUNTER = value;
  return 0;
}