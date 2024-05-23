#include <fcntl.h>
#include <myBigChars.h>

int
main (void)
{
  unsigned long a[18];
  // спасибо ув. DSG888 за предоставленный шрифт
  // верхняя половина фигуры - второй байт...
  // https://cs5.pikabu.ru/images/previews_comm/2014-10_3/14133944305572.jpg

  a[0] = 17001088593312768;
  a[1] = 13563782608990208;
  a[2] = 35468055689575424;
  a[3] = 35571943467941376;
  a[4] = 27127694167008768;
  a[5] = 17522093218496000;
  a[6] = 8481761581472768;
  a[7] = 1702147890642432;
  a[8] = 17001087888669696;
  a[9] = 16994466122841088;
  a[10] = 18650201816448000;
  a[11] = 17524300835864064;
  a[12] = 16961074997902336;
  a[13] = 17524300902972928;
  a[14] = 35468056792825344;
  a[15] = 565415298366976;
  a[16] = 6782331001509888;
  a[17] = 543279808512;
  int fd = open ("font.bin", O_CREAT | O_TRUNC | O_SYNC | O_RDWR, 0777);
  if (fd == -1)
    {
      perror ("could not open font.bin:");
      return 1;
    }
  else
    for (int i = 0; i < 18; i++)
      if (bc_bigcharwrite (fd, (int *)a, 18) == -1)
        perror ("could not write font to font.bin:");
  close (fd);
  return 0;
}