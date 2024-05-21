#include <myBigChars.h>
#include <myReadKey.h>
#include <mySimpleComputer.h>
#include <myTerm.h>
#include <signal.h>
#include <sys/time.h>

void printDecodedCommand (int value);
void printFlags (void);
void printAccumulator (void);
void printCounters (void);
void printCell (int address, enum colors fg, enum colors bg);
void printDecodedCommandBlock (int value);
void printTerm (int address);
int inputTerm (int address);
void printHelp (void);
void printBigCell (long *big, char *str, int index);
void prompt (char *str);
void CU (void);
void IRC (int signum);
void print_memarr (int a);
void printCache ();
int ALU (int command, int operand);