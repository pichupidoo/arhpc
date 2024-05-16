#include <myBigChars.h>
#include <myTerm.h>
int
bc_box (int x1, int y1, int x2, int y2, enum colors box_fg, enum colors box_bg,
        char *header, enum colors header_fg, enum colors header_bg)
{
  if (!header)
    return -1;
  mt_setbgcolor (box_bg);
  mt_setfgcolor (box_fg);
  mt_gotoXY (x1, y1);
  bc_printA ("l");
  mt_gotoXY (x1, ++y1);
  for (int i = 0; i < y2; i++)
    {
      bc_printA ("q");
      mt_gotoXY (x1, ++y1);
    }
  bc_printA ("k");
  mt_gotoXY (++x1, y1);
  for (int i = 0; i < x2; i++)
    {
      bc_printA ("x");
      mt_gotoXY (++x1, y1);
    }
  bc_printA ("j");
  mt_gotoXY (x1, --y1);
  for (int i = 0; i < y2; i++)
    {
      bc_printA ("q");
      mt_gotoXY (x1, --y1);
    }
  bc_printA ("m");
  mt_gotoXY (--x1, y1);
  for (int i = 0; i < x2; i++)
    {
      bc_printA ("x");
      mt_gotoXY (--x1, y1);
    }
  mt_setbgcolor (header_bg);
  mt_setfgcolor (header_fg);
  mt_gotoXY (x1, y1 + (y2 - bc_strlen (header)) / 2 + 1);
  mt_print ("%s", header);
  mt_setdefaultcolor ();
  return 0;
}