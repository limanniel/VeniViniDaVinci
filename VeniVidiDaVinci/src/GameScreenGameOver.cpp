#include "GameScreenGameOver.h"



GameScreenGameOver::GameScreenGameOver(SDL_Renderer* renderer)
	: GameScreen(renderer)
{
	_bgTexture = new Texture2D(renderer);
	_bgTexture->LoadFromFile("resources/Images/GameOver.png");

	_ReturnToMainMenu = new Text(renderer, MarioFont, new SDL_Rect{ 50, 380, 412, 64 });
	_ReturnToMainMenu->CreateText("Return to MainMenu", _textColour, _altTextColour);
}


GameScreenGameOver::~GameScreenGameOver()
{
	delete _bgTexture;
	_bgTexture = nullptr;
	delete _ReturnToMainMenu;
	_ReturnToMainMenu = nullptr;
}

void GameScreenGameOver::Render()
{
	_bgTexture->Render(Vector2D(0.0f, 0.0f), SDL_FLIP_NONE);
	_ReturnToMainMenu->Render();
}

void GameScreenGameOver::Update(float deltaTime, SDL_Event event)
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	SDL_Rect mouseRect = { x, y, 16, 16 };

	// Check if cursor is hoovering over button
	if (Collisions::Instance()->Box(mouseRect, *_ReturnToMainMenu->GetPosition()))
	{
		_ReturnToMainMenu->SetHooveredState(true);

		// Check if button is hidden
		if (!_ReturnToMainMenu->GetHiddenState())
		{

			// Check whether button is pressed
			switch (event.type)
			{
				// Apply appropriate action to corresponding button pressed
			case SDL_MOUSEBUTTONDOWN:
				if (event.button.button == SDL_BUTTON_LEFT)
				{
					_ReturnToMainMenu->SetTriggered(true);
					SCREEN = SCREEN_MENU;
					SCREEN_CHANGE = true;
				}
				break;

			case SDL_MOUSEBUTTONUP:
				if (event.button.button == SDL_BUTTON_LEFT)
					_ReturnToMainMenu->SetTriggered(false);
				break;

			default:
				break;
			}
		}
	}
	// Return to original text colour when not hoovered over
	else
	{
		_ReturnToMainMenu->SetHooveredState(false);
	}
}
