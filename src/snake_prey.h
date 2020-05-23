// Module for functions related to both, the snake and the prey.
#ifndef SNAKE_SRC_SNAKE_PREY_H
#define SNAKE_SRC_SNAKE_PREY_H

#include <types.h>

#include "prey_character.h"
#include "snake_character.h"

// Returns 1 if there's a collision with the prey, 0 if not.
UINT8 EatingPreyCollision(SnakeCharacter* snake_c, PreyCharacter* prey_c);

// Returns 1 if the Prey steps over the Snake. 0 if it doesn't.
UINT8 PreyStepsOnSnake(PreyCharacter* prey_c, SnakeCharacter* snake_c);

// Spawns a prey making sure it doesn't step on the snake.
void SpawnPrey(PreyCharacter* prey_c, SnakeCharacter* snake_c);

#endif  // SNAKE_SRC_SNAKE_PREY_H_
