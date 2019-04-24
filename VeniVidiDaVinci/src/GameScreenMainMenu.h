#pragma once
#include "GameScreen.h"

class Texture2D;

class GameScreenMainMenu : public GameScreen
{
private:
	Texture2D* _mainMenuBG;

	// Text
	/// <summary>
	///	0. Start Game 
	///	<para/>1. Level Editor
	///	<para/>2. Quit Game
	///	<para/>1.3. Single Player
	///	<para/>1.4. 2 Player
	///	<para/>1.5. Back
	/// </summary>
	Text* _mainMenuOptions[6];

	SDL_Color _TextColour{ 255,255,255 };
	SDL_Color _TextAltColour{ 255,146,30 };
	
	void UpdateButtons(SDL_Rect& mouse, SDL_Event event);
	void ButtonAction(int index);
	void FlipMenu();

public:
	GameScreenMainMenu(SDL_Renderer* renderer);
	~GameScreenMainMenu();

	void Render();
	void Update(float deltaTime, SDL_Event event);
};

