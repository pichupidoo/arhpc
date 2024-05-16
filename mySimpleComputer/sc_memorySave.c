#include "sc_variables.h"
#include <stdio.h>
int
sc_memorySave (char *filename)
{
  if (filename == NULL)
    return -1;
  FILE *file = fopen (filename, "wb");
  if (file == NULL)
    return -1;
  if (fwrite (SC_MEMARR, sizeof (*SC_MEMARR), SC_MEMARR_SIZE, file)
      != SC_MEMARR_SIZE)
    {
      fclose (file);
      return -1;
    }
  fclose (file);
  return 0;
}