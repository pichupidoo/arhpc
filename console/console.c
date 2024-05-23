#include "console.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
static long big[18] = { 0 };
static int mem_cp_x = 0;
static int mem_cp_y = 0;

void
prompt (char *str)
{
  mt_gotoXY (27, 1);
  const char *killline = "\x1B[2K\r";
  write (STDOUT_FILENO, killline, 5);
  write (STDOUT_FILENO, str, strlen (str));
  mt_gotoXY (27, 1 + bc_strlen (str));
}

void
print_memarr (int memcp)
{
  for (int i = 0; i < SC_MEMARR_SIZE; i++)
    {
      if (memcp == i)
        {
          char memcellstr[9];
          int sign;
          int command;
          int operand;
          int value;
          sc_memoryGet (i, &value);
          sc_commandDecode (value, &sign, &command, &operand);
          snprintf (memcellstr, 9, "%c%02x%02x", '+' + 2 * sign, command,
                    operand);
          printBigCell (big, memcellstr, -1);

          printDecodedCommandBlock (value);

          printCell (i, BLACK, WHITE);
        }
      else
        printCell (i, WHITE, BLACK);
    }
}

void
draw ()
{
  mt_clrscr ();
  bc_box (63, 7, 43, 11, 0, 0, " Редактируемая ячейка (увеличено) ", RED,
          WHITE);

  bc_box (1, 1, 61, 14, 0, 0, " Оперативная память ", RED, 0);

  print_memarr (mem_cp_x + mem_cp_y * 10);
  // char a[4] = { '\xf2', '\xf2', '\xf2', '\0' };
  bc_box (1, 16, 61, 2, 0, 0, " Редактируемая ячейка (формат) ", RED, WHITE);

  bc_box (63, 1, 21, 2, 0, 0, " Аккумулятор ", RED, 0);
  printAccumulator ();
  bc_box (63, 4, 21, 2, 0, 0, " Счетчик команд ", RED, 0);
  printCounters ();
  bc_box (85, 1, 21, 2, 0, 0, " Флаги ", RED, 0);
  bc_box (85, 4, 21, 2, 0, 0, " Команда ", RED, 0);
  printFlags ();

  bc_box (65, 19, 10, 6, 0, 0, " I/O ", GREEN, WHITE);
  bc_box (76, 19, 30, 6, 0, 0, " Клавиши ", GREEN, WHITE);
  bc_box (1, 19, 63, 6, 0, 0, " Кэш процессора ", GREEN, WHITE);
  printCache ();
  printHelp ();
}

