#include <myBigChars.h>
#include <myTerm.h>
void
draw_boxes (void)
{
  mt_clrscr ();
  bc_box (1, 1, 13, 59, DEFAULT, DEFAULT, " Оперативная память ", RED,
          DEFAULT);
  bc_box (16, 1, 1, 59, DEFAULT, DEFAULT, " Редактируемая ячейка (формат) ",
          RED, WHITE);
  bc_box (1, 62, 1, 21, DEFAULT, DEFAULT, " Аккумулятор ", RED, DEFAULT);
  bc_box (1, 85, 1, 22, DEFAULT, DEFAULT, " Регистр флагов ", RED, DEFAULT);
  bc_box (4, 62, 1, 21, DEFAULT, DEFAULT, " Счётчик команд ", RED, DEFAULT);
  bc_box (4, 85, 1, 22, DEFAULT, DEFAULT, " Команда ", RED, DEFAULT);
  bc_box (7, 62, 10, 45, DEFAULT, DEFAULT,
          " Редактируемая ячейка (увеличено) ", RED, WHITE);
  bc_box (19, 1, 5, 64, DEFAULT, DEFAULT, " Кеш процессора ", GREEN, WHITE);
  bc_box (19, 67, 5, 9, DEFAULT, DEFAULT, " IN--OUT ", GREEN, WHITE);
  bc_box (19, 78, 5, 29, DEFAULT, DEFAULT, " Клавиши ", GREEN, WHITE);
}