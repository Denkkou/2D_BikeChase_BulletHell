#include "GameManager.h"

GameManager::GameManager() {
	//initialise world state
	gameRunning = true;

	//viewport is x30, y30, w1200, h840
	gameViewportBacking.x = 30;
	gameViewportBacking.y = 30;
	gameViewportBacking.w = 1200;
	gameViewportBacking.h = 840;

	//initialise the gameField
	gameField.x = 330;
	gameField.y = 30;
	gameField.w = 600;
	gameField.h = 840;

	//initialise environment sprites
	windowFrame.Init(0, 0, 1600, 900);
	gameFieldSpriteA.Init(gameField.x, 0, gameField.w, 1000);
	gameFieldSpriteB.Init(gameField.x, -1000, gameField.w, 1000);
}

void GameManager::Run(SDL_Renderer* gameRenderer) {
	//frame timer
	FPSDelayTimer timer;
	const int DELTA_TIME = 16;

	//load sprites (make the field sprites pointers to one texture to avoid double loading)
	gameFieldSpriteA.Load(gameRenderer, "./Content/Sprites/MotorwayBackground.png");
	gameFieldSpriteB.Load(gameRenderer, "./Content/Sprites/MotorwayBackground.png");
	windowFrame.Load(gameRenderer, "./Content/Sprites/WindowFrame.png");

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
			SDL_Log("[%s] [KEY DOWN] | time %d; char %s", timestr, _event.key.timestamp, SDL_GetKeyName(keyPressed));	
		//log a key up
		if (_event.type == SDL_KEYUP && !_event.key.repeat)
			SDL_Log("[%s] [KEY UP]   | time %d; char %s", timestr, _event.key.timestamp, SDL_GetKeyName(keyPressed));

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

	//combat functions (implement cooldowns here)
	if (keystate[SDL_SCANCODE_Z]) { player.AttackLeft(); }
	if (keystate[SDL_SCANCODE_X]) { player.Shoot(); }
	if (keystate[SDL_SCANCODE_C]) { player.AttackRight(); }

	//slowdown function
	if (keystate[SDL_SCANCODE_LSHIFT]) { player.SlowDown(true); }
	else { player.SlowDown(false); }

	//pause the game
	if (keystate[SDL_SCANCODE_ESCAPE]) { 
		

	}
}

void GameManager::Update() {
	//update the scrolling scenery
	gameFieldSpriteA.UpdateDimensions(gameFieldSpriteA.dstRect.x, gameFieldSpriteA.dstRect.y += SCROLL_SPEED);
	if (gameFieldSpriteA.dstRect.y + SCROLL_SPEED >= 1000) 
		gameFieldSpriteA.dstRect.y = -1000;
	gameFieldSpriteB.UpdateDimensions(gameFieldSpriteB.dstRect.x, gameFieldSpriteB.dstRect.y += SCROLL_SPEED);
	if (gameFieldSpriteB.dstRect.y + SCROLL_SPEED >= 1000)
		gameFieldSpriteB.dstRect.y = -1000;

	//update player
	player.Update(gameField);
}

void GameManager::Render(SDL_Renderer* gameRenderer) {
	SDL_SetRenderDrawColor(gameRenderer, 0, 0, 0, 255);
	SDL_RenderClear(gameRenderer);
	
	//draw background scenery (placeholder atm)
	SDL_SetRenderDrawColor(gameRenderer, 0, 0, 0, 255);
	SDL_RenderFillRect(gameRenderer, &gameViewportBacking);

	//draw gamefield over background
	gameFieldSpriteA.Render(gameRenderer);
	gameFieldSpriteB.Render(gameRenderer);

	//draw player and entities
	player.Render(gameRenderer);

	//draw viewport decoration
	windowFrame.Render(gameRenderer);

	//push changes
	SDL_RenderPresent(gameRenderer);
}

GameManager::~GameManager() {
	//delete vector of entities
}
