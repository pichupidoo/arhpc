#define GET_BIT_VALUE(REGISTER, NUMBER) ((REGISTER >> (NUMBER - 1)) & 1)
#define SET_BIT_ZERO(REGISTER, NUMBER)                                        \
  REGISTER = (REGISTER & (~(1 << (NUMBER - 1))))
#define SET_BIT(REGISTER, NUMBER) REGISTER = (REGISTER | (1 << (NUMBER - 1)))

#define SC_OVERFLOW 16
#define SC_DIVIDING_BY_ZERO 8
#define SC_OUT_OF_MEMORY 4
#define SC_INVALID_COMMAND 2
#define SC_THROTTLE 1

int sc_accumulatorGet (int *value);
int sc_accumulatorInit (void);
int sc_accumulatorSet (int value);
int sc_commandDecode (int value, int *sign, int *command, int *operand);
int sc_commandEncode (int sign, int command, int operand, int *value);
int sc_commandValidate (int command);
int sc_icounterGet (int *value);
int sc_icounterInit (void);
int sc_icounterSet (int value);
int sc_memoryGet (int address, int *value);
int sc_memoryInit (void);
int sc_memoryLoad (char *filename);
int sc_memorySave (char *filename);
int sc_memorySet (int adress, int value);
int sc_regGet (int sc_register, int *value);
int sc_regInit (void);
int sc_regSet (int sc_register, int value);
int sc_cacheGet (int address, int *value);
int sc_cacheSet (int address, int value);
int sc_cacheInit (void);
int sc_tcounterSet (unsigned char value);
int sc_tcounterGet (unsigned char *value);
int sc_tcounterInit (void);
int sc_cachelineGet (int line_number, int *cacheline);
int sc_setIgnoreCache (int value);
int sc_delayInit (void);
int sc_delaySet (int value);
int sc_delayGet (int *value);