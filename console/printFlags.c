#include <mySimpleComputer.h>
#include <myTerm.h>
#include <stdio.h>
void
printFlags (void)
{
  int P, ZERO, M, T, E;
  if (sc_regGet (SC_OVERFLOW, &P))
    {
      mt_print ("Error!\n");
      return;
    }
  if (sc_regGet (SC_DIVIDING_BY_ZERO, &ZERO))
    {
      mt_print ("Error!\n");
      return;
    }
  if (sc_regGet (SC_OUT_OF_MEMORY, &M))
    {
      mt_print ("Error!\n");
      return;
    }
  if (sc_regGet (SC_THROTTLE, &T))
    {
      mt_print ("Error!\n");
      return;
    }
  if (sc_regGet (SC_INVALID_COMMAND, &E))
    {
      mt_print ("Error!\n");
      return;
    }
  mt_gotoXY (2, 90);
  if (P == 0)
    mt_print ("_ ");
  else
    mt_print ("P ");
  mt_gotoXY (2, 93);
  if (ZERO == 0)
    mt_print ("_ ");
  else
    mt_print ("0 ");
  mt_gotoXY (2, 96);
  if (M == 0)
    mt_print ("_ ");
  else
    mt_print ("M ");
  mt_gotoXY (2, 99);
  if (T == 0)
    mt_print ("_ ");
  else
    mt_print ("T ");
  mt_gotoXY (2, 102);
  if (E == 0)
    mt_print ("_ ");
  else
    mt_print ("E ");
}