#pragma once
#include <SDL.h>
#include "Commons.h"

class GameScreen;
class GameScreenLevel1;
class GameScreenMainMenu;
class GameScreenLevelEditor;
class GameScreenLevel2;

class GameScreenManager
{
private:
	SDL_Renderer* mRenderer;
	GameScreen* mCurrentScreen;

	bool QUIT_GAME{ false };

public:
	GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen);
	~GameScreenManager();

	void Render();
	void Update(double deltaTime, SDL_Event event);
	void ChangeScreen(SCREENS newScreen);

	inline bool CheckWhetherToQuit() const { return QUIT_GAME; }
};
