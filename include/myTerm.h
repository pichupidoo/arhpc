#pragma once
#include <stdio.h>
#include <unistd.h>
enum colors
{
  BLACK = 30,
  RED,
  GREEN,
  YELLOW,
  BLUE,
  MAGENTA,
  CYAN,
  WHITE,
};
int mt_clrscr (void);
int mt_gotoXY (int row, int col);
int mt_getscreensize (int *rows, int *cols);
int mt_setfgcolor (enum colors);
int mt_setbgcolor (enum colors);
int mt_setdefaultcolor (void);
int mt_setcursorvisible (int value);
int mt_delline (void);