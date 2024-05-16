#include <myReadKey.h>
struct termios backup;
int
rk_mytermsave (void)
{
  return tcgetattr (STDOUT_FILENO, &backup);
}