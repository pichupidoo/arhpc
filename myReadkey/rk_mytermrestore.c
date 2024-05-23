#include <myReadKey.h>
int
rk_mytermrestore (void)
{
  return tcsetattr (STDIN_FILENO, TCSANOW, &terminal_state);
}