#include <mySimpleComputer.h>
#include <myTerm.h>
#include <stdio.h>
void
printCounters (void)
{
  int IC;
  unsigned char TC;
  if (sc_icounterGet (&IC))
    {
      mt_print ("Error!\n");
      return;
    }
  if (sc_tcounterGet (&TC))
    {
      mt_print ("Error!\n");
      return;
    }
  mt_gotoXY (5, 63);
  mt_print ("T: %02d IC: ", TC);
  mt_gotoXY (5, 77);
  if (IC >> 14)
    {
      if (IC & 0x3FFF)
        {
          mt_print ("-");
          IC = (~IC & 0x3FFF) + 1;
        }
      else
        {
          mt_print ("-7F80");
          return;
        }
    }
  else
    mt_print ("+");
  mt_print ("%02X", IC >> 7 & 0b1111111);
  mt_print ("%02X", IC & 0b1111111);
}