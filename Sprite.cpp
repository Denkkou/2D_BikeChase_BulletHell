#include "Sprite.h"

Sprite::Sprite() {
}

Sprite::~Sprite() {
	if (texture != nullptr)
		SDL_DestroyTexture(texture);
}

void Sprite::Init(int xPos, int yPos, int widthPix, int heightPix) {
	//initialise source rectangle
	srcRect.w = widthPix;
	srcRect.h = heightPix;

	//initialise target rect
	dstRect.x = xPos;
	dstRect.y = yPos;
	dstRect.w = widthPix;
	dstRect.h = heightPix;
}

void Sprite::Load(SDL_Renderer* gameRenderer, const char* filePath) {
	texture = IMG_LoadTexture(gameRenderer, filePath);
}

void Sprite::UpdateDimensions(int newX, int newY) {
	dstRect.x = newX;
	dstRect.y = newY;
}

//overloaded UpdateDimensions to change width and height too
void Sprite::UpdateDimensions(int newX, int newY, int newW, int newH) {
	dstRect.x = newX;
	dstRect.y = newY;
	dstRect.w = newW;
	dstRect.h = newH;
}

void Sprite::Render(SDL_Renderer* gameRenderer) {
	SDL_RenderCopy(gameRenderer, texture, &srcRect, &dstRect);
}
