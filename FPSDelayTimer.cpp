#include "FPSDelayTimer.h"

FPSDelayTimer::FPSDelayTimer() {
	startTicks = 0;
}

void FPSDelayTimer::resetTicks() {
	startTicks = SDL_GetTicks();
}

int FPSDelayTimer::getTicks() {
	return (SDL_GetTicks() - startTicks);
}