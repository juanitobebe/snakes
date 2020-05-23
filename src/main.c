#include <gb/gb.h>
#include <rand.h>
#include <stdio.h>
#include <stdlib.h>
#include <types.h>

#include "prey.h"
#include "prey_character.h"
#include "snake.h"
#include "snake_character.h"
#include "tiles/prey_tiles.h"
#include "tiles/snake_body.h"
#include "tiles/snake_map.h"
#include "tiles/snake_sprite.h"
#include "utils.h"

// Returns 1 if there's a collision with the prey, 0 if not.
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

// Returns 1 if the Prey steps over the Snake. 0 if it doesn't.
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

// Spawns a prey making sure it doesn't step on the snake.
void SpawnPrey(PreyCharacter* prey_c, SnakeCharacter* snake_c) {
  do {
    InitPrey(prey_c);
  } while (PreyStepsOnSnake(prey_c, snake_c));
}

void UpdatePrey(PreyCharacter* prey_c, SnakeCharacter* snake_c, UINT8 eating) {
  if (eating) {
    SpawnPrey(prey_c, snake_c);
  }
}

void SetBackground(SnakeCharacter* snake) {
  for (unsigned long i = 0; i < 360; i++) {
    SnakeMap[i] = 0x0;
  }

  for (unsigned long i = 0; i < snake->size; i++) {
    SnakeMap[snake->body[i].map_index] = snake->body[i].tile;
  }
}

void Draw(SnakeCharacter* snake_c, PreyCharacter* prey_c) {
  // Draw background
  SetBackground(snake_c);
  // SnakeMap is an array that represents every background tile (20 * 18).
  // A SnakeMap tile is changed to the corresponding tile representing
  // movement of the snake.
  set_bkg_tiles(0, 0, 20, 18, SnakeMap);

  // Draw Snake
  move_sprite(0, snake_c->pos_x, snake_c->pos_y);

  // Draw prey
  move_sprite(1, prey_c->pos_x, prey_c->pos_y);
  set_sprite_tile(1, prey_c->tile);
}

// Returns 1 if there's a collision of the Snake head and body, 0 if not.
UINT8
SnakeCollision(SnakeCharacter* snake_c, UBYTE snake_previous_direction) {
  // Collided by going into oposite direction.
  if (snake_c->size > 0 &&
      ((snake_c->direction == J_LEFT && snake_previous_direction == J_RIGHT) ||
       (snake_c->direction == J_RIGHT && snake_previous_direction == J_LEFT) ||
       (snake_c->direction == J_UP && snake_previous_direction == J_DOWN) ||
       (snake_c->direction == J_DOWN && snake_previous_direction == J_UP))) {
    return 1;
  }

  // Check background tile positions for collistions.
  unsigned long background_map_index =
      CordToTileNumber(snake_c->pos_x, snake_c->pos_y);
  for (unsigned long i = 0; i < snake_c->size; i++) {
    if (background_map_index == snake_c->body[i].map_index) {
      return 1;
    }
  }

  return 0;
}

void SplashStart() {
  printf("\n \n \n \n \n \n \n       SNAKE \n \n \n \n \n \n    Press Start");
  PerformantDelay(1);
  waitpad(J_START);
  waitpadup();
}

void SplashGameOver() {
  for (unsigned long i = 0; i < 360; i++) {
    SnakeMap[i] = 0x0;
  }
  HIDE_SPRITES;
  printf("\n \n \n \n \n \n \n     GAME OVER");
}

void main() {
  SplashStart();

  // Init random after user input.
  initrand((UWORD)DIV_REG << 8);

  // Initialize Background
  set_bkg_data(0, 13, SnakeBody);
  set_bkg_tiles(0, 0, 20, 18, SnakeMap);

  // Initialize characters
  // Snake
  set_sprite_data(0, 4, Snake);
  SnakeCharacter snake_c;
  InitSnake(&snake_c);

  // Prey
  PreyCharacter prey_c;
  set_sprite_data(4, 2, PreyTiles);
  SpawnPrey(&prey_c, &snake_c);

  UINT8 eating = 0;
  UINT8 alive = 1;
  while (alive) {
    // Register Input
    UBYTE snake_previous_direction = snake_c.direction;
    switch (joypad()) {
      case J_LEFT:
        snake_c.direction = J_LEFT;
        break;
      case J_RIGHT:
        snake_c.direction = J_RIGHT;
        break;
      case J_UP:
        snake_c.direction = J_UP;
        break;
      case J_DOWN:
        snake_c.direction = J_DOWN;
        break;
      default:
        break;
    }

    // Move
    MoveSnake(&snake_c, snake_previous_direction);

    // Collision
    alive = !SnakeCollision(&snake_c, snake_previous_direction);
    eating = EatingPreyCollision(&snake_c, &prey_c);

    // Logic
    if (alive) {
      RotateSnakeHead(snake_c.direction);
      AnimateMouth(snake_c.direction);
      UpdatePrey(&prey_c, &snake_c, eating);
      HandleEating(&snake_c, eating);
      Draw(&snake_c, &prey_c);
    }

    // House keeping
    UpdateSwitches();
    PerformantDelay(8);
  }

  SplashGameOver();
}
