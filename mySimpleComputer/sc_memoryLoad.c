#include "sc_variables.h"
#include <mySimpleComputer.h>

/**
 * Load memory contents from binary file
 *
 * @param filename - File name string
 *
 * @retval 0 - success
 * @retval -1 - invalid filename/IO error, memory array remains unchanged
 */
int
sc_memoryLoad (char *filename)
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
  FILE *input = fopen (strbuf, "rb");
  if (!input)
    return -1;
  int tempMemArr[SC_MEMARR_SIZE];
  int readcnt = fread (tempMemArr, sizeof (int), SC_MEMARR_SIZE, input);
  fclose (input);
  if (readcnt != SC_MEMARR_SIZE)
    return -1;
  memcpy (SC_MEMARR, tempMemArr, sizeof (int) * SC_MEMARR_SIZE);
  return 0;
}