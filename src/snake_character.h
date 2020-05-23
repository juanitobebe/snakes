// Struct representing a Snake and its body.
#ifndef SNAKE_SRC_SNAKE_CHARACTER_H
#define SNAKE_SRC_SNAKE_CHARACTER_H
#include <types.h>

typedef struct BodyNodeStruct {
  UINT8 tile;
  unsigned long map_index;  // Expensive!
} BodyNode;

typedef struct SnakeStruct {
  UINT8 pos_x;
  UINT8 pos_y;
  UINT8 speed;
  UBYTE direction;
  UINT8 size;
  BodyNode body[369];
} SnakeCharacter;

#endif  // SNAKE_SRC_SNAKE_CHARACTER_H
