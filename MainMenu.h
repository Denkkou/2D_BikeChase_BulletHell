#ifndef aMainMenuFile
#define aMainMenuFile

/* The main menu container */
#include <SDL.h>
#include <vector>

#include "FPSDelayTimer.h"
#include "Vector2D.h"
#include "MenuButton.h"
//#include "InterfaceDecoration.h"

class MainMenu {
public:
	MainMenu();
	~MainMenu();

	int Run(SDL_Renderer* gameRenderer);

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
	bool isRunning;
	int returned;
	enum returnOption { NewGame, HiScore, Options, Quit };

	//mouse location
	int mPosX, mPosY;
	bool isClicked;

	//vectors to store menu objects
	std::vector<MenuButton*> listOfButtons;

	//std::vector<InterfaceDecoration*> listOfDecorations;
		//decorations might be sprites, effects, animations etc
};
#endif