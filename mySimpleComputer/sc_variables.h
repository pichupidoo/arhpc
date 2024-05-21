#pragma once
#define SC_MEMARR_SIZE 128
#define SC_CACHE_SIZE 5
#define SC_OVERFLOW 16
#define SC_DIVIDING_BY_ZERO 8
#define SC_OUT_OF_MEMORY 4
#define SC_INVALID_COMMAND 2
#define SC_THROTTLE 1
extern int SC_MEMARR[SC_MEMARR_SIZE];
extern int SC_ACCUMULATOR;
extern int SC_ICOUNTER;
extern unsigned char SC_TCOUNTER;
extern int SC_FLAGS;
extern int SC_IGNORE_CACHE;
extern int SC_REG_DELAY; 
typedef struct sc_cache_line
{
  int address;
  int downtime;
  int line[10];
} cacheline;
extern cacheline cache[SC_CACHE_SIZE];