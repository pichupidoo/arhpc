#ifndef RK_VARIABLES_H
#define RK_VARIABLES_H

#include <termios.h>

#define MIN_BUF_SIZE 6
extern char buffer[MIN_BUF_SIZE];
extern struct termios save;

#endif // RK_VARIABLES_H
