#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <vector>
#include "Commons.h"
#include "Constants.h"
#include "Text.h"
#include "Collisions.h"

class GameScreen
{
protected:
	SDL_Renderer* mRenderer{ nullptr };
	SDL_Cursor* mCursor{ nullptr };
	TTF_Font* MarioFont{ nullptr };

	int mPlayerScore{ 0 };
	
	bool SCREEN_CHANGE{ false };
	SCREENS SCREEN{ SCREEN_MENU };

	bool QUIT_GAME{ false };

public:
	GameScreen(SDL_Renderer* renderer);
	virtual ~GameScreen();

	virtual void Render();
	virtual void Update(double deltaTime, SDL_Event event);


	inline bool CheckWhetherToQuit() const { return QUIT_GAME; }
	inline bool CheckWhetherToChangeScreen() const { return SCREEN_CHANGE; }
	SCREENS GetWhichScreenToChangeTo();
};
