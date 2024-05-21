#include "console.h"

void
CU (void)
{
  static int address; // From IC
  static int value;   // From MEM
  static int sign;    // |
  static int code;    // |
  static int operand; // From Decode
  static int temp_value = __INT_MAX__;
  int acc_value;
  if (sc_icounterGet (&address) || sc_cacheGet (address, &value)
      || sc_commandDecode (value, &sign, &code, &operand) || sign)
    {
      sc_regSet (SC_THROTTLE, 1);
      sc_regSet (SC_INVALID_COMMAND, 1);
      prompt ("[УУ] Произошла ошибка при декодировании команды.");
      printCounters ();
      return;
    }
  printCache ();
  switch (code)
    {
    case 0x00:
      break;
    case 0x01:
      prompt ("Дмитрюк Вячеслав Вячеславович, ИС-241");
      break;
    case 0x0A:
      temp_value = inputTerm (operand);
      sc_cacheSet (operand, temp_value);
      printCache ();
      break;
    case 0x0B:
      printTerm (operand);
      break;
    case 0x14:
      // Load to acc memory addr in operand
      sc_cacheGet (operand, &value);
      printCache ();
      sc_accumulatorSet (value);
      printAccumulator ();
      break;
    case 0x15:
      sc_accumulatorGet (&value);
      sc_cacheSet (operand, value);
      printAccumulator ();
      break;
    case 0x1e:
    case 0x1f:
    case 0x20:
    case 0x21:
    case 0x33:
    case 0x34:
      ALU (code, operand);
      printAccumulator ();
      break;
    case 0x28:
      // sc_cacheGet (operand, &value);
      sc_icounterSet (operand);
      return;
      break;
    case 0x29: // jneg
      sc_accumulatorGet (&acc_value);
      if (acc_value >> 14)
        {
          sc_cacheGet (operand, &value);
          sc_icounterSet (value);
          return;
        }
      break;
    case 0x2a:
      sc_accumulatorGet (&acc_value);
      if (!acc_value)
        {
          sc_cacheGet (operand, &value);
          sc_icounterSet (value);
          return;
        }
      break;
    case 0x2b:
      prompt ("[УУ] Программа завершила работу.");
      sc_regSet (SC_INVALID_COMMAND, 1);
      break;
    case 0x37: // jns
      sc_accumulatorGet (&acc_value);
      if (acc_value >> 14 || !acc_value)
        break;
      sc_icounterSet (operand);
      return;
      break;
    default:
      sc_regSet (SC_THROTTLE, 1);
      sc_regSet (SC_INVALID_COMMAND, 1);
      prompt ("[УУ] Неизвестная команда.");
      return;
    }

  sc_icounterSet (++address);
  // printFlags ();
}