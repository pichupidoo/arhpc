#include "console.h"
void
printDecodedCommandBlock (int value)
{
  mt_gotoXY (17, 2);
  char s[256];
  char a[16] = { 0 };
  for (int i = 15; i >= 0; i--)
    {
      a[15 - i] = ((value >> i) & 1) + 0x30;
    }
  int len = snprintf (s, 255, "dec: %5d | oct: %5o | hex: %4x\tbin: ", value,
                      value, value);
  write (STDOUT_FILENO, s, len);
  write (STDOUT_FILENO, a, 16);

  mt_gotoXY (5, 91);
  int sign;
  int op;
  int opd;
  int ret = sc_commandDecode (value, &sign, &op, &opd);
  char str[512];
  int b;
  if (ret)
    b = snprintf (str, 512, "+ FF : FF");
  else
    {
      if (!sign)
        b = snprintf (str, 512, "+ %02x : %02x", op, opd);
      else
        b = snprintf (str, 512, "- %02x : %02x", op, opd);
    }
  write (STDOUT_FILENO, str, b);
}