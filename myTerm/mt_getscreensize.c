#include <myTerm.h>
#include <sys/ioctl.h>
int
mt_getscreensize (int *rows, int *cols)
{
  struct winsize w;
  if (ioctl (0, TIOCGWINSZ, &w) || !rows || !cols)
    return -1;

  *rows = w.ws_row;
  *cols = w.ws_col;
  return 0;
}
