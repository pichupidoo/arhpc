#include "console.h"
#include <myTerm.h>
#include <stdio.h>
int
check_terminal_size (void)
{
  int rows = 0, cols = 0;
  if (mt_getscreensize (&rows, &cols))
    return -1;
  if (rows < 27 || cols < 108)
    {
      printf ("Terminal is too small\n");
      printf ("Needs 27x108, but it's %dx%d\n", rows, cols);
      return -1;
    }
  return 0;
}