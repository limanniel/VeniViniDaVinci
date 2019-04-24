#include "GameScreenMainMenu.h"
#include "Texture2D.h"


GameScreenMainMenu::GameScreenMainMenu(SDL_Renderer* renderer)
	: GameScreen(renderer)
{
	_mainMenuBG = new Texture2D(renderer);
	if (!_mainMenuBG->LoadFromFile("resources/Images/MainMenu.png")) {
		std::cerr << "Failed to load MainMenuBG Texture!";
	}

	// Set up text's
	// Main Menu
	int yOffset = 0;
	for (unsigned int i = 0; i < 3; i++)
	{
		_mainMenuOptions[i] = new Text(mRenderer, MarioFont, new SDL_Rect{ 156, 200 + yOffset, 224, 42 });
		yOffset += 70;
	}
	_mainMenuOptions[0]->CreateText("Start Game", _TextColour, _TextAltColour);
	_mainMenuOptions[1]->CreateText("Level Editor", _TextColour, _TextAltColour);
	_mainMenuOptions[2]->CreateText("Quit Game", _TextColour, _TextAltColour);
	
	// Sub-Menu -> Start game
	yOffset = 0;
	for (unsigned int i = 3; i < 6; i++)
	{
		_mainMenuOptions[i] = new Text(mRenderer, MarioFont, new SDL_Rect{ 156, 200 + yOffset, 224, 42 });
		_mainMenuOptions[i]->SetHidden(true);
		yOffset += 70;
	}
	_mainMenuOptions[3]->CreateText("Single Player", _TextColour, _TextAltColour);
	_mainMenuOptions[4]->CreateText("2 Player", _TextColour, _TextAltColour);
	_mainMenuOptions[5]->CreateText("Back", _TextColour, _TextAltColour);
}


GameScreenMainMenu::~GameScreenMainMenu()
{
	for (unsigned int i = 0; i < 6; i++)
	{
		delete _mainMenuOptions[i];
	}

	delete _mainMenuBG;
	_mainMenuBG = nullptr;
}

void GameScreenMainMenu::Render()
{
	_mainMenuBG->Render(Vector2D(0.0f, 0.0f), SDL_FLIP_NONE, 0.0f);
	for (unsigned int i = 0; i < 6; i++)
	{
		_mainMenuOptions[i]->Render();
	}

}

void GameScreenMainMenu::Update(float deltaTime, SDL_Event event)
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	SDL_Rect mouseRect = { x, y, 16, 16 };

	for (unsigned int i = 0; i < 6; i++)
	{
		// If mouse hoovered over option, highlight and activate according case upon LMB press
		if (!_mainMenuOptions[i]->GetHiddenState() && Collisions::Instance()->Box(mouseRect, *_mainMenuOptions[i]->GetPosition())) {
			_mainMenuOptions[i]->SetHooveredState(true);

			bool trigger = false;

			if (!trigger && SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
				switch (i)
				{
				case 0:
					SwitchToSubMenu();
					break;
				case 1:
					break;
				case 2:
					QUIT_GAME = true;
					break;
				case 5:
					SwitchToSubMenu();
					trigger = true;
					break;
				default:
					break;
				}
			}
		}
		else {
			_mainMenuOptions[i]->SetHooveredState(false);
		}
	}
}

void GameScreenMainMenu::SwitchToSubMenu()
{
	for (unsigned int i = 0; i < 6; i++)
	{
		if (_mainMenuOptions[i]->GetHiddenState())
			_mainMenuOptions[i]->SetHidden(false);
		else
			_mainMenuOptions[i]->SetHidden(true);
	}
}

