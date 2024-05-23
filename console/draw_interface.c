#include "console.h"
#include <mySimpleComputer.h>
#include <myTerm.h>
void
draw_interface (void)
{
  int value;
  sc_setIgnoreCache (1);
  sc_memoryGet (cell, &value);
  print_all_mem_cells_def ();
  printCell (cell, BLACK, WHITE);
  printDecodedCommand (value);
  printBigCell ();
  printAccumulator ();
  printFlags ();
  printCache ();
  printCounters ();
  printCommand ();
  sc_setIgnoreCache (0);
  mt_gotoXY (27, 1);
}