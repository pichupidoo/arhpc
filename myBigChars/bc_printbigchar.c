#include <myBigChars.h>
#include <myTerm.h>
int
bc_printbigchar (int *big, int x, int y, enum colors fg, enum colors bg)
{
  if (!big)
    return -1;
  mt_setfgcolor (fg);
  mt_setbgcolor (bg);
  for (int i = 0; i < 8; i++)
    {
      for (int j = 0; j < 8; j++)
        {
          int value;
          mt_gotoXY (x + i, y + j);
          bc_getbigcharpos (big, i + 1, j + 1, &value);
          if (value)
            bc_printA ("a");
          else
            mt_print (" ");
        }
    }
  mt_setdefaultcolor ();
  return 0;
}