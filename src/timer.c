#include "timer.h"

#include <types.h>

static UBYTE time = 0;

UBYTE GetTimeFromTimer() { return time; }

void AddToTimer() { time++; }