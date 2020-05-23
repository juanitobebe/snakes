#include <types.h>

// Generates a random number within [min, max].
// Make sure to initialize random with initrand first.
int random(int min, int max);

// Rounds dowm n to multiple of m.
UINT8 RoundDown(UINT8 n, UINT8 m);

// Translates x,y coordinates to a tile number [0-359].
inline unsigned long CordToTileNumber(UINT8 x, UINT8 y);

// Updates switches for game loop.
void UpdateSwitches();

// Waits for the vertical blank interrupt (VBL) to finish num_loops times.
// This causes a delay.
void PerformantDelay(UINT8 num_loops);