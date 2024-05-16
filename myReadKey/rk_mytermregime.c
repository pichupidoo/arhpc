#include <myReadKey.h>
int
rk_mytermregime (int regime, int vtime, int vmin, int echo, int sigint)
{
  struct termios term;
  if (tcgetattr (STDIN_FILENO, &term))
    return -1;
  if (regime)
    term.c_lflag |= ICANON;
  else
    term.c_lflag &= ~ICANON;
  if (echo)
    term.c_lflag |= ECHO;
  else
    term.c_lflag &= ~ECHO;
  if (sigint)
    term.c_lflag |= ISIG;
  else
    term.c_lflag &= ~ISIG;
  term.c_cc[VTIME] = vtime;
  term.c_cc[VMIN] = vmin;
  return tcsetattr (STDIN_FILENO, TCSANOW, &term);
}