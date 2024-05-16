#include "mySimpleComputer.h"
#include "myTerm.h"
#include <stdio.h>
void
printCache (void)
{
  int cacheline[10];
  int line_size;
  int address;
  for (int line = 0; line < 5; line++)
    {
      address = sc_cachelineGet (line, cacheline);
      if (address != -1)
        {
          line_size = address == 120 ? 8 : 10;
          mt_gotoXY (20 + line, 2);
          mt_print ("%d: "
                    " ",
                    address);
          for (int i = 0; i < line_size; i++)
            {
              mt_gotoXY (20 + line, i * 6 + 7);
              if (cacheline[i] >> 14)
                {
                  mt_print ("-");
                  cacheline[i] = (~cacheline[i] & 0x3FFF) + 1;
                }
              else
                mt_print ("+");
              mt_print ("%02X", cacheline[i] >> 7 & 0b1111111);
              mt_print ("%02X", cacheline[i] & 0b1111111);
            }
        }
    }
}