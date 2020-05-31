#include "Player.h"

Player::Player() {
	//set initial spawn
	posX = 1200/2 + 15;
	posY = 3 * (900/4) + 30;

	//set player size
	playerRect.w = 32;
	playerRect.h = 64;
}

Player::~Player(){}

void Player::Update(SDL_Rect& gameField) {
	//update playerRect
	playerRect.x = posX;
	playerRect.y = posY;

	//prevent the player from leaving gameField
	if (posX < gameField.x) posX = gameField.x;
	if (posX + (playerRect.w) > gameField.x + gameField.w) posX = gameField.x + gameField.w - (playerRect.w);
	if (posY < gameField.y) posY = gameField.y;
	if (posY + (playerRect.h) > gameField.y + gameField.h) posY = gameField.y + gameField.h - (playerRect.h);

	//cap horizontal at maximum speed
	if (velocity.X > maxHoriSpeed)
		velocity.X = maxHoriSpeed;
	if (velocity.X < -maxHoriSpeed)
		velocity.X = -maxHoriSpeed;

	//cap vertical at maximum speed
	if (velocity.Y > maxVertSpeed)
		velocity.Y = maxVertSpeed;
	if (velocity.Y < -maxVertSpeed)
		velocity.Y = -maxVertSpeed;

	//update positions
	velocity.X += accelerationX;
	posX += velocity.X;
	velocity.Y += accelerationY;
	posY += velocity.Y;
}

//behaviour functions
void Player::AttackLeft() {
	SDL_Log("Player Attacked Left");
}

void Player::Shoot() {
}

void Player::AttackRight() {
	SDL_Log("Player Attacked Right");
}

void Player::MoveUp() {
	accelerationY = -1;
}

void Player::MoveDown() {
	accelerationY = 1;
}

void Player::MoveLeft() {
	accelerationX = -1;
}

void Player::MoveRight() {
	accelerationX = 1;
}

void Player::SlowDown(bool slow) {
	if (slow) {
		maxHoriSpeed = HORIZONTAL_MAX_SPEED / 2;
		maxVertSpeed = VERTICAL_MAX_SPEED / 2;
	}
	else {
		maxHoriSpeed = HORIZONTAL_MAX_SPEED;
		maxVertSpeed = VERTICAL_MAX_SPEED;
	}
}

void Player::Render(SDL_Renderer* gameRenderer) {
	SDL_SetRenderDrawColor(gameRenderer, 0, 255, 0, 255);
	SDL_RenderFillRect(gameRenderer, &playerRect);
}
