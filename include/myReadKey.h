#pragma once
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define RK_MODE_NONCANONICAL 0
#define RK_MODE_CANONICAL 1

#define MIN_BUF_SIZE 6

extern struct termios current, backup;
enum keys
{
  key_UNDEFINED,
  key_0 = 0,
  key_1,
  key_2,
  key_3,
  key_4,
  key_5,
  key_6,
  key_7,
  key_8,
  key_9,
  key_A = 10,
  key_B,
  key_C,
  key_D,
  key_E,
  key_F,

  key_ESC = 16,

  key_L,
  key_S,
  key_R,
  key_T,
  key_I,
  key_F5,
  key_F6,
  key_UP,
  key_DOWN,
  key_LEFT,
  key_RIGHT,
  key_ENTER,
  NOTHING_KEY,
  INVALID_KEY,
  key_BACKSPACE,
  key_UNKNOWN,

  key_plus = 45,
  key_minus = 43
};
int rk_readkey (enum keys *key);
int rk_mytermsave (void);
int rk_mytermregime (int regime, int vtime, int vmin, int echo, int sigint);
int rk_mytermrestore (void);
int rk_readvalue (int *value, int timeout, long *big, void (*printBig) (long *, char *, int), void (*pdc) (int));