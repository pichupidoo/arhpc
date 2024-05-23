#include "console.h"

void
printAccumulator (void)
{
  int value;
  mt_gotoXY (2, 64);
  sc_accumulatorGet (&value);
  char sc[] = "sc: ";
  write (STDOUT_FILENO, sc, strlen (sc));
  printDecodedCommand (value);
  char hexval[40];
  int len = snprintf (hexval, 40, " hex: %04x", value);
  write (STDOUT_FILENO, hexval, len);
}