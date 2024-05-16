#include "sc_variables.h"
#include <stdio.h>
#include <string.h>
int
sc_memoryLoad (char *filename)
{
  if (filename == NULL)
    return -1;
  FILE *file = fopen (filename, "rb");
  if (file == NULL)
    return -2;
  int tmp_SC_MEMARR[SC_MEMARR_SIZE] = { 0 };
  if (fread (tmp_SC_MEMARR, sizeof (int), SC_MEMARR_SIZE, file)
      != SC_MEMARR_SIZE)
    {
      fclose (file);
      return -3;
    }
  memcpy (SC_MEMARR, tmp_SC_MEMARR, sizeof (int) * SC_MEMARR_SIZE);
  fclose (file);
  return 0;
}