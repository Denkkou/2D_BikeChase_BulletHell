#include "PauseScreenOverlay.h"

PauseScreenOverlay::PauseScreenOverlay() {
	//set up overlay
	transparencyOverlay.x = 0;
	transparencyOverlay.y = 0;
	transparencyOverlay.w = 1600;
	transparencyOverlay.h = 900;
	overlayR = 40;
	overlayG = 140;
	overlayB = 200;
	overlayAlpha = 200;

	//reset paused to true
	paused = true;
}

PauseScreenOverlay::~PauseScreenOverlay() {
}

void PauseScreenOverlay::Run(SDL_Renderer* gameRenderer) {
	//create frame limiter
	FPSDelayTimer timer;
	const int DELTA_TIME = 16;

	while (paused) {
		timer.resetTicks();

		Input();
		Update();
		Render(gameRenderer);

		SDL_Log("loop iterated");

		//delay for rest of frame
		if (timer.getTicks() < DELTA_TIME)
			SDL_Delay(DELTA_TIME - timer.getTicks());
	}
}

void PauseScreenOverlay::Input() {
	
}

void PauseScreenOverlay::Update() {

}

void PauseScreenOverlay::Render(SDL_Renderer* gameRenderer) {
	SDL_SetRenderDrawColor(gameRenderer, overlayR, overlayG, overlayB, overlayAlpha);
	SDL_RenderFillRect(gameRenderer, &transparencyOverlay);
}
