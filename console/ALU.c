#include "console.h"

int
msb (int a) // fixSignBit
{
  if ((a << 14) & 1)
    {
      a &= ~(1 << 14); // обнулить 15
      a *= -1;
    }
  return a;
}

int
usb (int a) // unfixSignBit
{
  if (a < 0)
    {
      a *= -1;
      a |= (1 << 14); // поставить 15
    }
  return a;
}

int
ALU (int command, int operand)
{
  int value;
  int acc_value;
  switch (command)
    {
    case 0x1E: // add
      sc_cacheGet (operand, &value);
      sc_accumulatorGet (&acc_value);
      sc_accumulatorSet (usb (msb (acc_value) + msb (value)));
      break;
    case 0x1F: // sub
      sc_cacheGet (operand, &value);
      sc_accumulatorGet (&acc_value);
      sc_accumulatorSet (usb (msb (acc_value) - msb (value)));
      break;
    case 0x20:
      sc_cacheGet (operand, &value);
      sc_accumulatorGet (&acc_value);
      if (!value)
        {
          prompt ("[АЛУ] Произошло деление на ноль!");
          sc_regSet (SC_FLAG_ZERODIVISION, 1);
          sc_regSet (SC_FLAG_IGNORECLK, 1);
          break;
        }
      sc_accumulatorSet (usb (msb (acc_value) / msb (value)));
      break;
    case 0x21:
      sc_cacheGet (operand, &value);
      sc_accumulatorGet (&acc_value);
      sc_accumulatorSet (usb (msb (acc_value) * msb (value)));
      break;
    case 0x33:
      sc_accumulatorGet (&acc_value);
      sc_accumulatorSet ((~acc_value) & ~(1 << 15));
      break;
    case 0x34:
      sc_cacheGet (operand, &value);
      sc_accumulatorGet (&acc_value);
      sc_accumulatorSet ((acc_value & value) & ~(1 << 15));
      break;

    default:
      prompt ("[АЛУ] Неизвестная команда");
      sc_regSet (SC_FLAG_ZERODIVISION, 1);
      sc_regSet (SC_FLAG_IGNORECLK, 1);
      break;
    }
  return 0;
}