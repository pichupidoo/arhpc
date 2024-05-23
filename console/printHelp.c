#include "console.h"

void
printHelp (void)
{
  char buf[5][128];
  int len[5];
  len[0] = snprintf (buf[0], 128, "l - load  s - save  i - reset");
  len[1] = snprintf (buf[1], 128, "r - run   t - step");
  len[2] = snprintf (buf[2], 128, "ESC - выход");
  len[3] = snprintf (buf[3], 128, "F5 - accumulator");
  len[4] = snprintf (buf[4], 128, "F6 - instruction counter");
  for (int i = 0; i < 5; i++)
    {
      mt_gotoXY (20 + i, 77);
      write (STDOUT_FILENO, buf[i], len[i]);
    }
}