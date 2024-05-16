#include <sys/ioctl.h>
#include <unistd.h>
int
mt_getscreensize (int *rows, int *cols)
{
  struct winsize ws;
  if (ioctl (STDOUT_FILENO, TIOCGWINSZ, &ws))
    return -1;
  *rows = ws.ws_row;
  *cols = ws.ws_col;
  return 0;
}