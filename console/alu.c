#include "console.h"
#include <mySimpleComputer.h>
int
ADD_C (int cell_number)
{
  int accumulator_value, memory_value;
  sc_accumulatorGet (&accumulator_value);
  if (sc_memoryGet (cell_number, &memory_value) == -2)
    return 1000000;
  return (((accumulator_value << 17) + (memory_value << 17)) >> 17) & 0x7FFF;
}
int
SUB_C (int cell_number)
{
  int accumulator_value, memory_value;
  sc_accumulatorGet (&accumulator_value);
  if (sc_memoryGet (cell_number, &memory_value) == -2)
    return 1000000;
  return (((accumulator_value << 17) + ((~memory_value + 1) << 17)) >> 17)
         & 0x7FFF;
}
int
DIVIDE_C (int cell_number)
{
  int accumulator_value, memory_value;
  sc_accumulatorGet (&accumulator_value);
  if (sc_memoryGet (cell_number, &memory_value) == -2)
    return 1000000;
  if (memory_value == 0)
    {
      sc_regSet (SC_DIVIDING_BY_ZERO, 1);
      sc_regSet (SC_THROTTLE, 1);
      return accumulator_value;
    }
  int accumulator_sign = accumulator_value >> 14;
  int memory_sign = memory_value >> 14;
  accumulator_value = accumulator_value << 17;
  memory_value = memory_value << 17;
  int value = (accumulator_value / memory_value) & 0x3FFF;
  if (accumulator_sign ^ memory_sign)
    value = value | 0x4000;
  return value;
}
int
MUL_C (int cell_number)
{
  int accumulator_value, memory_value;
  sc_accumulatorGet (&accumulator_value);
  if (sc_memoryGet (cell_number, &memory_value) == -2)
    return 1000000;
  int accumulator_sign = accumulator_value >> 14;
  int memory_sign = memory_value >> 14;
  if (accumulator_sign)
    accumulator_value = ~(accumulator_value - 1);
  if (memory_sign)
    memory_value = ~(memory_value - 1);
  int value = (accumulator_value * memory_value) & 0x3FFF;
  if (accumulator_sign ^ memory_sign)
    value = ((~value & 0x3FFF) + 1) | 0x4000;
  return value;
}
int
NOT_C (void)
{
  int memory_value;
  sc_accumulatorGet (&memory_value);
  return ((~(memory_value << 17)) >> 17) & 0x7FFF;
}
int
AND_C (int cell_number)
{
  int accumulator_value, memory_value;
  sc_accumulatorGet (&accumulator_value);
  if (sc_memoryGet (cell_number, &memory_value) == -2)
    return 1000000;
  return accumulator_value & memory_value;
}
int
OR_C (int cell_number)
{
  int accumulator_value, memory_value;
  sc_accumulatorGet (&accumulator_value);
  if (sc_memoryGet (cell_number, &memory_value) == -2)
    return 1000000;
  return accumulator_value | memory_value;
}
int
XOR_C (int cell_number)
{
  int accumulator_value, memory_value;
  sc_accumulatorGet (&accumulator_value);
  if (sc_memoryGet (cell_number, &memory_value) == -2)
    return 1000000;
  return accumulator_value ^ memory_value;
}
int
CHL_C (int cell_number)
{
  int memory_value;
  if (sc_memoryGet (cell_number, &memory_value) == -2)
    return 1000000;
  return ((memory_value << 18) >> 17) & 0x7FFF;
}
int
SHR_C (int cell_number)
{
  int memory_value;
  if (sc_memoryGet (cell_number, &memory_value) == -2)
    return 1000000;
  return memory_value >> 1;
}
int
RCL_C (int cell_number)
{
  int memory_value;
  if (sc_memoryGet (cell_number, &memory_value) == -2)
    return 1000000;
  return ((memory_value << 1) | (memory_value >> 14)) & 0x3FFF;
}
int
RCR_C (int cell_number)
{
  int memory_value;
  if (sc_memoryGet (cell_number, &memory_value) == -2)
    return 1000000;
  return ((memory_value >> 1) | (memory_value << 14)) & 0x3FFF;
}
int
NEG_C (int cell_number)
{
  int memory_value;
  if (sc_memoryGet (cell_number, &memory_value) == -2)
    return 1000000;
  return (-(memory_value << 17) >> 17) & 0x7FFF;
}
int
ADDC_C (int cell_number)
{
  int accumulator_value, memory_value1, memory_value2;
  sc_accumulatorGet (&accumulator_value);
  if (sc_memoryGet (cell_number, &memory_value1) == -2)
    return 1000000;
  if (sc_memoryGet (accumulator_value & 0x3F, &memory_value2) == -2)
    return 1000000;
  return (((memory_value1 << 17) + (memory_value2 << 17)) >> 17);
}
int
SUBC_C (int cell_number)
{
  int accumulator_value, memory_value1, memory_value2;
  sc_accumulatorGet (&accumulator_value);
  if (sc_memoryGet (cell_number, &memory_value1) == -2)
    return 1000000;
  if (sc_memoryGet (accumulator_value & 0x3F, &memory_value2) == -2)
    return 1000000;
  return (((memory_value1 << 17) - (memory_value2 << 17)) >> 17);
}
int
alu (int command, int operand)
{
  switch (command)
    {
    case ADD:
      return ADD_C (operand);
    case SUB:
      return SUB_C (operand);
    case DIVIDE:
      return DIVIDE_C (operand);
    case MUL:
      return MUL_C (operand);
    case NOT:
      return NOT_C ();
    case AND:
      return AND_C (operand);
    case OR:
      return OR_C (operand);
    case XOR:
      return XOR_C (operand);
    case CHL:
      return CHL_C (operand);
    case SHR:
      return SHR_C (operand);
    case RCL:
      return RCL_C (operand);
    case RCR:
      return RCR_C (operand);
    case NEG:
      return NEG_C (operand);
    case ADDC:
      return ADDC_C (operand);
    case SUBC:
      return SUBC_C (operand);
    }
  return 0;
}