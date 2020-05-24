// Module for functions related to the Prey
#ifndef SNAKE_SRC_PREY_H
#define SNAKE_SRC_PREY_H

#include "prey_character.h"

// Initializes a prey character.
void InitPrey(PreyCharacter* prey_c);

// Returns 1 if the prey time has passed, 0 if not.
UINT8 PreyTimeout(PreyCharacter* prey_c);

// Returns 1 if the prey is special, 0 if not.
UINT8 IsSpecialPrey(PreyCharacter* prey_c);

#endif  // SNAKE_SRC_PREY_H
