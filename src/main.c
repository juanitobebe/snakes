#include <gb/gb.h>
#include <stdio.h>
#include <types.h>

#include "sprites/snake_sprite.h"

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

void main() {
  set_sprite_data(0, 4, Snake);
  set_sprite_tile(0, 0);
  SHOW_SPRITES;
  DISPLAY_ON;

  // Character control
  UINT8 SPEED = 10;  // TODO(juanitobebe): Move it to some constant file?
  UINT8 head_x = 88;
  UINT8 head_y = 78;
  move_sprite(0, head_x, head_y);

  while (1) {
    // Move Sprite
    switch (joypad()) {
      case J_LEFT:
        scroll_sprite(0, -SPEED, 0);
        break;
      case J_RIGHT:
        scroll_sprite(0, SPEED, 0);
        break;
      case J_UP:
        scroll_sprite(0, 0, -SPEED);
        break;
      case J_DOWN:
        scroll_sprite(0, 0, SPEED);
        break;
      default:
        break;
    }
    // Animate according to direction
    RotateHead(joypad());
    AnimateMouth(joypad());
    delay(200);
  }
}