#include "console.h"
#include <myReadKey.h>
#include <mySimpleComputer.h>
#include <myTerm.h>
#include <signal.h>
#include <unistd.h>
void
CPUINFO_C (void) // 0x01
{
  mt_gotoXY (20, 79);
  mt_print ("Жур Андрей Александрович, ИС-241");
  for (int i = 0; i < 4; i++)
    {
      mt_gotoXY (21 + i, 79);
      mt_print (" ");
    }
  sleep (2);
  printInfo ();
}
void
READ_C (int cell_number) // 0x0A
{
  sc_regSet (SC_THROTTLE, 1);
  sc_setIgnoreCache (1);
  printTerm (cell_number, 1);
  sc_setIgnoreCache (0);
  rk_mytermregime (0, 1, 0, 0, 0);
  sc_regSet (SC_THROTTLE, 0);
}
int
WRITE_C (int cell_number) // 0x0B
{
  if (printTerm (cell_number, 0) == -2)
    return -2;
  return 0;
}
int
LOAD_C (int cell_number) // 0x14
{
  int value;
  if (sc_memoryGet (cell_number, &value) == -2)
    return -2;
  sc_accumulatorSet (value);
  return 0;
}
int
STORE_C (int cell_number) // 0x15
{
  int value;
  sc_accumulatorGet (&value);
  if (sc_memorySet (cell_number, value) == -2)
    return -2;
  return 0;
}
void
JUMP_C (int cell_number) // 0x28
{
  sc_icounterSet (cell_number);
}
void
JNEG_C (int cell_number) // 0x29
{
  int value;
  sc_accumulatorGet (&value);
  if ((value >> 14) > 0)
    {
      sc_icounterSet (cell_number);
    }
}
void
JZ_C (int cell_number) // 0x2A
{
  int value;
  sc_accumulatorGet (&value);
  if ((value & 0x3FFF) == 0)
    {
      sc_icounterSet (cell_number);
    }
}
void
HALT_C (void)
{
  sc_regSet (SC_THROTTLE, 1);
}
void
JNS_C (int cell_number) // 0x37
{
  int value;
  sc_accumulatorGet (&value);
  if (((value >> 14) == 0) && (value & 0x3FFF) != 0)
    {
      sc_icounterSet (cell_number);
    }
}
void
JC_C (int cell_number) // 0x38
{
  int value = 0;
  sc_regGet (SC_OVERFLOW, &value);
  if (value)
    {
      sc_icounterSet (cell_number);
    }
}
void
JNC_C (int cell_number) // 0x39
{
  int value = 0;
  sc_regGet (SC_OVERFLOW, &value);
  if (!value)
    {
      sc_icounterSet (cell_number);
    }
}
void
JP_C (int cell_number) // 0x3A
{
  int value;
  sc_accumulatorGet (&value);
  if ((value & 0x3FFF) % 2 == 0)
    {
      sc_icounterSet (cell_number);
    }
}
void
JNP_C (int cell_number) // 0x3B
{
  int value;
  sc_accumulatorGet (&value);
  if ((value & 0x3FFF) % 2 != 0)
    {
      sc_icounterSet (cell_number);
    }
}
int
MOVA_C (int cell_number) // 0x47
{
  int value;
  int address;
  sc_accumulatorGet (&address);
  if (sc_memoryGet (cell_number, &value) == -2)
    return -2;
  if (sc_memorySet (address & 0x7F, value) == -2)
    return -2;
  return 0;
}
int
MOVR_C (int cell_number) // 0x48
{
  int value;
  int address;
  sc_accumulatorGet (&address);
  if (sc_memoryGet (address & 0x7F, &value) == -2)
    return -2;
  if (sc_memorySet (cell_number, value) == -2)
    return -2;
  return 0;
}
int
MOVCA_C (int cell_number) // 0x49
{
  int value;
  int address_from;
  int address_to;
  sc_accumulatorGet (&address_from);
  if (sc_memoryGet (address_from & 0x7F, &address_to) == -2)
    return -2;
  if (sc_memoryGet (cell_number, &value) == -2)
    return -2;
  if (sc_memorySet (address_to & 0x7F, value) == -2)
    return -2;
  return 0;
}
void
CU (void)
{
  int command_number;
  int memory_value;
  int sign;
  int value;
  int operand;
  int returned;
  sc_icounterGet (&command_number);
  sc_setIgnoreCache (0);
  returned = sc_memoryGet (command_number, &memory_value);
  if (returned == -1)
    {
      sc_regSet (SC_OUT_OF_MEMORY, 1);
      sc_regSet (SC_THROTTLE, 1);
      return;
    }
  if (returned == -2)
    return;
  if (sc_commandDecode (memory_value, &sign, &value, &operand))
    {
      sc_regSet (SC_INVALID_COMMAND, 1);
      sc_regSet (SC_THROTTLE, 1);
      return;
    }
  if (sc_commandValidate (value) || sign == 1)
    {
      sc_regSet (SC_INVALID_COMMAND, 1);
      sc_regSet (SC_THROTTLE, 1);
      return;
    }
  switch (value)
    {
    case NOP:
      break;
    case CPUINFO:
      CPUINFO_C ();
      break;
    case READ:
      READ_C (operand);
      break;
    case WRITE:
      if (WRITE_C (operand) == -2)
        return;
      break;
    case LOAD:
      if (LOAD_C (operand) == -2)
        return;
      break;
    case STORE:
      if (STORE_C (operand) == -2)
        return;
      break;
    case JUMP:
      JUMP_C (operand);
      break;
    case JNEG:
      JNEG_C (operand);
      break;
    case JZ:
      JZ_C (operand);
      break;
    case HALT:
      HALT_C ();
      break;
    case JNS:
      JNS_C (operand);
      break;
    case JC:
      JC_C (operand);
      break;
    case JNC:
      JNC_C (operand);
      break;
    case JP:
      JP_C (operand);
      break;
    case JNP:
      JNP_C (operand);
      break;
    case MOVA:
      if (MOVA_C (operand) == -2)
        return;
      break;
    case MOVR:
      if (MOVR_C (operand) == -2)
        return;
      break;
    case MOVCA:
      if (MOVCA_C (operand) == -2)
        return;
      break;
    case NOT:
      if (sc_memorySet (operand, alu (value, operand)) == -2)
        return;
      break;
    default:
      returned = alu (value, operand);
      if (returned == 1000000)
        return;
      sc_accumulatorSet (returned);
    }
  int new_command_number;
  sc_icounterGet (&new_command_number);
  if (new_command_number == command_number)
    if (sc_icounterSet (command_number + 1))
      sc_regSet (SC_THROTTLE, 1);
}