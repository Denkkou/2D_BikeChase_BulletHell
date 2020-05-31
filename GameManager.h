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
#include "Sprite.h"
//#include "Entity.h"

#define SCROLL_SPEED (20)

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

	int currentLives;
	int currentScore;

	//input fields
	SDL_Event _event;
	const Uint8* keystate = SDL_GetKeyboardState(NULL);

	//std::vector<Entity*> gameEntitiesVector;

	//restricted area of the viewport
	SDL_Rect gameField;
	Sprite gameFieldSpriteA;
	Sprite gameFieldSpriteB;
	

	SDL_Rect gameViewportBacking;
	Sprite windowFrame;
};
#endif