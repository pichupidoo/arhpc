#include "console.h"

void
printFlags (void)
{
  mt_gotoXY (2, 91);
  int flags[5] = { 'E', 'T', 'M', '0', 'P' };
  char buf[40] = { 0 };
  int len = 0;
  for (int i = 4; i >= 0; i--)
    {
      int value = 0;
      sc_regGet (1 << i, &value);
      if (value)
        len += snprintf (buf + 8 - 2 * i, 3, "%c ", flags[i]);
      else
        len += snprintf (buf + 8 - 2 * i, 3, "_ ");
    }
  write (STDOUT_FILENO, buf, len);
}