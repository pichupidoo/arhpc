#include <myBigChars.h>
int
bc_printbigchar (int big[2], int x, int y, enum colors fg, enum colors bg)
{
  if (!big)
    return -1;
  // Evil pointer hack
  __uint8_t *bigchar = (__uint8_t *)big;
  mt_setbgcolor (bg);
  mt_setfgcolor (fg);
  for (int i = 0; i < 8; i++)
    {
      for (int j = 0; j < 8; j++)
        {
          mt_gotoXY (y + i, x + j);
          (bigchar[i] >> j) & 1 ? bc_printA ("\x61") : bc_printA (" ");
        }
    }
  mt_setdefaultcolor ();
  return 0;
}