
#include <myReadKey.h>
#include <mySimpleComputer.h>
#include <myTerm.h>

static int
_clamp (int d, int min, int max)
{
  const int t = d < min ? min : d;
  return t > max ? max : t;
}

char *move5left = "\e[5D";
char *scpos = "\e[s";
char *rcpos = "\e[u";

int
rk_readvalue (int *value, int timeout, long *big,
              void (*printBig) (long *, char *, int), void (*pdc) (int))
{
  // In-place value editor
  // ESC - exit without saving value
  // ENTER - save valid value
  // Allowed inputs : PLUS MINUS ESC ENTER 0-9 A-Z L R

  // Assumption: SC console places the cursor in the first character of the
  // selected command.

  char val[6] = { '+', '0', '0', '0', '0', '\0' };
  int cmd;

  int pos = 0; // From 0 to 3
  int valerr = 0;
  int fin = 0;
  // Set terminal to noncanonical mode.
  // Wait for no character, do not echo or sigint
  rk_mytermregime (RK_MODE_NONCANONICAL, timeout, 0, 0, 1);

  // Input loop. Break on ESC/ENTER
  while (!fin)
    {
      // Print temporary command with cursor
      for (int i = 0; i < 5; i++)
        {
          if (i == (pos + 1))
            {
              mt_setfgcolor (BLACK);
              mt_setbgcolor (WHITE);
              write (STDOUT_FILENO, val + i, 1);
              mt_setdefaultcolor ();
            }
          else
            {
              if (valerr)
                mt_setbgcolor (RED);
              else
                mt_setdefaultcolor ();

              write (STDOUT_FILENO, val + i, 1);
            }
        }
      write (STDOUT_FILENO, move5left, 4);
      write (STDOUT_FILENO, scpos, 3);
      if (printBig)
        {
          if (valerr)
            printBig (big, val, -6);
          else
            printBig (big, val, pos + 1);
        }
      int tval = (int)strtol (val + 1, 0, 16);
      if (pdc)
        pdc ((tval & 127) + (((tval >> 8) & 127) << 7)
             + ((val[0] == '-') << 14));

      write (STDOUT_FILENO, rcpos, 3);
      valerr = 0;
      enum keys key;
      rk_readkey (&key);
      switch (key)
        {
        case KEY_RIGHT:
          pos = _clamp (++pos, 0, 3);
          break;
        case KEY_LEFT:
          pos = _clamp (--pos, 0, 3);
          break;
        case KEY_PLUS:
          val[0] = '+';
          break;
        case KEY_MINUS:
          val[0] = '-';
          break;
        case KEY_BACKSPACE:
          val[pos + 1] = '0';
          pos = _clamp (--pos, 0, 3);
          break;
        case KEY_ENTER:
          cmd = (int)strtol (val + 1, 0, 16);
          int opc = cmd >> 8;
          int cval = cmd & 0xff;
          if (opc > 0x7f || (val[0] == '+' && cval > 0x7f)
              || (val[0] == '-' && cval > 0x80))
            { // Values OK
              valerr = 1;
              break;
            }
          if (val[0] == '+')
            *value = 0 + cval + (opc << 7);
          else
            *value = 0 + cval + (opc << 7) + (1 << 14);
          fin++;
          break;
        default:
          // KEY_0 = 1
          if (key >= KEY_0 && key <= KEY_9)
            {
              val[pos + 1] = 47 + key;
              pos = _clamp (++pos, 0, 3);
            }
          if (key >= KEY_A && key <= KEY_F)
            {
              val[pos + 1] = 54 + key;
              pos = _clamp (++pos, 0, 3);
            }
          break;
        }
    }
  return *value;
}