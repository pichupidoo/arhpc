#include "console.h"
#include <mySimpleComputer.h>
#include <signal.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
int cell = 0;
int big[36];
int
main (int argc, char *argv[])
{
  if (argc > 1)
    {
      if (get_font (argv[1]))
        return 1;
    }
  else
    {
      if (get_font ("./console/font.bin"))
        return 1;
    }
  if (!isatty (STDIN_FILENO))
    {
      printf ("Can't reach terminal\n");
      return 1;
    }
  if (check_terminal_size ())
    return 1;
  sc_setIgnoreCache (1);
  default_state ();
  draw_interface ();
  sc_setIgnoreCache (0);
  /*signal (SIGUSR1, IRC);
  struct itimerval nval, oval;
  nval.it_interval.tv_sec = 0;
  nval.it_interval.tv_usec = 500000;
  nval.it_value.tv_sec = 1;
  nval.it_value.tv_usec = 0;
  setitimer (ITIMER_REAL, &nval, &oval);*/
  running_application ();
  mt_print ("\n");
  mt_gotoXY (50, 1);
}