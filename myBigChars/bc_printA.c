#include <myBigChars.h>
#include <unistd.h>
int
bc_printA (char *str)
{
  if (!str)
    return 0;
  char s[40] = { 0 };
  // set ext mode
  int len = snprintf (s, 39, "\33(0");
  write (STDOUT_FILENO, s, len);
  // print user input
  write (STDOUT_FILENO, str, strlen (str));
  // unset ext mode
  len = snprintf (s, 39, "\33(B");
  write (STDOUT_FILENO, s, len);
  return 0;
}
