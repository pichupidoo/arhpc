#include <myBigChars.h>
// KEEP IN MIND THAT x2, y2 ARE NOT COORS - THEY ARE WIDTH AND HEIGHT!
int
bc_box (int x1, int y1, int x2, int y2, enum colors box_fg, enum colors box_bg,
        char *header, enum colors header_fg, enum colors header_bg)
{
  if (!header || x1 < 0 || y1 < 0 || x2 < 0 || y2 < 0)
    return -1;

  mt_setfgcolor (box_fg);
  mt_setbgcolor (box_bg);
  // Horizontal lines
  mt_gotoXY (y1, x1);
  for (int i = 0; i < x2; i++)
    {
      mt_gotoXY (y1, x1 + i);
      bc_printA ("\x71");
      mt_gotoXY (y1 + y2, x1 + i);
      bc_printA ("\x71");
    };
  // Vertical lines
  for (int i = 0; i < y2; i++)
    {
      mt_gotoXY (y1 + i, x1);
      bc_printA ("\x78");
      mt_gotoXY (y1 + i, x1 + x2);
      bc_printA ("\x78");
    }
  mt_gotoXY (y1, x1);
  bc_printA ("\x6c");
  mt_gotoXY (y1, x1 + x2);
  bc_printA ("\x6b");
  mt_gotoXY (y1 + y2, x1);
  bc_printA ("\x6d");
  mt_gotoXY (y1 + y2, x1 + x2);
  bc_printA ("\x6a");
  mt_setdefaultcolor ();
  int header_len = bc_strlen (header);
  if (header_len)
    {
      // Align midpoints (Horizontal midpoint - half of the header)
      int text_offset = x2 / 2 - (header_len / 2);
      mt_setfgcolor (header_fg);
      mt_setbgcolor (header_bg);
      mt_gotoXY (y1, text_offset + x1);
      // Keep in mind it's important to use strlen and not bc_strlen here since
      // we want it to count bytes and not actual symbols

      write (STDOUT_FILENO, header, strlen (header));
      mt_setdefaultcolor ();
    }
  return 0;
}