#include "GameScreen.h"

GameScreen::GameScreen(SDL_Renderer* renderer)
	: mRenderer(renderer)
{
	mCursor = SDL_GetDefaultCursor();
	MarioFont = TTF_OpenFont("resources/Images/Mario64.ttf", 256);
}

GameScreen::~GameScreen()
{
	SDL_FreeCursor(mCursor);
	mCursor = nullptr;

	TTF_CloseFont(MarioFont);
	MarioFont = nullptr;

	mRenderer = nullptr;
}

void GameScreen::Update(float deltaTime, SDL_Event event)
{
}

SCREENS GameScreen::GetWhichScreenToChangeTo() 
{
	SCREEN_CHANGE = false;
	return SCREEN;
}

void GameScreen::Render()
{
}