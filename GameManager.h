#ifndef aGameManagementFile
#define aGameManagementFile

/*The Game Management Container*/
#include <SDL.h>
#include <SDL_image.h>
#include <vector>

//includes
#include "FPSDelayTimer.h"
#include "GetTime.h"
#include "Player.h"
//#include "Entity.h"

class GameManager {
public:
	GameManager();
	~GameManager();

	void Run(SDL_Renderer* gameRenderer);

	void Input(SDL_Renderer* gameRenderer);
	void Update();
	void Render(SDL_Renderer* gameRenderer);

	void AddEntity();
	void RemoveEntity();

private:
	//unique ptr to currentLevel
	Player player;
	GetTime timeGetter;

	bool gameRunning;
	bool isPaused;

	int currentLives;
	int currentScore;

	//input fields
	SDL_Event _event;
	const Uint8* keystate = SDL_GetKeyboardState(NULL);

	//std::vector<Entity*> gameEntitiesVector;

	//change this gamefield to restrict where the player
	//can move - this might change when the BG sprites
	//are implemented
	SDL_Rect gameField;
};
#endif