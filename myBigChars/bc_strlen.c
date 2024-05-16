int
bc_strlen (char *str)
{
  int length = 0;
  while (*str != '\0')
    {
      length++;
      if ((*str & 128) > 0)
        str += 2;
      else
        str++;
    }
  return length;
}