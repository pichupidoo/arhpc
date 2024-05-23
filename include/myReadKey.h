#pragma once
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#define RK_MODE_NONCANONICAL 0
#define RK_MODE_CANONICAL 1

extern struct termios terminal_state;

enum keys
{
  KEY_UNKNOWN = 0,
  KEY_0, // 1
  KEY_1,
  KEY_2,
  KEY_3,
  KEY_4,
  KEY_5,
  KEY_6,
  KEY_7,
  KEY_8,
  KEY_9, // A
  KEY_A, // 0x0B
  KEY_B,
  KEY_C,
  KEY_D,
  KEY_E,
  KEY_F,
  KEY_PLUS,
  KEY_MINUS,
  KEY_L,
  KEY_S,
  KEY_I,
  KEY_R,
  KEY_T,
  KEY_BACKSPACE,
  KEY_ESC,
  KEY_ENTER,
  KEY_F5,
  KEY_F6,
  KEY_UP,
  KEY_DOWN,
  KEY_RIGHT,
  KEY_LEFT
};

int rk_readkey (enum keys *key);
int rk_mytermsave (void);
int rk_mytermrestore (void);
int rk_mytermregime (int regime, int vtime, int vmin, int echo, int sigint);
int rk_readvalue (int *value, int timeout, long *big,
                  void (*printBig) (long *, char *, int), void (*pdc) (int));