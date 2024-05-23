#include "sc_variables.h"
#include <mySimpleComputer.h>
int
sc_cacheGet (int address, int *value)
{
  // при получении из кэша задержка + 1
  int tcounter = 0;
  sc_delayGet (&tcounter);
  sc_delaySet (tcounter + 1);

  // проверка на оверфлоу
  if (address < 0 || address > 127)
    {
      sc_regSet (SC_FLAG_INTOVERFLOW, 1);
      return -1;
    }

  // адрес начиная от которого забраем в кэщ
  int l1_address = (address / 10) * 10;

  int flag = 0;
  while (1)
    {
      // всего 5 линий кэща
      for (int i = 0; i < 5; i++)
        {
          // если строка закеширована
          if (SC_CACHE[i].start_address == l1_address)
            {
              // забираем значение сразу
              *value = SC_CACHE[i].str[address % 10];
              // время доступа к строке 0
              SC_CACHE[i].str_time = 0;
              // выходим
              flag = 1;
            }
          else
            {
              // время доступа к строке ++
              SC_CACHE[i].str_time++;
            }
        }
      // нашлось значение из кэша -- выходим
      if (flag)
        {
          return 0;
        }
      // грузим из памяти
      if (sc_cacheLoad (l1_address))
        {
          return -1;
        }
    }
}