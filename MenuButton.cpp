#include "MenuButton.h"

MenuButton::MenuButton(int btnX, int btnY, int btnW, int btnH, int rtnVal, SDL_Texture* texture) {
	//set up destination rectangle
	dstRect.x = btnX;
	dstRect.y = btnY;
	dstRect.w = btnW;
	dstRect.h = btnH;

	//set properties
	buttonReturnValue = rtnVal;
	tex = texture;

	//modify source rect to appropriate sprite
	srcRect.x = 0;
	srcRect.y = (btnH * rtnVal);
	srcRect.w = btnW;
	srcRect.h = btnH;
}

//if passed true, set the button to highlighted
void MenuButton::Highlight(bool flag) {
	highlighted = flag;
}

void MenuButton::Render(SDL_Renderer* gameRenderer) {
	//set the sprite
	if (highlighted)
		srcRect.y = (dstRect.h * buttonReturnValue) + 280;
	else
		srcRect.y = (dstRect.h * buttonReturnValue);

	//draw sprite to screen
	SDL_RenderCopy(gameRenderer, tex, &srcRect, &dstRect);
}

MenuButton::~MenuButton(){
	//deallocate memory
	if (tex != nullptr)
		SDL_DestroyTexture(tex);
}