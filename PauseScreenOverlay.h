#ifndef aPauseScreenOverlayFile
#define aPauseScreenOverlayFile

#include <SDL.h>
#include "FPSDelayTimer.h"

class PauseScreenOverlay {
public:
	PauseScreenOverlay();
	~PauseScreenOverlay();

	void Run(SDL_Renderer* gameRenderer);

	void Input();
	void Update();
	void Render(SDL_Renderer* gameRenderer);

private:
	bool paused;

	SDL_Rect transparencyOverlay;
	int overlayR;
	int overlayG;
	int overlayB;
	int overlayAlpha;
};

#endif
