#include <myReadKey.h>
int
rk_mytermregime (int regime, int vtime, int vmin, int echo, int sigint)
{
  struct termios curstate;
  tcgetattr (STDIN_FILENO, &curstate);

  curstate.c_cc[VMIN] = vmin;
  curstate.c_cc[VTIME] = vtime;
  curstate.c_lflag &= ~ICANON;
  if (regime)
    curstate.c_lflag |= ICANON;

  curstate.c_lflag &= ~ECHO;
  if (echo)
    curstate.c_lflag |= ECHO;

  curstate.c_iflag &= ~BRKINT;
  if (sigint)
    curstate.c_iflag |= BRKINT;
  return tcsetattr (STDIN_FILENO, TCSAFLUSH, &curstate);
}