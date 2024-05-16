#include <myReadKey.h>
#include <myTerm.h>
#include <stdlib.h>
int
rk_readvalue (int *value, int timeout)
{
  rk_mytermregime (0, timeout, 0, 0, 0);
  char buf[16] = "";
  int is_completed = 0;
  int n_symbol = 0;
  while (!is_completed)
    {
      enum keys key = key_UNDEFINED;
      if (rk_readkey (&key))
        return -1;
      if (key == key_ESC)
        return -1;
      if (n_symbol == 0)
        {
          if (key == key_plus)
            {
              buf[0] = '+';
              mt_print ("+");
              n_symbol++;
            }
          else if (key == key_minus)
            {
              buf[0] = '-';
              mt_print ("-");
              n_symbol++;
            }
        }
      else
        {
          if (key >= key_0 && key <= key_9)
            {
              buf[n_symbol] = key - key_0 + '0';
              mt_print ("%c", key - key_0 + '0');
              n_symbol++;
            }
          else if (key >= key_A && key <= key_F)
            {
              buf[n_symbol] = key - key_A + 'A';
              mt_print ("%c", key - key_A + 'A');
              n_symbol++;
            }
        }
      key = key_UNDEFINED;
      if (n_symbol == 5)
        is_completed++;
    }
  buf[5] = '\0';
  int sign = buf[0] == '+' ? 0 : 1;
  int right_value = strtol (&buf[3], NULL, 16);
  buf[3] = '\0';
  int left_value = strtol (&buf[1], NULL, 16);
  if (sign && right_value > 127 && left_value > 126)
    {
      *value = 0b100000000000000;
      return 0;
    }
  right_value = right_value > 127 ? 127 : right_value;
  left_value = left_value > 127 ? 127 << 7 : left_value << 7;
  *value = 0;
  *value |= (sign << 14) | right_value | left_value;
  if (sign)
    *value = ((~(*value - 1) & 0x3FFF) | (sign << 14));
  if (sign && !right_value && !left_value)
    *value = 0;
  return 0;
}