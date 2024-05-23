#include <myReadKey.h>
#include <mySimpleComputer.h>
#include <myTerm.h>
#include <stdio.h>
#include <string.h>
char terms[5][10];
int
printTerm (int address, int input)
{
  for (int i = 4; i > 0; i--)
    strcpy (terms[i], terms[i - 1]);
  int value = 0;
  int returned;
  if (input == 0)
    {
      returned = sc_memoryGet (address, &value);
      if (returned)
        {
          return returned;
        }
      if (value >> 14)
        {
          value = (~value & 0x3FFF) + 1;
          snprintf (terms[0], 10, "%02X> -%02X%02X", address,
                    (value >> 7) & 0x7F, value & 0x7F);
        }
      else
        snprintf (terms[0], 10, "%02X> +%02X%02X", address,
                  (value >> 7) & 0x7F, value & 0x7F);
    }
  else
    {
      returned = sc_memoryGet (address, &value);
      if (returned)
        {
          return returned;
        }
      if (value >> 14)
        {
          value = (~value & 0x3FFF) + 1;
          snprintf (terms[0], 10, "%02X< -%02X%02X", address,
                    (value >> 7) & 0x7F, value & 0x7F);
        }
      else
        snprintf (terms[0], 10, "%02X< +%02X%02X", address,
                  (value >> 7) & 0x7F, value & 0x7F);
    }
  int row = 20;
  for (int i = 4; i >= 0; i--)
    {
      mt_gotoXY (row++, 68);
      mt_print (terms[i]);
    }
  return 0;
}