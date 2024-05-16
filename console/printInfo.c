#include <myTerm.h>
void
printInfo ()
{
  mt_gotoXY (20, 79);
  mt_print ("l - load s - save i - reset");
  mt_gotoXY (21, 79);
  mt_print ("r - run t - step");
  mt_gotoXY (22, 79);
  mt_print ("ESC - выход");
  mt_gotoXY (23, 79);
  mt_print ("F5 - accumulator");
  mt_gotoXY (24, 79);
  mt_print ("F6 - instruction counter");
}