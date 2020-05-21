#ifndef aMainMenuFile
#define aMainMenuFile

/* The main menu container */
#include <SDL.h>
#include <SDL_image.h>
#include <vector>

#include "FPSDelayTimer.h"
#include "Vector2D.h"
#include "MenuButton.h"
//#include "InterfaceDecoration.h"

class MainMenu {
public:
	enum returnOption { NewGame, HiScore, Options, Quit };

	MainMenu();
	~MainMenu();

	int Run(SDL_Renderer* gameRenderer);
	void ConstructMenu(SDL_Renderer* gameRenderer);

	void Input();
	void Update();
	void Render(SDL_Renderer* gameRenderer);

	//utility
	void AddButton(int x, int y, int w, int h, int rtnVal);
private:
	//functions
	bool DetectMouseOver(int mouseX, int mouseY, MenuButton* button);

	//objects
	FPSDelayTimer timer;
	const int DELTA_TIME = 16;
	SDL_Event event;

	//flags and enums
	int returned;

	//mouse location
	int mPosX, mPosY;
	bool isClicked;

	//vectors to store menu objects
	std::vector<MenuButton*> listOfButtons;

	//std::vector<InterfaceDecoration*> listOfDecorations;
		//decorations might be sprites, effects, animations etc

	SDL_Texture* menuButtonTextures = nullptr;
	const char* menuButtonPath = "./Content/Sprites/MenuButtons_Sheet.png";

	//fade out
	bool isFading;
	int fadeDurationFrames;
	int fadeFrameCounter;
	int fadeRectAlpha;
	SDL_Rect fadeRect;
};
#endif
