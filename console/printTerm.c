#include "console.h"
static int valueReg[6];
static int dirReg[6];
static int addrReg[6];

void
printTerm (int address)
{
  // Push all entries back
  for (int i = 5; i >= 0; i--)
    {
      valueReg[i + 1] = valueReg[i];
      dirReg[i + 1] = dirReg[i];
      addrReg[i + 1] = addrReg[i];
    }

  addrReg[0] = address;
  dirReg[0] = 0;
  int value;
  sc_cacheGet (address, &value);
  valueReg[0] = value;
  for (int i = 4; i >= 0; i--)
    {
      mt_gotoXY (20 + i, 66);
      char buf[16];
      if (dirReg[i])
        snprintf (buf, 16, "%02x< ", addrReg[i]);
      else
        snprintf (buf, 16, "%02x> ", addrReg[i]);
      write (STDOUT_FILENO, buf, strlen (buf));
      printDecodedCommand (valueReg[i]);
    }
}

int
inputTerm (int address)
{
  // Push all entries back
  for (int i = 5; i >= 0; i--)
    {
      valueReg[i + 1] = valueReg[i];
      dirReg[i + 1] = dirReg[i];
      addrReg[i + 1] = addrReg[i];
    }

  addrReg[0] = address;
  dirReg[0] = 1;
  int value;
  mt_gotoXY (20, 66);
  char buf[16];
  snprintf (buf, 16, "%02x< ", addrReg[0]);
  write (STDOUT_FILENO, buf, strlen (buf));
  rk_readvalue (&value, 1, NULL, NULL, NULL);
  valueReg[0] = value;
  // sc_memorySet (address, value);
  for (int i = 4; i >= 0; i--)
    {
      mt_gotoXY (20 + i, 66);
      char buf[16];
      if (dirReg[i])
        snprintf (buf, 16, "%02x< ", addrReg[i]);
      else
        snprintf (buf, 16, "%02x> ", addrReg[i]);
      write (STDOUT_FILENO, buf, strlen (buf));
      printDecodedCommand (valueReg[i]);
    }
  return value;
}