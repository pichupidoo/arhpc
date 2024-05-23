#include <myBigChars.h>
#include <string.h>
int
bc_strlen (char *s)
{
  if (!s)
    {
      return 0;
    }
  // https://stackoverflow.com/questions/7298059/how-to-count-characters-in-a-unicode-string-in-c
  size_t len = 0;
  for (; *s; ++s)
    {
      // Invert *s and count leading 0s (count leading 1s)
      int lo = 0;
      for (int k = 7; k > 0; k--)
        {
          if (*s >> k & 1)
            lo++;
          else
            break;
        }
      // if character is represented by a single byte
      if (!lo)
        {
          len++;
          continue;
        }

      for (int i = 0; i < lo - 1; i++)
        {
          s++;
          if (!(*s) || (*s & 0xC0) != 0x80)
            return len;
        }
      len++;
    }
  return len;
}