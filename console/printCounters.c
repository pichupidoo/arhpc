#include "console.h"
void
printCounters (void)
{
  int value;
  mt_gotoXY (5, 65);
  sc_icounterGet (&value);
  char buf[40];
  int delay;
  sc_delayGet (&delay);
  int len = snprintf (buf, 40, "T: %02d \tIC: ", delay);
  write (STDOUT_FILENO, buf, len);
  printDecodedCommand (value);
  int mg_value;
  sc_memoryGet (value, &mg_value);
  printDecodedCommandBlock (mg_value);
}