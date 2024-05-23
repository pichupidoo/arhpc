#include <myReadKey.h>
int
rk_mytermsave (void)
{
  return tcgetattr (STDIN_FILENO, &terminal_state);
}