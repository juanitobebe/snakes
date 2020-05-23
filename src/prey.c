#include "prey.h"

#include <types.h>

#include "constants.h"
#include "utils.h"

void InitPrey(PreyCharacter* prey_c) {
  // The compiler might be doing wrong conversion from int to UINT8. So as a
  // workaround I'm casting to usigned int before.
  UINT8 random_x = (unsigned int)random(MIN_X, MAX_X);
  UINT8 random_y = (unsigned int)random(MIN_Y, MAX_Y);
  // Make sure we are on the grid.
  prey_c->pos_x = RoundDown(random_x, 8);
  prey_c->pos_y = RoundDown(random_y, 8);
  prey_c->tile = (unsigned int)random(4, 5);
}
