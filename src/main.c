#include <gb/gb.h>
#include <rand.h>
#include <stdio.h>
#include <stdlib.h>
#include <types.h>

#include "prey.h"
#include "prey_character.h"
#include "snake.h"
#include "snake_character.h"
#include "snake_prey.h"
#include "tiles/prey_tiles.h"
#include "tiles/snake_body.h"
#include "tiles/snake_map.h"
#include "tiles/snake_sprite.h"
#include "timer.h"
#include "utils.h"

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
    AddToTimer();

    // Register Input
    UBYTE snake_previous_direction, snake_new_direction;
    snake_previous_direction = snake_new_direction = snake_c.direction;
    switch (joypad()) {
      case J_LEFT:
        snake_new_direction = J_LEFT;
        break;
      case J_RIGHT:
        snake_new_direction = J_RIGHT;
        break;
      case J_UP:
        snake_new_direction = J_UP;
        break;
      case J_DOWN:
        snake_new_direction = J_DOWN;
        break;
      default:
        break;
    }

    // Move periodically
    if ((GetTimeFromTimer() & (UBYTE)0x03) == 0) {
      MoveSnake(&snake_c, snake_new_direction, snake_previous_direction);
    }

    // Collision
    alive = !SnakeCollision(&snake_c, snake_previous_direction);
    eating = EatingPreyCollision(&snake_c, &prey_c);

    if (alive) {
      // Animation
      RotateSnakeHead(snake_c.direction);
      AnimateMouth(snake_c.direction);

      // Prey handling
      if (eating) {
        snake_c.size += 1;
        SpawnPrey(&prey_c, &snake_c);
      } else if (IsSpecialPrey(&prey_c) && PreyTimeout(&prey_c)) {
        SpawnPrey(&prey_c, &snake_c);
      }

      Draw(&snake_c, &prey_c);
    }

    // House keeping
    UpdateSwitches();
    PerformantDelay(1);
  }

  SplashGameOver();
}
