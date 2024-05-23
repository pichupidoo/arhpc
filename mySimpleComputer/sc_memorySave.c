#include "sc_variables.h"
#include <mySimpleComputer.h>

/**
 * @brief Store memory contents in a file.
 *
 * @param filename - output file name
 *
 * @retval 0 - success
 * @retval -1 - invalid filename/IO error
 */
int
sc_memorySave (char *filename)
{
  if (!filename)
    return -1;
  char strbuf[512] = { 0 };
  int i = 0;
  while (filename[i] != '\n' && filename[i] != '\0')
    {
      strbuf[i] = filename[i];
      i++;
    }
  FILE *input = fopen (strbuf, "wb");
  if (!input)
    return -1;
  int readcnt = fwrite (SC_MEMARR, sizeof (int), SC_MEMARR_SIZE, input);
  fclose (input);
  if (readcnt != SC_MEMARR_SIZE)
    return -1;
  return 0;
}