// Module for functions related to the Snake.
#ifndef SNAKE_SRC_SNAKE_H
#define SNAKE_SRC_SNAKE_H

#include <gb/gb.h>
#include <types.h>

#include "snake_character.h"

// Initializes the Snake Character
void InitSnake(SnakeCharacter* snake_c);

void HandleEating(SnakeCharacter* snake_c, int eating);

// Move character respecting bounds and paintig a movement trial.
void MoveSnake(SnakeCharacter* snake_c, UBYTE snake_previous_direction);

UINT8 DetermineTile(UBYTE previous_direction, UBYTE current_direction);

// Updates the Snake body block positions in the background.
void UpdateBody(SnakeCharacter* snake_c, UINT8 snake_prev_x, UINT8 snake_prev_y,
                UBYTE snake_previous_direction);

// Rotates the head sprite based on direction.
// TODO(juanitobebe): Maybe fix the bug reseting flags.
// I kind of like the way it moves.
void RotateSnakeHead(UBYTE direction);

// Animates the mouth based on current direction.
// If the mouth is closed then we open it, if it was open then we close it.
// TODO(juanitobebe): I liked it more before but I guess I don't really need it.
void AnimateMouth(UBYTE direction);

// Returns 1 if there's a collision of the Snake head and body, 0 if not.
UINT8
SnakeCollision(SnakeCharacter* snake_c, UBYTE snake_previous_direction);

#endif  // SNAKE_SRC_SNAKE_H
