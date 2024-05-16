#include <string.h>
void
mt_itoa (int n, char *buf)
{
  int i = 0;
  if (n == 0)
    {
      buf[i++] = '0';
    }
  else
    {
      while (n != 0)
        {
          int digit = n % 10;
          buf[i++] = digit + '0';
          n /= 10;
        }
    }
  buf[i] = '\0';
  int len = strlen (buf);
  for (int j = 0; j < len / 2; ++j)
    {
      char temp = buf[j];
      buf[j] = buf[len - j - 1];
      buf[len - j - 1] = temp;
    }
}