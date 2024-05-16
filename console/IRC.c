#include "console.h"
#include <mySimpleComputer.h>
#include <signal.h>
#include <unistd.h>
void
IRC (int signum)
{
  if (signum == SIGUSR1)
    {
      sc_memoryInit ();
      sc_regInit ();
      sc_accumulatorInit ();
      sc_icounterSet (0);
      sc_regSet (SC_THROTTLE, 1);
    }
  if (signum == SIGALRM)
    {
      int flag;
      sc_regGet (SC_THROTTLE, &flag);
      unsigned char tcounter;
      sc_tcounterGet (&tcounter);
      if (tcounter)
        {
          sc_tcounterSet (--tcounter);
          sc_setIgnoreCache (1);
          print_all_mem_cells_def ();
          printBigCell ();
          printAccumulator ();
          printFlags ();
          printCounters ();
          printCommand ();
          printCache ();
          sc_setIgnoreCache (0);
          mt_gotoXY (27, 1);
          if (!tcounter)
            {
              sc_regSet (SC_THROTTLE, 0);
              flag = 0;
            }
          else
            {
              sc_regSet (SC_THROTTLE, 1);
              return;
            }
        }
      if (flag)
        return;
      CU ();
      sc_setIgnoreCache (1);
      print_all_mem_cells_def ();
      printBigCell ();
      printAccumulator ();
      printFlags ();
      printCounters ();
      printCommand ();
      printCache ();
      sc_setIgnoreCache (0);
      mt_gotoXY (27, 1);
    }
}