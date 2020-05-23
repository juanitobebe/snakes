#include "snake.h"

#include <gb/gb.h>
#include <types.h>

#include "constants.h"
#include "snake_character.h"
#include "tiles/snake_body.h"
#include "utils.h"

void InitSnake(SnakeCharacter* snake_c) {
  snake_c->speed = 8;
  snake_c->pos_x = 64;
  snake_c->pos_y = 40;
  snake_c->direction = 0;
  snake_c->size = 0;
}

void HandleEating(SnakeCharacter* snake_c, int eating) {
  if (eating) {
    snake_c->size += 1;
  }
}

void MoveSnake(SnakeCharacter* snake_c, UBYTE snake_previous_direction) {
  UINT8 snake_prev_x = snake_c->pos_x;
  UINT8 snake_prev_y = snake_c->pos_y;
  if (snake_c->direction == J_LEFT && snake_c->pos_x > kMinX) {
    snake_c->pos_x -= snake_c->speed;
  }

  if (snake_c->direction == J_RIGHT && snake_c->pos_x < kMaxX) {
    snake_c->pos_x += snake_c->speed;
  }

  if (snake_c->direction == J_UP && snake_c->pos_y > kMinY) {
    snake_c->pos_y -= snake_c->speed;
  }

  if (snake_c->direction == J_DOWN && snake_c->pos_y < kMaxY) {
    snake_c->pos_y += snake_c->speed;
  }

  if ((snake_prev_x != snake_c->pos_x) || (snake_prev_y != snake_c->pos_y)) {
    UpdateBody(snake_c, snake_prev_x, snake_prev_y, snake_previous_direction);
  }
}

UINT8 DetermineTile(UBYTE previous_direction, UBYTE current_direction) {
  if (previous_direction == J_LEFT) {
    if (current_direction == J_LEFT) {
      return kSnakeBody_LEFT;
    }
    if (current_direction == J_UP) {
      return kSnakeBody_LEFT_UP;
    }
    if (current_direction == J_DOWN) {
      return kSnakeBody_LEFT_DOWN;
    }
  }

  if (previous_direction == J_RIGHT) {
    if (current_direction == J_RIGHT) {
      return kSnakeBody_RIGHT;
    }
    if (current_direction == J_UP) {
      return kSnakeBody_RIGHT_UP;
    }
    if (current_direction == J_DOWN) {
      return kSnakeBody_RIGHT_DOWN;
    }
  }

  if (previous_direction == J_UP) {
    if (current_direction == J_LEFT) {
      return kSnakeBody_UP_LEFT;
    }
    if (current_direction == J_RIGHT) {
      return kSnakeBody_UP_RIGHT;
    }
    if (current_direction == J_UP) {
      return kSnakeBody_UP;
    }
  }

  if (previous_direction == J_DOWN) {
    if (current_direction == J_LEFT) {
      return kSnakeBody_DOWN_LEFT;
    }
    if (current_direction == J_RIGHT) {
      return kSnakeBody_DOWN_RIGHT;
    }
    if (current_direction == J_DOWN) {
      return kSnakeBody_DOWN;
    }
  }
  return kSnakeBody_EMPTY;
}

void UpdateBody(SnakeCharacter* snake_c, UINT8 snake_prev_x, UINT8 snake_prev_y,
                UBYTE snake_previous_direction) {
  for (UINT8 i = 0; i < snake_c->size; i++) {
    if (i == snake_c->size - 1) {
      snake_c->body[i].map_index = CordToTileNumber(snake_prev_x, snake_prev_y);
      snake_c->body[i].tile =
          DetermineTile(snake_previous_direction, snake_c->direction);
    } else {
      snake_c->body[i].map_index = snake_c->body[i + 1].map_index;
      snake_c->body[i].tile = snake_c->body[i + 1].tile;
    }
  }
}

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
