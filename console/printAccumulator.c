#include <mySimpleComputer.h>
#include <myTerm.h>
#include <stdio.h>
void
printAccumulator (void)
{
  int value;
  if (sc_accumulatorGet (&value))
    {
      mt_print ("Error!\n");
      return;
    }
  mt_gotoXY (2, 64);
  mt_print ("sc: ");
  if (value >> 14)
    {
      if (value & 0x3FFF)
        {
          mt_print ("-");
          value = (~value & 0x3FFF) + 1;
        }
      else
        {
          mt_print ("-7F80");
          mt_print (" hex: %04X", value);
          return;
        }
    }
  else
    mt_print ("+");
  mt_print ("%02X", value >> 7 & 0b1111111);
  mt_print ("%02X", value & 0b1111111);
  sc_accumulatorGet (&value);
  mt_print (" hex: %04X", value);
}