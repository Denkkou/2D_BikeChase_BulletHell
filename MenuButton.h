#ifndef aMenuButtonFile
#define aMenuButtonFile

#include <SDL.h>
#include <SDL_image.h>

class MenuButton {
public:
	MenuButton(int btnX, int btnY, int btnW, int btnH, int rtnVal, SDL_Texture* texture);
	~MenuButton();

	void Highlight(bool flag);
	void Render(SDL_Renderer* gameRenderer);

	int buttonReturnValue;

	//sprite variables
	SDL_Texture* tex = nullptr;
	SDL_Rect srcRect;
	SDL_Rect dstRect;
private:
	bool highlighted;
};

#endif
