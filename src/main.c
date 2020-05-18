#include <gb/gb.h>
#include <stdio.h>
#include <types.h>

#include "tiles/snake_body.h"
#include "tiles/snake_map.h"
#include "tiles/snake_sprite.h"

typedef struct SnakeStruct {
  UINT8 pos_x;
  UINT8 pos_y;
  UINT8 speed;
  UBYTE last_direction;
} SnakeCharacter;

// Rotates the head sprite based on direction.
// TODO(juanitobebe): Maybe fix the bug reseting flags.
// I kind of like the way it moves.
void RotateHead(UBYTE direction) {
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

  move_sprite(0, snake_c->pos_x, snake_c->pos_y);
  set_bkg_tiles(0, 0, 20, 18, SnakeMap);
}

void UpdateSwitches() {
  HIDE_WIN;
  SHOW_SPRITES;
  SHOW_BKG;
}

void main() {
  set_sprite_data(0, 4, Snake);
  set_sprite_tile(0, 0);
  DISPLAY_ON;

  // Initialize Background
  set_bkg_data(0, 3, SnakeBody);
  set_bkg_tiles(0, 0, 20, 18, SnakeMap);

  // Character control
  SnakeCharacter snake_c;
  snake_c.speed = 8;
  snake_c.pos_x = 64;
  snake_c.pos_y = 40;
  MoveSnake(&snake_c);

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

    // Move sprites
    MoveSnake(&snake_c);

    // Animate
    RotateHead(snake_c.last_direction);
    AnimateMouth(snake_c.last_direction);

    // House keeping
    UpdateSwitches();
    delay(150);
    wait_vbl_done();
  }
}
