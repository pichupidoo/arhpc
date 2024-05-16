int
sc_commandValidate (int command)
{
  if (command < 0 || command > 32767)
    return 1;
  int mask = 0x7f;
  command = (command >> 7) & mask;
  if (command != 0 && command != 1 && command != 10 && command != 20
      && command != 21 && command != 30 && command != 31 && command != 32
      && command != 33 && command != 40 && command != 41 && command != 42
      && command != 43 && command < 51 && command > 67)
    return 1;
  return 0;
}