#ifndef aPauseScreenOverlayFile
#define aPauseScreenOverlayFile

#include <SDL.h>

class PauseScreenOverlay {
public:
	void Run(SDL_Renderer* gameRenderer);

	void Update();
	void Render();

private:
	bool paused = true;
	SDL_Rect transparencyOverlay;
};

#endif
