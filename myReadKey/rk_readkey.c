#include "rk_variables.h"
#include <myReadKey.h>

int
rk_readkey (enum keys *key)
{

  char buf_local[MIN_BUF_SIZE];
  //очистка буфера
  for (int i = 0; i < MIN_BUF_SIZE; i++)
    {
      buf_local[i] = 0;
    }
  //переключаем терминал в неканонический режим
  rk_mytermregime (0, 0, 1, 0, 1);

  //считываем первый введённый символ
  fflush (stdin); //очистка потока ввода
  read (fileno (stdin), buf_local, MIN_BUF_SIZE);

  if (!key)
    {
      return -1;
    }
  //проверка введённого символа
  if (buf_local[0] == '\033')
    { // Esc-последовательности
      switch (buf_local[1])
        {
        case '\0':
          *key = key_ESC;
          break;
        case '[':
          switch (buf_local[2])
            {
            case 'A':
              *key = key_UP;
              break;
            case 'B':
              *key = key_DOWN;
              break;
            case 'C':
              *key = key_RIGHT;
              break;
            case 'D':
              *key = key_LEFT;
              break;
            case '1':
              if (buf_local[3] == '5' && buf_local[4] == '~')
                *key = key_F5;
              if (buf_local[3] == '7' && buf_local[4] == '~')
                *key = key_F6;
              break;
            default:
              *key = key_UNDEFINED;
              break;
            }
          break;
        default:
          *key = key_UNDEFINED;
          break;
        }
    }
  else if (buf_local[0] == '\n' && buf_local[1] == '\0')
    { // клавиша Enter
      *key = key_ENTER;
    }
  else
    { // прочие клавиши
      switch (buf_local[0])
        {
        case 'l':
        case 'L':
          *key = key_L;
          break;
        case 's':
        case 'S':
          *key = key_S;
          break;
        case 'r':
        case 'R':
          *key = key_R;
          break;
        case 't':
        case 'T':
          *key = key_T;
          break;
        case 'i':
        case 'I':
          *key = key_I;
          break;
        case 'a':
        case 'A':
          *key = key_A;
          break;
        case 'b':
        case 'B':
          *key = key_B;
          break;
        case 'c':
        case 'C':
          *key = key_C;
          break;
        case 'd':
        case 'D':
          *key = key_D;
          break;
        case 'e':
        case 'E':
          *key = key_E;
          break;
        case 'f':
        case 'F':
          *key = key_F;
          break;

        case '0':
          *key = key_0;
          break;

        case '1':
          *key = key_1;
          break;
        case '2':
          *key = key_2;
          break;
        case '3':
          *key = key_3;
          break;
        case '4':
          *key = key_4;
          break;
        case '5':
          *key = key_5;
          break;
        case '6':
          *key = key_6;
          break;
        case '7':
          *key = key_7;
          break;
        case '8':
          *key = key_8;
          break;
        case '9':
          *key = key_9;
          break;

        case '+':
          *key = key_plus;
          break;
        case '-':
          *key = key_minus;
          break;

        case 0:
          *key = NOTHING_KEY;
          break;
        default:
          *key = key_UNDEFINED;
          break;
        }
    }

  return 0;
}
