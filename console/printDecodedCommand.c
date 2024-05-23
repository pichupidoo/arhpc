#include "console.h"
void
printDecodedCommand (int value)
{
  int sign;
  int command;
  int operand;
  char cmd[19] = { 0 };
  if (sc_commandDecode (value, &sign, &command, &operand))
    snprintf (cmd, 6, "[ERR]");
  else
    snprintf (cmd, 19, "%c%02x%02x", '+' + 2 * sign, command, operand);
  write (STDOUT_FILENO, cmd, 6);
}