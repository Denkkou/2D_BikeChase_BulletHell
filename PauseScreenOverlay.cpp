#include "PauseScreenOverlay.h"

void PauseScreenOverlay::Run(SDL_Renderer* gameRenderer) {
	transparencyOverlay.x = 0;
	transparencyOverlay.y = 0;
	transparencyOverlay.w = 1600;
	transparencyOverlay.h = 900;

	while (paused) {
		Update();
		Render();
	}
}
