#include "snake_prey.h"

#include <types.h>

#include "prey.h"
#include "prey_character.h"
#include "snake_character.h"
#include "utils.h"

UINT8 EatingPreyCollision(SnakeCharacter* snake_c, PreyCharacter* prey_c) {
  if ((snake_c->pos_x < (prey_c->pos_x + 8)) &&
      ((snake_c->pos_x + 8) > prey_c->pos_x) &&
      (snake_c->pos_y < (prey_c->pos_y + 8)) &&
      ((snake_c->pos_y + 8) > prey_c->pos_y)) {
    return 1;
  } else {
    return 0;
  }
}

UINT8 PreyStepsOnSnake(PreyCharacter* prey_c, SnakeCharacter* snake_c) {
  if (EatingPreyCollision(snake_c, prey_c)) {
    return 1;
  }

  unsigned long prey_map_index = CordToTileNumber(prey_c->pos_x, prey_c->pos_y);
  for (UINT8 i = 0; i < snake_c->size; i++) {
    if (snake_c->body[i].map_index == prey_map_index) {
      return 1;
    }
  }
  return 0;
}

void SpawnPrey(PreyCharacter* prey_c, SnakeCharacter* snake_c) {
  do {
    InitPrey(prey_c);
  } while (PreyStepsOnSnake(prey_c, snake_c));
}