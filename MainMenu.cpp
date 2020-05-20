#include "MainMenu.h"

MainMenu::MainMenu() {
	//initialise members
	isRunning = true;
	isClicked = false;
	returned = -1;

	//construct the menu
	AddButton((1600 / 2) - 200, 495, 400, 70, NewGame);
	AddButton((1600 / 2) - 190, 575, 380, 70, HiScore);
	AddButton((1600 / 2) - 180, 655, 360, 70, Options);
	AddButton((1600 / 2) - 170, 735, 340, 70, Quit);
}

int MainMenu::Run(SDL_Renderer* gameRenderer) {
	//game loop
	while (isRunning) {
		timer.resetTicks();

		//core functions
		Input();
		Update();
		Render(gameRenderer);

		//check if returned has a value
		switch (returned) {
		case NewGame: { return NewGame; break; }
		case HiScore: { return HiScore; break; }
		case Options: { return Options; break; }
		case Quit: { return Quit; break; }
		} //potentially run a fade-out before returning

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

void MainMenu::Update() {
	for (auto& button : listOfButtons) {
		if (DetectMouseOver(mPosX, mPosY, button)) {
			button->Highlight(true);

			if (isClicked == true)
				returned = button->buttonReturnValue;
		}
		else
			button->Highlight(false);

	}
}

//detect if mouse is within boundaries of UI object
bool MainMenu::DetectMouseOver(int mouseX, int mouseY, MenuButton* menuButton) { 
	if (mouseX > menuButton->button.x &&
		mouseX < menuButton->button.x + menuButton->button.w &&
		mouseY > menuButton->button.y &&
		mouseY < menuButton->button.y + menuButton->button.h) {
		return true;
	}
	else 
		return false;
}

void MainMenu::AddButton(int x, int y, int w, int h, int rtnVal) {
	//add a new button to the vector of buttons
	MenuButton* aButton = new MenuButton(x, y, w, h, rtnVal);
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

	//push changes
	SDL_RenderPresent(gameRenderer);
}

MainMenu::~MainMenu() {
	//clear buttons from memory
	for (auto& button : listOfButtons){
		delete button;
	}

}