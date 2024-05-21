#include "console.h"

void
IRC (int signum)
{
  int delay_value;
  int value;
  switch (signum)
    {
    case SIGALRM: // CLK
      printFlags ();
      printCounters ();
      sc_delayGet (&delay_value);
      if (sc_regGet (SC_INVALID_COMMAND, &value) || value)
        {
          alarm (0);
          return;
        }

      if (!delay_value)
        {
        case 900:
          CU ();
          printCache ();
        }
      else
        sc_delaySet (delay_value - 1);
      printFlags ();
      printCounters ();
      break;

    case SIGUSR1: // RST
      sc_accumulatorInit ();
      sc_icounterInit ();
      sc_memoryInit ();
      sc_regInit ();
      alarm (0);
      break;
    }
}