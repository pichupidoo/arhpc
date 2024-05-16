#include <mySimpleComputer.h>
#include <myTerm.h>
void
printCommand (void)
{
  int value, cell_number;
  sc_icounterGet (&cell_number);
  mt_gotoXY (5, 90);
  if (cell_number < 0 || cell_number > 127)
    {
      mt_print ("! FF : FF");
      return;
    }
  sc_memoryGet (cell_number, &value);
  if (value >> 14 > 0)
    mt_print ("- ");
  else
    mt_print ("+ ");
  mt_print ("%02X : %02X", (value >> 7) & 0x7F, value & 0x7F);
}