#include "utils.h"

#include <gb/gb.h>
#include <rand.h>
#include <stdlib.h>

int random(int min, int max) { return min + abs(rand()) % ((max + 1) - min); }

UINT8 RoundDown(UINT8 n, UINT8 m) { return (n / m) * m; }

inline unsigned long CordToTileNumber(UINT8 x, UINT8 y) {
  UINT8 grid_x = (x - 8) / 8;
  UINT8 grid_y = (y - 16) / 8;
  return grid_y * 20 + grid_x;
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