int
main (int argc, char *argv[])
{

  rk_mytermsave ();
  int rows, cols;
  mt_getscreensize (&rows, &cols);
  if (cols < 106 || rows < 28)
    {
      printf ("screen size is too small\n");
      return 1;
    }
  // Init font
  char *path = "./font.bin";
  if (argc >= 2)
    path = argv[2];

  FILE *_big_file = fopen (path, "r");
  int read_cnt;
  bc_bigcharread (fileno (_big_file), (int *)big, 18, &read_cnt);
  if (read_cnt / sizeof (int) / 2 != 18)
    {
      printf ("bad font file (%ld/18)\n", read_cnt / sizeof (int) / 2);
      return -1;
    }
  close (fileno (_big_file));

  sc_accumulatorInit ();
  sc_icounterInit ();
  sc_memoryInit ();
  sc_regInit ();
  sc_cacheInit ();
  signal (SIGUSR1, IRC);
  signal (SIGALRM, IRC);
  draw ();
  int quit = 0;
  mt_setcursorvisible (0);
  while (!quit)
    {

      rk_mytermregime (RK_MODE_NONCANONICAL, 0.5, 0, 0, 1);
      enum keys key;
      rk_readkey (&key);
      int block_input;
      if (sc_regGet (SC_FLAG_IGNORECLK, &block_input) && block_input == 1
          && key != KEY_R)
        return 0;
      if (key == KEY_UNKNOWN)
        continue;
      switch (key)
        {
        case KEY_UP:
          mem_cp_y--;
          if (mem_cp_y < 0)
            {
              if (mem_cp_x >= 8)
                mem_cp_y = 11;
              else
                mem_cp_y = 12;
            }
          print_memarr (mem_cp_x + mem_cp_y * 10);
          break;
        case KEY_DOWN:
          mem_cp_y++;
          if (mem_cp_y > 11 && mem_cp_x >= 8)
            mem_cp_y = 0;
          if (mem_cp_y > 12 && mem_cp_x < 8)
            mem_cp_y = 0;
          print_memarr (mem_cp_x + mem_cp_y * 10);
          break;
        case KEY_LEFT:
          mem_cp_x--;
          if (mem_cp_x < 0 && mem_cp_y != 12)
            mem_cp_x = 9;
          if (mem_cp_x < 0 && mem_cp_y == 12)
            mem_cp_x = 7;
          print_memarr (mem_cp_x + mem_cp_y * 10);
          break;
        case KEY_RIGHT:
          mem_cp_x++;
          if ((mem_cp_x > 9 && mem_cp_y != 12)
              || (mem_cp_x > 7 && mem_cp_y == 12))
            mem_cp_x = 0;
          print_memarr (mem_cp_x + mem_cp_y * 10);
          break;
        case KEY_ENTER:
          mt_gotoXY (((mem_cp_x + mem_cp_y * 10) / 10) + 2,
                     ((mem_cp_x + mem_cp_y * 10) % 10) * 6 + 2);
          int value;
          rk_readvalue (&value, 1, big, printBigCell,
                        printDecodedCommandBlock);
          sc_memorySet ((mem_cp_x + mem_cp_y * 10), value);
          print_memarr (mem_cp_x + mem_cp_y * 10);
          break;
        case KEY_ESC:
          mt_clrscr ();
          mt_gotoXY (0, 0);
          mt_setcursorvisible (1);
          mt_setdefaultcolor ();
          rk_mytermrestore ();
          quit = 1;
          break;
        case KEY_F5:
          mt_gotoXY (2, 68);
          int value_acc;
          rk_readvalue (&value_acc, 1, big, printBigCell,
                        printDecodedCommandBlock);
          sc_accumulatorSet (value_acc);
          printAccumulator ();
          break;
        case KEY_F6:
          mt_gotoXY (5, 77);
          int value_ic;
          rk_readvalue (&value_ic, 1, big, printBigCell,
                        printDecodedCommandBlock);
          sc_icounterSet (value_ic);
          printCounters ();
          break;
        case KEY_S:
          mt_gotoXY (27, 1);
          rk_mytermsave ();
          rk_mytermregime (RK_MODE_CANONICAL, 0, 0, 1, 1);
          prompt ("Имя файла для сохранения: ");
          char fname[512];
          read (STDIN_FILENO, fname, 512);
          prompt ("Сохраняю...");
          if (!sc_memorySave (fname))
            prompt ("Успешно сохранено!");
          else
            prompt ("Ошибка! sc_memorySave вернул -1.");
          rk_mytermrestore ();
          break;
        case KEY_L:
          mt_gotoXY (27, 1);
          rk_mytermsave ();
          rk_mytermregime (RK_MODE_CANONICAL, 0, 0, 1, 1);
          prompt ("Имя файла для загрузки: ");
          char lfname[512];
          read (STDIN_FILENO, lfname, 512);
          prompt ("Загружаю...");
          if (!sc_memoryLoad (lfname))
            prompt ("Загружено!");
          else
            prompt ("Ошибка! sc_memoryLoad вернул -1.");
          print_memarr (mem_cp_x + mem_cp_y * 10);
          rk_mytermrestore ();
          break;
        case KEY_I:
          raise (SIGUSR1);
          draw ();
          break;
        case KEY_T:
          IRC (900);
          break;
        case KEY_R:
          sc_regInit ();
          sc_regSet (SC_FLAG_IGNORECLK, 0);
          sc_cacheInit ();
          print_memarr (-1);
          printFlags ();

          struct itimerval nval, oval;
          nval.it_interval.tv_sec = 0;
          nval.it_interval.tv_usec = 100000;
          nval.it_value.tv_sec = 0;
          nval.it_value.tv_usec = 100000;
          setitimer (ITIMER_REAL, &nval, &oval);

          break;
        default:
          break;
        }
    }
}
