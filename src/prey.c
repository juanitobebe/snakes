#include "prey.h"

#include <time.h>
#include <types.h>

#include "constants.h"
#include "utils.h"

const UBYTE kSpecialPreyDuration = 2;  // Around "2 seconds", feels more lke 4.
const UBYTE kSpecialPreyTile = 0x4;

void InitPrey(PreyCharacter* prey_c) {
  // The compiler might be doing wrong conversion from int to UINT8. So as a
  // workaround I'm casting to usigned int before.
  UINT8 random_x = (unsigned int)random(kMinX, kMaxX);
  UINT8 random_y = (unsigned int)random(kMinY, kMaxY);
  // Make sure we are on the grid.
  prey_c->pos_x = RoundDown(random_x, 8);
  prey_c->pos_y = RoundDown(random_y, 8);
  prey_c->tile = (unsigned int)random(4, 5);
  prey_c->spawn_time = clock();
}

UINT8 PreyTimeout(PreyCharacter* prey_c) {
  return ((clock() - prey_c->spawn_time) / CLOCKS_PER_SEC) ==
         kSpecialPreyDuration;
}

UINT8 IsSpecialPrey(PreyCharacter* prey_c) {
  return prey_c->tile == kSpecialPreyTile;
}
