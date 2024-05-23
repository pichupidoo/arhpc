#include "console.h"

void
printCell (int address, enum colors fg, enum colors bg)
{
  // Home at (1;1), 10 cells per line
  // address = 0 1 2 3 4 5 6 7 8 9 nl
  // +ffff +ffff
  // row = address div 10
  // col = adress mod 10
  int row = (address / 10) + 2;
  int col = (address % 10) * 6 + 2; // +ffff_ is 6 chars long

  mt_setfgcolor (fg);
  mt_setbgcolor (bg);
  int value;
  sc_memoryGet (address, &value);
  mt_gotoXY (row, col);
  printDecodedCommand (value);
  mt_setdefaultcolor ();
  bc_printA (" ");
}