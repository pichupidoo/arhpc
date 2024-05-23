#include "console.h"
#include <mySimpleComputer.h>
void
default_state (void)
{
  cell = 0;
  sc_accumulatorSet (0);
  sc_icounterSet (0);
  draw_boxes ();
  sc_setIgnoreCache (1);
  sc_memoryInit ();
  sc_setIgnoreCache (0);
  sc_regInit ();
  sc_cacheInit ();
  printFlags ();
  printAccumulator ();
  printCounters ();
  printInfo ();
}