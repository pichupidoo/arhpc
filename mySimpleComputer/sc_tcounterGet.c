#include "sc_variables.h"
#include <stdio.h>
int
sc_tcounterGet (unsigned char *value)
{
  if (value == NULL)
    return -1;
  *value = SC_TCOUNTER;
  return 0;
}