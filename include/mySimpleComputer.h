#pragma once
#include <memory.h>
#include <stdio.h>
#define SC_MEMARR_SIZE 128
#define SC_FLAG_INTOVERFLOW 0b00010000
#define SC_FLAG_ZERODIVISION 0b00001000
#define SC_FLAG_MEMOOB 0b00000100
#define SC_FLAG_IGNORECLK 0b00000010
#define SC_FLAG_BADOP 0b00000001

typedef struct cache_line
{
  int start_address; // Адрес начала строки
  int str[10];       // Строка значений из памяти
  int str_change;    // Флаг изменения строки
  int str_time; // Давность последнего использования строки
} cache_line;

int sc_memoryInit (void);

int sc_memoryGet (int address, int *value);

int sc_memoryLoad (char *filename);

int sc_memorySave (char *filename);

int sc_memorySet (int address, int value);

int sc_regInit (void);

int sc_regSet (int reg, int value);

int sc_regGet (int reg, int *value);

int sc_accumulatorInit (void);

int sc_accumulatorSet (int value);

int sc_accumulatorGet (int *value);

int sc_icounterInit (void);

int sc_icounterSet (int value);

int sc_icounterGet (int *value);

int sc_delayInit (void);

int sc_delaySet (int value);

int sc_delayGet (int *value);

int sc_commandEncode (int sign, int command, int operand, int *value);

int sc_commandDecode (int value, int *sign, int *command, int *operand);

int sc_commandValidate (int command);

// Кэш
int sc_cacheInit (void);
int sc_cacheSet (int address, int value);
int sc_cacheGet (int address, int *value);
int sc_cacheSave (int address);
int sc_cacheLoad (int address);
extern cache_line SC_CACHE[5];