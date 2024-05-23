#include "console.h"
#include <myBigChars.h>
#include <mySimpleComputer.h>
void
printBigCell (void)
{
  int value;
  sc_memoryGet (cell, &value);
  if (value >> 14)
    {
      bc_printbigchar (&big[34], 9, 64, DEFAULT, DEFAULT);
      value = ((~value & 0x3FFF) + 1) | 0x4000;
    }
  else
    bc_printbigchar (&big[32], 9, 64, DEFAULT, DEFAULT);
  if ((value >> 14) && ((value & 0x3FFF) == 0))
    {
      bc_printbigchar (&big[14], 9, 72, DEFAULT, DEFAULT);
      bc_printbigchar (&big[30], 9, 80, DEFAULT, DEFAULT);
      bc_printbigchar (&big[16], 9, 88, DEFAULT, DEFAULT);
      bc_printbigchar (&big[0], 9, 96, DEFAULT, DEFAULT);
    }
  else
    {
      bc_printbigchar (&big[((value >> 11) & 0b111) * 2], 9, 72, DEFAULT,
                       DEFAULT);
      bc_printbigchar (&big[((value >> 7) & 0b1111) * 2], 9, 80, DEFAULT,
                       DEFAULT);
      bc_printbigchar (&big[((value >> 4) & 0b111) * 2], 9, 88, DEFAULT,
                       DEFAULT);
      bc_printbigchar (&big[(value & 0b1111) * 2], 9, 96, DEFAULT, DEFAULT);
    }
  mt_gotoXY (17, 64);
  mt_setfgcolor (BLUE);
  mt_print ("Номер редактируемой ячейки: %03d", cell);
  mt_setfgcolor (DEFAULT);
}