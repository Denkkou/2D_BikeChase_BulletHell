#include "GameManager.h"

GameManager::GameManager() {
	//initialise world state
	gameRunning = true;
	isPaused = false;

	//initialise the gameField
	gameField.x = 30;
	gameField.y = 30;
	gameField.w = 1200;
	gameField.h = 840;
}

void GameManager::Run(SDL_Renderer* gameRenderer) {
	//frame timer
	FPSDelayTimer timer;
	const int DELTA_TIME = 16;

	//core loop
	while (gameRunning) {
		timer.resetTicks();

		Input(gameRenderer);
		Update();
		Render(gameRenderer);

		//delay for rest of frame
		if (timer.getTicks() < DELTA_TIME)
			SDL_Delay(DELTA_TIME - timer.getTicks());
	}
}

void GameManager::Input(SDL_Renderer* gameRenderer) {
	//polling for key presses
	while (SDL_PollEvent(&_event)) {
		//timestamp
		SDL_Keycode keyPressed = _event.key.keysym.sym;
		char timestr[32];
		timeGetter.getTime(timestr, 32);

		//log a key down
		if (_event.type == SDL_KEYDOWN && !_event.key.repeat)
			SDL_Log("[%s] [KEY DOWN] | time %d;  char %s; (InputHandler.cpp)", timestr, _event.key.timestamp, SDL_GetKeyName(keyPressed));
		//log a key up
		if (_event.type == SDL_KEYUP && !_event.key.repeat)
			SDL_Log("[%s] [KEY UP]   | time %d; char %s; (InputHandler.cpp)", timestr, _event.key.timestamp, SDL_GetKeyName(keyPressed));

		if (_event.type == SDL_QUIT)
			gameRunning = false;
	}

	//reset acceleration every tick
	player.accelerationX = 0;
	player.accelerationY = 0;

	//directional movement
	if (keystate[SDL_SCANCODE_UP]) { player.MoveUp(); }
	else if (player.velocity.Y < 0) { player.accelerationY = 1; }
	if (keystate[SDL_SCANCODE_DOWN]) { player.MoveDown(); }
	else if (player.velocity.Y > 0) { player.accelerationY = -1; }
	if (keystate[SDL_SCANCODE_LEFT]) { player.MoveLeft(); }
	else if (player.velocity.X < 0) { player.accelerationX = 1; }
	if (keystate[SDL_SCANCODE_RIGHT]) { player.MoveRight(); }
	else if (player.velocity.X > 0) { player.accelerationX = -1; }

	//combat functions
	if (keystate[SDL_SCANCODE_Z]) { player.AttackLeft(); }
	if (keystate[SDL_SCANCODE_X]) { player.Shoot(); }
	if (keystate[SDL_SCANCODE_C]) { player.AttackRight(); }

	//slowdown function
	if (keystate[SDL_SCANCODE_LSHIFT]) { player.SlowDown(true); }
	else { player.SlowDown(false); }

	if (keystate[SDL_SCANCODE_ESCAPE]){ /*pause*/ }
}

void GameManager::Update() {
	player.Update(gameField);
}

void GameManager::Render(SDL_Renderer* gameRenderer) {
	SDL_SetRenderDrawColor(gameRenderer, 0, 0, 0, 255);
	SDL_RenderClear(gameRenderer);
	
	//draw background
	SDL_SetRenderDrawColor(gameRenderer, 0, 0, 100, 255);
	SDL_RenderFillRect(gameRenderer, &gameField);

	//draw player
	player.Render(gameRenderer);

	//loop entities vector
	//draw window decoration

	//push changes
	SDL_RenderPresent(gameRenderer);
}

GameManager::~GameManager() {
	//delete vector of entities
}
