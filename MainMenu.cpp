#include "MainMenu.h"

MainMenu::MainMenu() {
	//initialise members
	isRunning = true;
	isClicked = false;
	returned = -1;

	//fade resources
	fadeRect.w = 1600;
	fadeRect.h = 900;

	//how many frames to fade out for
	fadeDurationFrames = 120;
	fadeFrameCounter = 0;
	fadeRectAlpha = 0;
}

int MainMenu::Run(SDL_Renderer* gameRenderer) {
	//build menu
	ConstructMenu(gameRenderer);

	//game loop
	while (isRunning) {
		timer.resetTicks();

		//check if returned has a value if not fading
		if (!isFading && returned != -1) {
			isRunning = false;
			return returned;
		}

		//core functions
		Input();
		Update();
		Render(gameRenderer);

		//delay for rest of frame
		if (timer.getTicks() < DELTA_TIME)
			SDL_Delay(DELTA_TIME - timer.getTicks());
	}
}

void MainMenu::Input() {
	//get mouse input
	while (SDL_PollEvent(&event)) {
		//get mouse position
		SDL_GetMouseState(&mPosX, &mPosY);

		//poll event types
		switch (event.type) {
		case SDL_QUIT:
			returned = Quit;
			break;
		case SDL_MOUSEBUTTONDOWN:
			isClicked = true;
			SDL_Log("Mouse Clicked at X: %i, Y: %i", mPosX, mPosY);
			break;
		case SDL_MOUSEBUTTONUP:
			isClicked = false;
			SDL_Log("Mouse Released at X: %i, Y: %i", mPosX, mPosY);
			break;
		}
	}
}

//load graphics, build the menu
void MainMenu::ConstructMenu(SDL_Renderer* gameRenderer) {
	//load the menu button textures
	menuButtonTextures = IMG_LoadTexture(gameRenderer, menuButtonPath);

	//construct the menu buttons
	AddButton(1150, 545, 400, 70, NewGame);
	AddButton(1150, 625, 400, 70, HiScore);
	AddButton(1150, 705, 400, 70, Options);
	AddButton(1150, 785, 400, 70, Quit);
}

void MainMenu::Update() {
	//if we are fading, advance the fade-out
	if (isFading) {
		if (fadeFrameCounter < fadeDurationFrames) {
			fadeFrameCounter++;

			//change alpha each frame
			fadeRectAlpha += (255 / fadeDurationFrames) + 1;

			if (fadeRectAlpha > 255)
				fadeRectAlpha = 255;
		}
		else
			isFading = false;
	}

	//mange mouseover and click for every button
	for (auto& button : listOfButtons) {
		if (DetectMouseOver(mPosX, mPosY, button)) {
			button->Highlight(true);

			//detect click
			if (isClicked == true && !isFading) {
				isFading = true;
				returned = button->buttonReturnValue;
			}
		}
		else
			button->Highlight(false);
	}
}

//detect if mouse is within boundaries of UI object
bool MainMenu::DetectMouseOver(int mouseX, int mouseY, MenuButton* menuButton) { 
	if (mouseX > menuButton->dstRect.x &&
		mouseX < menuButton->dstRect.x + menuButton->dstRect.w &&
		mouseY > menuButton->dstRect.y &&
		mouseY < menuButton->dstRect.y + menuButton->dstRect.h) {
		return true;
	}
	else 
		return false;
}

//create a new button, push back into vector
void MainMenu::AddButton(int x, int y, int w, int h, int rtnVal) {
	//add a new button to the vector of buttons
	MenuButton* aButton = new MenuButton(x, y, w, h, rtnVal, menuButtonTextures);
	this->listOfButtons.push_back(aButton);
}

void MainMenu::Render(SDL_Renderer* gameRenderer) {
	//clear screen for drawing
	SDL_SetRenderDrawColor(gameRenderer, 100, 100, 100, 255);
	SDL_RenderClear(gameRenderer);

	//draw button graphics
	for (auto& button : listOfButtons) {
		button->Render(gameRenderer);
	}

	SDL_SetRenderDrawBlendMode(gameRenderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(gameRenderer, 0, 0, 0, fadeRectAlpha);
	SDL_RenderFillRect(gameRenderer, &fadeRect);

	//push changes
	SDL_RenderPresent(gameRenderer);
}

MainMenu::~MainMenu(){
	//clear buttons from memory
	for (auto& button : listOfButtons){
		delete button;
	}

}