#include "mt_itoa.h"
#include <string.h>
#include <unistd.h>
int
mt_gotoXY (int x, int y)
{
  char buf[32];
  char *ptr = buf;
  const char *esc = "\033[";
  const char *sep = ";";
  const char *end = "H";
  strcpy (ptr, esc);
  ptr += strlen (esc);
  char x_str[16];
  mt_itoa (x, x_str);
  strcpy (ptr, x_str);
  ptr += strlen (x_str);
  *ptr++ = sep[0];
  char y_str[16];
  mt_itoa (y, y_str);
  strcpy (ptr, y_str);
  ptr += strlen (y_str);
  *ptr++ = end[0];
  if (write (STDOUT_FILENO, buf, ptr - buf) == -1)
    {
      return -1;
    }
  return 0;
}