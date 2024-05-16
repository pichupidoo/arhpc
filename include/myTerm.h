#pragma once
enum colors
{
  BLACK,
  RED,
  GREEN,
  YELLOW,
  BLUE,
  PURPLE,
  CYAN,
  WHITE,
  DEFAULT
};
int mt_clrscr (void);
int mt_delline (void);
int mt_getscreensize (int *rows, int *cols);
int mt_gotoXY (int x, int y);
int mt_setbgcolor (enum colors color);
int mt_setcursorvisible (int value);
int mt_setdefaultcolor (void);
int mt_setfgcolor (enum colors color);
int mt_print (char *format, ...);