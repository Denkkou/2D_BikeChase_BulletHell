//libraries
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

//headers
#include "MainMenu.h"
#include "GameManager.h"

//defines and enums
#define SCREEN_WIDTH = 1600;
#define SCREEN_HEIGHT = 900;

int main(int argc, char* argvp[]) {
	//initialise SDL and SDL_image
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) { return 1; }
	else { SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL_Init failed!"); }
	if (IMG_Init(SDL_INIT_EVERYTHING) < 0) { return 1; }
	else { SDL_LogError(SDL_LOG_CATEGORY_ERROR, "IMG_Init failed!"); }

	//create the window and renderer
	SDL_Window* gameWindow = SDL_CreateWindow("2D Bike Chase - Bullet Hell", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1600, 900, 0);
	SDL_Renderer* gameRenderer = SDL_CreateRenderer(gameWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	//initialise
	bool isRunning = true;

	do {
		//create our containers
		MainMenu mainMenu;
		GameManager gameManager;

		switch (mainMenu.Run(gameRenderer)) {
		case MainMenu::NewGame:
			//begin new game, run game manager
			SDL_Log("Starting a New Game");
			gameManager.Run(gameRenderer);
			break;
		case MainMenu::HiScore:
			SDL_Log("High Score returned to source");
			//log hi-score in a file?
			break;
		case MainMenu::Options:
			SDL_Log("Options returned to source");
			//go to the options menu
			break;
		case MainMenu::Quit:
			SDL_Log("Quit returned to source");
			isRunning = false;
			break;
		}
	} while (isRunning);

	//close application
	IMG_Quit();
	SDL_Quit();
	return 0;
}
