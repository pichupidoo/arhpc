#include <mySimpleComputer.h>
#include <myTerm.h>
#include <stdio.h>
void
printDecodedCommand (int value)
{
  mt_gotoXY (17, 2);
  mt_print ("dec: %05d | ", value);
  mt_print ("oct: %05o | ", value);
  mt_print ("hex: %04X ", value);
  mt_print ("bin: ");
  for (int i = 14; i >= 0; i--)
    mt_print ("%d", (value >> i) & 1);
  mt_print ("\n");
}