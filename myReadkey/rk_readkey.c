#include <myReadKey.h>
int
rk_readkey (enum keys *key)
{
  char a[7] = { 0 };
  read (STDIN_FILENO, a, 1);
  int ret;
  switch (*a)
    {
    case 'l':
    case 'L':
      *key = KEY_L;
      break;
    case 's':
    case 'S':
      *key = KEY_S;
      break;
    case 'i':
    case 'I':
      *key = KEY_I;
      break;
    case 'r':
    case 'R':
      *key = KEY_R;
      break;
    case 't':
    case 'T':
      *key = KEY_T;
      break;
    case '\n':
      *key = KEY_ENTER;
      break;
    case '0':
      *key = KEY_0;
      break;
    case '1':
      *key = KEY_1;
      break;
    case '2':
      *key = KEY_2;
      break;
    case '3':
      *key = KEY_3;
      break;
    case '4':
      *key = KEY_4;
      break;
    case '5':
      *key = KEY_5;
      break;
    case '6':
      *key = KEY_6;
      break;
    case '7':
      *key = KEY_7;
      break;
    case '8':
      *key = KEY_8;
      break;
    case '9':
      *key = KEY_9;
      break;
    case 'a':
    case 'A':
      *key = KEY_A;
      break;
    case 'b':
    case 'B':
      *key = KEY_B;
      break;
    case 'c':
    case 'C':
      *key = KEY_C;
      break;
    case 'd':
    case 'D':
      *key = KEY_D;
      break;
    case 'e':
    case 'E':
      *key = KEY_E;
      break;
    case 'f':
    case 'F':
      *key = KEY_F;
      break;
    case '+':
      *key = KEY_PLUS;
      break;
    case '-':
      *key = KEY_MINUS;
      break;
    case '\177':
      *key = KEY_BACKSPACE;
      break;
    case '\e':
      ret = read (STDIN_FILENO, a + 1, 1);
      if (!ret)
        // Just \e
        *key = KEY_ESC;
      else
        {
          read (STDIN_FILENO, a + 2, 1);
          if (!strncmp (a, "\e[A", 3))
            *key = KEY_UP;
          else if (!strncmp (a, "\e[B", 3))
            *key = KEY_DOWN;
          else if (!strncmp (a, "\e[C", 3))
            *key = KEY_RIGHT;
          else if (!strncmp (a, "\e[D", 3))
            *key = KEY_LEFT;
          else
            {
              read (STDIN_FILENO, a + 3, 1);
              if (!strncmp (a, "\e[15", strlen ("\e[15")))
                *key = KEY_F5;
              else if (!strncmp (a, "\e[17", strlen ("\e[15")))
                *key = KEY_F6;
              else
                *key = KEY_UNKNOWN;
            }
        }

      break;
    default:
      *key = KEY_UNKNOWN;
      break;
    }
  return 0;
}
