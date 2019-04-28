#include "GameScreen.h"

Mix_Music* GameScreen::LoadMusic(Mix_Music* musicVar, const char* path)
{
	if (musicVar != nullptr)
	{
		delete musicVar;
	}
	musicVar = Mix_LoadMUS(path);
	return musicVar;
}

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

	Mix_FreeMusic(_backgroundMusic);

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