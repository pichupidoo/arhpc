#include "sc_variables.h"
int
sc_memoryInit (void)
{
  for (int i = 0; i < SC_MEMARR_SIZE; i++)
    SC_MEMARR[i] = 0;
  return 0;
}