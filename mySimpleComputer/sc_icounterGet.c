#include "sc_variables.h"
#include <stdio.h>
int
sc_icounterGet (int *value)
{
  if (value == NULL)
    return -1;
  *value = SC_ICOUNTER;
  return 0;
}