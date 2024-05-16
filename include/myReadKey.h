#pragma once
#include <string.h>
#include <termios.h>
#include <unistd.h>
extern struct termios current, backup;
enum keys
{
  key_UNDEFINED,
  key_0,
  key_1,
  key_2,
  key_3,
  key_4,
  key_5,
  key_6,
  key_7,
  key_8,
  key_9,
  key_A,
  key_B,
  key_C,
  key_D,
  key_E,
  key_F,
  key_plus,
  key_minus,
  key_L,
  key_S,
  key_I,
  key_R,
  key_T,
  key_F5,
  key_F6,
  key_ESC,
  key_ENTER,
  key_UP,
  key_RIGHT,
  key_DOWN,
  key_LEFT
};
int rk_readkey (enum keys *key);
int rk_mytermsave (void);
int rk_mytermregime (int regime, int vtime, int vmin, int echo, int sigint);
int rk_mytermrestore (void);
int rk_readvalue (int *value, int timeout);