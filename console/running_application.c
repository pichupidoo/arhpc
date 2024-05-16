#include "console.h"
#include <myReadKey.h>
#include <mySimpleComputer.h>
#include <myTerm.h>
void
running_application ()
{
  rk_mytermsave ();
  int value;
  int running = 1;
  enum keys key;
  int throttle = 1;
  unsigned char tc = 0;
  draw_interface ();
  while (running)
    {
      rk_mytermregime (0, 1, 0, 0, 0);
      sc_regGet (SC_THROTTLE, &throttle);
      sc_tcounterGet (&tc);
      if (throttle && tc == 0)
        {
          if (key)
            draw_interface ();
          key = 0;
          rk_readkey (&key);
        }
      if (key == key_ESC)
        running = 0;
      if (key == key_RIGHT)
        {
          cell++;
          if (cell % 10 == 0)
            cell -= 10;
          if (cell == 128)
            cell = 120;
          sc_setIgnoreCache (1);
          print_all_mem_cells_def ();
          printCell (cell, BLACK, WHITE);
          sc_setIgnoreCache (0);
        }
      if (key == key_DOWN)
        {
          cell += 10;
          if (cell > 127)
            {
              cell -= 130;
              if (cell < 0)
                cell += 10;
            }
          sc_setIgnoreCache (1);
          print_all_mem_cells_def ();
          printCell (cell, BLACK, WHITE);
          sc_setIgnoreCache (0);
        }
      if (key == key_LEFT)
        {
          cell--;
          if ((cell + 1) % 10 == 0)
            {
              cell += 10;
              if (cell == 129)
                cell -= 2;
            }
          sc_setIgnoreCache (1);
          print_all_mem_cells_def ();
          printCell (cell, BLACK, WHITE);
          sc_setIgnoreCache (0);
        }
      if (key == key_UP)
        {
          cell -= 10;
          if (cell < 0)
            {
              cell += 130;
              if (cell > 127)
                cell -= 10;
            }
          sc_setIgnoreCache (1);
          print_all_mem_cells_def ();
          printCell (cell, BLACK, WHITE);
          sc_setIgnoreCache (0);
        }
      if (key == key_ENTER)
        {
          mt_gotoXY (2 + cell / 10, 2 + (cell % 10) * 6);
          mt_print (" ");
          mt_gotoXY (2 + cell / 10, 2 + (cell % 10) * 6);
          sc_setIgnoreCache (1);
          if (!rk_readvalue (&value, 100))
            sc_memorySet (cell, value);
          print_all_mem_cells_def ();
          printCell (cell, BLACK, WHITE);
          sc_setIgnoreCache (0);
        }
      if (key == key_F5)
        {
          mt_gotoXY (2, 68);
          mt_print (" ");
          mt_gotoXY (2, 68);
          if (!rk_readvalue (&value, 100))
            sc_accumulatorSet (value);
          printAccumulator ();
        }
      if (key == key_F6)
        {
          mt_gotoXY (5, 77);
          mt_print (" ");
          mt_gotoXY (5, 77);
          if (!rk_readvalue (&value, 100))
            sc_icounterSet (value);
          printCounters ();
        }
      if (key == key_L)
        {
          rk_mytermrestore ();
          mt_gotoXY (26, 1);
          mt_print ("Введите имя файла для загрузки: ");
          char filename[128];
          ssize_t size;
          size = read (STDIN_FILENO, filename, 127);
          filename[size - 1] = '\0';
          mt_gotoXY (26, 1);
          mt_print ("%*c", 108, ' ');
          mt_gotoXY (26, 1);
          if (sc_memoryLoad (filename))
            {
              mt_print ("Не удаётся загрузить память из файла \"%s\"",
                        filename);
              sleep (2);
            }
          else
            {
              mt_print ("Память из файла \"%s\" успешно загружена", filename);
              sleep (2);
            }
          mt_gotoXY (26, 1);
          mt_print ("%*c", 108, ' ');
          rk_mytermregime (0, 0, 1, 0, 0);
        }
      if (key == key_S)
        {
          rk_mytermrestore ();
          mt_gotoXY (26, 1);
          mt_print ("Введите имя файла для сохранения: ");
          char filename[128];
          ssize_t size;
          size = read (STDIN_FILENO, filename, 127);
          filename[size - 1] = '\0';
          mt_gotoXY (26, 1);
          mt_print ("%*c", 108, ' ');
          mt_gotoXY (26, 1);
          if (sc_memorySave (filename))
            {
              mt_print ("Не удаётся сохранить память в файл \"%s\"", filename);
              sleep (2);
            }
          else
            {
              mt_print ("Память успешно сохранена в файл \"%s\"", filename);
              sleep (2);
            }
          mt_gotoXY (26, 1);
          mt_print ("%*c", 108, ' ');
          rk_mytermregime (0, 0, 1, 0, 0);
        }
      if (key == key_I)
        {
          default_state ();
        }
      if (key == key_R)
        {
          sc_regSet (SC_THROTTLE, 0);
          key = 0;
        }
      if (key == key_T)
        {
          CU ();
        }
    }
  rk_mytermrestore ();
}