#include <gb/gb.h>
#include <rand.h>
#include <stdio.h>
#include <stdlib.h>
#include <types.h>

#include "tiles/prey_tiles.h"
#include "tiles/snake_body.h"
#include "tiles/snake_map.h"
#include "tiles/snake_sprite.h"

typedef struct SnakeStruct {
  UINT8 pos_x;
  UINT8 pos_y;
  UINT8 speed;
  UBYTE last_direction;
} SnakeCharacter;

typedef struct PreyStruct {
  UINT8 pos_x;
  UINT8 pos_y;
  UINT8 tile;
  UINT8 active;
} PreyCharacter;

// Rotates the head sprite based on direction.
// TODO(juanitobebe): Maybe fix the bug reseting flags.
// I kind of like the way it moves.
void RotateSnakeHead(UBYTE direction) {
  switch (direction) {
    case J_LEFT:
      set_sprite_prop(0, get_sprite_prop(0) | S_FLIPX);
      break;
    case J_RIGHT:
      set_sprite_prop(0, get_sprite_prop(0) & ~S_FLIPX);
      break;
    case J_UP:
      set_sprite_prop(0, get_sprite_prop(0) & ~S_FLIPY);
      break;
    case J_DOWN:
      set_sprite_prop(0, get_sprite_prop(0) | S_FLIPY);
      break;
    default:
      break;
  }
}

// Animates the mouth based on current direction.
// If the mouth is closed then we open it, if it was open then we close it.
// TODO(juanitobebe): I liked it more before but I guess I don't really need it.
void AnimateMouth(UBYTE direction) {
  // Head sprite tiles are:
  //   0: Closed Horizontal
  //   1: Open Horizontal
  //   2: Closed Vertical
  //   3: Open Vertical
  UINT8 current_tile = get_sprite_tile(0);
  UBYTE is_mouth_closed = (current_tile == 0 || current_tile == 2) ? 1 : 0;

  switch (direction) {
    case J_LEFT:
    case J_RIGHT:
      set_sprite_tile(0, (is_mouth_closed) ? 1 : 0);
      break;
    case J_UP:
    case J_DOWN:
      set_sprite_tile(0, (is_mouth_closed) ? 3 : 2);
  }
}

// Move character respecting bounds and paintig a movement trial.
void MoveSnake(SnakeCharacter* snake_c) {
  // Get Visible grid current location
  UINT8 grid_x = (snake_c->pos_x - 8) / 8;
  UINT8 grid_y = (snake_c->pos_y - 16) / 8;

  // SnakeMap is an array that represents every background tile (20 * 18).
  // A SnakeMap tile is changed to the corresponding tile representing
  // movement of the snake; current_map_index calculates grid_x, grid_y
  // into the array position.
  unsigned long current_map_index = grid_y * 20 + grid_x;
  if (snake_c->last_direction == J_LEFT && grid_x > 0) {
    snake_c->pos_x -= snake_c->speed;
    SnakeMap[current_map_index] = 0x1;
  }

  if (snake_c->last_direction == J_RIGHT && grid_x < 19) {
    snake_c->pos_x += snake_c->speed;
    SnakeMap[current_map_index] = 0x1;
  }

  if (snake_c->last_direction == J_UP && grid_y > 0) {
    snake_c->pos_y -= snake_c->speed;
    SnakeMap[current_map_index] = 0x2;
  }

  if (snake_c->last_direction == J_DOWN && grid_y < 17) {
    snake_c->pos_y += snake_c->speed;
    SnakeMap[current_map_index] = 0x2;
  }
}

// Generates a random number within [min, max].
int random(int min, int max) { return min + abs(rand()) % ((max + 1) - min); }

// Spawns a prey
// TODO(juanitobebe): Make it more random
void InitPrey(PreyCharacter* prey_c) {
  // The compiler is doing wrong conversion from int to UINT8. So as a
  // workaround I'm casting to usigned int before.
  prey_c->pos_x = (unsigned int)random(8, 160);
  prey_c->pos_y = (unsigned int)random(16, 152);
  prey_c->tile = (unsigned int)random(4, 5);
}

void UpdatePrey(PreyCharacter* prey_c, UINT8 eating) {
  if (eating) {
    InitPrey(prey_c);
  }
}

void UpdateSwitches() {
  HIDE_WIN;
  SHOW_SPRITES;
  SHOW_BKG;
}

void PerformantDelay(UINT8 num_loops) {
  for (UINT8 i = 0; i < num_loops; i++) {
    wait_vbl_done();
  }
}

void Draw(SnakeCharacter* snake_c, PreyCharacter* prey_c) {
  // Draw background
  set_bkg_tiles(0, 0, 20, 18, SnakeMap);

  // Draw Snake
  move_sprite(0, snake_c->pos_x, snake_c->pos_y);

  // Draw prey
  move_sprite(1, prey_c->pos_x, prey_c->pos_y);
  set_sprite_tile(1, prey_c->tile);
}

// Returns 1 if there's a collition with the prey, 0 if not.
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

void main() {
  // Initialize Background
  set_bkg_data(0, 3, SnakeBody);
  set_bkg_tiles(0, 0, 20, 18, SnakeMap);

  // Initialize characters
  // Snake
  set_sprite_data(0, 4, Snake);
  SnakeCharacter snake_c;
  snake_c.speed = 8;
  snake_c.pos_x = 64;
  snake_c.pos_y = 40;
  // Prey
  PreyCharacter prey_c;
  set_sprite_data(4, 2, PreyTiles);
  InitPrey(&prey_c);

  // TODO(juanitobebe): This seed is wrong.
  initrand(392);

  UINT8 eating = 0;
  while (1) {
    // Register Input
    switch (joypad()) {
      case J_LEFT:
        snake_c.last_direction = J_LEFT;
        break;
      case J_RIGHT:
        snake_c.last_direction = J_RIGHT;
        break;
      case J_UP:
        snake_c.last_direction = J_UP;
        break;
      case J_DOWN:
        snake_c.last_direction = J_DOWN;
        break;
      default:
        break;
    }

    // Logic
    MoveSnake(&snake_c);
    eating = EatingPreyCollision(&snake_c, &prey_c);
    RotateSnakeHead(snake_c.last_direction);
    AnimateMouth(snake_c.last_direction);
    UpdatePrey(&prey_c, eating);

    Draw(&snake_c, &prey_c);

    // House keeping
    UpdateSwitches();
    PerformantDelay(8);
  }
}
