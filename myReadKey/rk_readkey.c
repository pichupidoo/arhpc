#include <myReadKey.h>
int
rk_readkey (enum keys *key)
{
  char buf[16];
  ssize_t n;
  n = read (STDIN_FILENO, buf, 15);
  if (n == 0)
    return -1;
  buf[n] = '\0';
  if (strcmp (buf, "l") == 0)
    *key = key_L;
  else if (strcmp (buf, "s") == 0)
    *key = key_S;
  else if (strcmp (buf, "i") == 0)
    *key = key_I;
  else if (strcmp (buf, "r") == 0)
    *key = key_R;
  else if (strcmp (buf, "t") == 0)
    *key = key_T;
  else if (strcmp (buf, "\e[15~") == 0)
    *key = key_F5;
  else if (strcmp (buf, "\e[17~") == 0)
    *key = key_F6;
  else if (strcmp (buf, "\e") == 0)
    *key = key_ESC;
  else if (strcmp (buf, "\n") == 0)
    *key = key_ENTER;
  else if (strcmp (buf, "\e[A") == 0)
    *key = key_UP;
  else if (strcmp (buf, "\e[C") == 0)
    *key = key_RIGHT;
  else if (strcmp (buf, "\e[B") == 0)
    *key = key_DOWN;
  else if (strcmp (buf, "\e[D") == 0)
    *key = key_LEFT;
  else if (strcmp (buf, "0") == 0)
    *key = key_0;
  else if (strcmp (buf, "1") == 0)
    *key = key_1;
  else if (strcmp (buf, "2") == 0)
    *key = key_2;
  else if (strcmp (buf, "3") == 0)
    *key = key_3;
  else if (strcmp (buf, "4") == 0)
    *key = key_4;
  else if (strcmp (buf, "5") == 0)
    *key = key_5;
  else if (strcmp (buf, "6") == 0)
    *key = key_6;
  else if (strcmp (buf, "7") == 0)
    *key = key_7;
  else if (strcmp (buf, "8") == 0)
    *key = key_8;
  else if (strcmp (buf, "9") == 0)
    *key = key_9;
  else if (strcmp (buf, "a") == 0)
    *key = key_A;
  else if (strcmp (buf, "b") == 0)
    *key = key_B;
  else if (strcmp (buf, "c") == 0)
    *key = key_C;
  else if (strcmp (buf, "d") == 0)
    *key = key_D;
  else if (strcmp (buf, "e") == 0)
    *key = key_E;
  else if (strcmp (buf, "f") == 0)
    *key = key_F;
  else if (strcmp (buf, "+") == 0)
    *key = key_plus;
  else if (strcmp (buf, "-") == 0)
    *key = key_minus;
  return 0;
}