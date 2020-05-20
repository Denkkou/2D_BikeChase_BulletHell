#ifndef aMenuButtonFile
#define aMenuButtonFile

#include <SDL.h>

class MenuButton {
public:
	MenuButton(int btnX, int btnY, int btnW, int btnH, int rtnVal);
	~MenuButton();

	void Highlight(bool flag);
	void Render(SDL_Renderer* gameRenderer);

	SDL_Rect button;
	int buttonReturnValue;
private:
	bool highlighted;

	//texture for a sprite
};

#endif
