// Struct representing a Prey.
#ifndef SNAKE_SRC_PREY_CHARACTER_H
#define SNAKE_SRC_PREY_CHARACTER_H

#include <types.h>

typedef struct PreyStruct {
  UINT8 pos_x;
  UINT8 pos_y;
  UINT8 tile;
  UINT8 active;
  clock_t spawn_time;
} PreyCharacter;

#endif  // SNAKE_SRC_PREY_CHARACTER_H
