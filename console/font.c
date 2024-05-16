#include <fcntl.h>
#include <myBigChars.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
void
print_bin (int n)
{
  int j = 0;
  for (int i = 0; i < 32; i++)
    {
      printf ("%d", (n >> i) & 1);
      j++;
      if (j == 8)
        {
          printf ("\n");
          j = 0;
        }
    }
}
void
make_zero (int *big)
{
  big[0] = 0xffffffff;
  big[1] = 0xffffffff;
  for (int i = 1; i <= 8; i++)
    {
      bc_setbigcharpos (big, i, 1, 0);
      bc_setbigcharpos (big, i, 8, 0);
    }
  for (int i = 3; i <= 6; i++)
    {
      bc_setbigcharpos (big, i, 4, 0);
      bc_setbigcharpos (big, i, 5, 0);
    }
}
void
make_one (int *big)
{
  big[0] = 0;
  big[1] = 0;
  for (int i = 1; i <= 8; i++)
    {
      bc_setbigcharpos (big, i, 5, 1);
      bc_setbigcharpos (big, i, 6, 1);
    }
  bc_setbigcharpos (big, 2, 4, 1);
  bc_setbigcharpos (big, 3, 3, 1);
  bc_setbigcharpos (big, 3, 4, 1);
  bc_setbigcharpos (big, 7, 4, 1);
  bc_setbigcharpos (big, 8, 3, 1);
  bc_setbigcharpos (big, 8, 4, 1);
  bc_setbigcharpos (big, 8, 7, 1);
}
void
make_two (int *big)
{
  big[0] = 0xffffffff;
  big[1] = 0xffffffff;
  for (int i = 1; i <= 8; i++)
    {
      bc_setbigcharpos (big, i, 1, 0);
      bc_setbigcharpos (big, i, 8, 0);
    }
  for (int i = 2; i <= 5; i++)
    {
      bc_setbigcharpos (big, 3, i, 0);
      bc_setbigcharpos (big, 6, i + 2, 0);
    }
}
void
make_three (int *big)
{
  big[0] = 0xffffffff;
  big[1] = 0xffffffff;
  for (int i = 1; i <= 8; i++)
    {
      bc_setbigcharpos (big, i, 1, 0);
      bc_setbigcharpos (big, i, 8, 0);
    }
  for (int i = 3; i <= 5; i++)
    {
      bc_setbigcharpos (big, 3, i, 0);
      bc_setbigcharpos (big, 6, i, 0);
      bc_setbigcharpos (big, 4, i - 2, 0);
      bc_setbigcharpos (big, 5, i - 2, 0);
    }
}
void
make_four (int *big)
{
  big[0] = 0xffffffff;
  big[1] = 0xffffffff;
  for (int i = 1; i <= 8; i++)
    {
      bc_setbigcharpos (big, i, 1, 0);
      bc_setbigcharpos (big, i, 8, 0);
    }
  for (int i = 1; i <= 4; i++)
    {
      bc_setbigcharpos (big, i, 4, 0);
      bc_setbigcharpos (big, i, 5, 0);
      bc_setbigcharpos (big, 7, i + 1, 0);
      bc_setbigcharpos (big, 8, i + 1, 0);
    }
}
void
make_five (int *big)
{
  big[0] = 0xffffffff;
  big[1] = 0xffffffff;
  for (int i = 1; i <= 8; i++)
    {
      bc_setbigcharpos (big, i, 1, 0);
      bc_setbigcharpos (big, i, 8, 0);
    }
  for (int i = 2; i <= 5; i++)
    {
      bc_setbigcharpos (big, 3, i + 2, 0);
      bc_setbigcharpos (big, 6, i, 0);
    }
}
void
make_six (int *big)
{
  big[0] = 0xffffffff;
  big[1] = 0xffffffff;
  for (int i = 1; i <= 8; i++)
    {
      bc_setbigcharpos (big, i, 1, 0);
      bc_setbigcharpos (big, i, 8, 0);
    }
  for (int i = 4; i <= 7; i++)
    {
      bc_setbigcharpos (big, 3, i, 0);
    }
  bc_setbigcharpos (big, 6, 4, 0);
  bc_setbigcharpos (big, 6, 5, 0);
}
void
make_seven (int *big)
{
  big[0] = 0;
  big[1] = 0;
  for (int i = 2; i <= 7; i++)
    {
      bc_setbigcharpos (big, 1, i, 1);
      bc_setbigcharpos (big, 2, i, 1);
    }
  for (int i = 3; i <= 8; i++)
    {
      bc_setbigcharpos (big, i, 6, 1);
      bc_setbigcharpos (big, i, 7, 1);
    }
}
void
make_eight (int *big)
{
  big[0] = 0xffffffff;
  big[1] = 0xffffffff;
  for (int i = 1; i <= 8; i++)
    {
      bc_setbigcharpos (big, i, 1, 0);
      bc_setbigcharpos (big, i, 8, 0);
    }
  bc_setbigcharpos (big, 3, 4, 0);
  bc_setbigcharpos (big, 3, 5, 0);
  bc_setbigcharpos (big, 6, 4, 0);
  bc_setbigcharpos (big, 6, 5, 0);
}
void
make_nine (int *big)
{
  big[0] = 0xffffffff;
  big[1] = 0xffffffff;
  for (int i = 1; i <= 8; i++)
    {
      bc_setbigcharpos (big, i, 1, 0);
      bc_setbigcharpos (big, i, 8, 0);
    }
  for (int i = 2; i <= 5; i++)
    {
      bc_setbigcharpos (big, 6, i, 0);
    }
  bc_setbigcharpos (big, 3, 4, 0);
  bc_setbigcharpos (big, 3, 5, 0);
}
void
make_A (int *big)
{
  big[0] = 0xffffffff;
  big[1] = 0xffffffff;
  for (int i = 1; i <= 8; i++)
    {
      bc_setbigcharpos (big, i, 1, 0);
      bc_setbigcharpos (big, i, 8, 0);
    }
  for (int i = 4; i <= 5; i++)
    {
      bc_setbigcharpos (big, 3, i, 0);
      bc_setbigcharpos (big, 4, i, 0);
      bc_setbigcharpos (big, 7, i, 0);
      bc_setbigcharpos (big, 8, i, 0);
    }
}
void
make_B (int *big)
{
  big[0] = 0xffffffff;
  big[1] = 0xffffffff;
  for (int i = 1; i <= 8; i++)
    {
      bc_setbigcharpos (big, i, 1, 0);
      bc_setbigcharpos (big, i, 8, 0);
    }
  for (int i = 4; i <= 5; i++)
    {
      bc_setbigcharpos (big, 3, i, 0);
      bc_setbigcharpos (big, 6, i, 0);
      bc_setbigcharpos (big, i, 7, 0);
    }
}
void
make_C (int *big)
{
  big[0] = 0xffffffff;
  big[1] = 0xffffffff;
  for (int i = 1; i <= 8; i++)
    {
      bc_setbigcharpos (big, i, 1, 0);
      bc_setbigcharpos (big, i, 8, 0);
    }
  for (int i = 4; i <= 7; i++)
    {
      bc_setbigcharpos (big, 3, i, 0);
      bc_setbigcharpos (big, 4, i, 0);
      bc_setbigcharpos (big, 5, i, 0);
      bc_setbigcharpos (big, 6, i, 0);
    }
}
void
make_D (int *big)
{
  big[0] = 0xffffffff;
  big[1] = 0xffffffff;
  for (int i = 1; i <= 8; i++)
    {
      bc_setbigcharpos (big, i, 1, 0);
      bc_setbigcharpos (big, i, 8, 0);
    }
  for (int i = 3; i <= 6; i++)
    {
      bc_setbigcharpos (big, i, 4, 0);
    }
  bc_setbigcharpos (big, 4, 5, 0);
  bc_setbigcharpos (big, 5, 5, 0);
  bc_setbigcharpos (big, 1, 7, 0);
  bc_setbigcharpos (big, 8, 7, 0);
}
void
make_E (int *big)
{
  big[0] = 0xffffffff;
  big[1] = 0xffffffff;
  for (int i = 1; i <= 8; i++)
    {
      bc_setbigcharpos (big, i, 1, 0);
      bc_setbigcharpos (big, i, 8, 0);
    }
  for (int i = 4; i <= 7; i++)
    {
      bc_setbigcharpos (big, 3, i, 0);
      bc_setbigcharpos (big, 6, i, 0);
    }
}
void
make_F (int *big)
{
  big[0] = 0xffffffff;
  big[1] = 0xffffffff;
  for (int i = 1; i <= 8; i++)
    {
      bc_setbigcharpos (big, i, 1, 0);
      bc_setbigcharpos (big, i, 8, 0);
    }
  for (int i = 4; i <= 7; i++)
    {
      bc_setbigcharpos (big, 3, i, 0);
      bc_setbigcharpos (big, 6, i, 0);
      bc_setbigcharpos (big, 7, i, 0);
      bc_setbigcharpos (big, 8, i, 0);
    }
}
void
make_plus (int *big)
{
  big[0] = 0;
  big[1] = 0;
  for (int i = 1; i <= 8; i++)
    {
      bc_setbigcharpos (big, i, 4, 1);
      bc_setbigcharpos (big, i, 5, 1);
    }
  for (int i = 2; i <= 7; i++)
    {
      bc_setbigcharpos (big, 4, i, 1);
      bc_setbigcharpos (big, 5, i, 1);
    }
}
void
make_minus (int *big)
{
  big[0] = 0;
  big[1] = 0;
  for (int i = 2; i <= 7; i++)
    {
      bc_setbigcharpos (big, 4, i, 1);
      bc_setbigcharpos (big, 5, i, 1);
    }
}
int
main ()
{
  int *big = malloc (36 * sizeof (int));
  if (!big)
    return -1;
  int index = 0;
  make_zero (big + index);
  index += 2;
  make_one (big + index);
  index += 2;
  make_two (big + index);
  index += 2;
  make_three (big + index);
  index += 2;
  make_four (big + index);
  index += 2;
  make_five (big + index);
  index += 2;
  make_six (big + index);
  index += 2;
  make_seven (big + index);
  index += 2;
  make_eight (big + index);
  index += 2;
  make_nine (big + index);
  index += 2;
  make_A (big + index);
  index += 2;
  make_B (big + index);
  index += 2;
  make_C (big + index);
  index += 2;
  make_D (big + index);
  index += 2;
  make_E (big + index);
  index += 2;
  make_F (big + index);
  index += 2;
  make_plus (big + index);
  index += 2;
  make_minus (big + index);
  int fd = open ("font.bin", O_CREAT | O_WRONLY | O_TRUNC, 0644);
  if (fd == -1)
    {
      printf ("1\n");
      return -1;
    }
  if (bc_bigcharwrite (fd, big, 18))
    {
      printf ("2\n");
      return -1;
    }
  close (fd);
  free (big);
}