#include <gb/gb.h>

#include "sprites/snake_sprite.h"

void main() {
  set_sprite_data(0, 2, Snake);
  set_sprite_tile(0, 0);
  move_sprite(0, 88, 78);
  SHOW_SPRITES;

  UINT8 current_sprite = 0;
  while (1) {
    current_sprite = current_sprite ? 0 : 1;
    set_sprite_tile(0, current_sprite);
    delay(1000);
  }
}