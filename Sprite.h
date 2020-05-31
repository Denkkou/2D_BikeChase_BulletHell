#ifndef aSpriteFile
#define aSpriteFile

#include <SDL.h>
#include <SDL_image.h>

//For static sprites that don't animate
class Sprite {
public:
	Sprite();
	~Sprite();

	void Init(int xPos, int yPos, int widthPix, int heightPix);
	void Load(SDL_Renderer* gameRenderer, const char* filePath);

	//update functions to change sprite properties
	void UpdateDimensions(int newX, int newY);
	void UpdateDimensions(int newX, int newY, int newW, int newH);

	void Render(SDL_Renderer* gameRenderer);

	SDL_Rect srcRect;
	SDL_Rect dstRect;
protected:
	SDL_Texture* texture = nullptr;
};

#endif