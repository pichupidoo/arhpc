#include "console.h"
void
print_all_mem_cells_def (void)
{
  for (int i = 0; i < 128; i++)
    printCell (i, DEFAULT, DEFAULT);
}