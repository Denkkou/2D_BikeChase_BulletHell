#ifndef aPlayerFile
#define aPlayerFile

#include <SDL.h>
#include <SDL_image.h>
#include "Vector2D.h"

class Player {
public:
	Player();
	~Player();

	void Update(SDL_Rect &gameField);

	void AttackLeft();
	void Shoot();
	void AttackRight();

	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();

	void SlowDown(bool slow);

	void Render(SDL_Renderer* gameRenderer);

	Vector2D velocity;
	int posX, posY;
	int maxVertSpeed;
	int maxHoriSpeed;
	int attackRange;
	int accelerationX;
	int accelerationY;

	SDL_Rect playerRect;
};

#endif