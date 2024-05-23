#include "console.h"
void
printBigCell (long *big, char *str, int index)
{
  if (str[0] == '+')
    bc_printbigchar ((int *)(big + 16), 65, 9, 0, 0);
  if (str[0] == '-')
    bc_printbigchar ((int *)(big + 17), 65, 9, 0, 0);
  enum colors fg, bg;
  for (int i = 0; i < 4; i++)
    {
      if (index == i + 1)
        {
          fg = BLACK;
          bg = WHITE;
        }
      else if (index == -6)
        {
          bg = RED;
        }
      else
        {
          fg = 0;
          bg = 0;
        }
      if (str[1 + i] >= '0' && str[1 + i] <= '9')
        bc_printbigchar ((int *)(big + str[1 + i] - '0'), 73 + 8 * i, 9, fg,
                         bg);
      if (str[1 + i] >= 'A' && str[1 + i] <= 'F')
        bc_printbigchar ((int *)(big + str[1 + i] + 10 - 'A'), 73 + 8 * i, 9,
                         fg, bg);
      if (str[1 + i] >= 'a' && str[1 + i] <= 'f')
        bc_printbigchar ((int *)(big + str[1 + i] + 10 - 'a'), 73 + 8 * i, 9,
                         fg, bg);
    }
}