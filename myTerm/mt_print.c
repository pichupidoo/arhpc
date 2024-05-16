#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>
int
mt_print (char *format, ...)
{
  int buffer_size = 128;
  char buffer[buffer_size];
  size_t length = 0;
  va_list arguments;
  va_start (arguments, format);
  length = vsnprintf (buffer, buffer_size, format, arguments);
  va_end (arguments);
  if (write (STDOUT_FILENO, buffer, length))
    return -1;
  return 0;
}