#include "MenuButton.h"

MenuButton::MenuButton(int btnX, int btnY, int btnW, int btnH, int rtnVal) {
	button.x = btnX;
	button.y = btnY;
	button.w = btnW;
	button.h = btnH;

	buttonReturnValue = rtnVal;
}

//if passed true, set the button to highlighted
void MenuButton::Highlight(bool flag) {
	highlighted = flag;
}

void MenuButton::Render(SDL_Renderer* gameRenderer) {
	if (!highlighted)
		SDL_SetRenderDrawColor(gameRenderer, 0, 0, 0, 255);
	else
		SDL_SetRenderDrawColor(gameRenderer, 255, 255, 255, 255);

	SDL_RenderFillRect(gameRenderer, &button);
}

MenuButton::~MenuButton(){}