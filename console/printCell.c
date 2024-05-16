#include "mySimpleComputer.h"
#include "myTerm.h"
#include <stdio.h>
void
printCell (int address, enum colors fg, enum colors bg)
{
  int value;
  if (sc_memoryGet (address, &value) == -1)
    return;
  mt_setbgcolor (bg);
  mt_setfgcolor (fg);
  int row = 1, col = 0;
  col = address % 10;
  int tmp_address = address;
  while (tmp_address > 9)
    {
      tmp_address -= 10;
      row++;
    }
  mt_gotoXY (row + 1, col * 6 + 2);
  if (value >> 14)
    {
      mt_print ("-");
      value = (~value & 0x3FFF) + 1;
    }
  else
    mt_print ("+");
  mt_print ("%02X", value >> 7 & 0b1111111);
  mt_print ("%02X", value & 0b1111111);
  if (value >> 14 && (value & 0x3FFF) == 0)
    {
      mt_gotoXY (row + 1, col * 6 + 2);
      mt_print ("-7F80");
    }
  mt_setdefaultcolor ();
}